/*
** Nome: Matheus Gabriel Viana Araujo
** RA: 10420444
*/

#include <stdio.h>
#include <stdlib.h>

// Tamanho máximo das strings e dos vetores
#define TAMANHO_STRING 50
#define TAMANHO_VETOR 10000

// Algoritmos de ordenação
void insertion_sort(char vetor[][TAMANHO_STRING], int tamanho, int *passos,
                    FILE *out1);
void merge_sort(char vetor[][TAMANHO_STRING], int tamanho, int *passos);
void merge(char vetor[][TAMANHO_STRING], char esquerda[][TAMANHO_STRING],
           int tamanho_esq, char direita[][TAMANHO_STRING], int tamanho_dir,
           int *passos);

// Funções específicas para strings
size_t comprimento_string(const char *string);
int comparar_strings(const char *primeira_string, const char *segunda_string);
char *copiar_string(char *string_alvo, const char *string_fonte);

int main(int argc, char *argv[]) {

  int passos_insertion = 0;
  int passos_merge = 0;

  // Abre o arquivo contendo as 10000 strings aleatórias,
  // as strings são separadas por '\n'
  FILE *in = fopen("in.txt", "r");
  if (in == NULL) {
    printf("Erro ao abrir o arquivo\n");
    return 1;
  }

  // Vetores bidimensionais que armazenarão as strings do arquivo
  char vetor_insertion[TAMANHO_VETOR][TAMANHO_STRING];
  char vetor_merge[TAMANHO_VETOR][TAMANHO_STRING];

  // Preenche o vetor_insertion com as strings no arquivo "in"
  for (int i = 0;
       i < TAMANHO_VETOR &&
       fgets(vetor_insertion[i], sizeof(vetor_insertion[i]), in) != NULL;
       i++) {
    // Removendo o '\n' ao final da palavra, se necessário
    size_t len = comprimento_string(vetor_insertion[i]);
    if (vetor_insertion[i][len - 1] == '\n') {
      vetor_insertion[i][len - 1] = '\0';
    }
    // Copia o vetor para a versão a ser usada no merge sort
    copiar_string(vetor_merge[i], vetor_insertion[i]);
  }
  fclose(in);

  // INSERTION SORT

  // Cria o arquivo de saída para o insertion sort
  FILE *out1 = fopen("out1.txt", "w");
  if (out1 == NULL) {
    printf("Erro ao criar arquivo out1\n");
    return 1;
  }

  // Realiza o insertion sort
  insertion_sort(vetor_insertion, TAMANHO_VETOR, &passos_insertion, out1);
  fclose(out1);

  // Exibe o número total de passos do insertion sort
  printf("Insertion sort precisou de %d passos.\n", passos_insertion);

  // MERGE SORT

  // Realiza o merge sort
  merge_sort(vetor_merge, TAMANHO_VETOR, &passos_merge);

  // Cria o arquivo de saída para o merge sort
  FILE *out2 = fopen("out2.txt", "w");
  if (out2 == NULL) {
    printf("Erro ao criar arquivo out2\n");
    return 1;
  }

  // Escreve cada palavra ordenada no arquivo out2, uma por linha
  for (int i = 0; i < TAMANHO_VETOR; i++) {
    fprintf(out2, "%s\n", vetor_merge[i]);
  }
  fclose(out2);

  // Exibe o número total de passos do merge sort
  printf("Merge sort precisou de %d passos.\n", passos_merge);

  return 0;
}

// INSERTION SORT

void insertion_sort(char vetor[][TAMANHO_STRING], int tamanho, int *passos,
                    FILE *out1) {
  char chave[TAMANHO_STRING];
  int i, j;

  for (i = 1; i < tamanho; i++) {
    copiar_string(chave, vetor[i]);
    j = i - 1;

    // Move os elementos do vetor que são maiores que a chave
    while (j >= 0 && comparar_strings(vetor[j], chave) > 0) {
      copiar_string(vetor[j + 1], vetor[j]);
      j--;
      (*passos)++;
    }

    copiar_string(vetor[j + 1], chave);
    (*passos)++;
  }

  // Escreve cada palavra ordenada no arquivo out1, uma por linha
  for (i = 0; i < tamanho; i++) {
    fprintf(out1, "%s\n", vetor[i]);
  }
}

// MERGE SORT

void merge(char vetor[][TAMANHO_STRING], char esquerda[][TAMANHO_STRING],
           int tamanho_esq, char direita[][TAMANHO_STRING], int tamanho_dir,
           int *passos) {

  int i = 0;
  int j = 0;
  int k = 0;

  // Mescla dois subvetores ordenados em um único vetor ordenado, sempre
  // copiando o menor elemento das duas listas no vetor final
  while (i < tamanho_esq && j < tamanho_dir) {
    if (comparar_strings(esquerda[i], direita[j]) <= 0) {
      copiar_string(vetor[k], esquerda[i]);
      i++;
    } else {
      copiar_string(vetor[k], direita[j]);
      j++;
    }
    k++;
    (*passos)++;
  }

  // Copia os elementos restantes da metade esquerda, se houver
  while (i < tamanho_esq) {
    copiar_string(vetor[k], esquerda[i]);
    i++;
    k++;
    (*passos)++;
  }

  // Copia os elementos restantes da metade direita, se houver
  while (j < tamanho_dir) {
    copiar_string(vetor[k], direita[j]);
    j++;
    k++;
    (*passos)++;
  }
}

void merge_sort(char vetor[][TAMANHO_STRING], int tamanho, int *passos) {
  if (tamanho <= 1) {
    return;
  }

  int meio = tamanho / 2;

  // Vetores temporários para as metades esquerda e direita
  char esquerda[meio][TAMANHO_STRING];
  char direita[tamanho - meio][TAMANHO_STRING];

  // Preenche o vetor da metade esquerda
  for (int i = 0; i < meio; i++) {
    copiar_string(esquerda[i], vetor[i]);
  }
  // Preenche o vetor da metade direita
  for (int i = meio; i < tamanho; i++) {
    copiar_string(direita[i - meio], vetor[i]);
  }

  // Chama merge_sort recursivamente para ambas as metades
  merge_sort(esquerda, meio, passos);
  merge_sort(direita, tamanho - meio, passos);

  // Mescla as duas metades
  merge(vetor, esquerda, meio, direita, tamanho - meio, passos);
}

size_t comprimento_string(const char *string) {
  size_t tamanho = 0;
  while (*string++) {
    tamanho++;
  }
  return tamanho;
}

int comparar_strings(const char *primeira_string, const char *segunda_string) {
  while (*primeira_string && (*primeira_string == *segunda_string)) {
    primeira_string++;
    segunda_string++;
  }
  return *(const unsigned char *)primeira_string -
         *(const unsigned char *)segunda_string;
}

char *copiar_string(char *string_alvo, const char *string_fonte) {
  char *p = string_alvo;

  // Copia cada caractere da string_fonte para string_alvo
  while ((*string_alvo++ = *string_fonte++))
    ; // Loop até que o terminador nulo seja copiado

  return p; // Retorna o início da string de destino
}
