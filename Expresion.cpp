#include <cctype>
#include <cmath>

#include "Expresion.hpp"
#include "Pila.hpp"

using std::cout;
using std::endl;

enum Estado {
    INICIO_O_APERTURA,
    ESPERANDO_OPERANDO,
    LEYENDO_ENTERO,
    LEYENDO_DECIMAL,
    ESPERANDO_OPERADOR_O_CIERRE
};

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
        throw SyntaxError();
    }

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

    std::getline(std::cin, this->notInfija);

    // DESPUÉS DE CAPTURAR...
    this->ValidarExpresion();

    if(this->valido == true){
        ConversionInfAPol(); // La deja lista para evaluar
    }else{
        throw SyntaxError();
    }
}

//********************************

void Expresion::ImprimirExpresion()
{
    cout << "Expresi\242n Infija: " << notInfija;
}

//********************************

float Expresion::EvaluarExpresion()
{
    if (this->valido == false){
       throw SyntaxError();
    }

    Pila<float> evaluacion;

    string numero = "";
    float num1, num2, resultado;

    for(int i = 0 ; i < this->notPolacaInversa.size() ; ++i){

        char caracter = this->notPolacaInversa[i];

        if(caracter == '$'){

            // El numero se convierte a flotante
            // El flotante se mete a la pila

            evaluacion.Agregar(std::stof(numero));
            numero = "";

        }else if(caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/' || caracter == '^'){ // Si se lee un operador

            //num1 = std::stof(numero[numero.size()-1]);
            //num2 = stof(numero[numero.size()-1]);

            num2 = evaluacion.ObtenerTope();
            evaluacion.Eliminar();
            num1 = evaluacion.ObtenerTope();
            evaluacion.Eliminar();

            switch (caracter){
                case '+':
                    resultado = num1 + num2;

                break;

                case '*':
                    resultado = num1 * num2;

                break;

                case '-':
                    resultado = num1 - num2;

                break;

                case '/':
                    if (num2 == 0){
                        throw MathError();
                    }
                    resultado = num1 / num2;


                break;

                case '^':
                    if (num1 == 0 && num2 <= 0){
                        throw MathError();
                    }
                    resultado = pow(num1, num2);

                break;

            }

            evaluacion.Agregar(resultado);

        }else{ // De a fuerzas es un número

            numero = numero + caracter;

        }
    }

    return resultado;
}

//********************************
// MÉTODOS DEV
//********************************

void Expresion::ImprimirPolacaInversa()
{
    cout << "Expresi\242n polaca: " << notPolacaInversa;
}

//********************************

bool Expresion::ObtenerValidez()
{
    return valido;
}

//***********************************
// Implementación de la clase SyntaxError
//***********************************

Expresion::SyntaxError::SyntaxError() throw() {}

//***********************************

const char *Expresion::SyntaxError::what() const throw()
{
    return "Error de sintaxis.";
}
//***********************************
// Implementación de la clase MathError
//***********************************

Expresion::MathError::MathError() throw() {}

//***********************************

const char *Expresion::MathError::what() const throw()
{
    return "Error de c\240lculo.";
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

    Pila<char> agrupacion;

    Estado actual = INICIO_O_APERTURA;

    for(int i = 0; i < this->notInfija.size() ; i++){

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
            if(actual == LEYENDO_ENTERO || actual == LEYENDO_DECIMAL || actual == ESPERANDO_OPERADOR_O_CIERRE){
                return (this->valido = false);
            }

            agrupacion.Agregar(caracter);

            actual = INICIO_O_APERTURA;

        }else if(caracter == ')' || caracter == ']' || caracter == '}'){ // Si se lee un cierre de agrupación

            // No se puede hacer ()
            if(actual == ESPERANDO_OPERANDO || actual == INICIO_O_APERTURA) return (this->valido = false);

            if(agrupacion.EstaVacia()) return (this->valido = false);

            char tope = agrupacion.ObtenerTope();

            if((caracter == ')' && tope == '(') || (caracter == ']' && tope == '[') || (caracter == '}' && tope == '{')){
                agrupacion.Eliminar(); // Hacen pareja, lo sacamos...
            }else{
                return (this->valido = false); // Pareja invalida: "(]"
            }

            // Después de cerrar, obligatoriamente esperamos un operador
            actual = ESPERANDO_OPERADOR_O_CIERRE;

        }else{
            return (this->valido = false);
        }
    }

    // Si terminó la cadena y se sigue esperando un número. Ej: "3+"
    if (actual == ESPERANDO_OPERANDO) return (this->valido = false);

    // Si la pila no está vacía, faltó cerrar algún símbolo. Ej: "(3+2"
    if (!agrupacion.EstaVacia()) return (this->valido = false);

    return (this->valido = true);
}

//********************************

int Expresion::ObtenerPrioridad(char operador)
{
    if(operador == '^') return 3;
    if(operador == '*' || operador == '/') return 2;
    if(operador == '+' || operador == '-') return 1;
    return 0; // Cualquier otra cosa (incluye las agrupaciones)
}

//********************************

void Expresion::ConversionInfAPol()
{
    this->notPolacaInversa = "";
    Pila<char> Lectura;

    for(int i = 0; i < this->notInfija.size() ; i++){

        char caracter = this->notInfija[i];

        if(caracter == ' ') continue;

        if(isdigit(caracter) || caracter == '.'){ // Si es un operando

            this->notPolacaInversa += caracter;

            // ¿Cómo sabemos si ya terminamos de leer el número para poner el $?
            // Si es el último caracter del arreglo, o si el SIGUIENTE caracter NO es un número/punto.
            if(i == this->notInfija.size() - 1 || (!isdigit(this->notInfija[i+1]) && this->notInfija[i+1] != '.')){
                this->notPolacaInversa += "$";
            }

        }else if(caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/' || caracter == '^'){ // Si se lee un operador

            // A) Verificar si es un operador unario para inyectar un "0$"
            bool esUnario = false;
            if(i == 0){
                esUnario = true;
            }else{
                int j = i - 1;
                while(j >= 0 && this->notInfija[j] == ' ') j--; // Retrocede saltando espacios
                if(j >= 0 && (this->notInfija[j] == '(' || this->notInfija[j] == '[' || this->notInfija[j] == '{')){
                    esUnario = true;
                }
            }

            if(esUnario && (caracter == '+' || caracter == '-')){
                this->notPolacaInversa += "0$";
            }
            // B) Comparar prioridades con la pila
            // No comparamos si el tope es un paréntesis
            while(!Lectura.EstaVacia() && Lectura.ObtenerTope() != '(' && Lectura.ObtenerTope() != '[' && Lectura.ObtenerTope() != '{'){

                char tope = Lectura.ObtenerTope();
                int prioTope = ObtenerPrioridad(tope);
                int prioCar = ObtenerPrioridad(caracter);

                // Si es asociatividad Izquierda-Derecha (+, -, *, /): Saca si es MAYOR O IGUAL
                if(caracter != '^' && prioTope >= prioCar){
                    this->notPolacaInversa += tope;
                    Lectura.Eliminar();
                }else if(caracter == '^' && prioTope > prioCar){ // Si es asociatividad Derecha-Izquierda (^): Saca solo si es MAYOR estricto
                    this->notPolacaInversa += tope;
                    Lectura.Eliminar();
                }else{
                    break; // El nuevo operador gana
                }
            }

            Lectura.Agregar(caracter);

        }else if(caracter == '(' || caracter == '[' || caracter == '{'){
            Lectura.Agregar(caracter);
        }else if(caracter == ')' || caracter == ']' || caracter == '}'){ // Si es un cierre de agrupación
            // Sacamos todo a la expresión hasta toparnos con la apertura
            while(!Lectura.EstaVacia() && Lectura.ObtenerTope() != '(' && Lectura.ObtenerTope() != '[' && Lectura.ObtenerTope() != '{'){
                this->notPolacaInversa += Lectura.ObtenerTope();
                Lectura.Eliminar();
            }
            // Eliminamos la apertura de la pila
            if(!Lectura.EstaVacia()){
                Lectura.Eliminar();
            }
        }
    }

    // Vaciando la pila
    while(!Lectura.EstaVacia()){
        this->notPolacaInversa += Lectura.ObtenerTope();
        Lectura.Eliminar();
    }
}
