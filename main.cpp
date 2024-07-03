#include <iostream>
#include "ArbolBin.hpp"
#include <list>
#include <sstream>
using namespace std;

void arbolConocimiento(ArbolBin<string> arbol, list<string> listaHojas, list<string> *ramas, int longitudRama);
void hojas(ArbolBin<string> arbol, list<string> *listaHojas);

int main()
{
    ArbolBin<string> conocimiento;
    string orden, elemento, linea;
    list<string> pOrden, inOrden, listaHojas, result;
    int casos, k, corchetes = 0;
    bool preOrden = false;
    cin >> casos;
    for(int i = 1; i <= casos; i++)
    {
		//LECTURA DE ARBOL
        cin >> k;
		cin >> orden;
		for(int j = 1; j <= 2; j++)
		{
			if(orden == "INORDEN")
			{
				getline(cin, linea);
				stringstream stream(linea);
				stream >> elemento;
				getline(stream, elemento, '[');
				while(getline(stream, elemento,','))
				{
					inOrden.push_back(elemento);
					stream.get();
				}
				inOrden.pop_back();
				elemento.pop_back();
				inOrden.push_back(elemento);
			}
			else
			{
				if(orden == "PREORDEN")
				{
					preOrden = true;
					getline(cin, linea);
					stringstream stream(linea);
					stream >> elemento;
					getline(stream, elemento, '[');
					while(getline(stream, elemento,','))
					{
						pOrden.push_back(elemento);
						stream.get();
					}
					pOrden.pop_back();
					elemento.pop_back();
					pOrden.push_back(elemento);
				}
				else
				{
					preOrden = false;
					getline(cin, linea);
					stringstream stream(linea);
					stream >> elemento;
					getline(stream, elemento, '[');
					while(getline(stream, elemento,','))
					{
						pOrden.push_back(elemento);
						stream.get();
					}
					pOrden.pop_back();
					elemento.pop_back();
					pOrden.push_back(elemento);
				}
			}
			if(j == 1)
			{
				cin >> orden;
			}
		}
		
		//LLENADO DE ARBOL DEL CONOCIMIENTO
		if(preOrden)
		{
			conocimiento.leerPI(pOrden, inOrden);
		}
		else
		{
			conocimiento.leerPoI(pOrden, inOrden);
		}
		
		//LISTA DE HOJAS
		hojas(conocimiento, &listaHojas);
		
		//CREACION DE RESULTADO
		arbolConocimiento(conocimiento, listaHojas, &result, k);
		cout << "[ ";
		if(result.empty())
		{
			cout << "ninguno ";
		}
		while(!result.empty())
		{
			if(corchetes == 0)
			{
				cout << "( ";
			}
			cout << result.front() << " ";
			result.pop_front();
			corchetes++;
			if(corchetes == k + 1)
			{
				cout << ") ";
				corchetes = 0;
			}
		}
		cout << "]" << endl;
	
		
		//VACIADO Y REINICIO
		pOrden.clear();
		inOrden.clear();
		result.clear();
		listaHojas.clear();
    }
    return 0;
}

void hojas(ArbolBin<string> arbol, list<string> *listaHojas)
{
	if(arbol.esNulo())
	{
			return;
	}
	if((arbol.getHijoIzq().esNulo()) && (arbol.getHijoDer().esNulo()))
	{
		listaHojas->push_back(arbol.getInfo());
	}
	else
	{
		hojas(arbol.getHijoIzq(), listaHojas);
		hojas(arbol.getHijoDer(), listaHojas);
	}
}

void arbolConocimiento(ArbolBin<string> arbol, list<string> listaHojas, list<string> *ramas, int longitudRama)
{
	list<string> camino;
	int comp;
	while(!listaHojas.empty())
	{
		camino = arbol.camino(arbol.getInfo(), listaHojas.front());
		comp = camino.size() - 1;
		if(comp == longitudRama)
		{
			while(!camino.empty())
			{
				ramas->push_back(camino.front()); 
				camino.pop_front();
			}
		}
		camino.clear();
		listaHojas.pop_front();
	}
}
