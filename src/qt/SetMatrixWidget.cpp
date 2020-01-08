
#include <QFormLayout>
#include <cmath>
#include "SetMatrixWidget.h"
#include "Error.h"


SetMatrixWidget::SetMatrixWidget(const enum type& t, MatrixLibrary* library, QWidget* parent)
: QWidget(parent)
{
    this->library = library;
    type = t;
    selectedMatrix = QPair<QString, Matrix*> ("", nullptr);

    nameMatrix = new QLineEdit;
    QRegExpValidator* regex = new QRegExpValidator(QRegExp("[a-zA-Z0-9]+"), nameMatrix);
    nameMatrix->setValidator(regex);
    nameMatrix->setMaxLength(20);
    nameMatrix->setFixedSize(75,35);

    nbRowsSelector = new QSpinBox;
    nbColsSelector = new QSpinBox;
    QString styleButton = "QSpinBox{border: 1px solid grey; border-radius: 3px; font-size: 15px;}"
                          "QSpinBox::down-button{width: 20px; background:"
                          "qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 lightBlue, stop: 1 blue);}"
                          "QSpinBox::down-arrow{ image: url(:/img/minus.png); width: 12px; height: 30px;}"
                          "QSpinBox::up-button{width: 20px; background:"
                          "qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 lightBlue, stop: 1 blue)}"
                          "QSpinBox::up-arrow { image: url(:/img/plus.png); width: 35px; height:35px;}";

    nbRowsSelector->setRange(2,10);
    nbColsSelector->setRange(2,10);
    nbRowsSelector->setFixedSize(75,35);
    nbColsSelector->setFixedSize(75,35);
    nbRowsSelector->setStyleSheet(styleButton);
    nbColsSelector->setStyleSheet(styleButton);
    nbRowsSelector->setButtonSymbols(QAbstractSpinBox::PlusMinus);
    nbColsSelector->setButtonSymbols(QAbstractSpinBox::PlusMinus);
    nbRowsSelector->setAlignment(Qt::AlignHCenter);
    nbColsSelector->setAlignment(Qt::AlignHCenter);
    nbRowsSelector->setValue(3);
    nbColsSelector->setValue(3);

    QFormLayout* setSpecsLayout = new QFormLayout;
    setSpecsLayout->addRow(tr("Nom Matrice : "), nameMatrix);
    setSpecsLayout->addRow(tr("Nombre de Lignes : "), nbRowsSelector);
    setSpecsLayout->addRow(tr("Nombre de Collones :"), nbColsSelector);
    setSpecsLayout->setFormAlignment(Qt::AlignCenter);
    QWidget* setSpecsWidget = new QWidget;
    setSpecsWidget->setLayout(setSpecsLayout);

    lineEditsLayout = new QGridLayout;
    lineEditsLayout->setVerticalSpacing(15);
    lineEditsLayout->setAlignment( Qt::AlignCenter | Qt::AlignVCenter);

    QLineEdit* temp = nullptr;
    for(unsigned int i = 0; i < 9; ++i)
    {
        temp = new QLineEdit();
        temp->setMinimumWidth(30);
        temp->setMaximumWidth(50);
        temp->setMaxLength(8);
        temp->setValidator(new QDoubleValidator(temp));
        lineEditsTab.append(temp);
        lineEditsLayout->addWidget(temp, i/3, i%3);
    }

    lrows = 3;
    lcols = 3;

    QWidget* lineEditsWidget = new QWidget;
    lineEditsWidget->setLayout(lineEditsLayout);
    lineEditsWidget->setMinimumSize(700, 350);

    compute = new QPushButton;
    QVBoxLayout* mainLayout = new QVBoxLayout;

    compute->setStyleSheet("QPushButton:hover{ background-color: lightBlue }");
    compute->setCursor(Qt::PointingHandCursor);
    compute->setMinimumSize(250,30);
    compute->setToolTip("Ajouter cette matrice à la librairie");

    QVBoxLayout* buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(compute);
    buttonLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    mainLayout->addWidget(setSpecsWidget);
    mainLayout->addWidget(lineEditsWidget);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    constructType(t);

    connect(nbRowsSelector, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &SetMatrixWidget::updateLineEdits);
    connect(nbColsSelector, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &SetMatrixWidget::updateLineEdits);
    connect(compute, &QPushButton::pressed, this, &SetMatrixWidget::computeMatrix);
}



void SetMatrixWidget::constructType(const enum type &t)
{
    if(t == ADD)
    {
        compute->setText("Ajouter");
    }
    else
    {
        compute->setText("Modifier");
        nameMatrix->setEnabled(false);
        nameMatrix->setReadOnly(true);
    }
}



void SetMatrixWidget:: computeMatrix ()
{
    if(!controlKeyboardInput())
    {
        return;
    }

    VectorX values;
    QString currentValue;
    QString name = nameMatrix->text();
    unsigned int nbL = unsigned(nbRowsSelector->value());
    unsigned int nbC = unsigned(nbColsSelector->value());

    for(auto& i : lineEditsTab)
    {
        currentValue = i->text().replace(QLatin1Char(','), QLatin1Char('.'));
        values.push_back(currentValue.toDouble());
    }

    Matrix newMatrix (nbL, nbC, values);

    if(type == ADD)
    {
        library->addMatrix(name.toStdString(), newMatrix);
        emit newMatrixAdded(QPair<QString, Matrix&>(name, newMatrix));
    }
    else
    {
        *selectedMatrix.second = newMatrix;
        emit matrixEdited(QPair<QString, Matrix&>(name, newMatrix));
        nameMatrix->setText("");
        selectedMatrix.first = "";
        selectedMatrix.second = nullptr;
    }
}



bool SetMatrixWidget:: controlKeyboardInput() const
{
    QString name = this->nameMatrix->text();

    if(type == ADD)
    {
        if(library->find(name.toStdString()))
        {
            Error::showError("La Matrice " + name + " existe déjà !",
                       "Veuillez changer de nom.");
            return false;
        }

        if(!nameMatrix->hasAcceptableInput())
        {
            if((name[0] >= '0') || (name[0] <= '9'))
            Error::showError("Nom de Matrice " + name + " non valide !",
                       "Veuillez saisir 10 caractère Maximum, sans caractères spéciaux ni espaces ");
            return false;
        }
    }
    else
    {
        if(selectedMatrix.second == nullptr)
        {
            Error::showError("Erreur !", "Vous devez d'abord sélectionner la matrice à éditer.");
            return false;
        }
    }

    for(const auto& i : lineEditsTab)
    {
        if (!i->hasAcceptableInput())
        {
            Error::showError("Les valeurs de votre Matrice " + name + " sont incorrectes !",
                       "Vérifiez votre saisie. Chaque coefficient doit être un nombre Réel.");
            return false;
        }
    }

    return true;
}


void SetMatrixWidget:: chargeMatrix(const QString& name)
{
    assert(library->exist(name.toStdString()));
    selectedMatrix.first = name;
    selectedMatrix.second = library->find(name.toStdString());
    Matrix temp = *selectedMatrix.second;

    unsigned int nbRows = temp.getNbRows();
    unsigned int nbCols = temp.getNbCols();
    nameMatrix->setText(name);
    nbRowsSelector->setValue(int(nbRows));
    nbColsSelector->setValue(int(nbCols));

    QString valueToString;
    double val;
    for(unsigned int i = 0; i < nbRows*nbCols; ++i)
    {
        val = temp[i/nbCols][i%nbCols];
        if(floor(val) == val)
        {
            valueToString.setNum(val, 'f', 0);
        }
        else
        {
            valueToString.setNum(val, 'f', 10)
                    .replace('.', ',');
        }
        lineEditsTab[int(i)]->setText(valueToString);
    }
}



void SetMatrixWidget:: updateSelectedMatrix()
{
    if(!library->exist(selectedMatrix.first.toStdString()))
    {
        selectedMatrix.first = "";
        selectedMatrix.second = nullptr;
        nameMatrix->setText("");
        nbRowsSelector->setValue(3);
        nbColsSelector->setValue(3);
        for(auto i : lineEditsTab)
        {
            i->setText("");
        }
    }
    else
    {
        chargeMatrix(selectedMatrix.first);
    }
}



void SetMatrixWidget:: updateLineEdits ()
{
    unsigned int newNbRows = static_cast<unsigned>(nbRowsSelector->value());
    unsigned int newNbCols = static_cast<unsigned>(nbColsSelector->value());

    int diffRows = static_cast<int>(newNbRows - lrows);
    int diffCols = static_cast<int>(newNbCols - lcols);

    QLineEdit* temp;

    if(diffRows > 0)
    {
        for(int newRow = 0; newRow < diffRows; newRow++)
        {
            for(unsigned int i = 0; i < lcols; ++i )
            {
                temp = new QLineEdit;
                temp->setMinimumWidth(30);
                temp->setMaximumWidth(50);
                temp->setMaxLength(8);
                temp->setValidator(new QDoubleValidator(temp));
                lineEditsTab.append(temp);
                lineEditsLayout->addWidget(temp, int(lrows), int(i));
            }
            lrows++;
        }
    }
    else if(diffCols > 0)
    {
        for(int newCol = 0; newCol < diffCols; newCol++)
        {
            for(unsigned int i = 0; i < lrows; ++i )
            {
                temp = new QLineEdit;
                temp->setMinimumWidth(30);
                temp->setMaximumWidth(50);
                lineEditsTab.insert(int(lcols+1)*int(i)+int(lcols), temp);
                temp->setMaxLength(8);
                temp->setValidator(new QDoubleValidator(temp));
                lineEditsLayout->addWidget(temp, int(i), int(lcols));
                setTabOrder(lineEditsLayout->itemAtPosition(int(i), int(lcols-1))->widget(), temp);
            }
            lcols++;
        }
    }
    else if(diffRows < 0)
    {
        for(int removeRow = 0; removeRow < abs(diffRows); removeRow++)
        {
            for(unsigned int i = 0; i < lcols; ++i)
            {
                temp = dynamic_cast<QLineEdit*>(lineEditsLayout->itemAtPosition(int(lrows-1), int(i))->widget());
                lineEditsLayout->removeWidget(temp);
                lineEditsTab.removeOne(temp);
                temp->deleteLater();
            }
            lrows--;
        }
    }
    else
    {
        for(int removeCol = 0; removeCol < abs(diffCols); removeCol++)
        {
            for(unsigned int i = 0; i < lrows; ++i)
            {
                temp = dynamic_cast<QLineEdit*>(lineEditsLayout->itemAtPosition(int(i), int(lcols-1))->widget());
                lineEditsLayout->removeWidget(temp);
                lineEditsTab.removeOne(temp);
                temp->deleteLater();
            }
            lcols--;
        }
    }
}


SetMatrixWidget:: ~SetMatrixWidget ()
{
}
