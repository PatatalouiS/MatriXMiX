#include "MenuBar.h"

MenuBar:: MenuBar(QWidget* parent) : QMenuBar(parent)
{
    menuFile = addMenu("Fichier");
    menuFile->setCursor(Qt::PointingHandCursor);

    actionSave = new QAction("Sauvegarder" , this);
    menuFile -> addAction(actionSave);

    menuFile -> addSeparator();

    actionLoad = new QAction("Créer", this);
    menuFile -> addAction(actionLoad);

    menuMatrix = addMenu("Matrice");
    menuMatrix->setCursor(Qt::PointingHandCursor);

    libraryMatrix = new QAction("Librarie" , this);
    libraryMatrix-> setToolTip("Ici vous pouvez creer et visualiser les matrices");
    menuMatrix -> addAction(libraryMatrix);

    menuHelp = addMenu("Aide");
    menuHelp->setCursor(Qt::PointingHandCursor);
    actionHelpMatrix = new QAction("About MatriXMix",this);
    menuHelp->addAction(actionHelpMatrix);

    menuHelp->addSeparator();

    actionHelpQt = new QAction("About QT",this);
    menuHelp->addAction(actionHelpQt);

    menuQuit = addMenu("Quitter");
    menuQuit->setCursor(Qt::PointingHandCursor);


    connect(libraryMatrix, &QAction::triggered, [this]() -> void { emit openLibrary();});
    connect(actionHelpMatrix, &QAction::triggered , this, &MenuBar::showPageMatrix);
    connect(actionHelpQt, &QAction::triggered , this, &MenuBar::showPageQt);


}

void MenuBar::showPageMatrix()
{
    HelpWindow* wind = new HelpWindow(this);
    wind->hide();
}

void MenuBar::showPageQt()
{
    HelpWindowQt* wind = new HelpWindowQt(this);
    wind->hide();
}

MenuBar::~MenuBar()
{
}



