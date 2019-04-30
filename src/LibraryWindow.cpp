
#include <QCloseEvent>
#include <QDirModel>
#include <QHeaderView>
#include <QDebug>
#include "LibraryWindow.h"
#include "MainWindow.h"

using namespace std;

LibraryWindow:: LibraryWindow (MainWindow* main, MatrixLibrary* library) : QDialog(main)
{
    lib = library;
    matrixView = new MatrixViewWidget(lib, this);
    addMatrixWidget = new AddMatrixWidget(lib, this);
    showMatrixWidget = new ShowMatrixWidget(this);

    edit = new QPushButton("Editer");
    remove = new QPushButton("Supprimer");
    edit->setMinimumSize(100,50);
    remove->setMinimumSize(100,50);
    edit->setStyleSheet("QPushButton:hover{ background-color: lightBlue }");
    remove->setStyleSheet("QPushButton:hover{ background-color: lightBlue }");
    QHBoxLayout* viewFooterLayout = new QHBoxLayout;
    viewFooterLayout->addWidget(edit);
    viewFooterLayout->addWidget(remove);

    QVBoxLayout* matrixViewLayout = new QVBoxLayout;
    matrixViewLayout->addWidget(matrixView);
    matrixViewLayout->addLayout(viewFooterLayout);

    QTabWidget* choice = new QTabWidget;
    choice->addTab(showMatrixWidget, "Visualiser");
    choice->addTab(addMatrixWidget, "Ajouter");
    choice->setStyleSheet(
        "QTabBar::tab { background:"
        "qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 white, stop: 1 darkGrey);"
        "padding: 10px; border-radius: 6px; border:1px solid darkGrey ;} "
        "QTabBar::tab:selected { background: "
        "qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 lightBlue, stop: 1 blue); color:white } "
        "QTabWidget::tab-bar { alignment : center} ");

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addLayout(matrixViewLayout);
    mainLayout->addWidget(choice);

    setLayout(mainLayout);

    connect(matrixView, &MatrixViewWidget::clicked,
            this, &LibraryWindow::compute_selection);
    connect(addMatrixWidget, &AddMatrixWidget::matrixAdded,
            matrixView, &MatrixViewWidget::addNewRow);
    connect(addMatrixWidget, &AddMatrixWidget::matrixAdded,
            main,&MainWindow::addNewMatrix);
}

void LibraryWindow:: compute_selection()
{
	int currentRow = matrixView->currentIndex().row();
	QString currentName = matrixView->model()
            ->item(currentRow, 0)->data(2).toString();
	const Matrix* currentMatrix = lib->find(currentName.toStdString());
    showMatrixWidget->computeImgMatrix(*currentMatrix, QColor(226, 226, 226));
}


LibraryWindow:: ~LibraryWindow()
{   
}
