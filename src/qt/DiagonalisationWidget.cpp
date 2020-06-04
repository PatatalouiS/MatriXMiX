
#include "DiagonalisationWidget.h"
#include "Error.h"
#include <QVBoxLayout>
#include <QRadioButton>


DiagonalisationWidget::DiagonalisationWidget(const type t, const QMatrixLibrary* lib, QWidget* parent):
AbstractOperationWidget (lib, parent)
{
    QString style = "QLabel {"
                        "background-color: rgb(243,243,243);"
                        "border-top-left-radius : 4px;"
                        "border-top-right-radius : 4px;"
                        "border : 1px solid lightGrey;"
                    "}";

    constructType(t);

    result = std::array<Matrix,3>();
    op.first = "_";
    op.second = nullptr;
    description->setText(op.first);

    QRadioButton* resultP = new QRadioButton("Matrice P");
    QRadioButton* resultD = new QRadioButton("Matrice D");
    QRadioButton* resultPInverse = new QRadioButton("Matrice P^-1");
    resultD->setChecked(true);
    QHBoxLayout* choiceLayout = new QHBoxLayout;
    choiceLayout->addStretch(3);
    choiceLayout->addWidget(resultP);
    choiceLayout->addStretch(2);
    choiceLayout->addWidget(resultD);
    choiceLayout->addStretch(2);
    choiceLayout->addWidget(resultPInverse);
    choiceLayout->addStretch(3);
    choiceLayout->setAlignment(Qt::AlignCenter);
    choiceWidget = new QWidget;
    choiceWidget->setLayout(choiceLayout);
    choiceWidget->setStyleSheet(".QWidget {"
                                    "background-color : lightGrey;"
                                    "border : 1px solid grey;"
                                "}");
    choiceWidget->hide();

    QVBoxLayout* op1ChoiceLayout = new QVBoxLayout;
    QLabel* op1Title = new QLabel("Choix de la matrice : ");
    op1Title -> setAlignment(Qt::AlignCenter);
    op1Title->setStyleSheet(style);
    view = new MatrixViewWidget(lib, this);
    view->setMaximumWidth(300);
    op1ChoiceLayout->addWidget(op1Title);
    op1ChoiceLayout->addWidget(view);
    op1ChoiceLayout->setSpacing(0);
    op1ChoiceLayout->setAlignment(Qt::AlignCenter);

    QVBoxLayout* rightLayout = new QVBoxLayout;
    rightLayout->addWidget(description);
    rightLayout->addWidget(calculer);
    rightLayout->addWidget(resultAdder);
    rightLayout->setSpacing(15);
    rightLayout->setAlignment(Qt::AlignCenter);

    QHBoxLayout* centerLayout = new QHBoxLayout;
    centerLayout->addStretch(3);
    centerLayout->addLayout(op1ChoiceLayout);
    centerLayout->addStretch(2);
    centerLayout->addLayout(rightLayout);
    centerLayout->addStretch(3);
    centerLayout->setAlignment(Qt::AlignCenter);
    centerLayout->setContentsMargins(0, 20, 0, 20);

    QVBoxLayout* subLayout = new QVBoxLayout;
    subLayout->addLayout(centerLayout);
    subLayout->addWidget(choiceWidget);
    subLayout->setAlignment(Qt::AlignCenter);
    subLayout->setContentsMargins(0,0,0,0);
    subLayout->setSpacing(0);

    mainWidget->setLayout(subLayout);

    connect(view, &MatrixViewWidget::clicked,
            [this] () -> void
            {
                computeSelection();
            });

    connect(resultP, &QRadioButton::clicked,
            [this]() -> void
            {
                emitResultChoice(P);
            });

    connect(resultD, &QRadioButton::clicked,
            [this]() -> void
            {
                emitResultChoice(D);
            });

    connect(resultPInverse, &QRadioButton::clicked,
            [this]() -> void
            {
                emitResultChoice(P_INVERSE);
            });

    view->refresh(sortFunction);
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

    resultAdder->hide();
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
