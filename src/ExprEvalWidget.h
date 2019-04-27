

#ifndef EXPREVALWIDGET_H
#define EXPREVALWIDGET_H


#include "AbstractOperationWidget.h"
#include "MatrixViewWidget.h"
#include <QLineEdit>

class ExprEvalWidget : public AbstractOperationWidget
{
    Q_OBJECT

    public:

        ExprEvalWidget(const MatrixLibrary* lib, QWidget* parent = nullptr);

    public slots:

        virtual void updateViews() override final;

    private slots:

        virtual void computeSelection(bool view = 0) override final;
        virtual void computeOperation() override final;

    private:

        MatrixViewWidget* view;
        QLineEdit* expression;
        Matrix result;
};


#endif
