#include <iostream>
#include <cctype>

#include "Expresion.hpp"

using namespace std;

int main()
{
    try{
        cout << "==============================" << endl;
        cout << "CALCULADORA CON EXPRESI\340N() Y PILA<>" << endl;
        cout << "==============================" << endl;

        cout << "Probando el constructor con un ";

        Expresion a("(245.99^[4*6^{1/4}^({[(2+4)*6]^2/(8-6)}*(2-4))])+2*(8-6/2+4*2)");


        cout << "La expresi\242n es v\240lida? " << a.ObtenerValidez() << endl;
        a.ImprimirExpresion();

        cout << endl;
        cout << "ImprimirPolacaInversa: " << endl;
        a.ImprimirPolacaInversa();

        //no captura multiplicaciones sin paréntesis, ej. 5(2-3) no
        cout << "\nCapturando expresi\242n..." << endl;
        Expresion b;
        b.CapturarExpresion();
        cout << "Imprimiendo b\n = ";
        b.ImprimirExpresion();

        cout << endl;
        b.ImprimirPolacaInversa();

        cout << "b evaluada = " << b.EvaluarExpresion() << endl;



    }catch(Expresion::SyntaxError &errorSyntax){
        cerr << "Error: " << errorSyntax.what() << endl;
    }

    cout << endl;
    system("Pause");
    return 0;
}
