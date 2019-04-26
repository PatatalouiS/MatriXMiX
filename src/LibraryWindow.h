
#ifndef LIBRARY_WINDOW_H
#define LIBRARY_WINDOW_H

#include <QDialog>
#include <QPushButton>
#include "AddMatrixWidget.h"
#include "MatrixViewWidget.h"
#include "ShowMatrixWidget.h"

class MainWindow;


class LibraryWindow : public QDialog
{
    Q_OBJECT

private:

    //members


    MatrixLibrary* lib;
    MatrixViewWidget* matrixView;
    AddMatrixWidget* addMatrixWidget;
    ShowMatrixWidget* showMatrixWidget;
    QPushButton* edit;
    QPushButton* remove;


public: //fonctions
    
    LibraryWindow (MainWindow* main, MatrixLibrary* lib);
    ~LibraryWindow ();

private slots:

	void compute_selection();
        
signals:

     void close();
};



#endif
