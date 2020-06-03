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

        virtual void updateViews() override final;

    private:

        MatrixViewWidget* view;
        MatrixPair op;
        std::pair<Matrix, Matrix> result;
        QWidget* choiceWidget;
        QRadioButton* result1;
        QRadioButton* result2;
        UnaryOpMatrix operation;

        void constructType(const type t);

    private slots :

        virtual void computeSelection(const bool view = 0) override final;

        virtual void computeOperation() override final;

        void emitResultChoice(const unsigned int choice);
};

#endif // DECOMPOSITIONWIDGET_H
