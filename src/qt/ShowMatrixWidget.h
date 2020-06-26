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

#ifndef SHOWMATRIXWIDGET_H
#define SHOWMATRIXWIDGET_H



#include <QLabel>
#include "../maths/Matrix.h"



/**
@class ShowMatrixWidget none none   This class is made for draw the results of Matrix Operations.
*/


class ShowMatrixWidget : public QWidget
{
    Q_OBJECT

    private:

        QLabel* imgSelected;

        /**
         * @brief setPixmapToQLabel Compute the img with the given latex code
         * @param [in] col The colour of the text
         * @param [in] latex The latex string to compute
         * @param [in] sizeTxt The size of the text
         */

        void setPixmapToQLabel(const QColor& col, const QString& latex, const unsigned int sizeTxt);

    public:

        /**
         * @brief ShowMatrixWidget The constructor of the class
         * @param [in,out] parent a pointer on a potential parent QWidget, mainly for ensure good deletion.
         */

        explicit ShowMatrixWidget(QWidget *parent = nullptr);

        /**
         * @brief getCurrentPixmap return the QPixmap in the member QLabel imgSelected.
         * @return const QPixmap& a constant reference to a QPixmap
         */

        const QPixmap& getCurrentPixmap() const;

        /**
         * @brief computeImgMatrix Compute a Matrix Image
         * @param [in] mat the Matrix to compute
         * @param [in] sizeTxt The size of the text
         * @param [in] col The colour of the text
         */

        QString computeImgMatrix(const Matrix& mat, const unsigned int sizeTxt = 20, const QColor& col = QColor(0,0,0,0));

        /**
         * @brief computeImgDimMatrix Compute an image wich represents the Kernel Dimension and Image dimension of a Matrix
         * @param [in] res the dimensions to print
         * @param [in] name the name of the Matrix
         * @param [in] col The colour of the text
         */

        QString computeImgDimMatrix(const std::pair<unsigned int, unsigned int>& res,
                               const QString& name, const QColor& col = QColor(0,0,0,0));

        /**
         * @brief computeImgPolynomial Compute an Image wich represents the caracteristic polynomial of a Matrix
         * @param [in] res1 the polynomial in developped form
         * @param [in] res2 the polynomial in factorized form
         * @param [in] name the name of the Matrix
         * @param [in] col the colour of the text
         */

        QString computeImgPolynomial(const Polynomial& res1, const std::vector<Polynomial>& res2,
                                  const QString& name, const QColor& col = QColor(0,0,0,0));

        /**
         * @brief computeImgEigen Compute an Image wich represents the Eigen Values and Vectors of a Matrix
         * @param [in] res the Eigen Values and Vectors to draw
         * @param [in] name The name of the Matrix
         * @param [in] col the colour of the text
         */

        QString computeImgEigen(const std::vector<std::pair<std::complex<double>, VectorX>>& res,
                             const QString& name, const QColor& col = QColor(0,0,0,0));

        /**
         * @brief computeImgDet Compute an Image wich represents the Determinant of a Matrix
         * @param [in] scalar the Determinant of the Matrix
         * @param [in] name the name of the Matrix
         * @param [in] col the colour of the text
         */

        QString computeImgDet(const std::complex<double> scalar, const QString& name, const QColor& col = QColor(0,0,0,0));

        /**
         * @brief computeImgTrace Compute an Image wich represents the Trace of a Matrix
         * @param [in] scalar the Trace of the Matrix
         * @param [in] name The name of the Matrix
         * @param [in] col The colour of the text
         */

        QString computeImgTrace(const std::complex<double> scalar, const QString& name, const QColor& col = QColor(0,0,0,0));

        /**
         * @brief clear clear the current Image
         */

        void clear();
};


#endif
