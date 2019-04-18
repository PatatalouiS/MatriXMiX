
#ifndef DeterminantWindow_H
#define DeterminantWindow_H


#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include "MatrixLibrary.h"
#include "MatrixViewWidget.h"
#include "ShowMatrixWidget.h"


class DeterminantWindow : public QDialog
{

    Q_OBJECT

    public:

        DeterminantWindow (MatrixLibrary* lib, QWidget* parent = nullptr);
        ~DeterminantWindow ();

    private slots:

        void computeSelection();
        void computeOperation();

    private:

        MatrixLibrary* lib;
        MatrixViewWidget* op1View;
        QLabel* op1Name;
        const Matrix* op1;
        double result;
        ShowMatrixWidget* resultImg;
        QVBoxLayout* mainLayout;
};


#endif
