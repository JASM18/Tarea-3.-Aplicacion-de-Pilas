#include <iostream>
#include <cctype>

#include "Expresion.hpp"

using namespace std;

int main()
{

    Expresion a("(2^[4*6^{1/4}^({[(2+4)*6]^2/(8-6)}*(2-4))])+2*(8-6/2+4*2)");


    cout << "La expresi\242n es v\240lida? " << a.ObtenerValidez() << endl;
    a.ImprimirExpresion();

    cout << endl;
    cout << "ImprimirPolacaInversa: " << endl;
    a.ImprimirPolacaInversa();

    //no captura multiplicaciones sin paréntesis, ej. 5(2-3) no
    cout << "\nCapturando expresi\242n..." << endl;
    Expresion b;
    b.CapturarExpresion();
    cout << "Imprimiendo b" << endl;
    b.ImprimirExpresion();



    cout << endl;
    system("Pause");
    return 0;
}
