

#include "MatrixViewWidget.h"
#include <QHeaderView>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QDebug>
#include <QDesktopWidget>
#include <QTimer>


MatrixViewWidget::MatrixViewWidget (const MatrixLibrary* lib, QWidget* parent) : QTableView (parent)
{
    this->lib = lib;
    matrixModel = new QStandardItemModel(0,3, this);
    currentRowHovered = -1;

    matrixModel->setHorizontalHeaderLabels({"Nom", "NbL", "NbC"});
    imgToolTip = new ShowMatrixWidget(this);

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

    viewport()->installEventFilter(this);
    setMouseTracking(true);
    popup = new QDialog(this, Qt::Popup | Qt::ToolTip );
    QVBoxLayout* layout = new QVBoxLayout;
    popupLabel = new QLabel(popup);
    popupLabel->setWordWrap(true);
    layout->addWidget(popupLabel);
    popup->setLayout(layout);
    popup->installEventFilter(this);

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

    for(auto i : lib->data())
    {
        matrix = &(i.second);

        if(filter(matrix))
        {
            addNewRow(MatrixPair(QString::fromStdString(i.first), i.second));
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


void MatrixViewWidget:: removeRow (const int id)
{
    matrixModel->removeRow(id);
    sortByColumn(0, Qt::AscendingOrder);
}


bool MatrixViewWidget:: eventFilter(QObject *watched, QEvent *event)
{
//    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
//    QModelIndex index = indexAt(mouseEvent->pos());

//    if(index.isValid())
//    {
//        if(event->type() == QEvent::MouseMove)
//        {
//            popup->show();
//            if(index.row() != currentRowHovered)
//            {
//                QString hoveredMatrixName = matrixModel->item(index.row())->text();
//                const Matrix* hoveredMatrix = lib->find(hoveredMatrixName.toStdString());
//                imgToolTip->computeImgMatrix(*hoveredMatrix, 15);
//                popupLabel->setPixmap(imgToolTip->getCurrentPixmap());
//                popup->adjustSize();
//                currentRowHovered = index.row();
//            }
//            int posX = cursor().pos().x();
//            int posY = cursor().pos().y();
//            popup->move(posX+10, posY);
//        }
//    }
//    else if(event->type() == QEvent::Leave)
//    {
//        popup->hide();
//    }

    return QTableView::eventFilter(watched, event);
}


MatrixViewWidget:: ~MatrixViewWidget ()
{
}
