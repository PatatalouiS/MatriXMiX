
#ifndef BinaryOpMatrixMatrixWidget_H
#define BinaryOpMatrixMatrixWidget_H


#include "AbstractOperationWidget.h"
#include "MatrixViewWidget.h"
#include <QPair>


/**
@class BinaryOpMatrixMatrixWidget  none none   the goal of this class is to compute a binary operation between 2 matrices. \n
        The type and the operation is definitive and defined at the construction, with the enum BinaryOpMatrixMatrixWidget::type
*/


class BinaryOpMatrixMatrixWidget : public AbstractOperationWidget
{
    Q_OBJECT

    public:

        enum type
        {
            ADDITION,
            SOUSTRACTION,
            MULTIPLICATION,
            DIVISION,
            SOLVE
        };

        /** @brief Unique constructor of the class.
         * @param [in] type type of the Binary Matrix Operation. The enum is BinaryOpMatrixMatrixWidget::type .
         * @param [in] library a pointer on a QMatrixLibrary .
         * @param [in,out] parent a pointer on a potential parent QWidget, mainly for ensure good deletion.
         */

        BinaryOpMatrixMatrixWidget(const type& type, const QMatrixLibrary* library, QWidget* parent = nullptr);

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

       using BinaryOpMatrixMatrix = std::function<Matrix(const Matrix*, const Matrix*)>;
       using SortViewFunction = std::function<std::function<bool(const Matrix*)>(const Matrix*)>;

       MatrixViewWidget* view1;
       MatrixViewWidget* view2;
       MatrixPair op1;
       MatrixPair op2;
       QString logo;
       BinaryOpMatrixMatrix operation;
       SortViewFunction sortViewFunction;
       Matrix result;

       /**
        * @brief constructType this fonction is called one time, when the object is constructed.\n
        *       It construct the operation attributes and caracteristics in fonction of the enum BinaryOpMatrixMatrixWidget::type given.
        * @param [in] the type of the binary operation.
        */

       void constructType(const type& t);
};


#endif
