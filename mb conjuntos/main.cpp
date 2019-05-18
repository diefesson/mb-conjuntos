//Desenvolvido por Diefesson de Sousa Silva - 2019
#include <locale.h>
#include <stdio.h>

#include "main.h"
#include "conjunto.h"//Minha classe para operações de conjunto

using com::diefesson::conjuntos::Conjunto;
using com::diefesson::conjuntos::ComparacaoConjunto;

Conjunto *universo = nullptr;
Conjunto *a = nullptr;
Conjunto *b = nullptr;

int main() {
    setlocale(LC_ALL, "Portuguese");

    //Gera conjunto universo
    universo = Conjunto::de_sequencia(-50, 51);

    gerar_conjunto_a();
    gerar_conjunto_b();

    while(true) {
        int opcao;
        exibir_menu();
        printf("Opção = ");
        scanf("%d", &opcao);
        switch(opcao) {
        case 1:
            exec_ver_pertinencia();
            break;
        case 2:
            exec_maior_menor();
            break;
        case 3:
            exec_igualdade();
            break;
        case 4:
            exec_subconjunto();
            break;
        case 5:
            exec_uniao();
            break;
        case 6:
            exec_interseccao();
            break;
        case 7:
            exec_diferenca();
            break;
        case 8:
            exec_complemento();
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
            gerar_conjunto_a();
            break;
        case 93:
            gerar_conjunto_b();
            break;
        default:
            printf("A opção %d é inválida, tente outra\n", opcao);
        }
    }
}

void exibir_menu() {
    printf(
        "*** MENU - Desenvolvido por Diefesson de Sousa Silva - 2019 ******************\n"
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

void gerar_conjunto_a() {
    if(a != nullptr) delete a;

    int tamanho_a;
    while(true) {
        printf("Digite o tamanho do conjunto A(0 <= t <= 101)\n");
        scanf("%d", &tamanho_a);
        if(0 <= tamanho_a && tamanho_a <= 101) break;
        printf("O tamanho deve obedecer a regra 0 <= t <= 101\n");
    }
    Conjunto* temp = universo->gerar_embaralhado();
    a = temp->cortar(tamanho_a);
    delete temp;
}

void gerar_conjunto_b() {
    if(b != nullptr) delete b;

    b = ler_conjunto("B");
}

int ler_elemento(char* nome) {
    int elemento;
    while(true) {
        if(nome != NULL) printf("%s = ", nome);//Opcionalmente exibe o nome do elemento lido
        scanf("%d", &elemento);
        if(-50 <= elemento && elemento <= 50) break;
        printf("O valor deve pertencer ao conjunto universo[-50, 50]\n");
    }
    return elemento;
}

Conjunto* ler_conjunto(char* nome) {
    Conjunto *conjunto = new Conjunto();
    int tamanho;

    if(nome != nullptr) printf("Digite o tamanho do conjunto %s(0 < t <= 101)\n", nome);
    else printf("Digite o tamanho do conjunto(0 <= t <= 101)\n");
    while(true) {
        scanf("%d", &tamanho);
        if(0 <= tamanho && tamanho <= 101) break;
        printf("O tamanho deve obedecer a regra 0 <= t <= 101\n");
    }

    printf("Agora digite os valores do elementos\n");
    for(int i = 0; i < tamanho;) {
        char nome_elemento[3];
        sprintf(nome_elemento, "%d", i);
        int elemento = ler_elemento(nome_elemento);
        if(conjunto->adicionar_elemento(elemento)) i++;//Se o conjunto já não continha o elemento, prossegue
        else printf("O conjunto já tem esse elemento\n");
    }

    return conjunto;
}

void exec_ver_pertinencia() {
    printf("Digite o valor do elemento a ser procurado:\n");
    int elemento = ler_elemento("Elemento");

    bool em_a = a->procurar_elemento(elemento) != -1;//-1 significa não encontrado, enquanto valores maiores representam o indicce
    bool em_b = b->procurar_elemento(elemento) != -1;

    if(em_a && em_b) printf("%d pertence tanto a A, quando a B\n", elemento);
    else if(em_a) printf("%d pertence somente a A\n", elemento);
    else if(em_b) printf("%d pertence somente a B\n", elemento);
    else printf("%d não pertence nem a A nem a B\n", elemento);
}

void exec_maior_menor() {
    int maior_a, menor_a, maior_b, menor_b;
    if (a->obter_tamanho() > 0) {//O conjunto deve ter pelo menos um elemento para começarmos
        maior_a = a->obter_elemento(0);//Para o caso do conjunto conter apenas um elemento, então MAIOR = MENOR
        menor_a = maior_a;
    }
    if (b->obter_tamanho() > 0) {
        maior_b = b->obter_elemento(0);
        menor_b = maior_b;
    }

    for(int i = 1; i < a->obter_tamanho(); i++) {//O primeiro elemento não precisa ser analisado
        int elemento = a->obter_elemento(i);

        if(elemento > maior_a) maior_a = elemento;
        else if(elemento < menor_a) menor_a = elemento;
    }

    for(int i = 1; i < b->obter_tamanho(); i++) {
        int elemento = b->obter_elemento(i);

        if(elemento > maior_b) maior_b = elemento;
        else if(elemento < menor_b) menor_b = elemento;
    }

    printf("Os maiores e menores elementos de A e B são\n");

    if (a->obter_tamanho() > 0) printf("Maior de A: %d  menor de A: %d\n", maior_a, menor_b);
    else printf("O conjunto A está vazio\n");

    if(b->obter_tamanho() > 0) printf("Maior de B: %d  menor de B: %d\n", maior_b, menor_b);
    else printf("O conjunto B está vazio\n");
}

void exec_igualdade() {
    ComparacaoConjunto comp = a->comparar(b);

    if(comp == ComparacaoConjunto::IGUAL) printf("O conjunto A é igual ao conjunto B\n");
    else printf("O conjunto A e o conjunto B são diferentes\n");
}

void exec_subconjunto() {
    ComparacaoConjunto a_sub_b = a->comparar(b);
    ComparacaoConjunto b_sub_a = b->comparar(a);

    if(a_sub_b == ComparacaoConjunto::IGUAL) printf("A e B são iguais, e portanto subconjuntos um do outro\n");
    else if(a_sub_b == ComparacaoConjunto::SUBCONJUNTO) printf("O conjunto A é subconjunto de B\n");
    else if(b_sub_a == ComparacaoConjunto::SUBCONJUNTO) printf("O conjunto B é subconjunto de A\n");
    else printf("O conjunto A não é subconjunto de B e vice versa\n");
}

void exec_uniao() {
    Conjunto *uniao = a->unir(b);
    uniao->ordenar();

    printf("O conjunto união de A e B\n");
    uniao->imprimir();

    delete uniao;
}

void exec_interseccao() {
    Conjunto *interseccao = a->intersectar(b);
    interseccao->ordenar();

    printf("O conjunto instersecão de A e B\n");
    interseccao->imprimir();

    delete interseccao;
}

void exec_diferenca() {
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

void exec_complemento() {
    Conjunto *complemento_a = universo->subtrair(a);
    Conjunto *complemento_b = universo->subtrair(b);

    complemento_a->ordenar();
    complemento_b->ordenar();

    printf("O complemento de A\n");
    complemento_a->imprimir();

    printf("O complemento de B\n");
    complemento_b->imprimir();
}
