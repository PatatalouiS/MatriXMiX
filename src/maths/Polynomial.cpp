
#include <iostream>
#include <vector>
#include <math.h>
#include <cassert>
#include <complex>
#include "VectorX.h"
#include "Polynomial.h"

using namespace std;


const double EPSILON=0.0001;
const Polynomial Polynomial:: polynomial_null = Polynomial();



Polynomial :: Polynomial() : tab (vector<complex<double>>(1,0))
{
    this->degree = 0;
}


Polynomial :: Polynomial(const unsigned int & d) : tab(vector<complex<double>>(d+1,1))
{
    this->degree = d;
}


Polynomial :: Polynomial(const unsigned int & d, const VectorX & values)
{
    if ( values.size() != d + 1 )
    {
        cerr << "Erreur : Pas le nombre de coefficients" << endl;
        return;
    }

    this->degree = d;

    for (auto i : values)
    {
        tab.push_back(i);
    }

}


Polynomial::Polynomial(const Polynomial &p) : tab (vector<complex<double>>(p.tab))
{
    degree = p.degree;
}


void Polynomial::debugAffiche()
{
    unsigned int i;
    cout << "Affichage du polynôme de degrée " << degree << endl << endl;

    for (i = 0; i < degree + 1; i++)
    {
        cout << "degrée : " << i << "   " << tab[i].real() << " ; " << tab[i].imag() << endl;
    }

}


ostream& operator << (ostream& flux, const Polynomial & p)
{

    unsigned int i;

    if (p.tab[0].real() == 0.0)
    {
        if (p.tab[0].imag() != 0.0)
            {
                if (p.tab[0].imag() == 1.0)
                    flux << "i";
                else if (p.tab[0].imag() == - 1.0)
                    flux << "-i";
                else
                    flux << p.tab[0].imag() << "i";
            }
    }
    else if (p.tab[0].real() > 0.0)
    {

        if (p.tab[0].imag() > 0.0)
            flux << "(" << p.tab[0].real() << "+" << p.tab[0].imag() << "i)";
        else if (p.tab[0].imag() < 0.0)
            flux << "(" << p.tab[0].real() << p.tab[0].imag() << "i)";
        else //p.tab[0].imag() == 0.0
            flux << p.tab[0].real();
    }
    else //p.tab[0].real() < 0.0
    {
        if (p.tab[0].imag() == 0.0)
            flux << p.tab[0].real();
        else if (p.tab[0].imag() > 0.0)
            flux << "(" << p.tab[0].real() << "+" << p.tab[0].imag() << "i)";
        else //p.tab[0].imag() < 0.0
            flux << "- (" << abs(p.tab[0].real()) << "+" << abs(p.tab[0].imag()) << "i)";
    }


    for (i = 1; i < p.degree + 1; i++  )
    {
        double re (p.tab[i].real());
        double im (p.tab[i].imag());

        if (re == 0.0)
        {
            if (im > 0.0)
                {
                    if (im == 1.0)
                        flux << " + iX^" << i;
                    else
                        flux << " + " << im << "iX^" << i;
                  }
            else if (im < 0.0)
                {
                    if (im == -1.0)
                        flux << " - iX^" << i;
                    else
                        flux << " - " << abs(im) << "iX^" << i;
                }
        }
        else if (re > 0.0)
        {

                if (im > 0.0)
                {
                    flux << " + (" << re << "+" << im << "i)X^" << i;
                }
                else if (im < 0.0)
                    flux << " + (" << re << im << "i)X^" << i;
                else //im == 0.0
                    flux << " + " << re << "X^" << i;

        }
        else //re < 0.0
        {
            if (im == 0.0)
                flux << " + " << re << "X^" << i;
            else if (im > 0.0)
                flux << " + (" << re << "+" << im << "i)X^" << i;
            else //im < 0.0
                flux << "-(" << abs(re) << "+" << abs(im) << "i)X^" << i;
        }
    }



    return flux;
}


Polynomial& Polynomial:: operator = (const Polynomial & p)
{
    this->degree = p.degree;
    tab = vector<complex<double>>(this->degree + 1,0);
    unsigned int i;
    for (i = 0; i <= degree; i++)
    {
        tab[i]=p.tab[i];
    }

    return (*this);
}


bool Polynomial:: operator == (const Polynomial & p) const
{
    if(degree != p.degree)
        return false;
    unsigned int i;
    for(i = 0; i < degree; i++)
        if (tab[i] - p.tab[i] != 0.0)
            return false;

    return true;
}


const Polynomial Polynomial:: operator + (const Polynomial & p)const
{
    unsigned int i;
    if (degree > p.degree)
    {
        Polynomial result(*this);

        for (i = 0; i <= p.degree; i++)
        {
            result.tab[i] += p.tab[i];
        }

        return result;

    }
    else
    {
        Polynomial result(p);

        for (i = 0; i <= degree;i++)
        {
            result.tab[i] += tab[i];
        }

        return result;
    }

}


const Polynomial Polynomial:: operator - (const Polynomial & p)const
{
    unsigned int i, mindegree,k,tampon;

    Polynomial result(*this);

    if (degree > p.degree)
    {
        mindegree = p.degree;
    }
    else
    {
        mindegree = degree;
    }
    for(i = 0; i <= mindegree; i++)
    {
        result.tab[i] -= p.tab[i];
    }

    if (mindegree == degree)
    {
        for(i = mindegree + 1; i <= p.degree; i++)
        {
            result.tab.push_back(-p.tab[i]);
            result.degree++;
        }
    }

    tampon = 0;
    k = result.degree;

    while (result.tab[k] == 0.0 && k > 0)
    {
        tampon++;
        k--;
    }
    result.degree = result.degree-tampon;


    return result;
}


const Polynomial Polynomial:: operator * (const Polynomial & p)const
{
    unsigned int i,j,k,d = degree + p.degree;
    Polynomial result(d);

    for (i = 0; i <= d; i++)
        result.tab[i] = 0;

    for (i = 0; i <= d; i++)
    {
        for (j = 0; j <= degree; j++)
        {
            for (k = 0; k <= p.degree; k++)
            {
                if (j+k==i)
                {
                    result.tab[i] += tab[j] * p.tab[k];
                }
            }
        }
    }
    return result;
}


const Polynomial Polynomial:: operator * (const double & scale)const
{
    unsigned int i;
    Polynomial p(*this);
    for (i = 0; i <= degree; i++)
    {
        p.tab[i] *= scale;
    }
    return p;
}


const Polynomial Polynomial:: division(const Polynomial & divisor, Polynomial & rest)
{
    Polynomial quotient(degree - divisor.degree);
    Polynomial copy(*this);

    unsigned int i = 0, j, tampon;
    unsigned long k;

    while ((copy.degree - i >= divisor.degree)
           && (static_cast<int>(copy.degree - i) >= 0))
    {
        quotient.tab[copy.degree - divisor.degree - i] =
                copy.tab[copy.degree - i]
                / divisor.tab[divisor.degree];
        for (j = i; j <= divisor.degree; j++)
        {
            copy.tab[copy.degree - j] = copy.tab[copy.degree - j]
                                        - divisor.tab[divisor.degree - (j - i)]
                                          * quotient.tab[copy.degree - divisor.degree - i];

        }
        i++;
    }

    copy = quotient * divisor;
    rest = (*this) - copy;


    tampon = 0;
    k = rest.degree;
    while ((rest.tab[k] == 0.0) && (k != 0))
    {
        tampon++;
        k--;
    }
    rest.degree = rest.degree - tampon;

    if (rest.degree > divisor.degree)
    {

        Polynomial quotient2 (rest.degree - divisor.degree);
        quotient2 = rest.division(divisor,rest);
        quotient = quotient+quotient2;
    }

    return quotient;
}



void Polynomial::regressionTest() const
{
  VectorX v;
  complex<double> c1(1,0);
  v.push_back(c1);
  complex<double> c2(0,0);
  v.push_back(c2);
  v.push_back(c1);
  Polynomial p(2,v);
  cout << "Affichage de p" << endl << p << endl << endl;
  cout << "Affichage debug de p" << endl;
  p.debugAffiche();
}
