#include <iostream> 
#include <string>
#include <list>
#include <sstream>
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
        t2.Tokenizar("hHttp:\\www.google.es.coma HTTPs:lol.lol\"skere", lt1);
        imprimirListaSTL(lt1);

        string str = "12E+10";
        if (isdigit(atoi(str.c_str())))
        {
                cout << "es digito" << endl;
        }
        cout << str.c_str() << endl;
        cout << atoi(str.c_str()) << endl;
        cout << isdigit(atoi(str.c_str())) << endl;
        /* string::size_type p = str.find_first_of('2');
        if (isalpha(str[p + 1]) || isdigit(str[p + 1]))
        {
                cout << "SKRE" << endl;
        }
        t2.Tokenizar("", lt1);
        imprimirListaSTL(lt1); */
        int k = 90;
        string n;
        stringstream aux;
        aux << k;
        n = aux.str();
        cout << n << " -- " << n.size() << endl;

        t2.Tokenizar("10.0a ,,.10.100.00.0 23.01.,jaja6 3.15.69,,. 90.0  lmao  .98$ 0 .24,89% ,13466.558 1,23E+10 ,8e10 ,,.10.100.a.0 25E+9", lt1);
        imprimirListaSTL(lt1);

        t2.DelimitadoresPalabra("@.&");
        t2.Tokenizar("hola@email.com tremenda@@wea tremen@da@wea cat@iuii.ua.es@cd", lt1);
        imprimirListaSTL(lt1);

        t2.DelimitadoresPalabra("@.&");
        t2.Tokenizar("U.S.A p1 e.g p2. La ..N.A.S.A... A..l 100.a0.00", lt1);
        imprimirListaSTL(lt1);

        t2.DelimitadoresPalabra("-#");
        t2.Tokenizar("pal1 -MS-DOS p1 p2 -MS-DOS--TRES TU-la---", lt1);
        imprimirListaSTL(lt1);
}