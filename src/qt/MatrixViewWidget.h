
#ifndef MATRIXVIEWWIDGET_H
#define MATRIXVIEWWIDGET_H

#include <QTableView>
#include <QStandardItemModel>
#include "QMatrixLibrary.hpp"
#include "ShowMatrixWidget.h"


/**
 * @brief The MatrixViewWidget class is the widget for represent all the matrices in a MatrixLibrary.
 */


class MatrixViewWidget : public QTableView
{
    Q_OBJECT

    using MatrixPair = QPair<const QString&, const Matrix&>;

    public:

         /**
         * @brief MatrixViewWidget
         * @param [in] lib a pointer to a MatrixLibrray
         * @param [in,out] parent a pointer to a parent QWidget, to ensure good deletion
         */

        MatrixViewWidget(const QMatrixLibrary* lib, QWidget* parent = nullptr);

        /**
         * @brief the default Constructor
         */

        ~MatrixViewWidget ();

        /**
         * @brief nameOfSelectedMatrix return the current selection of the tab of matrices
         * @return the name of the selected Matrix in QString form
         */

        const QString nameOfSelectedMatrix() const;

    public slots:

        /**
        * @brief refresh refresh the view of matrices if a matrix is added, suspressed, or edited
        * @param [in] filter a comparison lambda function
        */

        void refresh(std::function<bool(Matrix*)> filter =
            [](const Matrix*) -> bool {return true;});

        /**
         * @brief addNewRow add a new matrix to the view
         * @param [in] m the Matrix to add
         */

        void addNewRow(const MatrixPair& m);

         /**
         * @brief editRow edit a matrix in the view
         * @param [in] m the edited Matrix
         */

        void editRow(const MatrixPair& m);

        /**
         * @brief removeRow remove a matrix in the view
         * @param [in] id the index of the matrix to remove
         */

        void removeRow(const int id);

    private:

        const QMatrixLibrary* lib;
        QStandardItemModel* matrixModel;
        static ShowMatrixWidget* matrixPreview;

    private slots:

        /**
         * @brief showMatrixPreview show a preview of the selected Matrix to the user screen
         */

        void showMatrixPreview() const;
};


#endif
