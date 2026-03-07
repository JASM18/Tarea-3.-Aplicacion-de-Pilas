#include <iostream>
#include <cctype>

#include "Expresion.hpp"

using namespace std;

int main()
{

    Expresion a("5.2*((4.0+3.2121)*(2.1+1.67))");

    cout << "La expresion es valida? " << a.ObtenerValidez() << endl;
    a.ImprimirExpresion();


    cout << endl;
    a.ConversionInfAPol();

    cout << "ImprimirPolacaInversa: " << endl;
    a.ImprimirPolacaInversa();


    cout << endl;
    system("Pause");
    return 0;
}
