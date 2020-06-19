#include "MathjaxRenderer.h"

#include <QHBoxLayout>
#include <QDebug>
#include <QSvgWidget>


MathjaxRenderer::MathjaxRenderer(QWidget* parent) : QWidget(parent) {
    page = new QWebEnginePage(this);
    page->load(QUrl("qrc:/mathjax/mathjax/main.html"));
    view = new QWebEngineView(this);
    view->setPage(page);
    view->setStyleSheet(""
                                "background-color : white;"
                                "border : 20px solid grey;"
                                "border-radius : 4px;"
                            "");

    webObj = new WebObject;
    channel = new QWebChannel(this);
    channel->registerObject("webObj", webObj);
    page->setWebChannel(channel);

    QWidget* wrapper = new QWidget(this);
    QHBoxLayout* wrapperLayout = new QHBoxLayout;

    wrapper->setStyleSheet(""
                                "background-color : white;"
                                "border : 20px solid grey;"
                                "border-radius : 4px;"
                            "");

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(view);
    wrapper->setLayout(mainLayout);
    wrapperLayout->addWidget(wrapper);

    setObjectName("MathJaxRenderer");

    connect(page, &QWebEnginePage::loadFinished, [this] () -> void {

        setLatex("\\begin{bmatrix} 1 & 2 \\\\ 3 & 4 \\end{bmatrix}");
    });

    setStyleSheet(".QWidget{"
                                "background-color : white;"
                                "border : 20px solid grey;"
                                "border-radius : 4px;"
                            "}");

    setLayout(wrapperLayout);
}


void MathjaxRenderer::setLatex(const QString& latex) {
    QString copy(latex);
    copy = copy.replace( "\\", "\\\\" ).replace( "'", "\\'" )
                     .replace( "\n", "\\\n" );

    QString setLatex = QString("loadLatex('%1');")
            .arg(copy);

    page->runJavaScript(setLatex, [](const QVariant& v) -> void {
        //qDebug() << v.toString() << endl;
    });
}


void WebObject::mathJaxDone(QString str) {
    if(!firstRender) {
        firstRender = true;
    }
}

void MathjaxRenderer::getSVG() {
};







