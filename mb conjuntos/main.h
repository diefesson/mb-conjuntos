//Desenvolvido por Diefesson de Sousa Silva - 2019
#include "conjunto.h"
#ifndef _MAIN_H_
#define _MAIN_H_

using com::diefesson::conjuntos::Conjunto;

void exibir_menu();

int ler_elemento(char* nome);

Conjunto* ler_conjunto(char* nome);

void gerar_conjunto_a();

void gerar_conjunto_b();

void exec_ver_pertinencia();//Opção 1

void exec_maior_menor();//Opção 2

void exec_igualdade();//Opção 3

void exec_subconjunto();//Opção 4

void exec_uniao();//Opção 5

void exec_interseccao();//Opção 6

void exec_diferenca();//Opção 7

void exec_complemento();//Opção 8

#endif //_MAIN_H_
