
#ifndef LIBRARY_WINDOW_H
#define LIBRARY_WINDOW_H

#include "MatrixViewWidget.h"
#include "ShowMatrixWidget.h"
#include "SetMatrixWidget.h"
#include "QMatrixLibrary.hpp"

/**
@class LibraryWindow none none  This class show to user a Window in wich he can Add Matrices, Remove Matrices, Or Edit Matrices.
*/


class LibraryWindow : public QWidget
{
    Q_OBJECT

    private:

        QMatrixLibrary* lib;
        QTabWidget* choice;
        MatrixViewWidget* matrixView;
        SetMatrixWidget* addMatrix;
        SetMatrixWidget* editMatrix;
        ShowMatrixWidget* showMatrixWidget;
        QPushButton* remove;

    private slots:

        /**
         * @brief removeSelectedMatrix remove the selected Matrix in the LibraryWindow::matrixView member. \n
         *      show to user an error message if no Matrix is selected.
         */

        void removeSelectedMatrix();

        /**
         * @brief computeViewSelection sets the values of the selected Matrix by user in the Editing Matrix Widget  \n
         *      Show the selected Matrix in the View Tab of the LibraryWindow too.
         */

        void computeViewSelection();

    public:

        /**
         * @brief LibraryWindow
         * @param [in,out] parent a pointer on a potential parent QWidget, mainly for ensure good deletion.
         * @param [in,out] lib a pointer on a QMatrixLibrary, for read on the QMatrixLibrary and write too.
         */

        LibraryWindow (QWidget* parent, QMatrixLibrary* lib);

        /**
         * @brief destructor of the class
         */

        ~LibraryWindow ();

    public slots:

        /**
          * @brief update update the LibraryWindow, (the views, the add or edit tab).\n
          *  particulary called if the lib member has changed.
          */

         void update();

    signals:

         /**
         * @brief libraryChanged this signal is emitted when a modification on the library happen
         */

        void libraryChanged() const;

        void showMatrixmixWindow();
};

#endif
