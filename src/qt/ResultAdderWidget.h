#ifndef RESULTADDERWIDGET_H
#define RESULTADDERWIDGET_H

#include "../maths/Matrix.h"
#include "QMatrixLibrary.hpp"

#include <QWidget>
#include <QVariant>
#include <QLineEdit>
#include <QPushButton>

class ResultAdderWidget : public QWidget
{
    Q_OBJECT

    public:

        ResultAdderWidget(QMatrixLibrary* lib,
                          QWidget* parent = nullptr);

        void addResult();

    public slots:

        void showAndLoadResult(const QVariant& result);

    private :

        Matrix result;
        QMatrixLibrary* library;
        QLineEdit* adderName;
        QPushButton* adderBtn;

    signals:

        void newMatrixAdded();
};

#endif // RESULTADDERWIDGET_H
