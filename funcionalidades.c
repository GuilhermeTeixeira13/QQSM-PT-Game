#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include"funcionalidades.h"

/*   ↓ Limpa o stdin ↓   */
void limpaInput()
{
    while (getchar() != '\n');
}

/*   ↓ Imprime as informações necessárias acerca da questão ↓   */
void mostraPerguntas(PERGUNTAS pr)
{
    printf("➤  Identificador: %s\n", pr.identificador);
    printf("   Questão: %s\n", pr.questao);
    printf("   Resposta certa: %s\n", pr.respostaCerta);
    printf("   Respostas erradas: %s, %s, %s\n", pr.respostaErrada1, pr.respostaErrada2, pr.respostaErrada3);
    printf("   Dificuldade: %s\n", pr.dificuldade);
}

/*   ↓ Transforma uma palavra qualquer (original) nela mesma em minúsculas (final) ↓   */
void minuscula(char *original, char *final)
{
    int i;
    for(i=0; original[i] != '\0'; i++)
        final[i] = tolower(original[i]);
    final[i] = '\0';
}

/*
 *  Dado um nome, a função procura dentro do array pr todas as questões e respetivas 
 * informações que contenham esse nome e imprime-as
 */
void indicePergunta(char *nome, PERGUNTAS *pr)
{
    int i = 0, cont = 0;
    char *o, *p, *q, *r, *s, *t, *u;
    char procuradoMinus[257];
    int saida=0, valido=0;
    
    while (i < N && strlen(pr[i].questao) > 0 && saida != 1)
    {
        char min0[strlen(pr[i].identificador)+1], min1[strlen(pr[i].questao)+1], min2[strlen(pr[i].respostaCerta)+1], min3[strlen(pr[i].respostaErrada1)+1], min4[strlen(pr[i].respostaErrada2)+1], min5[strlen(pr[i].respostaErrada3)+1], min6[strlen(pr[i].dificuldade)+1];
        char decisao[12], *pos;

        /*   ↓ Transforma todas as questões e respetivo conjunto de infos em minúsculas (Case insensitive) ↓   */
        minuscula(pr[i].identificador, min0);
        minuscula(pr[i].questao, min1);
        minuscula(pr[i].respostaCerta, min2);
        minuscula(pr[i].respostaErrada1, min3);
        minuscula(pr[i].respostaErrada2, min4);
        minuscula(pr[i].respostaErrada3, min5);
        minuscula(pr[i].dificuldade, min6);
        minuscula(nome, procuradoMinus);

        /*   ↓ Verifica se a palavra procurada está presente em cada uma das questões, respostas etc ↓   */
        /*   o, p, q, r, s, t, u são apontadores para o a primeira letra da palavra procurada(procuradoMinus), 
                            que aparece dentro da palavra/frase principal (min)   */
        o = strstr(min0, procuradoMinus);
        p = strstr(min1, procuradoMinus);
        q = strstr(min2, procuradoMinus);
        r = strstr(min3, procuradoMinus);
        s = strstr(min4, procuradoMinus);
        t = strstr(min5, procuradoMinus);
        u = strstr(min6, procuradoMinus);
        
        if(o || p || q || r || s || t || u) // Se sim, então mostra essas mesmas questões
        {
            mostraPerguntas(pr[i]);
            cont++;
            if ((cont) % 5 == 0) // Quando forem mostrados 5/10/15... perguntas, é dada a opção de sair(q ou quit) ou continuar(enter)
            {
                valido=0;
                printf("\n");
                printf(" - Prima enter para ver os próximos ou 'q'/'quit' para sair: ");
                fgets(decisao, 257, stdin);
                pos = strchr(decisao, '\n');
                *pos = '\0';

                if(strcmp(decisao, "q") == 0 || strcmp(decisao, "quit") == 0)
                    saida = 1;
                else if(decisao[0] == '\0')
                    saida = 0;
                else
                {
                    while(valido != 1)
                    {
                        printf(" ✘  Opção inválida! Prima enter para ver os próximos ou 'q'/'quit' para sair: ");
                        fgets(decisao, 257, stdin);
                        pos = strchr(decisao, '\n');
                        *pos = '\0';
                        if(strcmp(decisao, "q") == 0 || strcmp(decisao, "quit") == 0)
                        {
                            saida = 1;
                            valido = 1;
                        }
                        else if(decisao[0] == '\0')
                        {
                            saida = 0;
                            valido = 1;
                        }
                        else
                        {
                            valido = 0;
                        }   
                    }
                }
            }
            printf("\n");
        }
        i++;
    }
    if(cont==0) // Se não encontrar nenhuma, imprime a seguinte mensagem
        printf("- Não foram encontrados resultados que correspondem à sua pesquisa! ☹ \n");
}

/*   ↓  Abre o ficheiro 'fnome' no modo 'modo'  ↓   */
FILE *abreFicheiro(char *fnome, char *modo) 
{
    FILE *f = fopen(fnome, modo);

    if (f == NULL)
    {
        fprintf(stderr, "Falhou abertura de %s.\n", fnome);
        exit(EXIT_FAILURE);
    }

    return f;
}

/*   ↓  Fecha o ficheiro 'f' que se chama 'fnome'  ↓   */
void fechaFicheiro(FILE *f, char *fnome)
{
    if (fclose(f) == EOF)
    {
        fprintf(stderr, "Falhou o fecho de %s.\n", fnome);
        exit(EXIT_FAILURE);
    }
}

/*   ↓  Lê as perguntas que estão no ficheiro BINÁRIO chamado 'fnome'  ↓   */
void leBin(PERGUNTAS *pr, char *fnome)
{
    FILE *f = abreFicheiro(fnome, "rb");

    fread(pr, sizeof(PERGUNTAS), N, f); // Lê a partir do ficheiro f, N elementos de tamanho sizeof(PERGUNTAS), começando pelo início do bloco de dados

    fechaFicheiro(f, fnome);
}

/*   ↓  Lê as perguntas que estão no ficheiro TEXTO chamado 'fnome'  ↓   */
void leTXT(PERGUNTAS *pr, char *fnome)
{
    FILE *f = abreFicheiro(fnome, "r");

    int i = 0;
    /*             ↓  Lê o input formatado através da stream  ↓                       */
    /* Tudo o que estiver no lugar de %[^|], é guardado em pr[i].identificador etc... */
    while (fscanf(f, "ID %[^|]|QUESTÃO: %[^|]|RESPOSTA CERTA: %[^|]|RESPOSTAS ERRADAS: %[^,], %[^,], %[^|]|DIFICULDADE: %[^.].\n", pr[i].identificador, pr[i].questao, pr[i].respostaCerta, pr[i].respostaErrada1, pr[i].respostaErrada2, pr[i].respostaErrada3, pr[i].dificuldade) == 7)
    {
        i++; // percorre posições até que não consiga coletar tudo o que é desejado 
    }

    fechaFicheiro(f, fnome);
}

/*   ↓  Mostra o array de perguntas armazenado  ↓   */
void mostraArray(PERGUNTAS *pr, int n)
{
    int saida, valido;
    char decisao[12];
    char *pos;

    for (int i = 0; i < n && strlen(pr[i].questao) > 0 && saida != 1; i++) // Percorre posições enquanto existir alguma questão
    {
        mostraPerguntas(pr[i]);
        printf("\n");

        if ((i + 1) % 5 == 0) // Quando forem mostrados 5/10/15... perguntas, é dada a opção de sair(q) ou continuar(enter)
        {
            valido=0;
            printf(" - Prima enter para ver os próximos ou 'q'/'quit' para sair: ");
            fgets(decisao, 257, stdin);
            pos = strchr(decisao, '\n');
            *pos = '\0';

            if(strcmp(decisao, "q") == 0 || strcmp(decisao, "quit") == 0)
                saida = 1;
            else if(decisao[0] == '\0')
                saida = 0;
            else
            {
                while(valido != 1)
                {
                    printf(" ✘  Opção inválida! Prima enter para ver os próximos ou 'q'/'quit' para sair: ");
                    fgets(decisao, 257, stdin);
                    pos = strchr(decisao, '\n');
                    *pos = '\0';
                    if(strcmp(decisao, "q") == 0 || strcmp(decisao, "quit") == 0)
                    {
                        saida = 1;
                        valido = 1;
                    }
                    else if(decisao[0] == '\0')
                    {
                        saida = 0;
                        valido = 1;
                    }
                    else
                    {
                        valido = 0;
                    }   
                }
            }
            printf("\n");
        }
    }
}

/*   ↓  Pergunta se queremos repetir a ação que fizemos e retorna a opção escolhida, para ser usada na main  ↓   */
int repetirAcao()
{
    int opcaoEscolhida;

    printf("↪  1. REPETIR AÇÃO\n");
    printf("↪  2. VOLTAR AO MENU\n\n");
    printf("Opção -> ");
    while(scanf("%d", &opcaoEscolhida) != 1)
    {
        limpaInput();
        printf(" ✘  Input inválido! Digite algo válido: ");
    }
    while(opcaoEscolhida < 1 || opcaoEscolhida > 2)
    {
        limpaInput();
        printf(" ✘  Opção inválida! Digite algo válido: ");
        while(scanf("%d", &opcaoEscolhida) != 1)
        {
            limpaInput();
            printf(" ✘  Input inválido! Digite algo válido: ");
        }
    }

    return opcaoEscolhida;
}

/*   ↓  Cria uma pergunta pr, a partir das infos dadas: identificador, questao ...  ↓   */
PERGUNTAS criaPergunta(PERGUNTAS pr, char *identificador, char *questao, char *respostaCerta, char *respostaErrada1, char *respostaErrada2, char *respostaErrada3, char *dificuldade)
{
    strcpy(pr.identificador, identificador);
    strcpy(pr.questao, questao);
    strcpy(pr.respostaCerta, respostaCerta);
    strcpy(pr.respostaErrada1, respostaErrada1);
    strcpy(pr.respostaErrada2, respostaErrada2);
    strcpy(pr.respostaErrada3, respostaErrada3);
    strcpy(pr.dificuldade, dificuldade);

    return pr;
}

/*   ↓  Pede ao utilizador os dados necessários para poder criar uma pergunta. Verifica/valida o input  ↓   */
PERGUNTAS criaPerguntaIO()
{
    PERGUNTAS pr;
    int len;
    char *pos;
    char minus[257];
    char ident[4];
    char pergunta[257];
    char respostaCerta[257];
    char respostaErrada1[257];
    char respostaErrada2[257];
    char respostaErrada3[257];
    char dificuldade[257];

    do
    {
        printf("Identificador [Máximo 3 caracters]: ");
        fgets(ident, 257, stdin);
        pos = strchr(ident, '\n');
        *pos = '\0';
        len = strlen(ident);
        if (len == 0)
            printf(" ✘ Identificador vazio!!\n");
        if(len > 3)
            printf(" ✘ Identificador demasiado longo!!\n");
    } while (len == 0 || len > 3);

    do
    {
        printf("Pergunta: ");
        fgets(pergunta, 257, stdin);
        pos = strchr(pergunta, '\n');
        *pos = '\0';
        len = strlen(pergunta);
        if (len == 0)
            printf(" ✘ Pergunta vazia. Indique outra.\n");
    } while (len == 0);

    do
    {
        printf("Resposta Certa: ");
        fgets(respostaCerta, 257, stdin);
        pos = strchr(respostaCerta, '\n');
        *pos = '\0';
        len = strlen(respostaCerta);
        if (len == 0)
            printf(" ✘ Resposta vazia. Indique outra.\n");
    } while (len == 0);

    do
    {
        printf("Resposta Errada 1: ");
        fgets(respostaErrada1, 257, stdin);
        pos = strchr(respostaErrada1, '\n');
        *pos = '\0';
        len = strlen(respostaErrada1);
        if (len == 0)
            printf(" ✘ Resposta vazia. Indique outro.\n");
    } while (len == 0);

    do
    {
        printf("Resposta Errada 2: ");
        fgets(respostaErrada2, 257, stdin);
        pos = strchr(respostaErrada2, '\n');
        *pos = '\0';
        len = strlen(respostaErrada2);
        if (len == 0)
            printf(" ✘ Resposta vazia. Indique outro.\n");
    } while (len == 0);

    do
    {
        printf("Resposta Errada 3: ");
        fgets(respostaErrada3, 257, stdin);
        pos = strchr(respostaErrada3, '\n');
        *pos = '\0';
        len = strlen(respostaErrada3);
        if (len == 0)
            printf(" ✘ Resposta vazia. Indique outro.\n");
    } while (len == 0);

    do
    {
        printf("Diciculdade (facil/medio/dificil sem acentuação): ");
        fgets(dificuldade, 257, stdin);
        pos = strchr(dificuldade, '\n');
        *pos = '\0';
        minuscula(dificuldade, minus);
        len = strlen(minus);
        /*   ↓  Caso a 'dificuldade' escrita não esteja na forma pretendida, esta acaba não sendo aceite  ↓   */
        if (len == 0 || (strcmp(minus, "facil") != 0 && strcmp(minus, "medio") != 0 && strcmp(minus, "dificil") != 0))
            printf(" ✘ Dificuldade inválida. Indique outra.\n");
    } while (len == 0 || (strcmp(minus, "facil") != 0 && strcmp(minus, "medio") != 0 && strcmp(minus, "dificil") != 0));

    /*   ↓  Cria pergunta com a informação dada  ↓   */
    return criaPergunta(pr, ident, pergunta, respostaCerta, respostaErrada1, respostaErrada2, respostaErrada3, dificuldade);
}

/* ↓ Adiciona a pergunta 'p' ao array de perguntas 'pr' na ´última posição do conjunto de posições da dificuldade ↓ */
void adicionaPergunta(PERGUNTAS p, PERGUNTAS *pr)
{
    char dif[12];
    int min=0, max=0, i=0, u;

    strcpy(dif, p.dificuldade);
 
    /* ↓ Estabelece um mínimo e um máximo referente às posições de cada dificuldade  ↓ */
    if(strcmp(dif, "facil") == 0)
    {
        min=0; // Linha 1 a 50 em db.txt
        max=49;
    }
    if(strcmp(dif, "medio") == 0)
    {
        min=50; // Linha 51 a 100 em db.txt
        max=99;
    }
    if(strcmp(dif, "dificil") == 0)
    {
        min=100; // Linha 101 a 150 em db.txt
        max=149;
    }

    i=min;
    while (i <= max && strlen(pr[i].questao) > 0 && (strcmp(pr[i].dificuldade, dif)==0)) // Percorre todas as posições que contenham a dificuldade pretendida
        i++;
    u=N-1;
    /* ↓ Encontrada a última pergunta da dificuldade pretendida, move TODAS as posições que estão à sua frente, uma casa para a frente ↓ */
    while (u >= i && strlen(pr[i].questao )>0)
    {
        pr[u+1] = pr[u]; 
        u--;
    }
    pr[i] = p; // Coloca a pergunta pretendida no espaço que se encontra vazio
}

/*   ↓  Devolve o índice da última pergunta do array de perguntas pr ↓   */
int indice(PERGUNTAS *pr)
{
    int ret = 0;
    int i = 0;

    while (i < N && strlen(pr[i].questao) > 0)
        i++;
    
    if(i==N)
        ret = -1;
    else
        ret = i; // Caso contrário devolve a última posição cheia

    return ret;
}

/*   ↓  Adiciona uma pergunta à primeira posição LIVRE do array de perguntas pr  ↓   */
void adicionaPerguntaIO(PERGUNTAS *pr)
{
    int op, ind = 0;

    do // Está constantemente a adicionar perguntas até o user digitar algum número para além de 1
    {
        ind = indice(pr);
        if (ind == -1)
            printf(" ✘  Atenção! Não pode ter mais de 150 perguntas no total.\n");
        else
        {
            adicionaPergunta(criaPerguntaIO(), pr);
            printf("\n --> Prima 1 para adicionar nova pergunta ou qualquer outro número para sair.\n");
            while (scanf("%d", &op) != 1)
            {
                limpaInput();
                printf(" ✘  Prima 1 para adicionar nova pergunta ou qualquer outro número para sair.\n");
            }
            limpaInput();
            printf("\n");
        }
    } while (op == 1 && ind != -1);
}

/*   ↓  Grava o conteúdo do array de perguntas pr no ficheiro BINÁRIO "fnome"  ↓   */
void gravaBin(PERGUNTAS *pr, char *fnome)
{
    FILE *f = abreFicheiro(fnome, "wb");

    fwrite(pr, sizeof(PERGUNTAS), N, f);

    fechaFicheiro(f, fnome);
}

/*   ↓  Grava o conteúdo do array de perguntas pr no ficheiro de TEXTO "fnome"  ↓   */
void gravaTXT(PERGUNTAS *pr, char *fnome)
{
    FILE *f = abreFicheiro(fnome, "w");

    for (int i = 0; i < N && strlen(pr[i].questao) > 0; i++) // percorre todas as posições do array até encontrar uma questão vazia
        // Imprime no ficheiro o que é pretendido (formatado)
        fprintf(f, "ID %s|QUESTÃO: %s|RESPOSTA CERTA: %s|RESPOSTAS ERRADAS: %s, %s, %s|DIFICULDADE: %s.\n", pr[i].identificador, pr[i].questao, pr[i].respostaCerta, pr[i].respostaErrada1, pr[i].respostaErrada2, pr[i].respostaErrada3, pr[i].dificuldade);
    fechaFicheiro(f, fnome);
}

/*   ↓ Dado um identificador e um array de perguntas, 
devolve o índice do identificador no array  ↓   */
int indiceRemove(char *indentificador, PERGUNTAS *pr)
{
    int i = 0;
    int res = -1;
    char min1[100], min2[100];

    while (i < N && strlen(pr[i].questao) > 0)
    {
        /* A procura é feita em case insensitive */
        minuscula(pr[i].identificador, min1);
        minuscula(indentificador, min2);
        if (strcmp(min1, min2) == 0)
        {
            res = i;
            break;
        }
        i++;
    }
    return res; // res = indice da pergunta com o identificador pedido
                // Se não encontrar res = -1! 
}

/* Remove a pergunta com o identificador 'identificador' do array de perguntas 'pr'.
 * Se existir mais do que uma pergunta com o mesmo nome, remove a primeira
 * Devolve 1 se a pergunta não existir, 0 caso contrario */
int removePergunta(char *identificador, PERGUNTAS *pr)
{
    int i, ret = 0;

    i = indiceRemove(identificador, pr);

    if (i >= 0)
    {
        /* Encontrada a pergunta, move todas as posições que estão à sua frente, uma casa para trás */
        while (i < N - 1 && strlen(pr[i].questao) > 0)
        {
            pr[i] = pr[i + 1];
            i++;
        }
        PERGUNTAS per = {}; // A questão "mais avançada" passa então a ser vazia, para não haver repetição
        pr[i] = per;
    }
    else
        ret = 1; // Não encontrou a pergunta
    return ret;
}

/* Remove a(as) pergunta(s) pretendidas(s) e dá feedback  */
void removePerguntaIO(PERGUNTAS *pr)
{
    int op;
    char pnome[100];
    char *pos;

    do // Vai remover perguntas até que o utilizador digite 1 
    {
        printf("• Escreva o nome do IDENTIFICADOR da pergunta que pretende remover: ");
        fgets(pnome, 100, stdin);
        pos = strchr(pnome, '\n');
        *pos = '\0';
        
        if (removePergunta(pnome, pr) == 1) 
            printf(" ✘  Pergunta Inexistente.\n");
        else
            printf(" ✔ Pergunta relativa ao identificador %s removida com sucesso.\n", pnome);
        printf("\n-> Prima 1 para remover outra pergunta ou qualquer outro número para sair --> ");

        while (scanf("%d", &op) != 1)
        {
            limpaInput();
            printf(" ✘  Prima 1 para remover nova pergunta ou qualquer outro número para sair.\n");
        }
        printf("\n");
        limpaInput();
    } while (op == 1);
}

void linha()
{
    printf("――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――\n");
}

/*   ↓  Cria um jogaor jr, a partir das infos dadas: nome e quantia que ganhou  ↓   */
JOGADOR criaInfoJogador(JOGADOR jr, char *nome, int quantia)
{
    strcpy(jr.nome, nome);
    jr.quantia = quantia;

    return jr;
}

/*Adiciona um jogador 'jr' ao array de jogadores 'jrs' na posicao 'indice' */
void adicionaJogador(JOGADOR jr, int indice, JOGADOR *jrs)
{
    jrs[indice] = jr;
}

/*   ↓  Devolve o índice da última pergunta do array de jogadores jrs ↓   */
int indiceJOGADOR(JOGADOR *jrs)
{
    int ret = 0;
    int i = 0;

    while (i < N && strlen(jrs[i].nome) > 0)
        i++;
    ret = i;

    return ret;
}

/*   ↓  Adiciona um jogador à primeira posição LIVRE do array de jogadores jrs  ↓   */
void adicionaJogadorIO(JOGADOR *jrs, char *nome, int quantia)
{
    JOGADOR jr;
    int ind = 0;

    ind = indiceJOGADOR(jrs);
        
    adicionaJogador(criaInfoJogador(jr, nome, quantia), ind, jrs);
    printf("\n");
}

void gravaTXTJOGADOR(JOGADOR *jrs, char *fnome)
{
    FILE *f = abreFicheiro(fnome, "w");

    for (int i = 0; i < N && strlen(jrs[i].nome) > 0; i++) // percorre todas as posições do array até encontrar um jogador vazio
        // Imprime no ficheiro o que é pretendido (formatado)
        fprintf(f, "Nome: %s\nQuantia: %d\n\n", jrs[i].nome, jrs[i].quantia);

    fechaFicheiro(f, fnome);
}

/*   ↓  Lê as perguntas que estão no ficheiro TEXTO chamado 'fnome'  ↓   */
void leTXTJOGADOR(JOGADOR *jrs, char *fnome)
{
    FILE *f = abreFicheiro(fnome, "r");

    int i = 0;
    /*             ↓  Lê o input formatado através da stream  ↓                       */
    /* Tudo o que estiver no lugar de %[^|], é guardado em jrs[i].nome e em jrs[i].quantia */
    while (fscanf(f, "Nome: %[^\n]\nQuantia: %d\n\n", jrs[i].nome, &jrs[i].quantia) == 2)
        i++; // percorre posições até que não consiga coletar tudo o que é desejado 

    fechaFicheiro(f, fnome);
}

/*   ↓  Sorteia números randoms entre max e min e coloca-os num array resultado de tamanho n ↓  */
void Randoms(int max, int min, int *resultado, int n)
{
    int i, j, num;
    int range = max-min;

    srand(time(0));

    for(i=0; i<n; i++)
    {
        num = (rand() % range+1)+min;
        for(j=0; j<i; j++)
        {
            if(num==resultado[j])
                break;
        }

        if(j == i)
            resultado[i] = num;
        else
            i--;
    }
}

/*   ↓  Junta os elementos dos arrays f, m e d num array final  ↓   */
void juntaArrays(int *f, int *m, int *d, int *final)
{
    int tamanhoFinal = 9, fa=0, me=0, di=0;

    for(int i=0; i<tamanhoFinal; i++)
    {
        if(i>=0 && i<3)
        {
            final[i] = f[fa];
            fa++;
        }
        else if(i>=3 && i<6)
        {
            final[i] = m[me];
            me++;
        }
        else
        {
            final[i] = d[di];
            di++;
        }
    }
}

void tabela()
{
    printf("\n");
    printf("              ┎━━━━━━━━━━━━━━━┓━━━━━━━━━━━━━━┓  \n");
    printf("┎━━━━━━━━━━━━━┃     Nível     ┃    Quantia   ┃  \n");
    printf("┃  Questão 1  ┃     Fácil     ┃     100€     ┃  \n");
    printf("┃  Questão 2  ┃     Fácil     ┃     300€     ┃  \n");
    printf("┃ -Questão 3- ┃    -Fácil-    ┃    -500€-    ┃  \n");
    printf("┃  Questão 4  ┃     Médio     ┃     2000€    ┃  \n");
    printf("┃  Questão 5  ┃     Médio     ┃     3500€    ┃  \n");
    printf("┃ -Questão 6- ┃    -Médio-    ┃    -5000€-   ┃  \n");
    printf("┃  Questão 7  ┃    Difícil    ┃     1000€    ┃  \n");
    printf("┃  Questão 8  ┃    Difícil    ┃    15000€    ┃  \n");
    printf("┃  Questão 9  ┃    Difícil    ┃    20000€    ┃  \n");
    printf("┖━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┚\n");
}

void infos()
{
    printf("\n\t\t\t！ALGUMAS INFORMAÇÕES IMPORTANTES ！\n");
    tabela();
    printf("\n• Na tabela anterior encontram-se as quantias acumuladas consoante o sucesso \n");
    printf("que obtiver ao longo do concurso.\n");
    printf("• Estão também destacadas as questões que contêm os paramares de segurança, ou seja,\n");
    printf("caso acerte as 3 questões fáceis, garante 500€. O mesmo acontece para caso tome a\n");
    printf("melhor decisão quanto às 3 de nível médio, já que garante 5.000€.\n");
    printf("• Pode responder usando letras maiúsculas ou minúsculas.\n\n");
    printf("\t\t\t\t♣ BOA SORTE! ♣");
}
