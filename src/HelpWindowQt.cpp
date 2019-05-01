#include "HelpWindowQt.h"

HelpWindowQt::HelpWindowQt(QWidget* parent) : QDialog (parent)
{
    QWidget* wind = new QWidget;
    title = new QLabel("About QT");

    QFont fontTitle ("Arial");
    fontTitle.setPointSize(20);

    QFont font ("Arial Bold");
    font.setWeight(QFont::Bold);
    fontTitle.setPointSize(16);

    title->setFont(fontTitle);

    QPixmap im(":/img/qt.png");
    im = im.scaled(100, 56);

    logo = new QLabel;
    logo->setPixmap(im);
    logo->setMaximumWidth(150);

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

    QLabel* defIntro = new QLabel("L'afichage graphique de l'application MatriXMix"
                                  " a été réalisé à l'aide de la librarie QT. "
                                  "Des classes prédéfinis \n fournis par la "
                                  "librarie QT ont été utilisées.");

    documentation = new QGroupBox(tr("Documentation"));
    documentation->setFont(font);
    documentation -> setStyleSheet(
                "QGroupBox { border: 1px solid silver;"
                "background-color:white;"
                "margin-top: 30px;"
                "border-radius:6px;}"
                "QGroupBox::title { subcontrol-origin:margin;"
                "subcontrol-position:top left;"
                "font-weight:75; color: #283676;}");
    QLabel* defDoc = new QLabel("La documentation sur les classes / héritages"
                                " de la librarie QT:");
    QLabel* linkDoc = new QLabel;
    linkDoc->setOpenExternalLinks(true);
    linkDoc->setText("<a href = \"https://doc.qt.io\">"
                         "Qt Documentation</a>");

    QHBoxLayout* headerLayout = new QHBoxLayout;
    headerLayout->addWidget(logo);
    headerLayout->addWidget(title);
    headerLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    QVBoxLayout* subLayout1 = new QVBoxLayout;
    subLayout1->addWidget(defIntro);
    introduction->setLayout(subLayout1);

    QVBoxLayout* subLayout2 = new QVBoxLayout;
    subLayout2->addWidget(defDoc);
    subLayout2->addWidget(linkDoc);
    documentation->setLayout(subLayout2);

    QLabel* qt = new QLabel("@The Qt Company");
    qt->setFont(font);
    qt->setMinimumHeight(20);
    qt->setStyleSheet("font: bold; color: darkBlue;");

    QVBoxLayout* qtLayout = new QVBoxLayout;
    qtLayout->addWidget(qt);
    qtLayout->setAlignment(Qt::AlignHCenter);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(headerLayout);
    mainLayout->addWidget(introduction);
    mainLayout->addWidget(documentation);
    mainLayout->addLayout(qtLayout);
    mainLayout->setAlignment(Qt::AlignCenter);
    wind->setLayout(mainLayout);
    wind->show();
}

HelpWindowQt::~HelpWindowQt()
{
}
