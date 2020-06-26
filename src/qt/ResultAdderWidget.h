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

#ifndef RESULTADDERWIDGET_H
#define RESULTADDERWIDGET_H

#include "../maths/Matrix.h"
#include "QMatrixLibrary.hpp"

#include <QWidget>
#include <QVariant>
#include <QLineEdit>
#include <QPushButton>

/**
 * @brief The ResultAdderWidget class This class wrap a little widget wich allows the
 *  User to Add the result of a computation to a QMatrixLibrary instance.
 */

class ResultAdderWidget : public QWidget
{
    Q_OBJECT

    public:

        /**
         * @brief ResultAdderWidget the constructor
         * @param lib teh QMAtrixLibrary to use for add the result
         * @param parent the parent QWidget
         */
        ResultAdderWidget(QMatrixLibrary* lib,
                          QWidget* parent = nullptr);

        /**
         * @brief addResult add the current result to the MatrixLibrary
         */
        void addResult();

    public slots:

        /**
         * @brief showAndLoadResult load a new computation to the scope of this Widget
         *  end show this QWidget to user.
         * @param result the emitted result ( by an AbstractOperationWidget )
         */
        void showAndLoadResult(const QVariant& result);

    private :

        Matrix result;
        QMatrixLibrary* library;
        QLineEdit* adderName;
        QPushButton* adderBtn;

    signals:

        /**
         * @brief newMatrixAdded this signal is emitted when a new Matrix is added
         *  in the QMatrixLibrary
         */
        void newMatrixAdded();
};

#endif // RESULTADDERWIDGET_H
