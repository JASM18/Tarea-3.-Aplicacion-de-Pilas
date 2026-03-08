#ifndef EXPRESION_HPP_INCLUDED
#define EXPRESION_HPP_INCLUDED

#include <iostream>
#include <string>

using std::string;

class Expresion {

public:

    Expresion();

    Expresion(string textInfijo);


    void CapturarExpresion();

    void ImprimirExpresion();

    void EvaluarExpresion();

    // MÉTODOS DEVELOPER

    void ImprimirPolacaInversa();

    bool ObtenerValidez();

private:

    string notInfija; // Notacion infija es del tipo A + B
    bool valido; // Para indicar si la exprecion es valida o no
    string notPolacaInversa; // Notación polaca inversa

    bool ValidarExpresion();
    int ObtenerPrioridad(char operador);
    void ConversionInfAPol();
};

#endif // EXPRESION_HPP_INCLUDED
