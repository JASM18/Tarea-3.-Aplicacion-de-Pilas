#include <iostream>
#include <cctype>

#include "Expresion.hpp"

using namespace std;

int main()
{

    Expresion a("3*.2");

    cout << "La expresion es valida? " << a.ObtenerValidez() << endl;
    a.ImprimirExpresion();

    cout << endl;
    cout << "ImprimirPolacaInversa: " << endl;
    a.ImprimirPolacaInversa();


    cout << endl;
    system("Pause");
    return 0;
}
