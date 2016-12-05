#include <ostream>
#include "TiposBasicos.h"
using namespace std;
/**
 * Esta clase representa una Pila de objetos de tipo genérico T.
 *
 * ATENCION: Las únicas cosas que se pueden asumir sobre 'T' es que tiene
 * definido el constructor por copia, el operador '<< (std::ostream&)' y
 * el operador de comparación '=='.
 */
template <typename T>
class Pila
{
  public:

    // Constructor sin parámetros. Crea una pila vacía.
    Pila();

    // Constructor por copia. Crea una nueva instancia de una Pila
    // que debe ser igual a la pasada por parámetro.
    Pila(const Pila& otra);

    // Destructor. Limpia toda la memoria dinámica que aún esté en uso.
    ~Pila();

    // El constructor puede ser visto como un generador
    void apilar(const T& elem);

    // En este caso, a diferencia del TAD, desapilar cambia el estado interno de mi instancia de clase
    // PRE: la pila no es vacía
    void desapilar();

  // Observadores básicos

    // Devuelve true si la Pila es vacía, false en caso contrario.
    bool esVacia() const;

    // Devuelve una referencia al elemento en el tope de la Pila.
    // PRE: La Pila no está vacía.
    T& tope();

    // Devuelve una referencia al elemento en el tope de la Pila.
    // PRE: La Pila no está vacía.
    const T& tope() const;

  // Otras operaciones

    // Devuelve la cantidad de elementos que hay en la pila.
    aed2::Nat tamanio() const;

    // Modifica esta instancia de Pila de tal manera que termine
    // siendo una copia de la Pila pasada por parámetro.
    // Devuelve una referencia a si misma.
    Pila& operator = (const Pila& otra);

    // IMPLEMENTACION OPCIONAL (no va a ser evaluada).
    // Compara dos instancias de Pila. Devuelve true si son iguales
    // y false en caso contrario.
    bool operator == (const Pila& otra) const;

    /**
     * Muestra la lista en un ostream.
     * formato de salida:
     *   [e_0, e_1, e_2, ...]
     * donde e_i es el resultado del "mostrar" el elemento i.
     * PRE: está definido el operador '<<' para los elementos de tipo 'T'.
     *
     * Nota: imprimir sobre os, es decir: os << "[" << ...
     *
     * ATENCION:
     *
     *  - entre elemento y elemento de la pila debe haber una coma y un espacio.
     *
     *  - El primer elemento que se muestra representa al tope de la pila, es
     *    decir, los elementos se muestran en orden inverso al que fueron apilados.
     */
    template<typename S>
    friend std::ostream& operator << (std::ostream& os, const Pila<S>& pila);

  private:

    struct Nodo {
      T elem;
      Nodo* sig;

      Nodo(const T& e):
      elem(e), sig(NULL)
      {
      }
    };

    Nodo* tope_;
    aed2::Nat tamanio_;
};

template <typename T>
Pila<T>::Pila()
{
  this->tope_ = NULL;
  this->tamanio_ = 0;
}

template <typename T>
Pila<T>::Pila(const Pila& otra)
{
  this->tope_ = NULL;
  this->tamanio_ = 0;

  T arregloT[int(otra.tamanio_)];
  Nodo* aux = otra.tope_;
  int largo = (int) otra.tamanio_;
  int i = 0;

  while (i < largo){
    arregloT[i] = aux->elem;
    aux = aux->sig;
    i++;
  }

  i = 0;
  while(i < largo){
    this->apilar(arregloT[largo -i -1]);
    i++;
  }



}

template <typename T>
Pila<T>::~Pila()
{
  while (!esVacia())
  {
    this->desapilar();
  }
}

template <typename T>
void Pila<T>::apilar(const T& elem)
{
  if (this->tope_ == NULL){
    tope_ = new Nodo(elem);

  }else{
     Nodo* nuevo = new Nodo(elem);
     nuevo->sig = this->tope_;
     this->tope_ = nuevo;
  }
  this->tamanio_++;
}

template <typename T>
void Pila<T>::desapilar()
{

   if (this->tamanio_ >   0)
   {
      Nodo* aux;
      aux = this->tope_;
      this->tope_ = aux->sig;
      this->tamanio_--;
      delete aux;
   }
}

template <typename T>
bool Pila<T>::esVacia() const
{
   return (this->tamanio_ == 0);
}

template <typename T>
T& Pila<T>::tope()
{
  return this->tope_->elem;
}

template <typename T>
const T& Pila<T>::tope() const
{
  return this->tope_->elem;
}

template <typename T>
aed2::Nat Pila<T>::tamanio() const
{
  return this->tamanio_;
}

template <typename T>
Pila<T>& Pila<T>::operator = (const Pila& otra)
{

  Pila<T> nuevo;
  Nodo* recorrer;


  while (!esVacia())
  {
    desapilar();
  }

  recorrer = otra.tope_;
  T listaPila[otra.tamanio_];
  int n = 0;
  while (n != otra.tamanio_)
  {

    listaPila[n] = recorrer->elem;
    recorrer = recorrer->sig;
    n++;
  }

  while (n > 0)
  {
    this->apilar(listaPila[n-1]);
    n--;
  }

  return *this;
}

template <typename T>
std::ostream& operator << (std::ostream& os, const Pila<T>& pila)
{
  os << '[';
  typename Pila<T>::Nodo* recorrer;
  recorrer = pila.tope_;
  while (recorrer != NULL)
  {
    os << recorrer->elem;
    if (recorrer->sig != NULL)
      os << ", ";
    recorrer = recorrer->sig;
  }
  os << ']';
}
