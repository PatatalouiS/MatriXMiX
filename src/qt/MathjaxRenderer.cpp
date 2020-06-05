#include "MathjaxRenderer.h"

#include <QHBoxLayout>
#include <QDebug>
#include <QSvgWidget>


MathjaxRenderer::MathjaxRenderer(QWidget* parent) : QWidget(parent) {
    page = new QWebEnginePage(this);
    page->load(QUrl("qrc:/mathjax/mathjax/main.html"));
    //view = new QWebEngineView(this);
    //view->setPage(page);

    webObj = new WebObject;
    channel = new QWebChannel(this);
    channel->registerObject("webObj", webObj);
    page->setWebChannel(channel);

    img = new QSvgWidget;

    QHBoxLayout* mainLayout = new QHBoxLayout;

    mainLayout->addWidget(img);
    img->setMinimumSize(500, 500);

    connect(webObj, &WebObject::done, this, &MathjaxRenderer::getSVG);

    connect(page, &QWebEnginePage::loadFinished, [this] () -> void {
        setLatex("\\begin{bmatrix} 1 & 2 \\\\ 3 & 4 \\end{bmatrix}");
    });

    setLayout(mainLayout);
}


void MathjaxRenderer::setLatex(QString&& latex) {

    latex = latex.replace( "\\", "\\\\" ).replace( "'", "\\'" )
                     .replace( "\n", "\\\n" );

    QString setLatex = QString("loadLatex('%1');")
            .arg(latex);

    page->runJavaScript(setLatex, [](const QVariant& v) -> void {
        //qDebug() << v.toString() << endl;
    });



}


void WebObject::mathJaxDone(QString str) {
    if(!firstRender) {
        firstRender = true;
    }
    else {
          qDebug() << str;
          emit done();
    }
}

void MathjaxRenderer::getSVG() {
    QString svgGetter1 = QString("getSVG1(0);");
    QString svgGetter2 = QString("getSVG2(1);");

    page->runJavaScript(svgGetter1, [this, svgGetter2](const QVariant& v1) -> void {
        QString value1 = v1.toString();
        qDebug() << v1.toString();

        page->runJavaScript(svgGetter2, [this, &value1](const QVariant& v2) -> void {
            QString value2 = v2.toString();
            qDebug() << v2.toString();

            QString defs;
            QRegExp svgre( "<svg([^>]*)>(.*)</svg>" );
            QRegExp defre( "<defs.*defs>" );

            defre.indexIn( value1 );

            //qDebug() << defre.cap(0);

//            defs += defre.cap();
//            svgre.indexIn( value2 );

//            QString result = QString( "<svg%1>%2%3</svg>" );
//                    .arg( svgre.cap( 1 ) )
//                    .arg( defs );
                    //.arg( svgre.cap( 2 ) );


            //img->load(result.toUtf8());
        });
    });









}




