
#include <QCloseEvent>
#include <QDirModel>
#include <QHeaderView>
#include <QDebug>
#include <QScrollArea>
#include <QScrollBar>
#include "LibraryWindow.h"
#include "Error.h"

using namespace std;



LibraryWindow:: LibraryWindow (QWidget* main, MatrixLibrary* library) : QDialog(main)
{
    lib = library;
    matrixView = new MatrixViewWidget(lib, this);
    addMatrixWidget = new SetMatrixWidget(lib, this);
    editMatrixWidget = new SetMatrixWidget(lib, this);
    showMatrixWidget = new ShowMatrixWidget(this);

    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(showMatrixWidget);

    scrollArea->setStyleSheet("background-color:white ; border: none;");
    scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar:vertical "
               "{border: 1px solid #999999; background:white;"
               "width:15px; margin: 0px 0px 0px 0px;}"
               "QScrollBar::handle:vertical { background: qlineargradient"
               "(x1:0, y1:0, x2:1, y2:0,stop: 0 lightBlue, stop:1 Blue);"
               "border-radius:6px;}"
               "QScrollBar::add-line:vertical {height: 0px;}"
               "QScrollBar::sub-line:vertical {height: 0 px;}");
    scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal "
               "{border: 1px solid #999999; background:white; height:15px;}"
               "QScrollBar::handle:horizontal {background: qlineargradient"
               "(x1:0, y1:0, x2:0, y2:1,stop: 0 lightBlue, stop:1 Blue);"
               "border-radius:6px;}"
               "QScrollBar::add-line:horizontal {height: 0px;}"
               "QScrollBar::sub-line:horizontal {height: 0 px;}");


    remove = new QPushButton;

    QPixmap im(":/img/poubelle.png");
    im = im.scaled(50, 50);
    remove->setIcon(im);
    remove->setFixedSize(60,60);
    remove->setIconSize(im.rect().size());
    remove->setCursor(Qt::PointingHandCursor);
    remove->setStyleSheet("QPushButton:hover{ background-color: red;}");
    remove->setToolTip("Sélectionner une matrice et supprimer");
    QHBoxLayout* viewFooterLayout = new QHBoxLayout;
    viewFooterLayout->addWidget(remove);

    QVBoxLayout* matrixViewLayout = new QVBoxLayout;
    matrixViewLayout->addWidget(matrixView);
    matrixViewLayout->addLayout(viewFooterLayout);

    choice = new QTabWidget;
    choice->addTab(scrollArea, "Visualiser");
    choice->addTab(addMatrixWidget, "Ajouter");
    choice->addTab(editMatrixWidget, "Modifier");
    choice->setStyleSheet(
        "QTabBar::tab { background:"
        "qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 white, stop: 1 darkGrey);"
        "padding: 10px; border-radius: 6px; border:1px solid darkGrey ;} "
        "QTabBar::tab:selected { background: "
        "qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 lightBlue, stop: 1 blue); color:white } "
        "QTabWidget::tab-bar { alignment : center;}");

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addLayout(matrixViewLayout);
    mainLayout->addWidget(choice);

    setLayout(mainLayout);

    connect(matrixView, &MatrixViewWidget::clicked,
            this, &LibraryWindow::showSelectedMatrix);
    connect(addMatrixWidget, &SetMatrixWidget::newMatrixAdded,
            matrixView, &MatrixViewWidget::addNewRow);
    connect(addMatrixWidget, &SetMatrixWidget::newMatrixAdded,
            this,&LibraryWindow::libraryChanged);
    connect(remove, &QPushButton::clicked, this, &LibraryWindow::removeSelectedMatrix);
    //connect(edit, &QPushButton::clicked, this, &LibraryWindow::computeEditingQuery);
   //connect(editMatrixWidget, &SetMatrixWidget::matrixEdited, this, &LibraryWindow::libraryChanged);
   //connect(SetMatrixWidget, &SetMatrixWidget::matrixEdited, matrixView, &MatrixViewWidget::editRow());
}



void LibraryWindow:: showSelectedMatrix ()
{
    QString selectedName = matrixView->nameOfSelectedMatrix();
    assert(lib->exist(selectedName.toStdString()));
    const Matrix* selectedMatrix = lib->find(selectedName.toStdString());
    showMatrixWidget->computeImgMatrix(*selectedMatrix);
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
    emit libraryChanged();
}


void LibraryWindow:: computeEditingQuery()
{
    QString selectedMatrix = matrixView->nameOfSelectedMatrix();

    if(selectedMatrix == "")
    {
        Error::showError("Edition impossible !", "Vous devez sélectionner une matrice !", this);
        return;
    }

    choice->setTabEnabled(1, true);
    editMatrixWidget->computeEditing(selectedMatrix);
}



LibraryWindow:: ~LibraryWindow()
{   
}



