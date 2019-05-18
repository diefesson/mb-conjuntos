//Desenvolvido por Diefesson de Sousa Silva - 2019
#ifndef _CONJUNTO_H_
#define _CONJUNTO_H_

namespace com::diefesson::conjuntos {

enum ComparacaoConjunto{
    SUBCONJUNTO,
    IGUAL,
    NAO_CONTIDO
};


//Não usarei std::Vector, pois está é uma prática de arrays
class Conjunto {

private:

    int* numeros;
    int tamanho_aloc;
    int tamanho;
    float fator_de_crescimento;

    void crescer();

    void adicionar_ele_sem_ver(int elemento);//Considera que o elemento adcionado já tenha sido verificado

public:

    static Conjunto* de_sequencia(int inicio, int fim);

    Conjunto();

    Conjunto(Conjunto &original);

    ~Conjunto();

    bool adicionar_elemento(int elemento);

    bool remover_elemento(int elemento);

    ComparacaoConjunto comparar(Conjunto *outro);

    Conjunto* unir(Conjunto *outro);

    Conjunto* intersectar(Conjunto *outro);

    Conjunto* subtrair(Conjunto *outro);

    int procurar_elemento(int elemento);

    int obter_elemento(int indice);

    int obter_remover_elemento(int indice);

    int obter_tamanho();

    void ordenar();

    Conjunto* gerar_embaralhado();

    Conjunto* cortar(int fim);

    Conjunto* cortar(int inicio, int fim);

    void imprimir();
};

};

#endif //_CONJUNTO_H_
