
#include "DecompositionWidget.h"
#include <QVBoxLayout>
#include "Error.h"

#include <QDebug>

using namespace std;


DecompositionWidget::DecompositionWidget(const type type, const QMatrixLibrary* lib,
                QWidget* parent) : AbstractOperationWidget(lib, parent) {

    QString style = "QLabel {"
                        "background-color: rgb(243,243,243);"
                        "border-top-left-radius : 4px;"
                        "border-top-right-radius : 4px;"
                        "border : 1px solid lightGrey;"
                    "}";

    // Radio Button choices
    result1 = new QRadioButton("");
    result2 = new QRadioButton("");
    result1->setChecked(true);
    QHBoxLayout* choiceLayout = new QHBoxLayout;
    choiceLayout->addStretch(3);
    choiceLayout->addWidget(result1);
    choiceLayout->addStretch(2);
    choiceLayout->addWidget(result2);
    choiceLayout->addStretch(3);
    choiceLayout->setAlignment(Qt::AlignCenter);
    choiceWidget = new QWidget;
    choiceWidget->setLayout(choiceLayout);
    choiceWidget->hide();
    choiceWidget->setStyleSheet(".QWidget {"
                                    "background-color : lightGrey;"
                                    "border : 1px solid grey;"
                                "}");
    constructType(type);

    op.first = "_";
    op.second = nullptr;
    description->setText(op.first);

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

    resultAdder->hide();
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
