
#ifndef LIBRARY_WINDOW_H
#define LIBRARY_WINDOW_H

#include <QDialog>
#include <QPushButton>
#include "MatrixViewWidget.h"
#include "ShowMatrixWidget.h"
#include "SetMatrixWidget.h"


using MatrixViewItem = QPair<const int, const QString>;

class LibraryWindow : public QWidget
{
    Q_OBJECT

    private:

        //members

        MatrixLibrary* lib;
        QTabWidget* choice;
        MatrixViewWidget* matrixView;
        SetMatrixWidget* addMatrix;
        SetMatrixWidget* editMatrix;
        ShowMatrixWidget* showMatrixWidget;
        QPushButton* remove;

    public: //fonctions

        LibraryWindow (QWidget* main, MatrixLibrary* lib);
        ~LibraryWindow ();

    public slots:

         void update();

    private slots:

        void removeSelectedMatrix();
        void computeViewSelection();

    signals:

        void libraryChanged() const;
};

#endif
