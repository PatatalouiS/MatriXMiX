#include "MenuBar.h"

MenuBar:: MenuBar(QWidget* parent) : QMenuBar(parent)
{

    /*QString  menuStyle(
              "QMenuBar{"
              "background-color: lightBlue;"
              "}"
           ); */

    //this->setStyleSheet(menuStyle);

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
    connect(libraryMatrix, &QAction::triggered, this, &MenuBar::show_library);

    menuHelp = addMenu("Aide");
    menuHelp->setCursor(Qt::PointingHandCursor);
    menuQuit = addMenu("Quitter");
    menuQuit->setCursor(Qt::PointingHandCursor);
}

MenuBar::~MenuBar()
{
}

void MenuBar:: show_library()
{
    LibraryWindow* libWindow = new LibraryWindow(this, &lib);
    libWindow->setAttribute(Qt::WA_DeleteOnClose);
    libWindow->show();
    hide();
}

