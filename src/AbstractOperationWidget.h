

#ifndef AbstractOperationWidget_H
#define AbstractOperationWidget_H

#include <QLabel>
#include <QPushButton>
#include <QVariant>
#include "MatrixLibrary.h"


using EigenResult = QPair<QString, std::vector<std::pair<double, VectorX>>>;
using DoubleResult = QPair<QString, double>;
using PolynomialResult = std::tuple<QString, Polynomial, std::vector<Polynomial>>;
using KerImgDimResult = QPair<QString, std::pair<unsigned int, unsigned int>>;
Q_DECLARE_METATYPE(Matrix);
Q_DECLARE_METATYPE(DoubleResult);
Q_DECLARE_METATYPE(EigenResult);
Q_DECLARE_METATYPE(PolynomialResult);
Q_DECLARE_METATYPE(KerImgDimResult);



class AbstractOperationWidget : public QWidget
{

    Q_OBJECT

    using SortFunction = std::function<bool(const Matrix*)>;


    public :

        using MatrixPair = QPair<QString, const Matrix*>;
        AbstractOperationWidget(const MatrixLibrary* lib, QWidget* parent = nullptr);

    public slots:

        virtual void updateViews() = 0;

    protected slots:

        virtual void computeSelection(bool view = 0) = 0;
        virtual void computeOperation() = 0;

    protected :

        const MatrixLibrary* lib;
        SortFunction sortFunction;
        QLabel* description;
        QLabel* title;
        QPushButton* calculer;

        void setLib(const MatrixLibrary* lib);
        void setTitle(const QString& str);
        void setSortFunction(const SortFunction& s);

    signals:

        void newResult(const QVariant res);
};


#endif
