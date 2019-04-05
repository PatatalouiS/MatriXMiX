
#ifndef SHOWMATRIXWIDGET_H
#define SHOWMATRIXWIDGET_H

#include <QWidget>
#include <QLabel>
#include "Matrix.h"

class ShowMatrixWidget : public QWidget
{

    private:

    QLabel* imgSelected;


    Q_OBJECT

    public:

    explicit ShowMatrixWidget(QWidget *parent = nullptr);

    signals:


    public slots:

    void compute_img(const Matrix* mat);
};

#endif
