
#include <QPushButton>
#include <QDebug>
#include "ScalarMultiplicationWindow.h"
#include "Error.h"


ScalarMultiplicationWindow::ScalarMultiplicationWindow(MatrixLibrary* lib, QWidget* parent) : QWidget (parent)
{
    this->lib = lib;
    op1Name = "_";
    op1 = nullptr;
    op2 = 1;

    resultImg = new ShowMatrixWidget(this);
    resultImg->hide();

    QLabel* title = new QLabel("Multiplication Scalaire");
    title->setStyleSheet("font-size: 30px; font:bold;");
    title->setAlignment(Qt::AlignCenter);
    title->setContentsMargins(0,0,0,10);

    QVBoxLayout* op1ChoiceLayout = new QVBoxLayout;
    QLabel* op1Title = new QLabel("Choix de la matrice 1 : ");
    op1View = new MatrixViewWidget(lib, this);
    op1Title -> setAlignment(Qt::AlignCenter);
    op1ChoiceLayout->addWidget(op1Title);
    op1ChoiceLayout->addWidget(op1View);
    op1ChoiceLayout->setContentsMargins(0,0,20,0);

    QVBoxLayout* op2ChoiceLayout = new QVBoxLayout;
    QLabel* op2Title = new QLabel("Choix du Scalaire :");
    op2Title -> setAlignment(Qt::AlignBottom);
    op2Edit = new QLineEdit;
    op2Edit->setMinimumWidth(30);
    op2Edit->setMaximumWidth(50);
    op2Edit->setMaxLength(5);
    op2Edit->setValidator(new QDoubleValidator(op2Edit));

    op2ChoiceLayout->addWidget(op2Title);
    op2ChoiceLayout->addWidget(op2Edit);
    op2ChoiceLayout->setContentsMargins(20,0,0,0);

    QHBoxLayout* formLayout = new QHBoxLayout;
    formLayout->addLayout(op1ChoiceLayout);
    formLayout->addLayout(op2ChoiceLayout);
    formLayout->setAlignment(Qt::AlignCenter);

    QWidget* formWidget = new QWidget;
    formWidget->setLayout(formLayout);
    formWidget->setMaximumWidth(1330);
    formWidget->setMaximumHeight(350);

    formula = new QLabel("_  *  _");
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
    subWidget1->setFixedHeight(400);

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

    connect(calculer, &QPushButton::clicked, this, &ScalarMultiplicationWindow::computeOperation);

    connect(op2Edit, &QLineEdit::textChanged,
            [this] () -> void
            {
                this->computeSelection(1);
            });

    setLayout(mainLayout);
}


void ScalarMultiplicationWindow:: computeSelection (bool op)
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
        op2 = op2Edit->text().replace(QLatin1Char(','), QLatin1Char('.')).toDouble();
    }

    formula->setText(op1Name + " * " + QString::number(op2));
}


void ScalarMultiplicationWindow:: computeOperation ()
{
    if(op1 == nullptr)
    {
        showError("Opérande Manquante !", "Veuillez bien sélectionner"
                " vos 2 Opérandes !", this);
        return;
    }

    result = *op1 * op2;
    resultImg->computeImgMatrix(&result, palette().color(backgroundRole()));
    resultImg->show();
}


ScalarMultiplicationWindow:: ~ScalarMultiplicationWindow ()
{
}

