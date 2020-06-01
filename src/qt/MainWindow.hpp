#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "LibraryWindow.h"
#include "MatriXMiXWindow.h"
#include "MenuBar.h"

class MainWindow : public QMainWindow
{
    public:

        MainWindow();
        MenuBar* menuBar;
        QMatrixLibrary library;

        LibraryWindow* libraryWindow;
        MatriXMiXWindow* matrixmixWindow;

        /**
        * @brief Show the load and save tool
        * @param [in] type (\e enum \e QFileDialog::AcceptMode)
        */
        void showFileTool (enum QFileDialog::AcceptMode type);

        /**
        * @brief Differentiate which tool is selected: save or load
        * @param [in] fileTool ( \e QFileDialog)
        * @param [in] type (\e enum \e QFileDialog::AcceptMode)
        */
        void computeLoadOrRead(QFileDialog* fileTool, enum QFileDialog::AcceptMode type);

    signals :

        /**
        * @brief libraryChanged this signal is emitted when a modification on the library happen
        */
        void libraryChanged();
};

#endif // MAINWINDOW_HPP
