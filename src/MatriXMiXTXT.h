
#ifndef _MATRIXMIX_TXT_H_
#define _MATRIXMIX_TXT_H_

#include "MatrixLibrary.h"


class MatriXMiXTXT
{
    private:
    
    MatrixLibrary lib;
    
    
    void MsgEmptyLib () const;
    void addMatrixMenu ();
    void showLibrary () const;
    void addition ();
    
    

    public:
    
    void mainMenu ();
    
    
};



#endif
