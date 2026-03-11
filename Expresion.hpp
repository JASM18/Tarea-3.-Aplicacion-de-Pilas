#ifndef EXPRESION_HPP_INCLUDED
#define EXPRESION_HPP_INCLUDED

#include <iostream>
#include <string>

using std::string;

class Expresion {

public:
    /**
     * \brief Sobrecarga del operador de inserci&oacute;n (salida).
     * \param salida Flujo de salida.
     * \param expresion Expresion a imprimir.
     * \return Referencia al flujo de salida.
     */
    friend std::ostream & operator <<(std::ostream & salida, const Expresion &expresion);

    /**
     * \brief Sobrecarga del operador de extracci&oacute;n (entrada).
     * \param entrada Flujo de entrada.
     * \param expresion Expresion donde se guardar&aacute;n los datos.
     * \return Referencia al flujo de entrada.
     */
    friend std::istream & operator>>(std::istream & entrada, Expresion &expresion);

    Expresion();

    Expresion(string textInfijo);


    void CapturarExpresion();

    void ImprimirExpresion() const;

    float EvaluarExpresion() const;

    void ImprimirPolacaInversa();

    bool ObtenerValidez() const;


    class ErrorSintaxis : public std::exception {
    public:
        /** \brief Constructor por defecto de la excepci&oacute;n ErrorSintaxis.
         */
        ErrorSintaxis() throw();

        /** \brief Devuelve una descripci&oacute;n del error cuando la expresi&oacute;n no est&eacute; bien escrita.
         *
         * \return Cadena de caracteres con el mensaje de error.
         */
        virtual const char *what() const throw();
    };

    class ErrorCalculo : public std::exception {
    public:
        /** \brief Constructor por defecto de la excepci&oacute;n ErrorCalculo.
         */
        ErrorCalculo() throw();

        /** \brief Devuelve una descripci&oacute;n del error cuando el resultado no est&eacute; definido.
         *
         * \return Cadena de caracteres con el mensaje de error.
         */

        virtual const char *what() const throw();
    };

    class ErrorNulo : public std::exception {
    public:
        /** \brief Constructor por defecto de la excepci&oacute;n ErrorNulo.
         */
        ErrorNulo() throw();

        /** \brief Devuelve una descripci&oacute;n del error cuando la expresi&oacute;n est&aacute; vac&iacute;a.
         *
         * \return Cadena de caracteres con el mensaje de error.
         */
        virtual const char *what() const throw();
    };

private:

    string notInfija; // Notacion infija es del tipo A + B
    bool valido; // Para indicar si la exprecion es valida o no
    string notPolacaInversa; // Notación polaca inversa

    string infijaTokenizada; // para guardar la versión procesada de las funciones de los puntos extra

    void TokenizarFunciones();
    bool ValidarExpresion();
    int ObtenerPrioridad(char operador);
    void ConversionInfAPol();
};

#endif // EXPRESION_HPP_INCLUDED
