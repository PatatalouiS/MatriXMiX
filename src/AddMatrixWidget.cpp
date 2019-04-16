
#include <QFormLayout>
#include <QPushButton>
#include <QMessageBox>
#include "LibraryWindow.h"
#include "AddMatrixWidget.h"


AddMatrixWidget::AddMatrixWidget(QWidget *parent) : QWidget(parent)
{
}


AddMatrixWidget::AddMatrixWidget(MatrixLibrary* library, QWidget* parent)
: QWidget(parent)
{
    this->library = library;

    nameMatrix = new QLineEdit;
    QRegExpValidator* regex = new QRegExpValidator(QRegExp("[a-zA-Z0-9]+"), nameMatrix);
    nameMatrix->setValidator(regex);
    nameMatrix->setMaxLength(10);
    nameMatrix->setFixedSize(75,35);

    nbRowsSelector = new QSpinBox;
    nbColsSelector = new QSpinBox;
    QString styleButton = "QSpinBox{border: 1px solid grey; border-radius: 3px; value: 5; font-size: 15px;}"
                          "QSpinBox::down-button{width: 20px;}"
                          "QSpinBox::up-button{width: 20px;}";

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

    QPushButton* ajouter = new QPushButton("Ajouter");
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(setSpecsWidget);
    mainLayout->addWidget(lineEditsWidget);
    mainLayout->addWidget(ajouter);
    setLayout(mainLayout);

    connect(nbRowsSelector, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &AddMatrixWidget::update_EditSize);
    connect(nbColsSelector, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &AddMatrixWidget::update_EditSize);
    connect(this, &AddMatrixWidget::error, this, &AddMatrixWidget::showError);
    connect(ajouter, &QPushButton::pressed, this, &AddMatrixWidget::compute_add);
    connect(this, &AddMatrixWidget::matrixAdded,
            qobject_cast<LibraryWindow*>(parent), &LibraryWindow::updateView);
}



void AddMatrixWidget:: compute_add ()
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
    library->addMatrix(name.toStdString(), newMatrix);

    QList<QStandardItem*> a;
    a.append(new QStandardItem(name));
    a.append(new QStandardItem(QString::number(nbL)));
    a.append(new QStandardItem(QString::number(nbC)));

    emit matrixAdded(a);
}



bool AddMatrixWidget:: controlKeyboardInput() const
{
    QString name = this->nameMatrix->text();

    if(library->find(name.toStdString()))
    {
        emit error("La Matrice " + name + " existe déjà !",
                   "Veuillez changer de nom.");
        return false;
    }

    if(!nameMatrix->hasAcceptableInput())
    {
        emit error("Nom de Matrice " + name + " non valide !",
                   "Veuillez saisir 10 caractère Maximum, sans caractères spéciaux ni espaces ");
        return false;
    }

    for(const auto& i : lineEditsTab)
    {
        if (!i->hasAcceptableInput())
        {
            emit error("Les valeurs de votre Matrice " + name + " sont incorrectes !",
                       "Vérifiez votre saisie. Chaque coefficient doit être un nombre Réel.");
            return false;
        }
    }

    return true;
}


void AddMatrixWidget:: update_EditSize ()
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
                lineEditsTab.append(temp);
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
                delete temp;
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
                delete temp;
            }
            lcols--;
        }
    }
}



void AddMatrixWidget:: showError(QString title, QString body) const
{
    QMessageBox* error = new QMessageBox;
    error->setAttribute(Qt::WA_DeleteOnClose, true);
    error->setFixedSize(650,200);
    error->setIcon(QMessageBox::Critical);
    error->setText(title);
    error->setInformativeText(body);
    error->show();
}


AddMatrixWidget:: ~AddMatrixWidget ()
{
}

