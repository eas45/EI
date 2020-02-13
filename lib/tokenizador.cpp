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

// delimiters pasa a valer nuevoDelimiters, comprobando que no existan caracteres repetidos
void
Tokenizador::DelimitadoresPalabra (const string& nuevoDelimiters)
{
  delimiters.clear();
  AnyadirDelimitadoresPalabra(nuevoDelimiters);
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

// Devuelve los delimitadores
string
Tokenizador::DelimitadoresPalabra() const
{
  return delimiters;
}

// Cambia el valor de casosEspeciales
void
Tokenizador::CasosEspeciales (const bool& nuevoCasosEspeciales)
{
  casosEspeciales = nuevoCasosEspeciales;
}

// Devuelve el contenido de casosEspeciales
bool
Tokenizador::CasosEspeciales () const
{
  return casosEspeciales;
}

// Cambia el valor de pasarAminuscSinAcentos
void
Tokenizador::PasarAminuscSinAcentos (const bool& nuevoPasarAminuscSinAcentos)
{
  pasarAminuscSinAcentos = nuevoPasarAminuscSinAcentos;
}

// Devuelve el contenido de pasarAminuscSinAcentos
bool
Tokenizador::PasarAminuscSinAcentos () const
{
  return pasarAminuscSinAcentos;
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

/*
 *  TOKENIZAR
 */

// TODO : Optimizar
// Tokenizador de PALABRAS
void
Tokenizador::Tokenizar (const string& str, list<string>& tokens) const
{
  string::size_type lastPos = str.find_first_not_of(delimiters, 0);
  string::size_type pos = str.find_first_of(delimiters, lastPos + 1);

  tokens.clear();
  while (lastPos != string::npos || pos != string::npos)
  {
    tokens.push_back(str.substr(lastPos, pos - lastPos));
    lastPos = str.find_first_not_of(delimiters, pos + 1);
    pos = str.find_first_of(delimiters, lastPos + 1);
  }
}

// TODO : Optimizar
// Tokenizador de FICHEROS
// Devuelve 'true' si todo ha ido bien, si no mostrará un mensaje de error
bool
Tokenizador::Tokenizar (const string &i) const
{
  ifstream fLec;    // Fichero lectura
  string j = i + ".tk";     // Nombre del fichero de escritura
  ofstream fEsc;    // Fichero escritura
  string cadena;
  list<string> tokens;

  // 1) Lectura del fichero a tokenizar
  fLec.open(i.c_str());
  if (fLec.is_open())
  {
    while (!fLec.eof())
    {
      cadena = "";
      getline(fLec, cadena);
      if (cadena.length() != 0)
      {
        Tokenizar(cadena, tokens);
      }
    }
  }
  else
  {
    cerr << "ERROR: No existe el archivo: " << i << endl;

    return false;
  }
  fLec.close();
  // 2) Escritura de las palabras tokenizadas
  fEsc.open(j.c_str());
  list<string>::iterator itS;
  for (itS = tokens.begin(); itS != tokens.end(); itS++)
  {
    fEsc << (*itS) << endl;
  }
  fEsc.close();

  return true;
}

// TODO
bool
Tokenizador::TokenizarListaFicheros (const string& i) const
{
  
  return false;
}

bool
Tokenizador::TokenizarDirectorio (const string& dirAIndexar) const
{
  struct stat dir;
  // Compruebo la existencia del directorio
  int err = stat(dirAIndexar.c_str(), &dir);

  if (err == -1 || !S_ISDIR(dir.st_mode))
  {
    return false;
  }
  else
  {
    // Hago una lista en un fichero con find>fich
    string cmd = "find " + dirAIndexar + " -follow | sort > .lista_fich";
    system(cmd.c_str());

    return TokenizarListaFicheros(".lista_fich");
  }
}