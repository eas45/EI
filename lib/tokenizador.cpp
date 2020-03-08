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
    case 209:
      cadena += (unsigned char)241;
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


//////////////////////
// CASOS ESPECIALES //
//////////////////////

TCasosEspeciales
Tokenizador::asignaCasoEspecial (const string& cadena, const string::size_type& lastPos, const string::size_type& pos, const string& delimitadores) const
{
  if ((cadena.find("http:", lastPos) == lastPos || cadena.find("https:") == lastPos || cadena.find("ftp:") == lastPos) &&
    (cadena[pos] == ':' && pos != cadena.size() - 1))
  {
    return TCasosEspeciales::url;
  }
  string::size_type auxPos;
  string auxDelimiters;
  // Decimal con primer signo igual a ','
  if (!isdigit(cadena[lastPos - 2]) && cadena[lastPos - 1] == ',' && isdigit(cadena[lastPos]))
  { // Puede ser un decimal comenzando en signo
    // Hay que comprobar que no sea ni notación científica
    auxPos = cadena.find_first_of(delimitadores, pos + 1);
    string::size_type posE = cadena.find_first_of("Ee", pos);
    if (posE != string::npos&& posE < auxPos)
    { // Notación científica
      return TCasosEspeciales::ninguno;
    }
    // Hay que comprobar si es acrónimo
    auxDelimiters = delimitadores;
    creaDelimitersCasoEspecial(auxDelimiters, DEC_EXCEP);
    auxPos = cadena.find_first_of(auxDelimiters, pos);
    if (esNumero(cadena.substr(lastPos, auxPos - lastPos)))
    {
      return TCasosEspeciales::decSigno;
    }
    else
    {
      return TCasosEspeciales::acronimo;
    }
  }
  if (isdigit(cadena[lastPos]) && cadena[pos] == ',' && isdigit(cadena[pos + 1]))
  { // Puede ser un decimal comenzando en número
    string::size_type posE = cadena.find_first_of("Ee", pos);
    if (posE != string::npos)
    { // Notación científica
      return TCasosEspeciales::ninguno;
    }
    // Hay que comprobar si es acrónimo
    auxDelimiters = delimitadores;
    creaDelimitersCasoEspecial(auxDelimiters, DEC_EXCEP);
    auxPos = cadena.find_first_of(auxDelimiters, pos);
    if (esNumero(cadena.substr(lastPos, auxPos - lastPos)))
    {
      return TCasosEspeciales::decNumero;
    }
    else
    {
      return TCasosEspeciales::acronimo;
    }
  }
  // Decimal con primer signo igual a '.'
  if (cadena[lastPos - 1] == '.' && isdigit(cadena[lastPos]))
  { // Puede ser un decimal que empieza por signo
    // Hay que comprobar si es acrónimo
    auxDelimiters = delimitadores;
    creaDelimitersCasoEspecial(auxDelimiters, DEC_EXCEP);
    auxPos = cadena.find_first_of(auxDelimiters, pos);
    if (esNumero(cadena.substr(lastPos, auxPos - lastPos)))
    {
      return TCasosEspeciales::decSigno;
    }
    else
    {
      return TCasosEspeciales::acronimo;
    }
  }
  if (isdigit(cadena[lastPos]) && cadena[pos] == '.' && isdigit(cadena[pos + 1]))
  { // Puede ser un decimal comenzando en números
    // Hay que comprobar si es acrónimo
    auxDelimiters = delimitadores;
    creaDelimitersCasoEspecial(auxDelimiters, DEC_EXCEP);
    auxPos = cadena.find_first_of(auxDelimiters, pos);
    if (esNumero(cadena.substr(lastPos, auxPos - lastPos)))
    {
      return TCasosEspeciales::decNumero;
    }
    else
    {
      return TCasosEspeciales::acronimo;
    }
  }
  // Email
  if (cadena.find_first_of(delimitadores, pos - 1) != (pos - 1) && cadena[pos] == '@' &&
      cadena.find_first_of(delimitadores, pos + 1) != (pos + 1))
  { // Puede ser un email o ninguno
    // Hay que comprobar si el formato es correcto (no contiene más '@')
    auxDelimiters = delimitadores;
    creaDelimitersCasoEspecial(auxDelimiters, EMAIL_EXCEP);
    auxPos = cadena.find_first_of(auxDelimiters, pos);
    string::size_type posA = cadena.find('@', pos + 1);
    if (posA != string::npos && posA < auxPos)
    { // Formato incorrecto
      return TCasosEspeciales::ninguno;
    }
    return TCasosEspeciales::email;
  }
  // Acrónimo
  if (cadena[pos] == '.' && cadena.find_first_of(delimitadores, pos - 1) != (pos - 1) &&
      cadena.find_first_of(delimitadores, pos + 1) != (pos + 1))
  {
    return TCasosEspeciales::acronimo;
  }
  // Multipalabra
  if (cadena[pos] == '-' && cadena.find_first_of(delimitadores, pos - 1) != (pos - 1) &&
      cadena.find_first_of(delimitadores, pos + 1) != (pos + 1))
  {
    return TCasosEspeciales::multipal;
  }
  return TCasosEspeciales::ninguno;
}

// DECIMALES

// Comprueba que mantiene un formato correcto para ser un número
// decimal con '.'
bool
Tokenizador::esNumero (const string& cadena) const
{
  for (int i = 0; i < cadena.size(); i++)
  {
    if (isalpha(cadena[i]) ||
        ((cadena[i] == '.' || cadena[i] == ',') &&
        (cadena[i + 1] == '.' || cadena[i + 1] == ',')))
    {
      return false;
    }
  }

  return true;
}

string
Tokenizador::tokenizarDecimal (const string& cadena, string::size_type& lastPos, string::size_type& pos, const string& auxDelimiters) const
{
  
  do
  {
    pos = cadena.find_first_of(auxDelimiters, pos + 1);
  } while (pos != string::npos &&
          ((cadena[pos] == ',' || cadena[pos] == '.') && isdigit(cadena[pos + 1])));

  string auxCadena = cadena.substr(lastPos, pos - lastPos);
  if(auxCadena[auxCadena.size() - 1] == '%' || auxCadena[auxCadena.size() - 1] == '$')
  {
    if (pos != string::npos)
    {
      pos -= 1;
    }
    else
    {
      pos = cadena.size() - 1;
    }
    
  }

  return cadena.substr(lastPos, pos - lastPos);
}

string
Tokenizador::tokenizarEmail (const string& cadena, string::size_type& lastPos, string::size_type& pos, const string& auxDelimiters) const
{
  string::size_type auxPos = cadena.find_first_of(auxDelimiters, pos + 1);
  if (cadena[auxPos] != '@')
  {
    pos = auxPos;
  }

  return cadena.substr(lastPos, pos - lastPos);
}

string
Tokenizador::tokenizarAcronimo (const string& cadena, string::size_type& lastPos, string::size_type& pos, const string& auxDelimiters) const
{
  do
  {
    pos = cadena.find_first_of(auxDelimiters, pos + 1);
  } while (pos != string::npos &&
          ((cadena[pos] == '.') && cadena.find_first_of(auxDelimiters, pos + 1) != pos + 1));

  return cadena.substr(lastPos, pos - lastPos);
}

string
Tokenizador::tokenizarMultipalabra (const string& cadena, string::size_type& lastPos, string::size_type& pos, const string& auxDelimiters) const
{
  do
  {
    pos = cadena.find_first_of(auxDelimiters, pos + 1);
  } while (pos != string::npos &&
          ((cadena[pos] == '-') && cadena[pos + 1] != '-'));

  return cadena.substr(lastPos, pos - lastPos);
}

// TODO : Optimizar
// Tokenizador de PALABRAS
void
Tokenizador::Tokenizar (const string& str, list<string>& tokens) const
{
  string::size_type lastPos;
  string::size_type pos;
  string cadena = str;
  string auxToken;

  tokens.clear();
  // Comprueba primero si hay que tratar la cadena
  if (pasarAminuscSinAcentos)
  {
    cadena = minuscSinAcentos(str);
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
    }

    // Hace la primera tokenización
    lastPos = cadena.find_first_not_of(delimitadores, 0);
    pos = cadena.find_first_of(delimitadores, lastPos);

    while (lastPos != string::npos || pos != string::npos)
    {
      // Asigna un caso especial
      TCasosEspeciales casoEspecial = asignaCasoEspecial(cadena, lastPos, pos, delimitadores);

      string auxDelimiters = delimitadores;

      switch (casoEspecial)
      {
      case TCasosEspeciales::url :
        creaDelimitersCasoEspecial(auxDelimiters, URL_EXCEP);
        pos = cadena.find_first_of(auxDelimiters, pos);
        auxToken = cadena.substr(lastPos, pos - lastPos);
        //tokens.push_back(cadena.substr(lastPos, pos - lastPos));
        break;
      case TCasosEspeciales::decSigno :
        pos = lastPos -= 1;
        auxToken = '0' + tokenizarDecimal(cadena, lastPos, pos, auxDelimiters);
        //tokens.push_back(auxToken);
        break;
      case TCasosEspeciales::decNumero :
        auxToken = tokenizarDecimal(cadena, lastPos, pos, auxDelimiters);
        //tokens.push_back(auxToken);
        break;
      case TCasosEspeciales::email :
        creaDelimitersCasoEspecial(auxDelimiters, EMAIL_EXCEP);
        auxToken = tokenizarEmail(cadena, lastPos, pos, auxDelimiters);
        //tokens.push_back(auxToken);
        break;
      case TCasosEspeciales::acronimo :
        auxToken = tokenizarAcronimo(cadena, lastPos, pos, auxDelimiters);
        //tokens.push_back(auxToken);
        break;
      case TCasosEspeciales::multipal :
        auxToken = tokenizarMultipalabra(cadena, lastPos, pos, auxDelimiters);
        //tokens.push_back(auxToken);
        break;
      default:
        auxToken = cadena.substr(lastPos, pos - lastPos);
       
        if (isdigit(auxToken[0]) && esNumero(auxToken) &&
            (auxToken[auxToken.size() - 1] == '%' || auxToken[auxToken.size() - 1] == '$'))
        {
           if (isdigit(auxToken[0]) && auxToken.size() > 1 && pos == string::npos)
          {
            tokens.push_back(cadena.substr(lastPos, cadena.size() - lastPos - 1));
            auxToken = auxToken.substr(auxToken.size() - 1, 1);
          }
          else
          {
            pos--;
            auxToken = cadena.substr(lastPos, pos - lastPos);
          }
        }
        else
        {
          auxToken = cadena.substr(lastPos, pos - lastPos);
          //tokens.push_back(cadena.substr(lastPos, pos - lastPos));
        }
        break;
      }
      tokens.push_back(auxToken);
      // Tokeniza lo siguiente
      lastPos = cadena.find_first_not_of(delimitadores, pos);
      pos = cadena.find_first_of(delimitadores, lastPos);
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
        " TRATA CASOS ESPECIALES: " << token.casosEspeciales <<
        " PASAR A MINUSCULAS Y SIN ACENTOS: " << token.pasarAminuscSinAcentos;
}