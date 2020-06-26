#ifndef _INDEXADOR_HASH_
#define _INDEXADOR_HASH_

// #include <iostream>
// #include <unordered_map>
// #include <unordered_set>
#include "indexadorInformacion.h"
#include "tokenizador.h"
#include "stemmer.h"
#include <utility>

class IndexadorHash
{
  friend ostream& operator<< (ostream&, const IndexadorHash&);
  // -- Implementado en el enunciado (p. 6)

  public:
    /* - “fichStopWords” será el nombre del archivo que contendrá todas las
        palabras de parada (una palabra por cada línea del fichero) y se
        almacenará en el campo privado “ficheroStopWords”. Asimismo, almacenará
        todas las palabras de parada que contenga el archivo en el campo privado
        “stopWords”, el índice de palabras de parada.
       - “delimitadores” será el string que contiene todos los delimitadores
        utilizados por el tokenizador (campo privado “tok”)
       - detectComp y minuscSinAcentos serán los parámetros que se pasarán al
        tokenizador
       - “dirIndice” será el directorio del disco duro donde se almacenará el
        índice (campo privado “directorioIndice”). Si dirIndice=”” entonces se
        almacenará en el directorio donde se ejecute el programa
       - “tStemmer” inicializará la variable privada “tipoStemmer”:
          · 0 = no se aplica stemmer: se indexa el término tal y como
            aparece tokenizado
          · 1 = stemmer de Porter para español
          · 2 = stemmer de Porter para inglés
       - “almEnDisco” inicializará la variable privada “almacenarEnDisco”
       - “almPosTerm” inicializará la variable privada “almacenarPosTerm”
       - Los índices (p.ej. índice, indiceDocs e informacionColeccionDocs)
        quedarán vacíos
    */
    IndexadorHash (const string&, const string&, const bool&, const bool&,
      const string&, const int&, const bool&, const bool&);
    /* Constructor para inicializar IndexadorHash a partir de una indexación
        previamente realizada que habrá sido almacenada en “directorioIndexacion”
        mediante el método “bool GuardarIndexacion()”. Con ello toda la parte privada
        se inicializará convenientemente, igual que si se acabase de indexar la
        colección de documentos. En caso que no exista el directorio o que no
        contenga los datos de la indexación se tratará la excepción correspondiente
    */
    IndexadorHash (const string& directorioIndexacion);
    IndexadorHash (const IndexadorHash&);
    ~IndexadorHash ();
    IndexadorHash& operator= (const IndexadorHash&);

    bool Indexar(const string& ficheroDocumentos);
    bool IndexarDirectorio (const string&);
    bool GuardarIndexacion() const;
    bool RecuperarIndexacion (const string&);
    void ImprimirIndexacion() const;
    bool IndexarPregunta (const string&);
    bool DevuelvePregunta (string&) const;
    bool DevuelvePregunta (const string&, InformacionTerminoPregunta&) const;
    bool DevuelvePregunta (InformacionPregunta&) const;
    void ImprimirIndexacionPregunta ();
    void ImprimirPregunta ();
    bool Devuelve (const string&, InformacionTermino&) const;
    bool Devuelve (const string&, const string&, InfTermDoc&) const;
    bool Existe (const string&) const;
    bool Borra (const string&);
    bool BorraDoc (const string&);
    void VaciarIndiceDocs ();
    void VaciarIndicePreg();
    bool Actualiza (const string&, const InformacionTermino&);
    bool Inserta (const string&, const InformacionTermino&);
    int NumPalIndexadas () const;
    string DevolverFichPalParada () const;
    void ListarPalParada () const;
    int NumPalParada () const;
    string  DevolverDelimitadores () const;
    bool DevolverCasosEspeciales () const;
    bool DevolverPasarAminuscSinAcentos () const;
    bool DevolverAlmacenarPosTerm () const;
    string DevolverDirIndice () const;
    int DevolverTipoStemming () const;
    bool DevolverAlmEnDisco () const;
    void ListarInfColeccDocs () const;
    void ListarTerminos () const;
    bool ListarTerminos (const string&) const;
    void ListarDocs () const;
    bool ListarDocs (const string&) const;
  
  private:
    /* Este constructor se pone en la parte privada porque no se permitirá
        crear un indexador sin inicializarlo convenientemente. La inicialización
        la decidirá el alumno
    */
    IndexadorHash();
    // Índice de términos indexados accesible por el término
    unordered_map<string, InformacionTermino> indice;
    // Índice de documentos indexados accesible por el nombre del documento
    unordered_map<string, InfDoc> indiceDocs;
    // Información recogida de la colección de documentos indexada
    InfColeccionDocs informacionColeccionDocs;
    /* Pregunta indexada actualmente. Si no hay ninguna indexada, contendría
        el valor ""
    */
    string pregunta;
    /* Índice de términos indexados en una pregunta. Se almacenará en memoria
        principal
    */
    unordered_map<string, InformacionTerminoPregunta> indicePregunta;
    InformacionPregunta infPregunta;
    unordered_set<string> stopWords;
    string ficheroStopWords;
    Tokenizador tok;
    string directorioIndice;
    int tipoStemmer;
    bool almacenarEnDisco;
    bool almacenarPosTerm;

    // MÉTODOS Y FUNCIONES
    bool almacenarStopWords ();
    void stemming(string&) const;
    string aplicarTratamiento (const string&) const;
};

#endif