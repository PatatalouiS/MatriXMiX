
#ifndef BINARYOPMATRIXNUMBERWIDGET_H
#define BINARYOPMATRIXNUMBERWIDGET_H

#include <QLineEdit>
#include "AbstractOperationWidget.h"
#include "MatrixViewWidget.h"


class BinaryOpMatrixNumberWidget : public AbstractOperationWidget
{
    Q_OBJECT

    using BinaryOpMatrixNumber = std::function<Matrix(const Matrix*, const double)>;

    public:

        enum type
        {
            SCALAR_MULTIPLICATION,
            POWER
        };

        BinaryOpMatrixNumberWidget(const type& t, const MatrixLibrary* lib, QWidget* parent = nullptr);

    public slots:

        virtual void updateViews() override final;

    private slots:

        virtual void computeSelection(bool view = 0) override final;
        virtual void computeOperation() override final;

    private:

       void constructType(const type& t);

       MatrixViewWidget* view;
       QLineEdit* edit;
       QPair<QString,const Matrix*> op1;
       double op2;
       QString logo;
       BinaryOpMatrixNumber operation;
       Matrix result;
};

#endif
