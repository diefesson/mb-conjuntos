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

int inicioDoUniverso = -50;
int fimDoUniverso = 50;
int tamanhoDoUniverso = fimDoUniverso + 1 - inicioDoUniverso;//+ 1, pois fimDoUniverso é inclusivo

int main() {
    iniciar();

    //Gera conjunto universo
    //gerarConjuntoUniverso();
    universo = Conjunto::deSequencia(inicioDoUniverso,fimDoUniverso + 1);//A seguencia é exclusiva

    gerarConjuntoA();
    printf("Conjunto A\n");
    a->ordenar();
    a->imprimir();

    gerarConjuntoB();

    while(true) {
        int opcao;
        exibirMenu();
        //printf("Opção = ");
        //scanf("%d", &opcao);
        opcao = lerNumero((char*) "Opção");
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
            printf("Conjunto Universo\n");
            universo->ordenar();
            universo->imprimir();
            break;
        case 93:
            gerarConjuntoA();
            printf("Conjunto A\n");
            a->ordenar();
            a->imprimir();
            break;
        case 94:
            gerarConjuntoB();
            break;
        case 95:
            execGerarTodos();
            break;
        default:
            printf("A opção %d é inválida, tente outra\n", opcao);
        }
    }
}

void iniciar() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(nullptr));//Inicia o algoritmo de números aleatórios com o tempo atual
}

void exibirMenu() {
    printf(
        "*** MENU - Desenvolvido por Diefesson de Sousa Silva - 2019 V29.05.2019 *******\n"
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
        "92 - Exibir conjunto universo\n"
        "93 - Gerar conjunto A novamente\n"
        "94 - Gerar conjunto B novamente\n"
        "95 - Redefinir universo e gerar o conjuto A e B novamente\n"
        "*******************************************************************************\n"
    );
}

void gerarConjuntoA() {
    if(a != nullptr)
        delete a;

    int tamanho;
    while(true) {
        printf("Digite o tamanho do conjunto A(0 <= t <= %d)\n", tamanhoDoUniverso);
        //scanf("%d", &tamanho_a);
        tamanho = lerNumero((char*) "tamanho");
        if(0 <= tamanho && tamanho <= tamanhoDoUniverso)
            break;
        printf("O tamanho deve obedecer a regra 0 <= t <= %d\n", tamanhoDoUniverso);
    }

    Conjunto* temp = universo->gerarEmbaralhado();
    a = temp->cortar(tamanho);
    delete temp;
}

void gerarConjuntoB() {
    if(b != nullptr)
        delete b;

    b = lerConjunto((char*) "B");
}

void execGerarTodos(){
    printf("Digite o inicio e fim do universo, ambos inclusivos\n");
    inicioDoUniverso = lerNumero((char*) "inicio do universo");
    fimDoUniverso = lerNumero((char*) "fim do universo");

    if(fimDoUniverso < inicioDoUniverso){//O usuário trocou a ordem...
        int tmp = inicioDoUniverso;
        inicioDoUniverso = fimDoUniverso;
        fimDoUniverso = tmp;
    }

    tamanhoDoUniverso = fimDoUniverso + 1 - inicioDoUniverso;

    delete universo;
    universo = Conjunto::deSequencia(inicioDoUniverso, fimDoUniverso + 1);

    gerarConjuntoA();

    printf("Conjunto A\n");//Futuramente posso unir essas três linhas no método imprimir
    a->ordenar();
    a->imprimir();

    gerarConjuntoB();

}

int lerElemento(char* nome) {
    int elemento;
    while(true) {
//        if(nome != nullptr)
//            printf("%s = ", nome);//Opcionalmente exibe o nome do elemento lido
//            scanf("%d", &elemento);
        elemento = lerNumero(nome);
        if(inicioDoUniverso <= elemento && elemento <= fimDoUniverso)
            break;
        printf("O valor deve pertencer ao conjunto universo[%d, %d]\n", inicioDoUniverso, fimDoUniverso);
    }
    return elemento;
}

int lerNumero(char *nome) {
    int numero;

    if(nome != nullptr)
        printf("%s = ", nome);

    while(scanf("%d", &numero) != 1) { //Caso a leitura falhe, ele executa o loop que trata de limpar a entrada e tentar novamente
        printf("O valor deve ser um número inteiro válido\n");
        int c;
        while((c = getchar()) != EOF && c != '\n')//Ignora a entrada até que encontre um caracter de linha ou chegue no fim do terminal
            continue;
        if(c == EOF)
            exit(0);//Sai do programa caso o fluxo de entrada do terminal seja fechado

        if(nome != nullptr)
            printf("%s = ", nome);
    }

    return numero;
}

Conjunto* lerConjunto(char* nome) {
    Conjunto *conjunto = new Conjunto();
    int tamanho;

    if(nome != nullptr)
        printf("Digite o tamanho do conjunto %s(0 < t <= %d)\n", nome, tamanhoDoUniverso);
    else
        printf("Digite o tamanho do conjunto(0 <= t <= %d)\n", tamanhoDoUniverso);

    while(true) {
        tamanho = lerNumero((char*) "tamanho");
        if(0 <= tamanho && tamanho <= tamanhoDoUniverso)
            break;
        printf("O tamanho deve obedecer a regra 0 <= t <= %d\n", tamanhoDoUniverso);
    }

    printf("Agora digite os valores dos elementos\n");
    for(int i = 0; i < tamanho;) {
        char nomeElemento[12];//De acordo com o compilador um numero do tipo int poder ter até 12 bytes quando representando como string
        sprintf(nomeElemento, "%d", i + 1);
        int elemento = lerElemento(nomeElemento);
        if(conjunto->adicionarElemento(elemento))
            i++;//Se o conjunto já não continha o elemento, prossegue
        else
            printf("O conjunto já tem esse elemento\n");
    }

    return conjunto;
}

void execVerPertinencia() {
    printf("Digite o valor do elemento a ser procurado:\n");
    int elemento = lerElemento((char*) "Elemento");

    bool contidoEmA = a->procurar(elemento) != -1;//-1 significa não encontrado, enquanto valores maiores representam o indicce
    bool contidoEmB = b->procurar(elemento) != -1;

    if(contidoEmA && contidoEmB)
        printf("%d pertence tanto a A, quando a B\n", elemento);
    else if(contidoEmA)
        printf("%d pertence somente a A\n", elemento);
    else if(contidoEmB)
        printf("%d pertence somente a B\n", elemento);
    else
        printf("%d não pertence nem a A nem a B\n", elemento);
}

void execMaiorMenor() {
    printf("Os maiores e menores elementos de A e B são\n");

    //Refatorei este método no dia 29/05/2019 com o intuito de consertar alertas do compilador
    if (a->obterTamanho() != 0) {//Só procura o maior e menor elemento se o conjunto não estiver vazio
        int maiorA = a->obter(0);
        int menorA = maiorA;//Para o caso do conjunto conter apenas um elemento, então MAIOR = MENOR

        for(int i = 1; i < a->obterTamanho(); i++) {//O primeiro elemento não precisa ser analisado
            int elemento = a->obter(i);

            if(elemento > maiorA)
                maiorA = elemento;
            else if(elemento < menorA)
                menorA = elemento;
        }

        printf("Maior de A: %d  menor de A: %d\n", maiorA, menorA);
    } else {
        printf("O conjunto A está vazio\n");
    }

    if (b->obterTamanho() != 0) {
        int maiorB = b->obter(0);
        int menorB = maiorB;

        for(int i = 1; i < b->obterTamanho(); i++) {
            int elemento = b->obter(i);

            if(elemento > maiorB)
                maiorB = elemento;
            else if(elemento < menorB)
                menorB = elemento;
        }

        printf("Maior de B: %d  menor de B: %d\n", maiorB, menorB);
    } else {
        printf("O conjunto B está vazio\n");
    }
}

void execIgualdade() {
    ComparacaoConjunto comp = a->comparar(b);

    if(comp == ComparacaoConjunto::IGUAL)
        printf("O conjunto A é igual ao conjunto B\n");
    else
        printf("O conjunto A e o conjunto B são diferentes\n");
}

void execSubconjunto() {
    ComparacaoConjunto a_sub_b = a->comparar(b);
    ComparacaoConjunto b_sub_a = b->comparar(a);

    if(a_sub_b == ComparacaoConjunto::IGUAL)
        printf("A e B são iguais, e portanto subconjuntos um do outro\n");
    else if(a_sub_b == ComparacaoConjunto::SUBCONJUNTO)
        printf("O conjunto A é subconjunto de B\n");
    else if(b_sub_a == ComparacaoConjunto::SUBCONJUNTO)
        printf("O conjunto B é subconjunto de A\n");
    else
        printf("O conjunto A não é subconjunto de B e vice versa\n");
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
    Conjunto *diferencaAB = a->subtrair(b);
    Conjunto *diferencaBA = b->subtrair(a);
    diferencaAB->ordenar();
    diferencaBA->ordenar();

    printf("O conjunto diferença A - B\n");
    diferencaAB->imprimir();

    printf("O conjunto diferença B - A\n");
    diferencaBA->imprimir();

    delete diferencaAB;
    delete diferencaBA;
}

void execComplemento() {
    Conjunto *complementoA = universo->subtrair(a);
    Conjunto *complementoB = universo->subtrair(b);

    complementoA->ordenar();
    complementoB->ordenar();

    printf("O complemento de A\n");
    complementoA->imprimir();

    printf("O complemento de B\n");
    complementoB->imprimir();

    delete complementoA;
    delete complementoB;
}
