
#include <QScrollBar>
#include <QScrollArea>
#include "LibraryWindow.h"
#include "Error.h"


using namespace std;


LibraryWindow:: LibraryWindow (QWidget* main, MatrixLibrary* library) : QWidget(main)
{
    lib = library;
    matrixView = new MatrixViewWidget(lib, this);
    addMatrix = new SetMatrixWidget(SetMatrixWidget::ADD, lib, this);
    editMatrix = new SetMatrixWidget(SetMatrixWidget::EDIT, lib, this);
    showMatrixWidget = new ShowMatrixWidget(this);


    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(showMatrixWidget);

    scrollArea->setStyleSheet("border: none;"
                              "background:transparent;");
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

    remove = new QPushButton("  Supprimer");

    QPixmap im(":/img/trash.png");
    im = im.scaled(30, 30);
    remove->setIcon(im);
    remove->setMinimumSize(100,30);
    remove->setIconSize(im.rect().size());
    remove->setCursor(Qt::PointingHandCursor);
    remove->setStyleSheet("QPushButton:hover{ background-color: red;}");
    remove->setToolTip("Sélectionner une matrice et supprimer");
    QHBoxLayout* viewFooterLayout = new QHBoxLayout;
    viewFooterLayout->addWidget(remove);

    QVBoxLayout* matrixViewLayout = new QVBoxLayout;
    matrixViewLayout->addWidget(matrixView);
    matrixViewLayout->addLayout(viewFooterLayout);

    matrixViewLayout->setContentsMargins(0,38,0,0);

    choice = new QTabWidget;
    choice->addTab(scrollArea, "Visualiser");
    choice->addTab(addMatrix, "Ajouter");
    choice->addTab(editMatrix, "Modifier");
    choice->setStyleSheet(
        "QTabBar::tab { background:"
        "qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 white, stop: 1 darkGrey);"
        "padding: 10px; border-radius: 6px; border:1px solid darkGrey ;} "
        "QTabBar::tab:selected { background: "
        "qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 lightBlue, stop: 1 blue); color:white } "
        "QTabWidget::tab-bar { alignment : center;}"
        "QTabWidget::pane{border-radius:6px; border: 1px solid silver;"
        "background-color:white;}");

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addLayout(matrixViewLayout);
    mainLayout->addWidget(choice);
    mainLayout->setContentsMargins(30,10,30,30);

    QWidget* mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);

    QPalette p;
    p = palette();
    QPixmap background(":/img/background.png");
    p.setBrush(QPalette::Window, QBrush(QPixmap(":/img/background.png")));
    setPalette(p);

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
        Error::showError("Suppression impossible !", "Veuillez sélectionner une Matrice");
        return;
    }

    matrixView->removeRow(matrixView->currentIndex().row());
    assert(lib->exist(selectedName.toStdString()));
    lib->erase(selectedName.toStdString());
    editMatrix->updateSelectedMatrix();
    showMatrixWidget->clear();
    emit libraryChanged();
}


void LibraryWindow:: update()
{
    matrixView->refresh();
    editMatrix->updateSelectedMatrix();
}



LibraryWindow:: ~LibraryWindow()
{   
}



