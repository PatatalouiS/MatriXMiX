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

#include "ResultAdderWidget.h"
#include "Error.h"

#include <QHBoxLayout>
#include <QRegExpValidator>

Q_DECLARE_METATYPE(Matrix);

ResultAdderWidget::ResultAdderWidget(QMatrixLibrary* lib, QWidget* parent) :
                                        QWidget(parent), library(lib) {
    QHBoxLayout* resultAdder = new QHBoxLayout;
    adderName = new QLineEdit;
    QRegExpValidator* regex = new QRegExpValidator(QRegExp("[a-zA-Z0-9]+"),
                                                   adderName);
    adderName->setValidator(regex);
    adderName->setFixedHeight(30);
    adderName->setMaximumWidth(60);
    adderName->setPlaceholderText("Nom");
    adderName->setStyleSheet("QLineEdit {"
                                "border : 1px solid lightGrey;"
                             "}");
    adderBtn = new QPushButton("");
    adderBtn->setFixedHeight(30);
    adderBtn->setMaximumWidth(200);

    resultAdder->addWidget(adderName);
    resultAdder->addWidget(adderBtn);
    resultAdder->setContentsMargins(0,0,0,0);

    connect(adderBtn, &QPushButton::pressed,
            this, &ResultAdderWidget::addResult);

    setLayout(resultAdder);
}

void ResultAdderWidget::showAndLoadResult(const QVariant& res) {
    if(res.canConvert<Matrix>()) {
        show();
        result = res.value<Matrix>();

        adderBtn->setText("Ajouter le résultat");
        adderBtn->setStyleSheet("QPushButton{ "
                                "background-color:rgba(209,47,47, 90);"
                                "border-radius : 4px;"
                            "}"
                            "QPushButton:hover{ "
                                "background-color: lightBlue ;"
                            "}");
    }
}

void ResultAdderWidget::addResult() {
    QString name = adderName->text();

    if(!adderName->hasAcceptableInput()) {
        if((name[0] >= '0') || (name[0] <= '9'))
        Error::showError("Nom de Matrice " + name + " non valide !",
                   "Veuillez saisir 10 caractère Maximum, sans caractères spéciaux ni espaces ");
        return;
    }
    if(library->find(name))
    {
        Error::showError("La Matrice " + name + " existe déjà !",
                   "Veuillez changer de nom.");
        return;
    }

    library->addMatrix(name, result);

    emit newMatrixAdded();

    adderBtn->setText("Ajout effectué");

    adderBtn->setStyleSheet("QPushButton{ "
                                "background-color:rgba(0,200,0, 90);"
                                "border-radius : 4px;"
                            "}"
                            "QPushButton:hover{ "
                                "background-color: lightBlue ;"
                            "}");
    adderName->setText("");
}


