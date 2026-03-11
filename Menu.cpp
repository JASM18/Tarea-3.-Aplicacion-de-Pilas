/**
 * \file Menu.cpp
 * \brief Este archivo contiene la implementaci&oacute;n de las funciones de la interfaz y men&uacute; de usuario.
 * \author S&aacute;nchez Montoy, Jes&uacute;s Axel
 * \author Portugal Arreola, Marian Bethsab&eacute;
 * \date 07/03/2026
 */

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

    cout << "======================" << endl;
    cout << "Probando constructores" << endl;
    cout << "======================" << endl << endl;

    try{

        cout << "-> Construyendo Expresi\242n Default..." << endl;
        Expresion Default;

        cout << "\n-> Comprobando atributos..." << endl;
        cout << "\250La expresi\242n es v\240lida?: " << (Default.ObtenerValidez() ? "S\241." : "No.") << endl;
        cout << "Imprimiendo su expresi\242n en notaci\242n infija: " << Default << endl;
        cout << "Imprimiendo su expresi\242n en notaci\242n polaca inversa: ";
        Default.ImprimirPolacaInversa();

        //cout << "\nResultado de la evaluacion: " << Default.EvaluarExpresion() << endl;


        cout << "\n-> Construyendo Expresi\242n Default2..." << endl;
        Expresion Default2("{[(exp(0) + log(100) - ln(1)) * sqrt(16)] / (cos(0) + sin(0))} + (-2.5e1 * 4) + (1.5E^2 / 3 + .5e^1 * 2) + 2^[(3 + 1) / 2] - tan(0)");

        cout << "\n-> Comprobando atributos..." << endl;
        cout << "\250La expresi\242n es v\240lida?: " << (Default2.ObtenerValidez() ? "S\241." : "No.") << endl;
        cout << "Imprimiendo su expresi\242n en notaci\242n infija: " << Default2 << endl;
        cout << "Imprimiendo su expresi\242n en notaci\242n polaca inversa: ";
        Default2.ImprimirPolacaInversa();

        cout << "\nResultado de la evaluaci\242n: " << Default2.EvaluarExpresion() << endl;

        cout << "\n\250Qu\202 pasa si se eval\243a Default?" << endl;
        cout << "Resultado de la evaluaci\242n: " << Default.EvaluarExpresion() << endl;


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
    cout << "Capturando expresi\242n" << endl;
    cout << "====================" << endl << endl;

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    try{

        cout << "Ingresa la expresi\242n: ";
        cin >> expr;

        cout << "\n[Exito] Expresi\242n v\240lida y lista para evaluar." << endl;

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

    cout << "Expresi\242n infija: " << expr;

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

void GInstrucciones()
{
    system("CLS");

    cout << "======================" << endl;
    cout << "INSTRUCCIONES DE NOTACI\240N" << endl;
    cout << "======================" << endl << endl;

    cout << "--- NOTACION DE FUNCIONES ---" << endl;
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
    cout << "\n-> Ejemplo v\240lido: \"sin(3.1416/2) + sqrt(16)\"." << endl;
    cout << "-> La multiplicaci\242n por par\202ntesis y un escalar sin usar el s\240mbolo '*' NO se admite (Ej: \"3(1+2))\"." << endl;
    cout << "-> Los c\240lculos trigonom\202tricos est\240n en radianes." << endl;
    cout << "-> Se aceptan n\243meros con punto decimal (Ej: \"0.3\", \".3\", \"3.\")" << endl;
    cout << "-> Se acepta notaci\242n cient\241fica (Ej: \"3.0e05\", \".3e2\", \".3e^02\", ...)" << endl;

    cout << endl;
}
