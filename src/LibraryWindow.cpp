
#include <QCloseEvent>
#include <QDirModel>
#include <QHeaderView>
#include <QDebug>
#include "LibraryWindow.h"
#include "MainWindow.h"


using namespace std;


LibraryWindow:: LibraryWindow (QWidget* main, MatrixLibrary* library) : QDialog(main)
{
    lib = library;
    matrixView = new MatrixViewWidget(lib, this);
    addMatrixWidget = new AddMatrixWidget(lib, this);
    showMatrixWidget = new ShowMatrixWidget(this);

    edit = new QPushButton("Editer");
    remove = new QPushButton("Supprimer");
    edit->setMinimumSize(100,50);
    remove->setMinimumSize(100,50);
    QHBoxLayout* viewFooterLayout = new QHBoxLayout;
    viewFooterLayout->addWidget(edit);
    viewFooterLayout->addWidget(remove);

    QVBoxLayout* matrixViewLayout = new QVBoxLayout;
    matrixViewLayout->addWidget(matrixView);
    matrixViewLayout->addLayout(viewFooterLayout);

    QTabWidget* choice = new QTabWidget;
    choice->addTab(showMatrixWidget, "Visualiser");
    choice->addTab(addMatrixWidget, "Ajouter");

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addLayout(matrixViewLayout);
    mainLayout->addWidget(choice);

    setLayout(mainLayout);

    connect(this, &LibraryWindow::close, main, &QWidget::show);
    connect(matrixView, &MatrixViewWidget::clicked,
            this, &LibraryWindow::compute_selection);
    connect(addMatrixWidget, &AddMatrixWidget::matrixAdded,
            matrixView, &MatrixViewWidget::addNewRow);
    connect(addMatrixWidget, &AddMatrixWidget::matrixAdded,
            qobject_cast<MainWindow*>(main), &MainWindow::addNewMatrix);
}


void LibraryWindow:: compute_selection()
{
	int currentRow = matrixView->currentIndex().row();
	QString currentName = matrixView->model()
            ->item(currentRow, 0)->data(2).toString();
	const Matrix* currentMatrix = lib->find(currentName.toStdString());
	showMatrixWidget->computeImgMatrix(currentMatrix, QColor(226, 226, 226));
}


void LibraryWindow:: closeEvent (QCloseEvent* event)
{
    emit close();
    event->accept();
}


LibraryWindow:: ~LibraryWindow()
{   
}
