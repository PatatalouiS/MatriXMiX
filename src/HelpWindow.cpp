#include "HelpWindow.h"

HelpWindow::HelpWindow(QWidget* parent) : QDialog(parent)
{
   title = new QLabel("MatriXMiX Guide");

   QPixmap im(":/img/logo.png");
   im = im.scaled(100, 56);

   logo = new QLabel;
   logo->setPixmap(im);
   logo->setMaximumWidth(150);

   QFont fontTitle ("Arial");
   fontTitle.setPointSize(20);

   title->setFont(fontTitle);

   QHBoxLayout* headerLayout = new QHBoxLayout;
   headerLayout->addWidget(logo);
   headerLayout->addWidget(title);
   headerLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

   QWidget* headerWidget = new QWidget;
   headerWidget->setLayout(headerLayout);
   headerWidget->setMinimumHeight(100);

   QFont font ("Arial Bold");
   font.setWeight(QFont::Bold);
   fontTitle.setPointSize(16);

   introduction = new QGroupBox(tr("Introduction"));
   introduction->setFont(font);
   introduction -> setStyleSheet(
               "QGroupBox { border: 1px solid silver;"
               "background-color:white;"
               "margin-top: 30px;"
               "border-radius:6px;}"
               "QGroupBox::title { subcontrol-origin:margin;"
               "subcontrol-position:top left;"
               "font-weight:75; color: #283676;}");

   QLabel* defIntro = new QLabel("MatriXMiX est une application destinée aux étudiants de niveau licence"
                            "en mathématique. \nElle leur permet de "
                            "vérifier leurs résultats d'exercices d'algèbre linéaire, "
                            "ceux ci étant difficilement \ncorrigeables car les corrections"
                            "ne sont guère souvent données et les erreurs de calcul sont"
                            "très fréquentes.\n"
                            "MatriXMiX permet d'effectuer des opérations (de base) binaires, "
                            "unaires, et des "
                            "opérations liés à la diagonalisation.");

   utilisation = new QGroupBox(tr("Utilisation"));
   utilisation->setFont(font);
   utilisation -> setStyleSheet(
               "QGroupBox { border: 1px solid silver;"
               "background-color:white;"
               "margin-top: 30px;"
               "border-radius:6px;}"
               "QGroupBox::title { subcontrol-origin:margin;"
               "subcontrol-position:top left;"
               "font-weight:75; color: #283676;}");
   QLabel* defUtilisation = new QLabel("Pour effectuer un type d'opération "
                                       "presenté sur la page "
                                       "d'accueil vous devez rentrer sur la "
                                       "page de la librarie \n"
                                       "accessible sur la bare de menu et ajouter "
                                       "les matrices. \n"
                                       "D'ailleurs, vous pouvez visualiser, "
                                       "supprimmer ou modifier les "
                                       "matrices sur la page de la librarie. \n"
                                       "Du moment que vous avez ajouter une matrice dans la librarie"
                                       "elle est disponible \n dans la boîte de "
                                       "régroupement de l'opération"
                                       "sur la page d'accueil.");
   QLabel * att = new QLabel("Attention!");
   att->setStyleSheet("font: bold; color: red;");
   QLabel * defAttention = new QLabel("Pour les opérations binaires, unaires et "
                                      "liés à la diagonalisation seulement des "
                                      "matrices compatibles \n avec l'opération selectionnée sont"
                                      " affichées!");

   maths = new QGroupBox(tr("Calcul matriciel"));
   maths->setFont(font);
   maths -> setStyleSheet(
               "QGroupBox { border: 1px solid silver;"
               "background-color:white;"
               "margin-top: 30px;"
               "border-radius:6px;}"
               "QGroupBox::title { subcontrol-origin:margin;"
               "subcontrol-position:top left;"
               "font-weight:75; color: #283676;}");
   QLabel* defMaths = new QLabel("Théorie sur le calcul matriciel: ");
   QLabel* linkOpBinaires = new QLabel;
   linkOpBinaires->setOpenExternalLinks(true);
   linkOpBinaires->setText("<a href = \"https://www.unilim.fr/pages_perso/jean.debord/math"
                           "/matrices/matrices.htm\"> Opérations sur"
                           " les matrices </a>");
   QLabel* linkEspVect = new QLabel;
   linkEspVect->setOpenExternalLinks(true);
   linkEspVect->setText("<a href = \"http://uel.unisciel.fr/mathematiques"
                        "/calculmat1/calculmat1/co/calculmat1.html\"> "
                        "Matrice et espaces vectoriels</a>");
   QLabel* linkDiago = new QLabel;
   linkDiago->setOpenExternalLinks(true);
   linkDiago->setText("<a href = \"http://www.math.univ-paris13.fr/~schwartz/L2/diag.pdf\"> "
                        "Polynôme caractéristique/ Valeurs/Vecteurs propres / Diagonalisation</a>");

   QVBoxLayout* subLayout = new QVBoxLayout;
   subLayout->addWidget(defIntro);
   introduction->setLayout(subLayout);

   QVBoxLayout* subLayout2 = new QVBoxLayout;
   subLayout2->addWidget(defUtilisation);
   subLayout2->addWidget(att);
   subLayout2->addWidget(defAttention);
   utilisation->setLayout(subLayout2);

   QVBoxLayout* subLayout3 = new QVBoxLayout;
   subLayout3->addWidget(defMaths);
   subLayout3->addWidget(linkOpBinaires);
   subLayout3->addWidget(linkEspVect);
   subLayout3->addWidget(linkDiago);
   maths->setLayout(subLayout3);

   QLabel* matrix = new QLabel("@MatriXMiX 2019");
   matrix->setFont(font);
   matrix->setMinimumHeight(20);
   matrix->setStyleSheet("font: bold; color: darkBlue;");
   QLabel* matrixAuteurs = new QLabel("\n OLIVIE Maxime \n CERBULEAN Ana-Maria"
                                     "\n BOUMAZA Tarik \n SEBIA Hana");
   matrixAuteurs->setMaximumHeight(100);
   QVBoxLayout* matrixLayout = new QVBoxLayout;
   matrixLayout->addWidget(matrix);
   matrixLayout->addWidget(matrixAuteurs);
   matrixLayout->setAlignment(Qt::AlignHCenter);

   QVBoxLayout* mainLayout = new QVBoxLayout;
   mainLayout->addWidget(headerWidget);
   mainLayout->addWidget(introduction);
   mainLayout->addWidget(utilisation);
   mainLayout->addWidget(maths);
   mainLayout->addLayout(matrixLayout);
   mainLayout->setAlignment(Qt::AlignCenter);
   setLayout(mainLayout);
}

HelpWindow::~HelpWindow()
{
}
