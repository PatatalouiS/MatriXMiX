
#ifndef TraceWindow_H
#define TraceWindow_H


#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "MatrixLibrary.h"
#include "MatrixViewWidget.h"
#include "ShowMatrixWidget.h"


class TraceWindow : public QWidget
{

    Q_OBJECT

    public:

        TraceWindow (MatrixLibrary* lib, QWidget* parent = nullptr);
        ~TraceWindow ();

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
