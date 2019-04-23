
#ifndef ExprEvalWindow_H
#define ExprEvalWindow_H


#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include "MatrixLibrary.h"
#include "MatrixViewWidget.h"
#include "ShowMatrixWidget.h"


class ExprEvalWindow : public QDialog
{

    Q_OBJECT

    public:

        ExprEvalWindow (MatrixLibrary* lib, QWidget* parent = nullptr);
        ~ExprEvalWindow ();

    private slots:

        void computeSelection();
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
