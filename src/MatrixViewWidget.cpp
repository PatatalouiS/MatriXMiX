

#include "MatrixViewWidget.h"
#include <QHeaderView>
#include <QVBoxLayout>


MatrixViewWidget::MatrixViewWidget (const MatrixLibrary* lib, QWidget* parent) : QTableView (parent)
{
    this->lib = lib;
    matrixModel = new QStandardItemModel(0,3, this);


    matrixModel->setHorizontalHeaderLabels({"Nom", "NbL", "NbC"});

    setModel(matrixModel);
    setSortingEnabled(true);
    setColumnWidth(0, 100);
    setFixedWidth(200);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    verticalHeader()->hide();
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setShowGrid(false);
    setAlternatingRowColors(true);
    setStyleSheet("* {alternate-background-color: lightBlue;background-color: white;"
                  "border: 1px solid silver; border-radius:6px;}"
                  "QHeaderView::section { background:"
                  "qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 "
                  "lightBlue, stop: 1 blue); color:white; border: 0px; }");
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	refresh();
}

const QString MatrixViewWidget:: nameOfSelectedMatrix() const
{
    if(currentIndex().isValid())
    {
        return matrixModel->item(currentIndex().row())->text();
    }
    else
    {
        return "";
    }
}


void MatrixViewWidget::refresh(std::function<bool(Matrix*)> filter)
{       
    matrixModel->removeRows(0, matrixModel->rowCount());

    Matrix* matrix;
    QString matrixName;
    QList<QStandardItem*> line;

    for(auto i : lib->data())
    {
        line.clear();
        matrix = &(i.second);

        if(filter(matrix))
        {
            matrixName = QString(i.first.data());
            line.append(new QStandardItem(matrixName));
            line.append(new QStandardItem(QString::number(matrix->getNbRows())));
            line.append(new QStandardItem(QString::number(matrix->getNbCols())));
            matrixModel->appendRow(line);
        }
    }
    sortByColumn(0, Qt::AscendingOrder);
}


void MatrixViewWidget:: addNewRow (const QString name, const Matrix matrix)
{
    QList<QStandardItem*> line;
    line.append(new QStandardItem(name));
    line.append(new QStandardItem(QString::number(matrix.getNbRows())));
    line.append(new QStandardItem(QString::number(matrix.getNbRows())));
    matrixModel->appendRow(line);
    sortByColumn(0, Qt::AscendingOrder);
}


void MatrixViewWidget:: removeRow (const int id)
{
    matrixModel->removeRow(id);
    sortByColumn(0, Qt::AscendingOrder);
}



MatrixViewWidget:: ~MatrixViewWidget ()
{
}
