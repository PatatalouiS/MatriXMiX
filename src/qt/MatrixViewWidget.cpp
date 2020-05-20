

#include "MatrixViewWidget.h"
#include <QHeaderView>


ShowMatrixWidget* MatrixViewWidget::matrixPreview = nullptr;


MatrixViewWidget::MatrixViewWidget (const MatrixLibrary* lib, QWidget* parent) : QTableView (parent)
{
    this->lib = lib;
    matrixModel = new QStandardItemModel(0,3, this);
    matrixModel->setHorizontalHeaderLabels({"Nom", "NbL", "NbC"});

    setModel(matrixModel);
    setSortingEnabled(true);
    setColumnWidth(0, 100);
    setFixedWidth(200);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setShowGrid(false);
    setAlternatingRowColors(true);
    setStyleSheet("* {alternate-background-color: lightBlue;background-color: white;"
                  "border: 1px solid silver; border-radius:3px;}"
                  "QHeaderView::section { background:"
                  "qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 "
                  "lightBlue, stop: 1 blue); color:white; border: 0px; "
                  "}");
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->hide();
	refresh();
    setCurrentIndex(QModelIndex());

    connect(this, &MatrixViewWidget::doubleClicked,
            this, &MatrixViewWidget::showMatrixPreview);
}



void MatrixViewWidget:: showMatrixPreview () const
{
    QString currentSelectedName = nameOfSelectedMatrix();

    if(nameOfSelectedMatrix() == "")
    {
        return;
    }

    if(matrixPreview != nullptr)
    {
        delete matrixPreview;
    }

    assert(lib->exist(currentSelectedName.toStdString()));
    const Matrix* currentMatrix = lib->find_matrix(currentSelectedName.toStdString());
    matrixPreview = new ShowMatrixWidget(nullptr);
    matrixPreview->setWindowFlag(Qt::Tool);
    connect(matrixPreview, &ShowMatrixWidget::destroyed,
            [this]()
            {
                this->matrixPreview = nullptr;
            });
    matrixPreview->setAttribute(Qt::WA_DeleteOnClose);
    matrixPreview->setWindowFlag(Qt::WindowStaysOnBottomHint);
    matrixPreview->computeImgMatrix(*currentMatrix, 15);
    matrixPreview->move(matrixPreview->parentWidget()->mapFromGlobal(QCursor::pos()));
    matrixPreview->show();
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

    for(auto i : lib->data())
    {
        matrix = &i.second.first;

        if(filter(matrix))
        {
            addNewRow(MatrixPair(QString::fromStdString(i.first), i.second.first));
        }
    }
    update();
    sortByColumn(0, Qt::AscendingOrder);
}



void MatrixViewWidget:: addNewRow (const MatrixPair& m)
{
    QString name = m.first;
    Matrix matrix = m.second;
    QList<QStandardItem*> line;
    line.append(new QStandardItem(name));
    line.append(new QStandardItem(QString::number(matrix.getNbRows())));
    line.append(new QStandardItem(QString::number(matrix.getNbCols())));
    matrixModel->appendRow(line);
    update();
    sortByColumn(0, Qt::AscendingOrder);
    showRow(matrixModel->indexFromItem(line[0]).row());
    selectRow(matrixModel->indexFromItem(line[0]).row());
}


void MatrixViewWidget:: editRow (const MatrixPair& m)
{
    QModelIndex index = currentIndex();
    matrixModel->removeRow(index.row());
    addNewRow(m);
}


void MatrixViewWidget:: removeRow (const int idRow)
{
    matrixModel->removeRow(idRow);
    sortByColumn(0, Qt::AscendingOrder);
    setCurrentIndex(QModelIndex());
}


MatrixViewWidget:: ~MatrixViewWidget ()
{
}
