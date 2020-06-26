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

#include "ExprEvalWidget.h"
#include "Error.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <iostream>

ExprEvalWidget::ExprEvalWidget(const QMatrixLibrary* lib, QWidget* parent) :
AbstractOperationWidget (lib, parent)
{
    QString style = "QLabel {"
                        "background-color: rgb(243,243,243);"
                        "border-top-left-radius : 4px;"
                        "border-top-right-radius : 4px;"
                        "border : 1px solid lightGrey;"
                    "}";

    result = Matrix();

    setTitle("Evaluation d'expression");

    QVBoxLayout* matrixView = new QVBoxLayout;
    QLabel* op1Title = new QLabel("Matrices disponibles : ");
    op1Title -> setAlignment(Qt::AlignCenter);
    op1Title->setStyleSheet(style);
    view = new MatrixViewWidget(lib, this);
    view->setMaximumWidth(300);
    matrixView->addWidget(op1Title);
    matrixView->addWidget(view);
    matrixView->setSpacing(0);
    matrixView->setAlignment(Qt::AlignCenter);

    QLabel* info = new QLabel("Pour calculer l'inverse d'une matrice utiliser: A~");
    info->setStyleSheet("color:grey;");
    info->setAlignment(Qt::AlignCenter);

    expression = new QLineEdit();
    expression->setMinimumHeight(30);
    expression->setPlaceholderText("Ex: A+B*C/D");
    expression->setStyleSheet("QLineEdit {"
                                "border : 1px solid grey;"
                                "border-radius : 4px;"
                              "}");

    QVBoxLayout* exprLayout = new QVBoxLayout;
    exprLayout->setContentsMargins(20,20,20,20);

    QGroupBox* exprBox = new QGroupBox("Saisie de l'expression :");
    exprLayout->addWidget(expression);
    exprLayout->addWidget(info);
    exprLayout->setSpacing(10);

    exprBox->setLayout(exprLayout);
    exprBox->setMaximumSize(QSize(350, 250));
    exprBox->setStyleSheet("QGroupBox { "
                               "border: 1px solid silver;"
                               "background-color:rgb(243,243,243);"
                               "border-radius: 5px;"
                               "margin-top: 15px; }"
                               "QGroupBox::title { subcontrol-origin:margin;"
                               "margin-top : 5px;"
                               "background-color:rgb(235,235,235) ;"
                               "border : 1px solid grey;"
                               "border-radius : 5px;"
                               "subcontrol-position: top;"
                               "font: bold ; color: black;"
                            "}");

    QVBoxLayout* btnLayout = new QVBoxLayout;
    btnLayout->addWidget(calculer);
    btnLayout->setContentsMargins(0,30,0,30);
    btnLayout->setAlignment(Qt::AlignCenter);

    QVBoxLayout* rightLayout = new QVBoxLayout;
    rightLayout->addWidget(exprBox);
    rightLayout->addLayout(btnLayout);
    rightLayout->addWidget(resultAdder);
    rightLayout->setAlignment(Qt::AlignCenter);

    QHBoxLayout* subLayout = new QHBoxLayout;
    subLayout->addStretch(3);
    subLayout->addLayout(matrixView);
    subLayout->addStretch(2);
    subLayout->addLayout(rightLayout);
    subLayout->addStretch(3);
    subLayout->setAlignment(Qt::AlignCenter);
    subLayout->setContentsMargins(20,20,20,20);
    subLayout->setSpacing(0);

    mainWidget->setLayout(subLayout);

    connect(expression, &QLineEdit::textEdited,
            resultAdder, &ResultAdderWidget::hide);

    view->refresh(sortFunction);
}


void ExprEvalWidget:: updateViews()
{
    view->refresh();
}

void ExprEvalWidget:: computeOperation ()
{
    std::string testExpression = getLib()->isCalculableExpression(expression->text().toStdString());

    if(testExpression != "calculable")
    {
        Error::showError("Calcul d'expression impossible", QString::fromStdString(testExpression), this);
        return;
    }

    result = getLib()->calculateExpression(expression->text().toStdString());

    if(result == Matrix::matrix_null)
    {
        Error::showError("Calcul impossible", "Veuillez vérifier que le calcul demandé est réalisable", this);
        return ;
    }

    QVariant genericResult;
    genericResult.setValue(result);

    emit newResult(genericResult);
}


void ExprEvalWidget:: computeSelection(const bool view)
{
    (void)view;
}



