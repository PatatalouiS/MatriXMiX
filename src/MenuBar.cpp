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

    actionSave = new QAction("Sauvegarder" , this);
    menuFile -> addAction(actionSave);

    menuFile -> addSeparator();

    actionLoad = new QAction("Créer", this);
    menuFile -> addAction(actionLoad);

    menuMatrix = addMenu("Matrice");

    libraryMatrix = new QAction("Librarie" , this);
    menuMatrix -> addAction(libraryMatrix);

    connect(libraryMatrix, &QAction::triggered, this, &MenuBar::show_library);
    libraryMatrix-> setToolTip("lala");

    /*menuMatrix -> addSeparator();

    showMatrix = new QAction("Visualiser" , this);
    menuMatrix -> addAction(showMatrix);
    connect(showMatrix, &QAction::triggered, this, &MainWindow::show_library); */

    menuHelp = addMenu("Aide");
    menuQuit = addMenu("Quitter");
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

/*void MenuBar::show_add_matrix()
{
    AddMatrixWidget* add = new AddMatrixWidget(&lib,this);
    LibraryWindow* libWindow = new LibraryWindow(add , &lib);
    //libWindow->setAttribute(Qt::WA_DeleteOnClose);
    libWindow->show();
    hide();
} */
