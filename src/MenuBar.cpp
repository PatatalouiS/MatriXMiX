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
    actionHelp = new QAction("Page d'aide",this);
    menuHelp->addAction(actionHelp);

    menuQuit = addMenu("Quitter");
    menuQuit->setCursor(Qt::PointingHandCursor);

    connect(libraryMatrix, &QAction::triggered, [this]() -> void { emit openLibrary();});
    connect(actionHelp, &QAction::triggered , this, &MenuBar::showPage);

}

void MenuBar::showPage()
{
    HelpWindow* wind = new HelpWindow(this);
    hide();
    //wind->show();
}

MenuBar::~MenuBar()
{
}



