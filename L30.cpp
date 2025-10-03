#include <iostream>
#include <vector>

using namespace std;

class Nodo {
    private:
    vector<Nodo *> hijos;
    
    public:
    Nodo() : letra(' ') { }                     // usado para la raiz
    Nodo(char chr) : letra(chr) { }
    
    char letra;
    int vecesPalabra = 0;
    int vecesPrefijo = 0;

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

    char makeLower(char letra) {
        return letra | ' ';             // prender el 3 bit más significativo para convertir a minúscula.
    }

    void agregarLetra(Nodo * nodoActual, string palabra, int indiceLetra) {
        char letra = makeLower(palabra[indiceLetra]);
        bool esUltimaLetra = !palabra[indiceLetra + 1];             // los strings terminan con un character 'NUL'=00000000.
        Nodo * nodoLetra = nodoActual->getHijo(letra);
        
        // if esa letra no existe entre los hijos del nodoActual hay que agregarla.
        if (nodoLetra == nullptr) {
            nodoLetra = new Nodo(letra);
            nodoActual->agregarHijo(nodoLetra);
        }
        
        // el nodoActual va a ser prefijo de una nueva palabra cuando esa palabra se agregue.
        // solo es correcto hacer esto si está garantizado que cada palabra es válida y se va a insertar.
        nodoActual->vecesPrefijo++;

        if (esUltimaLetra) {
            nodoLetra->vecesPalabra++;      // llevar un contador en vez de solo un booleano para contar palabras repetidas.
            nodoLetra->vecesPrefijo++;      // una palabra es prefijo de ella misma.
            return;
        }

        agregarLetra(nodoLetra, palabra, indiceLetra + 1);  // seguir recorriendo el trie con la siguiente letra.
    }

    Nodo * buscarLetra(Nodo * nodoActual, string palabra, int indiceLetra) {
        char letra = makeLower(palabra[indiceLetra]);
        bool esUltimaLetra = !palabra[indiceLetra + 1];
        Nodo * nodoLetra = nodoActual->getHijo(letra);

        // la palabra no existe
        if (nodoLetra == nullptr) {
            return nullptr;
        }

        // estamos al final de la palabra
        if (esUltimaLetra) {
            return nodoLetra;
        }

        // si no es la última letra. Continuar recorriendo la palabra
        return buscarLetra(nodoLetra, palabra, indiceLetra + 1);
    }

    public:
    // la raiz es un nodo sin caracter
    Trie() : raiz(new Nodo()) { }

    void agregarPalabra(string palabra) {
        agregarLetra(raiz, palabra, 0);
    }

    Nodo * buscarPalabra(string palabra) {
        return buscarLetra(raiz, palabra, 0);
    }
};

int main() {
    Trie trie;

    int N, Q;
    cin >> N >> Q;

    while (N--) {
        string palabra;
        cin >> palabra;

        trie.agregarPalabra(palabra);
    }

    while (Q--) {
        string query;
        cin >> query;

        Nodo * R = trie.buscarPalabra(query);

        if (R == nullptr)
            cout << "La palabra '" << query << "' no existe!\n";
        else
            cout << R->vecesPalabra << " " << R->vecesPrefijo << "\n";
    }
}