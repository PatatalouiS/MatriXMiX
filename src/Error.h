
#ifndef ERROR_H
#define ERROR_H

#include <QString>
#include <QWidget>


class Error
{
    public:

    static void showError (const QString& title, const QString& body, QWidget* parent = nullptr);
};


#endif
