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

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "LibraryWindow.h"
#include "MatriXMiXWindow.h"
#include "MenuBar.h"

class MainWindow : public QMainWindow
{
    public:

        MainWindow();
        MenuBar* menuBar;
        QMatrixLibrary library;

        LibraryWindow* libraryWindow;
        MatriXMiXWindow* matrixmixWindow;

        /**
        * @brief Show the load and save tool
        * @param [in] type (\e enum \e QFileDialog::AcceptMode)
        */
        void showFileTool (enum QFileDialog::AcceptMode type);

        /**
        * @brief Differentiate which tool is selected: save or load
        * @param [in] fileTool ( \e QFileDialog)
        * @param [in] type (\e enum \e QFileDialog::AcceptMode)
        */
        void computeLoadOrRead(QFileDialog* fileTool, enum QFileDialog::AcceptMode type);

    signals :

        /**
        * @brief libraryChanged this signal is emitted when a modification on the library happen
        */
        void libraryChanged();
};

#endif // MAINWINDOW_HPP
