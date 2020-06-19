
#include "QMatrixLibrary.hpp"
#include <fstream>
#include <cassert>
#include <mpParser.h>
#include <QDebug>
#include <algorithm>

using namespace std;

namespace {

    QString complexToExpr(const Value& v) {
        const double& real = v.real();
        const double& imag = v.imag();

        if((real == 0.f ) && (imag == 0.f)) {
            return "0";
        }

        if(imag == 0.f) {
            return QString::number(real);
        }

        QString convert;

        if(real != 0.f) {
             convert.append(QString::number(real));
        }

        if(imag > 0.f) {
            if(real != 0.f) {
                convert.append(" + ");
            }
            if(imag == 1.f) {
                convert.append("i");
            }
            else {
                convert.append(QString::number(imag))
                        .append("*i");
            }
        }
        else if(imag < 0.f) {
            if(imag == -1.f) {
                convert.append("-i");
            }
            else {
                convert.append(" - ")
                        .append(QString::number(abs(imag)))
                        .append("*i");
            }
        }
        return convert;
    }

}

mup::ParserX QMatrixLibrary::parser = mup::ParserX();


QMatrixLibrary:: QMatrixLibrary () : tab(QMap<QString, UserMatrix>())
{}


QMatrixLibrary::  QMatrixLibrary (const QMatrixLibrary & lib) {
    for(const auto& [ name, userMtx ] : lib) {
        tab.insert(name, userMtx);
    }
}


unsigned long int QMatrixLibrary:: size () const {
    return tab.size();
}


bool QMatrixLibrary:: isEmpty () const {
    return size() == 0;
}


void QMatrixLibrary:: clear () {
    tab.clear();
}


bool QMatrixLibrary:: exist (const QString& name) const {
    //return (tab.count(name) != 0);
    return tab.contains(name);
}


bool QMatrixLibrary:: isName(const QString & chain) const {
    unsigned int i = 1, s = chain.length();

    if ( !( ((chain[0] >= 'A') && (chain[0] <= 'Z'))
            || ((chain[0] >= 'a') && (chain[0] <= 'z')) ) )
        return false;

    while (i<s) {
        if ( ((chain[i] >= 'A') && (chain[i] <= 'Z'))
             || ((chain[i] >= 'a') && (chain[i] <= 'z'))
             || ((chain[i] >= '0') && (chain[i] <= '9')))
            i++;
        else return false;
    }
    return true;
}


const Matrix& QMatrixLibrary:: addMatrix (const QString& name, const  UserInputs& entries) {
    if(isName(name)) {

        VectorX values;

        for(const QString& entry : entries) {
            parser.SetExpr(entry.toStdString());
            values.push_back(parser.Eval().GetComplex());
        }

        Matrix newMatrix(entries.getRows(), entries.getCols(), values);

        auto inserted = tab.insert(name, { newMatrix, entries });

        return inserted.value().matrix;
    }
    else {
        cout << "Nom de matrice non autorisé, "
             << "veuillez choisir un autre..."<< endl;
        return Matrix::matrix_null;
    }
}


void QMatrixLibrary:: addMatrix (const QString& name, const Matrix& m) {
    if(isName(name)) {
        unsigned int nbRows = m.getNbRows();
        unsigned int nbCols = m.getNbCols();

        UserInputs defaults(nbRows, nbCols);

        for(unsigned int i = 0; i < nbRows; i++) {
            for(unsigned int j = 0; j < nbCols; j++) {
                defaults.put(complexToExpr(m[i][j]));
            }
        }

        tab.insert( name, { m, defaults });
    }
    else {
        cout << "Nom de matrice non autorisé, "
             << "veuillez choisir un autre..."<< endl;
    }
}


const Matrix* QMatrixLibrary:: find (const QString& name) const {
    return exist(name)
        ? &const_cast<QMatrixLibrary&>(*this).tab[name].matrix
        : nullptr;
}


Matrix* QMatrixLibrary:: find (const QString& name) {
    return const_cast<Matrix*>(static_cast<const QMatrixLibrary&>(*this).find(name));
}

const UserInputs* QMatrixLibrary::find_inputs(const QString& name) const {
    return exist(name)
        ? &const_cast<QMatrixLibrary&>(*this).tab[name].entries
        : nullptr;
}

UserInputs* QMatrixLibrary::find_inputs(const QString& name) {
    return const_cast<UserInputs*>(static_cast<const QMatrixLibrary&>(*this).find_inputs(name));
}

const UserMatrix* QMatrixLibrary::find_all(const QString& name) const {
    return exist(name)
        ? &const_cast<QMatrixLibrary&>(*this).tab[name]
        : nullptr;
}

UserMatrix* QMatrixLibrary::find_all(const QString& name) {
    return const_cast<UserMatrix*>(static_cast< const QMatrixLibrary&>(*this).find_all(name));
}



void QMatrixLibrary:: erase (const QString & name) {
    tab.remove(name);
    if(exist(name)) {
        cout << "Suppression non effectuée" << endl;
    }
}


const QMap<QString, UserMatrix>& QMatrixLibrary:: data () const {
    return tab;
}


const QMap<QString, UserMatrix>::const_key_value_iterator QMatrixLibrary::begin() const {
    return tab.keyValueBegin();
}

const QMap<QString, UserMatrix>::const_key_value_iterator QMatrixLibrary::end() const {
    return tab.keyValueEnd();
}


// Parser Section




void QMatrixLibrary::copyVector(std::vector<std::string>& expression,
                                const std::vector<std::string>& result)const
{
    for (auto i :result)
    {
        expression.push_back(i);
    }

}


bool QMatrixLibrary:: isFloat(const string & chain) const
{
    unsigned long int i = 0, s = chain.length();
    unsigned short int nbcoma = 0;

    while (i<s)
    {
        if (chain[i]=='.')
            nbcoma++;
        else if (! ((chain[i]>='0') && (chain[i]<='9')) )
            return false ;

        if (nbcoma > 1)
            return false;

        i++;
    }

    return true;
}


bool QMatrixLibrary:: isOperator (const string & chain) const
{
    return ( (chain == "+")
             ||  (chain == "-")
             ||  (chain == "/")
             || (chain == "^")
             || (chain == "~")
             || (chain == "*"));
}


bool QMatrixLibrary:: isSpecialCaractere(const string & chain) const
{
    if (!isName(QString::fromStdString(chain)) && !isFloat(chain) &&
            !isOperator(chain))
        return true;
    return false;
}


vector<string> QMatrixLibrary:: explode (const string & expression)const
{
    vector<string> tab;
    string c, temp;
    temp="";

    for (auto i : expression)
    {
        c=i;

        if((isOperator(c)) || (c == ")") || (c == "(") || (c == "=") )
        {
            if (temp.length()!=0)
                tab.push_back(temp);
            tab.push_back(c);
            temp.clear();
        }
        else if (!c.empty())
        {
            temp+=c;
        }

    }
    if(temp != "")
    tab.push_back(temp);

    return tab;
}


bool QMatrixLibrary:: highEqualPriority (const string & opd,
                                          const string & opg) const
{
    switch (opd[0])
    {
        case '*':
            return ((opg[0] == '*') || (opg[0] == '/') || (opg[0] == '^')
                || (opg[0] == '~'));

        case '/':
            return ((opg[0] == '*') || (opg[0] == '/') || (opg[0] == '^')
                || (opg[0] == '~'));

        case '+':
            return ((opg[0] == '+') || (opg[0] == '-') || (opg[0] == '*')
                || (opg[0] == '/') || (opg[0] == '^') || (opg[0] == '~'));

        case '-':
            return ((opg[0] == '+') || (opg[0] == '-') || (opg[0] == '*')
                || (opg[0] == '/') || (opg[0] == '^') || (opg[0] == '~'));

        case '^':
            return ((opg[0] == '^') || (opg[0] == '~'));

        case '~':
            return ((opg[0] == '^') || (opg[0] == '~'));

        default: return false;
    }
}


Matrix QMatrixLibrary:: calculate (const string & op, const string & a,
                                  const string & b) const
{
    const Matrix* m_a;
    const Matrix* m_b;

    m_a = find(QString::fromStdString(a));
    m_b = find(QString::fromStdString(b));

    if(op == "+")
        return *m_a + *m_b;

    if(op == "-")
        return *m_a - *m_b;

    if(op == "*")
        return *m_a * *m_b;

    if(op == "/")
        return *m_a / *m_b;

    else return *m_a;
}


double QMatrixLibrary:: calculateFloat (const std::string & op,
                                       const std::string & a,
                                       const std::string & b) const
{
    if(op == "+")
        return atof(a.c_str()) + atof(b.c_str());

    if(op == "-")
        return atof(a.c_str()) - atof(b.c_str());

    if(op == "*")
        return atof(a.c_str()) * atof(b.c_str());

    if((op == "/") && (atof(b.c_str())!=0.0))
        return atof(a.c_str()) / atof(b.c_str());

    else return 0.0;
}


Matrix QMatrixLibrary:: calculateMatrixFloat (const std::string & op,
                                             const std::string & a,
                                             const double & b) const
{
    const Matrix* m_a;
    m_a=find(QString::fromStdString(a));

    Matrix identite(m_a->getNbRows(),m_a->getNbCols(),Matrix::I);
    Matrix bmatrix;
    bmatrix=static_cast<double>(b)*identite;



    if(op == "+")
        return *m_a + bmatrix ;

    if(op == "-")
        return *m_a - bmatrix;

    if(op == "/")
    {
        double scale;
        scale = static_cast<double>(1/b);
        return *m_a * scale;
    }

    else return *m_a;
}


Matrix QMatrixLibrary:: calculateFloatMatrix(const std::string &op, const std::string &a,
                                            const float &b)const
{
    const Matrix* m_a;
    m_a = find(QString::fromStdString(a));

    Matrix identite(m_a->getNbRows(),m_a->getNbCols(),Matrix::I);
    Matrix bmatrix;
    bmatrix = static_cast<double>(b)*identite;

    if(op == "+")
        return *m_a + bmatrix ;

    if(op == "-")
        return bmatrix - *m_a;

    else return *m_a;
}


void QMatrixLibrary:: polish(const std::string & chain ,
                            std::vector<std::string> & polish_notation)const
{

    stack<string> p;
    vector<string> expression;
    copyVector(expression,explode(chain));

    for (auto i : expression)
    {
        if ( (!isOperator(i)) && (i != "(") && (i != ")") && (i != "=") )
        {
            polish_notation.push_back(i);
        }
        else if ( (i == "("))
        {
            p.push(i);

        }
        else if (isOperator(i))
        {
            if (!p.empty())
            {
                while ((!p.empty()) && highEqualPriority(i,p.top()))
                {
                    polish_notation.push_back(p.top());
                    p.pop();
                }
            }

            p.push(i);


        }
        else if (i == ")")
        {
           do
            {
                if (p.top() != "(")
                {
                    polish_notation.push_back(p.top());
                    p.pop();
                }

            }while ((p.top() !=  "(") && (!p.empty()));

            if (p.top() != "")
                p.pop();
        }

    }
    if(polish_notation[polish_notation.size()-1]=="")
        polish_notation.pop_back();


    while (!p.empty())
    {
        polish_notation.push_back(p.top());
        p.pop();
    }

}


string QMatrixLibrary:: isCalculableExpression(const string & expression)const
{
   string expressionCopy = expression;
   expressionCopy.insert(0, 1, '(');
   expressionCopy.push_back(')');
   expressionCopy.erase(remove(expressionCopy.begin(),
                               expressionCopy.end(), ' '),
                        expressionCopy.end());

   vector<string> result = explode(expressionCopy);
   unsigned long int i, s = result.size();

   string calculable = "calculable";

   if (s == 0)
       return "Expression vide";
   if (s == 1)
   {
       if (isName(QString::fromStdString(result[0])))
       {
           if (find(QString::fromStdString(result[0])) != nullptr)
               return calculable;
           else
               return ("La matrice " + result[0] + " n'existe pas dans la librairie");
       }
       else
           return ("Aucune matrice dans l'expression saisie");
   }

   short int nbp = 0;

   for (i = 0; i < s; i++)
   {
       if (result[i] == "(")
       {
           nbp++;
       }
       else if (result[i] == ")")
       {
           nbp--;
           if (nbp < 0)
           return "Parenthèse fermante détectée..."
                  "\nVeuillez vérifier l'organisation des parenthèses" ;
       }
   }

   if (nbp != 0)
       return "Nombre de parenthèses ouvrantes différent du nombre de parenthèses fermantes" ;

   vector<string> no_parenthesis;

   for (i = 0; i < s; i++)
   {
       if (result[i] != "(" && result[i] != ")")
       {
           no_parenthesis.push_back(result[i]);
       }

       else if (result[i] == "(")
       {

           if (i == s - 1)
                return ("Impossible de calculer une expression se terminant par '(' ");
            else if (result[i+1] == ")")
            {
                return ("Impossible de calculer '()'");
            }
       }

       else
       {
           if (result[i] == " ")
               return ("Les espaces ne sont pas autorisés");
           if (isSpecialCaractere(result[i]) && result[i] != ")")
               return ("Les caractères spéciaux ne sont pas autorisés comme '" + result[i]
                       + "' ne sont pas autorisés");
       }

   }

    s = no_parenthesis.size();

    string error1 = "Expression vide" ;

    if (s == 0)
        return error1;
    if (s == 1)
    {
        if (isName(QString::fromStdString(no_parenthesis[0])))
        {
            if (find(QString::fromStdString(no_parenthesis[0])) != nullptr)
                return calculable;
            else
                return ("La matrice " + no_parenthesis[i] + " n'existe pas dans la librairie");
        }
        else
            return ("Aucune matrice dans l'expression saisie");
    }

    string error3a = "Calcul de " ;
    string error3b = " impossible" ;
    bool matrix_result = false;

    for(i = 0; i < s; i++)
    {
        if (no_parenthesis[i] == "^")
        {
            if (i == 0)
                return ("Une expression ne peut pas débuter par '^' ");
            else if (!isName(QString::fromStdString(no_parenthesis[i-1])) && no_parenthesis[i-1] != "~")
                return ("On ne peut calculer que les puissances de matrices");
            if (i < s - 1 && isName(QString::fromStdString(no_parenthesis[i+1])) )
                return "On ne peut calculer que les puissances de matrices";
            else if (i == s - 1)
                return "L'opérateur '^' doit être suivi d'un entier";
        }

        else if (no_parenthesis[i] == "~")
        {
            if (i == 0)
                return ("L'expression ne peut pas commencer par '~'"
                        "\nVeuillez saisir 'M~' pour désigner l'inverse d'une matrice");
            else if (!isName(QString::fromStdString(no_parenthesis[i-1])) && no_parenthesis[i-1] != "~")
                    return ("On ne peut calculer que l'inverse d'une matrice");
            if (i == s - 2)
                return ("Calcul de " + no_parenthesis[i-1] + no_parenthesis[i]
                        + no_parenthesis[i+1] + "impossible");
            if (i < s - 1)
                 if (!isOperator(no_parenthesis[i+1]))
                    if (no_parenthesis[i+1] != "^")
                        return "L'opérateur '~' doit être suivi d'un second opérateur";

        }

        else if (isOperator(no_parenthesis[i]))
        {
            if (i == 0)
                return ("L'expression ne peut pas débuter par un opérateur");
            if (i == s - 1)
                return ("Impossible de calculer " + no_parenthesis[i-1] + no_parenthesis[i]);
            if (isOperator(no_parenthesis[i-1]) && no_parenthesis[i-1] != "~")
                return ("Calcul de " + no_parenthesis[i] + no_parenthesis[i+1] + " impossible!");
        }

        else if (isName(QString::fromStdString(no_parenthesis[i])))
        {
            matrix_result = true;

            if (find(QString::fromStdString(no_parenthesis[i])) == nullptr)
                return ("La matrice " + no_parenthesis[i] + " n'existe pas dans la librairie");

            if (i == 0)
                continue;
            if (i == 1)
                return (error3a + no_parenthesis[i-1] + no_parenthesis[i] + error3b);
            if (i < s - 1 && no_parenthesis[i+1] == "~")
                    {
                        if ((i < s - 2) && !isOperator(no_parenthesis[i+2]))
                            return "L'opérateur '~' doit être suivi d'un opérateur";
                    }

            if ( (i > 1) && (i < s - 2) )
            {
                if (!isOperator(no_parenthesis[i-1]))
                    return (error3a + no_parenthesis[i-1] + error3b);
                else if ( (!isName(QString::fromStdString(no_parenthesis[i-2]))) && (!isFloat(no_parenthesis[i-2])) )
                    return (error3a + no_parenthesis[i-2] + no_parenthesis[i-1]
                            + no_parenthesis[i] + error3b);
                if (no_parenthesis[i+1] == "^")
                {
                    if (!isFloat(no_parenthesis[i+2]))
                        return (error3a + no_parenthesis[i] + no_parenthesis[i+1]
                                + no_parenthesis[i+2] + error3b + "\n"
                                + no_parenthesis[i+2] + " doit être un entier");
                    if (atoi(no_parenthesis[i+2].c_str()) < 0)
                        return (error3a + no_parenthesis[i] + no_parenthesis[i+1]
                                + no_parenthesis[i+2] + error3b
                                + "\nVeuillez utiliser '~' pour désigner l'inverse d'une matrice");
                    if (atoi(no_parenthesis[i+2].c_str()) - atof(no_parenthesis[i+2].c_str()) != 0.0)
                        return (error3a + no_parenthesis[i]
                                + no_parenthesis[i+1] + no_parenthesis[i+2]
                                + error3b + "...\nCalcul d'une puissance réelle impossible");
                        }

                    }

                }

        else if (isFloat(no_parenthesis[i]))
        {
            if (i == 0)
                continue;
            if (i == 1)
                return (error3a + no_parenthesis[i-1] + no_parenthesis[i] + error3b);
            if (i == s - 2)
                return (error3a + no_parenthesis[i] + no_parenthesis[i+1] + error3b);
            if (!isOperator(no_parenthesis[i-1]))
            {
                if (no_parenthesis[i-1] != "^")
                    return (error3a + no_parenthesis[i-1] + no_parenthesis[i] + error3b);
                if (atof(no_parenthesis[i].c_str()) < 0.0)
                    return (error3a + no_parenthesis[i-2] + no_parenthesis[i-1]
                            + no_parenthesis[i] + error3b
                            + "\nVeuillez utiliser 'M~' pour désigner l'inverser d'une matrice M");
                if (atof(no_parenthesis[i].c_str())
                        - atoi(no_parenthesis[i].c_str()) != 0.0)
                    return ("Calcul d'une puissance réelle impossible, "
                            "veuillez saisir un entier");
            }
            else if ( (i < s - 1) && isName(QString::fromStdString(no_parenthesis[i+1])))
                return "L'opération " + no_parenthesis[i] + no_parenthesis[i+1]
                        + " n'est pas définie" ;

        }

    }

    if (!matrix_result)
        return "Le résultat de sortie n'est pas une matrice!" ;

    return calculable;
}


Matrix QMatrixLibrary:: calculateExpression(const std::string & chain)const
{
    string chainCopy = chain;
    chainCopy.insert(0, 1, '(');
    chainCopy.push_back(')');
    chainCopy.erase(remove(chainCopy.begin(), chainCopy.end(), ' '), chainCopy.end());

    QMatrixLibrary copy(*this);
    vector<string> polish_not;
    copy.polish(chainCopy,polish_not);      //I write my expression in Polish notation

    stack<string> pile;
    Matrix temp;
    string identify;
    int name=0;

    for (auto i : polish_not)
    {
        if (i == "~")
        {
            /* if the current element is a tilde, I calculate the inverse of the matrix*/

            string a = pile.top();
            pile.pop();

            temp= *(copy.find(QString::fromStdString(a)))^-1;

            identify = static_cast<char>('0'+ name);
            pile.push("temp" + identify);
            copy.addMatrix(QString::fromStdString("temp" + identify),temp);
            name++;
        }
        else if ((copy.isOperator(i)) && (i != "~"))
        {
            /* In the case of binary operation, I extract both operands from the stack*/

            string b = pile.top();
            pile.pop();
            string a = pile.top();
            pile.pop();

            /* depending on the type of the two operands I calculate the result */

            if ((copy.isName(QString::fromStdString(b)) && copy.isName(QString::fromStdString(a)))
                    || (copy.isFloat(a) && copy.isName(QString::fromStdString(b)))
                    || (copy.isFloat(b) && copy.isName(QString::fromStdString(a))) )
            {
                if ((copy.isName(QString::fromStdString(b)) && copy.isName(QString::fromStdString(a))))
                {
                    temp = copy.calculate(i,a,b);
                }
                else if (copy.isFloat(b) && copy.isName(QString::fromStdString(a)))
                {
                    if(i == "*")
                    {
                        temp = *(copy.find(QString::fromStdString(a))) * atof(b.c_str());
                    }
                    else if (i == "^")
                    {
                        temp= *(copy.find(QString::fromStdString(a))) ^ (atoi(b.c_str()));
                    }
                    else
                    {
                        float scale;
                        scale = static_cast<float>(atof(b.c_str()));
                        temp =copy.calculateMatrixFloat(i,a,scale);
                    }
                }
                else if (copy.isFloat(a) && copy.isName(QString::fromStdString(b)))
                {
                    if(i == "*")
                    {
                        temp = *(copy.find(QString::fromStdString(b))) * atof(a.c_str());

                    }
                    else
                    {
                        float scale;
                        scale = static_cast<float>(atof(a.c_str()));
                        temp = copy.calculateFloatMatrix(i,b,scale);
                    }
                }

                /* I store the resulting matrix in the library and its name in the stack */

                identify = static_cast<char>('0'+ name);
                pile.push ("temp" + identify);          // i choose different names for the saved matrices
                copy.addMatrix (QString::fromStdString("temp" + identify), temp);
                name++;
            }
            else if (  copy.isFloat(a) && copy.isFloat(b) )
            {
                /* if both operands are floats i calculate the result diffrently then i store it in the stack */
                ostringstream ss;
                ss << copy.calculateFloat (i,a,b);
                string res = ss.str();
                pile.push(res);
            }
            else
            {
                return Matrix::matrix_null;
            }
        }
        else
        {
            /* if the current element is not an operator, i store it in the stack  */
            pile.push(i);
        }
    }

    /* the stack contains the name of the resulting matrix */

    const Matrix* res;
    res = copy.find(QString::fromStdString(pile.top()));
    Matrix result(*res);

    for(int i = 0; i <= name - 1; i++)
    {
        identify = static_cast<char>('0'+ i);
        copy.erase(QString::fromStdString("temp" + identify));                       // I empty the library from intermediate matrices
    }


    return result;
}


// to recode later, we must implement expr support
void QMatrixLibrary:: saveFile (const string & filename) const
{
    ofstream file (filename.c_str());

    if(!file.is_open())
    {
        cout << "Erreur lors de la lecture du fichier "
                "\nVeuillez vérifier le chemin du fichier" << endl;
        exit(EXIT_FAILURE);
    }

    file << "Matrix .mtmx" << endl;
    file << "nb " << size() << endl << endl;

    for (const auto& [ name, userMatrix ] : *this)
    {
       string matrixname = name.toStdString();
       Matrix matrix = userMatrix.matrix;
       unsigned int nbRows = matrix.getNbRows();
       unsigned int nbCols = matrix.getNbCols();

       file << endl;
       file << "name " << matrixname << endl;
       file << "rows " << nbRows << endl << "cols " << nbCols << endl;

       for (unsigned int i = 0; i < nbRows; i++)
       {
           file << endl;
           for (unsigned int j = 0; j < nbCols; j++)
           {
               file << userMatrix.entries[i * nbCols + j].toStdString();
               file << endl;
           }
       }
       cout << "La sauvegarde de la matrice " << matrixname
            << " est réussie" << endl << endl;
    }

    file.close();
}

// To recode later, we must implement expr support
void QMatrixLibrary:: readFile (const string & filename)
{
    string matrixname;
    unsigned int r;
    unsigned int c;
    unsigned int nbMatrices;
    ifstream file (filename.c_str());

    clear();

    if(!file.is_open())
    {
      cout << "Erreur lors de la lecture du file \nVeuillez vérifier le chemin du file" << endl;
    }

    string testfile;
    string entry;
    string trash;

    getline(file, testfile); // read top indicator

    if( testfile == "Matrix .mtmx")
    {
      file >> trash >> nbMatrices;

      for(unsigned int i = 0; i < nbMatrices; ++i)
      {
          file >> matrixname >> matrixname; // get name
          file >> trash >> r; //get rows
          file >> trash >> c; //get cols

          UserInputs inputs(r, c);

          getline(file, trash); // cr/lf between matrices

          for(unsigned int i = 0; i < r; ++i) {
              getline(file, trash); // cr/lf between lines
              for(unsigned int j = 0; j < c; ++j) {
                  getline(file, entry);
                  inputs.put(QString::fromStdString(entry));
              }
          }

          addMatrix(QString::fromStdString(matrixname), inputs);
      }

      file.close();

    }
    else
    {
      cout << "Erreur, ce fichier ne contient pas des matrices !" << endl ;

    }
}
