
#include <QCloseEvent>
#include <QDirModel>
#include <QHeaderView>
#include <QDebug>
#include "LibraryWindow.h"


using namespace std;


LibraryWindow:: LibraryWindow (QWidget* main, MatrixLibrary* library) : QDialog(main)
{
    lib = library;
    matrixView = new QTableView;
    matrixModel = new QStandardItemModel(0,3);
    addMatrixWidget = new AddMatrixWidget(lib, this);
    showMatrixWidget = new ShowMatrixWidget(this);

    matrixModel->setHorizontalHeaderLabels({"Nom", "NbL", "NbC"});
    matrixView->setModel(matrixModel);
    matrixView->setSortingEnabled(true);
    matrixView->setColumnWidth(0, 90);
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
    connect(matrixView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &LibraryWindow::compute_selection);
}


void LibraryWindow:: compute_selection()
{
	int currentRow = matrixView->currentIndex().row();
	QString currentName = matrixModel->item(currentRow, 0)->data(2).toString();
	const Matrix* currentMatrix = lib->find(currentName.toStdString());
	showMatrixWidget->compute_img(currentMatrix);
}


void LibraryWindow:: closeEvent (QCloseEvent* event)
{
    emit close();
    event->accept();
}

void LibraryWindow:: updateView (QList<QStandardItem*> newLine)
{
    matrixModel->appendRow(newLine);
    matrixView->sortByColumn(0, Qt::AscendingOrder);
}


LibraryWindow:: ~LibraryWindow()
{   
}
