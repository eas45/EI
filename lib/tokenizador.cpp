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
    pos = nuevoDelimiters.find_first_not_of(delimiters, pos);
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

string
Tokenizador::minuscSinAcentos (const string& str) const
{
  string cadena;
  // Se construye la cadena de nuevo pero sin mayúsculas y sin acentos
  for (int i = 0; i < str.length(); i++)
  {
    switch ((unsigned char)str[i])
    {
    case 192: case 193:
    case 224: case 225:
      cadena += 'a';
      break;
    case 200: case 201:
    case 232: case 233:
      cadena += 'e';
      break;
    case 204: case 205:
    case 236: case 237:
      cadena += 'i';
      break;
    case 210: case 211:
    case 242: case 243:
      cadena += 'o';
      break;
    case 217: case 218:
    case 249: case 250:
      cadena += 'u';
      break;
    default:
      cadena += tolower(str[i]);
      break;
    }
  }

  return cadena;
}

void
Tokenizador::creaDelimitersCasoEspecial (string& delimitadores, const string& excepcion) const
{
  string::size_type pos = delimitadores.find_first_of(excepcion);

  while (pos != string::npos)
  {
    delimitadores.erase(delimitadores.begin() + pos);
    pos = delimitadores.find_first_of(excepcion);
  }
}

/*
 *  TOKENIZAR
 */



// TODO : Optimizar
// Tokenizador de PALABRAS
void
Tokenizador::Tokenizar (const string& str, list<string>& tokens) const
{
  string::size_type lastPos;
  string::size_type pos;
  string cadena = str;

  tokens.clear();
  // Comprueba primero si hay que tratar la cadena
  if (pasarAminuscSinAcentos)
  {
    cadena = minuscSinAcentos(str);
    cout << "CADENA A MINUSCSINACENTOS : " << cadena << endl;
  }
  // Comprueba si en la tokenización se debe tener en cuenta los
  // casos especiales
  if (casosEspeciales)
  { // Este bucle debe controlar los casos especiales
    // Prepara los delimitadores para los casos especiales
    string delimitadores = delimiters;
    if (delimitadores.find_first_of(" ") == string::npos)
    {
      delimitadores += " ";
      cout << "DELIMITADORES : " << delimitadores << "-" << endl;
    }

    lastPos = cadena.find_first_not_of(delimitadores, 0);
    pos = cadena.find_first_of(delimitadores, lastPos);

    while (lastPos != string::npos || pos != string::npos)
    {
      string auxDelimiters = delimitadores;
      if (cadena[lastPos] == 'h' || cadena[lastPos] == 'f')
      { // Puede ser una URL
      cout << "- Puede ser una URL: " << endl;
        if (cadena.find("http:", lastPos) == lastPos ||
            cadena.find("https:", lastPos) == lastPos ||
            cadena.find("ftp:", lastPos) == lastPos)
        { // Es una URL
        cout << "+Es una URL;" << endl;
          creaDelimitersCasoEspecial(auxDelimiters, URL_EXCEP);
          pos = cadena.find_first_of(auxDelimiters, pos);
          tokens.push_back(cadena.substr(lastPos, pos - lastPos));
        }
      }
      else if (isdigit(cadena[lastPos]) && (cadena[lastPos - 1] == ',' || cadena[lastPos - 1] == '.'))
      { // Es un número decimal que empieza por punto o coma
      cout << "+Es un DECIMAL mierder" << endl;
        pos = lastPos -= 1;
        do
        {
          pos = cadena.find_first_of(auxDelimiters, pos + 1);
          cout << "2Me paro por : " << cadena[pos] << endl;
        } while (pos != string::npos &&
                ((cadena[pos] == ',' || cadena[pos] == '.') && isdigit(cadena[pos + 1])));
        tokens.push_back("0" + cadena.substr(lastPos, pos - lastPos));
        cout << cadena.substr(lastPos, pos - lastPos) << endl;
      }
      else if ((cadena[pos] == ',' || cadena[pos] == '.') && isdigit(cadena[pos + 1]))
      { // Es un número decimal que empieza por un número
      cout << "+Es un DECIMAL normal" << endl;
        do
        {
          pos = cadena.find_first_of(auxDelimiters, pos + 1);
          cout << "1Me paro por : " << cadena[pos] << endl;
        } while (pos != string::npos && isdigit(cadena[pos + 1]));
        tokens.push_back(cadena.substr(lastPos, pos - lastPos));
        cout << cadena.substr(lastPos, pos - lastPos) << endl;
      }
      else // OTRO CASO
      {
        tokens.push_back(cadena.substr(lastPos, pos - lastPos));
      }
      lastPos = cadena.find_first_not_of(auxDelimiters, pos);
      pos = cadena.find_first_of(auxDelimiters, lastPos);
    }
  }
  else
  {
    lastPos = cadena.find_first_not_of(delimiters, 0);
    pos = cadena.find_first_of(delimiters, lastPos);

    while (lastPos != string::npos || pos != string::npos)
    {
      tokens.push_back(cadena.substr(lastPos, pos - lastPos));
      lastPos = cadena.find_first_not_of(delimiters, pos);
      pos = cadena.find_first_of(delimiters, lastPos);
    }
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
  list<string> listaFicheros;    // Nombre de los ficheros a tokenizar
  ifstream fLec;
  string cadena;            // Almacena el nombre del fichero a tokenizar
  bool todoOK = true;       // Variable auxiliar para saber que todo ha ido bien

  // 1) Se guardan los nombres de los ficheros
  fLec.open(i.c_str());
  if (fLec.is_open())
  {
    while (!fLec.eof())
    {
      cadena = "";
      getline(fLec, cadena);
      listaFicheros.push_back(cadena);
    }
  }
  fLec.close();
  // 2) Se tokeniza cada fichero de la lista
  while (listaFicheros.size() != 0)
  {
    if (!Tokenizar(*listaFicheros.begin()))
    {
      todoOK = false;
    }
    listaFicheros.pop_front();
  }

  return todoOK;
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

ostream& operator<< (ostream& os, const Tokenizador& token)
{
  os << "DELIMITADORES: " << token.delimiters <<
        "TRATA CASOS ESPECIALES: " << token.casosEspeciales <<
        " PASAR A MINUSCULAS Y ACENTOS: " << token.pasarAminuscSinAcentos;
}