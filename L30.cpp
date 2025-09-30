#include <iostream>
#include <vector>

using namespace std;

class Nodo {
    private:
    char letra;
    int vecesRepetido;
    vector<Nodo *> hijos;

    public:
    Nodo(char l) : letra(l) {}

    char getLetra() { return letra; }

    int getVecesRepetido() { return vecesRepetido; }
    void incVecesRepetido() { vecesRepetido++; }

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

int main() {

}