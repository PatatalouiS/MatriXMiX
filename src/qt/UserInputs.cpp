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

#include "UserInputs.hpp"


using namespace std;


UserInputs::UserInputs(const unsigned int r, const unsigned int c)
    : rows(r), cols(c), inputs()
{}


unsigned int UserInputs::getRows() const {
    return rows;
}


unsigned int UserInputs::getCols() const {
    return cols;
}


QVector<QString>::const_iterator UserInputs::begin() const {
   return inputs.begin();
}


QVector<QString>::const_iterator UserInputs::end() const {
   return inputs.end();
}


const QString& UserInputs::put(const QString& input) {
    inputs.push_back(input);
    return inputs.back();
}

const QString& UserInputs::operator[](const unsigned int ind) const {
    return inputs.at(ind);
}
