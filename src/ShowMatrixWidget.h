
#ifndef SHOWMATRIXWIDGET_H
#define SHOWMATRIXWIDGET_H

#include <QLabel>
#include "Matrix.h"


class ShowMatrixWidget : public QWidget
{
    Q_OBJECT

    private:

    QLabel* imgSelected;

    void setPixmapToQLabel(const QColor& col, const QString& latex, const unsigned int sizeTxt);

    public:

    explicit ShowMatrixWidget(QWidget *parent = nullptr);

    public slots:

    void computeImgMatrix(const Matrix* mat, const QColor& col);
    void computeImgScalar(const double scalar, const unsigned int type,
     const QString& name, const QColor& col);
};

#endif
