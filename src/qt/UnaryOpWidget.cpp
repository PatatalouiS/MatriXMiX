
#include <QVBoxLayout>
#include "UnaryOpWidget.h"
#include "MatrixViewWidget.h"
#include "Error.h"


UnaryOpWidget::UnaryOpWidget(const type& t, const QMatrixLibrary* lib, QWidget* parent) :
AbstractOperationWidget(lib, parent)
{
    result.setValue(nullptr);
    op.first = "_";
    op.second = nullptr;

    constructType(t);

    QVBoxLayout* op1ChoiceLayout = new QVBoxLayout;
    QLabel* op1Title = new QLabel("Choix de la matrice : ");
    op1Title -> setAlignment(Qt::AlignCenter);
    view = new MatrixViewWidget(lib, this);
    op1ChoiceLayout->addWidget(op1Title);
    op1ChoiceLayout->addWidget(view);

    QHBoxLayout* formLayout = new QHBoxLayout;
    formLayout->addLayout(op1ChoiceLayout);
    formLayout->setAlignment(Qt::AlignCenter);

    QVBoxLayout* buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(calculer);
    buttonLayout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

    description->setText(op.first);

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
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);


    connect(view, &MatrixViewWidget::clicked,
            [this] () -> void
            {
                this->computeSelection(0);
            });

    view->refresh(sortFunction);
    setLayout(mainLayout);
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
    op.first = view->nameOfSelectedMatrix();
    assert(getLib()->exist(op.first.toStdString()));
    op.second = getLib()->find_matrix(op.first.toStdString());
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
                DoubleResult res(a.first, a.second->traceMatrix());
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
            setTitle("PolynomeCaractéristique");
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
    }
}








