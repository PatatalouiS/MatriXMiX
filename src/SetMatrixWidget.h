
#ifndef SET_MATRIX_WIDGET_H
#define SET_MATRIX_WIDGET_H

#include <QWidget>
#include <QList>
#include <QLineEdit>
#include <QGridLayout>
#include <QSpinBox>
#include <QStandardItem>
#include <QPushButton>
#include "MatrixLibrary.h"



class SetMatrixWidget : public QWidget
{
    Q_OBJECT

    using MatrixPair = QPair<const QString&, const Matrix&>;

    private:

        MatrixLibrary* library;
        QLineEdit* nameMatrix;
        QSpinBox* nbRowsSelector;
        QSpinBox* nbColsSelector;
        QList<QLineEdit*> lineEditsTab;
        QGridLayout* lineEditsLayout;
        QPushButton* ajouter;
        unsigned int lrows;
        unsigned int lcols;

        bool controlKeyboardInput () const;
        void constructType();

    private slots:

        void computeAdd();
        void updateLineEdits();

    public:

        SetMatrixWidget( MatrixLibrary* library, QWidget* parent = nullptr);
        ~SetMatrixWidget();

    public slots:

        void computeEditing(const QString& name);

    signals:

        void newMatrixAdded(const MatrixPair& m) const;
};

#endif
