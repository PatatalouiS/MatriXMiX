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

#ifndef DIAGONALISATIONWIDGET_H
#define DIAGONALISATIONWIDGET_H

#include "AbstractOperationWidget.h"
#include "MatrixViewWidget.h"
#include <array>
#include <QRadioButton>


/**
@class DiagonalisationWidget  none none   the goal of this class is to compute the diagonalisation of a Matrix in R set. \n
        User can compute the P, D, and P_INVERSE Matrices with this class.
*/


class DiagonalisationWidget : public AbstractOperationWidget
{
    Q_OBJECT

    public:

        enum type {
            DIAGONALISATION_R,
            DIAGONALISATION_C
        };
        /** @brief Unique constructor of the class.
         * @param [in] library a pointer on a QMatrixLibrary .
         * @param [in,out] parent a pointer on a potential parent QWidget, mainly for ensure good deletion.
         */

        DiagonalisationWidget (const type t, const QMatrixLibrary* lib, QWidget* parent = nullptr);

    public slots:


        /**
         * @brief implementation of AbstractOperationWidget::updateViews()
         */

        virtual void updateViews() override final;

    private:

        enum ResultChoice
        {
            P = 0,
            D = 1,
            P_INVERSE = 2
        };

        MatrixViewWidget* view;
        MatrixPair op;
        std::array<Matrix, 3> result;
        QWidget* choiceWidget;

        void constructType(const type t);


    private slots:

        /**
         * @brief implementation of AbstractOperationWidget::computeSelection(const bool view)
         */

        virtual void computeSelection(const bool view = 0) override final;

        /**
         * @brief implementation of AbstractOperationWidget::computeOperation()
         */

        virtual void computeOperation() override final;

        /** @brief emit the good Matrix Result (using AbstractOperationWidget::newResult(const QVariant result) \n
         *          in fonction of the user selection ( P Matrix, P_INVERSE Matrix or D Matrix).
         * @param [in] resultChoice the type of the selected Result (enum).
         */

        void emitResultChoice(const ResultChoice& resultChoice);
};



#endif
