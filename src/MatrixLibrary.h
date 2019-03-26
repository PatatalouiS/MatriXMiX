
#ifndef _MATRIX_LIBRARY_
#define _MATRIX_LIBRARY_

#include "Matrix.h"
#include <map>


class MatrixLibrary
{
	private:
	
	std::map<std::string, Matrix> tab;
	
	public:
	
    MatrixLibrary ();
    ~MatrixLibrary ();
    
    unsigned int size () const;
    bool isEmpty () const;
	bool exist (const std::string& name) const;
    void print () const;
	void addMatrix (const std::string& name, const Matrix& m);
	const Matrix* find (const std::string& name) const;
	void erase (const std:: string & name);
};


#endif
