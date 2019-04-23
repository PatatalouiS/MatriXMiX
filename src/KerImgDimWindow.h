
#ifndef KerImgDimWindow_H
#define KerImgDimWindow_H


#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "MatrixLibrary.h"
#include "MatrixViewWidget.h"
#include "ShowMatrixWidget.h"


class KerImgDimWindow : public QWidget
{

    Q_OBJECT

    public:

        KerImgDimWindow (MatrixLibrary* lib, QWidget* parent = nullptr);
        ~KerImgDimWindow ();

    private slots:

        void computeSelection();
        void computeOperation();

    private:

        MatrixLibrary* lib;
        MatrixViewWidget* op1View;
        QLabel* op1Name;
        const Matrix* op1;
        std::pair<unsigned int, unsigned int> result;
        ShowMatrixWidget* resultImg;
        QVBoxLayout* mainLayout;
};


#endif
