#include "Expresion.hpp"

using std::cout;

//********************************
// CONSTRUCTORES
//********************************

Expresion::Expresion()
{
    notInfija = "";
    notPolacaInversa = "";
    valido = false;
}

Expresion::Expresion(string textInfijo)
{
    notInfija = textInfijo; // Se guarda lo que el usuario escribió
    notPolacaInversa = "";

    /*
    Si la expresión es válida {
        la convierta a notación polaca inversa (la deje lista para evaluar)
    }

    */

}

//********************************
// Métodos publicos
//********************************

void Expresion::CapturarExpresion()
{
    /*
    Después de capturar la expresión{
        -> Debe validarla
        -> Convertirla para evaluar.
    }
    */
}

//********************************

void Expresion::ImprimirExpresion()
{
    cout << "Expresión Infija: " << notInfija;
}

//********************************

void Expresion::EvaluarExpresion()
{

}

//********************************
// MÉTODOS DEV
//********************************

void Expresion::ImprimirPolacaInversa()
{
    cout << "Expresión polasca: " << notPolacaInversa;
}

//********************************

bool Expresion::ObtenerValidez()
{
    return valido;
}
