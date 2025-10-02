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

int dividirVector(vector<Nodo *> &vec, int low, int high) {
    Nodo * pivote = vec[high];

    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (vec[j]->sizeSubarbol <= pivote->sizeSubarbol) {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    swap(vec[i + 1], vec[high]);
    return (i + 1);
}

void quickSort(vector<Nodo *> &vec, int low, int high) {
    if (low < high) {
        int pi = dividirVector(vec, low, high);

        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}

class Trie{
    private:
    Nodo * raiz;

    int countPalabras = 0;

    // Ocupamos imprimir primero la cantidad de operaciones y despues listar dichas operaciones.
    // Entonces vamos haciendo las operaciones, guardandolas aqui, las contamos.
    // Y al final, se imprime primero la cantidad y despues esta variable.
    string printData;

    int agregarLetra(Nodo * nodoActual, string palabra, int indiceLetra) {
        char letra = palabra[indiceLetra];
        bool esUltimaLetra = !palabra[indiceLetra + 1];             // los strings terminan con un character 'NUL'=00000000.
        Nodo * nodoLetra = nodoActual->getHijo(letra);
        int cantNuevosNodos = 0;

        // if esa letra no existe entre los hijos del nodoActual hay que agregarla.
        if (nodoLetra == nullptr) {
            nodoLetra = new Nodo(letra, esUltimaLetra);
            nodoActual->agregarHijo(nodoLetra);
            cantNuevosNodos++;
        }

        if (esUltimaLetra) {
            countPalabras++;
        }
        else {
            cantNuevosNodos += agregarLetra(nodoLetra, palabra, indiceLetra + 1);  // seguir recorriendo el trie con la siguiente letra.
        }

        nodoActual->sizeSubarbol += cantNuevosNodos;
        return cantNuevosNodos;
    }

    int imprimirTrieAux(Nodo * nodoActual) {
        int cuentaOps = 0;

        // es necesario recorrer el arbol empezando por las rutas con menos nodos para minimizar operaciones de borrado.
        quickSort(nodoActual->hijos, 0, nodoActual->hijos.size() - 1);

        for (Nodo * nodoLetra : nodoActual->hijos) {
            // imprimir letra
            printData += nodoLetra->letra;
            printData += "\n";
            cuentaOps++;

            // indicar si termina la palabra
            if (nodoLetra->formaPalabra) {
                printData += "P\n";
                cuentaOps++;
                countPalabras--;        // lleva la cuenta de palabras que nos faltan para imprimir todas.
            }

            // imprimir recursivamente todas las letras hijas
            cuentaOps += imprimirTrieAux(nodoLetra);

            if (countPalabras == 0) break;  // si ya escribimos todas las palabras terminar el ciclo sin borrar la ultima palabra (no es necesario)

            printData += "-\n";
            cuentaOps++;
        }

        return cuentaOps;
    }

    public:
    // la raiz es un nodo sin caracter
    Trie() : raiz(new Nodo()) { }

    void agregarPalabra(string palabra) {
        agregarLetra(raiz, palabra, 0);
    }

    void imprimirTrie() {
        int pasos = imprimirTrieAux(raiz);
        cout << pasos << "\n" << printData;
    }
};

int main() {
    Trie trie;

    int N;
    cin >> N;

    while (N--) {
        string palabra;
        cin >> palabra;
        trie.agregarPalabra(palabra);
    }

    trie.imprimirTrie();
}