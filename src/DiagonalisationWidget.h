

#ifndef DIAGONALISATIONWIDGET_H
#define DIAGONALISATIONWIDGET_H


#include "AbstractOperationWidget.h"
#include "MatrixViewWidget.h"
#include<array>



class DiagonalisationWidget : public AbstractOperationWidget
{
    Q_OBJECT

    private:

        enum ResultChoice
        {
            P = 0,
            D = 1,
            P_INVERSE = 2
        };

        MatrixViewWidget* view;
        MatrixPair op;
        std::array<Matrix, 3> result;
        QWidget* choiceWidget;


    private slots:

        virtual void computeSelection(bool view = 0) override;
        virtual void computeOperation() override;
        void emitResultChoice(const ResultChoice& c);

    public:

        DiagonalisationWidget (const MatrixLibrary* lib, QWidget* parent = nullptr);

    public slots:

        virtual void updateViews() override;
};



#endif
