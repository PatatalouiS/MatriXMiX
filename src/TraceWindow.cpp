
#include <QPushButton>
#include <QDebug>
#include "TraceWindow.h"
#include "Error.h"

TraceWindow::TraceWindow(MatrixLibrary* lib, QWidget* parent) : QWidget (parent)
{
    this->lib = lib;
    op1 = nullptr;

    resultImg = new ShowMatrixWidget(this);
    resultImg->hide();

    QLabel* title = new QLabel("Trace");
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
    mainLayout->addWidget(calculer);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);


    connect(op1View, &MatrixViewWidget::clicked,
            [this] () -> void
            {
                this->computeSelection();
            });
    connect(calculer, &QPushButton::clicked, this, &TraceWindow::computeOperation);

    op1View->refresh(
                [](const Matrix* a) -> bool
                {
                    return a->isSQMatrix();
                });

    setLayout(mainLayout);
}


void TraceWindow:: computeSelection ()
{
    int selectedRow;
    QString selectedName;
    resultImg->hide();
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    updateGeometry();

    selectedRow = op1View->currentIndex().row();
    selectedName = op1View->model()->item(selectedRow)->data(2).toString();
    op1Name->setText(selectedName);
    op1 = lib->find(op1Name->text().toStdString());
}


void TraceWindow:: computeOperation ()
{
    if(op1 == nullptr)
    {
        showError("Opérande Manquante !", "Veuillez bien sélectionner votre Matrice !", this);
        return;
    }

    result = op1->traceMatrix();
    resultImg->computeImgScalar(result, 1, op1Name->text(), palette().color(backgroundRole()));
    resultImg->show();
}


TraceWindow:: ~TraceWindow ()
{
}

