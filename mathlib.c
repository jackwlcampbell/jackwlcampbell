#include <assert.h>
#include <math.h>
#include <stdio.h>

//FUNCTION FILE
#define Abs(x)  ((x) < 0 ? -(x) : (x)) //Provided by Dr. Long found on the lecture slides.
#define EPSILON 1e-10

double Exp(double x) { //Provided by Dr. Long found on the class Piazza.
    double term = 1, sum = 1;
    for (int k = 1; Abs(term) > EPSILON; k += 1) {
        term *= x / k;
        sum += term;
    }
    return sum;
}

double Sqrt(double x) { //Provided by Dr. Long found on the class Piazza.
    double y = 1.0;
    assert(x >= 0);
    for (double guess = 0.0; Abs(y - guess) > EPSILON; y = (y + x / y) / 2.0) {
        guess = y;
    }
    return y;
}

//main functions
double arcSin(double x) {
    double next_val = 0.5;
    double val = 0.0;
    while ((Abs(next_val - val))
           > EPSILON) { //runs until the difference between guesses is less than 10e-10
        val = next_val;
        next_val = val - (sin(val) - x) / (cos(val)); //Newtons Method
    }
    return next_val;
}

double arcCos(double x) {
    return (M_PI_2 - arcSin(x));
}

double arcTan(double x) {
    return arcSin(x / (sqrt(1 + (x * x))));
}

double Log(double x) { //runs until the difference between guesses is less than 10e-10
    double next_val = 1.0;
    double val = 0.0;
    while ((Abs(next_val - val))
           > EPSILON) { //runs until the difference between guesses is less than 10e-10
        val = next_val;
        next_val = val - (exp(val) - x) / (exp(val)); //Newtons Method
    }
    return next_val;
}
