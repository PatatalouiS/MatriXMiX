#ifndef DECOMPOSITIONWIDGET_H
#define DECOMPOSITIONWIDGET_H

#include "AbstractOperationWidget.h"
#include "MatrixViewWidget.h"

#include <QRadioButton>

using UnaryOpMatrix = std::function<std::pair<Matrix, Matrix>(const Matrix*)>;

class DecompositionWidget : public AbstractOperationWidget
{
    Q_OBJECT

    public:

        enum type {
            QR,
            LU,
            CHOLESKY
        };

        DecompositionWidget(const type type, const QMatrixLibrary* lib,
                            QWidget* parent = nullptr);

    public slots :

        /**
         * @brief implementation of AbstractOperationWidget::updateViews()
         */
        virtual void updateViews() override final;

    private:

        MatrixViewWidget* view;
        MatrixPair op;
        std::pair<Matrix, Matrix> result;
        QWidget* choiceWidget;
        QRadioButton* result1;
        QRadioButton* result2;
        UnaryOpMatrix operation;

        /**
         * @brief constructType this fonction is called one time, when the object is constructed.\n
         *       It construct the operation attributes and caracteristics in fonction of the enum DecompositionWidget::type given.
         * @param [in] the type of the binary operation.
         */
        void constructType(const type t);

    private slots :

        /**
         * @brief implementation of AbstractOperationWidget::computeSelection(const bool view)
         */
        virtual void computeSelection(const bool view = 0) override final;

        /**
         * @brief implementation of AbstractOperationWidget::computeOperation()
         */
        virtual void computeOperation() override final;


        void emitResultChoice(const unsigned int choice);
};

#endif // DECOMPOSITIONWIDGET_H
