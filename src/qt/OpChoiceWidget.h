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
        DECOMPOSITION = 3
    };

    private:

        QGroupBox* opList;
        QVBoxLayout* opListLayout;

    private slots :

        void setOperationsList(const OpType& type);

    signals:

        void opSelected(unsigned int index);


};

#endif // OPCHOICEWIDGET_H
