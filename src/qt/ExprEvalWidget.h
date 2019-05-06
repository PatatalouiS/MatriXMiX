

#ifndef EXPREVALWIDGET_H
#define EXPREVALWIDGET_H


#include "AbstractOperationWidget.h"
#include "MatrixViewWidget.h"
#include <QLineEdit>


/**
@class ExPrEvalWidget  none none   the goal of this class is to compute a mathematical expresion, wich contains Matrices.
        User can edit his own expression in a QLineEdit
*/

class ExprEvalWidget : public AbstractOperationWidget
{
    Q_OBJECT

    public:

        /** @brief Unique constructor of the class.
         * @param [in] library a pointer on a MatrixLibrary .
         * @param [in,out] parent a pointer on a potential parent QWidget, mainly for ensure good deletion.
         */

        ExprEvalWidget(const MatrixLibrary* lib, QWidget* parent = nullptr);

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

        MatrixViewWidget* view;
        QLineEdit* expression;
        Matrix result;
};


#endif
