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

#ifndef OPCHOICEWIDGET_H
#define OPCHOICEWIDGET_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QStackedLayout>

class OpChoiceWidget : public QWidget
{
    Q_OBJECT

    public:

        OpChoiceWidget(QWidget* parent);

        enum class OpType {
            BINARY_OP = 0,
            UNARY_OP = 1,
            DIAGONALISATION = 2,
            DECOMPOSITION = 3,
            EXPR_EVAL = 4
        };

    private:

        QGroupBox* opList;
        QVBoxLayout* opListLayout;

    private slots :

        /**
         * @brief setOperationsList computes the new available opeation list choosed in function
         *  of the user choice. (type)
         * @param type the new type of operations choosed by user
         */
        void setOperationsList(const OpType& type);

    signals:

        /**
         * @brief opSelected this signal is emitted when a new operation is selected by user
         * @param index the new index of the new operation choosen
         */
        void opSelected(unsigned int index);
};

#endif // OPCHOICEWIDGET_H
