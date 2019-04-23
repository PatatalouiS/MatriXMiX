
#ifndef ScalarMultiplicationWindow_H
#define ScalarMultiplicationWindow_H


#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include "MatrixLibrary.h"
#include "MatrixViewWidget.h"
#include "ShowMatrixWidget.h"


class ScalarMultiplicationWindow : public QWidget
{

    Q_OBJECT

    public:

        ScalarMultiplicationWindow (MatrixLibrary* lib, QWidget* parent = nullptr);
        ~ScalarMultiplicationWindow ();

    private slots:

        void computeSelection(bool op);
        void computeOperation();

    private:

        MatrixLibrary* lib;
        MatrixViewWidget* op1View;
        QLineEdit* op2Edit;
        QString op1Name;
        const Matrix* op1;
        double op2;
        Matrix result;
        QLabel* formula;
        ShowMatrixWidget* resultImg;
        QVBoxLayout* mainLayout;
};





#endif
