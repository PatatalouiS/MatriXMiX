
#ifndef SHOWMATRIXWIDGET_H
#define SHOWMATRIXWIDGET_H

#include <QLabel>
#include <QScrollArea>
#include "../maths/Matrix.h"

class ShowMatrixWidget : public QWidget
{
    Q_OBJECT

    private:

    QLabel* imgSelected;
    QScrollArea* scrollArea;

    void setPixmapToQLabel(const QColor& col, const QString& latex, const unsigned int sizeTxt);

    public:

    explicit ShowMatrixWidget(QWidget *parent = nullptr);
    const QPixmap& getCurrentPixmap() const;

    public slots:

    void computeImgMatrix(const Matrix& mat, const unsigned int sizeTxt = 20, const QColor& col = QColor(0,0,0,0));
    void computeImgDimMatrix(const std::pair<unsigned int, unsigned int>& res,
                           const QString& name, const QColor& col = QColor(0,0,0,0));
    void computeImgPolynomial(const Polynomial& res1, const std::vector<Polynomial>& res2,
                              const QString& name, const QColor& col = QColor(0,0,0,0));
    void computeImgEigen(const std::vector<std::pair<double, VectorX>>& res,
                         const QString& name, const QColor& col = QColor(0,0,0,0));
    void computeImgDet(const double scalar, const QString& name, const QColor& col = QColor(0,0,0,0));
    void computeImgTrace(const double scalar, const QString& name, const QColor& col = QColor(0,0,0,0));
    void clear();

};

#endif
