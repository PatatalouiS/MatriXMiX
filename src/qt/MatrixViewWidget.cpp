
/*
 __  __       _        ___  ____  __ ___  __
|  \/  | __ _| |_ _ __(_) \/ /  \/  (_) \/ /
| |\/| |/ _` | __| '__| |\  /| |\/| | |\  /
| |  | | (_| | |_| |  | |/  \| |  | | |/  \
|_|  |_|\__,_|\__|_|  |_/_/\_\_|  |_|_/_/\_\

Copyright (C) 2019-2020, Sebia Hana, Cerbulean Ana-Maria, Boumaza Tarik, Olivié Maxime.

This file is part of MatriXMiX.

MatriXMiX is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MatriXMiX is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with MatriXMiX.  If not, see <https://www.gnu.org/licenses/>

*/

#include "MatrixViewWidget.h"
#include <QHeaderView>

ShowMatrixWidget* MatrixViewWidget::matrixPreview = nullptr;


MatrixViewWidget::MatrixViewWidget (const QMatrixLibrary* lib, QWidget* parent) : QTableView (parent)
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

    assert(lib->exist(currentSelectedName));
    const Matrix* currentMatrix = lib->find(currentSelectedName);
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

    for(const auto& [ name, userMtx ] : *lib)
    {
        matrix = const_cast<Matrix*>(&userMtx.matrix);

        if(filter(matrix))
        {
            addNewRow(MatrixPair(name, userMtx.matrix));
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
