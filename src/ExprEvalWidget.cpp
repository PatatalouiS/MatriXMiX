
#include "ExprEvalWidget.h"
#include "Error.h"
#include <QVBoxLayout>



ExprEvalWidget::ExprEvalWidget(const MatrixLibrary* lib, QWidget* parent) :
AbstractOperationWidget (lib, parent)
{
    result = Matrix();
    setTitle("Evaluation d'expression");

    view = new MatrixViewWidget(lib, this);
    view->setFixedSize(200, 200);

    QVBoxLayout* subLayout1 = new QVBoxLayout;
    subLayout1->addWidget(title);
    subLayout1->addWidget(view);

    QWidget* subWidget1 = new QWidget(this);
    subWidget1->setLayout(subLayout1);

    expression = new QLineEdit();
    expression->setMinimumSize(200, 30);

    QVBoxLayout* buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(calculer);
    buttonLayout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);
    mainLayout->addWidget(subWidget1);
    mainLayout->addWidget(expression);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    view->refresh(sortFunction);
    setLayout(mainLayout);
}


void ExprEvalWidget:: updateViews()
{

}



void ExprEvalWidget:: computeOperation ()
{
    MatrixLibrary* temp = const_cast <MatrixLibrary*>(lib);

    std::string testExpression = temp->isCalculableExpression(expression->text().toStdString());

    if(testExpression != "calculable")
    {
        Error::showError("Calcul d'expression impossible", QString::fromStdString(testExpression), this);
        return;
    }

    result = temp->expressionCalcul(expression->text().toStdString());

    QVariant genericResult;
    genericResult.setValue(result);

    emit newResult(genericResult);
}


void ExprEvalWidget:: computeSelection(bool view)
{
    (void)view;
}



