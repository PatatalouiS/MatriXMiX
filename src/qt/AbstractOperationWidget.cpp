

#include "AbstractOperationWidget.h"

#include <QVBoxLayout>


AbstractOperationWidget:: AbstractOperationWidget(const QMatrixLibrary* lib, QWidget* parent): QWidget (parent)
{
    this->lib = lib;
    sortFunction = [](const Matrix*){return true;};

    //QVBoxLayout* generalLayout = new QVBoxLayout;



    description = new QLabel(this);
    description->setStyleSheet("font-size: 40px");
    description->setAlignment(Qt::AlignCenter);

    //generalLayout->addWidget(title);

    title = new QLabel(this);
    title->setStyleSheet("font-size: 20px; font:bold;");
    title->setAlignment(Qt::AlignCenter);

    calculer = new QPushButton("Calculer", this);
    calculer->setCursor(Qt::PointingHandCursor);
    calculer->setStyleSheet("QPushButton{ background-color: lightGrey } "
                            "QPushButton:hover{ background-color: lightBlue }");
    calculer->setFixedSize(300,30);

    setStyleSheet("background-color:white;");

    //setLayout(generalLayout);

    connect(calculer, &QPushButton::clicked, this, &AbstractOperationWidget::computeOperation);
}



void AbstractOperationWidget:: setTitle (const QString& str)
{
    title->setText(str);
}


void AbstractOperationWidget:: setSortFunction(SortFunction&& s)
{
    this->sortFunction = s;
}


const QMatrixLibrary* AbstractOperationWidget:: getLib() const
{
    return lib;
}

