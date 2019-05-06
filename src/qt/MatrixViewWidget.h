
#ifndef MATRIXVIEWWIDGET_H
#define MATRIXVIEWWIDGET_H

#include <QTableView>
#include <QStandardItemModel>
#include "../maths/MatrixLibrary.h"
#include "ShowMatrixWidget.h"



class MatrixViewWidget : public QTableView
{
    Q_OBJECT

    using MatrixPair = QPair<const QString&, const Matrix&>;

    public:

        MatrixViewWidget(const MatrixLibrary* lib, QWidget* parent = nullptr);
        ~MatrixViewWidget ();

        const QString nameOfSelectedMatrix() const;

    public slots:

        void refresh(const std::function<bool(Matrix*)> filter =
            [](const Matrix*) -> bool {return true;});

        void addNewRow(const MatrixPair& m);
        void editRow(const MatrixPair& m);
        void removeRow(const int id);

    private:

        const MatrixLibrary* lib;
        QStandardItemModel* matrixModel;
        static ShowMatrixWidget* matrixPreview;

    private slots:

        void showMatrixPreview() const;
};


#endif
