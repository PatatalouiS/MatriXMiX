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

#include "MenuBar.h"
#include <QApplication>

MenuBar:: MenuBar(QWidget* parent) : QMenuBar(parent)
{

    QFont font ("Arial");
    font.setPointSize(16);
    setFont(font);

    menuFile = addMenu("Fichier");
    menuFile->setCursor(Qt::PointingHandCursor);

    QPixmap im(":/img/save.png");
    im = im.scaled(50, 50);

    actionSave = new QAction("Sauver.." , this);
    actionSave->setIcon(im);
    menuFile -> addAction(actionSave);

    QPixmap im4(":/img/create.png");
    im4 = im4.scaled(50, 50);

    menuFile -> addSeparator();

    actionLoad = new QAction("Ouvrir..", this);
    actionLoad->setIcon(im4);
    menuFile -> addAction(actionLoad);

    menuMatrix = addMenu("Afficher");
    QPixmap im1(":/img/library.png");
    im1 = im1.scaled(50, 50);

    menuMatrix->setCursor(Qt::PointingHandCursor);

    QPixmap imMenu(":/img/menu.png");
    libraryMatrix = new QAction("Librairie" , this);
    libraryMatrix->setIcon(im1);
    menuMatrix -> addAction(libraryMatrix);
    matrixmixWindow = new QAction("Menu", this);
    matrixmixWindow->setIcon(imMenu);
    menuMatrix->addAction(matrixmixWindow);

    menuHelp = addMenu("Aide");
    menuHelp->setCursor(Qt::PointingHandCursor);

    QPixmap im5(":/img/icons/MatriXMiX.png");
    im5 = im5.scaled(200, 200);

    actionHelpMatrix = new QAction("About MatriXMix",this);
    actionHelpMatrix->setIcon(im5);
    menuHelp->addAction(actionHelpMatrix);

    menuHelp->addSeparator();

    QPixmap im2(":/img/qt.png");
    im2 = im2.scaled(250, 200);

    actionHelpQt = new QAction("About QT",this);
    actionHelpQt->setIcon(im2);
    menuHelp->addAction(actionHelpQt);

    menuQuit = addMenu("Quitter");
    menuQuit->setCursor(Qt::PointingHandCursor);

    QPixmap im3(":/img/quit.png");
    im3 = im3.scaled(200, 200);

    actionQuit = new QAction("MatriXMiX", this);
    actionQuit->setIcon(im3);
    menuQuit->addAction(actionQuit);

    connect(actionHelpMatrix, &QAction::triggered , this, &MenuBar::showPageMatrix);
    connect(actionHelpQt, &QAction::triggered , this, &MenuBar::showPageQt);
    connect(actionQuit, &QAction::triggered, this , &QApplication::quit);
    connect(libraryMatrix, &QAction::triggered, this, &MenuBar::openLibraryWindow);
    connect(matrixmixWindow, &QAction::triggered, this, &MenuBar::openMatrixmixWindow);
    connect(actionSave, &QAction::triggered, this, &MenuBar::openSaveTool);
    connect(actionLoad, &QAction::triggered, this, &MenuBar::openLoadTool);
}


void MenuBar::showPageMatrix()
{
    HelpWindow* wind = new HelpWindow(this);
    wind->setAttribute(Qt::WA_DeleteOnClose);
    wind->exec();
}

void MenuBar::showPageQt()
{
    HelpWindowQt* wind = new HelpWindowQt(this);
    wind->setAttribute(Qt::WA_DeleteOnClose);
    wind->exec();
}


MenuBar::~MenuBar()
{
}



