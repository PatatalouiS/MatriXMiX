
#include <QPainter>
#include <QHBoxLayout>
#include "jkqtmathtext/jkqtmathtext.h"
#include "ShowMatrixWidget.h"


ShowMatrixWidget::ShowMatrixWidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* showMatrixLayout = new QHBoxLayout;
    showMatrixLayout->setAlignment(Qt::AlignCenter);
	imgSelected = new QLabel(this);
    showMatrixLayout->addWidget(imgSelected);

    setLayout(showMatrixLayout);
}


void ShowMatrixWidget:: compute_img(const Matrix* mat)
{
	unsigned int rows = mat->getNbRows();
	unsigned int cols = mat->getNbCols();

	QPixmap temp(500,500);
	temp.fill(QColor("white"));
	QPainter painter;

	JKQTMathText mathText;
	mathText.useXITS();
	mathText.setFontSize(20);

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

	mathText.parse(latex);
	painter.begin(&temp);
	mathText.draw(painter, Qt::AlignCenter, QRectF(0,0, temp.width(), temp.height()), false);
	painter.end();

	imgSelected->setPixmap(temp);
	imgSelected->resize(500, 500);
}


