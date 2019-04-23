
#ifndef RowReducedWindow_H
#define RowReducedWindow_H


#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "MatrixLibrary.h"
#include "MatrixViewWidget.h"
#include "ShowMatrixWidget.h"


class RowReducedWindow : public QWidget
{

    Q_OBJECT

    public:

        RowReducedWindow (MatrixLibrary* lib, QWidget* parent = nullptr);
        ~RowReducedWindow ();

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
