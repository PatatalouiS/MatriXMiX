
#include <iostream>
#include <QHBoxLayout>
#include <complex>
#include "ShowMatrixWidget.h"
#include "jkqtmathtext/jkqtmathtext.h"
#include "../maths/Fraction.h"



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


QString complexLatex (std::complex<double> coef)
{
    QString str;

    if (coef.real() != 0.0)
    {
        if (coef.imag() > 0)
            str = QString::number(coef.real()) + "+" + QString::number(coef.imag()) + "i";
        else if (coef.imag() < 0)
        {
            str = QString::number(coef.real()) + QString::number(coef.imag()) + "i";
        }
        else
        {
            str = QString::number(coef.real());
        }
    }

    else
    {
        if (coef.imag() != 0.0)
            str = QString::number(coef.imag()) + "i";
        else
            str = QString::number(0);
    }

    return str;

}


void ShowMatrixWidget:: computeImgMatrix(const Matrix& mat, const unsigned int sizeTxt, const QColor& col)
{
    unsigned int rows = mat.getNbRows();
    unsigned int cols = mat.getNbCols();
    QString latex = "\\begin{bmatrix}";
    
    for(unsigned int i = 0; i < rows; ++i)
    {
        latex += "\t" +  complexLatex(mat[i][0]);

        for(unsigned int j = 1; j < cols; ++j)
        {
            if(j != cols) 
                latex += " & ";
            else latex += " &";

            latex += "\t" +  complexLatex(mat[i][j]);
            if((j == cols-1) && (i != rows-1)) latex += "\\\\";
        }
    }
    latex += "\\end{bmatrix}";
   setPixmapToQLabel(col, latex, sizeTxt);
}


void ShowMatrixWidget:: computeImgDet(const double scalar, const QString& name, const QColor& col)
{
    QString latex = "\\mathit{Det}\\(" + name + ") = " + QString::number(scalar);
    setPixmapToQLabel(col, latex, 40);
}


void ShowMatrixWidget:: computeImgTrace(const std::complex<double> scalar, const QString& name,
                                        const QColor& col)
{
    QString latex = "\\mathit{Tr}\\(" + name + ") = " + complexLatex(scalar);
    setPixmapToQLabel(col, latex, 40);
}


void ShowMatrixWidget:: computeImgDimMatrix(const std::pair<unsigned int, unsigned int>& res,
                                            const QString& name, const QColor& col)
{
    QString latex = "\\begin{matrix}\\mathit{Rg}\\(" + name + ") = " + QString::number(res.first) +
                    "\\\\\\mathit{DimKer}\\(" + name + ") = " + QString::number(res.second) + "\\end{matrix}";

    setPixmapToQLabel(col, latex, 40);
}


 void ShowMatrixWidget:: computeImgPolynomial(const Polynomial& res1, const std::vector<Polynomial>& res2,
                                              const QString& name, const QColor& col)
{
    std::ostringstream flux;
    QString developpedForm;
    QString factorizedForm;

    flux << res1.check();

    for(unsigned int i = 0; i < res1.tab.size(); i++)
    {
        QString x;
        QString power;
        std::complex<double> temp = res1.tab[i];

        if (i == 0)
            x = QString("");
        else
            x = QString("+X^{");

        if (i == 1)
            power = QString ("");
        else
            power = QString::number(i);


        if(temp.real() == 0.0)
        {
            if(temp.imag() != 0.0)
                developpedForm += QString::number(temp.imag()) + "i";
        }

        else if(temp.real() < 0.0)
        {
            if(temp.imag() == 0.0)
                developpedForm += QString::number(temp.real());
            else if (temp.imag() < 0.0)
                developpedForm += " - (" + QString::number(abs(temp.real())) + QString::number(abs(temp.imag())) + "i)";
            else
                developpedForm += " + (" + QString::number(temp.real()) + "+" + QString::number(temp.imag()) + "i)";
        }

        else
        {
            if(temp.imag() == 0.0)
                developpedForm += "+" + QString::number(temp.real());
            else if (temp.imag() < 0.0)
                developpedForm += "+ (" + QString::number(temp.real()) + QString::number(temp.imag()) + "i)";
            else
                developpedForm += "+ (" + QString::number(temp.real()) + "+" + QString::number(temp.imag()) + "i)";
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
}


void ShowMatrixWidget:: computeImgEigen(const std::vector<std::pair<std::complex<double>, VectorX>>& res,
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
        coef = complexLatex(i.first);
        tab.push_back(coef);
        spec += coef + ", ";

        for(auto j : i.second)
        {
            temp += complexLatex(j) + ", ";
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









