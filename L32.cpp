#include <iostream>
#include <vector>

using namespace std;

class Nodo {
    public:
    Nodo() : letra(' ') { }                     // usado para la raiz
    Nodo(char chr, bool esUltimaLetra) : letra(chr), formaPalabra(esUltimaLetra) { }
    
    char letra;
    bool formaPalabra = false;
    int sizeSubarbol = 1;

    vector<Nodo *> hijos;

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
            nodoLetra = new Nodo(letra, esUltimaLetra);
            nodoActual->agregarHijo(nodoLetra);
        }

        if (!esUltimaLetra) {
            agregarLetra(nodoLetra, palabra, indiceLetra + 1);  // seguir recorriendo el trie con la siguiente letra.
        }
    }

    public:
    // la raiz es un nodo sin caracter
    Trie() : raiz(new Nodo()) { }

    void agregarPalabra(string palabra) {
        agregarLetra(raiz, palabra, 0);
    }
};

int main() {
    Trie trie;
}