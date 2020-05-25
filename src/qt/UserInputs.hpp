#ifndef USERINPUTS_HPP
#define USERINPUTS_HPP

#include <vector>
#include <string>

class UserInputs {

    public :


    UserInputs(const unsigned int nRows = 0, const unsigned int nCols = 0 );

    unsigned int getRows() const;

    unsigned int getCols() const;

    std::vector<std::string>::const_iterator begin() const;

    std::vector<std::string>::const_iterator end() const;


    private :


    unsigned int rows;

    unsigned int cols;

    std::vector<std::string> inputs;
};




#endif // USERINPUTS_HPP
