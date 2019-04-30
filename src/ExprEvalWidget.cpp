
#include "ExprEvalWidget.h"
#include <QVBoxLayout>



ExprEvalWidget::ExprEvalWidget(const MatrixLibrary* lib, QWidget* parent) :
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
    subLayout2->addLayout(buttonLayout);

    QHBoxLayout* subLayout3 = new QHBoxLayout;
    subLayout3->addLayout(subLayout1);
    subLayout3->addLayout(subLayout2);

    QWidget* subWidget1 = new QWidget(this);
    subWidget1->setLayout(subLayout3);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);
    mainLayout->addWidget(subWidget1);
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

    result = temp->expressionCalcul(expression->text().toStdString());

    QVariant genericResult;
    genericResult.setValue(result);

    emit newResult(genericResult);
}


void ExprEvalWidget:: computeSelection(bool view)
{

}



