
#include <QVBoxLayout>
#include "UnaryOpWidget.h"
#include "MatrixViewWidget.h"
#include "Error.h"



UnaryOpWidget::UnaryOpWidget(const type& t, const MatrixLibrary* lib, QWidget* parent) :
AbstractOperationWidget(lib, parent)
{
    result.setValue(nullptr);
    op.first = "_";
    op.second = nullptr;
    sortFunction = [](const Matrix* a)->bool
    {
        return a->isSQMatrix();
    };

    constructType(t);

    QVBoxLayout* op1ChoiceLayout = new QVBoxLayout;
    QLabel* op1Title = new QLabel("Choix de la matrice : ");
    view = new MatrixViewWidget(lib, this);
    view->setFixedSize(200, 200);
    op1ChoiceLayout->addWidget(op1Title);
    op1ChoiceLayout->addWidget(view);

    QHBoxLayout* formLayout = new QHBoxLayout;
    formLayout->addLayout(op1ChoiceLayout);

    description->setText(op.first);

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
    mainLayout->addLayout(buttonLayout);
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
    view->refresh();
    view->refresh(sortFunction);
}



void UnaryOpWidget:: computeOperation()
{
    if(op.second == nullptr)
    {
        Error::showError("opérande Manquante !", "Veuillez bien sélectionner votre Matrice !", this);
    }

    result.setValue(operation(op));
    emit newResult(result);
}



void UnaryOpWidget:: computeSelection(bool viewId)
{
    (void)viewId;
    op.first = view->nameOfSelectedMatrix();
    assert(lib->exist(op.first.toStdString()));
    op.second = lib->find(op.first.toStdString());
    description->setText(op.first);
}


void UnaryOpWidget:: constructType(const type &t)
{
    switch (t)
    {
        case DETERMINANT:
        {
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








