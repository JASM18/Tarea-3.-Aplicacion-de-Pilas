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

    float EvaluarExpresion();

    // MÉTODOS DEVELOPER

    void ImprimirPolacaInversa();

    bool ObtenerValidez();


    class SyntaxError : public std::exception {
    public:
        /** \brief Constructor por defecto de la excepci&oacute;n SyntaxError.
         */
        SyntaxError() throw();

        /** \brief Devuelve una descripci&oacute;n del error cuando la expresi&oacute;n no est&eacute; bien escrita.
         *
         * \return Cadena de caracteres con el mensaje de error.
         */
        virtual const char *what() const throw();
    };

    class MathError : public std::exception {
    public:
        /** \brief Constructor por defecto de la excepci&oacute;n MathError.
         */
        MathError() throw();

        /** \brief Devuelve una descripci&oacute;n del error cuando el resultado no est&eacute; definido.
         *
         * \return Cadena de caracteres con el mensaje de error.
         */

        virtual const char *what() const throw();
    };

private:

    string notInfija; // Notacion infija es del tipo A + B
    bool valido; // Para indicar si la exprecion es valida o no
    string notPolacaInversa; // Notación polaca inversa

    bool ValidarExpresion();
    int ObtenerPrioridad(char operador);
    void ConversionInfAPol();
};

#endif // EXPRESION_HPP_INCLUDED
