#include <iostream>
#include <QDebug>
#include <QPainter>
#include <QHBoxLayout>
#include <QScrollBar>
#include "ShowMatrixWidget.h"
#include "jkqtmathtext/jkqtmathtext.h"
#include "Fraction.h"



ShowMatrixWidget::ShowMatrixWidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* showMatrixLayout = new QHBoxLayout;
    showMatrixLayout->setAlignment(Qt::AlignCenter);
    imgSelected = new QLabel(this);

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


void ShowMatrixWidget:: computeImgMatrix(const Matrix& mat, const unsigned int sizeTxt, const QColor& col)
{

//    unsigned int rows = mat.getNbRows();
//    unsigned int cols = mat.getNbCols();

//	QString latex = "\\begin{bmatrix}";

//	for(unsigned int i = 0; i < rows; ++i)
//	{
//        latex += "\t" +  QString::number(mat[i][0]);

//		for(unsigned int j = 1; j < cols; ++j)
//		{
//			if(j != cols) latex += " & ";
//			else latex += " &";
//            latex += QString::number(mat[i][j]);
//			if((j == cols-1) && (i != rows-1)) latex += "\\\\";
//		}
//	}
//	latex += "\\end{bmatrix}";
//   setPixmapToQLabel(col, latex, sizeTxt);

    unsigned int rows = mat.getNbRows();
    unsigned int cols = mat.getNbCols();
    clock_t t1 = clock();
    QString latex = "\\begin{bmatrix}";
    Fraction ftemp;
    for(unsigned int i = 0; i < rows; ++i)
    {
        if (ftemp.isFraction(mat[i][0]))
        {
            Fraction f (ftemp.double2Fraction(mat[i][0]));
            latex += "\t " + QString ("\\frac{")
                    + QString::number(f.numerateur)
                    + QString ("}{")
                    + QString::number(f.denominateur)
                    + QString ("}");
        }
        else
        {
            latex += "\t" +  QString::number(mat[i][0]);
        }

        for(unsigned int j = 1; j < cols; ++j)
        {
            if(j != cols) latex += " & ";
            else latex += " &";
            if (ftemp.isFraction(mat[i][j]))
            {
                Fraction f (ftemp.double2Fraction(mat[i][j]));
                latex += "\t " + QString ("\\frac{")
                        + QString::number(f.numerateur)
                        + QString ("}{")
                        + QString::number(f.denominateur)
                        + QString ("}");
            }
            else
            {
                latex += "\t" +  QString::number(mat[i][j]);
            }
            if((j == cols-1) && (i != rows-1)) latex += "\\\\";
        }
    }
    latex += "\\end{bmatrix}";

    clock_t t2 = clock();
    cout << "Temps d'exécution : " << t2-t1 << endl;
   setPixmapToQLabel(col, latex, sizeTxt);
}

void ShowMatrixWidget:: computeImgDet(const double scalar, const QString& name, const QColor& col)
{
    QString latex = "\\mathit{Det}\\(" + name + ") = " + QString::number(scalar);
    setPixmapToQLabel(col, latex, 40);
}


void ShowMatrixWidget:: computeImgTrace(const double scalar, const QString& name, const QColor& col)
{
    QString latex = "\\mathit{Tr}\\(" + name + ") = " + QString::number(scalar);
    setPixmapToQLabel(col, latex, 40);
}


void ShowMatrixWidget:: computeImgDimMatrix(const std::pair<unsigned int, unsigned int>& res,
const QString& name, const QColor& col)
{
    QString latex = "\\begin{matrix}\\mathit{Rg}\\(" + name + ") = " + QString::number(res.first) +
                    "\\\\\\mathit{DimKer}\\(" + name + ") = " + QString::number(res.second) + "\\end{matrix}";

    setPixmapToQLabel(col, latex, 40);
}




void ShowMatrixWidget:: computeImgPolynomial(const Polynomial& res1, const std::vector<Polynomial>& res2, const QString& name, const QColor& col)
{
    std::ostringstream flux;
    QString developpedForm;
    QString factorizedForm;

    flux << res1;
    developpedForm = flux.str().c_str();
    for(auto i : res2)
    {
        flux.str("");
        flux << i;
        factorizedForm += QString::fromStdString( "(" + flux.str() + ") ");
    }

    QString latex = "\\begin{matrix}\\mathit{\\text{P}_{\\text{" + name + "}}}\\(X) = " + developpedForm + "\\\\"
                    "\\mathit{\\text{P}_{\\text{" + name + "}}}\\(X) = " + factorizedForm + "\\end{matrix}";

    setPixmapToQLabel(col, latex, 30);
}

void ShowMatrixWidget:: computeImgEigen(const std::vector<std::pair<double, VectorX>>& res,
const QString& name, const QColor& col)
{
    QString spec;
    QList<QString> vectors;

    QString temp;

    for(auto i : res)
    {
        temp = "( ";
        spec += QString::number(i.first) + ", ";
        for(auto j : i.second)
        {
            temp += QString::number(j) + ", ";
        }
        temp += " )";
        vectors.append(temp);
    }

    QString latex = "\\begin{matrix}\\mathit{Spec}\\(" + name + ") = \\{ " + spec + "\\} \\\\";

    for(unsigned int i = 0; i < res.size(); ++i)
    {
        latex += "\\mathit{\\text{v}_{\\text{" + QString::number(i) + "}}}\\ = " + vectors[int(i)] + "\\\\";
    }
    latex += "\\end{matrix}";

    setPixmapToQLabel(col, latex, 30);
}




void ShowMatrixWidget:: setPixmapToQLabel (const QColor &col, const QString& latex, const unsigned int sizeTxt)
{
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










