
#include "BinaryOpMatrixMatrixWidget.h"
#include "Error.h"
#include <QVBoxLayout>
#include <QPushButton>



BinaryOpMatrixMatrixWidget:: BinaryOpMatrixMatrixWidget(const type& t, const MatrixLibrary* lib, QWidget* parent) : AbstractOperationWidget(lib,parent)
{    
    constructType(t);
    result = Matrix();

    op1.first = "_";
    op2.first = "_";
    op1.second = nullptr;
    op2.second = nullptr;

    QVBoxLayout* op1ChoiceLayout = new QVBoxLayout;
    QLabel* op1Title = new QLabel("Choix de la matrice 1 : ");
    op1Title -> setAlignment(Qt::AlignCenter);
    view1 = new MatrixViewWidget(lib, this);
    op1ChoiceLayout->addWidget(op1Title);
    op1ChoiceLayout->addWidget(view1);
    op1ChoiceLayout->setContentsMargins(0,0,20,0);

    QVBoxLayout* op2ChoiceLayout = new QVBoxLayout;
    QLabel* op2Title = new QLabel("Choix de la matrice 2 : ");
    op2Title->setAlignment(Qt::AlignCenter);
    view2 = new MatrixViewWidget(lib, this);
    op2ChoiceLayout->addWidget(op2Title);
    op2ChoiceLayout->addWidget(view2);
    op2ChoiceLayout->setContentsMargins(20,0,0,0);

    QHBoxLayout* formLayout = new QHBoxLayout;
    formLayout->addLayout(op1ChoiceLayout);
    formLayout->addLayout(op2ChoiceLayout);
    formLayout->setAlignment(Qt::AlignCenter);

    QWidget* formWidget = new QWidget;
    formWidget->setLayout(formLayout);
    formWidget->setMaximumWidth(1330);
    formWidget->setMaximumHeight(350);

    description->setText(op1.first + logo + op2.first);

    QVBoxLayout* buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(calculer);
    buttonLayout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

    QVBoxLayout* subLayout1 = new QVBoxLayout;
    subLayout1->addWidget(title);
    subLayout1->addWidget(formWidget);
    subLayout1->addWidget(description);

    QWidget* subWidget1 = new QWidget(this);
    subWidget1->setLayout(subLayout1);
    subWidget1->setMaximumHeight(400);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);
    mainLayout->addWidget(subWidget1);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

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

    setLayout(mainLayout);
}



void BinaryOpMatrixMatrixWidget:: updateViews()
{
    view1->refresh();
    view2->refresh();
    if(op1.second != nullptr)
    {
        view2->refresh(sortViewFunction(op1.second));
    }
}



void BinaryOpMatrixMatrixWidget:: computeOperation()
{
    if(operation == nullptr) return;

    if((op1.second == nullptr) || (op2.second == nullptr))
    {
        Error::showError("Opérande Manquante !", "Veuillez bien sélectionner vos 2 Matrices", this);
        return;
    }

    result = operation(op1.second, op2.second);
    QVariant genericResult;
    genericResult.setValue(result);

    emit newResult(genericResult);
}


void BinaryOpMatrixMatrixWidget:: computeSelection(bool view)
{
    if(!view)
    {
        op2.second = nullptr;
        op2.first = "_";

        op1.first = view1->nameOfSelectedMatrix();
        assert(lib->exist(op1.first.toStdString()));
        op1.second = lib->find(op1.first.toStdString());
        view2->refresh(sortViewFunction(op1.second));
    }
    else
    {
        op2.first = view2->nameOfSelectedMatrix();
        assert(lib->exist(op2.first.toStdString()));
        op2.second = lib->find(op2.first.toStdString());
    }
    description->setText(op1.first + logo + op2.first);
}


void BinaryOpMatrixMatrixWidget:: setLogo (const QString& logo)
{
    this->logo = logo;
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
            setLogo(" + ");

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
            setLogo(" - ");

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
            setLogo(" * ");

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
            setLogo(" / ");
        }
    }
}

