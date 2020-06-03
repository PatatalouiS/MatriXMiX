
#include "ExprEvalWidget.h"
#include "Error.h"
#include <QVBoxLayout>



ExprEvalWidget::ExprEvalWidget(const QMatrixLibrary* lib, QWidget* parent) :
AbstractOperationWidget (lib, parent)
{
    result = Matrix();
    setTitle("Evaluation d'expression");

    view = new MatrixViewWidget(lib, this);

    QVBoxLayout* subLayout1 = new QVBoxLayout;
    subLayout1->addWidget(title);
    subLayout1->addWidget(view);
    subLayout1->setAlignment(Qt::AlignCenter);

    QLabel* titleExpr = new QLabel("Insérer votre expression : ");
    QLabel* title2 = new QLabel("Pour calculer l'inverse d'une matrice utiliser: A~");
    title2->setStyleSheet("color:grey;");
    titleExpr->setAlignment(Qt::AlignBottom |Qt::AlignCenter);

    expression = new QLineEdit();
    expression->setMaximumSize(400, 40);
    expression->setPlaceholderText("Ex: A+B*C/D");

    QVBoxLayout* buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(calculer);
    buttonLayout->setAlignment(Qt::AlignCenter);

    QVBoxLayout* subLayout2 = new QVBoxLayout;
    subLayout2->addWidget(titleExpr);
    subLayout2->addWidget(expression);
    subLayout2->addWidget(title2);
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

    view->refresh(sortFunction);
    setLayout(mainLayout);
}


void ExprEvalWidget:: updateViews()
{
    view->refresh();
}

void ExprEvalWidget:: computeOperation ()
{
    std::string testExpression = getLib()->isCalculableExpression(expression->text().toStdString());

    if(testExpression != "calculable")
    {
        Error::showError("Calcul d'expression impossible", QString::fromStdString(testExpression), this);
        return;
    }

    result = getLib()->calculateExpression(expression->text().toStdString());

    if(result == Matrix::matrix_null)
    {
        Error::showError("Calcul impossible", "Veuillez vérifier que le calcul demandé est réalisable", this);
        return ;
    }

    QVariant genericResult;
    genericResult.setValue(result);

    emit newResult(genericResult);
}


void ExprEvalWidget:: computeSelection(const bool view)
{
    (void)view;
}



