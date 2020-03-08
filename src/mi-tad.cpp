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
  
  // Prueba URL
  Tokenizador t2("\".,", true, true);
  t2.Tokenizar("hHttp:\\www.google.es.coma HTTPs:lol.lol\"skere", lt1);
  imprimirListaSTL(lt1);

  // Prueba DECIMALES
  t2.Tokenizar("10. 23.01.,\"\" 20,12.456,7.8.9,\" .34 ,56 10.0a ,,.10.100.00.0 jaja6 3.15.69,,. 90.0  lmao  .98$ 0 ,24,89% ,24,89 ,13466.558 1,23E+10 ,8e10 ,,.10.100.a.0 25E+9", lt1);
  imprimirListaSTL(lt1);

  // Prueba EMAIL
  t2.DelimitadoresPalabra("@.&");
  t2.Tokenizar("hola@email.com tremenda@@wea tremen@da@wea cat@iuii.ua.es@cd cat@@iuii.ua.es", lt1);
  imprimirListaSTL(lt1);

  // Prueba ACRONIMO
  t2.DelimitadoresPalabra("@.&");
  t2.Tokenizar("U.S.A p1 e.g p2. La ..N.A.S.A... A..l 100.a0.00", lt1);
  imprimirListaSTL(lt1);

  // Prueba MULTIPALABRAS
  t2.DelimitadoresPalabra("-#");
  t2.Tokenizar("pal1 -MS-DOS p1 p2 -MS-DOS--TRES TU-la---", lt1);
  imprimirListaSTL(lt1);
}