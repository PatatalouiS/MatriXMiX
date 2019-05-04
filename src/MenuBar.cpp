
#include "MenuBar.h"
#include <QApplication>

MenuBar:: MenuBar(QWidget* parent) : QMenuBar(parent)
{
    menuFile = addMenu("Fichier");
    menuFile->setCursor(Qt::PointingHandCursor);

    QPixmap im(":/img/save.png");
    im = im.scaled(50, 50);

    actionSave = new QAction("Sauver.." , this);
    actionSave->setIcon(im);
    menuFile -> addAction(actionSave);

    QPixmap im4(":/img/create.png");
    im4 = im4.scaled(50, 50);

    menuFile -> addSeparator();

    actionLoad = new QAction("Ouvrir..", this);
    actionLoad->setIcon(im4);
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

    QPixmap im3(":/img/quitter.jpg");
    im3 = im3.scaled(200, 200);

    actionQuit = new QAction("MatriXMiX", this);
    actionQuit->setIcon(im3);
    menuQuit->addAction(actionQuit);

    connect(actionHelpMatrix, &QAction::triggered , this, &MenuBar::showPageMatrix);
    connect(actionHelpQt, &QAction::triggered , this, &MenuBar::showPageQt);
    connect(actionQuit, &QAction::triggered, this , &QApplication::quit);
    connect(libraryMatrix, &QAction::triggered, this, &MenuBar::openLibraryWindow);
    connect(actionSave, &QAction::triggered, this, &MenuBar::openSaveTool);
    connect(actionLoad, &QAction::triggered, this, &MenuBar::openLoadTool);
}


void MenuBar::showPageMatrix()
{
    HelpWindow* wind = new HelpWindow(this);
    wind->setAttribute(Qt::WA_DeleteOnClose);
    wind->exec();
}

void MenuBar::showPageQt()
{
    HelpWindowQt* wind = new HelpWindowQt(this);
    wind->setAttribute(Qt::WA_DeleteOnClose);
    wind->exec();
}


MenuBar::~MenuBar()
{
}



