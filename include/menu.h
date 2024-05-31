// Define as funções úteis para o código
#define red "\033[31m"
#define green "\033[32m"
#define blue "\033[34m"
#define yellow "\033[33m"
#define white "\033[0m"
#define clear() printf("\e[1;1H\e[2J")

// header principal
int header(void) {
  clear();
  // Utilizando o site https://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20, criei a header para o jogo
  printf(" %s____ %s____ %s____ %s__  __ %s____ %s_  _ \n", green, blue, red,
         yellow, green, blue);
  printf("%s(_  _%s( ___%s(  _ %s(  \\/  %s(_  _%s( \\/ )\n", green, blue, red,
         yellow, green, blue);
  printf("  %s)(  %s)__) %s)   /%s)    ( %s_)(_ %s)  ( \n", green, blue, red,
         yellow, green, blue);
  printf(" %s(__)%s(____%s(_)_\\_%s(_/\\/_%s(____%s(_/\\_)%s\n", green, blue,
         red, yellow, green, blue, white);
  printf("-----------------------------------\n\n");
} // No início de todas as funções que imprimem informações, uma nova header é printada para manter a tela limpa a todos os momentos

// Menu das opções
int options(void) {
  header(); 
  printf("%sEscolha uma das opções abaixo:%s\n\n", blue, white);
  printf("1 - %sJogar%s\n", green, white);
  printf("2 - Cadastrar palavra\n");
  printf("3 - Acessar dicionario\n");
  printf("4 - %sCréditos%s\n", red, white);
}

// Menu dos créditos
int creditos(void) {
  header();
  printf("\n   Feito por %sGabriela Bassegio%s  \n   %sDesenvolvimento de "
         "Algoritmos%s\n             %sCCP130\n              %sT350%s\n",
         blue, white, green, white, red, yellow, white);
  exit(0); // Finaliza o jogo
}

// Menu das instruções
int how_to_play(void) {
  header();
  printf("Uma palavra de 5 letras será sorteada do dicionário;\n");
  printf("Você terá 6 tentativas para adivinhar a palavra;\n");
  printf("A cada tentativa você receberá dicas sobre a palavra:\n");
  printf("Se a letra estiver na posição correta, ela será %sverde%s;\n", green, white);
  printf("Se a letra estiver na palavra, mas na posição errada, ela será %samarela%s;\n", yellow, white);
  printf("Se a letra não estiver na palavra, ela será %svermelha%s;\n", red, white);
  printf("\n\n%sBom jogo! :)%s\n", green, blue);
    press_to_continue(); // Aguarda o usuário para continuar
}

// Pressione qualquer tecla para continuar
int press_to_continue(void) {
  printf("\n\n%sPressione qualquer tecla para prosseguir%s\n", blue, white);
  getchar();
  getchar();
}

// Menu sim ou não
int yes_no(void) {
  char a;
  scanf(" %c", &a);
  if (a == 's' || a == 'S') {
    return 1;
  } else if (a == 'n' || a == 'N') {
    return 0;
  } else {
    printf("Insira uma opção válida.\n");
  }
}

// Fazer outra consulta no dicionario
int outra_consulta(void) {
  printf("Deseja fazer outra consulta? (S/N)\n");
  if (yes_no() == 1) {
    return checar_dicionario();
  } else {
    return main();
  }
}

// Printar a tela de vitória
int win(char *str, int tentativas) {
  header();
  printf("\n\n%sParabéns! Você venceu!%s\n\n", green, white);
  printf("\nA palavra era: %s%s%s", green, str, white);
  printf(" e foi adivinhada em %s%d%s tentativas!\n", blue, tentativas + 1,
         white);
  printf("\n%sDeseja jogar novamente? (S/N)%s\n", blue, white);
  if (yes_no() == 1) {
    return start_jogo();
  } else {
    return main();
  }
}

// Printar a tela de derrota
int lose(char *str) {
  header();
  printf("\n\n%sQue pena... Você não acertou a palavra nas 6 tentativas...%s\n\n", red, white);
  printf("\n\nA palavra era: %s%s%s\n\n", green, str, white);
  printf("\n%sDeseja jogar novamente? (S/N)%s\n", blue, white);
  if (yes_no() == 1) {
    return start_jogo();
  } else {
    return main();
  }
}

