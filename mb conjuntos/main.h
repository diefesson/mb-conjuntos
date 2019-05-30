//Desenvolvido por Diefesson de Sousa Silva - 2019
#include "conjunto.h"
#ifndef _MAIN_H_
#define _MAIN_H_

int main();

using com::diefesson::conjuntos::Conjunto;

void iniciar();

void exibirMenu();

int lerElemento(char* nome);

Conjunto* lerConjunto(char* nome);

int lerNumero(char* nome);

void gerarConjuntoA();

void gerarConjuntoB();

void execGerarTodos();

void execVerPertinencia();//Opção 1

void execMaiorMenor();//Opção 2

void execIgualdade();//Opção 3

void execSubconjunto();//Opção 4

void execUniao();//Opção 5

void execInterseccao();//Opção 6

void execDiferenca();//Opção 7

void execComplemento();//Opção 8

#endif //_MAIN_H_
