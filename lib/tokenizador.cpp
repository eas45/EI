#include "tokenizador.h"

/******************
 * FORMA CANÓNICA *
 ******************/

// Constructor por defecto
Tokenizador::Tokenizador ()
{
  delimiters = ",;:.-/+*\\ '\"{}[]()<>¡!¿?&#=\t\n\r@";
  casosEspeciales = true;
  pasarAminuscSinAcentos = false;
}

Tokenizador::Tokenizador (const string& delimitadoresPalabra, const bool& kcasosEspeciales,
                          const bool& minuscSinAcentos)
{
  if (delimiters.size() < N_DELIMITERS)
  { // Se puede dar el caso de encontrar un nuevo delimitador
    AnyadirDelimitadoresPalabra(delimitadoresPalabra);
  }
  casosEspeciales = kcasosEspeciales;
  pasarAminuscSinAcentos = minuscSinAcentos;
}

// Constructor de copia
Tokenizador::Tokenizador (const Tokenizador& token)
{
  Copia(token);
}

// Destructor
Tokenizador::~Tokenizador ()
{
  delimiters = "";
}

// Operador asignación
Tokenizador&
Tokenizador::operator= (const Tokenizador& token)
{
  if (this != &token)
  {
    (*this).~Tokenizador();
    Copia(token);
  }
}

/**********************
 * GETTTERS Y SETTERS *
 **********************/

// Devuelve los delimitadores
string
Tokenizador::DelimitadoresPalabra() const
{
  return delimiters;
}

// Devuelve el contenido de casosEspeciales
bool
Tokenizador::CasosEspeciales () const
{
  return casosEspeciales;
}

// Devuelve el contenido de pasarAminuscSinAcentos
bool
Tokenizador::PasarAminuscSinAcentos () const
{
  return pasarAminuscSinAcentos;
}

// Añade nuevos delimitadores a la cadena delimiters
void
Tokenizador::AnyadirDelimitadoresPalabra (const string& nuevoDelimiters)
{
  // Busca el primer caracter que no esté como delimitador
  string::size_type pos = nuevoDelimiters.find_first_not_of(delimiters);

  while (pos != string::npos)
  {
    // Lo añade a los delimitadores
    delimiters.push_back(nuevoDelimiters[pos]);
    // Busca el siguiente
    pos = nuevoDelimiters.find_first_not_of(delimiters, pos + 1);
  }
}

// Cambia el valor de casosEspeciales
void
Tokenizador::CasosEspeciales (const bool& nuevoCasosEspeciales)
{
  casosEspeciales = nuevoCasosEspeciales;
}

// Cambia el valor de pasarAminuscSinAcentos
void
Tokenizador::PasarAminuscSinAcentos (const bool& nuevoPasarAminuscSinAcentos)
{
  pasarAminuscSinAcentos = nuevoPasarAminuscSinAcentos;
}

/*************************
 ** MÉTODOS Y FUNCIONES **
 *************************/

void
Tokenizador::Copia (const Tokenizador& token)
{
  delimiters = token.DelimitadoresPalabra();
  casosEspeciales = token.CasosEspeciales();
  pasarAminuscSinAcentos = token.PasarAminuscSinAcentos();
}