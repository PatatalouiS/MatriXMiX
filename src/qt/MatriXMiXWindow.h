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

#include <QFileDialog>

#include "MenuBar.h"
#include "LibraryWindow.h"
#include "AbstractOperationWidget.h"

/**
@class MatriXMiXWindow The class MatriXMiXWindow generate the main page of the application
MatriXMiX. This window contains all the operation buttons grouped in QGroupBox,
the view of consulting operation and the view of result.
*/

class MatriXMiXWindow : public QWidget
{
    Q_OBJECT
    
    public:
        /**
        * @brief Default constructor
        */
        MatriXMiXWindow (QWidget* parent, const QMatrixLibrary* lib);

    public slots:

          void updateCurrentOperationWidget();
       
    private slots:
          /**
          * @brief Verify if the result of the operation have a good format
          * @param [in] res (\e QVariant)
          */
          void transferResult (const QVariant& res);
          /**
          * @brief Show the selected operation in a widget
          * @param [in] choice ( \e unsigned \e int)
          */
          void computeChoice (const unsigned int choice);


    private:

        // members
        const QMatrixLibrary* library;
        AbstractOperationWidget* currentOpWidget;
        QVBoxLayout* currentOpLayout;
        unsigned int currentChoice;
        ShowMatrixWidget* imgResult;
        std::function<AbstractOperationWidget*(void)> createWindow [21];

        // functions
        /**
        * @brief Fill the table of createWindow with the good function
        */
        void setFunctorTab ();

    signals :

        /**
         * @brief this signal is emitted when the user wants to access the library window.
         */
        void showLibraryWindow();
};
