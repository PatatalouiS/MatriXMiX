#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>

#include "Fraction.h"
#include "Utils.hpp"

using namespace std;

const double EPSILON = 0.000001;

Fraction::Fraction() {
    numerator = 0;
    denominator = 1;
}

Fraction::Fraction(const long int & n) {
    numerator = n;
    denominator = 1;
}

Fraction::Fraction(const long int & n,
    const long int & d) {
    if (d != 0)
        denominator = d;
    else
        exit(EXIT_FAILURE);
    numerator = n;
}

Fraction::Fraction(const double & d) {
    numerator = Utils::double2fraction(d).numerator;
    denominator = Utils::double2fraction(d).denominator;
}

long int Fraction::getNumerator() const {
    return numerator;
}

long int Fraction::getDenominator() const {
    return denominator;
}

void Fraction::setNumerator(const long &n) {
    numerator = n;
}

void Fraction::setDenominator(const long &d) {
    denominator = d;
}

ostream & operator << (ostream & flux,
    const Fraction & f) {
    flux << f.numerator << "/" << f.denominator;
    return flux;
}

Fraction & Fraction::operator = (const Fraction & f) {
    numerator = f.numerator;
    denominator = f.denominator;

    return *this;
}

Fraction& Fraction::operator= (const double& d) {
    *this = Fraction(d);
    return *this;
}


bool Fraction::operator == (const Fraction & f) const {
    long int num1, num2;
    num1 = numerator * f.denominator;
    num2 = f.numerator * denominator;

    return (num1 == num2);

}

bool Fraction::operator < (const Fraction & f) const {
    double d1 = numerator / denominator;
    double d2 = f.numerator / f.denominator;

    return (d1 < d2);
}

const Fraction Fraction::inverse() const {
    Fraction f(denominator, numerator);
    return f;
}

long int Fraction::gcd(long int a, long int b) const {
    while (b != 0) {
        long int t = b;
        b = a % b;
        a = t;
    }

    return a;
}

const Fraction Fraction::simplify() const {
    long int div, num, den;
    div = gcd(numerator, denominator);
    num = numerator / div;
    den = denominator / div;

    if (den < 0) {
        den *= -1;
        num *= -1;
    }

    Fraction f(num, den);

    return f;

}

const Fraction Fraction::operator + (const Fraction & f) const {
    long int num, den;
    num = numerator * f.denominator + f.numerator * denominator;
    den = denominator * f.denominator;
    Fraction res(num, den);
    res = res.simplify();
    return res;
}

const Fraction Fraction::operator + (const long int & d) const {
    long int temp = d * denominator;
    temp = temp + numerator;
    Fraction res(temp, denominator);
    return res;
}

const Fraction Fraction::operator * (const Fraction & f) const {
    long int num, den;
    num = numerator * f.numerator;
    den = denominator * f.denominator;
    Fraction res(num, den);
    res = res.simplify();
    return res;
}

const Fraction Fraction::operator / (const Fraction & f) const {
    long int num, den;
    num = numerator * f.denominator;
    den = denominator * f.numerator;
    Fraction res(num, den);
    res = res.simplify();
    return res;
}


void Fraction::regressionTest() const {
    cout << endl << endl <<
        "****** DEBUT DU TEST DE REGRESSION DE FRACTION ******" <<
        endl << endl << endl;

    Fraction f1(1, 1);
    Fraction f2(1, 2);
    Fraction f3(1, 3);
    Fraction f4(3, 2);
    Fraction f5(25, 125);
    Fraction f6(5, 6);

    long int n = 2;
    double d1 = 0.3333333;
    double d2 = 0.857163;
    double temp;

    Fraction r1(3, 2);
    Fraction r2(7, 3);
    Fraction r3(3, 6);
    Fraction r4(1, 5);
    Fraction r5(150, 625);
    Fraction r6(1, 3);

    Fraction r;

    cout << "! Addition de 2 fractions" << endl; {
        r = f1 + f2;
        if (r == r1)
            cout << "Résultat correct! Poursuite..." << endl;
        else {
            cout << "Erreur détectée! \nEchec du test..." << endl;
            return;
        }
        cout << endl;
    }

    cout << "! Addition d'une fraction et d'un entier" << endl; {
        r = f3 + n;
        if (r == r2)
            cout << "Résultat correct! Poursuite..." << endl;
        else {
            cout << "Erreur détectée! \nEchec du test..." << endl;
            return;
        }
        cout << endl;
        cout << endl;
    }

    cout << "! Multiplication de deux fractions" << endl; {
        r = f3 * f4;
        if (r == r3)
            cout << "Résultat correct! Poursuite..." << endl;
        else {
            cout << "Erreur détectée! \nEchec du test..." << endl;
            return;
        }
        cout << endl;
        cout << endl;
    }

    cout << "! Simplification d'une fraction" << endl; {
        r = f5.simplify();
        if (r.numerator == r4.numerator && r.denominator == r4.denominator)
            cout << "Résultat correct! Poursuite..." << endl;
        else {
            cout << "Erreur détectée! \nEchec du test..." << endl;
            return;
        }
        cout << endl;
        cout << endl;
    }

    cout << "! Division de deux fractions" << endl; {
        r = f5 / f6;
        if (r == r5)
            cout << "Résultat correct! Poursuite..." << endl;
        else {
            cout << "Erreur détectée! \nEchec du test..." << endl;
            return;
        }
        cout << endl;
        cout << endl;
    }

    cout << "! Convertion d'un réel en fraction" << endl; {
        r = d1;
        if (r == r6)
            cout << "Résultat correct! Poursuite..." << endl;
        else {
            cout << "Erreur détectée! \nEchec du test..." << endl;
            return;
        }
        cout << endl;
        cout << endl;
    }

    cout << "! Convertion d'un réel en fraction n°2" << endl; {
        r = d2;
        temp = r.numerator;
        temp /= r.denominator;
        if (temp - d2 < EPSILON)
            cout << "Résultat correct! Poursuite..." << endl;
        else {
            cout << "Erreur détectée! \nEchec du test..." << endl;
            return;
        }
        cout << endl;
        cout << endl;
    }

    cout << endl << endl << "******* TEST REUSSI ******" << endl << endl <<
        "****** FIN DU TEST DE REGRESSION DE FRACTION ******" <<
        endl << endl;

}
