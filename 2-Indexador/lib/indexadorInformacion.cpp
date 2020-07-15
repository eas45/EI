#include "indexadorInformacion.h"

/************************
 *  InformacionTermino  *
 ************************/

// ### FORMA CANONICA ###

// Constructor de copia
InformacionTermino::InformacionTermino (const InformacionTermino& infoTermino)
{
  ftc = infoTermino.ftc;
  l_docs = infoTermino.l_docs;
}

// Constructor por defecto
InformacionTermino::InformacionTermino ()
{
  ftc = 0;
}

// Destructor
InformacionTermino::~InformacionTermino ()
{
  ftc = 0;
  l_docs.clear();
}

// Operador asignacion
InformacionTermino&
InformacionTermino::operator= (const InformacionTermino& infoTermino)
{
  if (this != &infoTermino)
  { // Si no es el mismo objeto
    // Se destruye
    this->~InformacionTermino();
    // Se copia
    ftc = infoTermino.ftc;
    l_docs = infoTermino.l_docs;
  }

  return (*this);
}

// ### OPERADOR SALIDA ###

ostream& operator<< (ostream& s, const InformacionTermino& p)
{
  s << p.ToString();
  
  return s;
}

// ### MÉTODOS Y FUNCIONES ###

// Lista la información del objeto
string
InformacionTermino::ToString () const
{
  string salida;

  salida = "Frecuencia total: " + to_string(ftc) + "\t" + "fd: " + to_string(l_docs.size());
  // A continuación se mostrarán todos los elementos de "l_docs"
  for (auto pos = l_docs.begin(); pos != l_docs.end(); pos++)
  { // Se coloca en cada una de las posiciones de la tabla hash
    salida += "\tId.Doc: " + to_string(pos->first) + "\t" + pos->second.ToString();
  }

  return salida;
}

// Devuelve la información del término en el documento correspondiente
InfTermDoc
InformacionTermino::getInfTermDoc (const long int& idDoc) const
{
  return l_docs.at(idDoc);
}

void
InformacionTermino::eliminarDoc (const long int& idDoc)
{
  unsigned int nEliminados = l_docs.erase(idDoc);

  ftc -= nEliminados;
}

bool
InformacionTermino::perteneceAdoc(const long int& id) const
{
  return (l_docs.find(id) != l_docs.cend());
}

// Inserta la pareja de id de un documento con la información del término en ese documento
void
InformacionTermino::incrementarFrecuencia (const long int& id, const int& posicion)
{
  // Aumenta la frecuencia del término en la colección
  ftc++;
  // Inserta el documento en el que aparece el término
  unordered_map<long int, InfTermDoc>::iterator insercionDoc = l_docs.insert(pair<long int, InfTermDoc>(id, InfTermDoc())).first;
  // Incrementa la frecuencia del término en el documento e inserta la posición en la que se encuentra
  insercionDoc->second.incrementarFrecuencia(posicion);
}

/****************
 *  InfTermDoc  *
 ****************/

// ### FORMA CANÓNICA ###

// Constructor de copia
InfTermDoc::InfTermDoc (const InfTermDoc& infoTerminoDoc)
{
  ft = infoTerminoDoc.ft;
  posTerm = infoTerminoDoc.posTerm;
}

// Constructor por defecto
InfTermDoc::InfTermDoc ()
{
  ft = 0;
}

// Destructor
InfTermDoc::~InfTermDoc ()
{
  ft = 0;
  posTerm.clear();
}

// Operador asignación
InfTermDoc&
InfTermDoc::operator= (const InfTermDoc& infoTerminoDoc)
{
  if (this != &infoTerminoDoc)
  { // Si no es el mismo objeto
    // Se destruye
    this->~InfTermDoc();
    // Se copia
    ft = infoTerminoDoc.ft;
    posTerm = infoTerminoDoc.posTerm;
  }
}

// ### OPERADOR SALIDA ###

ostream& operator<< (ostream& s, const InfTermDoc& p)
{
  s << p.ToString();

 return s;
}

// ### MÉTODOS Y FUNCIONES ###

string
InfTermDoc::ToString () const
{
  string salida;

  salida = "ft: " + to_string(ft);
  // A continuación se mostrarán todos los elementos de posTerm
  for (list<int>::const_iterator elem = posTerm.begin(); elem != posTerm.end(); elem++)
  {
    salida += "\t" + to_string(*elem);
  }

  return salida;
}

// Aumenta la frecuencia del término en un documento y se añade la posición en la que se encuentra
void
InfTermDoc::incrementarFrecuencia (const int& pos)
{
  // Aumenta la frecuencia del término
  ft++;
  // Inserta la posición en la que se ha encontrado
  posTerm.push_back(pos);
}

/************
 *  InfDoc  *
 ************/

// ### FORMA CANÓNICA ###

// Constructor de copia
InfDoc::InfDoc (const InfDoc& infoDocumento)
{
  idDoc = infoDocumento.idDoc;
  numPal = infoDocumento.numPal;
  numPalSinParada = infoDocumento.numPalSinParada;
  numPalDiferentes = infoDocumento.numPalSinParada;
  tamBytes = infoDocumento.tamBytes;
  fechaModificacion = infoDocumento.fechaModificacion;
}

// Constructor por defecto
InfDoc::InfDoc ()
{
  idDoc = 0;
  numPal = 0;
  numPalSinParada = 0;
  numPalDiferentes = 0;
  tamBytes = 0;
  // La fecha de modificación se inicializa por defecto
}

// Destructor
InfDoc::~InfDoc ()
{
  idDoc = 0;
  numPal = 0;
  numPalSinParada = 0;
  numPalDiferentes = 0;
  tamBytes = 0;
  fechaModificacion.~Fecha();
}

// Operador asignación
InfDoc&
InfDoc::operator= (const InfDoc& infoDocumento)
{
  if (this != &infoDocumento)
  { // Si no es el mismo objeto
    // Se destruye
    this->~InfDoc();
    // Se copia
    idDoc = infoDocumento.idDoc;
    numPal = infoDocumento.numPal;
    numPalSinParada = infoDocumento.numPalSinParada;
    numPalDiferentes = infoDocumento.numPalSinParada;
    tamBytes = infoDocumento.tamBytes;
    fechaModificacion = infoDocumento.fechaModificacion;
  }

  return *this;
}

// Operador salida
ostream& operator<< (ostream& s, const InfDoc& p)
{
  s << p.ToString();

  return s;
}

// ### CONSTRUCTORES ###

// Inicializa el documento con una id
InfDoc::InfDoc (long int& id)
{
  idDoc = id;
  numPal = 0;
  numPalSinParada = 0;
  numPalDiferentes = 0;
  tamBytes = 0;
}

// ### MÉTODOS Y FUNCIONES ###

string
InfDoc::ToString () const
{
  string salida;

  salida = "idDoc: " + to_string(idDoc) + "\tnumPal: " + to_string(numPal) +
    "\tnumPalSinParada: " + to_string(numPalSinParada) + "\tnumPalDiferentes: " +
    to_string(numPalDiferentes) + "\ttamBytes: " + to_string(tamBytes);

  return salida;
}

long int
InfDoc::getIdDoc () const
{
  return idDoc;
}

Fecha
InfDoc::getFechaModificacion () const
{
  return fechaModificacion;
}

int
InfDoc::getTamBytes () const
{
  return tamBytes;
}

void
InfDoc::setId (const long int& id)
{
  idDoc = id;
}

void
InfDoc::setNumPal (const int& nPals)
{
  numPal = nPals;
}

void
InfDoc::setTamBytes (const int& tam)
{
  tamBytes = tam;
}

void
InfDoc::setFechaMod (const time_t& f)
{
  fechaModificacion.setFecha(f);
}

void
InfDoc::incrementarNumPalSinParada (const int& num = 1)
{
  numPalSinParada += num;
}

void
InfDoc::incrementarNumPalDiferentes (const int& num = 1)
{
  numPalDiferentes += num;
}

/**********************
 *  InfColeccionDocs  *
 **********************/

// ### FORMA CANÓNICA ###

// Cosntructor de copia
InfColeccionDocs::InfColeccionDocs (const InfColeccionDocs& coleccionDocs)
{
  numDocs = coleccionDocs.numDocs;
  numTotalPal = coleccionDocs.numTotalPal;
  numTotalPalSinParada = coleccionDocs.numTotalPalSinParada;
  numTotalPalDiferentes = coleccionDocs.numTotalPalDiferentes;
  tamBytes = coleccionDocs.tamBytes;
}

// Constructor por defecto
InfColeccionDocs::InfColeccionDocs ()
{
  numDocs = 0;
  numTotalPal = 0;
  numTotalPalSinParada = 0;
  numTotalPalDiferentes = 0;
  tamBytes = 0;
}

// Destructor
InfColeccionDocs::~InfColeccionDocs ()
{
  numDocs = 0;
  numTotalPal = 0;
  numTotalPalSinParada = 0;
  numTotalPalDiferentes = 0;
  tamBytes = 0;
}

// Operador asignación
InfColeccionDocs&
InfColeccionDocs::operator= (const InfColeccionDocs& coleccionDocs)
{
  if (this != &coleccionDocs)
  { // Si no es el mismo objeto
    // Se destruye
    this->~InfColeccionDocs();
    // Se copia
    numDocs = coleccionDocs.numDocs;
    numTotalPal = coleccionDocs.numTotalPal;
    numTotalPalSinParada = coleccionDocs.numTotalPalSinParada;
    numTotalPalDiferentes = coleccionDocs.numTotalPalDiferentes;
    tamBytes = coleccionDocs.tamBytes;
  }

  return *this;
}

// Operador salida
ostream& operator<< (ostream& s, const InfColeccionDocs& p)
{
  s << p.ToString();

  return s;
}

string
InfColeccionDocs::ToString () const
{
  string salida;

  salida = "numDocs: " + to_string(numDocs) + "\tnumTotalPal: " + to_string(numTotalPal) +
    "\tnumTotalPalSinParada: " + to_string(numTotalPalSinParada) +
    "\tnumTotalPalDiferentes: " + to_string(numTotalPalDiferentes) +
    "\ttamBytes: " + to_string(tamBytes);

  return salida;
}

long int
InfColeccionDocs::getNumDocs () const
{
  return numDocs;
}

void
InfColeccionDocs::incrementarNumDocs (const long int& num = 1)
{
  numDocs += num;
}

void
InfColeccionDocs::incrementarNumTotalPal (const long int& num = 1)
{
  numTotalPal += num;
}

void
InfColeccionDocs::incrementarNumTotalPalSinParada (const long int& num = 1)
{
  numTotalPalSinParada += num;
}

void
InfColeccionDocs::incrementarNumTotalPalDiferentes (const long int& num = 1)
{
  numTotalPalDiferentes += num;
}

void
InfColeccionDocs::incrementarTamBytes (const long int& num)
{
  tamBytes += num;
}

/********************************
 *  InformacionTerminoPregunta  *
 ********************************/

// ### FORMA CANÓNICA ###

// Constructor de copia
InformacionTerminoPregunta::InformacionTerminoPregunta (const InformacionTerminoPregunta& infoTerminoPreg)
{
  ft = infoTerminoPreg.ft;
  posTerm = infoTerminoPreg.posTerm;
}

// Constructor por defecto
InformacionTerminoPregunta::InformacionTerminoPregunta ()
{
  ft = 0;
}

// Destructor
InformacionTerminoPregunta::~InformacionTerminoPregunta ()
{
  ft = 0;
  posTerm.clear();
}

// Operador asignación
InformacionTerminoPregunta&
InformacionTerminoPregunta::operator= (const InformacionTerminoPregunta& infoTerminoPreg)
{
  if (this != &infoTerminoPreg)
  { // Si no es el mismo objeto
    // Se destruye
    this->~InformacionTerminoPregunta();
    // Se copia
    ft = infoTerminoPreg.ft;
    posTerm = infoTerminoPreg.posTerm;
  }

  return *this;
}

// Operador salida
ostream& operator<< (ostream& s, const InformacionTerminoPregunta& p)
{
  s << p.ToString();

  return s;
}

// Lista la información del objeto
string
InformacionTerminoPregunta::ToString () const
{
  string salida;

  salida = "ft: " + to_string(ft);
  // A continuación se mostrarán todos los elementos de "posTerm"
  for (list<int>::const_iterator pos = posTerm.begin(); pos != posTerm.end(); pos++)
  {
    salida += "\t" + to_string(*pos);
  }

  return salida;
}

void
InformacionTerminoPregunta::incrementarFrecuencia (const int& posicion)
{
  // Se incrementa la frecuencia
  ft++;
  // Se inserta la posición en la que se ha encontrado la palabra
  posTerm.push_back(posicion);
}

/************************
 *  InformacionPregunta *
 ************************/

// ### FORMA CANÓNICA ###

// Constructor de copia
InformacionPregunta::InformacionPregunta (const InformacionPregunta& infoPregunta)
{
  numTotalPal = infoPregunta.numTotalPal;
  numTotalPalSinParada = infoPregunta.numTotalPalSinParada;
  numTotalPalDiferentes = infoPregunta.numTotalPalDiferentes;
}

// Constructor por defecto
InformacionPregunta::InformacionPregunta ()
{
  numTotalPal = 0;
  numTotalPalSinParada = 0;
  numTotalPalDiferentes = 0;
}

// Destructor
InformacionPregunta::~InformacionPregunta ()
{
  numTotalPal = 0;
  numTotalPalSinParada = 0;
  numTotalPalDiferentes = 0;
}

// Operador asignación
InformacionPregunta&
InformacionPregunta::operator= (const InformacionPregunta& infoPregunta)
{
  if (this != &infoPregunta)
  { // Si no es el mismo objeto
    // Se destruye
    this->~InformacionPregunta();
    // Se copia
    numTotalPal = infoPregunta.numTotalPal;
    numTotalPalSinParada = infoPregunta.numTotalPalSinParada;
    numTotalPalDiferentes = infoPregunta.numTotalPalDiferentes;
  }

  return *this;
}

// Operador salida
ostream& operator<< (ostream& s, const InformacionPregunta& p)
{
  s << p.ToString();

  return s;
}

string
InformacionPregunta::ToString () const
{
  string salida;

  salida = "numTotalPal: " + to_string(numTotalPal) + "\tnumTotalPalSinParada: " +
    to_string(numTotalPalSinParada) + "\tnumTotalPalDiferentes: " + to_string(numTotalPalDiferentes);

  return salida;
}

void
InformacionPregunta::incrementarNumTotalPal (const int& num = 1)
{
  numTotalPal += num;
}

void
InformacionPregunta::incrementarNumTotalPalSinParada (const int& num = 1)
{
  numTotalPalSinParada += num;
}

void
InformacionPregunta::incrementarNumTotalPalDiferentes (const int& num = 1)
{
  numTotalPalDiferentes += num;
}

/**********
 *  Fecha *
 **********/

// ### FORMA CANÓNICA ###

// Constructor con parámetros
Fecha::Fecha ()
{
  // Recupera la fecha actual del sistema
  time(&fecha);
}

// Constructor de copia
Fecha::Fecha (const Fecha& f)
{
  fecha = f.fecha;
}

// Destructor
Fecha::~Fecha ()
{
  // Deja la fecha en 00:00 horas, 1 de enero de 2000 UTC
  struct tm fInicio = {0};

  fInicio.tm_hour = 0;
  fInicio.tm_min = 0;
  fInicio.tm_sec = 0;
  fInicio.tm_year = 100;
  fInicio.tm_mon = 0;
  fInicio.tm_mday = 1;

  fecha = mktime(&fInicio);
}

// Operador asignación
Fecha&
Fecha::operator= (const Fecha& f)
{
  if (this != &f)
  {
    fecha = f.fecha;
  }

  return *this;
}

// Compara si la fecha pasada es menor
bool
Fecha::operator< (const Fecha& f) const
{
  // La fecha es menor si f.fecha-fecha > 0
  return (difftime(f.fecha, fecha) > 0);
}

void
Fecha::setFecha (const time_t& f)
{
  fecha = f;
}

time_t
Fecha::getFecha () const
{
  return fecha;
}