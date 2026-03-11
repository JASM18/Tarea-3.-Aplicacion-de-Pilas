/**
 * \file main.cpp
 * \brief Cliente que prueba la clase Expresi&oacute;n, incluyendo un men&uacute; interactivo.
 * \author S&aacute;nchez Montoy, Jes&uacute;s Axel
 * \author Portugal Arreola, Marian Bethsab&eacute;
 * \date 07/03/2026
 */

#include <iostream>
#include <cctype>

#include "Expresion.hpp"
#include "CapturaSegura.hpp"
#include "Menu.hpp"

using namespace std;

/**
 * \brief Opciones del men&uacute; principal.
 */
enum Opciones_principales {
    CONSTRUCTOR = 1,    /// Opci&oacute;n para ir al men&uacute; de los constructores.
    CAPTURAR,           /// Opci&oacute;n para ir al men&uacute; de captura.
    IMP_INFIJO,         /// Opci&oacute;n para ir al men&uacute; que imprime la notaci&oacute;n infija.
    IMP_POLACA,         /// Opci&oacute;n para ir al men&uacute; que imprime la notaci&oacute;n de la polaca inversa.
    EVALUAR,            /// Opci&oacute;n para ir al men&uacute; que eval&uacute;a la expresi&oacute;n.
    INSTRUCCIONES,      /// Opci&oacute;n para ver c&oacute;mo usar las funciones radicales, trigonom&eacute;tricas, logar&iacute;tmicas y exponenciales.
    SALIR               /// Opci&oacute;n para salir del programa.

};

int main()
{
    int opcion = -1;
    Expresion calc;

    do{
        cout << "==============================" << endl;
        cout << "Tarea 3. Aplicaci\242n de pila" << endl;
        cout << "==============================" << endl << endl;

        if(calc.ObtenerValidez()){
            cout << "Expresi\242n guardada: " << calc << endl << endl;
        }

        cout << "Opciones:" << endl;
        cout << "\t" << CONSTRUCTOR << ") Pone a prueba el constructor por default y el constructor de un par\240metro." << endl;
        cout << "\t" << CAPTURAR << ") Captura una nueva expresi\242n." << endl;
        cout << "\t" << IMP_INFIJO << ") Imprime la expresi/242n infija." << endl;
        cout << "\t" << IMP_POLACA << ") Imprime la expresi/242n polaca inversa." << endl;
        cout << "\t" << EVALUAR << ") Evaluar la expresi/242n." << endl;
        cout << "\t" << INSTRUCCIONES << ") Ver indicaciones de sintaxis." << endl;
        cout << "\t" << SALIR << ") Salir del programa." << endl;

        do{
            CapturarNumero(opcion, "Elige una opci\242n: ");
        }while(opcion > SALIR || opcion < CONSTRUCTOR);

        if(opcion == SALIR) continue;

        try{
            switch(opcion){

                case CONSTRUCTOR:
                    GConstructores();
                break;
                case CAPTURAR:
                    GCapturar(calc);
                break;
                case IMP_INFIJO:
                    GImpInfijo(calc);
                break;
                case IMP_POLACA:
                    GImpPolaca(calc);
                break;
                case EVALUAR:
                    GEvaluar(calc);
                break;
                case INSTRUCCIONES:
                    cout << "\n--- INSTRUCCIONES DE FUNCIONES ---" << endl;
                    cout << "x+y     -> Suma" << endl;
                    cout << "x-y     -> Resta" << endl;
                    cout << "x*y     -> Multiplicaci\242n" << endl;
                    cout << "(x)     -> Par\202ntesis" << endl;
                    cout << "x/y     -> Divisi\242n" << endl;
                    cout << "x^y     -> Exponenciaci\242n" << endl;
                    cout << "sin(x)  -> Seno" << endl;
                    cout << "cos(x)  -> Coseno" << endl;
                    cout << "tan(x)  -> Tangente" << endl;
                    cout << "sqrt(x) -> Ra\241z cuadrada" << endl;
                    cout << "log(x)  -> Logaritmo base 10" << endl;
                    cout << "ln(x)   -> Logaritmo natural" << endl;
                    cout << "exp(x)  -> Exponencial (e^x)" << endl;

                    cout << "\nNotas: " << endl;
                    cout << "\n- Ejemplo v\240lido: sin(3.1416/2) + sqrt(16)" << endl;
                    cout << "- La multiplicaci\242n por par\202ntesis y un escalar sin usar el s\240mbolo '*' no se admite." << endl;
                    cout << "- Los c\240lculos trigonom\202tricos est\240n en radianes." << endl;
                    cout << "- Se aceptan n\243meros con punto decimal, incluyendo expreiones como: " << endl;
                    cout << "   0.3\n   .3" << endl;
                    cout << "- Se acepta notaci\242n cient\241fica, por ejemplo:" << endl;
                    cout << "   3.0e4" << endl;

                break;
            }
        }catch(const char *mensaje){
            cerr << "\nERROR: " << mensaje << endl;
        }catch(...) {
            cerr << "\nERROR: Ocurri\242 un error inesperado." << endl;
        }

        system ("pause");
        system("CLS");
    }while(opcion != SALIR);

    cout << "\nEl programa ha terminado." << endl;

    system("pause");
    return 0;
}
