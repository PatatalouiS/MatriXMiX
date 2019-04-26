

#ifndef AbstractOperationWidget_H
#define AbstractOperationWidget_H

#include <QLabel>
#include <QPushButton>
#include <QVariant>
#include "MatrixLibrary.h"


Q_DECLARE_METATYPE(Matrix);


class AbstractOperationWidget : public QWidget
{

    Q_OBJECT

    using SortFunction = std::function<bool(const Matrix*)>;


    public :

        AbstractOperationWidget(const MatrixLibrary* lib, QWidget* parent = nullptr);

    public slots:

        virtual void updateViews() = 0;

    protected slots:

        virtual void computeSelection(bool view = 0) = 0;
        virtual void computeOperation() = 0;

    protected :

        const MatrixLibrary* lib;
        SortFunction sortFunction;
        QLabel* description;
        QLabel* title;
        QPushButton* calculer;
        QVariant result;

        void setLib(const MatrixLibrary* lib);
        void setTitle(const QString& str);
        void setSortFunction(const SortFunction& s);

    signals:

        void newResult(const QVariant res);
};


#endif
