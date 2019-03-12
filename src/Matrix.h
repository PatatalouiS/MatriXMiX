
#ifndef _MATRIX_H
#define _MATRIX_H


#include <vector>
#include "VectorX.h"


class Matrix
{
    private:

    unsigned int rows;
    unsigned int cols;
    std::vector<std::vector<double>> tab;

    public:

    /**
     * @brief Constructeur par défaut
     */
    Matrix ();

    /**
     * @brief Constructeur
     * @details constructeur avec deux paramètres
     * @param rows (nombre de lignes)
     * @param cols (nombre de colonnes)
     */
    Matrix ( const unsigned int rows, const unsigned int cols );

    /**
     * @brief Constructeur
     * @details constructeur avec 3 paramètres
     * @param rows (nombre de lignes)
     * @param cols (nombre de colonnes)
     * @param values (vecteur de valeurs à introduire dans la matrice)
     */
    Matrix ( const unsigned int rows, const unsigned int cols, const VectorX & values );

    /**
     * @brief Constructeur par copie
     * @param m
     */
    Matrix ( const Matrix & m );

    /**
     * @brief Destructeur
     */
    ~Matrix ();


    double& getVal ( const unsigned int indice );
    double getVal ( const unsigned int indice ) const;
    std::vector<double>& operator [] ( const unsigned int indice );
    const std::vector<double>& operator [] ( const unsigned int indice ) const;
    friend std::ostream& operator << ( std::ostream& flux, const Matrix & m );

    /**
     * @brief Accesseur
     * @details récupère le nombre de lignes d'une matrice
     * @return \e unsigned int
     */
    unsigned int getRows() const;

    /**
     * @brief Accesseur
     * @details récupère le nombre de colonne d'une matrice
     * @return \e unsigned int
     */
    unsigned int getCols() const;

    /**
     * @brief Génère une matrice aléatoire
     * @param r
     * @param c
     * @return \e Matrix
     */
    Matrix randomMatrix(const unsigned int & r, const unsigned int & c);

    /**
     * @brief Matrice identité
     * @details renvoie la matrice identité de la bonne dimension
     * @return \e Matrix
     */
    Matrix identityMatrix();

    /**
     * @brief Matrice transposée
     * @return \e Matrix
     */
    Matrix transposeMatrix();

    /**
     * @brief Addition de matrices
     * @details ATTENTION: les matrices doivent etre de memes dimensions!
     * @param m
     * @return \e Matrix
     */
    Matrix additionMatrix(const Matrix & m);

    /**
     * @brief Soustraction de matrices
     * @details ATTENTION: les matrices doivent etre de memes dimensions!
     * @param m \e Matrix
     * @return \e Matrix
     */
    Matrix soustractionMatrix(const Matrix & m);

    /**
     * @brief Multiplication par un scalaire
     * @param lambda (double)
     * @return \e Matrix
     */
    Matrix multiplicationScale(const double & lambda);

    /**
     * @brief Multplication par une matrice
     * @param m (Matrix)
     * @return \e Matrix
     */
    Matrix multiplicationMatrix(const Matrix & m);

    /**
     * @brief Retourne vrai si la matrice est carrée
     * @return \e bool
     */
    bool squareMatrix() const;

    /**
     * @brief Retourne vrai si la matrice est égale à celle passée en paramètre
     * @param m (Matrix)
     * @return \e bool
     */
    bool isEqualMatrix(const Matrix & m);

    /**
     * @brief Opérateur +
     * @param m (Matrix)
     * @return \e Matrix
     */
    const Matrix operator + (const Matrix & m);

    /**
     * @brief Opérateur -
     * @param m (Matrix)
     * @return \e Matrix
     */
    const Matrix operator - (const Matrix & m);

    /**
     * @brief Opérateur *
     * @details Matrix * Matrix
     * @param m (Matrix)
     * @return \e Matrix
     */
    const Matrix operator * (const Matrix & m);

    /**
     * @brief Opérateur *
     * @details Matrix * double
     * @param lambda
     * @return \e Matrix
     */
    const Matrix operator * (const double & lambda);

    /**
     * @brief Opérateur ==
     * @param m (Matrix)
     * @return \e bool
     */
    bool operator == (const Matrix & m);

    /**
     * @brief Opérateur !=
     * @param m (Matrix)
     * @return \e bool
     */
    bool operator != (const Matrix & m);

    /**
     * @brief Puissance de matrice
     * @param p (int)
     * @return \e Matrix
     */
    Matrix powerMatrix(const int & p);

    /**
     * @brief Puissance de matrice
     * @param p (int)
     * @return \e Matrix
     */
    Matrix powerMat(Matrix& m,const int & p);

    /**
     * @brief Sauvegarde d'une matrice dans un fichier .txt
     * @param filename (string)
     */
    void saveMatrix(const std::string & filename);

    /**
     * @@brief Interpréte un fichier .txt pour construire une matrice
     * @param filename (string)
     */
    void readMatrix(const std::string & filename);

    /**
     * @brief Calcul de la trace d'une Matrice
     * @return \e double
     */
    double traceMatrix() const;

    /**
     * @brief Renvoie la sous-matrice en supprimant la a-ième ligne et la b-ième colonne
     * @param a (unsigned int)
     * @param b (unsigned int)
     * @return \e Matrix
     */
    Matrix subMatrix(const unsigned int & a, const unsigned int & b);

    double determinant(unsigned int dim);

    /**
     * @brief Calcul du déterminant d'une matrice
     * @return \e double
     */
    double determinant();

    /**
     * @brief Renvoie la comatrice associée
     * @return \e Matrix
     */
    Matrix coMatrix();

    /**
     * @brief Renvoie l'inverse d'une matrice
     * @return \e Matrix
     */
    Matrix inverse();

    /**
     * @brief Divise une matrice par une matrice
     * @param m (Matrix)
     * @return \e Matrix
     */
    Matrix divideMatrix(const Matrix & m);

    /**
     * @brief Opérateur /
     * @param m (Matrix)
     * @return \e Matrix
     */
    const Matrix operator / (const Matrix & m);

    /**
     * @brief Opérateur ^ (puissance)
     * @param p (int)
     * @return \e Matrix
     */
    const Matrix operator ^ (const int & p);


};

Matrix identityMatrix(const unsigned int & n);


#endif