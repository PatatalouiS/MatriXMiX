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

#include <ostream>
#include <math.h>
#include <stdlib.h>
#include <string>

#include "Utils.hpp"

const double EPSILON = 0.000001;

namespace {

    void recursived2f(std::vector < long int > & tab,
        const double & rest) {
        if (tab.size() < 10 && rest > EPSILON) {
            double div, rest2;
            long int integer;
            div = 1 / rest;
            integer = static_cast < long int > (floor(div));
            rest2 = div - integer;
            tab.push_back(integer);
            recursived2f(tab, rest2);
        }
    }

    std::string double2sqrt_hard(const double & d) {
        unsigned int i = 3, j = 2;
        std::string num, denum, s;
        double r = d;
        bool found = false;

        if (d < 1)
            r = abs(1 / d);
        while (i < 1000 && !found) {
            j = 2;
            while (j < i && !found) {
                if (abs((sqrt(i) / sqrt(j)) - r) < EPSILON) {
                    if (abs(std::round(sqrt(i)) - sqrt(i)) < EPSILON)
                        num = std::to_string(static_cast<int>(std::round(sqrt(i))));
                    else
                        num =  std::string("\\sqrt{" + std::to_string(i)) + "}";
                    if (abs(std::round(sqrt(j)) - sqrt(j)) < EPSILON)
                        denum = std::to_string(static_cast<int>(std::round(sqrt(j))));
                    else
                        denum =  std::string("\\sqrt{" + std::to_string(j)) + "}";
                    found = true;
                }
                j++;
            }
            i++;
        }
        if (!found)
            return "";

        if (abs(d) < 1)
            s = "\\frac{" + denum + "}{" + num + "}";
        else
            s = "\\frac{" + num + "}{" + denum + "}";
        if (d < 0.0)
            s = "-" + s;

        return s;
    }
}


bool Utils::isFraction(const double & d) {
    long int integer = static_cast < long int > (d);
    double r = d - integer;
    if (r == 0.0)
        return false;

    return true;
}


const Fraction Utils::double2fraction(const double & d) {
    double abs_d = abs(d);
    std::vector < long int > tab;

    double rest;
    long int integer;
    unsigned long int size;

    integer = static_cast < long int > (floor(abs_d));
    rest = abs_d - integer;

    tab.push_back(integer);
    recursived2f(tab, rest);

    size = tab.size();

    if (size == 1) {
        Fraction f(tab[0], 1);
        if (d * f.getNumerator() > 0 && d * f.getDenominator() > 0) {
            return f;
        } else {
            f.setNumerator(f.getNumerator() * -1);
            return f;
        }
    }
    if (size == 2) {
        Fraction f(1, tab[1]);
        f = f + tab[0];
        if (d * f.getNumerator() > 0 && d * f.getDenominator() > 0) {
            return f;
        } else {
            f.setNumerator(f.getNumerator() * -1);
            return f;
        }
    }

    Fraction f(1, tab[size - 1]);

    for (unsigned long int i = size - 2; i > 0; i--) {
        f = f + tab[i];
        f = f.inverse();
        f = f.simplify();
    }

    f = f + tab[0];
    f = f.simplify();

    if (d * f.getNumerator() > 0 && d * f.getDenominator() > 0) {
        return f;
    } else {
        f.setNumerator(f.getNumerator() * -1);
        return f;
    }

}


std::string Utils:: double2sqrt(const double & d) {
    double res = abs(d);
    std::string s;

    if (res < 1) // cas 1/sqrt(x)
        res = 1 / res;

    int n = round(res * res);

    if (abs((res * res) - n) < EPSILON)
    {
        if (abs(std::round(sqrt(n)) - sqrt(n)) < EPSILON)
            s += std::to_string(static_cast<int>(std::round(sqrt(n))));
        else
            s += "\\sqrt{" + std::to_string(n) += "}";;
    }
    else
        return double2sqrt_hard(d);

    if (abs(d) < 1) {
      s = "\\frac{1}{" + s + "}";
    }
    if (d < 0.0)
        s = "-" + s;

    return s;

}


std::string Utils::print(const double & d) {
    if (abs(round(d) - d) < EPSILON)
        return std::to_string(static_cast<int>(round(d)));

    std::string s = double2sqrt(d);

    if (s != "")
        return s;

    Fraction f (d);

    s = std::to_string(f.getNumerator());

    if (s.size() < 4)
      return "\\frac{" + std::to_string(f.getNumerator()) + "}{"
              + std::to_string(f.getDenominator()) + "}";

    return std::to_string(d);
}


std::string Utils::complex2LaTeX (const std::complex<double> & coeff)
{
    std::string str;
    std::complex<double> casted = checkCast(coeff);

    if (casted.real() != 0.0)
    {
        if (casted.imag() > 0)
            str = print(casted.real()) + " + " + print(casted.imag()) + "$i$";
        else if (casted.imag() < 0)
        {
            str = print(casted.real()) + " - " + print(abs(casted.imag())) + "$i$";
        }
        else
        {
            str = print(casted.real());
        }
    }

    else
    {
        if (casted.imag() != 0.0)
            str = print(casted.imag()) + "$i$";
        else
            str = print(0);
    }

    return str;
}

std::complex<double> Utils::checkCast(const std::complex<double> & c)
{
    double re = c.real(), im = c.imag();
    int temp;

    temp = round(c.real());
    if (abs(temp - re) < EPSILON)
        re = static_cast<double>(temp);

    temp = round(c.imag());
    if (abs(temp - im) < EPSILON)
        im = static_cast<double>(temp);

    return { re, im };
}
