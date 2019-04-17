

#ifndef DivisionWindow_H
#define DivisionWindow_H


#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include "MatrixLibrary.h"
#include "MatrixViewWidget.h"
#include "ShowMatrixWidget.h"


class DivisionWindow : public QDialog
{

    Q_OBJECT

    public:

        DivisionWindow (MatrixLibrary* lib, QWidget* parent = nullptr);
        ~DivisionWindow ();

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

        void showError(QString title, QString body) const;
        void setOperationSpecs(unsigned int type);
};





#endif
