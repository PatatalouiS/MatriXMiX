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

#ifndef UNARYOPWIDGET_H
#define UNARYOPWIDGET_H


#include "AbstractOperationWidget.h"
#include "MatrixViewWidget.h"


/**
@class UnaryOpWidget  none none   the goal of this class is to compute a Unary operation. \n
        The type and the operation is definitive and defined at the construction, with the enum UnaryOpWidget::type
*/


class UnaryOpWidget : public AbstractOperationWidget
{
    Q_OBJECT

    public:

        enum type
        {
            DETERMINANT,
            TRACE,
            INVERSE,
            ROW_REDUCED_FORM,
            EIGEN_PROPERTIES,
            CARACTERISTIC_POLYNOMIAL,
            KER_IMG_DIM,
            TRANSPOSE
        };

        /** @brief Unique constructor of the class.
         * @param [in] type type of the Unary Operation. The enum is BinaryOpWidget::type .
         * @param [in] library a pointer on a QMatrixLibrary .
         * @param [in,out] parent a pointer on a potential parent QWidget, mainly for ensure good deletion.
         */

        UnaryOpWidget(const type& t, const QMatrixLibrary* lib, QWidget* parent = nullptr);

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

        using UnaryOpMatrix = std::function<const QVariant(const QPair<const QString, const Matrix*>)>;

        MatrixViewWidget* view;
        MatrixPair op;
        UnaryOpMatrix operation;
        QVariant result;

        /**
         * @brief constructType this fonction is called one time, when the object is constructed.\n
         *       It construct the operation attributes and caracteristics in fonction of the enum UnaryOpWidget::type given.
         * @param [in] the type of the unary operation.
         */

        void constructType(const type& type);
};



#endif
