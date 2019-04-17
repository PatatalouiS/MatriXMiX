

#ifndef MultiplicationWindow_H
#define MultiplicationWindow_H


#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include "MatrixLibrary.h"
#include "MatrixViewWidget.h"
#include "ShowMatrixWidget.h"


class MultiplicationWindow : public QDialog
{

    Q_OBJECT

    public:

        MultiplicationWindow (MatrixLibrary* lib, QWidget* parent = nullptr);
        ~MultiplicationWindow ();

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
