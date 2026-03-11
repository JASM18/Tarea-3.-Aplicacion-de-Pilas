/**
 * \file Pila.hpp
 * \brief Este archivo contiene la definici&oacute;n de la plantilla de clase Pila de elementos enlazados.
 * \author S&aacute;nchez Montoy, Jes&uacute;s Axel
 * \author Portugal Arreola, Marian Bethsab&eacute;
 * \date 07/03/2026
 */

#ifndef PILA_HPP
#define PILA_HPP

#include <exception>

template <typename T = std::string>
class Pila {
public:
    /** Constructor por default */
    Pila();

    /** Destructor por default */
    ~Pila();

    /** Constructor de copias
     *  \param pila Objecto el cual copiar
     */
    Pila(const Pila& pila);

    /** Operador de asignaci&oacute;n
     *  \param pila Object al cual igualar
     *  \return Una referencia a this
     */
    Pila& operator=(const Pila& pila);

    /** \brief Agrega un elemento al tope de la pila
     *
     * \param valor T
     * \return void
     *
     */
    void Agregar(T valor);

    /** \brief Elimina el tope de la pila
     *
     * \return void
     *
     */
    void Eliminar();

    /** \brief Obtiene el valor del tope de la pila
     *
     * \return T
     *
     */
    T ObtenerTope() const;

    /** \brief Regresa la cantidad de elementos que hay en la pila
     *
     * \return int
     *
     */
    int ObtenerTam() const;

    /** \brief Nos dice si la pila esta vac&iacute;a o no
     *
     * \return bool
     *
     */
    bool EstaVacia() const;

    /** \brief Vac&icute;a toda la pila, pone el tope en -1
     *
     * \return void
     *
     */
    void Vaciar();

    /** \brief Imprime la pila
     *
     * \return void
     *
     */
    void Imprimir();

    class PilaVacia : public std::exception {
    public:
        /** \brief Constructor por defecto de la excepci&oacute;n PilaVacia.
         */
        PilaVacia() throw();

        /** \brief Devuelve una descripci&oacute;n del error al intentar operar con una pila vac&iacute;a.
         *
         * \return Cadena de caracteres con el mensaje de error.
         */
        virtual const char *what() const throw();
    };

    class PilaNoMemoria : public std::exception {
    public:
        /** \brief Constructor por defecto de la excepci&oacute;n PilaNoMemoria.
         */
        PilaNoMemoria() throw();

        /** \brief Devuelve una descripci&oacute;n del error cuando no haya memoria disponible.
         *
         * \return Cadena de caracteres con el mensaje de error.
         */
        virtual const char *what() const throw();
    };

private:

    int numElem; //!< Member variable "numElem"
    struct Elemento{
        T valor;
        Elemento *siguiente;
        Elemento(T val, Elemento *sig); // Constructor de Elemento
    };
    Elemento *tope; //!< Member variable "*tope";
};

#include "Pila.tpp"

#endif // PILA_HPP
