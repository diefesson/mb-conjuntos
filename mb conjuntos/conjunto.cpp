//Desenvolvido por Diefesson de Sousa Silva - 2019
#include "conjunto.h"
#include <stdlib.h>
#include <stdio.h>

namespace com::diefesson::conjuntos {

Conjunto* Conjunto::de_sequencia(int inicio, int fim) {
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
    fator_de_crescimento = 1.1;
    numeros = new int[tamanho_aloc];
}

Conjunto::Conjunto(Conjunto &original) {
    tamanho_aloc = original.tamanho;
    tamanho = original.tamanho;
    fator_de_crescimento = original.fator_de_crescimento;
    numeros = new int[tamanho_aloc];
    for(int i = 0; i < tamanho; i++) {
        numeros[i] = original.numeros[i];
    }
}

Conjunto::~Conjunto() {
    delete numeros;
}

void Conjunto::crescer() {
    tamanho_aloc *= fator_de_crescimento;

    numeros = (int*) realloc(numeros, tamanho_aloc * sizeof(int));
}

void Conjunto::adicionar_ele_sem_ver(int elemento) {
    if(tamanho == tamanho_aloc) crescer();

    numeros[tamanho++] = elemento;
}

bool Conjunto::adicionar_elemento(int elemento) {
    if(procurar_elemento(elemento) != -1) return false;

    adicionar_ele_sem_ver(elemento);
    return true;
}

bool Conjunto::remover_elemento(int elemento) {
    int indice = procurar_elemento(elemento);
    if(indice < 0) return false;

    numeros[indice] = numeros[--tamanho];
    return true;
}

int Conjunto::procurar_elemento(int elemento) {
    for(int i = 0; i < tamanho; i++) {
        if(numeros[i] == elemento) return i;
    }
    return -1;
}

int Conjunto::obter_elemento(int indice) {
    return numeros[indice];
}

int Conjunto::obter_remover_elemento(int indice) {
    int elemento = numeros[indice];
    numeros[indice] = numeros[--tamanho];
    return elemento;
}

int Conjunto::obter_tamanho() {
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

Conjunto* Conjunto::gerar_embaralhado() {
    Conjunto temp = *this;
    Conjunto* embaralhado = new Conjunto();

    embaralhado->tamanho = temp.tamanho;
    embaralhado->tamanho_aloc = temp.tamanho_aloc;
    embaralhado->fator_de_crescimento = temp.fator_de_crescimento;

    embaralhado->numeros = (int*) realloc(embaralhado->numeros, temp.tamanho * sizeof(int));

    for(int i = 0; i < embaralhado->tamanho; i++) {
        int indice = rand() % temp.tamanho;
        embaralhado->numeros[i] = temp.obter_remover_elemento(indice);
    }

    return embaralhado;
}

void Conjunto::imprimir() {
    printf("Tamanho: %d, Tamanho alocado: %d\n", tamanho, tamanho_aloc);

    if(tamanho == 0) {
        printf("O conjunto está vazio\n");
    } else {
        printf("Elementos:\n");
        int coluna = 0;
        for(int i = 0; i < tamanho; i++) {
            printf("%d = %d   ", i, numeros[i]);
            coluna++;
            if(coluna == 6){//Imprime os elementos em 6 colunas
                coluna = 0;
                printf("\n");
            }
        }
        if(coluna != 0) printf("\n");//Se a última coluna estiver completa(já terminar com espaço), então não imprime mais um \n
    }
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
    if(tamanho > outro->tamanho) return ComparacaoConjunto::NAO_CONTIDO;//Este conjunto é maior que o outro
    bool tamanho_igual = tamanho == outro->tamanho;

    for(int i = 0; i < tamanho; i++) {
        if(outro->procurar_elemento(numeros[i]) == -1) return ComparacaoConjunto::NAO_CONTIDO;//Este conjunto tem um elemento que o outro não tem
    }

    if(tamanho_igual) return ComparacaoConjunto::IGUAL;
    else return ComparacaoConjunto::SUBCONJUNTO;
}

Conjunto* Conjunto::unir(Conjunto *outro) {
    Conjunto* uniao = new Conjunto();

    for(int i = 0; i < tamanho; i++) {
        uniao->adicionar_elemento(numeros[i]);
    }

    for(int i = 0; i < outro->tamanho; i++) {
        uniao->adicionar_elemento(outro->numeros[i]);
    }

    return uniao;
}

Conjunto* Conjunto::intersectar(Conjunto *outro) {
    Conjunto* interseccao = new Conjunto();

    for(int i = 0; i < tamanho; i++) {
        int elemento = numeros[i];
        if(outro->procurar_elemento(elemento) != -1) interseccao->adicionar_ele_sem_ver(elemento);
    }

    return interseccao;
}

Conjunto* Conjunto::subtrair(Conjunto *outro) {
    Conjunto* subtraido = new Conjunto();

    for(int i = 0; i < tamanho; i++) {
        int elemento = numeros[i];
        if(outro->procurar_elemento(elemento) == -1) subtraido->adicionar_ele_sem_ver(elemento);
    }

    return subtraido;
}

}
