
#include <QPainter>
#include <QHBoxLayout>
#include "ShowMatrixWidget.h"
#include "jkqtmathtext/jkqtmathtext.h"


ShowMatrixWidget::ShowMatrixWidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* showMatrixLayout = new QHBoxLayout;
    showMatrixLayout->setAlignment(Qt::AlignCenter);
	imgSelected = new QLabel(this);
    showMatrixLayout->addWidget(imgSelected);
    setLayout(showMatrixLayout);
}


void ShowMatrixWidget:: computeImgMatrix(const Matrix* mat, const QColor& col)
{
	unsigned int rows = mat->getNbRows();
	unsigned int cols = mat->getNbCols();

	QString latex = "\\begin{bmatrix}";

	for(unsigned int i = 0; i < rows; ++i)
	{
		latex += "\t" +  QString::number((*mat)[i][0]);

		for(unsigned int j = 1; j < cols; ++j)
		{
			if(j != cols) latex += " & ";
			else latex += " &";
			latex += QString::number((*mat)[i][j]);
			if((j == cols-1) && (i != rows-1)) latex += "\\\\";
		}
	}
	latex += "\\end{bmatrix}";

   setPixmapToQLabel(col, latex, 20);
}


void ShowMatrixWidget:: computeImgScalar(const double scalar, const unsigned int type,
const QString& name, const QColor& col)
{
    QString latex;

    switch(type)
    {
        case 0: latex = "\\mathit{Det}\\(" + name + ") = " + QString::number(scalar); break;
        default: break;
    }

    setPixmapToQLabel(col, latex, 40);
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










