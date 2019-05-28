//Desenvolvido por Diefesson de Sousa Silva - 2019
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>//Para iniciar o sistema rand com uma seed baseada no tempo

#include "main.h"
#include "conjunto.h"//Minha classe para operações de conjunto

using com::diefesson::conjuntos::Conjunto;
using com::diefesson::conjuntos::ComparacaoConjunto;

Conjunto *universo = nullptr;
Conjunto *a = nullptr;
Conjunto *b = nullptr;

int main() {
    iniciar();

    //Gera conjunto universo
    universo = Conjunto::deSequencia(-50, 51);

    gerarConjuntoA();
    printf("Conjunto A\n");
    a->ordenar();
    a->imprimir();
    gerarConjuntoB();

    while(true) {
        int opcao;
        exibirMenu();
        printf("Opção = ");
        //scanf("%d", &opcao);
        opcao = lerNumero();
        switch(opcao) {
        case 1:
            execVerPertinencia();
            break;
        case 2:
            execMaiorMenor();
            break;
        case 3:
            execIgualdade();
            break;
        case 4:
            execSubconjunto();
            break;
        case 5:
            execUniao();
            break;
        case 6:
            execInterseccao();
            break;
        case 7:
            execDiferenca();
            break;
        case 8:
            execComplemento();
            break;
        case 0:
            printf("Bye bye...\n");
            return 0;
        case 91:
            printf("Conjunto A\n");
            a->ordenar();
            a->imprimir();
            printf("Conjunto B\n");
            b->ordenar();
            b->imprimir();
            break;
        case 92:
            gerarConjuntoA();
            printf("Conjunto A\n");
            a->ordenar();
            a->imprimir();
            break;
        case 93:
            gerarConjuntoB();
            break;
        default:
            printf("A opção %d é inválida, tente outra\n", opcao);
        }
    }
}

void iniciar(){
    setlocale(LC_ALL, "Portuguese");
    srand(time(nullptr));//Inicia o algoritmo de números aleatórios com o tempo atual
}

void exibirMenu() {
    printf(
        "*** MENU - Desenvolvido por Diefesson de Sousa Silva - 2019 V28.05.2019 *******\n"
        "1 - Verificar pertinência de um elemento\n"
        "2 - Exibir elementos de maior e menor valor de A e B\n"
        "3 - Verificar igualdade dos conjuntos\n"
        "4 - Verificar se A é subconjunto de B ou se B é subconjunto de A\n"
        "5 - Gerar conjunto união de A e B\n"
        "6 - Gerar conjunto intersecção entre A e B\n"
        "7 - Gerar conjunto de diferença A - B e B - A\n"
        "8 - Gerar conjunto de complento de A e B\n"
        "0 - Sair\n"
        "*** OPÇÕES EXTRA **************************************************************\n"
        "91 - Exibir conjuntos A e B\n"
        "92 - Gerar conjunto A novamente\n"
        "93 - Gerar conjunto B novamente\n"
        "*******************************************************************************\n"
    );
}

void gerarConjuntoA() {
    if(a != nullptr) delete a;

    int tamanho_a;
    while(true) {
        printf("Digite o tamanho do conjunto A(0 <= t <= 101)\n");
        //scanf("%d", &tamanho_a);
        tamanho_a = lerNumero();
        if(0 <= tamanho_a && tamanho_a <= 101) break;
        printf("O tamanho deve obedecer a regra 0 <= t <= 101\n");
    }
    Conjunto* temp = universo->gerarEmbaralhado();
    a = temp->cortar(tamanho_a);
    delete temp;
}

void gerarConjuntoB() {
    if(b != nullptr) delete b;

    b = lerConjunto("B");
}

int lerElemento(char* nome) {
    int elemento;
    while(true) {
        if(nome != nullptr) printf("%s = ", nome);//Opcionalmente exibe o nome do elemento lido
        //scanf("%d", &elemento);
        elemento = lerNumero();
        if(-50 <= elemento && elemento <= 50) break;
        printf("O valor deve pertencer ao conjunto universo[-50, 50]\n");
    }
    return elemento;
}

int lerNumero(){
    int numero;

    while(scanf("%d", &numero) != 1){//Caso a leitura falhe, ele executa o loop que trata de limpar a entrada e tentar novamente
        printf("O valor deve ser um número inteiro válido\n");
        int c;
        while((c = getchar()) != EOF && c != '\n')//Ignora a entrada até que encontre um caracter de linha ou chegue no fim do terminal
            continue;
        if(c == EOF)
            exit(0);//Sai do programa caso o fluxo de entrada do terminal seja fechado
    }

    return numero;
}

Conjunto* lerConjunto(char* nome) {
    Conjunto *conjunto = new Conjunto();
    int tamanho;

    if(nome != nullptr) printf("Digite o tamanho do conjunto %s(0 < t <= 101)\n", nome);
    else printf("Digite o tamanho do conjunto(0 <= t <= 101)\n");
    while(true) {
        tamanho = lerNumero();
        if(0 <= tamanho && tamanho <= 101) break;
        printf("O tamanho deve obedecer a regra 0 <= t <= 101\n");
    }

    printf("Agora digite os valores do elementos\n");
    for(int i = 0; i < tamanho;) {
        char nome_elemento[11];//Um numero inteiro poder ter até 10 bytes quando representando como string
        sprintf(nome_elemento, "%d", i + 1);
        int elemento = lerElemento(nome_elemento);
        if(conjunto->adicionarElemento(elemento)) i++;//Se o conjunto já não continha o elemento, prossegue
        else printf("O conjunto já tem esse elemento\n");
    }

    return conjunto;
}

void execVerPertinencia() {
    printf("Digite o valor do elemento a ser procurado:\n");
    int elemento = lerElemento("Elemento");

    bool em_a = a->procurar(elemento) != -1;//-1 significa não encontrado, enquanto valores maiores representam o indicce
    bool em_b = b->procurar(elemento) != -1;

    if(em_a && em_b) printf("%d pertence tanto a A, quando a B\n", elemento);
    else if(em_a) printf("%d pertence somente a A\n", elemento);
    else if(em_b) printf("%d pertence somente a B\n", elemento);
    else printf("%d não pertence nem a A nem a B\n", elemento);
}

void execMaiorMenor() {
    int maior_a, menor_a, maior_b, menor_b;

    bool a_vazio = a->obterTamanho() == 0;
    bool b_vazio = b->obterTamanho() == 0;

    if (!a_vazio) {//O conjunto deve ter pelo menos um elemento para começarmos
        maior_a = a->obter(0);//Para o caso do conjunto conter apenas um elemento, então MAIOR = MENOR
        menor_a = maior_a;
    }
    if (!b_vazio) {
        maior_b = b->obter(0);
        menor_b = maior_b;
    }

    for(int i = 1; i < a->obterTamanho(); i++) {//O primeiro elemento não precisa ser analisado
        int elemento = a->obter(i);

        if(elemento > maior_a) maior_a = elemento;
        else if(elemento < menor_a) menor_a = elemento;
    }

    for(int i = 1; i < b->obterTamanho(); i++) {
        int elemento = b->obter(i);

        if(elemento > maior_b) maior_b = elemento;
        else if(elemento < menor_b) menor_b = elemento;
    }

    printf("Os maiores e menores elementos de A e B são\n");

    if (!a_vazio) printf("Maior de A: %d  menor de A: %d\n", maior_a, menor_b);
    else printf("O conjunto A está vazio\n");

    if(!b_vazio) printf("Maior de B: %d  menor de B: %d\n", maior_b, menor_b);
    else printf("O conjunto B está vazio\n");
}

void execIgualdade() {
    ComparacaoConjunto comp = a->comparar(b);

    if(comp == ComparacaoConjunto::IGUAL) printf("O conjunto A é igual ao conjunto B\n");
    else printf("O conjunto A e o conjunto B são diferentes\n");
}

void execSubconjunto() {
    ComparacaoConjunto a_sub_b = a->comparar(b);
    ComparacaoConjunto b_sub_a = b->comparar(a);

    if(a_sub_b == ComparacaoConjunto::IGUAL) printf("A e B são iguais, e portanto subconjuntos um do outro\n");
    else if(a_sub_b == ComparacaoConjunto::SUBCONJUNTO) printf("O conjunto A é subconjunto de B\n");
    else if(b_sub_a == ComparacaoConjunto::SUBCONJUNTO) printf("O conjunto B é subconjunto de A\n");
    else printf("O conjunto A não é subconjunto de B e vice versa\n");
}

void execUniao() {
    Conjunto *uniao = a->unir(b);
    uniao->ordenar();

    printf("O conjunto união de A e B\n");
    uniao->imprimir();

    delete uniao;
}

void execInterseccao() {
    Conjunto *interseccao = a->intersectar(b);
    interseccao->ordenar();

    printf("O conjunto instersecão de A e B\n");
    interseccao->imprimir();

    delete interseccao;
}

void execDiferenca() {
    Conjunto *diferenca_a_b = a->subtrair(b);
    Conjunto *diferenca_b_a = b->subtrair(a);
    diferenca_a_b->ordenar();
    diferenca_b_a->ordenar();

    printf("O conjunto diferença A - B\n");
    diferenca_a_b->imprimir();

    printf("O conjunto diferença B - A\n");
    diferenca_b_a->imprimir();

    delete diferenca_a_b;
    delete diferenca_b_a;
}

void execComplemento() {
    Conjunto *complemento_a = universo->subtrair(a);
    Conjunto *complemento_b = universo->subtrair(b);

    complemento_a->ordenar();
    complemento_b->ordenar();

    printf("O complemento de A\n");
    complemento_a->imprimir();

    printf("O complemento de B\n");
    complemento_b->imprimir();
}
