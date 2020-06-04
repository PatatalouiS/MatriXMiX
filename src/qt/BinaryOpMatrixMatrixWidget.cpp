
#include "BinaryOpMatrixMatrixWidget.h"
#include "Error.h"
#include <QVBoxLayout>
#include <QPushButton>

BinaryOpMatrixMatrixWidget:: BinaryOpMatrixMatrixWidget(const type& t, const QMatrixLibrary* lib, QWidget* parent) : AbstractOperationWidget(lib,parent)
{    
    constructType(t);
    result = Matrix();

    op1.first = "_";
    op2.first = "_";
    op1.second = nullptr;
    op2.second = nullptr;

    description->setText(op1.first + logo + op2.first);

    QString style = "QLabel {"
                        "background-color: rgb(243,243,243);"
                        "border-top-left-radius : 4px;"
                        "border-top-right-radius : 4px;"
                        "border : 1px solid lightGrey;"
                    "}";

    QVBoxLayout* op1ChoiceLayout = new QVBoxLayout;
    QLabel* op1Title = new QLabel("Choix de la matrice 1 : ");
    op1Title -> setAlignment(Qt::AlignCenter);
    op1Title->setStyleSheet(style);
    view1 = new MatrixViewWidget(lib, this);
    view1->setMaximumWidth(300);
    op1ChoiceLayout->addWidget(op1Title);
    op1ChoiceLayout->addWidget(view1);
    op1ChoiceLayout->setSpacing(0);
    op1ChoiceLayout->setContentsMargins(0,0,10,0);

    QVBoxLayout* op2ChoiceLayout = new QVBoxLayout;
    QLabel* op2Title = new QLabel("Choix de la matrice 2 : ");
    op2Title->setAlignment(Qt::AlignCenter);
    op2Title->setStyleSheet(style);
    view2 = new MatrixViewWidget(lib, this);
    view2->setMaximumWidth(300);
    op2ChoiceLayout->addWidget(op2Title);
    op2ChoiceLayout->addWidget(view2);
    op2ChoiceLayout->setSpacing(0);
    op2ChoiceLayout->setContentsMargins(10,0,0,0);

    QVBoxLayout* rightLayout = new QVBoxLayout;
    rightLayout->addWidget(description);
    rightLayout->addWidget(calculer);
    rightLayout->setAlignment(Qt::AlignCenter);

    QHBoxLayout* subLayout = new QHBoxLayout;
    subLayout->addStretch(1);
    subLayout->addLayout(op1ChoiceLayout);
    subLayout->addStretch(1);
    subLayout->addLayout(op2ChoiceLayout);
    subLayout->addStretch(1);
    subLayout->addLayout(rightLayout);
    subLayout->addStretch(1);
    subLayout->setAlignment(Qt::AlignCenter);
    subLayout->setContentsMargins(22, 13, 22, 22);

    mainWidget->setLayout(subLayout);

    connect(view1, &MatrixViewWidget::clicked,
            [this] () -> void
            {
                this->computeSelection(0);
            });
    connect(view2, &MatrixViewWidget::clicked,
            [this] () -> void
            {
                this->computeSelection(1);
            });

    view1->refresh(sortFunction);
    view2->refresh(sortFunction);
}


void BinaryOpMatrixMatrixWidget:: updateViews()
{
    view1->refresh();
    view2->refresh();
    if(op1.second != nullptr) // si op1 is selected, refresh view2 with the good closure.
    {
        view2->refresh(sortViewFunction(op1.second));
    }
}

void BinaryOpMatrixMatrixWidget:: computeOperation()
{
    if(operation == nullptr) return;

    if((op1.second == nullptr) || (op2.second == nullptr))
    {
        Error::showError("Opérande manquante !", "Veuillez bien sélectionner vos 2 matrices", this);
        return;
    }

    result = operation(op1.second, op2.second);
    QVariant genericResult;
    genericResult.setValue(result);

    emit newResult(genericResult);
}


void BinaryOpMatrixMatrixWidget:: computeSelection(const bool view)
{
    if(!view)
    {
        op2.second = nullptr;
        op2.first = "_";

        op1.first = view1->nameOfSelectedMatrix();
        assert(getLib()->exist(op1.first));
        op1.second = getLib()->find(op1.first);
        view2->refresh(sortViewFunction(op1.second));
    }
    else
    {
        op2.first = view2->nameOfSelectedMatrix();
        assert(getLib()->exist(op2.first));
        op2.second = getLib()->find(op2.first);
    }

    description->setText(op1.first + logo + op2.first);
}



void BinaryOpMatrixMatrixWidget:: constructType(const type& t)
{
    switch(t)
    {
        case ADDITION :
        {
            sortViewFunction = [](const Matrix* a) -> std::function<bool(const Matrix* b)>
            {
                return [a](const Matrix* b) -> bool
                {
                    return (a->getNbRows() == b->getNbRows()) && (a->getNbCols() == b->getNbCols());
                };
            };

            operation =[](const Matrix* a, const Matrix* b) -> Matrix
            {
                return *a + *b;
            };

            setTitle("Addition");
            logo =  " + " ;

            break;
        }
        case SOUSTRACTION :
        {
            sortViewFunction = [](const Matrix* a) -> std::function<bool(const Matrix* b)>
            {
                return [a](const Matrix* b) -> bool
                {
                    return (a->getNbRows() == b->getNbRows()) && (a->getNbCols() == b->getNbCols());
                };
            };

            operation =[](const Matrix* a, const Matrix* b) -> Matrix
            {
                return *a - *b;
            };

            setTitle("Soustraction");
            logo = " - ";

            break;
        }
        case MULTIPLICATION :
        {
            sortViewFunction = [](const Matrix* a) -> std::function<bool(const Matrix* b)>
            {
                return [a](const Matrix* b) -> bool
                {
                    return (a->getNbCols() == b->getNbRows());
                };
            };

            operation = [](const Matrix* a, const Matrix* b) -> Matrix
            {
                return *a * *b;
            };

            setTitle("Multiplication");
            logo = " * ";

            break;
        }
        case DIVISION :
        {
            sortViewFunction = [] (const Matrix* a) -> std::function<bool(const Matrix* b)>
            {
                return [a](const Matrix* b) -> bool
                {
                    return (a->getNbCols() == b->getNbRows()) && b->isSQMatrix() && (b->determinant() != 0.0);
                };
            };

            operation = [](const Matrix* a, const Matrix* b) -> Matrix
            {
                return  a->operator/(*b);
            };

            setTitle("Division");
            logo = " / ";
            break;
        }
        case SOLVE :
        {
            sortViewFunction = [] (const Matrix* a) -> std::function<bool(const Matrix* b)>
            {
                return [a](const Matrix* b) -> bool
                {
                    return ((a->getNbRows() == b->getNbRows()) && a->isSQMatrix() && (b->getNbCols() == 1));
                };
            };

            operation = [](const Matrix* a, const Matrix* b) -> Matrix
            {
                return  a->solveAx(*b);
            };

            setTitle("Résolution Ax = b");
            logo = " x = ";
            break;
        }
    }
}

