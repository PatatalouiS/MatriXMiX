
#ifndef ERROR_H
#define ERROR_H

#include <QString>
#include <QWidget>


/**
@class Error  none none   this little class is in charge to send an Error Modal Window to user \n
*/



class Error
{
    public:

    /** @brief this fonction show an Error Modal Window to user. He Must close it.
     * @param [in] title the title of the Window
     * @param [in] body the body of the window
     * @param [in, out] a pointer on a potential parent QWidget, mainly for ensure good deletion.
     */

    static void showError (const QString& title, const QString& body, QWidget* parent = nullptr);
};


#endif
