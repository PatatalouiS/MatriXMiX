#ifndef WEB_OBJ
#define WEB_OBJ

#include <QObject>

class WebObject : public QObject {
    Q_OBJECT

    public slots :

        void mathJaxDone(QString str);

    private:

        bool firstRender = false;

    signals :

        void done();
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


        void setLatex(QString&& latex);

    public slots :

        void getSVG();

    private :

        QWebEnginePage* page;
        QWebEngineView* view;
        QWebChannel* channel;
        WebObject* webObj;
        QSvgWidget* img;
        QImage* img2;
};

#endif // MATHJAXRENDERER_H
