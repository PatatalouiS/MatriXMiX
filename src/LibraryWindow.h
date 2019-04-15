
#ifndef LIBRARY_WINDOW_H
#define LIBRARY_WINDOW_H

#include <QDialog>
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>
#include "AddMatrixWidget.h"
#include "ShowMatrixWidget.h"



class LibraryWindow : public QDialog
{
    Q_OBJECT

private:

    //members

    QTableView* matrixView;
    QStandardItemModel* matrixModel;
    MatrixLibrary* lib;
    AddMatrixWidget* addMatrixWidget;
    ShowMatrixWidget* showMatrixWidget;
    QPushButton* edit;
    QPushButton* remove;

    //fonctions

    void closeEvent (QCloseEvent* event);


public: //fonctions
    
    LibraryWindow (QWidget* main, MatrixLibrary* lib);
    ~LibraryWindow ();

private slots:

	void compute_selection();

public slots:

     void updateView (QList<QStandardItem*> newLine);
        
signals:

     void close();
};



#endif
