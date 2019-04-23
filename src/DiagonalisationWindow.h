
#ifndef DiagonalisationWindow_H
#define DiagonalisationWindow_H


#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <array>
#include "MatrixLibrary.h"
#include "MatrixViewWidget.h"
#include "ShowMatrixWidget.h"


class DiagonalisationWindow : public QDialog
{

    Q_OBJECT

    public:

        DiagonalisationWindow (MatrixLibrary* lib, QWidget* parent = nullptr);
        ~DiagonalisationWindow ();

    private slots:

        void computeSelection();
        void computeOperation();

    private:

        MatrixLibrary* lib;
        MatrixViewWidget* op1View;
        QLabel* op1Name;
        const Matrix* op1;
        std::array<Matrix,3> result;
        QWidget* choiceWidget;
        ShowMatrixWidget* resultImg;
        QVBoxLayout* mainLayout;
};


#endif
