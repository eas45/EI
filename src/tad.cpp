#include <iostream> 
#include <string>
#include <list> 
#include "tokenizador.h"

using namespace std;

///////// Comprobaci?n de que vac?e la lista resultado

void imprimirListaSTL(const list<string>& cadena)
{
        list<string>::const_iterator itCadena;
        for(itCadena=cadena.begin(); itCadena!=cadena.end(); itCadena++)
        {
                cout << (*itCadena) << ", ";
        }
        cout << endl;
}

int
main(void)
{
	bool kCasosEspeciales = true, kpasarAminusculas = false;

	list<string> lt1, lt2;

        Tokenizador a("@.&", true, false); 
        list<string> tokens; 

        a.Tokenizar("U..S.A p1 e..g. p2. La", lt1);
        imprimirListaSTL(lt1);

        a.Tokenizar("...U.S.A p1 e..g. p2. La", lt1);
        imprimirListaSTL(lt1);

        a.Tokenizar("Hack.4.Good p1 ", lt1);
        imprimirListaSTL(lt1);
        

        // TOKENIZADOR SIMPLE
        Tokenizador t1(".", false, true);
        t1.Tokenizar("U.S.A Ñ ÁÀáàÉÈéèÍÌíìÓÒóòÚÙúù", lt1);
        imprimirListaSTL(lt1);

        string s = "è¡";
        unsigned char c = s[0];
        int i = c;
        char x = s[1];
        cout << c << " -> " << i << " -- " << x << endl;
        cout << (unsigned char)209 << endl;
        s = "ñ";
        cout << s << endl;
        if ((unsigned char)s[0] == 232)
        {
                cout << "sí" << endl;
        }

        // PRUEBAS CON CADENAS
        /* string str = "hola";
        string::size_type pos = str.find_first_of("hl");
        cout << "posicion : " << pos << endl;
        while (pos != string::npos)
        {
                cout << "cadena : " << str << endl;
                str.erase(str.begin() + pos);
                cout << "cadena B : " << str << endl;
                cout << "PRIMERA LETRA = " << str[0] << endl;
                pos = str.find_first_of("hl");

                cout << "posicion : " << pos << endl;
        }
        cout << str << endl; */

        // Prueba URL
        Tokenizador t2("\".,", true, true);
        t2.Tokenizar("23.01.,jaja6 3.15.69,,.http:\\www.google.es.coma HTTPs:lol.lol\"skere 90.0  lmao  .98 0 .24,89 e,13466.558 ", lt1);
        imprimirListaSTL(lt1);

        string str = "e2";
        if (isdigit(str[0]))
        {
                cout << "es digito" << endl;
        }
}