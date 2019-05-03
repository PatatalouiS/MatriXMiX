#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QEvent>
#include <QToolTip>
#include "LibraryWindow.h"
#include "HelpWindow.h"
#include "HelpWindowQt.h"

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
        QAction* actionHelpMatrix;
        QAction* actionHelpQt;
        QMenu *menuQuit;
        QAction *actionQuit;

    public:

        MenuBar(QWidget* parent = nullptr);
        ~MenuBar ();

    signals:

        void openLibraryWindow();
        void openSaveTool();
        void openLoadTool();

    private slots:

        void showPageMatrix();
        void showPageQt();
};

#endif
