#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

class Nodo {
    private:
    map<char, Nodo *> hijos;
    
    public:
    Nodo() : letra(' ') { }
    
    char letra;

    Nodo * getHijo(char letra) {
        if (!hijos.count(letra)) return nullptr;
        return hijos[letra];
    }

    Nodo * agregarHijo(char letra) {
        Nodo * newHijo = new Nodo();
        hijos.insert(pair<char, Nodo *>(letra, newHijo));
        return newHijo;
    }
};

class Trie{
    private:
    Nodo * raiz;

    void agregarLetra(Nodo * nodoActual, string palabra, int indiceLetra) {
        char letra = palabra[indiceLetra];
        bool esUltimaLetra = !palabra[indiceLetra + 1];             // los strings terminan con un character 'NUL'=00000000.
        Nodo * nodoLetra = nodoActual->getHijo(letra);
        
        // if esa letra no existe entre los hijos del nodoActual hay que agregarla.
        if (nodoLetra == nullptr) {
            nodoLetra = nodoActual->agregarHijo(letra);
            cantNodos++;
        }
        
        if (!esUltimaLetra) {
            agregarLetra(nodoLetra, palabra, indiceLetra + 1);  // seguir recorriendo el trie con la siguiente letra.
        }
    }

    public:
    // la raiz es un nodo sin caracter
    Trie() : raiz(new Nodo()) { }

    int cantNodos = 0;

    void agregarPalabra(string palabra) {
        agregarLetra(raiz, palabra, 0);
    }
};

int main() {
    Trie trie;
    
    string nombreArchivo;
    cin >> nombreArchivo;

    ifstream diccionario(nombreArchivo);

    string palabra;
    while (getline(diccionario, palabra)) {
        trie.agregarPalabra(palabra);
    }

    diccionario.close();

    cout << trie.cantNodos << "\n";
}