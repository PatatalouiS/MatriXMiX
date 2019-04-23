
#include <QPushButton>
#include <QRadioButton>
#include <QDebug>
#include "DiagonalisationWindow.h"
#include "Error.h"
#include "Matrix.h"

DiagonalisationWindow::DiagonalisationWindow(MatrixLibrary* lib, QWidget* parent) : QDialog (parent)
{
    this->lib = lib;
    op1 = nullptr;

    resultImg = new ShowMatrixWidget(this);
    resultImg->hide();

    QLabel* title = new QLabel("Diagonalisation");
    title->setStyleSheet("font-size: 30px;");
    title->setAlignment(Qt::AlignCenter);

    QVBoxLayout* op1ChoiceLayout = new QVBoxLayout;
    QLabel* op1Title = new QLabel("Choix de la matrice : ");
    op1View = new MatrixViewWidget(lib, this);
    op1View->setFixedSize(200, 200);
    op1ChoiceLayout->addWidget(op1Title);
    op1ChoiceLayout->addWidget(op1View);

    QHBoxLayout* formLayout = new QHBoxLayout;
    formLayout->addLayout(op1ChoiceLayout);

    op1Name = new QLabel("_");
    op1Name->setStyleSheet("font-size: 40px");
    op1Name->setAlignment(Qt::AlignCenter);
    op1Name->setContentsMargins(0,25,0, 25);


    QRadioButton* showP = new QRadioButton("Matrice Passage");
    QRadioButton* showD = new QRadioButton("Matrice Diagonale");
    showD->setChecked(true);
    QRadioButton* showPInverse = new QRadioButton("Matrice Passage^-1");
    QHBoxLayout* choiceLayout = new QHBoxLayout;
    choiceLayout->addWidget(showP);
    choiceLayout->addWidget(showD);
    choiceLayout->addWidget(showPInverse);
    choiceWidget = new QWidget;
    choiceWidget->setLayout(choiceLayout);
    choiceWidget->hide();

    QPushButton* calculer = new QPushButton("Calculer");

    QVBoxLayout* subLayout1 = new QVBoxLayout;
    subLayout1->addWidget(title);
    subLayout1->addLayout(formLayout);
    subLayout1->addWidget(op1Name);
    QWidget* subWidget1 = new QWidget(this);
    subWidget1->setLayout(subLayout1);
    subWidget1->setFixedHeight(400);

    mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);
    mainLayout->addWidget(subWidget1);
    mainLayout->addWidget(resultImg);
    mainLayout->addWidget(choiceWidget);
    mainLayout->addWidget(calculer);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    op1View->refresh(
    [](const Matrix* a) -> bool
    {
         return a->isDiagonalisable();
    });

    connect(op1View, &MatrixViewWidget::clicked,
            [this] () -> void
            {
                this->computeSelection();
            });

    connect(showP, &QRadioButton::clicked,
            [this]() -> void
            {
                resultImg->computeImgMatrix(&result[0], QColor(0,0,0,0));
            });

    connect(showD, &QRadioButton::clicked,
            [this]() -> void
            {
                resultImg->computeImgMatrix(&result[1], QColor(0,0,0,0));
            });

    connect(showPInverse, &QRadioButton::clicked,
            [this]() -> void
            {
                resultImg->computeImgMatrix(&result[2], QColor(0,0,0,0));
            });

    connect(calculer, &QPushButton::clicked, this, &DiagonalisationWindow::computeOperation);

    setLayout(mainLayout);
}


void DiagonalisationWindow:: computeSelection ()
{
    resultImg->hide();
    choiceWidget->hide();

    int selectedRow;
    QString selectedName;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    updateGeometry();

    selectedRow = op1View->currentIndex().row();
    selectedName = op1View->model()->item(selectedRow)->data(2).toString();
    op1Name->setText(selectedName);
    op1 = lib->find(op1Name->text().toStdString());
}


void DiagonalisationWindow:: computeOperation ()
{
    if(op1 == nullptr)
    {
        showError("Opérande Manquante !", "Veuillez bien sélectionner votre Matrice !", this);
        return;
    }

    op1->allMatrix(result[0], result[1], result[2]);
    resultImg->computeImgMatrix(&result[1], QColor(0,0,0,0));
    choiceWidget->show();
    resultImg->show();
}


DiagonalisationWindow:: ~DiagonalisationWindow ()
{
}

