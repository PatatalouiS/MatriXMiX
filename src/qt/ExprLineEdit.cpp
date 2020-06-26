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

#include "ExprLineEdit.hpp"

mup::ParserX ExprLineEdit::parser = mup::ParserX();

ExprLineEdit::ExprLineEdit(QWidget* parent, const unsigned int width,
                           const unsigned int height) : QLineEdit(parent) {
    setMinimumWidth(width);
    setMaximumHeight(height);
    setMaxLength(MAX_LENGTH);
}

std::complex<double> ExprLineEdit::getComplex() const {
    parser.SetExpr(text().toStdString());
    return parser.Eval().GetComplex();
}

bool ExprLineEdit::isValidExpr() const {
    try {
        getComplex();
        return true;
    }
    catch(const mup::ParserError& err) {
        return false;
    }
}


