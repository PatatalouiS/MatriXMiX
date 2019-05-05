

#ifndef DIAGONALISATIONWIDGET_H
#define DIAGONALISATIONWIDGET_H

#include "AbstractOperationWidget.h"
#include "MatrixViewWidget.h"
#include <array>


/**
@class DiagonalisationWidget  none none   the goal of this class is to compute the diagonalisation of a Matrix in R set. \n
        User can compute the P, D, and P_INVERSE Matrices with this class.
*/


class DiagonalisationWidget : public AbstractOperationWidget
{
    Q_OBJECT

    public:

        /** @brief Unique constructor of the class.
         * @param [in] library a pointer on a MatrixLibrary .
         * @param [in,out] parent a pointer on a potential parent QWidget, mainly for ensure good deletion.
         */

        DiagonalisationWidget (const MatrixLibrary* lib, QWidget* parent = nullptr);

    public slots:


        /**
         * @brief implementation of AbstractOperationWidget::updateViews()
         */

        virtual void updateViews() override final;

    private:

        enum ResultChoice
        {
            P = 0,
            D = 1,
            P_INVERSE = 2
        };

        MatrixViewWidget* view;
        MatrixPair op;
        std::array<Matrix, 3> result;
        QWidget* choiceWidget;


    private slots:

        /**
         * @brief implementation of AbstractOperationWidget::computeSelection(const bool view)
         */

        virtual void computeSelection(const bool view = 0) override final;

        /**
         * @brief implementation of AbstractOperationWidget::computeOperation()
         */

        virtual void computeOperation() override final;

        /** @brief emit the good Matrix Result (using AbstractOperationWidget::newResult(const QVariant result) \n
         *          in fonction of the user selection ( P Matrix, P_INVERSE Matrix or D Matrix).
         * @param [in] resultChoice the type of the selected Result (enum).
         */

        void emitResultChoice(const ResultChoice& resultChoice);
};



#endif
