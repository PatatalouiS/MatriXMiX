
#include <QPushButton>
#include <QDebug>
#include "PowerWindow.h"
#include "Error.h"


PowerWindow::PowerWindow(MatrixLibrary* lib, QWidget* parent) : QWidget (parent)
{
    this->lib = lib;
    op1Name = "_";
    op1 = nullptr;
    op2 = 1;

    resultImg = new ShowMatrixWidget(this);
    resultImg->hide();

    QLabel* title = new QLabel("Puissance");
    title->setStyleSheet("font-size: 30px;");
    title->setAlignment(Qt::AlignCenter);

    QVBoxLayout* op1ChoiceLayout = new QVBoxLayout;
    QLabel* op1Title = new QLabel("Choix de la matrice 1 : ");
    op1View = new MatrixViewWidget(lib, this);
    op1View->setFixedSize(200, 200);
    op1ChoiceLayout->addWidget(op1Title);
    op1ChoiceLayout->addWidget(op1View);

    QVBoxLayout* op2ChoiceLayout = new QVBoxLayout;
    QLabel* op2Title = new QLabel("Choix de la puissance :");
    op2Edit = new QSpinBox;
    op2Edit->setRange(-1,100);
    op2Edit->setFixedSize(75,35);
    op2Edit->setStyleSheet("QSpinBox{border: 1px solid grey; border-radius: 3px;"
                           "font-size: 15px;}"
                           "QSpinBox::down-button{width: 20px;}"
                           "QSpinBox::up-button{width: 20px;}");
    op2Edit->setButtonSymbols(QAbstractSpinBox::PlusMinus);
    op2Edit->setValue(1);
    op2ChoiceLayout->addWidget(op2Title);
    op2ChoiceLayout->addWidget(op2Edit);

    QHBoxLayout* formLayout = new QHBoxLayout;
    formLayout->addLayout(op1ChoiceLayout);
    formLayout->addLayout(op2ChoiceLayout);

    formula = new QLabel("_  ^  _");
    formula->setStyleSheet("font-size: 40px");
    formula->setAlignment(Qt::AlignCenter);
    formula->setContentsMargins(0,25,0, 25);

    QPushButton* calculer = new QPushButton("Calculer");

    QVBoxLayout* subLayout1 = new QVBoxLayout;
    subLayout1->addWidget(title);
    subLayout1->addLayout(formLayout);
    subLayout1->addWidget(formula);
    QWidget* subWidget1 = new QWidget(this);
    subWidget1->setLayout(subLayout1);
    subWidget1->setFixedHeight(400);

    mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);
    mainLayout->addWidget(subWidget1);
    mainLayout->addWidget(resultImg);
    mainLayout->addWidget(calculer);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);


    connect(op1View, &MatrixViewWidget::clicked,
            [this] () -> void
            {
                this->computeSelection(0);
            });

    connect(calculer, &QPushButton::clicked, this, &PowerWindow::computeOperation);

    connect(op2Edit, QOverload<int>::of(&QSpinBox::valueChanged),
            [this] () -> void
            {
                this->computeSelection(1);
            });



    op1View->refresh(
                [] (const Matrix* a) -> bool
                {
                    return a->isSQMatrix();
                });

    setLayout(mainLayout);
}


void PowerWindow:: computeSelection (bool op)
{
    if(!op)
    {
        int selectedRow;
        QString selectedName;
        resultImg->hide();
        mainLayout->setSizeConstraint(QLayout::SetFixedSize);
        updateGeometry();

        selectedRow = op1View->currentIndex().row();
        selectedName = op1View->model()->item(selectedRow)->data(2).toString();
        op1Name = selectedName;
        op1 = lib->find(selectedName.toStdString());
    }
    else
    {
        op2 = op2Edit->value();
    }

    formula->setText(op1Name + " ^ " + QString::number(op2));
}


void PowerWindow:: computeOperation ()
{
    if(op1 == nullptr)
    {
        showError("Opérande Manquante !", "Veuillez bien sélectionner"
                " vos 2 Opérandes !", this);
        return;
    }
    else if((op2 == -1) && (op1->determinant() == 0.0))
    {
        showError("Calcul Impossible !", "La Matrice " + op1Name +
                  " n'est pas inversible !", this);
        return;
    }

    result = (*op1) ^ op2;
    resultImg->computeImgMatrix(&result, palette().color(backgroundRole()));
    resultImg->show();
}


PowerWindow:: ~PowerWindow ()
{
}

