
#ifndef LIBRARY_WINDOW_H
#define LIBRARY_WINDOW_H

#include <QDialog>
#include <QPushButton>
#include "AddMatrixWidget.h"
#include "MatrixViewWidget.h"
#include "ShowMatrixWidget.h"


using MatrixViewItem = QPair<const int, const QString>;

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

        LibraryWindow (QWidget* main, MatrixLibrary* lib);
        ~LibraryWindow ();

    private slots:

        void removeSelectedMatrix();
        void showSelectedMatrix();

    signals:

        void libraryChanged() const;
};



#endif
