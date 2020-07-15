#ifndef _INDEXADOR_INFORMACION_
#define _INDEXADOR_INFORMACION_

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <ctime>


using namespace std;

class InfTermDoc;

class Fecha
{ 
  public:
    Fecha ();
    Fecha (const Fecha&);
    ~Fecha ();
    Fecha& operator= (const Fecha&);
    bool operator< (const Fecha&) const;
    void setFecha (const time_t&);
    time_t getFecha() const;

  private:
    time_t fecha;
};

class InfTermDoc
{
  friend ostream& operator<< (ostream&, const InfTermDoc&);
  // -- Implementado en el enunciado (p. 4)

  public:
    InfTermDoc (const InfTermDoc&);
    InfTermDoc ();    // Inicializa ft = 0;
    ~InfTermDoc ();   // Pone ft = 0;
    InfTermDoc& operator= (const InfTermDoc&);
    // MÉTODOS Y FUNCIONES
    string ToString () const;
    void incrementarFrecuencia (const int&);

  private:
    // Frecuencia del término en el documento
    int ft;
    /* Solo se almacenará esta información si el campo privado del indexador
        almacenar PosTerm == true
       Lista de números de palabra en los que aparece el término en el
        documento. Los números de palabra comenzarán desde cero (la primera
        palabra del documento). Se numerarán las palabras de parada. Estará
        ordenada de menor a mayor posición.
    */
    list<int> posTerm;
};

// Clase en la que se implementará la generación de información para la indexación
class InformacionTermino
{
  friend ostream& operator<< (ostream&, const InformacionTermino&);
  // -- Implementado en el enunciado (p. 3)

  public:
    InformacionTermino (const InformacionTermino&);
    InformacionTermino ();    // Inicializa ftc = 0
    ~InformacionTermino ();   // Pone ftc = 0 y vacia l_docs
    InformacionTermino& operator= (const InformacionTermino&);
    // MÉTODOS Y FUNCIONES
    string ToString () const;
    InfTermDoc getInfTermDoc (const long int&) const;
    bool perteneceAdoc(const long int&) const;
    // Busca el idDoc en "l_docs" y lo borra si aparece
    void eliminarDoc (const long int&);
    void incrementarFrecuencia (const long int&, const int&);

  private:
    // Frecuencia total del término en la colección
    int ftc;
    /* Tabla Hash que se accederá por el id del documento, devolviendo un
        objeto de la clase InfTermDoc que contiene toda la información de
        aparición del término en el documento
    */
    unordered_map<long int, InfTermDoc> l_docs;
};

class InfDoc
{
  friend ostream& operator<< (ostream&, const InfDoc&);
  // -- Implementado en el enunciado (p. 4)

  public:
    InfDoc (const InfDoc&);
    InfDoc ();
    InfDoc (long int&);
    ~InfDoc ();
    InfDoc& operator= (const InfDoc&);
    // MÉTODOS Y FUNCIONES
    string ToString () const;
    long int getIdDoc () const;
    Fecha getFechaModificacion () const;
    void setId (const long int&);
    void setNumPal (const int&);
    void setTamBytes (const int&);
    void setFechaMod (const time_t&);
    void incrementarNumPalSinParada ();
    void incrementarNumPalDiferentes ();

  private:
    /* Identificador del documento. El primer documento indexado en la
        colección será el identificador 1
    */
    long int idDoc;
    // Nº total de palabras del documento
    int numPal;
    // Nº total de palabras sin stop-words del documento
    int numPalSinParada;
    /* Nº total de palabras diferentes que no sean stop-words (sin acumular
        la frecuencia de cada una de ellas)
    */
    int numPalDiferentes;
    // Tamaño en bytes del documento
    int tamBytes;
    /* Atributo correspondiente a la fecha y hora de modificación del
        documento. El tipo "Fecha/hora" lo eligirá/implementará el alumno
    */
    Fecha fechaModificacion;
};

class InfColeccionDocs
{
  friend ostream& operator<< (ostream&, InfColeccionDocs&);
  // -- Implementado en el enunciado (p. 5)

  public:
    InfColeccionDocs (const InfColeccionDocs&);
    InfColeccionDocs ();
    ~InfColeccionDocs ();
    InfColeccionDocs& operator= (const InfColeccionDocs&);
    // MÉTODOS Y FUNCIONES
    string ToString () const;
    long int getNumDocs () const;
    void incrementarNumDocs ();

  private:
    // Nº total de documentos en la colección
    long int numDocs;
    // Nº total de palabras en la colección
    long int  numTotalPal;
    // Nº total de palabras sin stop-words en la colección
    long int numTotalPalSinParada;
    /* Nº total de palabras diferentes en la colección que no sean
        stop-words (sin acumular la frecuencia de cada una de ellas)
    */
    long int numTotalPalDiferentes;
    // Tamaño total en bytes de la colección
    long int tamBytes;
};

class InformacionTerminoPregunta
{
  friend ostream& operator<< (ostream&, const InformacionTerminoPregunta&);
  // -- Implementado en el enunciado (p. 5)

  public:
    InformacionTerminoPregunta (const InformacionTerminoPregunta&);
    InformacionTerminoPregunta ();
    ~InformacionTerminoPregunta ();
    InformacionTerminoPregunta& operator= (const InformacionTerminoPregunta&);
    // MÉTODOS Y FUNCIONES
    string ToString () const;

  private:
    // Frecuencia total del término en la pregunta
    int ft;
    /* Solo se almacenará esta información si el campo privado del indexador
        almacenarPostTerm == true
      Lista de números de palabra en los que aparece el término en la
        pregunta. Los números de palabra comenzarán desde cero (la primera
        palabra de la pregunta). Se numerarán las palabras de parada. Estará
        ordenada de menor a mayor posición.
    */
    list<int> posTerm;
};

class InformacionPregunta
{
  friend ostream& operator<< (ostream&, const InformacionPregunta&);
  // -- Implementado en el enunciado (p. 6)

  public:
    InformacionPregunta (const InformacionPregunta&);
    InformacionPregunta ();
    ~InformacionPregunta ();
    InformacionPregunta& operator= (const InformacionPregunta&);
    string ToString() const;

  private:
    // Nº total de palabras en la pregunta
    long int numTotalPal;
    // Nº total de palabras sin stop-words en la pregunta
    long int numTotalPalSinParada;
    /* Nº total de palabras diferentes en la pregunta que no sean stop-words
        (sin acumular la frecuencia de cada una de ellas)
    */
   long int numTotalPalDiferentes;
};

#endif