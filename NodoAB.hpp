#ifndef NODO_ARBOL_BIN_HEADER
#define NODO_ARBOL_BIN_HEADER

using namespace std;

template <class Elemento>
class NodoAB
{
    private:
        Elemento e;
        NodoAB<Elemento> *hijoIzq, *hijoDer;

    public:
        NodoAB();
        NodoAB(Elemento e, NodoAB<Elemento> *izq = nullptr,NodoAB<Elemento> *der = nullptr);
        ~NodoAB();

        Elemento getInfo();
        void setInfo(Elemento e);

        NodoAB *getHijoIzq();
        NodoAB *getHijoDer();

        void setPointerHI(NodoAB<Elemento> *hijo);
        void setPointerHD(NodoAB<Elemento> *hijo);

        void setHijoIzq(Elemento e);
        void setHijoDer(Elemento e);
};

template <class Elemento>
NodoAB<Elemento>::NodoAB(){
    this->hijoIzq = nullptr;
    this->hijoDer = nullptr;
}

template <class Elemento>
NodoAB<Elemento>::NodoAB(Elemento valor, NodoAB<Elemento> *izq,NodoAB<Elemento> *der){
    this->e = valor;
    this->hijoIzq = izq;
    this->hijoDer = der;
}

template <class Elemento>
NodoAB<Elemento>::~NodoAB(){
    delete this->hijoIzq;
    delete this->hijoDer;
}

template <class Elemento>
Elemento NodoAB<Elemento>::getInfo(){
    return this->e;
}

template <class Elemento>
void NodoAB<Elemento>::setInfo(Elemento valor){
    this->e = valor;
}

template <class Elemento>
NodoAB<Elemento>* NodoAB<Elemento>::getHijoIzq(){
    return this->hijoIzq;
}

template <class Elemento>
NodoAB<Elemento> *NodoAB<Elemento>::getHijoDer(){
    return this->hijoDer;
}

template <class Elemento>
void NodoAB<Elemento>::setHijoIzq(Elemento e){
    if(this->hijoIzq == nullptr){
        NodoAB<Elemento> *aux = new NodoAB<Elemento>;
        this->hijoIzq = aux;
    }
    this->hijoIzq->setInfo(e);
}

template <class Elemento>
void NodoAB<Elemento>::setHijoDer(Elemento e){
    if(this->hijoDer == nullptr){
        NodoAB<Elemento> *aux = new NodoAB<Elemento>;
        this->hijoDer = aux;
    }
    this->hijoDer->setInfo(e);
}

template <class Elemento>
void NodoAB<Elemento>::setPointerHI(NodoAB<Elemento> *hijo){
    this->hijoIzq = hijo;
}

template <class Elemento>
void NodoAB<Elemento>::setPointerHD(NodoAB<Elemento> *hijo){
    this->hijoDer = hijo;
}

#endif