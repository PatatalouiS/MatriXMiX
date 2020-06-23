
#include <iostream>
#include <QHBoxLayout>
#include <complex>
#include "ShowMatrixWidget.h"
#include "jkqtmathtext/jkqtmathtext.h"
#include "../maths/Fraction.h"
#include "../maths/Utils.hpp"


namespace {

QString complexToQLaTeX(const std::complex<double> & v) {
    return QString::fromStdString(Utils::complex2LaTeX(v));
}

QString doubleToQLaTeX(const double & d) {
    return QString::fromStdString(Utils::print(d));
}

}


ShowMatrixWidget::ShowMatrixWidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* showMatrixLayout = new QHBoxLayout;
    showMatrixLayout->setAlignment(Qt::AlignCenter);
    imgSelected = new QLabel(this);
    clear();
    showMatrixLayout->addWidget(imgSelected);
    showMatrixLayout->setAlignment(Qt::AlignHCenter);
    setLayout(showMatrixLayout);
    hide();
}


const QPixmap& ShowMatrixWidget:: getCurrentPixmap() const
{
    const QPixmap* temp = imgSelected->pixmap();
    return *temp;
}


QString ShowMatrixWidget:: computeImgMatrix(const Matrix& mat, const unsigned int sizeTxt, const QColor& col)
{
    unsigned int rows = mat.getNbRows();
    unsigned int cols = mat.getNbCols();
    QString latex = "\\begin{bmatrix}";

    for(unsigned int i = 0; i < rows; ++i)
    {
        latex += "\t" +  complexToQLaTeX(mat[i][0]);

        if(cols == 1) {
            latex += "\\\\";
        }


        for(unsigned int j = 1; j < cols; ++j)
        {
            if(j != cols) 
                latex += " & ";
            else latex += " &";

            latex += "\t" +  complexToQLaTeX(mat[i][j]);
            if((j == cols-1) && (i != rows-1)) latex += "\\\\";
        }
    }
    latex += "\\end{bmatrix}";


   setPixmapToQLabel(col, latex, sizeTxt);
   return latex;
}


QString ShowMatrixWidget:: computeImgDet(const std::complex<double> det, const QString& name, const QColor& col)
{
    QString latex = "\\mathit{Det}\\(" + name + ") = " + complexToQLaTeX(det);
    setPixmapToQLabel(col, latex, 40);
    return latex;
}


QString ShowMatrixWidget:: computeImgTrace(const std::complex<double> scalar, const QString& name,
                                        const QColor& col)
{
    QString latex = "\\mathit{Tr}\\(" + name + ") = " + complexToQLaTeX(scalar);
    setPixmapToQLabel(col, latex, 40);
    return latex;
}


QString ShowMatrixWidget:: computeImgDimMatrix(const std::pair<unsigned int, unsigned int>& res,
                                            const QString& name, const QColor& col)
{
    QString latex = "\\begin{matrix}\\mathit{Rg}\\(" + name + ") = " + QString::number(res.first) +
                    "\\\\\\mathit{DimKer}\\(" + name + ") = " + QString::number(res.second) + "\\end{matrix}";

    setPixmapToQLabel(col, latex, 40);
    return latex;
}


 QString ShowMatrixWidget:: computeImgPolynomial(const Polynomial& res1, const std::vector<Polynomial>& res2,
                                              const QString& name, const QColor& col)
{
    std::ostringstream flux;
    QString developpedForm;
    QString factorizedForm;

    for(unsigned int i = 0; i < res1.tab.size(); i++)
    {
        QString x;
        QString power;
        std::complex<double> temp = res1.tab[i];

        double real = temp.real();
        double imag = temp.imag();

        if (i == 0)
            x = QString("");
        else
            x = QString("+X^{");

        if (i == 1)
            power = QString ("");
        else
            power = QString::number(i);


        if(real == 0.0)
        {
            if(imag != 0.0)
                developpedForm += doubleToQLaTeX(imag) + "i";
        }

        else if(real < 0.0)
        {
            if(imag == 0.0)
                developpedForm += doubleToQLaTeX(real);
            else if (imag < 0.0)
                developpedForm += " - (" + doubleToQLaTeX(abs(real)) + doubleToQLaTeX(abs(imag)) + "i)";
            else
                developpedForm += " + (" + doubleToQLaTeX(real) + "+" + doubleToQLaTeX(imag) + "i)";
        }

        else
        {
            if(imag == 0.0)
                developpedForm += "+" + doubleToQLaTeX(real);
            else if (imag < 0.0)
                developpedForm += "+ (" + doubleToQLaTeX(real) + doubleToQLaTeX(imag) + "i)";
            else
                developpedForm += "+ (" + doubleToQLaTeX(real) + "+" + doubleToQLaTeX(imag) + "i)";
        }

        if (x != "")
            developpedForm += x + power + "}";

    }


    for(auto i : res2)
    {
        flux.str("");
        flux << i.check();
        factorizedForm += QString::fromStdString( "(" + flux.str() + ") ");
    }

    QString latex = "\\begin{matrix}\\mathit{\\text{P}_{\\text{" + name + "}}}\\(X) = " + developpedForm + "\\\\"
                    "\\mathit{\\text{P}_{\\text{" + name + "}}}\\(X) = " + factorizedForm + "\\end{matrix}";

    setPixmapToQLabel(col, latex, 30);
    return latex;
}


QString ShowMatrixWidget:: computeImgEigen(const std::vector<std::pair<std::complex<double>, VectorX>>& res,
                                        const QString& name, const QColor& col)
{
    QString spec;
    QList<QString> vectors;
    QVector<QString> tab;
    QString temp, coef;


    if (res.empty())
    {

    }

    for(auto i : res)
    {
        temp = "( ";
        coef = complexToQLaTeX(i.first);
        tab.push_back(coef);
        spec += coef + ", ";

        for(auto j : i.second)
        {
            temp += complexToQLaTeX(j) + ", ";
        }

        temp.truncate(temp.size() - 2);
        temp += " )";
        vectors.append(temp);
    }
    spec.truncate(spec.size() - 2);

    QString latex = "\\begin{matrix}\\mathit{Spec}\\(" + name + ") = \\{ " + spec + "\\} \\\\";

    for(unsigned int i = 0; i < res.size(); ++i)
    {
        latex += "\\mathit{\\text{E}_{\\text{" + tab[int(i)]
                + "}}}\\ = vect\\{ " + vectors[int(i)] + "\\} \\\\";
    }
    latex += "\\end{matrix}";

    setPixmapToQLabel(col, latex, 30);
    return latex;
}


void ShowMatrixWidget:: setPixmapToQLabel (const QColor &col, const QString& latex, const unsigned int sizeTxt)
{

    clear();
    JKQTMathText mathText;
    mathText.useXITS();
    mathText.setFontSize(sizeTxt);
    mathText.parse(latex);
    QPainter painter;
    QSizeF size = mathText.getSize(painter);
    QPixmap temp(static_cast<int>(size.width()),static_cast<int>(size.height()));
    temp.fill(col);
    painter.begin(&temp);
    mathText.draw(painter, Qt::AlignCenter, QRectF(-5, 0, temp.width(), temp.height()), false);
    painter.end();
    imgSelected->setPixmap(temp);
}


void ShowMatrixWidget:: clear ()
{
    imgSelected->setPixmap(QPixmap());
}










