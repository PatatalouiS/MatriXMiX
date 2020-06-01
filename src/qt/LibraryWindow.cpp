
#include <QScrollBar>
#include <QScrollArea>
#include "LibraryWindow.h"
#include "Error.h"


using namespace std;


LibraryWindow:: LibraryWindow (QWidget* main, QMatrixLibrary* library) : QWidget(main)
{
    lib = library;
    matrixView = new MatrixViewWidget(lib, this);
    addMatrix = new SetMatrixWidget(SetMatrixWidget::ADD, lib, this);
    editMatrix = new SetMatrixWidget(SetMatrixWidget::EDIT, lib, this);
    showMatrixWidget = new ShowMatrixWidget(this);

    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(showMatrixWidget);
    scrollArea->setStyleSheet("border : none; background : transparent;");
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

    remove = new QPushButton("  Supprimer", this);
    QPixmap imTrash(":/img/trash.png");
    remove->setIcon(imTrash);
    remove->setIconSize(QSize(25, 25));
    remove->setCursor(Qt::PointingHandCursor);
    remove->setToolTip("Sélectionner une matrice et supprimer");

    remove->setStyleSheet("QPushButton {"
                                     "height: 50px;"
                                     "width : 100px;"
                                     "border-style: solid;"
                                     "border-radius : 3px;"
                                     "background-color:rgb(210, 210, 210);"
                                 "}"
                                 "QPushButton:pressed{ background-color : grey; }"
                                "QPushButton:hover{background-color:rgb(150,0,0); }");



    QHBoxLayout* viewFooterLayout = new QHBoxLayout;
    viewFooterLayout->addWidget(remove);

    QPushButton* showMatrixmixButton = new QPushButton("Menu principal", this);
    QPixmap imButton(":/img/back.png");
    imButton = imButton.scaled(30, 30);
    showMatrixmixButton->setIcon(QIcon(imButton));
    showMatrixmixButton->setIconSize(QSize(25, 25));
    showMatrixmixButton->setCursor(Qt::PointingHandCursor);

    showMatrixmixButton->setStyleSheet("QPushButton {"
                                     "height: 50px;"
                                     "width : 100px;"
                                     "border-style: solid;"
                                     "border-radius : 3px;"
                                     "background-color:rgb(210, 210, 210);"
                                 "}"
                                 "QPushButton:pressed{ background-color : grey; }");
    showMatrixmixButton->setToolTip("Retour au menu principal...");


    QVBoxLayout* leftLayout = new QVBoxLayout;
    leftLayout->setContentsMargins(0, 5, 0, 0);
    leftLayout->addWidget(showMatrixmixButton);
    leftLayout->addWidget(matrixView);
    leftLayout->addLayout(viewFooterLayout);

    choice = new QTabWidget(this);
    choice->addTab(scrollArea, "Visualiser");
    choice->addTab(addMatrix, "Ajouter");
    choice->addTab(editMatrix, "Modifier");
    choice->setStyleSheet("QTabWidget::pane {"
                            "background-color : white;"
                            "border : 1px;"
                            "border-radius: 3px;"
                            "top : -10px;"
                          "}"

                           );

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(choice);
    mainLayout->setContentsMargins(18,18,18,18);

    QWidget* mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);

    QPalette p;
    p = palette();
    QPixmap background(":/img/background.png");
    p.setBrush(QPalette::Window, QBrush(QPixmap(":/img/background.png")));
    setPalette(p);

    setLayout(mainLayout);

    // select the matrix to draw in the view tab
    connect(matrixView, &MatrixViewWidget::clicked,
            this, &LibraryWindow::computeViewSelection);

    // When a matrix is addedd
    connect(addMatrix, &SetMatrixWidget::newMatrixAdded,
            matrixView, &MatrixViewWidget::addNewRow);

    connect(addMatrix, &SetMatrixWidget::newMatrixAdded,
            this,&LibraryWindow::update);

    connect(addMatrix, &SetMatrixWidget::newMatrixAdded,
            this,&LibraryWindow::libraryChanged);


    // When a matrix is edited
    connect(editMatrix, &SetMatrixWidget::matrixEdited,
            matrixView, &MatrixViewWidget::editRow);

    connect(editMatrix, &SetMatrixWidget::matrixEdited,
            this, &LibraryWindow::update);

    connect(editMatrix, &SetMatrixWidget::matrixEdited,
            [this]() -> void
            {
                computeViewSelection();
                choice->setCurrentIndex(0);
            });

    connect(editMatrix, &SetMatrixWidget::matrixEdited,
            this, &LibraryWindow::libraryChanged);

    // When a matrix is removed
    connect(remove, &QPushButton::clicked,
            this, &LibraryWindow::removeSelectedMatrix);

    connect(showMatrixmixButton, &QPushButton::clicked, [this]() -> void {
                emit showMatrixmixWindow();
            });
}


void LibraryWindow:: computeViewSelection ()
{
    QString selectedName = matrixView->nameOfSelectedMatrix();
    assert(lib->exist(selectedName));
    const Matrix* selectedMatrix = lib->find_matrix(selectedName);
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
    assert(lib->exist(selectedName));
    lib->erase(selectedName);
    editMatrix->updateSelectedMatrix();
    showMatrixWidget->clear();
    update();
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



