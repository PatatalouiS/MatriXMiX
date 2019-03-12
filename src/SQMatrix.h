
#ifndef _SQ_MATRIX_H
#define _SQ_MATRIX_H

#include "Matrix.h"
#include "VectorX.h"

class SQMatrix : public Matrix
{
    public:
    
    SQMatrix (const unsigned int size, const VectorX& v);
    ~SQMatrix();
    
    
};





#endif

