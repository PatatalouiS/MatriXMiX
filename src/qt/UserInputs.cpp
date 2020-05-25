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


QVector<QString>::const_iterator UserInputs::begin() const {
   return inputs.begin();
}


QVector<QString>::const_iterator UserInputs::end() const {
   return inputs.end();
}


const QString& UserInputs::put(const QString& input) {
    inputs.push_back(input);
    return inputs.back();
}

const QString& UserInputs::operator[](const unsigned int ind) const {
    return inputs[ind];
}
