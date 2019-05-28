//Desenvolvido por Diefesson de Sousa Silva - 2019
#include "conjunto.h"
#include <stdlib.h>
#include <stdio.h>

namespace com::diefesson::conjuntos {

Conjunto* Conjunto::deSequencia(int inicio, int fim) {
    Conjunto* c = new Conjunto();
    c->tamanho = fim - inicio;
    c->tamanho_aloc = c->tamanho;
    c->numeros = (int*) realloc(c->numeros, c->tamanho_aloc * sizeof(int));

    int indice = 0;
    for(int i = inicio; i < fim; i++) {
        c->numeros[indice] = i;
        indice++;
    }
    return c;
}

Conjunto::Conjunto() {
    tamanho_aloc = 32;
    tamanho = 0;
    fatorCrescimento = 1.1;
    numeros = new int[tamanho_aloc];
}

//Conjunto::Conjunto(Conjunto &original) {
//    tamanho_aloc = original.tamanho;
//    tamanho = original.tamanho;
//    fator_de_crescimento = original.fator_de_crescimento;
//    numeros = new int[tamanho_aloc];
//    for(int i = 0; i < tamanho; i++) {
//        numeros[i] = original.numeros[i];
//    }
//}

//O operador de copia é implicito demais, usarei uma aproximação semelhante á do Java
Conjunto* Conjunto::clone() {
    Conjunto *clone = new Conjunto();
    clone->tamanho = tamanho;
    clone->tamanho_aloc = tamanho;
    clone->numeros = (int*) realloc(clone->numeros, sizeof(int) * tamanho);
    for(int i = 0; i < tamanho; i++) {
        clone->numeros[i] = numeros[i];
    }
    return clone;
}

Conjunto::~Conjunto() {
    delete numeros;
}

void Conjunto::crescer() {
    tamanho_aloc *= fatorCrescimento;

    numeros = (int*) realloc(numeros, tamanho_aloc * sizeof(int));
}

void Conjunto::adicionarElementoSemVerificar(int elemento) {
    if(tamanho == tamanho_aloc)
        crescer();

    numeros[tamanho++] = elemento;
}

bool Conjunto::adicionarElemento(int elemento) {
    if(procurar(elemento) != -1)
        return false;

    adicionarElementoSemVerificar(elemento);
    return true;
}

bool Conjunto::removerElemento(int elemento) {
    int indice = procurar(elemento);
    if(indice < 0)
        return false;

    numeros[indice] = numeros[--tamanho];
    return true;
}

int Conjunto::procurar(int elemento) {
    for(int i = 0; i < tamanho; i++) {
        if(numeros[i] == elemento)
            return i;
    }
    return -1;
}

int Conjunto::obter(int indice) {
    return numeros[indice];
}

int Conjunto::obterRemoverElemento(int indice) {
    int elemento = numeros[indice];
    numeros[indice] = numeros[--tamanho];
    return elemento;
}

int Conjunto::obterTamanho() {
    return tamanho;
}

void Conjunto::ordenar() {
    for(int i = tamanho - 1; i > 0; i--) {
        for(int j = 0; j < i; j++) {
            if(numeros[j] > numeros[j + 1]) {
                int temp = numeros[j];
                numeros[j] = numeros[j + 1];
                numeros[j + 1] = temp;
            }
        }
    }
}

Conjunto* Conjunto::gerarEmbaralhado() {
    //Conjunto temp = *this;
    Conjunto *temp = this->clone();
    Conjunto* embaralhado = new Conjunto();

    embaralhado->tamanho = temp->tamanho;
    embaralhado->tamanho_aloc = temp->tamanho;
    embaralhado->fatorCrescimento = temp->fatorCrescimento;

    embaralhado->numeros = (int*) realloc(embaralhado->numeros, temp->tamanho * sizeof(int));

    for(int i = 0; i < embaralhado->tamanho; i++) {
        int indice = rand() % temp->tamanho;
        embaralhado->numeros[i] = temp->obterRemoverElemento(indice);
    }

    return embaralhado;
}

void Conjunto::imprimir() {
    printf("Tamanho: %d, Tamanho alocado: %d\n", tamanho, tamanho_aloc);

    if(tamanho == 0) {
        printf("O conjunto está vazio\n");
        return;
    }

    printf("Elementos:");
    for(int i = 0; i < tamanho; i++) {
        if(i % 10 == 0)
            printf("\n");

        printf("%d ", numeros[i]);
    }
    printf("\n");
}

Conjunto* Conjunto::cortar(int fim) {
    return cortar(0, fim);
}

Conjunto* Conjunto::cortar(int inicio, int fim) {
    Conjunto* cortado = new Conjunto();
    cortado->tamanho = fim - inicio;
    cortado->tamanho_aloc = cortado->tamanho;
    cortado->numeros = (int*) realloc(cortado->numeros, cortado->tamanho_aloc * sizeof(int));

    int indice = 0;
    for(int i = inicio; i < fim; i++) {
        cortado->numeros[indice++] = this->numeros[i];
    }

    return cortado;
}

ComparacaoConjunto Conjunto::comparar(Conjunto *outro) {
    if(tamanho > outro->tamanho)
        return ComparacaoConjunto::NAO_CONTIDO;//Este conjunto é maior que o outro
    bool tamanho_igual = tamanho == outro->tamanho;

    for(int i = 0; i < tamanho; i++) {
        if(outro->procurar(numeros[i]) == -1)
            return ComparacaoConjunto::NAO_CONTIDO;//Este conjunto tem um elemento que o outro não tem
    }

    if(tamanho_igual)
        return ComparacaoConjunto::IGUAL;
    else
        return ComparacaoConjunto::SUBCONJUNTO;
}

Conjunto* Conjunto::unir(Conjunto *outro) {
    Conjunto* uniao = new Conjunto();

    for(int i = 0; i < tamanho; i++) {
        uniao->adicionarElemento(numeros[i]);
    }

    for(int i = 0; i < outro->tamanho; i++) {
        uniao->adicionarElemento(outro->numeros[i]);
    }

    return uniao;
}

Conjunto* Conjunto::intersectar(Conjunto *outro) {
    Conjunto* interseccao = new Conjunto();

    for(int i = 0; i < tamanho; i++) {
        int elemento = numeros[i];
        if(outro->procurar(elemento) != -1)
            interseccao->adicionarElementoSemVerificar(elemento);
    }

    return interseccao;
}

Conjunto* Conjunto::subtrair(Conjunto *outro) {
    Conjunto* subtraido = new Conjunto();

    for(int i = 0; i < tamanho; i++) {
        int elemento = numeros[i];
        if(outro->procurar(elemento) == -1)
            subtraido->adicionarElementoSemVerificar(elemento);
    }

    return subtraido;
}

}
