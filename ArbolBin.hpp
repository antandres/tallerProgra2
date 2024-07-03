#ifndef ARBOL_BIN_HEADER
#define ARBOL_BIN_HEADER

#include "NodoAB.hpp"
#include <iostream>
#include <list>
#include <queue>
#include <algorithm>

using namespace std;

template<class Elemento>
class ArbolBin
{
protected:
    NodoAB<Elemento> *NodoRaiz;
    int peso;
    static NodoAB<Elemento> *copiarNodos(NodoAB<Elemento> *ptrNodo, int &contador);
    void destruirNodos(NodoAB<Elemento> **ptrNodo);
    void find(NodoAB<Elemento> *actual ,Elemento padre,NodoAB<Elemento> *papa2,NodoAB<Elemento> *abuelo, NodoAB<Elemento> **salida, NodoAB<Elemento> **dad, NodoAB<Elemento> **granddad);
    void anadir(NodoAB<Elemento> *actual, Elemento nuevo);
    void preOrden(NodoAB<Elemento> *actual, list<Elemento> &result);
    void inOrden(NodoAB<Elemento> *actual, list<Elemento> &result);
    void postOrden(NodoAB<Elemento> *actual, list<Elemento> &result);
    void niveles(queue<NodoAB<Elemento>*> actual,list<Elemento> &result);
    void LCA(NodoAB<Elemento> *actual, Elemento origen, Elemento destino, bool *encontrado1, bool *encontrado2, bool &LCAEncontrado, Elemento &ancestro);
    void camino(NodoAB<Elemento> *actual, Elemento origen, Elemento destino, bool *encontrado1, bool *encontrado2, bool &LCAEncontrado, list<Elemento> &salida, list<Elemento> &aux);
    NodoAB<Elemento> *leerPreIn(list<Elemento> preorden, list<Elemento> inorden);
    NodoAB<Elemento> *leerPosIn(list<Elemento> postorden, list<Elemento> inorden);
    void diametro(NodoAB<Elemento> *actual, int &diametroP, int *altura, NodoAB<Elemento> **lejano, NodoAB<Elemento> **cercano);

public:
    ArbolBin();
    ArbolBin(Elemento info, ArbolBin<Elemento> HI, ArbolBin<Elemento> HD);
    ArbolBin(const ArbolBin<Elemento> &a);
    ~ArbolBin();

    void copiar(const ArbolBin<Elemento> &a);
    bool esNulo();

    Elemento getInfo();
    void setInfo(Elemento e);

    void setHijoIzq(Elemento info);
    void setHijoDer(Elemento info);
    ArbolBin<Elemento> getHijoIzq();
    ArbolBin<Elemento> getHijoDer();

    void insertarNodo(Elemento padre, Elemento nuevo);
    void eliminarSubArbol(Elemento e);
    int getPeso();
    int getDiametro();

    void leerPI(list<Elemento> preorden, list<Elemento> inorden);
    void leerPoI(list<Elemento> postorden, list<Elemento> inorden);

    Elemento LCA(Elemento origen, Elemento destino);
    list<Elemento> camino(Elemento origen, Elemento destino);
    list<Elemento> preOrden();
    list<Elemento> inOrden();
    list<Elemento> postOrden();
    list<Elemento> niveles();
};

template<class Elemento>
ArbolBin<Elemento>::ArbolBin(Elemento info, ArbolBin<Elemento> HI, ArbolBin<Elemento> HD)
{
    this->peso = 1;
    this->NodoRaiz->setInfo(info);
    if(HD != NULL){
        this->NodoRaiz->setHijoDer(HD.NodoRaiz);
    }
    if(HI != NULL){
        this->NodoRaiz->setHijoIzq(HI.NodoRaiz);
    }
    
}

template<class Elemento>
ArbolBin<Elemento>::ArbolBin(const ArbolBin<Elemento> &a)
{
    this->copiar(a);
}

template<class Elemento>
ArbolBin<Elemento>::ArbolBin()
{
    this->peso = 0;
}

template<class Elemento>
void ArbolBin<Elemento>::setHijoIzq(Elemento info){
    ++(this->peso);
    NodoRaiz->setHijoIzq(info);
}

template<class Elemento>
void ArbolBin<Elemento>::setHijoDer(Elemento info){
    ++(this->peso);
    NodoRaiz->setHijoDer(info);
}

template<class Elemento>
ArbolBin<Elemento> ArbolBin<Elemento>::getHijoIzq(){
    ArbolBin<Elemento> Hijo;
    int aux = 0;
    if(NodoRaiz != nullptr){
        Hijo.NodoRaiz = copiarNodos(NodoRaiz->getHijoIzq(), aux);
        Hijo.peso = aux;
    }else{
        Hijo.NodoRaiz = nullptr;
    }
    return Hijo;
}

template<class Elemento>
ArbolBin<Elemento> ArbolBin<Elemento>::getHijoDer(){
    ArbolBin<Elemento> Hijo;
    int aux = 0;
    if(NodoRaiz != nullptr){
        Hijo.NodoRaiz = copiarNodos(NodoRaiz->getHijoDer(),aux);
        Hijo.peso = aux;
    }else{
        Hijo.NodoRaiz = nullptr;
    }
    return Hijo;
}

template<class Elemento>
int ArbolBin<Elemento>::getPeso(){
    return this->peso;
}

template<class Elemento>
bool ArbolBin<Elemento>::esNulo(){
    return this->NodoRaiz != nullptr ? false : true;
}

template<class Elemento>
Elemento ArbolBin<Elemento>::getInfo(){
    return this->NodoRaiz->getInfo();
}

template<class Elemento>
void ArbolBin<Elemento>::setInfo(Elemento e){
    if(NodoRaiz == nullptr){
        ++(this->peso);
        NodoRaiz = new NodoAB<Elemento>;
    }
    NodoRaiz->setInfo(e);
}

template<class Elemento>
ArbolBin<Elemento>::~ArbolBin()
{
    this->peso = 0;
}

template<class Elemento>
NodoAB<Elemento> *ArbolBin<Elemento>::copiarNodos(NodoAB<Elemento> *ptrNodo, int &contador)
{
    NodoAB<Elemento> *Aux;
    if(ptrNodo == nullptr){
        return nullptr;
    }
    ++contador; 
    Aux = new NodoAB<Elemento>(ptrNodo->getInfo(), copiarNodos(ptrNodo->getHijoIzq(),contador), copiarNodos(ptrNodo->getHijoDer(),contador) );
    return Aux;
}

template<class Elemento>
void ArbolBin<Elemento>::copiar(const ArbolBin<Elemento> &a){
    int aux = 1;
    NodoRaiz = copiarNodos(a.NodoRaiz,aux);
    this->peso = a.peso;
}

template<class Elemento>
void ArbolBin<Elemento>::insertarNodo(Elemento padre, Elemento nuevo){
    NodoAB<Elemento> *aux, *papa, *abuelo;
    papa = abuelo = nullptr;
    find(NodoRaiz,padre,nullptr,nullptr, &aux, &papa, &abuelo);
    anadir(aux,nuevo);
    /*if(papa != nullptr && abuelo != nullptr){
        cout << abuelo->getInfo() << endl;
        cout << papa->getInfo() << endl;
        cout << padre << "\n\n";
    }*/
}

template<class Elemento>
void ArbolBin<Elemento>::find(NodoAB<Elemento> *actual ,Elemento padre,NodoAB<Elemento> *papa2,NodoAB<Elemento> *abuelo, NodoAB<Elemento> **salida, NodoAB<Elemento> **dad, NodoAB<Elemento> **granddad){
    if(actual == nullptr){
        return;
    }
    if(actual->getInfo() == padre){
        *granddad = abuelo;
        *dad = papa2;
        *salida = actual;
        return;
    }
    this->find(actual->getHijoIzq(),padre,actual,papa2,salida,dad,granddad);
    this->find(actual->getHijoDer(),padre,actual,papa2,salida,dad,granddad);
}

template<class Elemento>
void ArbolBin<Elemento>::anadir(NodoAB<Elemento> *actual, Elemento nuevo){

    NodoAB<Elemento> *aux = new NodoAB<Elemento>;
    aux->setInfo(nuevo);
    if(actual->getHijoIzq() != nullptr && actual->getHijoDer() != nullptr){
        cout << "\n Ya tiene dos hijos \n";
        return;
    }
    ++(this->peso);
    if(actual->getHijoIzq() == nullptr){
        actual->setPointerHI(aux);
        return;
    }
    actual->setPointerHD(aux);
}

template<class Elemento>
void ArbolBin<Elemento>::destruirNodos(NodoAB<Elemento> **ptrNodo){
    delete *ptrNodo;
}

template<class Elemento>
void ArbolBin<Elemento>::eliminarSubArbol(Elemento e){
    NodoAB<Elemento> *aux, *padre, *abuelo;
    this->find(NodoRaiz,e,nullptr,nullptr, &aux, &padre, &abuelo);
    if(padre->getHijoDer() == aux){
        padre->setPointerHD(nullptr);
    }
    if(padre->getHijoIzq() == aux){
        padre->setPointerHI(nullptr);
    }
    this->destruirNodos(&aux);
}

template<class Elemento>
list<Elemento> ArbolBin<Elemento>::preOrden(){
    list<Elemento> result;
    this->preOrden(NodoRaiz, result);
    typename list<Elemento>::iterator it;
    for(it = result.begin(); it != result.end();++it){
        cout << *it << " "; 
    }
    return result;
}

template<class Elemento>
list<Elemento> ArbolBin<Elemento>::inOrden(){
    list<Elemento> result;
    this->inOrden(NodoRaiz, result);

    typename list<Elemento>::iterator it;
    for(it = result.begin(); it != result.end();++it){
        cout << *it << " "; 
    }
    return result;
}

template<class Elemento>
list<Elemento> ArbolBin<Elemento>::postOrden(){
    list<Elemento> result;
    this->postOrden(NodoRaiz, result);

    typename list<Elemento>::iterator it;
    for(it = result.begin(); it != result.end();++it){
        cout << *it << " "; 
    }
    return result;
}

template<class Elemento>
list<Elemento> ArbolBin<Elemento>::niveles(){
    list<Elemento> result;
    queue<NodoAB<Elemento>*> aux;
    aux.push(NodoRaiz);
    this->niveles(aux,result);
    typename list<Elemento>::iterator it;
    for(it = result.begin(); it != result.end();++it){
        cout << *it << " "; 
    }
    return result;
}

template<class Elemento>
void ArbolBin<Elemento>::preOrden(NodoAB<Elemento> *actual, list<Elemento> &result){
    if(actual == nullptr){
        return;
    }
    result.push_back(actual->getInfo());
    preOrden(actual->getHijoIzq(),result);
    preOrden(actual->getHijoDer(),result);
}

template<class Elemento>
void ArbolBin<Elemento>::inOrden(NodoAB<Elemento> *actual, list<Elemento> &result){
    if(actual == nullptr){
        return;
    }
    inOrden(actual->getHijoIzq(),result);
    result.push_back(actual->getInfo());
    inOrden(actual->getHijoDer(),result);
}

template<class Elemento>
void ArbolBin<Elemento>::postOrden(NodoAB<Elemento> *actual, list<Elemento> &result){
    if(actual == nullptr){
        return;
    }
    postOrden(actual->getHijoIzq(),result);
    postOrden(actual->getHijoDer(),result);
    result.push_back(actual->getInfo());
}

template <typename Elemento>
void ArbolBin<Elemento>::niveles(queue<NodoAB<Elemento>*> actual,list<Elemento> &result){

    queue<NodoAB<Elemento>*> sigNivel;
    while (!actual.empty()) {
        if (actual.front()->getHijoIzq() != nullptr){
            sigNivel.push(actual.front()->getHijoIzq());
        }
        if (actual.front()->getHijoDer() != nullptr){
            sigNivel.push(actual.front()->getHijoDer());
        }
        result.push_back(actual.front()->getInfo());
        actual.pop();
    }
    if(!sigNivel.empty()){
        this->niveles(sigNivel,result);
    }
}

template<class Elemento>
void ArbolBin<Elemento>::LCA(NodoAB<Elemento> *actual, Elemento origen, Elemento destino, bool *encontrado1, bool *encontrado2, bool &LCAEncontrado, Elemento &ancestro){
    bool e1HI, e2HI, e1HD, e2HD;
    if(actual == nullptr || LCAEncontrado){
        return;
    }
    if(actual->getHijoIzq() == nullptr && actual->getHijoDer() == nullptr){
        *encontrado1 = actual->getInfo() == origen;
        *encontrado2 = actual->getInfo() == destino;
        return;
    }
    e1HI = e2HI = e1HD = e2HD = false;

    this->LCA(actual->getHijoIzq(),origen,destino, &e1HI, &e2HI,LCAEncontrado,ancestro);
    this->LCA(actual->getHijoDer(),origen,destino, &e1HD, &e2HD,LCAEncontrado,ancestro);

    if(!LCAEncontrado){
        *encontrado1 = e1HI || e1HD || actual->getInfo() == origen;
        *encontrado2 = e2HI || e2HD || actual->getInfo() == destino;
        LCAEncontrado = *encontrado1 && *encontrado2;

        if(LCAEncontrado){
            ancestro = actual->getInfo();
        }
    }
}

template<class Elemento>
Elemento ArbolBin<Elemento>::LCA(Elemento origen, Elemento destino){
    bool e1,e2, LCAEncontrado;
    Elemento ancestro;

    e1 = e2 = LCAEncontrado = false;
    this->LCA(NodoRaiz,origen,destino,&e1,&e2,LCAEncontrado,ancestro);
    return ancestro;
}

template<class Elemento>
void ArbolBin<Elemento>::camino(NodoAB<Elemento> *actual, Elemento origen, Elemento destino, bool *encontrado1, bool *encontrado2, bool &LCAEncontrado, list<Elemento> &salida, list<Elemento> &aux){
    bool e1HI, e2HI, e1HD, e2HD;
    if(actual == nullptr || LCAEncontrado){
        return;
    }
    e1HI = e2HI = e1HD = e2HD = false;

    this->camino(actual->getHijoIzq(),origen,destino, &e1HI, &e2HI,LCAEncontrado,salida,aux);
    this->camino(actual->getHijoDer(),origen,destino, &e1HD, &e2HD,LCAEncontrado,salida,aux);

    if(!LCAEncontrado){
        *encontrado1 = e1HI || e1HD || actual->getInfo() == origen;
        *encontrado2 = e2HI || e2HD || actual->getInfo() == destino;
        if(*encontrado1 && !*encontrado2){
            salida.push_back(actual->getInfo());
        }
        if(*encontrado2 && !*encontrado1){
            aux.push_front(actual->getInfo());
        }
        LCAEncontrado = *encontrado1 && *encontrado2;

        if(LCAEncontrado){
            salida.push_back(actual->getInfo());
            salida.splice(salida.end(),aux);
            for (auto v: salida)
            {
               // cout << v << endl;
            }
            
        }
    }
}

template<class Elemento>
list<Elemento> ArbolBin<Elemento>::camino(Elemento origen, Elemento destino){
    bool e1,e2, LCAEncontrado;
    list<Elemento> camino,aux;

    e1 = e2 = LCAEncontrado = false;
    this->camino(NodoRaiz,origen,destino,&e1,&e2,LCAEncontrado,camino,aux);
    typename list<Elemento>::iterator it;
    for(it = aux.begin(); it != aux.end();++it){
        //cout << *it << " "; 
    }
    return camino;
}

template <typename Elemento>
NodoAB<Elemento> * ArbolBin<Elemento>::leerPreIn(list<Elemento> preorden, list<Elemento> inorden){
    
    NodoAB<Elemento> *r;
    list<Elemento> preIzq, preDer, inIzq, inDer;

    if(!preorden.empty()){
        r = new (NodoAB<Elemento>);
        r->setInfo(preorden.front());
        preorden.pop_front();
        while(inorden.front() != r->getInfo()){
            inIzq.push_back(inorden.front());
            preIzq.push_back(preorden.front());

            inorden.pop_front();
            preorden.pop_front();
        }
        inorden.pop_front();

        while(!inorden.empty()){
            preDer.push_back(preorden.front());
            inDer.push_back(inorden.front());

            preorden.pop_front();
            inorden.pop_front();
        }

        r->setPointerHI(leerPreIn(preIzq, inIzq));
        r->setPointerHD(leerPreIn(preDer, inDer));
        return r;

    }else{
        return nullptr;
    }

}

template <typename Elemento>
NodoAB<Elemento> * ArbolBin<Elemento>::leerPosIn(list<Elemento> postorden, list<Elemento> inorden){
    
    NodoAB<Elemento> *r;
    list<Elemento> postIzq, postDer, inIzq, inDer;

    if(!postorden.empty()){
        r = new (NodoAB<Elemento>);
        r->setInfo(postorden.back());
        postorden.pop_back();

        while(inorden.front() != r->getInfo()){
            inIzq.push_back(inorden.front());
            postIzq.push_back(postorden.front());

            inorden.pop_front();
            postorden.pop_front();
        }
        inorden.pop_front();

        while(!inorden.empty()){
            postDer.push_back(postorden.front());
            inDer.push_back(inorden.front());

            postorden.pop_front();
            inorden.pop_front();
        }

        r->setPointerHI(leerPosIn(postIzq, inIzq));
        r->setPointerHD(leerPosIn(postDer, inDer));

        return r;

    }else{
        return nullptr;
    }

}

template <class Elemento>
void ArbolBin<Elemento>::leerPI(list<Elemento> preorden, list<Elemento> inorden){
    NodoRaiz = this->leerPreIn(preorden,inorden);
}

template <class Elemento>
void ArbolBin<Elemento>::leerPoI(list<Elemento> postorden, list<Elemento> inorden){
    NodoRaiz = this->leerPosIn(postorden,inorden);
}

template <class Elemento>
void ArbolBin<Elemento>::diametro(NodoAB<Elemento> *actual, int &diametroP, int *altura, NodoAB<Elemento> **lejano, NodoAB<Elemento> **cercano){
    int alturaHD, alturaHI;
    NodoAB<Elemento> *aux,*lejanoHI,*lejanoHD,*cercanoHI,*cercanoHD;

    if(actual == nullptr){
        *altura = 0;
        return;
    }

    diametro(actual->getHijoIzq(),diametroP,&alturaHI,&lejanoHI,&cercanoHI);
    diametro(actual->getHijoDer(),diametroP,&alturaHD,&lejanoHD,&cercanoHD);

    int max_diameter = alturaHD + alturaHI + 1;
    if(max_diameter == 1){
        *lejano = actual;
        *cercano = actual;
    }

    diametroP = max(diametroP,max_diameter);
    if(alturaHI > alturaHD){
        *altura = alturaHI + 1;
        *lejano = lejanoHI;
        *cercano = lejanoHD;
    }else{
        *altura = alturaHD + 1;
        *lejano = lejanoHD;
        *cercano = lejanoHI;
    }
}

template <class Elemento>
int ArbolBin<Elemento>::getDiametro(){
    int res = 0,altura = 0;
    NodoAB<Elemento> *cercano,*lejano;
    this->diametro(this->NodoRaiz,res,&altura,&lejano,&cercano);
    return res;
}

#endif
