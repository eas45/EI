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

        // AMINUSCSINACENTOS
        /*Tokenizador t2;
        string str = "SkàRÁáÀ";
        t2.minuscSinAcentos(str);
        cout << str << endl;*/
}