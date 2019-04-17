#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QEvent>
#include <QToolTip>
#include "LibraryWindow.h"

class MenuBar : public QMenuBar
{
    Q_OBJECT

    private:
        MatrixLibrary lib;
        QMenu *menuFile;
        QAction *actionSave;
        QAction *actionLoad;
        QMenu *menuMatrix;
        QAction *libraryMatrix;
        QAction *showMatrix;
        QMenu *menuHelp;
        QMenu *menuQuit;


    public:
        MenuBar(QWidget* parent);
        ~MenuBar ();

    public slots :
        void show_library ();
        //void show_add_matrix();

};

#endif // MENUBAR_H
