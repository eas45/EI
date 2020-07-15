#ifndef _TOKENIZADOR_
#define _TOKENIZADOR_

#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>

using namespace std;

enum TCasosEspeciales
{
  ninguno,
  url,
  decSigno,   // Decimal que empieza por ',' o '.'
  decNumero,  // Decimal que empieza por un número
  email,
  acronimo,
  multipal
};

class Tokenizador {
  friend ostream& operator<<(ostream&, const Tokenizador&);
  // cout << "DELIMITADORES: " << delimiters << " TRATA CASOS ESPECIALES: "
  //      << casosEspeciales << " PASAR A MINUSCULAS Y SIN ACENTOS: "
  //      << pasarAminuscSinAcentos;

  private:
  string delimiters;                // Delimitadores de términos
  bool casosEspeciales;             // Detectará palabras compuestas y casos especiales
  bool pasarAminuscSinAcentos;      // Pasará a minúsculas y quitará acentos (antes de tokenizar)

  void Copia(const Tokenizador&);
  // Convierte los caracteres de una cadena a minúsculas y sin acentos
  string minuscSinAcentos(const string&) const;
  void creaDelimitersCasoEspecial(string&, const string&) const;
  bool esURL (const string&, const string::size_type&, const string::size_type&, const string&) const;
  TCasosEspeciales asignaCasoEspecial (const string&, const string::size_type&, const string::size_type&, const string&) const;
  bool esNumero (const string&) const;
  string tokenizarDecimal (const string&, string::size_type&, string::size_type&, const string&) const;
  string tokenizarEmail (const string&, string::size_type&, string::size_type&, const string&) const;
  string tokenizarAcronimo (const string&, string::size_type&, string::size_type&, const string&) const;
  string tokenizarMultipalabra (const string&, string::size_type&, string::size_type&, const string&) const;

  public:
  Tokenizador (const string&, const bool&, const bool&);
    /* Inicializa delimiters a delimitadoresPalabra filtrando que no se introduzcan
      delimitadores repetidos (de izquierda a derecha, en cuyo caso se eliminarían
      los que hayan sido repetidos por la derecha); casosEspeciales a kcasosEspeciales;
      pasarAminuscSinAcentos a minuscSinAcentos;
    */

  // Constructor de copia
  Tokenizador (const Tokenizador&);

  /* Constructor por defecto
    Inicializa todos los delimitadores ",;:.-/+*\\ '\"{}[]()<>¡!¿?&#=\t\n\r@";
    casosEspeciales a true; pasarAminuscSinAcentos a false
  */
  Tokenizador ();

  /* Destructor
    Pone delimiters = "";
  */
  ~Tokenizador ();

  // Operador asignación
  Tokenizador& operator= (const Tokenizador&);

  /* Tokeniza str devolviendo el resultado en tokens. La lista tokens se vaciará
    antes de almacenar el resultado de la tokenización.
  */
  void Tokenizar (const string&, list<string>&) const;

  bool Tokenizar (const string&, const string&) const;

  bool Tokenizar (const string&) const;

  bool TokenizarListaFicheros (const string&) const;

  bool TokenizarDirectorio (const string&) const;

  void DelimitadoresPalabra (const string&);

  void AnyadirDelimitadoresPalabra (const string&);

  string DelimitadoresPalabra() const;

  void CasosEspeciales (const bool&);

  bool CasosEspeciales () const;

  void PasarAminuscSinAcentos (const bool&);

  bool PasarAminuscSinAcentos () const;

  // MÉTODOS Y FUNCIONES
  string UsarMinuscSinAcentos(const string&) const;
  string ToString () const;
};
// Número de delimitadores posibles
static const short N_DELIMITERS = 36;
static const string URL_EXCEP = "_:/.?&-=#@";
static const string DEC_EXCEP = ",.";
static const string EMAIL_EXCEP = ".-_";

#endif