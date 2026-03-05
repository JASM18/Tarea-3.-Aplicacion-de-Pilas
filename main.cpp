#include <iostream>

#include "Expresion.hpp"

using namespace std;

int main()
{

    Expresion a("3+2");

    cout << "Expresion a es " << a.ObtenerValidez() << endl;

    cout << endl;
    a.ImprimirExpresion();

    cout << endl;
    system("Pause");
    return 0;
}
