
#include "DecompositionWidget.h"
#include <QVBoxLayout>
#include "Error.h"

#include <QDebug>

using namespace std;


DecompositionWidget::DecompositionWidget(const type type, const QMatrixLibrary* lib,
                QWidget* parent) : AbstractOperationWidget(lib, parent) {

    result1 = new QRadioButton("");
    result2 = new QRadioButton("");
    result1->setChecked(true);

    constructType(type);

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

    QHBoxLayout* choiceLayout = new QHBoxLayout;
    choiceLayout->addWidget(result1);
    choiceLayout->addWidget(result2);

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

    connect(result1, &QRadioButton::clicked,
            [this]() -> void
            {
                emitResultChoice(0);
            });

    connect(result2, &QRadioButton::clicked,
            [this]() -> void
            {
                emitResultChoice(1);
            });

    view->refresh(sortFunction);
    setLayout(mainLayout);
}

void DecompositionWidget::constructType(const type t) {
    switch (t) {
        case LU :{
            setTitle("Décomposition LU");
            result1->setText("Matrice L");
            result2->setText("Matrice U");
            setSortFunction([](const Matrix* a) -> bool {
                return a->isPositiveDefinite() &&
                        a->isSQMatrix();
            });
            operation = [](const Matrix* a) -> pair<Matrix, Matrix> {
                return a->LUDecomposition();
            };
            break;
        }
        case QR :{
            setTitle("Décomposition QR");
            result1->setText("Matrice Q");
            result2->setText("Matrice R");
            setSortFunction([](const Matrix* a) -> bool {
                return a->getNbRows() >= a->getNbCols();
            });
            operation = [](const Matrix* a) -> pair<Matrix, Matrix> {
                return a->QR_Householder();
            };
            break;
        }
        case CHOLESKY:{
            setTitle("Décomposition Cholesky");
            result1->setText("Matrice C");
            result2->setText("Matrice C*");
            setSortFunction([](const Matrix* a) -> bool {
                return a->isSQMatrix() &&
                        a->isSQMatrix() &&
                        a->isPositiveDefinite();
            });
            operation = [](const Matrix* a) -> pair<Matrix, Matrix> {
                return a->cholesky();
            };
            break;
        }
    }
}


void DecompositionWidget::updateViews() {
    view->refresh(sortFunction);
}


void DecompositionWidget::computeSelection(const bool viewID) {
    (void)viewID;

    choiceWidget->hide();
    op.first = view->nameOfSelectedMatrix();
    assert(getLib()->exist(op.first));
    op.second = getLib()->find(op.first);
    description->setText(op.first);
}

void DecompositionWidget::computeOperation() {
    if(op.second == nullptr)
    {
        Error::showError("opérande Manquante !",
                         "Veuillez bien sélectionner votre matrice !", this);
        return;
    }

    result = operation(op.second);
    choiceWidget->show();
    emitResultChoice(0);
}

void DecompositionWidget::emitResultChoice(const unsigned int choice) {
    QVariant genericResult;
    genericResult.setValue(choice ? result.second : result.first);
    emit newResult(genericResult);
}
