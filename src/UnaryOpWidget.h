
#ifndef UNARYOPWIDGET_H
#define UNARYOPWIDGET_H



#include "AbstractOperationWidget.h"
#include "MatrixViewWidget.h"



class UnaryOpWidget : public AbstractOperationWidget
{
    Q_OBJECT

    using UnaryOpMatrix = std::function<const QVariant(const QPair<const QString, const Matrix*>)>;

    public:

        enum type
        {
            DETERMINANT,
            TRACE,
            INVERSE,
            ROW_REDUCED_FORM,
            EIGEN_PROPERTIES,
            CARACTERISTIC_POLYNOMIAL,
            KER_IMG_DIM
        };

        UnaryOpWidget(const type& t, const MatrixLibrary* lib, QWidget* parent = nullptr);


    public slots:

        virtual void updateViews() override final;

    private slots:

        virtual void computeSelection(bool view = 0) override final;
        virtual void computeOperation() override final;

    private:

        void constructType(const type& t);

        MatrixViewWidget* view;
        MatrixPair op;
        UnaryOpMatrix operation;
        QVariant result;
};



#endif
