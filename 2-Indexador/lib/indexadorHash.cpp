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
}