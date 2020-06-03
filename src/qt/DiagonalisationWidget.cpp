
#include "DiagonalisationWidget.h"
#include "Error.h"
#include <QVBoxLayout>
#include <QRadioButton>


DiagonalisationWidget::DiagonalisationWidget(const type t, const QMatrixLibrary* lib, QWidget* parent):
AbstractOperationWidget (lib, parent)
{
    constructType(t);

    result = std::array<Matrix,3>();
    op.first = "_";
    op.second = nullptr;

    QVBoxLayout* op1ChoiceLayout = new QVBoxLayout;
    QLabel* op1Title = new QLabel("Choix de la matrice : ");
    op1Title -> setAlignment(Qt::AlignCenter);
    view = new MatrixViewWidget(lib, this);

    op1ChoiceLayout->addWidget(op1Title);
    op1ChoiceLayout->addWidget(view);

    QHBoxLayout* formLayout = new QHBoxLayout;
    formLayout->addLayout(op1ChoiceLayout);
    formLayout->setAlignment(Qt::AlignCenter);

    description->setText(op.first);

    QRadioButton* showP = new QRadioButton("Matrice de passage");
    QRadioButton* showD = new QRadioButton("Matrice Diagonale");
    showD->setChecked(true);
    QRadioButton* showPInverse = new QRadioButton("Matrice de passage^-1");
    QHBoxLayout* choiceLayout = new QHBoxLayout;
    choiceLayout->addWidget(showP);
    choiceLayout->addWidget(showD);
    choiceLayout->addWidget(showPInverse);
    choiceWidget = new QWidget;
    choiceWidget->setLayout(choiceLayout);
    choiceWidget->hide();

    QVBoxLayout* buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(calculer);
    buttonLayout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

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
    subWidget1->setMaximumWidth(600);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);
    mainLayout->addWidget(subWidget1);
    mainLayout->addWidget(choiceWidget);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    connect(view, &MatrixViewWidget::clicked,
            [this] () -> void
            {
                computeSelection();
            });

    connect(showP, &QRadioButton::clicked,
            [this]() -> void
            {
                emitResultChoice(P);
            });

    connect(showD, &QRadioButton::clicked,
            [this]() -> void
            {
                emitResultChoice(D);
            });

    connect(showPInverse, &QRadioButton::clicked,
            [this]() -> void
            {
                emitResultChoice(P_INVERSE);
            });

    view->refresh(sortFunction);
    setLayout(mainLayout);
}


void DiagonalisationWidget::constructType(const type t) {
    switch(t) {
        case DIAGONALISATION_R : {
            setTitle("Diagonalisation dans R");
            setSortFunction([](const Matrix* a) -> bool {
                return a->isDiagonalisableR();
            });
            break;

        }
        case DIAGONALISATION_C : {
            setTitle("Diagonalisation dans C");
            setSortFunction([](const Matrix* a) -> bool {
                return a->isDiagonalisableC();
            });
            break;
        }
    }
}


void DiagonalisationWidget:: emitResultChoice(const ResultChoice& c)
{
    QVariant genericResult;
    genericResult.setValue(result[c]);
    emit newResult(genericResult);
}



void DiagonalisationWidget::updateViews()
{
    view->refresh(sortFunction);
}


void DiagonalisationWidget:: computeSelection(const bool viewID)
{
    (void)viewID;

    choiceWidget->hide();
    op.first = view->nameOfSelectedMatrix();
    assert(getLib()->exist(op.first));
    op.second = getLib()->find(op.first);
    description->setText(op.first);
}

void DiagonalisationWidget:: computeOperation()
{
    if(op.second == nullptr)
    {
        Error::showError("opérande Manquante !", "Veuillez bien sélectionner votre matrice !", this);
        return;
    }

    op.second->allMatrix(result[0], result[1], result[2]);
    choiceWidget->show();
    emitResultChoice(D);
}
