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

#ifndef BINARYOPMATRIXNUMBERWIDGET_H
#define BINARYOPMATRIXNUMBERWIDGET_H

#include <QLineEdit>
#include "AbstractOperationWidget.h"
#include "MatrixViewWidget.h"



/**
@class BinaryOpMatrixNumberWidget  none none   the goal of this class is to compute a binary operation between a Matrix and a number. \n
        The type and the operation is definitive and defined at the construction, with the enum BinaryOpMatrixNumberWidget::type
*/



class BinaryOpMatrixNumberWidget : public AbstractOperationWidget
{
    Q_OBJECT  

    public:

        enum type
        {
            SCALAR_MULTIPLICATION,
            POWER
        };

        /** @brief Unique constructor of the class.
         * @param [in] type type of the Binary Matrix/Number Operation. The enum is BinaryOpMatrixNumberWidget::type .
         * @param [in] library a pointer on a QMatrixLibrary .
         * @param [in,out] parent a pointer on a potential parent QWidget, mainly for ensure good deletion.
         */

        BinaryOpMatrixNumberWidget(const type& t, const QMatrixLibrary* lib, QWidget* parent = nullptr);

    public slots:

        /**
         * @brief implementation of AbstractOperationWidget::updateViews()
         */

        virtual void updateViews() override final;

    private slots:

        /**
         * @brief implementation of AbstractOperationWidget::computeSelection(const bool view)
         */

        virtual void computeSelection(const bool view = 0) override final;

        /**
         * @brief implementation of AbstractOperationWidget::computeOperation()
         */

        virtual void computeOperation() override final;

    private:

       using BinaryOpMatrixNumber = std::function<Matrix(const Matrix*, const double)>;

       MatrixViewWidget* view;
       QLineEdit* edit;
       MatrixPair op1;
       double op2;
       QString logo;
       BinaryOpMatrixNumber operation;
       Matrix result;

       /**
        * @brief constructType this fonction is called one time, when the object is constructed.\n
        *       It construct the operation attributes and caracteristics in fonction of the enum BinaryOpMatrixNumberWidget::type given.
        * @param [in] the type of the binary operation.
        */

       void constructType(const type& t);
};

#endif
