// Incluindo as bibliotecas 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>

// Incluindo as bibliotecas locais criadas para melhor funcionamento do código
#include "include/dicionario.h"
#include "include/jogo.h"
#include "include/menu.h"


// GABRIELA BASSEGIO
// T650
// RA 11.123.140-3


int main(void) {
  options(); //menu.h - printa as opções
  int opt;
  scanf("%d", &opt);
  switch (opt) { // Utiliza um switch case para acessar as funções de acordo com a opção escolhida
    case 1:
      how_to_play(); //menu.h - printa as instruções
      start_jogo(); //jogo.h - inicia o jogo e acessa suas funções
      break; 
    case 2:
      inserir_palavra(); //dicionario.h - insere uma nova palavra no dicionário
      break; 
    case 3:
      checar_dicionario(); //dicionario.h - acessa o dicionário para consulta
      break; 
    case 4:
      creditos(); //menu.h - printa os créditos e finaliza o jogo
      break; 
    default: // Qualquer caractere diferente de 1, 2, 3 ou 4 é considerado inválido
      printf("%sOpção inválida, por favor tente novamente%s\n", red, white);
      getchar(); // Consome o caractere de nova linha pendente para não cair no default novamente
      sleep(1);
      break; 
  }main(); //Todas as funções retornam para o início do programa para que o usuário possa escolher outra opção, menos os créditos
}
