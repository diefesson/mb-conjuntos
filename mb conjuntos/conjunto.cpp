//Desenvolvido por Diefesson de Sousa Silva - 2019
#include "conjunto.h"
#include <stdlib.h>
#include <stdio.h>

namespace com::diefesson::conjuntos {

Conjunto* Conjunto::deSequencia(int inicio, int fim) {
    Conjunto* c = new Conjunto();
    c->tamanho = fim - inicio;
    c->tamanhoAloc = c->tamanho;
    c->numeros = (int*) realloc(c->numeros, c->tamanhoAloc * sizeof(int));

    int indice = 0;
    for(int i = inicio; i < fim; i++) {
        c->numeros[indice] = i;
        indice++;
    }
    return c;
}

Conjunto::Conjunto() {
    tamanhoAloc = 32;
    tamanho = 0;
    fatorCrescimento = 1.1;
    numeros = new int[tamanhoAloc];
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
    clone->tamanhoAloc = tamanho;
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
    tamanhoAloc *= fatorCrescimento;
    if(tamanhoAloc < 32)
        tamanhoAloc = 32;//Um tamanho minimo, previne casos de estagnação do crescimento

    numeros = (int*) realloc(numeros, tamanhoAloc * sizeof(int));
}

void Conjunto::adicionarElementoSemVerificar(int elemento) {
    if(tamanho == tamanhoAloc)
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
    embaralhado->tamanhoAloc = temp->tamanho;
    embaralhado->fatorCrescimento = temp->fatorCrescimento;

    embaralhado->numeros = (int*) realloc(embaralhado->numeros, temp->tamanho * sizeof(int));

    for(int i = 0; i < embaralhado->tamanho; i++) {
        int indice = rand() % temp->tamanho;
        embaralhado->numeros[i] = temp->obterRemoverElemento(indice);
    }

    return embaralhado;
}

void Conjunto::imprimir() {
    printf("Tamanho: %d, Tamanho alocado: %d\n", tamanho, tamanhoAloc);

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
    printf("\n\n");//espaço em branco por utilidade
}

Conjunto* Conjunto::cortar(int fim) {
    return cortar(0, fim);
}

Conjunto* Conjunto::cortar(int inicio, int fim) {
    Conjunto* cortado = new Conjunto();
    cortado->tamanho = fim - inicio;
    cortado->tamanhoAloc = cortado->tamanho;
    cortado->numeros = (int*) realloc(cortado->numeros, cortado->tamanhoAloc * sizeof(int));

    int indice = 0;
    for(int i = inicio; i < fim; i++) {
        cortado->numeros[indice++] = this->numeros[i];
    }

    return cortado;
}

ComparacaoConjunto Conjunto::comparar(Conjunto *outro) {
    if(tamanho > outro->tamanho)
        return ComparacaoConjunto::NAO_CONTIDO;//Este conjunto é maior que o outro
    bool tamanhoIgual = tamanho == outro->tamanho;

    for(int i = 0; i < tamanho; i++) {
        if(outro->procurar(numeros[i]) == -1)
            return ComparacaoConjunto::NAO_CONTIDO;//Este conjunto tem um elemento que o outro não tem
    }

    if(tamanhoIgual)
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
