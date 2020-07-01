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

#include "HelpWindow.h"

HelpWindow::HelpWindow(QWidget* parent) : QDialog(parent)
{
   title = new QLabel("MatriXMix Guide");

   QPixmap im(":img/icons/MatriXMiX.png");
   im = im.scaled(60, 60);

   logo = new QLabel;
   logo->setPixmap(im);

   QFont fontTitle ("Arial");
   fontTitle.setPointSize(20);

   title->setFont(fontTitle);

   QHBoxLayout* headerLayout = new QHBoxLayout;
   headerLayout->addWidget(logo);
   headerLayout->addWidget(title);
   headerLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

   QWidget* headerWidget = new QWidget;
   headerWidget->setLayout(headerLayout);
   headerWidget->setMinimumHeight(100);

   QFont font ("Arial Bold");
   font.setWeight(QFont::Bold);
   fontTitle.setPointSize(16);

   introduction = new QGroupBox(tr("Introduction"));
   introduction->setFont(font);
   introduction -> setStyleSheet(
               "QGroupBox { border: 1px solid silver;"
               "background-color:white;"
               "margin-top: 30px;"
               "border-radius:6px;}"
               "QGroupBox::title { subcontrol-origin:margin;"
               "subcontrol-position:top left;"
               "font-weight:75; color: #283676;}");

   utilisation = new QGroupBox(tr("Utilisation"));
   utilisation->setFont(font);
   utilisation -> setStyleSheet(
               "QGroupBox { border: 1px solid silver;"
               "background-color:white;"
               "margin-top: 30px;"
               "border-radius:6px;}"
               "QGroupBox::title { subcontrol-origin:margin;"
               "subcontrol-position:top left;"
               "font-weight:75; color: #283676;}");

   QLabel* defUtilisation = new QLabel("Pour effectuer un type d'opération "
                                       "presenté sur la page "
                                       "d'accueil, vous devez accéder à la librairie "
                                       "et ajouter vos\nmatrices. \n"
                                       "Par ailleurs, vous pouvez visualiser, "
                                       "supprimer ou modifier les "
                                       "matrices dans la librairie. \n"
                                       "Vos matrices seront ainsi disponibles sur"
                                        " le menu et vous pourrez exécuter vos opérations");
   QLabel * att = new QLabel("Attention!");
   att->setStyleSheet("font: bold; color: red;");
   QLabel * defAttention = new QLabel("Pour les opérations binaires, "
                                      "liées à la diagonalisation et les factorisation"
                                      " seules les matrices compatibles avec\n"
                                      "l'opération selectionnée sont affichées!");

   maths = new QGroupBox(tr("Calcul matriciel"));
   maths->setFont(font);
   maths -> setStyleSheet(
               "QGroupBox { border: 1px solid silver;"
               "background-color:white;"
               "margin-top: 30px;"
               "border-radius:6px;}"
               "QGroupBox::title { subcontrol-origin:margin;"
               "subcontrol-position:top left;"
               "font-weight:75; color: #283676;}");
   QLabel* defMaths = new QLabel("Théorie sur le calcul matriciel : ");
   QLabel* bases = new QLabel("<a href = \"https://fr.wikipedia.org/wiki/"
                                 "Matrice_(math%C3%A9matiques)\"> Introduction "
                                 " aux matrices </a>"
                                 " , <a href = \"https://fr.wikipedia.org/wiki/"
                                 "Calcul_du_d%C3%A9terminant_d%27une_matrice\">"
                                 "Déterminant</a>"
                                 " , <a href = \"https://fr.wikipedia.org/wiki/"
                                "Matrice_%C3%A9chelonn%C3%A9e\">Échelonnage</a>"
                                 " , <a href = \"https://fr.wikipedia.org/wiki/"
                                 "Matrice_diagonalisable\">Diagonalisation</a>");

  QLabel* decompositions = new QLabel("<a href = \"https://fr.wikipedia.org/wiki/"
                                 "D%C3%A9composition_LU\"> "
                                 "Décomposition LU</a>"
                                 " , <a href = \"https://fr.wikipedia.org/wiki/"
                                 "D%C3%A9composition_QR\"> "
                                 "Décomposition QR</a>"
                                 " , <a href = \"https://fr.wikipedia.org/wiki/"
                                 "Factorisation_de_Cholesky\"> "
                                 "Factorisation de Cholesky</a>");


   defMaths->setOpenExternalLinks(true);
   bases->setOpenExternalLinks(true);
   decompositions->setOpenExternalLinks(true);

   QLabel* def = new QLabel("MatriXMiX est une application sous licence GNU/GPL v3,"
                          " destinée aux mathématiciens, qui réalise des calculs"
                          "\nmatriciels. ");
   QLabel* def2 = new QLabel("MatriXMiX permet de faire des opérations unaires et binaires,"
                            "des opérations liées à la diagonalisation ainsi que des"
                            "\ndécompositions classiques (LU, QR, Cholesky)");
   def->setMaximumWidth(650);

   QVBoxLayout* subLayout = new QVBoxLayout;
   subLayout->addWidget(def);
   subLayout->addWidget(def2);
   introduction->setLayout(subLayout);

   QVBoxLayout* subLayout2 = new QVBoxLayout;
   subLayout2->addWidget(defUtilisation);
   subLayout2->addWidget(att);
   subLayout2->addWidget(defAttention);
   utilisation->setLayout(subLayout2);

   QVBoxLayout* subLayout3 = new QVBoxLayout;
   subLayout3->addWidget(defMaths);
   subLayout3->addWidget(bases);
   subLayout3->addWidget(decompositions);
   maths->setLayout(subLayout3);

   QLabel* matrix = new QLabel("@MatriXMiX 2019");
   matrix->setFont(font);
   matrix->setStyleSheet("font: bold; color: darkBlue;");
   QLabel* matrixAuteurs = new QLabel("Maxime Olivié \nAna-Maria Cerbulean"
                                     "\nTarik Boumaza \nHana Sebia");
   QVBoxLayout* matrixLayout = new QVBoxLayout;
   matrixLayout->addWidget(matrix);
   matrixLayout->addWidget(matrixAuteurs);
   matrixLayout->setAlignment(Qt::AlignHCenter);

   QVBoxLayout* mainLayout = new QVBoxLayout;
   mainLayout->addWidget(headerWidget);
   mainLayout->addWidget(introduction);
   mainLayout->addWidget(utilisation);
   mainLayout->addWidget(maths);
   mainLayout->addLayout(matrixLayout);
   mainLayout->setAlignment(Qt::AlignCenter);
   setLayout(mainLayout);
   show();
}

HelpWindow::~HelpWindow()
{
}
