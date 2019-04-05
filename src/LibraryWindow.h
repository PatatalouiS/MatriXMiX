
#ifndef _LIBRARY_WINDOW_H_
#define _LIBRARY_WINDOW_H_

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
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
    ShowMatrixWidget* showMatrixWidget;

    //fonctions

    void closeEvent (QCloseEvent* event);


public: //fonctions
    
    LibraryWindow (QWidget* main);
    ~LibraryWindow ();

private slots:

	void compute_selection();

public slots:

     void updateView (QList<QStandardItem*> newLine);
        
    
signals:

     void close();
};



#endif
