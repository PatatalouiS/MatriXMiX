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

#ifndef MATRIXVIEWWIDGET_H
#define MATRIXVIEWWIDGET_H

#include <QTableView>
#include <QStandardItemModel>
#include "QMatrixLibrary.hpp"
#include "ShowMatrixWidget.h"


/**
 * @brief The MatrixViewWidget class is the widget for represent all the matrices in a MatrixLibrary.
 */


class MatrixViewWidget : public QTableView
{
    Q_OBJECT

    using MatrixPair = QPair<const QString&, const Matrix&>;

    public:

         /**
         * @brief MatrixViewWidget
         * @param [in] lib a pointer to a MatrixLibrray
         * @param [in,out] parent a pointer to a parent QWidget, to ensure good deletion
         */

        MatrixViewWidget(const QMatrixLibrary* lib, QWidget* parent = nullptr);

        /**
         * @brief the default Constructor
         */

        ~MatrixViewWidget ();

        /**
         * @brief nameOfSelectedMatrix return the current selection of the tab of matrices
         * @return the name of the selected Matrix in QString form
         */

        const QString nameOfSelectedMatrix() const;

    public slots:

        /**
        * @brief refresh refresh the view of matrices if a matrix is added, suspressed, or edited
        * @param [in] filter a comparison lambda function
        */

        void refresh(std::function<bool(Matrix*)> filter =
            [](const Matrix*) -> bool {return true;});

        /**
         * @brief addNewRow add a new matrix to the view
         * @param [in] m the Matrix to add
         */

        void addNewRow(const MatrixPair& m);

         /**
         * @brief editRow edit a matrix in the view
         * @param [in] m the edited Matrix
         */

        void editRow(const MatrixPair& m);

        /**
         * @brief removeRow remove a matrix in the view
         * @param [in] id the index of the matrix to remove
         */

        void removeRow(const int id);

    private:

        const QMatrixLibrary* lib;
        QStandardItemModel* matrixModel;
        static ShowMatrixWidget* matrixPreview;

    private slots:

        /**
         * @brief showMatrixPreview show a preview of the selected Matrix to the user screen
         */

        void showMatrixPreview() const;
};


#endif
