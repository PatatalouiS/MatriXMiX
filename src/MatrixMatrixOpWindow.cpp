
//#include "MatrixMatrixOpWindow.h"
//#include <QVBoxLayout>
//#include <QPushButton>
//#include <QDebug>
//#include <QMessageBox>


//MatrixMatrixOpWindow::MatrixMatrixOpWindow(MatrixLibrary* lib, unsigned int type, QWidget* parent) : QDialog(parent)
//{
//    this->lib = lib;
//    op1Name = "_";
//    op2Name = "_";
//    op1 = nullptr;
//    op2 = nullptr;

//    resultImg = new ShowMatrixWidget(this);
//    resultImg->hide();

//    QLabel* title = new QLabel(specs.nameOp);
//    title->setStyleSheet("font-size: 30px;");
//    title->setAlignment(Qt::AlignCenter);

//    QVBoxLayout* op1ChoiceLayout = new QVBoxLayout;
//    QLabel* op1Title = new QLabel("Choix de la matrice 1 : ");
//    op1View = new MatrixViewWidget(lib, this);
//    op1ChoiceLayout->addWidget(op1Title);
//    op1ChoiceLayout->addWidget(op1View);

//    QVBoxLayout* op2ChoiceLayout = new QVBoxLayout;
//    QLabel* op2Title = new QLabel("Choix de la matrice 2 : ");
//    op2View = new MatrixViewWidget(lib, this);
//    op2ChoiceLayout->addWidget(op2Title);
//    op2ChoiceLayout->addWidget(op2View);

//    QHBoxLayout* formLayout = new QHBoxLayout;
//    formLayout->addLayout(op1ChoiceLayout);
//    formLayout->addLayout(op2ChoiceLayout);

//    formula = new QLabel("_ " + specs.logoOp + " _");
//    formula->setStyleSheet("font-size: 40px");
//    formula->setAlignment(Qt::AlignCenter);
//    formula->setContentsMargins(0,25,0, 25);

//    QPushButton* calculer = new QPushButton("Calculer");

//    QVBoxLayout* subLayout1 = new QVBoxLayout;
//    subLayout1->addWidget(title);
//    subLayout1->addLayout(formLayout);
//    subLayout1->addWidget(formula);
//    QWidget* subWidget1 = new QWidget(this);
//    subWidget1->setLayout(subLayout1);
//    subWidget1->setFixedHeight(400);

//    mainLayout = new QVBoxLayout;
//    mainLayout->setSpacing(10);
//    mainLayout->addWidget(subWidget1);
//    mainLayout->addWidget(resultImg);
//    mainLayout->addWidget(calculer);
//    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);


//    connect(op1View->selectionModel(), &QItemSelectionModel::selectionChanged,
//            [this] () -> void
//            {
//                this->computeSelection(0);
//            });
//    connect(op2View->selectionModel(), &QItemSelectionModel::selectionChanged,
//            [this] () -> void
//            {
//                this->computeSelection(1);
//            });
//    connect(calculer, &QPushButton::pressed, this, &MatrixMatrixOpWindow::computeOperation);

//    setLayout(mainLayout);
//}


//void MatrixMatrixOpWindow:: computeSelection (bool op)
//{
//    int selectedRow;
//    QString selectedName;
//    resultImg->hide();
//    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
//    updateGeometry();

//    if(!op)
//    {
//        selectedRow = op1View->currentIndex().row();
//        selectedName = op1View->model()->item(selectedRow)->data(2).toString();
//        op1Name = selectedName;
//        op1 = lib->find(selectedName.toStdString());
//        formula->setText(selectedName + " " + specs.logoOp + " " + op2Name);
//    }
//    else
//    {
//        selectedRow = op2View->currentIndex().row();
//        selectedName = op2View->model()->item(selectedRow)->data(2).toString();
//        op2Name = selectedName;
//        op2 = lib->find(selectedName.toStdString());
//        formula->setText(op1Name + " " + specs.logoOp + " " + selectedName);
//    }
//}


//void MatrixMatrixOpWindow:: computeOperation ()
//{
//    if(!specs.
//    validator(op1, op2))
//    {
//        showError("Matrices incompatibles pour : " + specs.nameOp,
//        specs.errorMsg);
//        return;
//    }

//    result = specs.operation(op1, op2);
//    resultImg->compute_img(&result);
//    resultImg->show();
//}


//void MatrixMatrixOpWindow::setOperationSpecs(unsigned int type)
//{
//    specs.idOp = type;

//    switch(type)
//    {
//        case 0 :
//        {
//            specs.nameOp = "Addition";
//            specs.logoOp = "+";
//            specs.validator = [](const Matrix* a, const Matrix* b) -> bool
//            {
//                return((a->getNbRows() == b->getNbRows()) && (a->getNbCols() == b->getNbCols()));
//            };
//            specs.operation = [](const Matrix* a, const Matrix* b) -> Matrix
//            {
//                return *a + *b;
//            };
//            specs.errorMsg = "La matrice " + op1Name +
//            " doit avoir les même dimensions que la matrice " + op2Name;
//            break;
//        }
//        case 1 :
//        {
//            specs.nameOp = "Multiplication";
//            specs.logoOp = "*";
//            specs.validator = [](const Matrix* a, const Matrix* b) -> bool
//            {
//                return((a->getNbCols() == b->getNbRows()));
//            };
//            specs.operation = [](const Matrix* a, const Matrix* b) -> Matrix
//            {
//                return *a * *b;
//            };
//            specs.errorMsg = "La matrice " + op1Name +
//            " doit avoir le même nombre de colonnes que le nombre de lignes de " + op2Name;
//            break;
//        }
//        case 2 :
//        {
//            specs.nameOp = "Soustraction";
//            specs.logoOp = "-";
//            specs.validator = [](const Matrix* a, const Matrix* b) -> bool
//            {
//                return((a->getNbRows() == b->getNbRows()) && (a->getNbCols() == b->getNbCols()));
//            };
//            specs.operation = [](const Matrix* a, const Matrix* b) -> Matrix
//            {
//                return *a - *b;
//            };
//            specs.errorMsg = "La matrice " + op1Name +
//            " doit avoir les même dimensions que la matrice " + op2Name;
//            break;
//        }
//        case 3 :
//        {
//            specs.nameOp = "Division";
//            specs.logoOp = "/";
//            specs.validator = [](const Matrix* a, const Matrix* b) -> bool
//            {
//                return((a->getNbRows() == b->getNbRows()) && (a->getNbCols() == b->getNbCols())
//                && (b->determinant() != 0.0));
//            };
//            specs.operation = [](const Matrix* a, const Matrix* b) -> Matrix
//            {
//                return *a / *b;
//            };
//            specs.errorMsg = "La matrice " + op1Name +
//            " doit avoir les même dimensions que la matrice " + op2Name + ".\n"
//            + "La Matrice " + op2Name + " doit être inversible";
//            break;
//        }
//        default : break;
//    }
//}


//void MatrixMatrixOpWindow:: showError(QString title, QString body) const
//{
//    QMessageBox* error = new QMessageBox;
//    error->setAttribute(Qt::WA_DeleteOnClose, true);
//    error->setFixedSize(650,200);
//    error->setIcon(QMessageBox::Critical);
//    error->setText(title);
//    error->setInformativeText(body);
//    error->show();
//}

//MatrixMatrixOpWindow:: ~MatrixMatrixOpWindow ()
//{
//}

