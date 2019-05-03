
#ifndef SET_MATRIX_WIDGET_H
#define SET_MATRIX_WIDGET_H

#include <QLineEdit>
#include <QGridLayout>
#include <QSpinBox>
#include <QPushButton>
#include "MatrixLibrary.h"



class SetMatrixWidget : public QWidget
{
    Q_OBJECT

    using MatrixPair = QPair<const QString, const Matrix&>;

    public:

        enum type
        {
            ADD,
            EDIT,
        };

        SetMatrixWidget(const enum type& t, MatrixLibrary* library, QWidget* parent = nullptr);
        ~SetMatrixWidget();

    private:

        MatrixLibrary* library;
        QLineEdit* nameMatrix;
        QSpinBox* nbRowsSelector;
        QSpinBox* nbColsSelector;
        QList<QLineEdit*> lineEditsTab;
        QGridLayout* lineEditsLayout;
        QPushButton* compute;

        unsigned int lrows;
        unsigned int lcols;
        QPair<QString, Matrix*> selectedMatrix;
        type type;

        bool controlKeyboardInput () const;
        void constructType(const enum type& t);

    private slots:

        void computeMatrix();
        void updateLineEdits();

    public slots:

        void chargeMatrix(const QString& matrixName);
        void updateSelectedMatrix();

    signals:

        void newMatrixAdded(const MatrixPair m) const;
        void matrixEdited(const MatrixPair m) const;
};

#endif
