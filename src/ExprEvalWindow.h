
#ifndef ExprEvalWindow_H
#define ExprEvalWindow_H


#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include "MatrixLibrary.h"
#include "MatrixViewWidget.h"
#include "ShowMatrixWidget.h"


class ExprEvalWindow : public QWidget
{

    Q_OBJECT

    public:

        ExprEvalWindow (MatrixLibrary* lib, QWidget* parent = nullptr);
        ~ExprEvalWindow ();

    private slots:

        void computeOperation();

    private:

        MatrixLibrary* lib;
        MatrixViewWidget* op1View;
        QLineEdit* expression;
        Matrix result;
        ShowMatrixWidget* resultImg;
        QVBoxLayout* mainLayout;
};


#endif
