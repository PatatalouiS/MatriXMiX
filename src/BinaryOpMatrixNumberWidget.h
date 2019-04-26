
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

        void setLogo(const QString& logo);

    public slots:

        virtual void updateViews() override;

    private slots:

        virtual void computeSelection(bool view) override;
        virtual void computeOperation() override;

    private:

       void constructType(const type& t);

       MatrixViewWidget* view;
       QLineEdit* edit;
       QPair<QString,const Matrix*> op1;
       double op2;
       QString logo;
       BinaryOpMatrixNumber operation;
};

#endif
