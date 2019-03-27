

#include <iostream>
#include <vector>
#include "VectorX.h"
#include "Polynomial.h"

using namespace std;

Polynomial :: Polynomial() : tab (1,0)
{
    degree=0;
}


Polynomial :: Polynomial(const unsigned int & d) : tab(d,1)
{
    degree=d;
}


Polynomial :: Polynomial(const unsigned int & d, const VectorX & values)
{
    if ( values.size() != d+1 )
    {
        cout << "Erreur : Pas le nombre de coefficients" << endl;
        exit ( EXIT_FAILURE );
    }

    this->degree = d;

    for ( unsigned int i=0; i<d+1; i++ )
    {
        tab.push_back(values[i]);
    }

}


Polynomial::Polynomial(const Polynomial &p) : tab (vector<double>(p.tab))
{
    degree = p.degree;
}


Polynomial::~Polynomial()
{
}


const Polynomial Polynomial:: operator + (const Polynomial & p)
{

    unsigned int i;

    if (degree>p.degree)
    {
        Polynomial resultat(*this);

        for (i=0; i<=p.degree;i++)
        {
            resultat.tab[i]+=p.tab[i];
        }

        return resultat;

    }
    else
    {
        Polynomial resultat(p);

        for (i=0; i<=degree;i++)
        {
            resultat.tab[i]+=tab[i];
        }

        return resultat;
    }

}


const Polynomial Polynomial:: operator - (const Polynomial & p)
{
    unsigned int i, mindegree;

    Polynomial resultat(*this);

    if(degree>p.degree)
        mindegree=p.degree;
    else
        mindegree=degree;

    for(i=0; i<=mindegree; i++)
    {
        resultat.tab[i]-=p.tab[i];
    }

    if(mindegree==degree)
    {
        for(i=mindegree+1; i<=p.degree; i++)
        {
            resultat.tab.push_back(-p.tab[i]);
            resultat.degree++;
        }
    }

    return resultat;
}


ostream& operator << (ostream& flux, const Polynomial & p)
{
    for ( auto i : p.tab )
    {
        flux << i << " ";
    }

    return flux;
}


const Polynomial Polynomial:: operator *(const Polynomial & p)
{
    unsigned int i,j,k,d=degree+p.degree;
    Polynomial result(d);

    for(i=0; i<d; i++)
        result.tab[i]=0;

    for(i=0; i<d; i++)
    {
        for(j=0; j<degree; j++)
        {
            for(k=0; k<p.degree; k++)
            {
                if(i==k+j)
                {
                    result.tab[i]+=(tab[j]+p.tab[k]);
                }

            }
        }
    }
    return result;
}