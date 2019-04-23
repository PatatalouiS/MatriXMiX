
#include <QPushButton>
#include <QDebug>
#include "ExprEvalWindow.h"
#include "Error.h"


ExprEvalWindow::ExprEvalWindow(MatrixLibrary* lib, QWidget* parent) : QDialog (parent)
{
    this->lib = lib;

    resultImg = new ShowMatrixWidget(this);
    resultImg->hide();

    QLabel* title = new QLabel("Evaluation d'expression");
    title->setStyleSheet("font-size: 30px;");
    title->setAlignment(Qt::AlignCenter);

    QVBoxLayout* op1ChoiceLayout = new QVBoxLayout;
    QLabel* op1Title = new QLabel("Matrices disponibles : ");
    op1View = new MatrixViewWidget(lib, this);
    op1View->setFixedSize(200, 200);
    op1ChoiceLayout->addWidget(op1Title);
    op1ChoiceLayout->addWidget(op1View);

    QHBoxLayout* formLayout = new QHBoxLayout;
    formLayout->addLayout(op1ChoiceLayout);

    expression = new QLineEdit("Votre Expression");
    expression->setMinimumSize(200, 30);

    QPushButton* calculer = new QPushButton("Calculer");

    QVBoxLayout* subLayout1 = new QVBoxLayout;
    subLayout1->addWidget(title);
    subLayout1->addLayout(formLayout);
    QWidget* subWidget1 = new QWidget(this);
    subWidget1->setLayout(subLayout1);
    subWidget1->setFixedHeight(400);

    mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);
    mainLayout->addWidget(subWidget1);
    mainLayout->addWidget(resultImg);
    mainLayout->addWidget(expression);
    mainLayout->addWidget(calculer);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);


    connect(op1View, &MatrixViewWidget::clicked,
            [this] () -> void
            {
                this->computeSelection();
            });
    connect(calculer, &QPushButton::clicked, this, &ExprEvalWindow::computeOperation);

    op1View->refresh(
                [](const Matrix* a) -> bool
                {
                    return ((a->isSQMatrix()) && (a->determinant() != 0.0));
                });

    setLayout(mainLayout);
}


void ExprEvalWindow:: computeSelection ()
{

}


void ExprEvalWindow:: computeOperation ()
{


    resultImg->computeImgMatrix(&result, palette().color(backgroundRole()));
    resultImg->show();
}


ExprEvalWindow:: ~ExprEvalWindow ()
{
}

