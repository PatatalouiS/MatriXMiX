

#ifndef AbstractOperationWidget_H
#define AbstractOperationWidget_H

#include <QLabel>
#include <QPushButton>
#include <QVariant>
#include "QMatrixLibrary.hpp"

using EigenResult = QPair<QString, std::vector<std::pair<std::complex<double>, VectorX>>>;
using DoubleResult = QPair<QString, std::complex<double>>;
using PolynomialResult = std::tuple<QString, Polynomial, std::vector<Polynomial>>;
using KerImgDimResult = QPair<QString, std::pair<unsigned int, unsigned int>>;
Q_DECLARE_METATYPE(Matrix);
Q_DECLARE_METATYPE(DoubleResult);
Q_DECLARE_METATYPE(EigenResult);
Q_DECLARE_METATYPE(PolynomialResult);
Q_DECLARE_METATYPE(KerImgDimResult);


/**
@class AbstractOperationWidget the base class for all the Operation classes defined in MatriXMIX. \n
        It's an abstract class, you CAN'T instantiate it in your code .
*/

class AbstractOperationWidget : public QWidget
{

    Q_OBJECT

    public :

        /**
         * @brief Unique constructor of the class. he is used in the child classes constructor.
         * @param [in] lib a pointer on a MatrixLibrary class
         * @param [in, out] parent a pointer on a potential parent Qwidget, mainly for ensure good deletion.
         */

        AbstractOperationWidget(const QMatrixLibrary* lib, QWidget* parent = nullptr);

    public slots:


        /**
         * @brief Pure Virtual Function. In charge to update the different MatrixViewWidget of Matrix in child classes.
         */

        virtual void updateViews() = 0;

    protected slots:

        /**
         * @brief Pure Virtual Function. In charge to compute the user choices, when he select a Matrix in a MatrixViewWidget.
         * @param [in] viewId the Id of the MatrixViewWidget 's selected by the user. \n
         *      Only two values are possible because the child classes can contains only 2 views . (Unary or Binary operations).
         */

        virtual void computeSelection(const bool viewId = 0) = 0;

        /**
         * @brief Pure Virtual Function. In charge to compute the result of a Matrix operation. The operands are selected by the user.\n
         *      the signal newResult(const QVariant res) is emitted if the result is valid.
         */

        virtual void computeOperation() = 0;

    protected :

        using SortFunction = std::function<bool(const Matrix*)>;
        using MatrixPair = QPair<QString, const Matrix*>;

        SortFunction sortFunction;
        QLabel* description;
        QLabel* title;
        QPushButton* calculer;

        /**
         *  @brief getter function, return a pointer on the const MatrixLibrary lib member
         *  @return const MatrixLibrary*
         */

        const QMatrixLibrary* getLib () const;

        /**
         * @brief set the Title of the OperationWidget.
         * @param [in] str the title of the Operation
         */

        void setTitle(const QString& str);

        /**
         * @brief set the SortFunction of the OperationWidget, in charge to order the availables Matrices for an operation.
         * @param [in] sort the lambda SortFunction
         */

        void setSortFunction(SortFunction&& sort);

    private :

        const QMatrixLibrary* lib;

    signals:

        void newResult(const QVariant res);
};


#endif
