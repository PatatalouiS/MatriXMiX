
#include "OpChoiceWidget.h"
#include <QRadioButton>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

OpChoiceWidget::OpChoiceWidget(QWidget* parent) : QWidget(parent)
{
    QFont font ("Arial");
    font.setPointSize(16);

    opListLayout = nullptr;

    QVBoxLayout* mainLayout = new QVBoxLayout;
    QLabel* title = new QLabel("Menu", this);
    title->setFixedHeight(40);
    title->setContentsMargins(30, 0, 30, 0);
    title->setStyleSheet("QLabel{"
                             "background-color : lightGrey;"
                             "border-top-left-radius : 5px;"
                             "border-top-right-radius : 5px;"
                             "border : 1px solid grey;"
                         "}");
    title->setAlignment(Qt::AlignCenter);
    title->setFont(font);

    QVBoxLayout* opTypesLayout = new QVBoxLayout;
    QGroupBox* opTypes = new QGroupBox("Type d'opération :", this);
    QFont fontUnderline("Arial");
    fontUnderline.setPointSize(14);
    opTypes->setFont(fontUnderline);

    static const QString opTypesNames[4] = {
        "Opérations binaires",
        "Opération unaires",
        "Diagonalisation",
        "Décompositions"
    };

    for(unsigned int i = 0; i < 4; ++i) {
        QRadioButton* btn = new QRadioButton(opTypesNames[i], this);

        if(i == 0) {
            btn->setChecked(true);
        }

        connect(btn, &QRadioButton::clicked, [this, i]() -> void {
                   setOperationsList(OpType(i));
                });

        opTypesLayout->addWidget(btn);
    }

    opTypes->setLayout(opTypesLayout);



    opList = new QGroupBox("Opérations :", this);
    opList->setFont(fontUnderline);

    QWidget* menu = new QWidget(this);
    menu->setStyleSheet(".QWidget{"
                            "background-color : white;"
                            "border-bottom-left-radius : 5px;"
                            "border-bottom-right-radius : 5px;"
                            "border-left : 1px solid grey;"
                            "border-bottom : 1px solid grey;"
                            "border-right : 1px solid grey;"
                        "}"
                        "QGroupBox { "
                              "border: 1px solid silver;"
                              "background-color:rgb(243,243,243);"
                              "border-radius: 5px;"
                              "margin-top: 15px; }"
                              "QGroupBox::title { subcontrol-origin:margin;"
                              "margin-top : 5px;"
                              "background-color:rgb(235,235,235) ;"
                              "border : 1px solid grey;"
                              "border-radius : 5px;"
                              "subcontrol-position: top;"
                              "font: bold ; color: black;"
                        "}");

    QVBoxLayout* menuLayout = new QVBoxLayout;
    menuLayout->addWidget(opTypes);
    menuLayout->addWidget(opList);
    menu->setLayout(menuLayout);

    mainLayout->addWidget(title);
    mainLayout->addWidget(menu);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    setFont(font);
    setOperationsList(OpType::BINARY_OP);
    setLayout(mainLayout);
    setMinimumWidth(250);
}


void OpChoiceWidget::setOperationsList(const OpType& type) {
    const static QString opNames [15] = {
        "Addition (A+B)",
        "Soustraction (A-B)",
        "Multiplication (A*B)",
        "Division (A/B)",
        "Multiplication (A*lambda)",
        "Puissance (A^n)",
        "Déterminant",
        "Trace",
        "Inverse",
        "Echelonnage",
        "Etudes des dimensions",
        "Polynôme caractéristique",
        "Valeurs/Vecteurs propres",
        "Diagonalisation",
        "Evaluation d'expression",
    };

    unsigned int firstIndex;
    unsigned int lastIndex;

    switch(type) {
        case OpType::BINARY_OP : {
            firstIndex = 0;
            lastIndex = 6;
            break;
        }
        case OpType::UNARY_OP : {
            firstIndex = 6;
            lastIndex = 11;
            break;
        }
        case OpType::DIAGONALISATION : {
            firstIndex = 11;
            lastIndex = 15;
            break;
        }
        case OpType::DECOMPOSITION : {
            firstIndex = 0;
            lastIndex = 0;
            break;
        }
    }

    if(opListLayout != nullptr) {
        opListLayout->deleteLater();
        qDeleteAll(opList->children());
    }

    opListLayout = new QVBoxLayout;

    for(unsigned int i = firstIndex; i < lastIndex; ++i) {
        QPushButton* btn = new QPushButton(opNames[i], this);

        connect(btn, &QPushButton::pressed, [this, i] () -> void {
            emit opSelected(i);
        });

        opListLayout->addWidget(btn);
    }

    opList->setLayout(opListLayout);
}
