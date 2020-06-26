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

#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QEvent>
#include <QToolTip>
#include "LibraryWindow.h"
#include "HelpWindow.h"
#include "HelpWindowQt.h"

/**
@class MenuBar The class MenuBar generate the menu of the application
MatriXMiX which give the access to the library, help pages, to safeguard
and loading a file.
*/
class MenuBar : public QMenuBar
{
    Q_OBJECT

    private:
        QMatrixLibrary lib;
        QMenu *menuFile;
        QAction *actionSave;
        QAction *actionLoad;
        QMenu *menuMatrix;
        QAction *libraryMatrix;
        QAction *matrixmixWindow;
        QMenu *menuHelp;
        QAction* actionHelpMatrix;
        QAction* actionHelpQt;
        QMenu *menuQuit;
        QAction *actionQuit;

    public:
        /**
         * @brief Default constructor
         * @param [in] parent (\e pointer of QWidget)
         */
        MenuBar(QWidget* parent = nullptr);
        /**
         * @brief Default destructor
         */
        ~MenuBar ();

    signals:
        /**
         * @brief Open the library window
         */
        void openLibraryWindow();

        void openMatrixmixWindow();
        /**
         * @brief Open the save tool
         */
        void openSaveTool();
        /**
         * @brief Open the save tool
         */
        void openLoadTool();

    private slots:

        /**
         * @brief Open the help page of MatriXMiX
         */
        void showPageMatrix();
        /**
         * @brief Open the help page of Qt
         */
        void showPageQt();
};

#endif
