
#ifndef LIBRARY_WINDOW_H
#define LIBRARY_WINDOW_H

#include <QDialog>
#include <QPushButton>
#include "SetMatrixWidget.h"
#include "MatrixViewWidget.h"
#include "ShowMatrixWidget.h"


using MatrixViewItem = QPair<const int, const QString>;

class LibraryWindow : public QDialog
{
    Q_OBJECT

    private:

        //members

        MatrixLibrary* lib;
        QTabWidget* choice;
        MatrixViewWidget* matrixView;
        SetMatrixWidget* addMatrixWidget;
        SetMatrixWidget* editMatrixWidget;
        ShowMatrixWidget* showMatrixWidget;
        QPushButton* edit;
        QPushButton* remove;

    public: //fonctions

        LibraryWindow (QWidget* main, MatrixLibrary* lib);
        ~LibraryWindow ();

    private slots:

        void removeSelectedMatrix();
        void showSelectedMatrix();
        void computeEditingQuery();

    signals:

        void libraryChanged() const;
};



#endif
