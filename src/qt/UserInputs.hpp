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

#ifndef USERINPUTS_HPP
#define USERINPUTS_HPP

#include <QVector>
#include <QString>

/**
 * @brief The UserInputs class It's a Matrix Represantation of a user Input.
 */
class UserInputs {

    public :

        /**
         * @brief UserInputs the constructor
         * @param nRows the number of rows
         * @param nCols the number of cols
         */
        UserInputs(const unsigned int nRows = 0, const unsigned int nCols = 0 );

        /**
         * @brief getRows getter for the number of rows of the UserInputs
         * @return the number of rows
         */
        unsigned int getRows() const;

        /**
         * @brief getCols getter for the number of cols of the UserInputs
         * @return the number of cols
         */
        unsigned int getCols() const;

        /**
         * @brief begin allow range-based for by returning an iterator to the first user entry.
         * @return a const iterator
         */
        QVector<QString>::const_iterator begin() const;

        /**
         * @brief begin allow range-based for by returning an iterator to the first user entry.
         * @return a const iterator
         */
        QVector<QString>::const_iterator end() const;

        /**
         * @brief put add a new user input to the UserInputs instance
         * @param input the new input to add
         * @return a reference to the added input
         */
        const QString& put(const QString& input);

        /**
         * @brief operator [] operator[] implementation
         * @param ind the index to acess
         * @return the user input at given index
         */
        const QString& operator[] (const unsigned int ind) const;


    private :

        unsigned int rows;

        unsigned int cols;

        QVector<QString> inputs;
};




#endif // USERINPUTS_HPP
