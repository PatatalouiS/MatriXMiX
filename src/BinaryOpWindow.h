
#ifndef BINARY_OP_WINDOW_H
#define BINARY_OP_WINDOW_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include "MatrixLibrary.h"
#include "MatrixViewWidget.h"
#include "ShowMatrixWidget.h"

class BinaryOpWindow : public QDialog
{
    Q_OBJECT

    using OpValidator = std::function<bool(const Matrix*, const Matrix*)>;

public:

    BinaryOpWindow (MatrixLibrary* lib, QString type,
     QString logo, OpValidator v, QWidget* parent = nullptr);
    ~BinaryOpWindow ();

private slots:

    void computeSelection(bool op);
    void computeOperation();

private:

    QString nameOp;
    QString logoOp;
    OpValidator validator;
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
};

#endif
