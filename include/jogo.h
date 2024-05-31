char *generate_word();

// Inicia o jogo
int start_jogo() {
  header();
  remove("jogo.txt"); // Remove o arquivo jogo.txt para iniciar um novo jogo
  char palavra[50];
  strcpy(palavra, generate_word()); // Seleciona uma palavra aleatória do arquivo 
  formatar_jogo(palavra); //dicionario.h - formata a palavra para maiúsculas
  first_stage(palavra); // primeira parte do jogo
}

// Cria uma estrutura para gerar a palavra
struct lista_palavras {
  char palavra[50];
};

// Gera uma palavra aleatória do dicionário
char* generate_word() {
  srand(time(NULL)); // Utiliza uma seed aleatória
  struct lista_palavras lista[5757]; // Inicia um vetor da lista de palavras com um número alto para evitar lotação
  char palavra[50], definicao[100];
  int word_count = 0;

  // Abre o arquivo para leitura e copia todas as palavras para a struct lista_palavras
  FILE *dict;
  dict = fopen("dict.txt", "r");
  while (fscanf(dict, "%49s %999[^\n]", palavra, definicao) == 2) {
    word_count++;
    strcpy(lista[word_count].palavra, palavra);
  }
  fclose(dict);
  // Seleciona um indice aleatorio no vetor de palavras e retorna a palavra
  int random = rand() % word_count + 1;
  char *chosen = malloc(sizeof(char) * 50);
  strcpy(chosen, lista[random].palavra);
  return chosen;
}

// Confere se a palavra é válida para o jogo (5 letras e não repetida)
int check_word(char *str) {
  // Abre o arquivo jogo e adiciona a palavra nova caso esteja dentro das regras
  FILE *jogo;
  jogo = fopen("jogo.txt", "a+");
  char palavra[50];
  
  if (strlen(str) == 5) { 
    while (fscanf(jogo, "%s", palavra) == 1) { // Se a palavra já tiver sido chutada, retorna 0
      if (strcmp(str, palavra) == 0) {
        printf("Palavra já foi usada.\n");
        fclose(jogo);
        return 0;
      }
    } // Caso não tenha sido usada, adiciona a palavra nova no arquivo para futuras checagens
    fprintf(jogo, "%s\n", str);
    fclose(jogo);
    return 1;
  } else { // Caso a palavra não tenha 5 letras, retorna 0
    printf("Palavra inválida.\n");
    fclose(jogo);
    return 0;
  }
}

// Inicia a primeira parte do jogo
int first_stage(char *objetivo) {
  for (int i = 0; i < 6; i++) { // Dentro das 6 tentativas
    char tentativa[50];
    printf("%sTENTATIVA %d %s\n", blue, i + 1, white); // Informa a tentativa atual
    scanf("%s", tentativa); // Recebe a palavra
    formatar_jogo(tentativa);
    if (check_word(tentativa) == 0) { //Caso a palavra não seja válida, retorna para a tentativa atual
      printf("Tente novamente.\n");
      i--;
    } else { // Caso a palavra seja válida, verifica se é igual ao objetivo
      if (second_stage(tentativa, objetivo, i) == 1) {
        return 1; // Vitória
      }
    }
  }
  return lose(objetivo); // Jogo terminou sem vitória
}

// Segunda fase do jogo
int second_stage(char *tent, char *obj, int n_tent) {
  int inside[5] = {0}; // Marcações para letras usadas na palavra objetivo
  int matched[5] = {0}; // Marcações para letras corretamente posicionadas
  char result[5]; // Armazena o resultado para ser printado 
  for (int i = 0; i < 5; i++) {
    result[i] = ' ';
  }
  // Divide a impressão dos resultados em 3:
  // 1. Marca as letras corretas na posição correta
  // 2. Marca as letras corretas na posição errada
  // 3. Marca as letras erradas
  
  for (int i = 0; i < 5; i++) { // Tenta todas as letras da palavra objetivo
    if (tent[i] == obj[i]) {
      result[i] = 'G'; // G para green
      inside[i] = 1; // Marca a letra como usada
      matched[i] = 1; // Marca a letra como correta
    }
  }

  for (int i = 0; i < 5; i++) { // Tenta todas as letras da palavra objetivo
    if (!matched[i]) { // Caso a letra não esteja correta
      int found = 0;
      for (int j = 0; j < 5; j++) { // Tenta todas as letras novamente
        if (!inside[j] && tent[i] == obj[j]) { // Caso a letra esteja na palavra objetivo 
          result[i] = 'Y'; // Y para yellow
          inside[j] = 1; // Marca como usada
          found = 1; // Marca como encontrada
          break;
        }
      }
      if (!found) { // Caso ela não tenha sido encontrada, marca-se como errada
        result[i] = 'R'; // R para red
      }
    }
  }
  // Printa o resultado com as cores correspondentes
  for (int i = 0; i < 5; i++) {
    if (result[i] == 'G') {
      printf("%s%c%s", green, tent[i], white);
    } else if (result[i] == 'Y') {
      printf("%s%c%s", yellow, tent[i], white);
    } else {
      printf("%s%c%s", red, tent[i], white);
    }
  }
  printf("\n");

  if (strcmp(tent, obj) == 0) { // Caso a tentativa seja igual ao objetivo, retorna vitoria
    return win(obj, n_tent); //menu.h - printa a tela de vitória
  }
  return 0; // Tentativa falhou, mas o jogo continua
}
