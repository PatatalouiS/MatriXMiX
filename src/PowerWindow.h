
#ifndef PowerWindow_H
#define PowerWindow_H


#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QSpinBox>
#include "MatrixLibrary.h"
#include "MatrixViewWidget.h"
#include "ShowMatrixWidget.h"


class PowerWindow : public QWidget
{

    Q_OBJECT

    public:

        PowerWindow (MatrixLibrary* lib, QWidget* parent = nullptr);
        ~PowerWindow ();

    private slots:

        void computeSelection(bool op);
        void computeOperation();

    private:

        MatrixLibrary* lib;
        MatrixViewWidget* op1View;
        QSpinBox* op2Edit;
        QString op1Name;
        const Matrix* op1;
        int op2;
        Matrix result;
        QLabel* formula;
        ShowMatrixWidget* resultImg;
        QVBoxLayout* mainLayout;
};





#endif
