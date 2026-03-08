#include <cctype>

#include "Expresion.hpp"
#include "Pila.hpp"

using std::cout;
using std::endl;

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
    valido = false;

    this->ValidarExpresion();

    if(this->valido == true){
        ConversionInfAPol(); // La deja lista para evaluar
    }else{
        cout << "Error: La expresión " << this->notInfija << " no es valida." << endl;
    }

    /*
    Si la expresión es válida {
        la convierta a notación polaca inversa (la deje lista para evaluar)
    }
    */

    if(ValidarExpresion()){
        cout << "LA EXPRESION ES VALIDA" << endl;
    }else{
        cout << "LA EXPRESION NO ES VALIDA" << endl;
    }

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

    // CÓDIGO PARA CAPTURAR...


    // DESPUÉS DE CAPTURAR...
    this->ValidarExpresion();

    if(this->valido == true){
        ConversionInfAPol(); // La deja lista para evaluar
    }else{
        cout << "Error: La expresión " << this->notInfija << " no es valida." << endl;
    }
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
    cout << "Expresión polaca: " << notPolacaInversa;
}

//********************************

bool Expresion::ObtenerValidez()
{
    return valido;
}

//********************************
// Métodos privados
//********************************

bool Expresion::ValidarExpresion()
{
    // Si encuentro algo que no es ni "(" ni ")" y tampoco es un operador...
    // Entonces, se tiene que verificar que "eso" sea correspondiente a un número
    // Un número puede tener "números", "." e incluso un "e" o "E".
    // Si queremos que acepte la notacion cientifica, despues de la "e" debe de haber un "numero" o un "+" o "-" (POR AHORA NO QUIERO ACEPTARLO)
    // La exprecion cientifica son puntos extra
    // Los numeros reales se van a dividir en dos partes, "parte entera"$"."$"parte decimal"
    // Si el numero es un numero entero, lo convertimos a numero real, el "." y la "parte decimal" será nulo

    // Después de un operador debe de existir un operando, antes del operador debe de existir un operando (expreciones no validas: "a*/b")
    // Despues de los simbolos de agrupacion, en algunos casos es valido y en otros no...
    // No aceptado: "'operador')"
    // Aceptado "'operador'(", ")'operador'"

    // No sería practico validar la agrupacion, y otro recorrido diferente para validar otros detalles
    // Al mismo tiempo hay que hacer el proceso, dependiendo de si encontramos un operador, operando o simbolo de agrupación.


    enum Estado {
        INICIO_O_APERTURA,
        ESPERANDO_OPERANDO,
        LEYENDO_ENTERO,
        LEYENDO_DECIMAL,
        ESPERANDO_OPERADOR_O_CIERRE
    };


    Pila<char> agrupacion;

    Estado actual = INICIO_O_APERTURA;


    //"(1+2)*2"

    for (int i = 0; i < this->notInfija.size() ; i++) {

        char caracter = notInfija[i];

        if(caracter == ' ') continue;

        if(isdigit(caracter)){ // Si se lee un digito (0-9)...

            // No puede haber un número despues de cerrar un parentesis
            if(actual == ESPERANDO_OPERADOR_O_CIERRE){
                return (this->valido = false);
            }

            // Si estábamos esperando operando, ahora estamos leyendo el valor
            if(actual == INICIO_O_APERTURA ||actual == ESPERANDO_OPERANDO){
                actual = LEYENDO_ENTERO;
            }

        }else if(caracter == '.'){ // Si lee un '.'
            // El punto es valido si ya de por si estabamos leyendo la parte entera

            if(actual == LEYENDO_ENTERO || actual == ESPERANDO_OPERANDO || actual == INICIO_O_APERTURA){
                actual = LEYENDO_DECIMAL;
            }else{
                return (this->valido = false);
            }


        }else if(caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/' || caracter == '^'){ // Si se lee un operador

            if(actual == INICIO_O_APERTURA){
                if(caracter == '+' || caracter == '-'){
                    actual = ESPERANDO_OPERANDO; // Obliga a que sea otro caracter
                }else{
                    return (this->valido = false); // Evita "(*3)"
                }

            }else if(actual == ESPERANDO_OPERANDO){
                return (this->valido = false); // Evia "++"
            }else{
                actual = ESPERANDO_OPERANDO;
            }


        }else if(caracter == '(' || caracter == '[' || caracter == '{'){ // Si se lee una apertura de agrupación

            // No se puede abrir paréntesis después de un número o un cierre. ejemplo: "3(" o ")("
            if (actual == LEYENDO_ENTERO || actual == LEYENDO_DECIMAL || actual == ESPERANDO_OPERADOR_O_CIERRE) {
                return (this->valido = false);
            }

            agrupacion.Agregar(caracter);

            actual = INICIO_O_APERTURA;

        }else if(caracter == ')' || caracter == ']' || caracter == '}'){ // Si se lee un cierre de agrupación

            // No se puede hacer ()
            if(actual == ESPERANDO_OPERANDO || actual == INICIO_O_APERTURA) return (this->valido = false);

            if(agrupacion.EstaVacia()) return (this->valido = false);

            char tope = agrupacion.ObtenerTope();

            if ((caracter == ')' && tope == '(') || (caracter == ']' && tope == '[') || (caracter == '}' && tope == '{')) {
                agrupacion.Eliminar(); // Hacen pareja, lo sacamos
            }else{
                return (this->valido = false); // Pareja incorrecta "(]"
            }

            // Después de cerrar, obligatoriamente esperamos un operador
            actual = ESPERANDO_OPERADOR_O_CIERRE;

        }else{
            return (this->valido = false);
        }

    }

    // Si terminó la cadena y seguía esperando un número (Ej: "3+")
    if (actual == ESPERANDO_OPERANDO) return (this->valido = false);

    // Si la pila no está vacía, faltó cerrar algún símbolo (Ej: "(3+2")
    if (!agrupacion.EstaVacia()) return (this->valido = false);

    return (this->valido = true);
}

//********************************

void Expresion::ConversionInfAPol()
{
    this->notPolacaInversa = "";
    Pila<char> Lectura;

    for (int i = 0; i < this->notInfija.size() ; i++) {

        char caracter = this->notInfija[i];

        if(isdigit(caracter)){

            this->notPolacaInversa += caracter;

        }else if(caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/' || caracter == '^'){ // Si se lee un operador






        }else if(caracter == '(' || caracter == '[' || caracter == '{'){ // Si se lee una apertura de agrupación
            Lectura.Agregar(caracter);
        }
    }

    // Al final, este método debe de modificar el atributo string notPolacaInversa
}
