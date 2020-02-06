#include "tokenizador.h"

/******************
 * FORMA CANÓNICA *
 ******************/

// Constructor por defecto
Tokenizador::Tokenizador () {
  delimiters = ",;:.-/+*\\ '\"{}[]()<>¡!¿?&#=\t\n\r@";
  casosEspeciales = true;
  pasarAminuscSinAcentos = false;
}

Tokenizador::Tokenizador (const string& delimitadoresPalabra, const bool& kcasosEspeciales,
                          const bool& minuscSinAcentos) {
  // TODO : ¡¡ Filtrar delimitadores !!
  delimiters = delimitadoresPalabra;
  casosEspeciales = kcasosEspeciales;
  pasarAminuscSinAcentos = minuscSinAcentos;
}

// Constructor de copia
Tokenizador::Tokenizador (const Tokenizador& token) {
  copia(token);
}

// Destructor
Tokenizador::~Tokenizador () {
  delimiters = "";
}

// Operador asignación
Tokenizador& Tokenizador::operator= (const Tokenizador& token) {
  if (this != &token) {
    (*this).~Tokenizador();
    copia(token);
  }
}

/**********************
 * GETTTERS Y SETTERS *
 **********************/

// Devuelve los delimitadores
string Tokenizador::DelimitadoresPalabra() const {
  return delimiters;
}

// Devuelve el contenido de casosEspeciales
bool Tokenizador::CasosEspeciales () const {
  return casosEspeciales;
}

// Devuelve el contenido de pasarAminuscSinAcentos
bool Tokenizador::PasarAminuscSinAcentos () const {
  return pasarAminuscSinAcentos;
}

// Añade nuevos delimitadores a la cadena delimiters
void Tokenizador::AnyadirDelimitadoresPalabra (const string& nuevoDelimiters) {
  // TODO : Comprobar que no se almacenan caracteres repetidos
}

// Cambia el valor de casosEspeciales
void Tokenizador::CasosEspeciales (const bool& nuevoCasosEspeciales) {
  casosEspeciales = nuevoCasosEspeciales;
}

// Cambia el valor de pasarAminuscSinAcentos
void Tokenizador::PasarAminuscSinAcentos (const bool& nuevoPasarAminuscSinAcentos) {
  pasarAminuscSinAcentos = nuevoPasarAminuscSinAcentos;
}

/*************************
 ** MÉTODOS Y FUNCIONES **
 *************************/

void Tokenizador::copia (const Tokenizador& token) {
  delimiters = token.DelimitadoresPalabra();
  casosEspeciales = token.CasosEspeciales();
  pasarAminuscSinAcentos = token.PasarAminuscSinAcentos();
}