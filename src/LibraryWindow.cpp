
#include <QCloseEvent>
#include <QDirModel>
#include <QHeaderView>
#include <QDebug>
#include "LibraryWindow.h"
#include "Error.h"

using namespace std;



LibraryWindow:: LibraryWindow (QWidget* main, MatrixLibrary* library) : QDialog(main)
{
    lib = library;
    matrixView = new MatrixViewWidget(lib, this);
    addMatrix = new SetMatrixWidget(SetMatrixWidget::ADD, lib, this);
    editMatrix = new SetMatrixWidget(SetMatrixWidget::EDIT, lib, this);
    showMatrixWidget = new ShowMatrixWidget(this);

    remove = new QPushButton("Supprimer");
    remove->setMinimumSize(100,50);
    remove->setStyleSheet("QPushButton:hover{ background-color: lightBlue }");
    QHBoxLayout* viewFooterLayout = new QHBoxLayout;
    viewFooterLayout->addWidget(remove);

    QVBoxLayout* matrixViewLayout = new QVBoxLayout;
    matrixViewLayout->addWidget(matrixView);
    matrixViewLayout->addLayout(viewFooterLayout);

    choice = new QTabWidget;
    choice->addTab(showMatrixWidget, "Visualiser");
    choice->addTab(addMatrix, "Ajouter");
    choice->addTab(editMatrix, "Modifier");
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
            this, &LibraryWindow::computeViewSelection);
    connect(addMatrix, &SetMatrixWidget::newMatrixAdded,
            matrixView, &MatrixViewWidget::addNewRow);
    connect(addMatrix, &SetMatrixWidget::newMatrixAdded,
            this,&LibraryWindow::libraryChanged);
    connect(editMatrix, &SetMatrixWidget::matrixEdited,
            matrixView, &MatrixViewWidget::editRow);
    connect(editMatrix, &SetMatrixWidget::matrixEdited,
            this, &LibraryWindow::libraryChanged);
    connect(editMatrix, &SetMatrixWidget::matrixEdited,
            [this]() -> void
            {
                computeViewSelection();
                choice->setCurrentIndex(0);
            });
    connect(remove, &QPushButton::clicked,
            this, &LibraryWindow::removeSelectedMatrix);
}



void LibraryWindow:: computeViewSelection ()
{
    QString selectedName = matrixView->nameOfSelectedMatrix();
    assert(lib->exist(selectedName.toStdString()));
    const Matrix* selectedMatrix = lib->find(selectedName.toStdString());
    showMatrixWidget->computeImgMatrix(*selectedMatrix);
    editMatrix->chargeMatrix(selectedName);
}


void LibraryWindow:: removeSelectedMatrix ()
{
    QString selectedName = matrixView->nameOfSelectedMatrix();

    if(selectedName == "")
    {
        Error::showError("Suppression impossible !", "Veuillez sélectionner une Matrice", this);
    }

    matrixView->removeRow(matrixView->currentIndex().row());
    assert(lib->exist(selectedName.toStdString()));
    lib->erase(selectedName.toStdString());
    lib->print();
    emit libraryChanged();
}


void LibraryWindow:: updateView()
{
    matrixView->refresh();
}



LibraryWindow:: ~LibraryWindow()
{   
}



