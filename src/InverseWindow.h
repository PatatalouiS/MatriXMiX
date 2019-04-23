
#ifndef InverseWindow_H
#define InverseWindow_H


#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include "MatrixLibrary.h"
#include "MatrixViewWidget.h"
#include "ShowMatrixWidget.h"


class InverseWindow : public QDialog
{

    Q_OBJECT

    public:

        InverseWindow (MatrixLibrary* lib, QWidget* parent = nullptr);
        ~InverseWindow ();

    private slots:

        void computeSelection();
        void computeOperation();

    private:

        MatrixLibrary* lib;
        MatrixViewWidget* op1View;
        QLabel* op1Name;
        const Matrix* op1;
        Matrix result;
        ShowMatrixWidget* resultImg;
        QVBoxLayout* mainLayout;
};


#endif
