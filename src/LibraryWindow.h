
#ifndef _LIBRARY_WINDOW_H
#define _LIBRARY_WINDOW_H

#include <QWidget>
#include <QList>
#include <QTableView>
#include <QStandardItemModel>
#include <QLabel>
#include "MatrixLibrary.h"



class LibraryWindow : public QWidget
{
    Q_OBJECT
    
    public:
    
    
        LibraryWindow (QWidget* main);
        ~LibraryWindow ();
        void add();
    
    private:
    
        void closeEvent (QCloseEvent* event);
		void compute_img(const Matrix* mat, QLabel* img);
        void compute_add();
    
        QTableView* matrixView;
        QStandardItemModel* model;
        MatrixLibrary lib;
		QLabel* imgSelected;
	
	
	private slots:
		void compute_selection();
    
        
    
    signals:
		void update();
        void close();
};



#endif
