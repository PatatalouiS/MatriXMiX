
#ifndef BinaryOpMatrixMatrixWidget_H
#define BinaryOpMatrixMatrixWidget_H


#include "AbstractOperationWidget.h"
#include "MatrixViewWidget.h"
#include <QPair>




class BinaryOpMatrixMatrixWidget : public AbstractOperationWidget
{
    Q_OBJECT

    using BinaryOpMatrixMatrix = std::function<Matrix(const Matrix*, const Matrix*)>;
    using SortViewFunction = std::function<std::function<bool(const Matrix*)>(const Matrix*)>;

    public:

        enum type
        {
            ADDITION,
            SOUSTRACTION,
            MULTIPLICATION,
            DIVISION
        };

        BinaryOpMatrixMatrixWidget(const type& t, const MatrixLibrary* lib, QWidget* parent = nullptr);
        void setLogo(const QString& logo);

    public slots:

        virtual void updateViews() override final;

    private slots:

        virtual void computeSelection(bool view = 0) override final;
        virtual void computeOperation() override final;

    private:

       void constructType(const type& t);

       MatrixViewWidget* view1;
       MatrixViewWidget* view2;
       QPair<QString,const Matrix*> op1;
       QPair<QString,const Matrix*> op2;
       QString logo;
       BinaryOpMatrixMatrix operation;
       SortViewFunction sortViewFunction;
       Matrix result;
};


#endif
