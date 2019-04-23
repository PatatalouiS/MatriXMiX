
#ifndef PolynomialWindow_H
#define PolynomialWindow_H


#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "MatrixLibrary.h"
#include "MatrixViewWidget.h"
#include "ShowMatrixWidget.h"


class PolynomialWindow : public QWidget
{

    Q_OBJECT

    public:

        PolynomialWindow (MatrixLibrary* lib, QWidget* parent = nullptr);
        ~PolynomialWindow ();

    private slots:

        void computeSelection();
        void computeOperation();

    private:

        MatrixLibrary* lib;
        MatrixViewWidget* op1View;
        QLabel* op1Name;
        const Matrix* op1;
        Polynomial result1;
        std::vector<Polynomial> result2;
        ShowMatrixWidget* resultImg;
        QVBoxLayout* mainLayout;
};


#endif
