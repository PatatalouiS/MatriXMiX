
#include "ResultAdderWidget.h"
#include "Error.h"

#include <QHBoxLayout>
#include <QRegExpValidator>

Q_DECLARE_METATYPE(Matrix);

ResultAdderWidget::ResultAdderWidget(QMatrixLibrary* lib, QWidget* parent) :
                                        QWidget(parent), library(lib) {
    QHBoxLayout* resultAdder = new QHBoxLayout;
    adderName = new QLineEdit;
    QRegExpValidator* regex = new QRegExpValidator(QRegExp("[a-zA-Z0-9]+"),
                                                   adderName);
    adderName->setValidator(regex);
    adderName->setFixedHeight(30);
    adderName->setMaximumWidth(60);
    adderName->setStyleSheet("QLineEdit {"
                                "border : 1px solid lightGrey;"
                             "}");
    adderBtn = new QPushButton("");
    adderBtn->setFixedHeight(30);
    adderBtn->setMaximumWidth(200);

    resultAdder->addWidget(adderName);
    resultAdder->addWidget(adderBtn);
    resultAdder->setContentsMargins(0,0,0,0);

    connect(adderBtn, &QPushButton::pressed,
            this, &ResultAdderWidget::addResult);

    setLayout(resultAdder);
}

void ResultAdderWidget::showAndLoadResult(const QVariant& res) {
    if(res.canConvert<Matrix>()) {
        show();
        result = res.value<Matrix>();

        adderBtn->setText("Ajouter le résultat");
        adderBtn->setStyleSheet("QPushButton{ "
                                "background-color:rgba(209,47,47, 90);"
                                "border-radius : 4px;"
                            "}"
                            "QPushButton:hover{ "
                                "background-color: lightBlue ;"
                            "}");
    }
}

void ResultAdderWidget::addResult() {
    QString name = adderName->text();

    if(!adderName->hasAcceptableInput()) {
        if((name[0] >= '0') || (name[0] <= '9'))
        Error::showError("Nom de Matrice " + name + " non valide !",
                   "Veuillez saisir 10 caractère Maximum, sans caractères spéciaux ni espaces ");
        return;
    }
    if(library->find(name))
    {
        Error::showError("La Matrice " + name + " existe déjà !",
                   "Veuillez changer de nom.");
        return;
    }

    library->addMatrix(name, result);

    emit newMatrixAdded();

    adderBtn->setText("Ajout effectué");

    adderBtn->setStyleSheet("QPushButton{ "
                                "background-color:rgba(0,200,0, 90);"
                                "border-radius : 4px;"
                            "}"
                            "QPushButton:hover{ "
                                "background-color: lightBlue ;"
                            "}");
    adderName->setText("");
}


