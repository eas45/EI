#ifndef _TOKENIZADOR_
#define _TOKENIZADOR_

#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>

using namespace std;

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
};
// Número de delimitadores posibles
static const short N_DELIMITERS = 36;

#endif