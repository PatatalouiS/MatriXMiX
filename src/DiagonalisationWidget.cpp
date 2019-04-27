
#include "DiagonalisationWidget.h"
#include "Error.h"
#include <QVBoxLayout>
#include <QRadioButton>



DiagonalisationWidget::DiagonalisationWidget(const MatrixLibrary* lib, QWidget* parent):
AbstractOperationWidget (lib, parent)
{
    result = std::array<Matrix,3>();
    op.first = "_";
    op.second = nullptr;

    setTitle("Diagonalisation");

    setSortFunction([](const Matrix* a) -> bool
    {
        return a->isDiagonalisable();
    });

    QVBoxLayout* op1ChoiceLayout = new QVBoxLayout;
    QLabel* op1Title = new QLabel("Choix de la matrice : ");
    view = new MatrixViewWidget(lib, this);
    //view->setFixedSize(200, 200);
    op1ChoiceLayout->addWidget(op1Title);
    op1ChoiceLayout->addWidget(view);

    QHBoxLayout* formLayout = new QHBoxLayout;
    formLayout->addLayout(op1ChoiceLayout);

    description->setText(op.first);

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

    QVBoxLayout* subLayout1 = new QVBoxLayout;
    subLayout1->addWidget(title);
    subLayout1->addLayout(formLayout);
    subLayout1->addWidget(description);
    QWidget* subWidget1 = new QWidget(this);
    subWidget1->setLayout(subLayout1);
    subWidget1->setFixedHeight(400);

    QVBoxLayout* buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(calculer);
    buttonLayout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);
    mainLayout->addWidget(subWidget1);
    mainLayout->addWidget(choiceWidget);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    connect(view, &MatrixViewWidget::clicked,
            [this] () -> void
            {
                this->computeSelection();
            });

    connect(showP, &QRadioButton::clicked,
            [this]() -> void
            {
                this->emitResultChoice(P);
            });

    connect(showD, &QRadioButton::clicked,
            [this]() -> void
            {
                this->emitResultChoice(D);
            });

    connect(showPInverse, &QRadioButton::clicked,
            [this]() -> void
            {
                this->emitResultChoice(P_INVERSE);
            });

    view->refresh(sortFunction);
    setLayout(mainLayout);
}



void DiagonalisationWidget:: emitResultChoice(const ResultChoice& c)
{
    QVariant genericResult;
    genericResult.setValue(result[c]);
    emit newResult(genericResult);
}



void DiagonalisationWidget::updateViews()
{

}



void DiagonalisationWidget:: computeSelection(bool viewID)
{
    (void)viewID;

    choiceWidget->hide();
    int selectedRow;
    selectedRow = view->currentIndex().row();
    op.first = view->model()->item(selectedRow)->data(2).toString();
    op.second = lib->find(op.first.toStdString());
    description->setText(op.first);
}


void DiagonalisationWidget:: computeOperation()
{
    if(op.second == nullptr)
    {
        showError("opérande Manquante !", "Veuillez bien sélectionner votre Matrice !", this);
    }

    op.second->allMatrix(result[0], result[1], result[2]);
    choiceWidget->show();
    emitResultChoice(D);
}


