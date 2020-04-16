#ifndef _INDEXADOR_INFORMACION_
#define _INDEXADOR_INFORMACION_

#include <iostream>

using namespace std;

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

  private:
    // Frecuencia total del término en la colección
    int ftc;
    /* Tabla Hash que se accederá por el id del documento, devolviendo un
        objeto de la clase InfTermDoc que contiene toda la información de
        aparición del término en el documento
    */
    unordered_map<long int, InfTermDoc> l_docs;
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

// Clase InfDoc

#endif