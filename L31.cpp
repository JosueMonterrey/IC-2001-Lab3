#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Nodo {
    private:
    vector<Nodo *> hijos;
    
    public:
    Nodo() : letra(' ') { }                     // usado para la raiz
    Nodo(char chr) : letra(chr) { }
    
    char letra;

    Nodo * getHijo(char l) {
        for (Nodo * h : hijos) {
            if (h->letra == l) return h;
        }
        return nullptr;
    }

    void agregarHijo(Nodo * nuevoHijo) {
        hijos.push_back(nuevoHijo);
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
            nodoLetra = new Nodo(letra);
            nodoActual->agregarHijo(nodoLetra);
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