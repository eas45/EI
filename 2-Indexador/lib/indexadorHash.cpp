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

// Devuelve TRUE si recuperan los documentos correctamente
bool
IndexadorHash::cargarDocsAindexar (const string& ficheroDocumentos, list<string>& listaDocs) const
{
  ifstream f;
  f.open(ficheroDocumentos.c_str());

  if (f.is_open())
  {
    string linea;
    while (!f.eof())
    {
      getline(f, linea);
      listaDocs.push_back(linea);
    }
    
    f.close();

    return true;
  }

  return false;
}

// Devuelve TRUE si se crea el índice para la colección de documentos de "ficheroDocumentos".
bool
IndexadorHash::Indexar (const string& ficheroDocumentos)
{
  list<string> listaDocsIndexar;
  
  if (cargarDocsAindexar(ficheroDocumentos, listaDocsIndexar))
  { // Si se han cargado los ficheros correctamente
    // Se indexa cada uno de ellos
    try
    {
      ifstream fichero;
      for (string doc : listaDocsIndexar)
      { // Para cada documento
        // Comprueba si ya ha sido indexado
        unordered_map<string, InfDoc>::iterator itDoc = indiceDocs.find(doc);
        if (itDoc == indiceDocs.end())
        { // Si el documento NO ha sido indexado, se indexa
          // Se crea la información del documento
          
        }
        else
        { // Si el documento ha sido previamente indexado
          // Comprueba si la fecha de modificación es posterior a la ya almacenada
          
        }
        
      }
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
  }
  else
  {
    cout << "ERROR: En Indexar con el documento " << ficheroDocumentos << endl;
  }

  return false;
}

/* Se guardará en disco duro (incluidos todos los parámetros de la parte privada)
    Devolverá TRUE si finaliza la operación correcctamente
*/
bool  // TODO
IndexadorHash::GuardarIndexacion () const
{
  // Se crean los punteros para manejar la ruta del directorio
  DIR *directorio;
  struct dirent *entrada;

  // Se intenta abrir el directorio de "directorioIndice"
  directorio = opendir(directorioIndice.c_str());
  if (!directorio)
  { // Si no existe
    // Se crea
    string comando = "mkdir " + directorioIndice;
    system(comando.c_str());
    // Se vuelve a intentar abrir el directorio
    directorio = opendir(directorioIndice.c_str());
  }

  if (directorio)
  { // Si el directorio existe o ha sido creado correctamente
    // Abre o crea el fichero donde se guardará la indexación
    ofstream ficheroIndexacion(NOMBRE_INDEX.c_str());

    //ficheroIndexacion << 
  }  

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

bool
IndexadorHash::Borra (const string& word)
{
  if (Existe(word))
  {
    string palabra = aplicarTratamiento(word);
    indice.erase(palabra);
    return true;
  }

  return false;
}

bool
IndexadorHash::BorraDoc (const string& nomDoc)
{
  // Se recupera el puntero del nombre del documento
  unordered_map<string, InfDoc>::const_iterator doc = indiceDocs.find(nomDoc);

  if (doc != indiceDocs.cend())
  { // Si lo ha encontrado
    // Se borran todos los términos del documento
    long int id = doc->second.getIdDoc();
    // Se busca en todos los términos indexados
    unordered_map<long int, InfTermDoc>::const_iterator posIndice;
    for (unordered_map<string, InformacionTermino>::iterator pos = indice.begin(); 
      pos != indice.end(); pos++)
    { // Para cada elemento del índice
      // Intenta eliminar el término indexado del documento de igual id
      pos->second.eliminarDoc(id);
    }
    // Después se elimina de la colección de documentos
    // TODO

    return true;
  }

  return false;
}

// Borra todos los términos del índice de documentos
void
IndexadorHash::VaciarIndiceDocs ()
{
  indiceDocs.clear();
}

// Borra todos los términos del índice de la pregunta
void
IndexadorHash::VaciarIndicePreg ()
{
  indicePregunta.clear();
}

// Sustituye la información almacenada en el índice por la de "inf"
bool
IndexadorHash::Actualiza (const string& word, const InformacionTermino& inf)
{
  if (Existe(word))
  { // Si existe
    // Actualiza la información del término indexado
    string termino = aplicarTratamiento(word);
    indice.at(termino) = inf;

    return true;
  }

  return false;
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

// Devuelve el número de términos diferentes indexados
int
IndexadorHash::NumPalIndexadas () const
{
  return indice.size();
}

// Devuelve el contenido del campo "ficheroStopWords"
string
IndexadorHash::DevolverFichPalParada () const
{
  return ficheroStopWords;
}

// Muestra por pantalla las palabras de parada almacenadas
void
IndexadorHash::ListarPalParada () const
{
  string salida;

  for (const string& palParada : stopWords)
  {
    salida += palParada + "\n";
  }

  cout << salida;
}

// Devuelve el número de palabras de parada almacenadas
int
IndexadorHash::NumPalParada () const
{
  return stopWords.size();
}

// Devuelve los delimitadores utilizados por el tokenizador
string
IndexadorHash::DevolverDelimitadores () const
{
  return tok.DelimitadoresPalabra();
}

// Devuelve si el tokenizador analiza los casos especiales
bool
IndexadorHash::DevolverCasosEspeciales () const
{
  return tok.CasosEspeciales();
}

// Devuelve si el tokenizador pasa a minúsculas sin acentos
bool
IndexadorHash::DevolverPasarAminuscSinAcentos () const
{
  tok.PasarAminuscSinAcentos();
}

// Devuelve el valor de almacenarPosTerm
bool
IndexadorHash::DevolverAlmacenarPosTerm () const
{
  return almacenarPosTerm;
}

// Devulve "directorioIndice"
string
IndexadorHash::DevolverDirIndice () const
{
  return directorioIndice;
}

// Devuelve el valor de "tipoStemmer"
int
IndexadorHash::DevolverTipoStemming () const
{
  return tipoStemmer;
}

// Devuekve el valor indicado en "almEnDisco"
bool
IndexadorHash::DevolverAlmEnDisco () const
{
  return almacenarEnDisco;
}

// Muestra por pantalla la información de la colección de documentos
void
IndexadorHash::ListarInfColeccDocs () const
{
  cout << informacionColeccionDocs.ToString() << endl;
}

// Muestra el contenido de "indice"
void
IndexadorHash::ListarTerminos () const
{
  string salida = "";

  for (unordered_map<string, InformacionTermino>::const_iterator pos = indice.cbegin();
    pos != indice.cend(); pos++)
  {
    salida += pos->first + "\t" + pos->second.ToString() + "\n";
  }

  cout << salida;
}

/* Devuelve TRUE si el documento ha sido indexado y muestra por pantalla los términos
    indexados del documento con ese nombre
*/
bool
IndexadorHash::ListarTerminos (const string& nomDoc) const
{
  unordered_map<string, InfDoc>::const_iterator doc = indiceDocs.find(nomDoc);

  if (doc != indiceDocs.cend())
  { // Si el documento ha sido indexado
    // Se buscan los términos indexados procendentes del mismo
    string salida = "";
    long int id = doc->second.getIdDoc();
    // Recupera todos los términos indexados que pertenezcan a ese documento
    for (unordered_map<string, InformacionTermino>::const_iterator pos = indice.cbegin();
      pos != indice.cend(); pos++)
    {
      if (pos->second.perteneceAdoc(id))
      { // Si el término pertenece al documento, se añade a la cadena de salida
        salida += pos->first + pos->second.ToString() + "\n";
      }
    }
    // Muestra el término y la información del término
    cout << salida;

    return true;
  }

  return false;
}

// Muestra el contenido de "indiceDocs"
void
IndexadorHash::ListarDocs () const
{
  string salida = "";

  for (unordered_map<string, InfDoc>::const_iterator pos = indiceDocs.cbegin();
    pos != indiceDocs.cend(); pos++)
  {
    salida += pos->first + "\t" + pos->second.ToString() + "\n";
  }

  cout << salida; 
}

// Devuelve TRUE si el documento ha sido indexado, y muestra por pantalla el nombre y la información
bool
IndexadorHash::ListarDocs (const string& nomDoc) const
{
  unordered_map<string, InfDoc>::const_iterator doc = indiceDocs.find(nomDoc);

  if (doc != indiceDocs.cend())
  { // Si el documento ha sido indexado
    // Se muestra su información
    string salida = nomDoc + "\t" + doc->second.ToString();
    cout << salida;

    return true;
  }

  return false;
}