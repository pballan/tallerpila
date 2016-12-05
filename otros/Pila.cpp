typedef unsigned long Nat;

#include <string>
#include <ostream>
#include <iostream>
using namespace std;
#include "Pila.h"

Pila::Pila()
{
	this->tam = 0;
	this->prim = NULL;
}
Pila::~Pila()
{
  while (!esVacia())
  {
    desapilar();
  } 	
}
void Pila::vacia()
{
	this->tam = 0;
	this->prim = NULL;	
}

void Pila::apilar(ElemPila& elem)
{
	Nodo* nuevo = new Nodo;
	
	nuevo->sig = this->prim;
	nuevo->elem = elem;

	this->prim = nuevo;
	this->tam++;
}

bool Pila::esVacia()
{
	bool res = (this->tam == 0 && this->prim == NULL);
	return res;
}

ElemPila& Pila::tope()
{
	return this->prim->elem;
}

void Pila::desapilar()
{	
	if (this->tam >	0)
	{
		Nodo* aux;
		aux = this->prim;
		this->prim = aux->sig;
		this->tam--;
		delete aux;
	}
}

Nat Pila::tamanio() const 
{
	return this->tam;
}
 
Pila& Pila::operator=(const Pila & aCopiar)
{
	Pila nuevo;
	Nodo* recorrer;
	
	while (!esVacia())
	{
		desapilar();
	} 

	this->prim = aCopiar.prim;
	this->tam = aCopiar.tam;

	recorrer = aCopiar.prim;

	while (recorrer != NULL)
	{
		this->apilar(recorrer->elem);
		recorrer = recorrer->sig;
	}
}
void Pila::mostrar(ostream& os) const
{
	Nodo* aux;
	os << '[';
	/*while (aux!=NULL)
	{
		os << this->tope(); 
		if (aux->sig != NULL)
			os << ',';
		aux = aux->sig;
	}*/
	os << ']';
}