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

/**
@class MenuBar The class MenuBar generate the menu of the application
MatriXMiX which give the access to the library, help pages, to safeguard
and loading a file.
*/
class MenuBar : public QMenuBar
{
    Q_OBJECT

    private:
        QMatrixLibrary lib;
        QMenu *menuFile;
        QAction *actionSave;
        QAction *actionLoad;
        QMenu *menuMatrix;
        QAction *libraryMatrix;
        QAction *matrixmixWindow;
        QMenu *menuHelp;
        QAction* actionHelpMatrix;
        QAction* actionHelpQt;
        QMenu *menuQuit;
        QAction *actionQuit;

    public:
        /**
         * @brief Default constructor
         * @param [in] parent (\e pointer of QWidget)
         */
        MenuBar(QWidget* parent = nullptr);
        /**
         * @brief Default destructor
         */
        ~MenuBar ();

    signals:
        /**
         * @brief Open the library window
         */
        void openLibraryWindow();

        void openMatrixmixWindow();
        /**
         * @brief Open the save tool
         */
        void openSaveTool();
        /**
         * @brief Open the save tool
         */
        void openLoadTool();

    private slots:

        /**
         * @brief Open the help page of MatriXMiX
         */
        void showPageMatrix();
        /**
         * @brief Open the help page of Qt
         */
        void showPageQt();
};

#endif
