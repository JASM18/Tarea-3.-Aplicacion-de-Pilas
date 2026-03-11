#include <iostream>
#include <limits>

#include "Menu.hpp"

using std::cout;
using std::endl;
using std::cerr;
using std::cin;

void GConstructores()
{
    system("CLS");

    cout << "====================" << endl;
    cout << "Probando constructores" << endl;
    cout << "====================" << endl << endl;

    try{

        cout << "-> Construyendo Expresi\242n Default..." << endl;
        Expresion Default;

        cout << "\n-> Comprobando atributos..." << endl;
        cout << "\250La expresion es valida?: " << (Default.ObtenerValidez() ? "S\241." : "No.") << endl;
        cout << "Imprimiendo su expresi\242n en notaci\242n infija: " << Default << endl;
        cout << "Imprimiendo su expresi\242n en notaci\242n polaca inversa: ";
        Default.ImprimirPolacaInversa();

        //cout << "\nResultado de la evaluacion: " << Default.EvaluarExpresion() << endl;


        cout << "\n-> Construyendo Expresion Default2..." << endl;
        Expresion Default2("(2.1^[3.2*3.1^{1/4}^({[(2+4)*6]^2/(8-6)}*(2-4))])+2*(8-6/2+4*2)");

        cout << "\n-> Comprobando atributos..." << endl;
        cout << "\250La expresion es valida?: " << (Default2.ObtenerValidez() ? "S\241." : "No.") << endl;
        cout << "Imprimiendo su expresi\242n en notaci\242n infija: " << Default2 << endl;
        cout << "Imprimiendo su expresi\242n en notaci\242n polaca inversa: ";
        Default2.ImprimirPolacaInversa();

        cout << "\nResultado de la evaluacion: " << Default2.EvaluarExpresion() << endl;

        cout << "\n¡¿Que pasa si se evalua Default?!" << endl;
        cout << "Resultado de la evaluacion: " << Default.EvaluarExpresion() << endl;


    }catch(Expresion::ErrorNulo &errorNulo){
        cerr << "Error: " << errorNulo.what() << endl;
    }catch(Expresion::ErrorSintaxis &errorSyntax){
        cerr << "Error: " << errorSyntax.what() << endl;
    }catch(Expresion::ErrorCalculo &errorMath){
        cerr << "Error: " << errorMath.what() << endl;
    }catch(...){
        cerr << "Ocurri\242 un error inesperado." << endl;
    }
}

void GCapturar(Expresion &expr)
{
    system("CLS");

    cout << "====================" << endl;
    cout << "Capturando expresion" << endl;
    cout << "====================" << endl << endl;

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    try{

        cout << "Ingresa la expresi\242n: ";
        cin >> expr;

        cout << "\n[Exito] Expresi\242n valida y lista para evaluar." << endl;

    }catch(Expresion::ErrorNulo &errorNulo){
        cerr << "\nError: " << errorNulo.what() << endl;
    }catch (Expresion::ErrorSintaxis &errorSyntax){
        cerr << "\nError: " << errorSyntax.what() << endl;
    }catch (Expresion::ErrorCalculo &errorMath){
        cerr << "\nError: " << errorMath.what() << endl;
    }catch (...){
        cerr << "\nOcurri\242 un error inesperado." << endl;
    }
}

void GImpInfijo(Expresion &expr)
{
    cout << "\n- - - - - - - - - -" << endl;

    cout << "Expresión infija: " << expr;

    cout << "\n\n";
}


void GImpPolaca(Expresion &expr)
{
    cout << "\n- - - - - - - - - -" << endl;

    cout << "Expresi\242n en Notaci\242n Polaca Inversa: ";
    expr.ImprimirPolacaInversa();
    cout << "\n\n";
}

void GEvaluar(Expresion &expr)
{
    cout << "\n- - - - - - - - - -" << endl;

    try{
        cout << "Resultado de la evaluaci\242n: " << expr.EvaluarExpresion() << endl;
    }catch(Expresion::ErrorNulo &errorNulo){
        cerr << "Error: " << errorNulo.what() << endl;
    }catch(Expresion::ErrorSintaxis &errorSyntax){
        cerr << "Error: " << errorSyntax.what() << endl;
    }catch(Expresion::ErrorCalculo &errorMath){
        cerr << "Error: " << errorMath.what() << endl;
    }catch(...){
        cerr << "Ocurri\242 un error inesperado al evaluar." << endl;
    }

    cout << "\n";
}
