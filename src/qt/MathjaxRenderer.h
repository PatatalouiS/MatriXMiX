#ifndef WEB_OBJ
#define WEB_OBJ

#include <QObject>

class WebObject : public QObject {

    Q_OBJECT

    public slots :

        void mathJaxDone(QString str);

    private:

        bool firstRender = false;
};


#endif

#ifndef MATHJAXRENDERER_H
#define MATHJAXRENDERER_H

#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebEngineWidgets/QWebEnginePage>
#include <QWebChannel>
#include <QSvgWidget>

class MathjaxRenderer : public QWidget
{
    Q_OBJECT

    public:

        MathjaxRenderer(QWidget* parent = nullptr);


        void setLatex(const QString& latex);

    public slots :

        void getSVG();

    private :

        QWebEnginePage* page;
        QWebEngineView* view;
        QWebChannel* channel;
        WebObject* webObj;
};

#endif // MATHJAXRENDERER_H
