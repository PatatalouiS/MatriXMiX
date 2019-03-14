
#ifndef _MATRIX_LIBRARY_
#define _MATRIX_LIBRARY_


#include "Matrix.h"
#include <vector>




class MatrixLibrary
{
    private:
    
    std::vector<Matrix> library;
    bool exist(const Matrix& m);
    
    
    public:
    
    MatrixLibrary ();
    ~MatrixLibrary ();
    unsigned int size () const;
    void addMatrix (const Matrix& m);
};




#endif
