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

#include "AbstractOperationWidget.h"

#include <QVBoxLayout>


AbstractOperationWidget:: AbstractOperationWidget(const QMatrixLibrary* lib, QWidget* parent): QWidget (parent)
{
    this->lib = lib;
    sortFunction = [](const Matrix*){return true;};

    QFont font ("Arial");
    font.setPointSize(20);

    description = new QLabel(this);
    description->setStyleSheet("font-size: 40px");
    description->setAlignment(Qt::AlignCenter);

    title = new QLabel(this);
    title->setStyleSheet("font-size: 20px; font:bold;");
    title->setAlignment(Qt::AlignCenter);
    title->setFixedHeight(40);
    title->setFont(font);
    title->setStyleSheet("QLabel{"
                             "background-color : lightGrey;"
                             "border-top-left-radius : 5px;"
                             "border-top-right-radius : 5px;"
                             "border : 1px solid grey;"
                         "}");



    calculer = new QPushButton("Calculer", this);
    calculer->setCursor(Qt::PointingHandCursor);
    calculer->setStyleSheet("QPushButton{ "
                                "background-color: lightGrey ;"
                                "border-radius : 4px;"
                            "}"
                            "QPushButton:hover{ "
                                "background-color: lightBlue ;"
                            "}");
    calculer->setFixedSize(200,30);

    mainWidget = new QWidget(this);
    mainWidget->setStyleSheet(".QWidget{"
                                  "border-left : 1px solid grey;"
                                  "border-right : 1px solid grey;"
                                  "border-bottom : 1px solid grey;"
                                  "background-color : white;"
                                  "border-bottom-left-radius : 5px;"
                                  "border-bottom-right-radius : 5px;"
                              "}");



    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(title);
    mainLayout->addWidget(mainWidget);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    resultAdder = new ResultAdderWidget(const_cast<QMatrixLibrary*>(lib), this);
    resultAdder->hide();

    connect(calculer, &QPushButton::clicked,
            this, &AbstractOperationWidget::computeOperation);

    connect(this, &AbstractOperationWidget::newResult,
            resultAdder, &ResultAdderWidget::showAndLoadResult );

    connect(resultAdder, &ResultAdderWidget::newMatrixAdded,
            this, &AbstractOperationWidget::libraryChanged);

    setLayout(mainLayout);
}



void AbstractOperationWidget:: setTitle (const QString& str)
{
    title->setText(str);
}


void AbstractOperationWidget:: setSortFunction(SortFunction&& s)
{
    this->sortFunction = s;
}


const QMatrixLibrary* AbstractOperationWidget:: getLib() const
{
    return lib;
}

