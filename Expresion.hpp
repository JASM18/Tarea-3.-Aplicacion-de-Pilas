/**
 * \file Expresion.hpp
 * \brief Este archivo contiene la definici&oacute;n de la clase Expresion para manejar, validar y evaluar expresiones matem&aacute;ticas infijas y postfijas.
 * \author S&aacute;nchez Montoy, Jes&uacute;s Axel
 * \author Portugal Arreola, Marian Bethsab&eacute;
 * \date 07/03/2026
 */

#ifndef EXPRESION_HPP_INCLUDED
#define EXPRESION_HPP_INCLUDED

#include <iostream>
#include <string>

using std::string;

/**
 * \brief Decripci&oacute;n de la enumeraci&oacute;n: Estados de la m&aacute;quina de estados para validar la sintaxis de la expresi&oacute;n.
 */
enum Estado {
    INICIO_O_APERTURA,           /// Estado inicial o tras abrir un s&iacute;mbolo de agrupaci&oacute;n
    ESPERANDO_OPERANDO,          /// Estado en el que se espera un n&uacute;mero o variable
    LEYENDO_ENTERO,              /// Estado en el que se est&aacute; leyendo la parte entera de un n&uacute;mero
    LEYENDO_DECIMAL,             /// Estado en el que se est&aacute; leyendo la parte decimal de un n&uacute;mero
    ESPERANDO_OPERADOR_O_CIERRE, /// Estado en el que se espera un operador o cerrar agrupaci&oacute;n
    ESPERANDO_APERTURA_FUNCION,  /// Estado en el que se espera un par&eacute;ntesis tras una funci&oacute;n
    LEYENDO_EXPONENTE,           /// Estado en el que se lee la letra del exponente cient&iacute;fico
    LEYENDO_SIGNO_EXPONENTE,     /// Estado en el que se lee el signo del exponente cient&iacute;fico
    LEYENDO_ENTERO_EXPONENTE     /// Estado en el que se est&aacute; leyendo el valor num&eacute;rico del exponente
};

/**
 * \brief Clase Expresion dise&ntilde;ada para procesar operaciones aritm&eacute;ticas y funciones matem&aacute;ticas.
 */
class Expresion {

public:
    /**
     * \brief Sobrecarga del operador de inserci&oacute;n (salida).
     * \param salida Flujo de salida.
     * \param expresion Expresi&oacute;n a imprimir.
     * \return Referencia al flujo de salida.
     */
    friend std::ostream & operator <<(std::ostream & salida, const Expresion &expresion);

    /**
     * \brief Sobrecarga del operador de extracci&oacute;n (entrada).
     * \param entrada Flujo de entrada.
     * \param expresion Expresi&oacute;n donde se guardar&aacute;n los datos.
     * \return Referencia al flujo de entrada.
     */
    friend std::istream & operator>>(std::istream & entrada, Expresion &expresion);

    /**
     * \brief Constructor por default que define una expresi&oacute;n vac&iacute;a, no v&aacute;lida para evaluar.
     */
    Expresion();

    /** \brief Constructor que inicializa la expresi&oacute;n con la cadena recibida, la valida y la convierte a notaci&oacute;n polaca inversa.
     *
     * \param textInfijo Cadena de caracteres que representa la expresi&oacute;n aritm&eacute;tica a evaluar.
     * \throw ErrorSintaxis Lanza una excepci&oacute;n si la cadena de texto no es una expresi&oacute;n matem&aacute;tica v&aacute;lida.
     */
    Expresion(string textInfijo);

    /** \brief M&eacute;todo que permite capturar la expresi&oacute;n desde consola, validarla y convertirla para evaluar.
     *
     * \return void
     * \throw ErrorNulo Lanza una excepci&oacute;n si el usuario no ingres&oacute; ning&uacute;n caracter v&aacute;lido.
     * \throw ErrorSintaxis Lanza una excepci&oacute;n si la expresi&oacute;n introducida contiene errores de escritura o balanceo.
     */
    void CapturarExpresion();

    /** \brief M&eacute;todo que permite imprimir la expresi&oacute;n en su notaci&oacute;n infija.
     *
     * \return void
     */
    void ImprimirExpresion() const;

    /** \brief M&eacute;todo que eval&uacute;a la expresi&oacute;n postfija y calcula su resultado matem&aacute;tico.
     *
     * \return El resultado en double de la evaluaci&oacute;n aritm&eacute;tica.
     *
     * \pre
     * La expresi&oacute;n debe haber sido capturada y validada correctamente previamente (estado v&aacute;lido = true).
     * \throw ErrorNulo Lanza una excepci&oacute;n si la expresi&oacute;n est&aacute; vac&iacute;a al intentar evaluarla.
     * \throw ErrorSintaxis Lanza una excepci&oacute;n si la expresi&oacute;n no pas&oacute; la validaci&oacute;n.
     * \throw ErrorCalculo Lanza una excepci&oacute;n si ocurre una indeterminaci&oacute;n (ej. divisi&oacute;n por cero o logaritmo negativo).
     */
    double EvaluarExpresion() const;

    /** \brief M&eacute;todo que permite imprimir la expresi&oacute;n en su notaci&oacute;n polaca inversa.
     *
     * \return void
     */
    void ImprimirPolacaInversa();

    /** \brief Devuelve el estado actual de validez de la expresi&oacute;n.
     *
     * \return true si la expresi&oacute;n es v&aacute;lida, false en caso contrario.
     */
    bool ObtenerValidez() const;

    /**
     * \brief Descripci&oacute;n de la clase/struct: Excepci&oacute;n lanzada cuando la expresi&oacute;n contiene errores de sintaxis.
     */
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

    /**
     * \brief Descripci&oacute;n de la clase/struct: Excepci&oacute;n lanzada cuando ocurre un error matem&aacute;tico al evaluar la expresi&oacute;n.
     */
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

    /**
     * \brief Descripci&oacute;n de la clase/struct: Excepci&oacute;n lanzada cuando se intenta evaluar o procesar una expresi&oacute;n vac&iacute;a.
     */
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

    string notInfija;           ///< Una cadena de caracteres para la expresi&oacute;n en notaci&oacute;n infija.
    bool valido;                ///< Un indicador del estado de la expresi&oacute;n: true si es v&aacute;lida, false en caso contrario
    string notPolacaInversa;    ///< Una cadena de caracteres para la expresi&oacute;n en notaci&oacute;n polaca inversa
    string infijaTokenizada;    ///< Cadena auxiliar para guardar la versi&oacute;n procesada de las funciones de los puntos extra

    /** \brief Convierte las palabras clave de las funciones trigonom&eacute;tricas y logar&iacute;tmicas a tokens de un solo caracter.
     * \return void
     */
    void TokenizarFunciones();

    /** \brief Valida el balanceo de s&iacute;mbolos y la estructura correcta de los operandos y operadores.
     * \return true si la estructura es l&oacute;gicamente evaluable, false en caso contrario.
     */
    bool ValidarExpresion();

    /** \brief Obtiene la prioridad de precedencia de un operador espec&iacute;fico.
     * \param operador Caracter que representa la operaci&oacute;n aritm&eacute;tica o funci&oacute;n.
     * \return Nivel de prioridad en formato num&eacute;rico entero.
     */
    int ObtenerPrioridad(char operador);

    /** \brief Transforma la expresi&oacute;n infija validada a notaci&oacute;n postfija mediante el uso de pilas.
     * \return void
     */
    void ConversionInfAPol();
};

#endif // EXPRESION_HPP_INCLUDED
