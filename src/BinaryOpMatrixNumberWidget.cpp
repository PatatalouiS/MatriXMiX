
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
    view = new MatrixViewWidget(lib, this);
    view->setFixedSize(200, 200);
    op1ChoiceLayout->addWidget(op1Title);
    op1ChoiceLayout->addWidget(view);

    QVBoxLayout* op2ChoiceLayout = new QVBoxLayout;
    QLabel* op2Title = new QLabel("Choix du nombre:");
    edit = new QLineEdit;
    edit->setFixedSize(75,35);
    edit->setStyleSheet("QLineEdit{border: 1px solid grey; border-radius: 3px;"
                           "font-size: 15px;}"
                       );
    edit->setText("0");
    op2ChoiceLayout->addWidget(op2Title);
    op2ChoiceLayout->addWidget(edit);

    QHBoxLayout* formLayout = new QHBoxLayout;
    formLayout->addLayout(op1ChoiceLayout);
    formLayout->addLayout(op2ChoiceLayout);

    description->setText(op1.first + logo + QString::number(op2));
    description->setStyleSheet("font-size: 40px");
    description->setAlignment(Qt::AlignCenter);
    description->setContentsMargins(0,25,0, 25);

    QVBoxLayout* subLayout1 = new QVBoxLayout;
    subLayout1->addWidget(title);
    subLayout1->addLayout(formLayout);
    subLayout1->addWidget(description);
    QWidget* subWidget1 = new QWidget(this);
    subWidget1->setLayout(subLayout1);
    subWidget1->setFixedHeight(400);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);
    mainLayout->addWidget(subWidget1);
    mainLayout->addWidget(calculer);
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

    constructType(t);
    view->refresh(sortFunction);
    setLayout(mainLayout);
}



void BinaryOpMatrixNumberWidget:: updateViews()
{
}



void BinaryOpMatrixNumberWidget:: computeOperation()
{
    if(operation == nullptr) return;

    if(op1.second == nullptr)
    {
        showError("Opérande Manquante !", "Veuillez bien sélectionner votre matrice !", this);
        return;
    }

    result = operation(op1.second, op2);
    QVariant genericResult;
    genericResult.setValue(result);

    emit newResult(genericResult);
}


void BinaryOpMatrixNumberWidget:: computeSelection(bool view)
{
    if(!view)
    {
        int selectedRow;
        selectedRow = this->view->currentIndex().row();
        op1.first = this->view->model()->item(selectedRow)->data(2).toString();
        op1.second = lib->find(op1.first.toStdString());
    }
    else
    {
        op2 = edit->text().replace(',', '.').toDouble();
    }
    description->setText(op1.first + logo + QString::number(op2));
}


void BinaryOpMatrixNumberWidget:: setLogo (const QString& logo)
{
    this->logo = logo;
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

            setLogo(" * ");
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

            setLogo(" ^ ");
            setTitle("Puissance");
        }
    }
}




