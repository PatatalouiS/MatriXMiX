#ifndef OPCHOICEWIDGET_H
#define OPCHOICEWIDGET_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QStackedLayout>

class OpChoiceWidget : public QWidget
{
    Q_OBJECT

    public:

        OpChoiceWidget(QWidget* parent);

        enum class OpType {
            BINARY_OP = 0,
            UNARY_OP = 1,
            DIAGONALISATION = 2,
            DECOMPOSITION = 3,
            EXPR_EVAL = 4
        };

    private:

        QGroupBox* opList;
        QVBoxLayout* opListLayout;

    private slots :

        /**
         * @brief setOperationsList computes the new available opeation list choosed in function
         *  of the user choice. (type)
         * @param type the new type of operations choosed by user
         */
        void setOperationsList(const OpType& type);

    signals:

        /**
         * @brief opSelected this signal is emitted when a new operation is selected by user
         * @param index the new index of the new operation choosen
         */
        void opSelected(unsigned int index);
};

#endif // OPCHOICEWIDGET_H
