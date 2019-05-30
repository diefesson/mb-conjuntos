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
    int tamanhoAloc;
    int tamanho;
    float fatorCrescimento;

    void crescer();

    void adicionarElementoSemVerificar(int elemento);//Considera que o elemento adcionado já tenha sido verificado

public:

    static Conjunto* deSequencia(int inicio, int fim);

    Conjunto();

    //Conjunto(Conjunto &original);
    Conjunto* clone();//Não usarei mais o operador de copia, pois sua funcionalidade é implicita e imprevissivel

    ~Conjunto();

    bool adicionarElemento(int elemento);

    bool removerElemento(int elemento);

    ComparacaoConjunto comparar(Conjunto *outro);

    Conjunto* unir(Conjunto *outro);

    Conjunto* intersectar(Conjunto *outro);

    Conjunto* subtrair(Conjunto *outro);

    int procurar(int elemento);

    int obter(int indice);

    int obterRemoverElemento(int indice);

    int obterTamanho();

    void ordenar();

    Conjunto* gerarEmbaralhado();

    Conjunto* cortar(int fim);

    Conjunto* cortar(int inicio, int fim);

    void imprimir();
};

};

#endif //_CONJUNTO_H_
