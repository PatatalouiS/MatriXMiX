
#ifndef SHOWMATRIXWIDGET_H
#define SHOWMATRIXWIDGET_H

#include <QLabel>
#include<QScrollArea>
#include "Matrix.h"


class ShowMatrixWidget : public QWidget
{
    Q_OBJECT

    private:

    QLabel* imgSelected;
    QScrollArea* scrollArea;

    void setPixmapToQLabel(const QColor& col, const QString& latex, const unsigned int sizeTxt);

    public:

    explicit ShowMatrixWidget(QWidget *parent = nullptr);

    public slots:

    void computeImgMatrix(const Matrix* mat, const QColor& col);
    void computeImgScalar(const double scalar, const unsigned int type,
                          const QString& name, const QColor& col);
    void computeImgDimMatrix(const std::pair<unsigned int, unsigned int>& res,
                           const QString& name, const QColor& col);
    void computeImgPolynomial(const Polynomial& res1, const std::vector<Polynomial>& res2,
                              const QString& name, const QColor& col);
    void computeImgEigen(const std::vector<std::pair<double, VectorX>>& res,
                         const QString& name, const QColor& col);

};

#endif
