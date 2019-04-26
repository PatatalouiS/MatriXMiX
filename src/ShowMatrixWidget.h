
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

    void computeImgMatrix(const Matrix& mat, const QColor& col = QColor(0,0,0,0));
    void computeImgDimMatrix(const std::pair<unsigned int, unsigned int>& res,
                           const QString& name, const QColor& col = QColor(0,0,0,0));
    void computeImgPolynomial(const Polynomial& res1, const std::vector<Polynomial>& res2,
                              const QString& name, const QColor& col = QColor(0,0,0,0));
    void computeImgEigen(const std::vector<std::pair<double, VectorX>>& res,
                         const QString& name, const QColor& col = QColor(0,0,0,0));
    void computeImgDet(const double scalar, const QString& name, const QColor& col = QColor(0,0,0,0));
    void computeImgTrace(const double scalar, const QString& name, const QColor& col = QColor(0,0,0,0));

};

#endif
