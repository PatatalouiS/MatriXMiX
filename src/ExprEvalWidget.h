

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

        virtual void updateViews() override;

    private slots:

        virtual void computeSelection(bool view = 0) override;
        virtual void computeOperation() override;

    private:

        MatrixViewWidget* view;
        QLineEdit* expression;
        Matrix result;
};








#endif
