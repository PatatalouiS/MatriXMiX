#include "UserInputs.hpp"

using namespace std;

UserInputs::UserInputs(const unsigned int r, const unsigned int c)
    : rows(r), cols(c), inputs()
{}


unsigned int UserInputs::getRows() const {
    return rows;
}


unsigned int UserInputs::getCols() const {
    return cols;
}


vector<string>::const_iterator UserInputs::begin() const {
   return inputs.begin();
}


vector<string>::const_iterator UserInputs::end() const {
   return inputs.end();
}
