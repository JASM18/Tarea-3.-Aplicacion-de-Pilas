/**
 * \file main.cpp
 * \brief Cliente que prueba la clase Expresi&oacute;n, incluyendo un men&uacute; interactivo.
 * \author S&aacute;nchez Montoy, Jes&uacute;s Axel
 * \author Portugal Arreola, Marian Bethsab&eacute;
 * \date 07/03/2026
 * \code{.cpp}
 * #include <iostream>
 * * using namespace std;
 * * int main(){
 * * try{
 * * Expresion A;
 * * cout << "Ingresa la expresi\242n: ";
 * cin >> A;
 * * cout << "Expresion: " << A << endl;
 * * cout << "Resultado: " << A.EvaluarExpresion() << endl;
 * * }catch(Expresion::ErrorNulo &errorNulo){
 * cerr << "Error: " << errorNulo.what() << endl;
 * }catch(Expresion::ErrorSintaxis &errorSyntax){
 * cerr << "Error: " << errorSyntax.what() << endl;
 * }catch(Expresion::ErrorCalculo &errorMath){
 * cerr << "Error: " << errorMath.what() << endl;
 * }catch(...){
 * cerr << "Ocurri\242 un error inesperado." << endl;
 * }
 * * return 0;
 * }
 * \endcode
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
        cout << "\t" << IMP_INFIJO << ") Imprime la expresi\242n infija." << endl;
        cout << "\t" << IMP_POLACA << ") Imprime la expresi\242n polaca inversa." << endl;
        cout << "\t" << EVALUAR << ") Evaluar la expresi\242n." << endl;
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
                    GInstrucciones();
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
