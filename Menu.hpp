/**
 * \file Menu.hpp
 * \brief Este archivo contiene las declaraciones de las funciones del men&uacute; interactivo para probar la clase Expresion.
 * \author S&aacute;nchez Montoy, Jes&uacute;s Axel
 * \author Portugal Arreola, Marian Bethsab&eacute;
 * \date 07/03/2026
**/

#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include "Expresion.hpp"

/** \brief Funci&oacute;n que pone a prueba los constructores de la clase Expresion
 *
 * \return void
 */
void GConstructores();

/** \brief Funci&oacute;n que coordina la captura de una expresi&oacute;n por teclado, manejando las posibles excepciones lanzadas.
 *
 * \param expr Referencia al objeto Expresion donde se guardar&aacute; y validar&aacute; la cadena capturada.
 * \return void
 */
void GCapturar(Expresion &expr);

/** \brief Funci&oacute;n que imprime la expresi&oacute;n en su formato infijo original.
 *
 * \param expr Referencia al objeto Expresion que contiene los datos.
 * \return void
 */
void GImpInfijo(Expresion &expr);

/** \brief Funci&oacute;n que imprime la expresi&oacute;n convertida a notaci&oacute;n polaca inversa.
 *
 * \param expr Referencia al objeto Expresion que contiene los datos ya convertidos.
 * \return void
 */
void GImpPolaca(Expresion &expr);

/** \brief Funci&oacute;n eval&uacute;a la expresi&oacute;n matem&aacute;tica manejando errores de c&aacute;lculo y muestra el resultado final.
 *
 * \param expr Referencia al objeto Expresion que ser&aacute; evaluado.
 * \return void
 */
void GEvaluar(Expresion &expr);

#endif // MENU_HPP_INCLUDED
