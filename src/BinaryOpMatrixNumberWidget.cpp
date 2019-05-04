
#include "BinaryOpMatrixNumberWidget.h"
#include "Error.h"
#include <QVBoxLayout>



BinaryOpMatrixNumberWidget::BinaryOpMatrixNumberWidget(const type& t, const MatrixLibrary* lib, QWidget* parent) :
AbstractOperationWidget(lib, parent)
{
    op1.first = "_";
    op1.second = nullptr;
    op2 = 0;
    result = Matrix();

    QVBoxLayout* op1ChoiceLayout = new QVBoxLayout;
    QLabel* op1Title = new QLabel("Choix de la matrice 1 : ");
    op1Title -> setAlignment(Qt::AlignCenter);
    view = new MatrixViewWidget(lib, this);
    op1ChoiceLayout->addWidget(op1Title);
    op1ChoiceLayout->addWidget(view);
    op1ChoiceLayout->setContentsMargins(0,0,20,0);

    QVBoxLayout* op2ChoiceLayout = new QVBoxLayout;
    QLabel* op2Title = new QLabel("Choix du nombre:");
    op2Title -> setAlignment(Qt::AlignCenter);
    edit = new QLineEdit;
    edit->setFixedSize(75,35);
    edit->setStyleSheet("QLineEdit{border: 1px solid grey; border-radius: 3px;"
                           "font-size: 15px;}"
                       );
    constructType(t);

    edit->setText("0");
    op2ChoiceLayout->addWidget(op2Title);
    op2ChoiceLayout->addWidget(edit);
    op2ChoiceLayout->setAlignment(Qt::AlignVCenter);
    op2ChoiceLayout->setContentsMargins(20,0,0,0);

    QHBoxLayout* formLayout = new QHBoxLayout;
    formLayout->addLayout(op1ChoiceLayout);
    formLayout->addLayout(op2ChoiceLayout);
    formLayout->setAlignment(Qt::AlignCenter);
    formLayout->setContentsMargins(0,0,20,0);

    description->setText(op1.first + logo + QString::number(op2));
    description->setStyleSheet("font-size: 40px");
    //description->setAlignment(Qt::AlignCenter);

    QVBoxLayout* buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(calculer);
    buttonLayout->setAlignment(Qt::AlignCenter| Qt::AlignTop);

    QVBoxLayout* subLayout1 = new QVBoxLayout;
    subLayout1->addWidget(title);
    subLayout1->addLayout(formLayout);

    QVBoxLayout* subLayout2 = new QVBoxLayout;
    subLayout2->addWidget(description);
    subLayout2->addLayout(buttonLayout);

    QHBoxLayout* subLayout3 = new QHBoxLayout;
    subLayout3->addLayout(subLayout1);
    subLayout3->addLayout(subLayout2);

    QWidget* subWidget1 = new QWidget(this);
    subWidget1->setLayout(subLayout3);
    subWidget1->setMaximumHeight(300);
    subWidget1->setMaximumWidth(800);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);
    mainLayout->addWidget(subWidget1);
    //mainLayout->addWidget(calculer);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    connect(view, &MatrixViewWidget::clicked,
            [this] () -> void
            {
                this->computeSelection(0);
            });

    connect(edit, &QLineEdit::textChanged,
            [this] () -> void
            {
                this->computeSelection(1);
            });

    view->refresh(sortFunction);
    setLayout(mainLayout);
}



void BinaryOpMatrixNumberWidget:: updateViews()
{
    view->refresh(sortFunction);
}



void BinaryOpMatrixNumberWidget:: computeOperation()
{
    if(operation == nullptr) return;

    if(op1.second == nullptr)
    {
        Error::showError("Opérande Manquante !", "Veuillez bien sélectionner votre matrice !", this);
        return;
    }

    result = operation(op1.second, op2);
    QVariant genericResult;
    genericResult.setValue(result);

    emit newResult(genericResult);
}


void BinaryOpMatrixNumberWidget:: computeSelection(bool viewId)
{
    if(!viewId)
    {
        op1.first = view->nameOfSelectedMatrix();
        assert(lib->exist(op1.first.toStdString()));
        op1.second = lib->find(op1.first.toStdString());
    }
    else
    {
        op2 = edit->text().replace(',', '.').toDouble();
    }

    description->setText(op1.first + logo + QString::number(op2));
}


void BinaryOpMatrixNumberWidget:: constructType(const type& t)
{
    switch(t)
    {
        case SCALAR_MULTIPLICATION :
        {
            operation = [](const Matrix* a, const double b) -> Matrix
            {
              return *a * b;
            };

            edit->setValidator(new QDoubleValidator(-99999, 99999, 5, this));

            logo = " * ";
            setTitle("Multiplication");

            break;
        }
        case POWER :
        {
            setSortFunction([](const Matrix* a)-> bool
            {
               return a->isSQMatrix();
            });

            operation = [](const Matrix* a, const double b) -> Matrix
            {
              return (*a) ^ int(b);
            };

            edit->setValidator(new QIntValidator(-1, 200, this));

            logo = " ^ ";
            setTitle("Puissance");
        }
    }
}




