
#ifndef ADDMATRIXWIDGET_H
#define ADDMATRIXWIDGET_H

#include <QWidget>
#include <QList>
#include <QLineEdit>
#include <QGridLayout>
#include <QSpinBox>
#include <QStandardItem>
#include "MatrixLibrary.h"

class AddMatrixWidget : public QWidget
{
    Q_OBJECT

    private:

        MatrixLibrary* library;
        QLineEdit* nameMatrix;
        QSpinBox* nbRowsSelector;
        QSpinBox* nbColsSelector;
        QList<QLineEdit*> lineEditsTab;
        QGridLayout* lineEditsLayout;
        unsigned int lrows;
        unsigned int lcols;

        bool controlKeyboardInput () const;

    private slots:

        void compute_add();
        void update_EditSize();

    public:

        AddMatrixWidget(MatrixLibrary* library, QWidget* parent = nullptr);
        ~AddMatrixWidget();

    signals:

        void newMatrixAdded(const QString& name, const Matrix& m) const;
};

#endif
