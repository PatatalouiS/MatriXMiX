
#include "BinaryOpMatrixNumberWidget.h"
#include "Error.h"
#include <QVBoxLayout>
#include <QGroupBox>



BinaryOpMatrixNumberWidget::BinaryOpMatrixNumberWidget(const type& t, const QMatrixLibrary* lib, QWidget* parent) :
AbstractOperationWidget(lib, parent)
{
    QString style = "QLabel {"
                        "background-color: rgb(243,243,243);"
                        "border-top-left-radius : 4px;"
                        "border-top-right-radius : 4px;"
                        "border : 1px solid lightGrey;"
                    "}";

    op1.first = "_";
    op1.second = nullptr;
    op2 = 0;
    result = Matrix();

    description->setText(op1.first + logo + QString::number(op2));
    description->setStyleSheet("font-size: 40px");

    QVBoxLayout* op1ChoiceLayout = new QVBoxLayout;
    QLabel* op1Title = new QLabel("Choix de la matrice 1 : ");
    op1Title -> setAlignment(Qt::AlignCenter);
    op1Title->setStyleSheet(style);
    view = new MatrixViewWidget(lib, this);
    view->setMaximumWidth(300);
    op1ChoiceLayout->addWidget(op1Title);
    op1ChoiceLayout->addWidget(view);
    op1ChoiceLayout->setSpacing(0);
    op1ChoiceLayout->setContentsMargins(0,0,10,0);

    QVBoxLayout* op2ChoiceLayout = new QVBoxLayout;
    QGroupBox* op2Group = new QGroupBox("Choix du nombre :", this);
    edit = new QLineEdit;
    edit->setFixedHeight(50);
    edit->setStyleSheet("QLineEdit{border: 1px solid grey; border-radius: 3px;"
                           "font-size: 15px;}"
                       );
    constructType(t);

    edit->setText("0");
    op2ChoiceLayout->addWidget(edit);
    op2Group->setLayout(op2ChoiceLayout);
    op2Group->setMaximumHeight(250);
    op2Group->setStyleSheet( "QGroupBox { "
                             "border: 1px solid silver;"
                             "background-color:rgb(243,243,243);"
                             "border-radius: 5px;"
                             "margin-top: 15px; }"
                             "QGroupBox::title { subcontrol-origin:margin;"
                             "margin-top : 5px;"
                             "background-color:rgb(235,235,235) ;"
                             "border : 1px solid grey;"
                             "border-radius : 5px;"
                             "subcontrol-position: top;"
                             "font: bold ; color: black;"
                       "}");

    QVBoxLayout* rightLayout = new QVBoxLayout;
    rightLayout->addWidget(description);
    rightLayout->addWidget(calculer);
    rightLayout->addWidget(resultAdder);
    rightLayout->setAlignment(Qt::AlignCenter);

    QHBoxLayout* subLayout = new QHBoxLayout;
    subLayout->addStretch(1);
    subLayout->addLayout(op1ChoiceLayout);
    subLayout->addStretch(1);
    subLayout->addWidget(op2Group);
    subLayout->addStretch(1);
    subLayout->addLayout(rightLayout);
    subLayout->addStretch(1);
    subLayout->setAlignment(Qt::AlignCenter);
    subLayout->setContentsMargins(20, 20, 20, 20);

    mainWidget->setLayout(subLayout);

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
        Error::showError("Opérande manquante !", "Veuillez bien sélectionner votre matrice !", this);
        return;
    }

    result = operation(op1.second, op2);
    QVariant genericResult;
    genericResult.setValue(result);

    emit newResult(genericResult);
}


void BinaryOpMatrixNumberWidget:: computeSelection(const bool viewId)
{
    resultAdder->hide();

    if(!viewId)
    {
        op1.first = view->nameOfSelectedMatrix();
        assert(getLib()->exist(op1.first));
        op1.second = getLib()->find(op1.first);
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




