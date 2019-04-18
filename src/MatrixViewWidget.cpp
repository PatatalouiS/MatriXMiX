

#include "MatrixViewWidget.h"
#include <QHeaderView>
#include <QVBoxLayout>


MatrixViewWidget::MatrixViewWidget (MatrixLibrary* lib, QWidget* parent) : QTableView (parent)
{
    this->lib = lib;
    matrixModel = new QStandardItemModel(0,3, this);

    matrixModel->setHorizontalHeaderLabels({"Nom", "NbL", "NbC"});

    setModel(matrixModel);
    setSortingEnabled(true);
    setColumnWidth(0, 98);
    setColumnWidth(1, 50);
    setColumnWidth(2, 50);
    setFixedWidth(200);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    verticalHeader()->hide();
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setShowGrid(false);
    setAlternatingRowColors(true);
	setStyleSheet("* {alternate-background-color: #d6d1d0;background-color: white;}"
							  "QHeaderView::section { background-color: #bdcef0; border: 0px;}");
	refresh();
}


QStandardItemModel* MatrixViewWidget:: model () const
{
    return matrixModel;
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



MatrixViewWidget:: ~MatrixViewWidget ()
{

}
