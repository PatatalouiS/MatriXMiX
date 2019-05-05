
#ifndef BINARYOPMATRIXNUMBERWIDGET_H
#define BINARYOPMATRIXNUMBERWIDGET_H

#include <QLineEdit>
#include "AbstractOperationWidget.h"
#include "MatrixViewWidget.h"



/**
@class BinaryOpMatrixNumberWidget  none none   the goal of this class is to compute a binary operation between a Matrix and a number. \n
        The type and the operation is definitive and defined at the construction, with the enum BinaryOpMatrixNumberWidget::type
*/



class BinaryOpMatrixNumberWidget : public AbstractOperationWidget
{
    Q_OBJECT  

    public:

        enum type
        {
            SCALAR_MULTIPLICATION,
            POWER
        };

        /** @brief Unique constructor of the class.
         * @param [in] type type of the Binary Matrix/Number Operation. The enum is BinaryOpMatrixNumberWidget::type .
         * @param [in] library a pointer on a MatrixLibrary .
         * @param [in,out] parent a pointer on a potential parent QWidget, mainly for ensure good deletion.
         */

        BinaryOpMatrixNumberWidget(const type& t, const MatrixLibrary* lib, QWidget* parent = nullptr);

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

       using BinaryOpMatrixNumber = std::function<Matrix(const Matrix*, const double)>;

       MatrixViewWidget* view;
       QLineEdit* edit;
       MatrixPair op1;
       double op2;
       QString logo;
       BinaryOpMatrixNumber operation;
       Matrix result;

       void constructType(const type& t);
};

#endif
