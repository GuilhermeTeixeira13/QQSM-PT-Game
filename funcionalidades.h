#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

#define N 150 // Número máximo de perguntas

/*   ↓ Representa a estrutura simplificada de uma pergunta ↓   */
typedef struct
{
    char identificador[4];
    char questao[257];
    char respostaCerta[257];
    char respostaErrada1[257];
    char respostaErrada2[257];
    char respostaErrada3[257];
    char dificuldade[10];
} PERGUNTAS;

/*   ↓ Representa a estrutura simplificada de um jogador (Para colocar nos resultados.txt) ↓   */
typedef struct
{
    char nome[100];
    int quantia;
}JOGADOR;

/*   ↓ Limpa o stdin ↓   */
void limpaInput();

/*   ↓ Imprime as informações necessárias acerca da questão ↓   */
void mostraPerguntas(PERGUNTAS pr);

/*   ↓ Transforma uma palavra qualquer (original) nela mesma em minúsculas (final) ↓   */
void minuscula(char *original, char *final);

/*
 * Dado um nome, a função procura dentro do array pr todas as questões e respetivas 
 * informações que contenham esse nome e imprime-as
 */
void indicePergunta(char *nome, PERGUNTAS *pr);

/*   ↓  Abre o ficheiro 'fnome' no modo 'modo'  ↓   */
FILE *abreFicheiro(char *fnome, char *modo);

/*   ↓  Fecha o ficheiro 'f' que se chama 'fnome'  ↓   */
void fechaFicheiro(FILE *f, char *fnome);

/*   ↓  Lê as perguntas que estão no ficheiro BINÁRIO chamado 'fnome'  ↓   */
void leBin(PERGUNTAS *pr, char *fnome);

/*   ↓  Lê as perguntas que estão no ficheiro TEXTO chamado 'fnome'  ↓   */
void leTXT(PERGUNTAS *pr, char *fnome);

/*   ↓  Mostra o array de perguntas armazenado  ↓   */
void mostraArray(PERGUNTAS *pr, int n);

/*   ↓  Pergunta se queremos repetir a ação que fizemos e retorna a opção escolhida, para ser usada na main  ↓   */
int repetirAcao();

/*   ↓  Cria uma pergunta pr, a partir das infos dadas: identificador, questao ...  ↓   */
PERGUNTAS criaPergunta(PERGUNTAS pr, char *identificador, char *questao, char *respostaCerta, char *respostaErrada1, char *respostaErrada2, char *respostaErrada3, char *dificuldade);

/*   ↓  Pede ao utilizador os dados necessários para poder criar uma pergunta. Verifica/valida o input  ↓   */
PERGUNTAS criaPerguntaIO();

/* ↓ Adiciona a pergunta 'p' ao array de perguntas 'pr' na ´última posição do conjunto de posições da dificuldade ↓ */
void adicionaPergunta(PERGUNTAS p, PERGUNTAS *pr);

/*   ↓  Devolve o índice da última pergunta do array de perguntas pr ↓   */
int indice(PERGUNTAS *pr);

/*   ↓  Adiciona uma pergunta à primeira posição LIVRE do array de perguntas pr  ↓   */
void adicionaPerguntaIO(PERGUNTAS *pr);

/*   ↓  Grava o conteúdo do array de perguntas pr no ficheiro BINÁRIO "fnome"  ↓   */
void gravaBin(PERGUNTAS *pr, char *fnome);

/*   ↓  Grava o conteúdo do array de perguntas pr no ficheiro de TEXTO "fnome"  ↓   */
void gravaTXT(PERGUNTAS *pr, char *fnome);

/*   ↓ Dado um identificador e um array de perguntas, 
devolve o índice do identificador no array  ↓   */
int indiceRemove(char *indentificador, PERGUNTAS *pr);

/* Remove a pergunta com o identificador 'identificador' do array de perguntas 'pr'.
 * Se existir mais do que uma pergunta com o mesmo nome, remove a primeira
 * Devolve 1 se a pergunta não existir, 0 caso contrario */
int removePergunta(char *identificador, PERGUNTAS *pr);

/* Remove a(as) pergunta(s) pretendidas(s) e dá feedback  */
void removePerguntaIO(PERGUNTAS *pr);

void linha();

/*   ↓  Cria um jogaor jr, a partir das infos dadas: nome e quantia que ganhou  ↓   */
JOGADOR criaInfoJogador(JOGADOR jr, char *nome, int quantia);

/*Adiciona um jogador 'jr' ao array de jogadores 'jrs' na posicao 'indice' */
void adicionaJogador(JOGADOR jr, int indice, JOGADOR *jrs);

/*   ↓  Devolve o índice da última pergunta do array de jogadores jrs ↓   */
int indiceJOGADOR(JOGADOR *jrs);

/*   ↓  Adiciona um jogador à primeira posição LIVRE do array de jogadores jrs  ↓   */
void adicionaJogadorIO(JOGADOR *jrs, char *nome, int quantia);

void gravaTXTJOGADOR(JOGADOR *jrs, char *fnome);

/*   ↓  Lê as perguntas que estão no ficheiro TEXTO chamado 'fnome'  ↓   */
void leTXTJOGADOR(JOGADOR *jrs, char *fnome);

/*   ↓  Sorteia números randoms entre max e min e coloca-os num array resultado de tamanho n ↓  */
void Randoms(int max, int min, int *resultado, int n);

/*   ↓  Junta os elementos dos arrays f, m e d num array final  ↓   */
void juntaArrays(int *f, int *m, int *d, int *final);

void tabela();

void infos();

int estaNoArray(int num, int *array, int tam);