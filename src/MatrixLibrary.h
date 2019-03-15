
#ifndef _MATRIX_LIBRARY_
#define _MATRIX_LIBRARY_

#include "Matrix.h"
#include <map>

class MatrixLibrary
{
    private:
    
    std::map<std::string,Matrix> tab;
    
    public:
    
    MatrixLibrary ();
    ~MatrixLibrary ();
    
    unsigned int size () const;
    bool empty () const;
    bool exist (const Matrix& m) const;
    void print () const;
    void addMatrix (const Matrix& m);
    const Matrix* search (const std::string& name) const;
};


#endif
