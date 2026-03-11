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
    ESPERANDO_OPERADOR_O_CIERRE,
    ESPERANDO_APERTURA_FUNCION
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

    TokenizarFunciones();

    this->ValidarExpresion();

    if(this->valido == true){
        ConversionInfAPol(); // La deja lista para evaluar
    }else{
        throw ErrorSintaxis();
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

    std::getline(std::cin, this->notInfija);

    if(this->notInfija.empty() || this->notInfija.find_first_not_of(" \r\n\t") == std::string::npos){
        this->valido = false;
        throw ErrorNulo();
    }

    TokenizarFunciones();

    // DESPUÉS DE CAPTURAR...
    this->ValidarExpresion();

    if(this->valido == true){
        ConversionInfAPol(); // La deja lista para evaluar
    }else{
        throw ErrorSintaxis();
    }
}

//********************************

void Expresion::ImprimirExpresion() const
{
    if(notInfija.empty()){
        cout << "La expresi\242n esta vacia.";
    }else{
        cout << notInfija;
    }
}

//********************************

float Expresion::EvaluarExpresion() const
{
    if (notInfija.empty()){
       throw ErrorNulo();
    }

    if (this->valido == false){
       throw ErrorSintaxis();
    }

    Pila<float> evaluacion;

    string numero = "";
    float num1 = 0.0, num2 = 0.0, resultado = 0.0;

    for(int i = 0 ; i < this->notPolacaInversa.size() ; ++i){

        char caracter = this->notPolacaInversa[i];

        if(caracter == '$'){

            // El numero se convierte a flotante
            // El flotante se mete a la pila

            // Si el usuario metió un punto solitario (".", "-.", "+."), se convierte en
            if(numero == "."){
                numero = "0";
            }

            // El numero se convierte a flotante y se mete a la pila
            evaluacion.Agregar(std::stof(numero));
            numero = "";





        }else if(caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/' || caracter == '^' ||
                 caracter == 'S' || caracter == 'C' || caracter == 'T' || caracter == 'R' || caracter == 'L' || caracter == 'N' || caracter == 'E'){

            // ¿Es una operación de dos números o de un solo número?
            bool esBinario = (caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/' || caracter == '^');

            if (esBinario) {
                num2 = evaluacion.ObtenerTope(); evaluacion.Eliminar();
                num1 = evaluacion.ObtenerTope(); evaluacion.Eliminar();
            } else {
                // Si es función, solo sacamos UN número (x)
                num1 = evaluacion.ObtenerTope(); evaluacion.Eliminar();
                num2 = 0; // No lo usamos
            }

            switch (caracter){
                case '+': resultado = num1 + num2; break;
                case '-': resultado = num1 - num2; break;
                case '*': resultado = num1 * num2; break;
                case '/':
                    if (num2 == 0) throw ErrorCalculo();
                    resultado = num1 / num2;
                    break;
                case '^':
                    if (num1 == 0 && num2 <= 0) throw ErrorCalculo();
                    resultado = pow(num1, num2);
                    break;
                case 'S': resultado = sin(num1); break; // Usa radianes por defecto en C++
                case 'C': resultado = cos(num1); break;
                case 'T': resultado = tan(num1); break;
                case 'E': resultado = exp(num1); break;
                case 'R':
                    if (num1 < 0) throw ErrorCalculo(); // Raíz imaginaria
                    resultado = sqrt(num1);
                    break;
                case 'L':
                    if (num1 <= 0) throw ErrorCalculo(); // Fuera de dominio
                    resultado = log10(num1);
                    break;
                case 'N':
                    if (num1 <= 0) throw ErrorCalculo();
                    resultado = log(num1); // En C++, log() es ln
                    break;
            }

            // ¡AQUÍ ESTÁ LA MAGIA QUE FALTABA! Guardamos el resultado de vuelta a la pila.
            evaluacion.Agregar(resultado);

        }else{ // De a fuerzas es un número
            numero = numero + caracter;
        }
    }

    if(std::isinf(resultado) || std::isnan(resultado)){
        throw ErrorCalculo();
    }

    return resultado;
}

//********************************
// MÉTODOS DEV
//********************************

void Expresion::ImprimirPolacaInversa()
{


    if(notPolacaInversa.empty()){

        if(this->valido == false){
            ValidarExpresion();
        }

        if(this->valido == true){

            ConversionInfAPol(); // El método ImprimirPolacaInversa() sería constante si no fuera por esta linea...
            cout << notPolacaInversa;

        }else{
            cout << "La expresi\242n polaca no esta definida.";
        }

    }else{
        cout << notPolacaInversa;
    }
}

//********************************

bool Expresion::ObtenerValidez() const
{
    return valido;
}

//***********************************
// Implementación de la clase ErrorSintaxis
//***********************************

Expresion::ErrorSintaxis::ErrorSintaxis() throw() {}

//***********************************

const char *Expresion::ErrorSintaxis::what() const throw()
{
    return "Error de sintaxis.";
}
//***********************************
// Implementación de la clase ErrorCalculo
//***********************************

Expresion::ErrorCalculo::ErrorCalculo() throw() {}

//***********************************

const char *Expresion::ErrorCalculo::what() const throw()
{
    return "Error de c\240lculo.";
}

//***********************************
// Implementación de la clase ErrorNulo
//***********************************

Expresion::ErrorNulo::ErrorNulo() throw() {}

//***********************************

const char *Expresion::ErrorNulo::what() const throw()
{
    return "Error de expresion nula.";
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

    if(infijaTokenizada.empty()){
        return (this->valido = false);
    }

    Pila<char> agrupacion;

    Estado actual = INICIO_O_APERTURA;

    for(int i = 0; i < this->infijaTokenizada.size() ; i++){

        char caracter = infijaTokenizada[i];

        if(caracter == ' ') continue;
        // Ignora espacios, retornos de carro (\r) y saltos de línea (\n)
        if(caracter == ' ' || caracter == '\r' || caracter == '\n') continue;

        if(isalpha(caracter)){

            if(caracter == 'S' || caracter == 'C' || caracter == 'T' ||
               caracter == 'R' || caracter == 'L' || caracter == 'N' || caracter == 'E'){

                // Una función solo es válida donde podría ir un número
                if(actual == INICIO_O_APERTURA || actual == ESPERANDO_OPERANDO){
                    actual = ESPERANDO_APERTURA_FUNCION; // Obliga a que el siguiente sea '('
                }else{
                    return (this->valido = false);
                }
            }else{
                return (this->valido = false); // Rechaza variables o palabras mal escritas ("san", "x", etc.)
            }

        }else if(isdigit(caracter)){ // Si se lee un digito (0-9)...

            // No puede haber un número despues de cerrar un parentesis
            if(actual == ESPERANDO_OPERADOR_O_CIERRE || actual == ESPERANDO_APERTURA_FUNCION){
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

            if(actual == ESPERANDO_APERTURA_FUNCION){
                return (this->valido = false);
            }

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
            if(actual == ESPERANDO_OPERANDO || actual == INICIO_O_APERTURA || actual == ESPERANDO_APERTURA_FUNCION){
                return (this->valido = false);
            }

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

    // Si terminó la cadena y seguía esperando un número (Ej: "3+")
    // O si nunca se escribió nada válido (Ej: "   ")
    if (actual == ESPERANDO_OPERANDO || actual == INICIO_O_APERTURA) return (this->valido = false);

    // Si la pila no está vacía, faltó cerrar algún símbolo (Ej: "(3+2")
    if (!agrupacion.EstaVacia()) return (this->valido = false);

    return (this->valido = true);
}

//********************************

int Expresion::ObtenerPrioridad(char operador)
{
    if(operador == 'S' || operador == 'C' || operador == 'T' || operador == 'R' || operador == 'L' || operador == 'N' || operador == 'E') return 4;
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

    for(int i = 0; i < this->infijaTokenizada.size() ; i++){

        char caracter = this->infijaTokenizada[i];

        if(caracter == ' ') continue;
        // Mantenemos la cadena Polaca limpia de basura
        if(caracter == ' ' || caracter == '\r' || caracter == '\n') continue;

        if(isdigit(caracter) || caracter == '.'){ // Si es un operando

            this->notPolacaInversa += caracter;

            // ¿Cómo sabemos si ya terminamos de leer el número para poner el $?
            // Si es el último caracter del arreglo, o si el SIGUIENTE caracter NO es un número/punto.
            if(i == this->infijaTokenizada.size() - 1 || (!isdigit(this->infijaTokenizada[i+1]) && this->infijaTokenizada[i+1] != '.')){
                this->notPolacaInversa += "$";
            }
        }else if(caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/' || caracter == '^' || caracter == 'S' || caracter == 'C' || caracter == 'T' || caracter == 'R' || caracter == 'L' || caracter == 'N' || caracter == 'E'){

            // A) Verificar si es un operador unario para inyectar un "0$"
            // (La lógica del unario se mantiene igual, no afecta a las funciones)
            bool esUnario = false;
            if(i == 0){
                esUnario = true;
            }else{
                int j = i - 1;
                while(j >= 0 && this->infijaTokenizada[j] == ' ') j--; // Retrocede saltando espacios
                if(j >= 0 && (this->infijaTokenizada[j] == '(' || this->infijaTokenizada[j] == '[' || this->infijaTokenizada[j] == '{')){
                    esUnario = true;
                }
            }

            // OJO: Solo los '+' y '-' pueden ser unarios en este contexto de rellenar con ceros
            if(esUnario && (caracter == '+' || caracter == '-')){
                this->notPolacaInversa += "0$";
            }

            // B) Comparar prioridades con la pila
            // No comparamos si el tope es un paréntesis
            while(!Lectura.EstaVacia() && Lectura.ObtenerTope() != '(' && Lectura.ObtenerTope() != '[' && Lectura.ObtenerTope() != '{'){

                char tope = Lectura.ObtenerTope();
                int prioTope = ObtenerPrioridad(tope);
                int prioCar = ObtenerPrioridad(caracter);

                // Si es asociatividad Izquierda-Derecha (+, -, *, /, Funciones): Saca si es MAYOR O IGUAL
                if(caracter != '^' && prioTope >= prioCar){
                    this->notPolacaInversa += tope;
                    Lectura.Eliminar();
                }else if(caracter == '^' && prioTope > prioCar){ // Si es asociatividad Derecha-Izquierda (^): Saca solo si es MAYOR estricto
                    this->notPolacaInversa += tope;
                    Lectura.Eliminar();
                }else{
                    break; // El nuevo operador/función gana
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

//**********************************

// Este método busca las palabras clave y las reemplaza por su Token mayúscula
void Expresion::TokenizarFunciones(){
    this->infijaTokenizada = this->notInfija;

    const string funciones[] = {"sin", "cos", "tan", "sqrt", "log", "ln", "exp"};
    const string tokens[] = {"S", "C", "T", "R", "L", "N", "E"};

    for(int i = 0; i < 7; ++i){
        size_t pos = 0;
        // Busca todas las apariciones de la función y las reemplaza
        while((pos = this->infijaTokenizada.find(funciones[i], pos)) != string::npos){
            this->infijaTokenizada.replace(pos, funciones[i].length(), tokens[i]);
            pos += tokens[i].length();
        }
    }
}


//**********************************
// Flujos sobrecargados de entrada y salida
//**********************************

std::ostream & operator<<(std::ostream & salida, const Expresion &expresion)
{
    expresion.ImprimirExpresion();
    return salida;
}

//**********************************

std::istream & operator>>(std::istream & entrada, Expresion &expresion)
{
    expresion.CapturarExpresion();
    return entrada;
}
