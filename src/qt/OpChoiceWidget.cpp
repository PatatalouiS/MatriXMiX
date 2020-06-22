
#include "OpChoiceWidget.h"
#include <QRadioButton>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>

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
    QFont subFont("Arial");
    QComboBox* typeChoice = new QComboBox(this);
    subFont.setPointSize(14);
    opTypes->setFont(subFont);
    opTypes->setMaximumHeight(100);

    static const QList<QString> opTypesNames = {
        "Opérations Binaires",
        "Opérations Unaires",
        "Diagonalisation",
        "Décompositions",
        "Evaluation et Résolution"
    };

    typeChoice->addItems(opTypesNames);
    typeChoice->setCurrentIndex(static_cast<unsigned int>(OpType::BINARY_OP));
    opTypesLayout->addWidget(typeChoice);
    opTypes->setLayout(opTypesLayout);


    opList = new QGroupBox("Opérations :", this);
    opList->setFont(subFont);

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

    connect(typeChoice, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=](int index) -> void {
            setOperationsList(static_cast<OpType>(index));
            switch (index) {
                case 0 : emit opSelected(0); break;
                case 1 : emit opSelected(6); break;
                case 2 : emit opSelected(12); break;
                case 3 : emit opSelected(16); break;
                case 4 : emit opSelected(19); break;
                default : break;
            }
    });

    setFont(font);
    setOperationsList(OpType::BINARY_OP);
    setLayout(mainLayout);
    setMinimumWidth(250);
}

void OpChoiceWidget::setOperationsList(const OpType& type) {
    const static QString opNames [21] = {
        "Addition (A+B)",
        "Soustraction (A-B)",
        "Multiplication (A*B)",
        "Division (A/B)",
        "Multiplication (A*lambda)",
        "Puissance (A^n)",
        "Transposée",
        "Déterminant",
        "Trace",
        "Inverse",
        "Echelonnage",
        "Etudes des dimensions",
        "Polynôme caractéristique",
        "Valeurs/Vecteurs propres",
        "Diagonalisation dans R",
        "Diagonalisation dans C",
        "Décomposition LU",
        "Decomposition QR",
        "Décomposition Cholesky",
        "Evaluation d'expression",
        "Résolution de système"
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
            lastIndex = 12;
            break;
        }
        case OpType::DIAGONALISATION : {
            firstIndex = 12;
            lastIndex = 16;
            break;
        }
        case OpType::DECOMPOSITION : {
            firstIndex = 16;
            lastIndex = 19;
            break;
        }
        case OpType::EXPR_EVAL : {
            firstIndex = 19;
            lastIndex = 21;
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
        btn->setCursor(Qt::PointingHandCursor);
        btn->setStyleSheet(
                    "QPushButton {"
                        "background-color : white;"
                        "height : 30px;"
                        "border : 1px solid lightGrey;"
                        "border-radius : 4px;"
                    "}"
                    "QPushButton:hover {"
                        "background-color:rgb(90,122,228);"
                        "color : white;"
                    "}");

        connect(btn, &QPushButton::pressed, [this, i] () -> void {
            emit opSelected(i);
        });

        opListLayout->addWidget(btn);
    }

    opList->setLayout(opListLayout);
}
