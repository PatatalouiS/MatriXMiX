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

#ifndef EXPRLINEEDIT_HPP
#define EXPRLINEEDIT_HPP

#include <QLineEdit>
#include <complex>
#include <mpParser.h>

/**
 * @class The ExprLineEdit class This clas is an implementation of a Matrix text entry
 *      a math parser is included to parse simple math exprsessions to a Complex.
 */

class ExprLineEdit : public QLineEdit {

    Q_OBJECT

    private :

        static constexpr unsigned int DEFAULT_WIDTH = 30;
        static constexpr unsigned int DEFAULT_HEIGHT = 70;
        static constexpr unsigned int MAX_LENGTH = 50;

        static mup::ParserX parser;

    public:

        /**
         * @brief ExprLineEdit the default constructor
         * @param parent the parent of this widget
         * @param width the width of the text entry
         * @param height the height of the text entry
         */
        ExprLineEdit(QWidget* parent = nullptr, const unsigned int width = DEFAULT_WIDTH,
                 const unsigned int height = DEFAULT_HEIGHT);

        /**
         * @brief getComplex return the complex put by the user in text entry (use a math parser)
         * @return the parsed complex<double>
         */
        std::complex<double> getComplex() const;

        /**
         * @brief isValidExpr test if the current user entry is a valid mathematical expression
         * @return true if valid, else false.
         */
        bool isValidExpr() const;
};

#endif // EXPRLINEEDIT_HPP
