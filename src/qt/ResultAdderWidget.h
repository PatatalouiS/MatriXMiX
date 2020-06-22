#ifndef RESULTADDERWIDGET_H
#define RESULTADDERWIDGET_H

#include "../maths/Matrix.h"
#include "QMatrixLibrary.hpp"

#include <QWidget>
#include <QVariant>
#include <QLineEdit>
#include <QPushButton>

/**
 * @brief The ResultAdderWidget class This class wrap a little widget wich allows the
 *  User to Add the result of a computation to a QMatrixLibrary instance.
 */

class ResultAdderWidget : public QWidget
{
    Q_OBJECT

    public:

        /**
         * @brief ResultAdderWidget the constructor
         * @param lib teh QMAtrixLibrary to use for add the result
         * @param parent the parent QWidget
         */
        ResultAdderWidget(QMatrixLibrary* lib,
                          QWidget* parent = nullptr);

        /**
         * @brief addResult add the current result to the MatrixLibrary
         */
        void addResult();

    public slots:

        /**
         * @brief showAndLoadResult load a new computation to the scope of this Widget
         *  end show this QWidget to user.
         * @param result the emitted result ( by an AbstractOperationWidget )
         */
        void showAndLoadResult(const QVariant& result);

    private :

        Matrix result;
        QMatrixLibrary* library;
        QLineEdit* adderName;
        QPushButton* adderBtn;

    signals:

        /**
         * @brief newMatrixAdded this signal is emitted when a new Matrix is added
         *  in the QMatrixLibrary
         */
        void newMatrixAdded();
};

#endif // RESULTADDERWIDGET_H
