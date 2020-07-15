#include "indexadorHash.h"

// Almacena el id del siguiente documento a indexar
long int IndexadorHash::id = 1;

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
  //tok.~Tokenizador();
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

// Operador salida
ostream& operator<< (ostream& s, const IndexadorHash& p)
{
  s << p.ToString();

  return s;
}

string
IndexadorHash::ToString () const
{
  string salida;

  salida = "Fichero con el listado de palabras de parada: " + ficheroStopWords + "\n"
    + "Tokenizador: " + tok.ToString() + "\n"
    + "Directorio donde se almacenara el indice generado: " + directorioIndice + "\n"
    + "Stemmer utilizado: " + to_string(tipoStemmer) + "\n"
    + "Informacion de la coleccion indexada: " + informacionColeccionDocs.ToString() + "\n"
    + "Se almacenara parte del indice en disco duro: " + to_string(almacenarEnDisco) + "\n"
    + "Se almacenaran las posiciones de los terminos: " + to_string(almacenarPosTerm) + "\n";

    return salida;
}

// ### CONTRUCTORES ###

// Constructor con parámetros de inicialización
IndexadorHash::IndexadorHash (const string& fichStopWords, const string& delimitadores,
  const bool& detectComp, const bool& minuscSinAcentos, const string& dirIndice,
  const int& tStemmer, const bool& almEnDisco, const bool& almPosTerm)
{
  ficheroStopWords = fichStopWords;
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
      if (!linea.empty())
      {
        listaDocs.push_back(linea);
      }
    }
    
    f.close();

    return true;
  }

  return false;
}

int
IndexadorHash::calcularTamDocumento (const string& doc) const
{
  FILE *auxDoc;
  int tam;

  auxDoc = fopen(doc.c_str(), "r");
  fseek(auxDoc, 0L, SEEK_END);
  tam = ftell(auxDoc);
  fclose(auxDoc);

  return tam;
}

// Indexa el documento que se pasa por parámetro
void
IndexadorHash::indexarDocumento (const string& nombreDoc, const unordered_map<string, InfDoc>::iterator& itDoc)
{
  // Se recupera la tokenización, para indexar las palabras del documento
  ifstream token;
  token.open(FICHERO_TOKEN.c_str());

  // Se recupera la tokenización
  string linea;
  list<string> tokenizacion;
  if (token.is_open())
  {
    while (!token.eof())
    {
      getline(token, linea);
      if (!linea.empty())
      {
        tokenizacion.push_back(linea);
      }
    }
    token.close();
  }
  
  // Se almacena el tamaño en bytes del documento
  itDoc->second.setTamBytes(calcularTamDocumento(nombreDoc));
  // Se almacena la cantidad de palabras del documento
  itDoc->second.setNumPal(tokenizacion.size());
  // Se indexa cada palabra
  string palabra;
  int posicionPal = -1;
  // Número de palabras sin stopwords en el documento
  int auxNumPalSinParada = 0;
  // Número de palabras diferentes en el documento
  int auxNumPalDiferentes = 0;
  // Número de nuevas palabras indexadas
  int auxNuevasPal = 0;
  // Posición de la palabra en el ínidice
  pair<unordered_map<string, InformacionTermino>::iterator, bool> insercionPal;

  for (list<string>::const_iterator pos = tokenizacion.cbegin(); pos != tokenizacion.cend(); pos++)
  {
    posicionPal++;
    palabra = aplicarTratamiento(pos->data());
    if (stopWords.find(palabra) == stopWords.cend())
    { // Si la palabra no es una stopword (si lo es, se ignora)
      // Se incrementa el número de palabras que no son stopwords en el documento
      auxNumPalSinParada++;
      // Se intenta insertar la palabra
      insercionPal = indice.insert(pair<string, InformacionTermino>(palabra,InformacionTermino()));
      if (insercionPal.second)
      { // Si la palabra se ha insertado (es nueva en el índice)
        // Se incrementa el número de nuevas palabras indexadas
        auxNuevasPal++;
        // Se incrementa el número de palabras diferentes en el documento
        auxNumPalDiferentes++;
      }
      else if (!insercionPal.first->second.perteneceAdoc(itDoc->second.getIdDoc()))
      { // Si es nueva en el documento
        // Se incrementa el número de palabras diferentes en el documento
        auxNumPalDiferentes++;
      }
      // Se incrementa la frecuencia del término
      insercionPal.first->second.incrementarFrecuencia(itDoc->second.getIdDoc(), posicionPal);
    }
  }
  // Se actualizan los campos de la información del documento
  itDoc->second.incrementarNumPalSinParada(auxNumPalSinParada);
  itDoc->second.incrementarNumPalDiferentes(auxNumPalDiferentes);
  // Se actualizan los campos de la informcación de la colección de documentos
  informacionColeccionDocs.incrementarNumTotalPal(tokenizacion.size());
  informacionColeccionDocs.incrementarNumTotalPalSinParada(auxNumPalSinParada);
  informacionColeccionDocs.incrementarNumTotalPalDiferentes(auxNuevasPal);
  informacionColeccionDocs.incrementarTamBytes(itDoc->second.getTamBytes());
}

void
IndexadorHash::reindexarDocumento (const string& nombreDoc, const unordered_map<string, InfDoc>::iterator& itDoc, const off_t& tamB, const time_t& fMod)
{
  long int auxId = itDoc->second.getIdDoc();
  // Se elimina toda la información del de los índices
  // TODO
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
      long int auxNumDocs = 0;
      pair<unordered_map<string, InfDoc>::iterator, bool> insercionDoc;
      for (string doc : listaDocsIndexar)
      { // Para cada documento
        // Se intenta insertar
        insercionDoc = indiceDocs.insert(pair<string, InfDoc>(doc, InfDoc()));
        if (insercionDoc.second)
        { // Si el documento ha sido insertado (no había sido indexado)
          // Se le asigna una id
          insercionDoc.first->second.setId(id);
          // Se incrementa el número de documentos en la indexación
          auxNumDocs++;
          // Se tokeniza
          tok.Tokenizar(doc, FICHERO_TOKEN);
          // Se indexa el documento
          indexarDocumento(doc, insercionDoc.first);
          // Se incrementa la id del documento, para el siguiente
          id++;
        }
        else
        { // Si ya había sido indexado
          // Se extrae la información del fichero
          struct stat infoFichero;
          stat(doc.c_str(), &infoFichero);
          if (difftime(infoFichero.st_mtime, insercionDoc.first->second.getFechaModificacion().getFecha()) > 0)
          { // Si la fecha de modificación es más reciente (mayor)
            // Se reindexa
            reindexarDocumento(doc, insercionDoc.first, infoFichero.st_size, infoFichero.st_mtime);
          }
        }
      }
      informacionColeccionDocs.incrementarNumDocs(auxNumDocs);
      return true;
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
      return false;
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
  // Se vacían campos
  indicePregunta.clear();
  infPregunta.~InformacionPregunta();

  if (!preg.empty())
  {
    try
    {
      pregunta = preg;
      // Número de palabras que no son stopword en la pregunta
      int auxNumPalSinParada = 0;
      // Número de nuevas palabras indexadas
      int auxNuevasPal = 0;
      // Posición de la palabra en la pregunta
      int posicion = -1;

      // Se tokeniza
      list<string> tokenizacion;
      tok.Tokenizar(preg, tokenizacion);
      // Se almacena la cantidad de palabras de la pregunta
      infPregunta.incrementarNumTotalPal(tokenizacion.size());
      
      // Para cada palabra
      for (string palabra : tokenizacion)
      {
        posicion++;
        if (stopWords.find(palabra) == stopWords.cend())
        { // Si no es una stopword
          auxNumPalSinParada++;
          // Se inserta en el índice de la pregunta
          pair<unordered_map<string, InformacionTerminoPregunta>::iterator, bool> insercionPal = indicePregunta.insert(pair<string, InformacionTerminoPregunta>(palabra, InformacionTerminoPregunta()));
          if (insercionPal.second)
          { // Si ha sido insertado (nueva palabra)
            auxNuevasPal++;
          }
          // Se incrementa la frecuencia del término en la pregunta y se almacena la posición en la que aparece la palabra en la pregunta
          insercionPal.first->second.incrementarFrecuencia(posicion);
        }
      }
      // Se incrementa el número de palabras que no son stopwords en la pregunta
      infPregunta.incrementarNumTotalPalSinParada(auxNumPalSinParada);
      // Se actualiza el número de palabras diferentes en la pregunta
      infPregunta.incrementarNumTotalPalDiferentes(auxNuevasPal);

      return true;
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
  }

  cout << "ERROR: No se ha podido indexar la pregunta al estar vacía\n";
  return false;
}

bool
IndexadorHash::DevuelvePregunta (string& preg) const
{
  if (!indicePregunta.empty())
  {
    preg = pregunta;

    return true;
  }

  return false;
}

bool
IndexadorHash::DevuelvePregunta (const string& word, InformacionTerminoPregunta& inf) const
{
  string palabra = aplicarTratamiento(word);
  unordered_map<string, InformacionTerminoPregunta>::const_iterator posicion = indicePregunta.find(palabra);

  if (posicion != indicePregunta.cend())
  { // Si encuentra la palabra  
    inf = posicion->second;

    return true;
  }

  return false;
}

bool
IndexadorHash::DevuelvePregunta (InformacionPregunta& inf) const
{
  if (!indicePregunta.empty())
  {
    inf = infPregunta;

    return true;
  }

  return false;
}

void
IndexadorHash::ImprimirIndexacionPregunta ()
{
  string salida;

  salida = "Pregunta indexada: " + pregunta + "\nTerminos indexados en la pregunta: \n";
  // Se lista el contenido de "indicePregunta"
  for (unordered_map<string, InformacionTerminoPregunta>::const_iterator pos = indicePregunta.cbegin(); pos != indicePregunta.cend(); pos++)
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
    cout << salida << endl;

    return true;
  }

  return false;
}