#include <iostream>
#include <fstream>
#include <vector>
#include <map>

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
    map<char, int> mapaLetrasAnagrama;      // cada letra y las veces que se repite
    int lenAnagrama;                        // la cantidad total de letras que se necesitan
    vector<string> resultado;               // vector de resultados para facilitar el tema de que la ultima linea no puede tener espacios :[

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

    void buscarAnagramasAux(Nodo * nodoActual, string palabraFormada) {
        char letra = nodoActual->letra;

        /* Si la letra no es parte del anagrama
        o si la letra ya se uso todas las veces que aparecia
        then return porque esta letra no puede ser parte del anagrama */
        if (!mapaLetrasAnagrama.count(letra) || !mapaLetrasAnagrama[letra])
            return;

        mapaLetrasAnagrama[letra]--;        // marcar la letra como usada
        lenAnagrama--;

        // la palabra ya es del tamaño esperado dejar de recorrer el trie por esta ruta
        if (lenAnagrama <= 0) {
            // si este nodo forma una palabra entonces encontramos un anagrama valido
            if (nodoActual->formaPalabra)
                resultado.push_back(palabraFormada + letra);
        }
        // sino hay que seguir recorriendo el trie
        else {
            for (Nodo * hijos : nodoActual->hijos)
                buscarAnagramasAux(hijos, palabraFormada + letra);
        }

        // Hay que devolver el mapa al estado en el que estaba antes de este nodo
        mapaLetrasAnagrama[letra]++;
        lenAnagrama++;
    }

    public:
    // la raiz es un nodo sin caracter
    Trie() : raiz(new Nodo()) { }

    void agregarPalabra(string palabra) {
        agregarLetra(raiz, palabra, 0);
    }

    void buscarAnagramas(string letras) {
        // resetar de queries pasados
        mapaLetrasAnagrama.clear();
        resultado.clear();

        lenAnagrama = letras.size();
        for (char l : letras) {
            // if la letra ya existe en el mapa aumentar la cantidad de veces que aparece
            if (mapaLetrasAnagrama.count(l)) {
                mapaLetrasAnagrama[l]++;
            }
            // sino, insertar la llave
            else {
                mapaLetrasAnagrama.insert(pair<char, int>(l, 1));
            }
        }

        // buscar anagramas iniciando por los hijos de la raiz
        for (Nodo * primeraLetra : raiz->hijos)
            buscarAnagramasAux(primeraLetra, "");
        
        // imprimir resultados
        for (string anagrama : resultado) {
            cout << anagrama;
            if (resultado.back() != anagrama)
                cout << " ";
        }
        cout << "\n";
    }
};

int main() {
    Trie trie;

    //// cargar diccionario
    string nombreArchivo;
    cin >> nombreArchivo;

    ifstream diccionario(nombreArchivo);

    string palabra;
    while (getline(diccionario, palabra)) {
        trie.agregarPalabra(palabra);
    }

    diccionario.close();
    //

    //// consultas
    int Q;
    cin >> Q;
    while (Q--) {
        string letras;
        cin >> letras;
        trie.buscarAnagramas(letras);
    }
}