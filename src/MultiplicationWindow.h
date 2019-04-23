

#ifndef MULTIPLICATIONWINDOW_H
#define MULTIPLICATIONWINDOW_H


#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "MatrixLibrary.h"
#include "MatrixViewWidget.h"
#include "ShowMatrixWidget.h"


class MultiplicationWindow : public QWidget
{

    Q_OBJECT

    public:

        MultiplicationWindow (MatrixLibrary* lib, QWidget* parent = nullptr);
        ~MultiplicationWindow ();

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
