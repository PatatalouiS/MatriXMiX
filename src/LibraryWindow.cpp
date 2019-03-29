
#include <QCloseEvent>
#include <QDirModel>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QDebug>
#include "LibraryWindow.h"
#include "jkqtmathtext/jkqtmathtext.h"

using namespace std;


LibraryWindow:: LibraryWindow (QWidget* main) : QWidget()
{
    QHBoxLayout* lay = new QHBoxLayout;
    model = new QStandardItemModel(0,3);
    model->setHorizontalHeaderLabels({"Nom", "NbL", "NbC"});

    matrixView = new QTableView;
    matrixView->setModel(model);
    matrixView->setColumnWidth(0, 98);
    matrixView->setColumnWidth(1, 50);
    matrixView->setColumnWidth(2, 50);
    matrixView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    matrixView->setFixedWidth(200);
    matrixView->verticalHeader()->hide();
    matrixView->setSelectionBehavior(QAbstractItemView::SelectRows);
    matrixView->setShowGrid(false);
    matrixView->setAlternatingRowColors(true);
	matrixView->setStyleSheet("* {alternate-background-color: #d6d1d0;background-color: white;}"
							  "QHeaderView::section { background-color: #bdcef0; border: 0px;}");
    lay->addWidget(matrixView);
    
    
    compute_add();
	
	matrixView->selectRow(0);
	
	connect(matrixView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &LibraryWindow::compute_selection);
    
    QWidget* showMatrixWidget = new QWidget;
    QHBoxLayout* showMatrixLayout = new QHBoxLayout;
	imgSelected = new QLabel;
	showMatrixLayout->addWidget(imgSelected);
	showMatrixWidget->setLayout(showMatrixLayout);
	
	
	
	
	
    QWidget* addMatrix = new QWidget;
    QTabWidget* choice = new QTabWidget;
    choice->addTab(showMatrixWidget, "Visualiser");
    choice->addTab(addMatrix, "Ajouter");
    lay->addWidget(choice);
    
    
    setLayout(lay);
    connect(this, &LibraryWindow::close, main, &QWidget::show);
	connect(this, &LibraryWindow::update, this, &LibraryWindow::compute_selection);
	
	
	emit update();
}


void LibraryWindow:: compute_selection()
{
	int currentRow = matrixView->currentIndex().row();
	QString currentName = model->item(currentRow, 0)->data(2).toString();
	const Matrix* currentMatrix = lib.find(currentName.toStdString());
	
	compute_img(currentMatrix, imgSelected);
	
	
	
	
	
	
}


void LibraryWindow:: compute_img(const Matrix* mat, QLabel* img)
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
	
	img->setPixmap(temp);
	img->resize(500, 500);
}


void LibraryWindow:: compute_add ()
{
    lib.addMatrix("A", Matrix(3,3,Matrix::I));
    lib.addMatrix("B", Matrix(4,4,Matrix::I));
    QList<QStandardItem*> a;
    QList<QStandardItem*> b;
    
    const Matrix* mat = lib.find("A");
    a.append(new QStandardItem("A"));
    a.append(new QStandardItem(QString::number(mat->getNbRows())));
    a.append(new QStandardItem(QString::number(mat->getNbCols())));
    model->appendRow(a);
    
    mat = lib.find("B");
    b.append(new QStandardItem("B"));
    b.append(new QStandardItem(QString::number(mat->getNbRows())));
    b.append(new QStandardItem(QString::number(mat->getNbCols())));
    model->appendRow(b);
}


void LibraryWindow:: closeEvent (QCloseEvent* event)
{
    emit close();
    event->accept();
}



LibraryWindow:: ~LibraryWindow()
{
    
}
