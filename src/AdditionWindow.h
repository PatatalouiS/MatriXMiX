
#ifndef ADDITIONWINDOW_H
#define ADDITIONWINDOW_H


#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include "MatrixLibrary.h"
#include "MatrixViewWidget.h"
#include "ShowMatrixWidget.h"


class AdditionWindow : public QDialog
{

    Q_OBJECT

    public:

        AdditionWindow (MatrixLibrary* lib, QWidget* parent = nullptr);
        ~AdditionWindow ();

    private slots:

        void computeSelection(bool op);
        void computeOperation();

    private:

        MatrixLibrary* lib;
        MatrixViewWidget* op1View;
        MatrixViewWidget* op2View;
        QString op1Name;
        QString op2Name;
        const Matrix* op1;
        const Matrix* op2;
        Matrix result;
        QLabel* formula;
        ShowMatrixWidget* resultImg;
        QVBoxLayout* mainLayout;
};





#endif
