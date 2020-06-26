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

#ifndef DECOMPOSITIONWIDGET_H
#define DECOMPOSITIONWIDGET_H

#include "AbstractOperationWidget.h"
#include "MatrixViewWidget.h"

#include <QRadioButton>

using UnaryOpMatrix = std::function<std::pair<Matrix, Matrix>(const Matrix*)>;

class DecompositionWidget : public AbstractOperationWidget
{
    Q_OBJECT

    public:

        enum type {
            QR,
            LU,
            CHOLESKY
        };

        DecompositionWidget(const type type, const QMatrixLibrary* lib,
                            QWidget* parent = nullptr);

    public slots :

        /**
         * @brief implementation of AbstractOperationWidget::updateViews()
         */
        virtual void updateViews() override final;

    private:

        MatrixViewWidget* view;
        MatrixPair op;
        std::pair<Matrix, Matrix> result;
        QWidget* choiceWidget;
        QRadioButton* result1;
        QRadioButton* result2;
        UnaryOpMatrix operation;

        /**
         * @brief constructType this fonction is called one time, when the object is constructed.\n
         *       It construct the operation attributes and caracteristics in fonction of the enum DecompositionWidget::type given.
         * @param [in] the type of the binary operation.
         */
        void constructType(const type t);

    private slots :

        /**
         * @brief implementation of AbstractOperationWidget::computeSelection(const bool view)
         */
        virtual void computeSelection(const bool view = 0) override final;

        /**
         * @brief implementation of AbstractOperationWidget::computeOperation()
         */
        virtual void computeOperation() override final;


        void emitResultChoice(const unsigned int choice);
};

#endif // DECOMPOSITIONWIDGET_H
