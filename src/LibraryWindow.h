
#ifndef LIBRARY_WINDOW_H
#define LIBRARY_WINDOW_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>
#include "AddMatrixWidget.h"
#include "MatrixLibrary.h"
#include "ShowMatrixWidget.h"



class LibraryWindow : public QWidget
{
    Q_OBJECT

private:

    //members

    QTableView* matrixView;
    QStandardItemModel* matrixModel;
    MatrixLibrary lib;
    AddMatrixWidget* addMatrixWidget;
    AddMatrixWidget* updateMatrixWidget;
    ShowMatrixWidget* showMatrixWidget;
    QPushButton* edit;
    QPushButton* remove;

    //fonctions@&

    void closeEvent (QCloseEvent* event);


public: //fonctions
    
    LibraryWindow (QWidget* main);
    ~LibraryWindow ();

private slots:

	void compute_selection();

public slots:

     void updateView (QList<QStandardItem*> newLine);
     //void editMatrix ();
        
    
signals:

     void close();
};



#endif
