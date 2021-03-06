/*
 __  __       _        ___  ____  __ ___  __
|  \/  | __ _| |_ _ __(_) \/ /  \/  (_) \/ /
| |\/| |/ _` | __| '__| |\  /| |\/| | |\  /
| |  | | (_| | |_| |  | |/  \| |  | | |/  \
|_|  |_|\__,_|\__|_|  |_/_/\_\_|  |_|_/_/\_\

Copyright (C) 2019-2020, Sebia Hana, Cerbulean Ana-Maria, Boumaza Tarik, Olivié Maxime.

This file is part of MatriXMiX.

MatriXMiX is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MatriXMiX is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with MatriXMiX.  If not, see <https://www.gnu.org/licenses/>

*/

#include <iostream>
#include <vector>
#include <math.h>
#include <cassert>
#include <complex>
#include "VectorX.h"
#include "Polynomial.h"
#include "Utils.hpp"


static const double EPSILON = 0.000001;


Polynomial :: Polynomial() : tab (std::vector<std::complex<double>>(1,0))
{
    this->degree = 0;
}


Polynomial :: Polynomial(const unsigned int & d) : 
                tab(std::vector<std::complex<double>>(d+1,1))
{
    this->degree = d;
}


Polynomial :: Polynomial(const unsigned int & d, const VectorX & values)
{
    if ( values.size() != d + 1 )
    {
        std::cerr << "Erreur : Pas le nombre de coefficients" << std::endl;
        return;
    }

    this->degree = d;

    for (auto i : values)
    {
        tab.push_back(i);
    }

}


Polynomial::Polynomial(const Polynomial &p) : 
            tab (std::vector<std::complex<double>>(p.tab))
{
    degree = p.degree;
}


Polynomial Polynomial::check() const {
    VectorX vect;
    double re, im;
    for (unsigned int i = 0 ; i <= degree ; i++) {
        if (abs(tab[i].real() - std::round(tab[i].real())) < EPSILON)
            re = std::round(tab[i].real());
        else
            re = tab[i].real();
        if (abs(tab[i].imag() - std::round(tab[i].imag())) < EPSILON)
            im = std::round(tab[i].imag());
        else
            im = tab[i].imag();
        vect.push_back(std::complex<double>(re,im));
    }

    return (Polynomial(degree,vect));
}


void Polynomial::debugAffiche()
{
    unsigned int i;
    std::cout << "Affichage du polynôme de degrée " 
                << degree << std::endl << std::endl;

    for (i = 0; i < degree + 1; i++)
    {
        std::cout << "degré : " << i << "   " << tab[i].real()
                << " ; " << tab[i].imag() << "i" << std::endl;
    }

}


std::ostream& operator << (std::ostream& flux, const Polynomial & p)
{

    unsigned int i;
	double re = p.tab[0].real();
    double im = p.tab[0].imag();


    if (re == 0.0)
    {
        if (im != 0.0)
            {
                if (im == 1.0)
                    flux << "i";
                else if (im == - 1.0)
                    flux << "-i";
                else
                    flux << Utils::print(im) << "i";
            }
    }
    else if (re > 0.0)
    {

        if (im > 0.0)
		{
			if (im == 1.0)
				flux << "(" << Utils::print(re) << "+i)";
			else
				flux << "(" << Utils::print(re) << "+" << Utils::print(im) << "i)";
		} 
        else if (im < 0.0) {
			if (im == -1.0)
				flux << "(" << Utils::print(re) << "-i)";
			else
				flux << "(" << Utils::print(re) << Utils::print(im) << "i)";
		}
        else //im == 0.0
            flux << Utils::print(re);
    }
    else //re < 0.0
    {
        if (im == 0.0)
            flux << Utils::print(re);
        else if (im > 0.0)
            flux << "(" << Utils::print(re) << "+" << Utils::print(im) << "i)";
        else //im < 0.0
            flux << "-(" << Utils::print(abs(re)) << "+"
                  << Utils::print(abs(im)) << "i)";
    }

    for (i = 1; i < p.degree + 1; i++  )
    {
        re = p.tab[i].real();
		im = p.tab[i].imag();

        if (re == 0.0)
        {
            if (im > 0.0)
                {
                    if (im == 1.0)
                        flux << " + iX";
                    else
                        flux << " + " << Utils::print(im) << "iX";
                  }
            else if (im < 0.0)
                {
                    if (im == -1.0)
                        flux << " - iX";
                    else
                        flux << " - " << Utils::print(abs(im)) << "iX";
                }
        }
        else if (re > 0.0)
        {

            if (im > 0.0)
            {
                flux << " + (" << Utils::print(re) << "+" << Utils::print(im) << "i)X";
            }
            else if (im < 0.0)
                flux << " + (" << Utils::print(re) << Utils::print(im) << "i)X";
            else //im == 0.0
            {
                if (re == 1.0)
                    flux << " X";
                else
                    flux << " + " << Utils::print(re) << "X";
            }

        }
        else //re < 0.0
        {
            if (im == 0.0)
            {
                if (re == -1.0)
                    flux << " - X";
                else
                    flux << " " << Utils::print(re) << "X";
            }

            else if (im > 0.0)
			{
				if (im == 1.0)
                	flux << " + (" << Utils::print(re) << "+i)X";
				else
					flux << " + (" << Utils::print(re) << "+" << Utils::print(im) << "i)X";
			}

            else //im < 0.0 
			{
				if (im == -1.0)
					flux << "- (" << Utils::print(abs(re)) << "+i)X";
				else
					flux << "- (" << Utils::print(abs(re)) << "+" << Utils::print(abs(im)) << "i)X";
			}
        }

		if (i != 1)
			flux << "^" << i ;

    }

    return flux;
}


Polynomial& Polynomial:: operator = (const Polynomial & p)
{
    this->degree = p.degree;
    tab = std::vector<std::complex<double>>(this->degree + 1,0);
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


const Polynomial Polynomial:: division(const Polynomial & divisor, Polynomial & remain)
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
    remain = (*this) - copy;


    tampon = 0;
    k = remain.degree;
    while ((remain.tab[k] == 0.0) && (k != 0))
    {
        tampon++;
        k--;
    }
    remain.degree = remain.degree - tampon;

    if (remain.degree > divisor.degree)
    {

        Polynomial quotient2 (remain.degree - divisor.degree);
        quotient2 = remain.division(divisor,remain);
        quotient = quotient+quotient2;
    }

    return quotient;
}



void Polynomial::regressionTest() const
{
    Polynomial p1(1,{0,1});
    Polynomial p2(1,{1,1});
    Polynomial p3(2,{6,5,1});
    Polynomial p4(2,{2,3,1});
    Polynomial p5(5,{1,2,0,0,3,0.5});
    Polynomial p6(2,{-1,0,1});
    Polynomial p7(0,{1});

    Polynomial res1(1,{1,2});
    Polynomial res2(1,{4,2});
    Polynomial res3(3,{1,3,3,1});
    Polynomial res4(4,{0,0,6,5,1});
    Polynomial res5(5,{2,4,0,0,6,1});
    Polynomial res6(3,{18,34,18,3});
    Polynomial res7(1,{-1,1});
    Polynomial res8(1,{2,1});
    Polynomial res9(4,{2,0,0,3,0.5});
    Polynomial res10;
    Polynomial rest7(0);
    Polynomial rest9(0,{1});


    Polynomial result;
    Polynomial rest;

    result = p1 + p2;
    assert(result == res1);
    assert(result.degree == res1.degree);

    result = p3 - p4;
    assert(result == res2);
    assert(result.degree == res2.degree);

    result = p1 * p4 + p2;
    assert(result == res3);
    assert(result.degree == res3.degree);

    result = p1 * p1 * p3;
    assert(result == res4);
    assert(result.degree == res4.degree);

    result = p1 * p1 * p3;
    assert(result == res4);
    assert(result.degree == res4.degree);

    result = p5 * 2;
    assert(result == res5);
    assert(result.degree == res5.degree);

    result = p1 + p2 * p3 * 3;
    assert(result == res6);
    assert(result.degree == res6.degree);

    result = p6.division(p2,rest);
    assert(result == res7);
    assert(result.degree == res7.degree);
    assert(rest == rest7);
    assert(rest.degree == rest7.degree);

    result = p4.division(p2,rest);
    assert(result == res8);
    assert(result.degree == res8.degree);
    assert(rest == rest7);
    assert(rest.degree == rest7.degree);

    result = p5.division(p1,rest);
    assert(result == res9);
    assert(result.degree == res9.degree);
    assert(rest == rest9);
    assert(rest.degree == rest9.degree);


    result = p3.division(p7,rest);
    assert(result == p3);
    assert(result.degree == p3.degree);
    assert(rest == rest7);
    assert(rest.degree == rest7.degree);


}
