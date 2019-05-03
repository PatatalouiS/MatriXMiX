
#include "MenuBar.h"
#include <QApplication>

MenuBar:: MenuBar(QWidget* parent) : QMenuBar(parent)
{
    menuFile = addMenu("Fichier");
    menuFile->setCursor(Qt::PointingHandCursor);

<<<<<<< HEAD
    actionSave = new QAction("Sauver.." , this);
=======
    QPixmap im(":/img/save.png");
    im = im.scaled(50, 50);

    actionSave = new QAction("Sauvegarder" , this);
    actionSave->setIcon(im);
>>>>>>> origin/modif_graph
    menuFile -> addAction(actionSave);

    QPixmap im4(":/img/create.png");
    im4 = im4.scaled(50, 50);

    menuFile -> addSeparator();

<<<<<<< HEAD
    actionLoad = new QAction("Ouvrir..", this);
=======
    actionLoad = new QAction("Créer", this);
    actionLoad->setIcon(im4);
>>>>>>> origin/modif_graph
    menuFile -> addAction(actionLoad);

    menuMatrix = addMenu("Matrice");
    QPixmap im1(":/img/library.png");
    im1 = im1.scaled(50, 50);

    menuMatrix->setCursor(Qt::PointingHandCursor);

    libraryMatrix = new QAction("Librarie" , this);
    libraryMatrix->setIcon(im1);
    menuMatrix -> addAction(libraryMatrix);

    menuHelp = addMenu("Aide");
    menuHelp->setCursor(Qt::PointingHandCursor);
    actionHelpMatrix = new QAction("About MatriXMix",this);
    menuHelp->addAction(actionHelpMatrix);

    menuHelp->addSeparator();

    QPixmap im2(":/img/qt.png");
    im2 = im2.scaled(250, 200);

    actionHelpQt = new QAction("About QT",this);
    actionHelpQt->setIcon(im2);
    menuHelp->addAction(actionHelpQt);

    menuQuit = addMenu("Quitter");
    menuQuit->setCursor(Qt::PointingHandCursor);

<<<<<<< HEAD
    connect(libraryMatrix, &QAction::triggered, this, &MenuBar::openLibraryWindow);
    connect(actionSave, &QAction::triggered, this, &MenuBar::openSaveTool);
    connect(actionLoad, &QAction::triggered, this, &MenuBar::openLoadTool);
    connect(actionHelp, &QAction::triggered , this, &MenuBar::showPage);
=======
    QPixmap im3(":/img/quitter.jpg");
    im3 = im3.scaled(200, 200);

    actionQuit = new QAction("MatriXMiX");
    actionQuit->setIcon(im3);
    menuQuit->addAction(actionQuit);

    connect(libraryMatrix, &QAction::triggered, [this]() -> void { emit openLibrary();});
    connect(actionHelpMatrix, &QAction::triggered , this, &MenuBar::showPageMatrix);
    connect(actionHelpQt, &QAction::triggered , this, &MenuBar::showPageQt);
    connect(actionQuit, &QAction::triggered, this , &QApplication::quit);

>>>>>>> origin/modif_graph

}

void MenuBar::showPageMatrix()
{
    HelpWindow* wind = new HelpWindow(this);
<<<<<<< HEAD
    (void) wind;
    //hide();
    //wind->show();
=======
    wind->hide();
}

void MenuBar::showPageQt()
{
    HelpWindowQt* wind = new HelpWindowQt(this);
    wind->hide();
>>>>>>> origin/modif_graph
}

MenuBar::~MenuBar()
{
}



