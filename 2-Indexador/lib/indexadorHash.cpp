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