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

ostream& operator<< (ostream& s, const InformacionTermino& p) {
  s << "Frecuencia total: " << p.ftc << "\tdf: " << p.l_docs.size();
  // TODO
  // A continuacion se mostraran todos los elementos de p.l_docs:
  // s << "\tId.Doc: " << idDoc << "\t" << InfTermDoc;
}

// Lista la información del objeto
string
InformacionTermino::ToString () const
{
  string salida;

  salida = "Frecuencia total: " + to_string(ftc) + "\t" + to_string(l_docs.size());
  // A continuación se mostrarán todos los elementos de "l_docs"
  for (auto pos = l_docs.begin(); pos != l_docs.end(); pos++)
  { // Se coloca en cada una de las posiciones de la tabla hash
    salida += "\tId.Doc: " + to_string(pos->first) + "\t" + pos->second.ToString();
  }

  return salida;
}

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

  //return nEliminados;
}

/****************
 *  InfTermDoc  *
 ****************/

// ### FORMA CANÓNICA ###

// Constructor de copia
InfTermDoc::InfTermDoc (const InfTermDoc& infoTerminoDoc)
{
  ft = infoTerminoDoc.ft;
  // TODO
  // Solo almacenará esta información si el campo privado del indexador almacenarPosTerm == true;
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
    // TODO
    // Solo almacenará esta información si el campo privado del indexador almacenarPosTerm == true;
    posTerm = infoTerminoDoc.posTerm;
  }
}

// ### OPERADOR SALIDA ###

ostream& operator<< (ostream& s, const InfTermDoc& p)
{
  s << "ft: " << p.ft;
  // TODO
  /* A continuación se mostrarían todos los elementos de p.posTerm ("posicion TAB posicion TAB ... posicion, es decir,
      nunca finalizará en un TAB"):
    s << "\t" << posicion;
  */
 return s;
}

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
// TODO

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

bool
InformacionTermino::perteneceAdoc(const long int& id) const
{
  return (l_docs.find(id) != l_docs.cend());
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
// TODO

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

/********************************
 *  InformacionTerminoPregunta  *
 ********************************/

// ### FORMA CANÓNICA ###

// Constructor de copia
InformacionTerminoPregunta::InformacionTerminoPregunta (const InformacionTerminoPregunta& infoTerminoPreg)
{
  ft = infoTerminoPreg.ft;
  // TODO
  // Copia posTerm
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
    // TODO
    // Solo almacenará esta información si el campo privado del indexador almacenarPosTerm == true;
    posTerm = infoTerminoPreg.posTerm;
  }

  return *this;
}

// Operador salida
// TODO
ostream& operator<< (ostream& s, const InformacionTerminoPregunta& p)
{
  s << p.ToString();
}

// Lista la información del objeto
string
InformacionTerminoPregunta::ToString () const
{
  string salida = "";

  salida += "ft: " + ft;
  // A continuación se mostrarán todos los elementos de "posTerm"
  for (list<int>::const_iterator pos = posTerm.begin(); pos != posTerm.end(); pos++)
  {
    salida += "\t" + *pos;
  }

  return salida;
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
// TODO

string
InformacionPregunta::ToString () const
{
  string salida;

  salida = "numTotalPal: " + to_string(numTotalPal) + "\tnumTotalPalSinParada: " +
    to_string(numTotalPalSinParada) + "\tnumTotalPalDiferentes: " + to_string(numTotalPalDiferentes);

  return salida;
}