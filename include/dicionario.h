#define red "\033[31m"
#define green "\033[32m"
#define blue "\033[34m"
#define yellow "\033[33m"
#define white "\033[0m"
#define clear() printf("\e[1;1H\e[2J")

// Formatação para HIGH LOW LOW LOW LOW case
void formatar_dict(char *str) {
    str[0] = toupper((unsigned char)str[0]); //coloca a primeira letra em maiusculo
    for (int i = 1; i < strlen(str); i++) { //formata o resto da string para minuscula
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Formatação para HIGH case
void formatar_jogo(char *str){
  for (int i = 0; i < strlen(str); i++) { //formata a string para maiuscula
      str[i] = toupper((unsigned char)str[i]);
  }
}

// Inputing palavra nova
int inserir_palavra(void) {
  header();
  char palavra[50];
  char definicao[100];
  
  printf("%sDigite uma palavra de 5 letras:%s \n", blue, white);
  scanf("%s", palavra); // Recebe a palavra digitada pelo usuário
  formatar_dict(palavra); // Formata para conferencia
  if(conferir(palavra)==0){// Confere se a palavra é válida
    if(yes_no()==1){ // Caso não seja, pergunta se deve voltar ao menu ou tentar novamente
      return inserir_palavra(); // Tentar novamente
    }else{
      return 0; // Menu
    }
  }
  // Caso a palavra seja válida, pede a definição
  printf("%sDigite a definição da sua palavra: %s\n",blue,white);
  scanf(" %[^\n]", definicao);
  
  formatar_dict(definicao); // Formata a definição 
  add_palavra(palavra,definicao);
  printf("%sNova palavra no dicionario!\n%sPalavra: %s\nDefinição: %s\n", green,white,palavra, definicao); // Confirma a adição da nova palavra
  
  printf("%sDeseja adicionar uma nova palavra? (S/N)%s\n",blue,white); // Pergunta se deseja adicionar uma nova palavra
  if(yes_no()==1){
    return inserir_palavra(); // Retorna para o inicio da função
  }else{
    return 0; //main
  }
  

}


// Conferir se a palavra é válida
int conferir(char *str) {
  if (strlen(str) != 5) { // Caso a palavra tenha mais ou menos de 5 letras
    printf("%sA palavra deve ter 5 letras. Deseja tentar novamente? (S/N) %s\n",red,white);
    return 0;
  }else if(repeticao(str)==0){ // Confere se, apesar de estar formatada corretamente, a palavra já não foi utilizada anteriormente
    return 0; //Já foi utilizada
  }else{
    return 1; // Palavra válida
  }
}

// Verificar se a palavra já existe no dicionário
int repeticao(char *palavra) {
  char palavra_arquivo[50];
  char definicao[100];
  // Abre o arquivo para leitura e confere se alguma das palavras é igual àquela inserida pelo usuário
  FILE *file;
  file = fopen("dict.txt", "r");
  while (fscanf(file, "%49s %999[^\n]", palavra_arquivo, definicao) == 2) {
    if (strcmp(palavra, palavra_arquivo) == 0) {
      fclose(file);
      printf("%sPalavra já existente no dicionario. Deseja tentar novamente? (S/N) %s\n",red,white);
      return 0; // Já foi utilizada
    }
  }
  fclose(file);
  return 1; // Palavra válida
}

// Adicionando a palavra no arquivo
int add_palavra(char *palavra, char *definicao){
  // Abre o arquivo para escrita e adiciona a nova palavra e definição
  FILE *dict;
  dict = fopen("dict.txt","a");
  fprintf(dict, "%s %s\n", palavra, definicao);
  fclose(dict);
  
}

// Checando o dicionario procurando pela palavra
int checar_dicionario(void){
  header();
  FILE *dict;
  dict = fopen("dict.txt", "r");
  char palavra[50],palavra_arquivo[50];
  char definicao[100];
  while (fscanf(dict, "%49s %999[^\n]", palavra_arquivo, definicao) == 2){ // Printa todas as palavras e suas definições
    printf("%s: %s\n",palavra_arquivo,definicao);
  }
  fclose(dict);
  // Abre novamente o arquivo para buscar por palavras específicas
  dict = fopen("dict.txt", "r");
  printf("%s\n\nDigite a palavra que você deseja checar: %s\n",blue,white);
  scanf("%s", palavra);
  formatar_dict(palavra);
  while (fscanf(dict, "%49s %99[^\n]", palavra_arquivo, definicao) == 2) {
      if (strcmp(palavra, palavra_arquivo) == 0) {
          printf("\n%sPalavra encontrada no dicionário!%s\n\n", green, white);
          printf("Palavra: %s\nDefinição: %s\n\n", palavra, definicao);
          fclose(dict);
          return outra_consulta(); //menu.h - pergunta se o usuario deseja fazer uma nova consulta
      }
  }
  fclose(dict);
  printf("%sPalavra não encontrada no dicionario!\n%s",red,white); // Caso nao haja "match" com as palavras do dicionario, pergunta se o usuario deseja adiciona-la ao dicionario
  printf("Deseja adiciona-la ao dicionario? (S/N)\n");
  if (yes_no() == 1){
    return inserir_palavra(); // Caso sim, retorna a funcao de inserir novas palavras
  }else{
    return outra_consulta(); // Caso nao, pergunta se o usuario deseja fazer uma nova consulta
  }
  
  
}


