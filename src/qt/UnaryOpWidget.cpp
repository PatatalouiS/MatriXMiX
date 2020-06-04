
#include <QVBoxLayout>
#include "UnaryOpWidget.h"
#include "MatrixViewWidget.h"
#include "Error.h"

UnaryOpWidget::UnaryOpWidget(const type& t, const QMatrixLibrary* lib, QWidget* parent) :
AbstractOperationWidget(lib, parent)
{
    QString style = "QLabel {"
                        "background-color: rgb(243,243,243);"
                        "border-top-left-radius : 4px;"
                        "border-top-right-radius : 4px;"
                        "border : 1px solid lightGrey;"
                    "}";

    result.setValue(nullptr);
    op.first = "_";
    op.second = nullptr;
    description->setText(op.first);

    constructType(t);

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

    QHBoxLayout* subLayout = new QHBoxLayout;
    subLayout->addStretch(3);
    subLayout->addLayout(op1ChoiceLayout);
    subLayout->addStretch(2);
    subLayout->addLayout(rightLayout);
    subLayout->addStretch(3);
    subLayout->setAlignment(Qt::AlignCenter);
    subLayout->setContentsMargins(20,20,20,20);
    subLayout->setSpacing(0);

    mainWidget->setLayout(subLayout);

    connect(view, &MatrixViewWidget::clicked,
            [this] () -> void
            {
                this->computeSelection(0);
            });

    view->refresh(sortFunction);
}


void UnaryOpWidget:: updateViews()
{
    view->refresh(sortFunction);
}



void UnaryOpWidget:: computeOperation()
{
    if(op.second == nullptr)
    {
        Error::showError("opérande Manquante !", "Veuillez bien sélectionner votre Matrice !", this);
        return;
    }

    result.setValue(operation(op));
    emit newResult(result);
}



void UnaryOpWidget:: computeSelection(const bool viewId)
{
    (void)viewId;
    resultAdder->hide();
    op.first = view->nameOfSelectedMatrix();
    assert(getLib()->exist(op.first));
    op.second = getLib()->find(op.first);
    description->setText(op.first);
}


void UnaryOpWidget:: constructType(const type &t)
{
    switch (t)
    {
        case DETERMINANT:
        {
            sortFunction = [](const Matrix* a) -> bool
            {
                return a->isSQMatrix();
            };
            setTitle("Determinant");
            operation = [](MatrixPair a) -> QVariant
            {
                DoubleResult res(a.first, a.second->determinant());
                QVariant resv;
                resv.setValue(res);
                return resv;
            };

            break;
        }
        case TRACE:
        {
            sortFunction = [](const Matrix* a) -> bool
            {
                return a->isSQMatrix();
            };
            setTitle("Trace");
            operation = [](MatrixPair a) -> QVariant
            {
                DoubleResult res(a.first, a.second->trace());
                QVariant resv;
                resv.setValue(res);
                return resv;
            };

            break;
        }
        case INVERSE:
        {
            setTitle("Inverse");
            operation = [](MatrixPair a) -> QVariant
            {
                QVariant resv;
                resv.setValue(Matrix(a.second->inverse()));
                return resv;
            };
            setSortFunction([](const Matrix* a) -> bool
            {
                return a->isSQMatrix() && (a->determinant() != 0.0);
            });

            break;
        }
        case ROW_REDUCED_FORM:
        {
            setTitle("Echelonnage");
            operation = [](MatrixPair a) -> QVariant
            {
                QVariant resv;
                resv.setValue(Matrix(a.second->gaussReduction()));
                return resv;
            };

            break;
        }
        case EIGEN_PROPERTIES:
        {
            sortFunction = [](const Matrix* a) -> bool
            {
                return a->isSQMatrix() && a->isDiagonalisableR();
            };
            setTitle("Valeurs / Vecteurs Propres");
            operation = [](MatrixPair a) -> QVariant
            {
                QVariant resv;
                resv.setValue(EigenResult(a.first, a.second->allEigen()));
                return resv;
            };

            break;
        }
        case CARACTERISTIC_POLYNOMIAL:
        {
            sortFunction = [](const Matrix* a) -> bool
            {
                return a->isSQMatrix() && a->isDiagonalisableR();
            };
            setTitle("Polynome Caractéristique");
            operation = [](MatrixPair a) -> QVariant
            {
                QVariant resv;
                resv.setValue(PolynomialResult(a.first, a.second->characteristicPolynomial(),
                                               a.second->splitCharacteristicPolynomial()));
                return resv;
            };

            break;
        }
        case KER_IMG_DIM:
        {
            setTitle("DimKer et Rang");
            operation = [](MatrixPair a) -> QVariant
            {
                QVariant resv;
                resv.setValue(KerImgDimResult(a.first, a.second->dimensionsStudy()));
                return resv;
            };
            break;
        }
        case TRANSPOSE:
        {
            setTitle("Matrice Transposée");
            operation = [](MatrixPair a) -> QVariant
            {
                QVariant resv;
                resv.setValue(Matrix(a.second->transposeMatrix()));
                return resv;
            };
            break;
        }
    }
}
