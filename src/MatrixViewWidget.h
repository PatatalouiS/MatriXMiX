
#ifndef MATRIXVIEWWIDGET_H
#define MATRIXVIEWWIDGET_H

#include <QTableView>
#include <QStandardItemModel>
#include <QDialog>
#include <QLabel>
#include "MatrixLibrary.h"
#include "ShowMatrixWidget.h"

using MatrixPair = QPair<const QString&, const Matrix&>;

class MatrixViewWidget : public QTableView
{

    Q_OBJECT

    public:

        MatrixViewWidget(const MatrixLibrary* lib, QWidget* parent = nullptr);
        ~MatrixViewWidget ();

        const QString nameOfSelectedMatrix() const;

    private:

        const MatrixLibrary* lib;
        QStandardItemModel* matrixModel;
        static ShowMatrixWidget* matrixPreview;

    private slots:

        void showMatrixPreview() const;

    public slots:

        void refresh(const std::function<bool(Matrix*)> filter =
            [](const Matrix*) -> bool {return true;});

        void addNewRow(const MatrixPair& m);
        void editRow(const MatrixPair& m);
        void removeRow(const int id);
};

#endif
