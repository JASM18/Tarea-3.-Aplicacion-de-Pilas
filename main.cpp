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
    CONSTRUCTOR = 1,    /// Opci&oacute;n para ir al menu de los constructores
    CAPTURAR,           /// Opci&oacute;n para ir al menu de captura
    IMP_INFIJO,         /// Opci&oacute;n para ir al menu que imprime la notacion infija
    IMP_POLACA,         /// Opci&oacute;n para ir al menu que imprime la notacion de la polaca inversa
    EVALUAR,            /// Opci&oacute;n para ir al menu que evalua la expresion
    SALIR               /// Opci&oacute;n para salir del programa
};

int main()
{
    int opcion = -1;
    Expresion calc;

    do{
        cout << "====================" << endl;
        cout << "Tarea 3. Aplicaci\242n de pila" << endl;
        cout << "====================" << endl << endl;

        if(calc.ObtenerValidez()){
            cout << "Expresion guardada: " << calc << endl << endl;
        }

        cout << "Opciones:" << endl;
        cout << "\t" << CONSTRUCTOR << ") Pone a prueba el constructor por default y el constructor de un par\240metro." << endl;
        cout << "\t" << CAPTURAR << ") Captura una nueva expresi\242n." << endl;
        cout << "\t" << IMP_INFIJO << ") Imprime la expresión infija." << endl;
        cout << "\t" << IMP_POLACA << ") Imprime la expresión polaca inversa." << endl;
        cout << "\t" << EVALUAR << ") Evaluar la expresión" << endl;
        cout << "\t" << SALIR << ") Salir del programa" << endl;

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
