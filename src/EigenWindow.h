
#ifndef EigenWindow_H
#define EigenWindow_H


#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include "MatrixLibrary.h"
#include "MatrixViewWidget.h"
#include "ShowMatrixWidget.h"


class EigenWindow : public QDialog
{

    Q_OBJECT

    public:

        EigenWindow (MatrixLibrary* lib, QWidget* parent = nullptr);
        ~EigenWindow ();

    private slots:

        void computeSelection();
        void computeOperation();

    private:

        MatrixLibrary* lib;
        MatrixViewWidget* op1View;
        QLabel* op1Name;
        const Matrix* op1;
        std::vector<std::pair<double,VectorX>> result;
        ShowMatrixWidget* resultImg;
        QVBoxLayout* mainLayout;
};


#endif
