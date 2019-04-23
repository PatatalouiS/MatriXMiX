
#include <QPushButton>
#include <QDebug>
#include "AdditionWindow.h"
#include "Error.h"

AdditionWindow::AdditionWindow(MatrixLibrary* lib, QWidget* parent) : QWidget (parent)
{
    this->lib = lib;
    op1Name = "_";
    op2Name = "_";
    op1 = nullptr;
    op2 = nullptr;

    resultImg = new ShowMatrixWidget(this);
    resultImg->hide();

    QLabel* title = new QLabel("Addition");
    title->setStyleSheet("font-size: 30px; font:bold;");
    title->setAlignment(Qt::AlignCenter);
    title->setContentsMargins(0,0,0,10);

    QVBoxLayout* op1ChoiceLayout = new QVBoxLayout;
    QLabel* op1Title = new QLabel("Choix de la matrice 1 : ");
    op1Title -> setAlignment(Qt::AlignCenter);
    op1View = new MatrixViewWidget(lib, this);
    op1ChoiceLayout->addWidget(op1Title);
    op1ChoiceLayout->addWidget(op1View);
    op1ChoiceLayout->setContentsMargins(0,0,20,0);

    QVBoxLayout* op2ChoiceLayout = new QVBoxLayout;
    QLabel* op2Title = new QLabel("Choix de la matrice 2 : ");
    op2Title->setAlignment(Qt::AlignCenter);
    op2View = new MatrixViewWidget(lib, this);
    op2ChoiceLayout->addWidget(op2Title);
    op2ChoiceLayout->addWidget(op2View);
    op2ChoiceLayout->setContentsMargins(20,0,0,0);

    QHBoxLayout* formLayout = new QHBoxLayout;
    formLayout->addLayout(op1ChoiceLayout);
    formLayout->addLayout(op2ChoiceLayout);
    formLayout->setAlignment(Qt::AlignCenter);

    QWidget* formWidget = new QWidget;
    formWidget->setLayout(formLayout);
    formWidget->setMaximumWidth(1330);
    formWidget->setMaximumHeight(350);

    formula = new QLabel("_  +  _");
    formula->setStyleSheet("font-size: 40px");
    formula->setAlignment(Qt::AlignCenter);

    QPushButton* calculer = new QPushButton("Calculer");
    calculer->setCursor(Qt::PointingHandCursor);
    calculer->setStyleSheet("QPushButton{ background-color: lightGrey } "
                            "QPushButton:hover{ background-color: lightBlue }");
    calculer->setFixedSize(300,30);

    QVBoxLayout* buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(calculer);
    buttonLayout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

    QVBoxLayout* subLayout1 = new QVBoxLayout;
    subLayout1->addWidget(title);
    subLayout1->addWidget(formWidget);
    subLayout1->addWidget(formula);

    QWidget* subWidget1 = new QWidget(this);
    subWidget1->setLayout(subLayout1);
    subWidget1->setMaximumHeight(400);

    mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);
    mainLayout->addWidget(subWidget1);
    mainLayout->addWidget(resultImg);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    connect(op1View, &MatrixViewWidget::clicked,
            [this] () -> void
            {
                this->computeSelection(0);
            });
    connect(op2View, &MatrixViewWidget::clicked,
            [this] () -> void
            {
                this->computeSelection(1);
            });
    connect(calculer, &QPushButton::clicked, this, &AdditionWindow::computeOperation);

    setLayout(mainLayout);
}


void AdditionWindow:: computeSelection (bool op)
{
    int selectedRow;
    QString selectedName;
    resultImg->hide();
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    updateGeometry();

    if(!op)
    {
        op2 = nullptr;
        op2Name = "_";

        selectedRow = op1View->currentIndex().row();
        selectedName = op1View->model()->item(selectedRow)->data(2).toString();
        op1Name = selectedName;
        op1 = lib->find(op1Name.toStdString());
        formula->setText(op1Name + " + " + op2Name);
        op2View->refresh(
               [this](const Matrix* a)
               {
                   return ((op1->getNbCols() == a->getNbCols()) &&
                    (op1->getNbRows() == a->getNbRows()));
               });
    }
    else
    {
        selectedRow = op2View->currentIndex().row();
        selectedName = op2View->model()->item(selectedRow)->data(2).toString();
        op2Name = selectedName;
        op2 = lib->find(selectedName.toStdString());
        formula->setText(op1Name + " + " + op2Name);
    }
}


void AdditionWindow:: computeOperation ()
{
    if((op1 == nullptr) || (op2 == nullptr))
    {
        showError("Opérande Manquante !", "Veuillez bien sélectionner vos 2 Matrices", this);
        return;
    }

    result = *op1 + *op2;
    resultImg->computeImgMatrix(&result, QColor(0,0,0,0));
    resultImg->show();
}


AdditionWindow:: ~AdditionWindow ()
{
}

