
#ifndef SET_MATRIX_WIDGET_H
#define SET_MATRIX_WIDGET_H

#include <QLineEdit>
#include <QGridLayout>
#include <QSpinBox>
#include <QPushButton>
#include <mpParser.h>
#include "ExprLineEdit.hpp"
#include "QMatrixLibrary.hpp"



/**
@class SetMatrixWidget  none none This class shows to user the tools for Add a Matrix to a Library, or to Edit a Matrix too.
*/


class SetMatrixWidget : public QWidget
{
    Q_OBJECT

    public:

        enum type
        {
            ADD,
            EDIT,
        };

        /**
         * @brief SetMatrixWidget The Unique constructor of the class
         * @param [in] type the type of the SetMatrixWidget ( for Add a Matrix or Edit a Matrix ) . see SetMatrixWidget::type.
         * @param [in] library a pointer on a QMatrixLibrary, for add Matrices or edit Matrices.
         * @param [in,out] parent a pointer on a potential parent QWidget, mainly for ensure good deletion.
         */

        SetMatrixWidget(const enum type& type, QMatrixLibrary* library, QWidget* parent = nullptr);

        /**
        *  @brief The destructor of the class
        */

        ~SetMatrixWidget();

    public slots:

        /**
         * @brief chargeMatrix this function charge the values of a given Matrix in the line edits.
         * @param [in] matrixName the name of the Matrix to Load
         */

        void chargeMatrix(const QString& matrixName);

        /**
         * @brief updateSelectedMatrix this function update the values of the selected member Matrix.\n
         *      it's usefull when a Matrix is deleted by another widget but still selected in a SetMatrixWidget.
         */

        void updateSelectedMatrix();

    private:

        QMatrixLibrary* library;
        QLineEdit* nameMatrix;
        QSpinBox* nbRowsSelector;
        QSpinBox* nbColsSelector;
        QList<ExprLineEdit*> lineEditsTab;
        QGridLayout* lineEditsLayout;
        QPushButton* compute;
        QPair<QString, Matrix*> selectedMatrix;
        type type;
        unsigned int lrows;
        unsigned int lcols;

        /**
         * @brief controlKeyboardInput This function control the user entries when the button "calculate" is pressed.\n
         *          the user is notified if his entries are invalid by a QMessageBox, ( see the Error Class ).
         * @return return true if the user entries are valid, else return false.
         */

        bool controlKeyboardInput () const;

        /**
         * @brief constructType construct the type of the SetMatrixWidget ( For Add a Amtrix or Edit a Matrix ).
         * @param [in] type The type to construct the SetMatrixWidget. See SetMatrixWidget::type
         */

        void constructType(const enum type& type);

    private slots:

        /**
         * @brief computeMatrix add a user Matrix (based on user entries) to the Library, only if the user entries are Valid.
         */

        void computeMatrix();

        /**
         * @brief updateLineEdits this fonction create and delete line edits in function of the Matrix size selected by the user.
         */

        void updateLineEdits();

    signals:

        /**
         * @brief newMatrixAdded this signal is emitted when a Matrix is added to the Library. \n
         */

        void newMatrixAdded(const QPair<QString, Matrix&>) const;

        /**
         * @brief matrixEdited this signal is emitted when a Matrix is edited.
         */

        void matrixEdited(const QPair<QString, Matrix& >) const;
};

#endif
