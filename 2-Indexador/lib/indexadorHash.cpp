#include "indexadorHash.h"

// ### FORMA CANÓNICA ###

// Constructor de copia
IndexadorHash::IndexadorHash (const IndexadorHash& indexador)
{
  indice = indexador.indice;
  indiceDocs = indexador.indiceDocs;
  informacionColeccionDocs = indexador.informacionColeccionDocs;
  pregunta = indexador.pregunta;
  indicePregunta = indexador.indicePregunta;
  infPregunta = indexador.infPregunta;
  stopWords = indexador.stopWords;
  ficheroStopWords = indexador.ficheroStopWords;
  tok = indexador.tok;
  directorioIndice = indexador.directorioIndice;
  tipoStemmer = indexador.tipoStemmer;
  almacenarEnDisco = indexador.almacenarEnDisco;
  almacenarPosTerm = indexador.almacenarPosTerm;
}

// Constructor por defecto
IndexadorHash::IndexadorHash ()
{
  pregunta = "";
  directorioIndice = "";
  tipoStemmer = 0;
  almacenarEnDisco = false;
  almacenarPosTerm = false;
}

// Destructor
IndexadorHash::~IndexadorHash ()
{
  indice.clear();
  indiceDocs.clear();
  informacionColeccionDocs.~InfColeccionDocs();
  pregunta.clear();
  indicePregunta.clear();
  infPregunta.~InformacionPregunta();
  stopWords.clear();
  ficheroStopWords.clear();
  tok.~Tokenizador();
  tipoStemmer = 0;
  almacenarEnDisco = false;
  almacenarPosTerm = false;
}

// Operador asignación
IndexadorHash&
IndexadorHash::operator= (const IndexadorHash& indexador)
{
  if (this != &indexador)
  {
    this->~IndexadorHash();
    // Se copia
    indice = indexador.indice;
    indiceDocs = indexador.indiceDocs;
    informacionColeccionDocs = indexador.informacionColeccionDocs;
    pregunta = indexador.pregunta;
    indicePregunta = indexador.indicePregunta;
    infPregunta = indexador.infPregunta;
    stopWords = indexador.stopWords;
    ficheroStopWords = indexador.ficheroStopWords;
    tok = indexador.tok;
    directorioIndice = indexador.directorioIndice;
    tipoStemmer = indexador.tipoStemmer;
    almacenarEnDisco = indexador.almacenarEnDisco;
    almacenarPosTerm = indexador.almacenarPosTerm;
  }

  return *this;
}

// ### CONTRUCTORES ###

// Constructor con parámetros de inicialización
IndexadorHash::IndexadorHash (const string& fichStopWords, const string& delimitadores,
  const bool& detectComp, const bool& minuscSinAcentos, const string& dirIndice,
  const int& tStemmer, const bool& almEnDisco, const bool& almPosTerm)
{
  ficheroStopWords = ficheroStopWords;
  // Almacena todas las stopwords del fichero
  almacenarStopWords();
  // Se inicializa el tokenizador
  tok.DelimitadoresPalabra(delimitadores);
  tok.CasosEspeciales(detectComp);
  tok.PasarAminuscSinAcentos(minuscSinAcentos);
  directorioIndice = dirIndice;
  if (directorioIndice.empty())
  { // Si está vacío
    // Se almacenará en el directorio donde se ejecuta el proyecto
    directorioIndice = "./";
  }
  tipoStemmer = tStemmer;
  almacenarEnDisco = almEnDisco;
  almacenarPosTerm = almPosTerm;
}

// Constructor a partir de una indexación previa
IndexadorHash::IndexadorHash (const string& directorioIndexacion)
{
  // TODO
}

// ### MÉTODOS Y FUNCIONES ###

/* Lee el fichero del atributo "ficheroStopWords" y guarda las palabras en el atributo
    "stopWords".
    Devolverá TRUE si se lleva a cabo correctamente.
*/
bool
IndexadorHash::almacenarStopWords ()
{
  ifstream fLectura;
  string linea = ""; // En cada línea habrá una stopWord

  fLectura.open(ficheroStopWords.c_str());

  if (fLectura.is_open())
  { // Si se abre el fichero del que se quiere leer
    while (!fLectura.eof())
    { // Mientras no se llegue al final del fichero
      linea = "";
      // Se lee la línea (que contiene una palabra)
      getline(fLectura, linea);
      if (!linea.empty())
      { // Si la línea no está vacía
        // Se inserta a stopWords
        stopWords.insert(linea);
      }
    }
    fLectura.close();
    return true;
  }
  
  cerr << "ERROR: No existe el archivo: -" << ficheroStopWords << "-" << endl;
  return false;
}

// Aplica stemming a una palabra
void
IndexadorHash::stemming(string& palabra) const
{
  stemmerPorter stemmer;
  stemmer.stemmer(palabra, tipoStemmer);
}

// Aplica el tratamiendo te mayúsculas y stemming a una palabra
string
IndexadorHash::aplicarTratamiento (const string& palabra) const
{
  string aux = palabra;

  if (DevolverPasarAminuscSinAcentos())
  {
    aux = tok.UsarMinuscSinAcentos(palabra);
  }
  stemming(aux);

  return aux;
}

// Lista el contenido del campo "indice" y del campo "indiceDocs"
void
IndexadorHash::ImprimirIndexacion () const
{
  string salida = "";

  salida += "Terminos indexados: \n";
  // Lista el contenido de campo "indice"
  for (auto termino = indice.begin(); termino != indice.end(); termino++)
  {
    salida += " " + termino->first + "\t" + termino->second.ToString() + "\n";
  }
  salida += "Documentos indexados: ";
  // Lista el contenido del campo indiceDocs
  for (auto doc = indiceDocs.begin(); doc != indiceDocs.end(); doc++)
  {
    salida += doc->first + "\t" + doc->second.ToString() + "\n";
  }

  cout << salida;
}

bool
IndexadorHash::IndexarPregunta (const string& preg)
{
  return true;
}

bool
IndexadorHash::DevuelvePregunta (string& preg) const
{
  return true;
}

bool
IndexadorHash::DevuelvePregunta (InformacionPregunta& inf) const
{
  return true;
}

void
IndexadorHash::ImprimirIndexacionPregunta ()
{
  string salida;

  salida = "Pregunta indexada: " + pregunta + "\nTerminos indexados en la pregunta: \n";
  // Se lista el contenido de "indicePregunta"
  for (auto pos = indicePregunta.begin(); pos != indicePregunta.end(); pos++)
  {
    salida += pos->first + "\t" + pos->second.ToString() + "\n";
  }
  salida += infPregunta.ToString();

  cout << salida;
}

void
IndexadorHash::ImprimirPregunta ()
{
  string salida;

  salida = "Pregunta indexada: " + pregunta +
    "\nInformacion de la pregunta: " + infPregunta.ToString();

  cout << salida;
}

// Devuelve TRUE si word ha sido indexado y devuelve la información en inf
bool
IndexadorHash::Devuelve (const string& word, InformacionTermino& inf) const
{
  string palabra;

  if (Existe(word))
  {
    palabra = aplicarTratamiento(word);
    inf = indice.at(palabra);
    return true;
  }
  // Si no encuentra el término, devuelve inf vacío
  inf.~InformacionTermino();

  return false;
}

/* Devuelve TRUE si word ha sido indexado y aparece en el documento de nombre nomDoc.
    Devuelve la información almacenada para word en el documento
*/
bool
IndexadorHash::Devuelve (const string& word, const string& nomDoc, InfTermDoc& infDoc) const
{
  unordered_map<string, InfDoc>::const_iterator documento = indiceDocs.find(nomDoc);

  if (Existe(word) && documento != indiceDocs.cend())
  { // Si existe la palabra indexada y el documento
    // Se trata el termino
    string termino = aplicarTratamiento(word);
    unordered_map<string, InformacionTermino>::const_iterator infoTermino = indice.find(termino);
    // Se recupera la información del término en el documento
    infDoc = infoTermino->second.getInfTermDoc(documento->second.getIdDoc());
    return true;
  }

  // Si no devuelve infDoc vacío
  infDoc.~InfTermDoc();
  return false;
}

bool
IndexadorHash::Existe (const string& word) const
{
  string palabra = word;

  aplicarTratamiento(palabra);

  return indice.find(palabra) != indice.end();
}

/* Se insertará la palabra (habiendo aplicado stemming y mayúsculas) si no
    estaba previamente indexada
*/
bool
IndexadorHash::Inserta (const string& word, const InformacionTermino& inf)
{
  if (Existe(word))
  { // Si el término no ha sido indexado
    string termino = aplicarTratamiento(word);
    // Se inserta
    pair<string, InformacionTermino> nuevoTermino(termino, inf);
    indice.insert(nuevoTermino);
    return true;
  }

  return false;
}