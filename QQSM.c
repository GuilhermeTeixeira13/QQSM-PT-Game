#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"funcionalidades.h"

int main()
{
    int formatoLeitura, gerirOuiniciar, gerirConcurso, escolha, quantia=0, d[4], m[4], f[4], LinhasPerguntas[12], eliminaCinquenta[2],i=0, suficientes=1, tamanhoNomeJogador, posAjuda, trocaDisponivel = 1, opInvalida=0;
    int numPosPerguntaTXT, resp[4], respAJUDA[4],numResposta, desistiu = 0, tam, garantido=0, valorPorCerta = 0, facilCont=0, medioCont=0, dificilCont=0, numPergunta, cinquentaDisponivel = 1;
    char palavraProcurada[257], nomeJogador[100], dif[20], respostaJogador[10], resposta[10];
    char *pos, ch;

    PERGUNTAS p[N] = {}; // Array de perguntas de tamanho N
    JOGADOR j[1000] = {}; // Array de jogadores (e respetivas quantias ganhas) -> Neste caso 1000 jogadores

    /*   ↓  Pergunta em que formato queremos que o ficheiro das perguntas seja lido  ↓   */
    linha();
    printf("\t\t\t★  - QUEM QUER SER MILIONÁRiO - ★\n");
    linha();
    printf("• Em que formato gostaria que as perguntas fossem lidas?\n\n");
    printf("↪  1. TEXTO\n");
    printf("↪  2. BiNÁRiO\n\n");
    printf("Opção -> ");
    do
    {
        if (scanf("%d", &formatoLeitura) != 1) 
        {
            limpaInput();
            printf(" ✘  Input inválido! Digite algo válido: ");
            continue;
        }
        /*   ↓  Lê o ficheiro das perguntas na forma de texto ou binário  ↓   */
        switch (formatoLeitura)
        {
        case 1:
            leTXT(p, "db.txt");
            break;
        case 2:
            leBin(p, "db.bin");
            break;
        default:
            printf(" ✘  Opção inválida! Digite algo válido: ");
            break;
        }
    }while(formatoLeitura != 1 && formatoLeitura != 2);

    do // Estará sempre a mostrar o menu principal até o user decidir sair do programa (OPÇÃOP 0 NO MENU PRiNCiPAL)
    {
        linha();
        printf("___________________________| ⇒  - MENU PRINCIPAL - ⇐  |_____________________________\n\n");
        printf("• Escolha uma das opções disponíveis: \n\n");
        printf("↪  1. GERIR CONCURSO\n");
        printf("↪  2. INICIAR CONCURSO\n\n");
        printf("↪  0. SAIR\n\n");
        printf("Opção -> ");

        /*   ↓  Faz a verificação do input, só aceitanto 0, 1 ou 2  ↓   */
        while(scanf("%d", &gerirOuiniciar) != 1)
        {
            limpaInput();
            printf(" ✘  input inválido! Digite algo válido: ");
        }
        while(gerirOuiniciar < 0 || gerirOuiniciar > 2)
        {
            limpaInput();
            printf(" ✘  Opção inválida! Digite algo válido: ");
            while(scanf("%d", &gerirOuiniciar) != 1)
            {
                limpaInput();
                printf(" ✘  Input inválido! Digite algo válido: ");
            }
        }
        linha();

        /*   ↓  GERiR CONCURSO  ↓   */
        if(gerirOuiniciar == 1) 
        {
            do
            {
                printf("___________________________| ⇒  - GERiR CONCURSO - ⇐  |_____________________________\n\n");
                printf("• Escolha uma das opções disponíveis: \n\n");
                printf("↪  1. LISTAR QUESTÕES\n");
                printf("↪  2. PROCURAR QUESTÕES\n");
                printf("↪  3. ADICIONAR QUESTÃO\n");
                printf("↪  4. ELIMINAR QUESTÃO\n");
                printf("↪  5. VOLTAR AO MENU PRINCIPAL\n\n");
                printf("Opção -> ");

                /*   ↓  Verifica input, só aceitanto 1, 2, 3, 4 ou 5  ↓   */
                while(scanf("%d", &gerirConcurso) != 1) // CAso o input seja uma letra
                {
                    limpaInput();
                    printf(" ✘  Input inválido! Digite algo válido --> ");
                }
                while(gerirConcurso < 1 || gerirConcurso > 5)
                {
                    limpaInput();
                    printf(" ✘  Opção inválida! Digite algo válido --> ");
                    while(scanf("%d", &gerirConcurso) != 1)
                    {
                        limpaInput();
                        printf(" ✘  Input inválido! Digite algo válido --> ");
                    }
                } 

                /*   ↓  Consoante a opção, executa determinada tarefa (switch)  ↓   */
                switch (gerirConcurso)
                {
                case 1:
                    do
                    {
                        linha();
                        printf("__________________| ⇒  - GERIR CONCURSO / LISTAR QUESTÕES - ⇐  |___________________\n\n");
                        limpaInput();

                        mostraArray(p, N); // Lista as perguntas do array de perguntas de tamanho N
                        escolha = repetirAcao(); // Pergunta ao user se quer repetir a ação ou se quer sair
                    } while (escolha == 1);
                    break;
                case 2:
                    do
                    {
                        linha();
                        printf("__________________| ⇒  - GERIR CONCURSO / PROCURAR QUESTÕES - ⇐  |__________________\n\n");
                        limpaInput();

                        /*   ↓  Pede uma palavra/frase e vai procurá-la no array de perguntas  ↓   */
                        printf("• Escreva uma palavra / frase e será remetido para a(s) pergunta(s) que a(s) contêm.\n");
                        printf("🔎 -> ");
                        fgets(palavraProcurada, 100, stdin);
                        pos = strchr(palavraProcurada, '\n');
                        *pos = '\0';

                        printf("\n");
                        indicePergunta(palavraProcurada, p); // Mostra todas as perguntas que contêm a letra/palavra/frase pretendida
                        escolha = repetirAcao(); // Pergunta ao user se quer repetir a ação ou se quer sair
                    } while (escolha == 1);
                    break;
                case 3:
                    facilCont = 0, medioCont = 0, dificilCont = 0;

                    linha();
                    printf("_________________| ⇒  - GERIR CONCURSO / ADICIONAR QUESTÕES - ⇐  |__________________\n\n");
                    printf("• Nesta secção pode criar novas questões, adicionando-as ao programa.\n");
                    printf("• Das 150 perguntas no total, deve haver 50 de cada dificuldade.\n\n");
                    printf("   Feita a contagem, relembramos que existem:\n");

                    /*   ↓  Avisa o user sobre quantas perguntas de cada dificuldade já estão "registadas" depois d efazer a contagem ↓   */
                    for(i=0; i<N && strlen(p[i].questao)>0; i++)
                    {
                        if(strcmp("facil", p[i].dificuldade) == 0)
                            facilCont++;
                        if(strcmp("medio", p[i].dificuldade) == 0)
                            medioCont++;
                        if(strcmp("dificil", p[i].dificuldade) == 0)
                            dificilCont++;
                    }

                    printf("  ➙  %d FÁCEIS\n", facilCont);
                    printf("  ➙  %d MÉDIAS\n", medioCont);
                    printf("  ➙  %d DIFÍCEIS\n\n", dificilCont);
                    limpaInput();

                    adicionaPerguntaIO(p); // Adiciona pergunta(s)

                    /*   ↓  Grava as alterações cometidas↓   */
                    gravaBin(p, "db.bin"); 
                    gravaTXT(p, "db.txt");
                    break;
                case 4:
                    linha();
                    printf("__________________| ⇒  - GERIR CONCURSO / ELIMINAR QUESTÕES - ⇐  |__________________\n\n");
                    printf("❗ -> CASO O IDENTIFICADOR SE REPITA, SERÁ REMOVIDA A PERGUNTA CUJO MESMO APARECER\n");
                    printf("  PRIMEIRO NA LISTA (EM CASO DE DÚVIDA VERIFICAR OPÇÃO 1.LISTAR QUESTÕES).\n\n");
                    limpaInput();

                    removePerguntaIO(p); // Remove pergunta(s) depois do user digitar o identificador da mesma 

                    /*   ↓  Grava as alterações cometidas↓   */
                    gravaBin(p, "db.bin"); 
                    gravaTXT(p, "db.txt");
                default:
                    break;
                }
                if(gerirConcurso != 5)
                    linha();
            }while(gerirConcurso != 5);
        }


        /*   ↓  INICIAR CONCURSO  ↓   */
        if(gerirOuiniciar == 2)
        {
            i=0, desistiu = 0, numResposta=0, quantia = 0, facilCont=0, medioCont=0, dificilCont=0, suficientes = 0, trocaDisponivel = 1, cinquentaDisponivel = 1;
            
            leTXTJOGADOR(j, "resultados.txt"); // Lê o que está no ficheiro resultados.txt (histórico de jogadores e quantias ganhas)
            limpaInput();

            printf("________________|  ⇒  - CONCURSO - QUEM QUER SER MILIONÁRIO - ⇐   |_________________\n\n\n");

            /*   ↓  Pede o nome do jogador ↓   */
            printf("• NOME DO JOGADOR: ");
            fgets(nomeJogador, 257, stdin);
            pos = strchr(nomeJogador, '\n');
            *pos = '\0';
            tamanhoNomeJogador = strlen(nomeJogador);
            while(tamanhoNomeJogador == 0)
            {
                printf(" ✘  Nome vazio! Indique outro: ");
                fgets(nomeJogador, 257, stdin);
                pos = strchr(nomeJogador, '\n');
                *pos = '\0';
                tamanhoNomeJogador = strlen(nomeJogador);
            }

            /*   ↓ Mostra algumas infos importantes para que o user perceba o funcionamento do jogo ↓   */
            infos();

            /* Conta quantas questões de nível fácil/médio/difícil existem */
            for(i=0; i<N && strlen(p[i].questao)>0; i++)
            {
                if(strcmp("facil", p[i].dificuldade) == 0)
                    facilCont++;
                if(strcmp("medio", p[i].dificuldade) == 0)
                    medioCont++;
                if(strcmp("dificil", p[i].dificuldade) == 0)
                    dificilCont++;
            }

            if(facilCont > 3  && medioCont > 3 && dificilCont > 3) // Só deixa começar o jogo se houver mais de 2 perguntas de cada categoria
            {    
                suficientes = 1;

                /* Sorteia as linhas do db.txt (dentro das perguntas possíveis existentes), q correspondem às perguntas que farão parte do concurso */
                /* 3 fáceis + 1 fácil de ajuda //  3 médias + 1 média de ajuda // 3 difícil + 1 difícil de ajuda */

                Randoms(facilCont, 1, f, 4); 
                Randoms(facilCont+medioCont, facilCont+1, m, 4); 
                Randoms(facilCont+medioCont+dificilCont, facilCont+medioCont+1, d, 4);  
                juntaArrays(f, m, d, LinhasPerguntas); // Junta todas as linhas das perguntas no array LinhasPerguntas --> Exemplo: 4 36 17 26 // 56 93 68 71 // 111 102 143 144 

                //Tirar comentário se se quiser ver quais foram as linhas referentes às perguntas escolhidas
                /*printf("As perguntas (db.txt) que foram 'sorteadas' foram as referentes às seguintes linhas: ");
                for(int p=0; p<12; p++)
                    printf("%d ", LinhasPerguntas[p]);*/

                printf("\n\n");   
                linha();

                i=0;
                while(i<11 && desistiu != 1 && numResposta == 0) // Executa o loop enquanto o número de perguntas for menor que nove (casa 11) e o jogador não tiver desistido e a resposta estiver correta, 
                {   
                    numPosPerguntaTXT = LinhasPerguntas[i]-1; // A posição da pergunta no array de pergundas é igual ao número da linha - 1 
                    ch = 65;

                     /*   ↓  São feitos alguns ajustes para o número da pergunta aparecer certo  ↓   */
                    if(i >= 0 && i<= 2)
                        numPergunta = i+1;
                    else if(i >= 4 && i<= 6)
                        numPergunta = i;
                    else
                        numPergunta = i-1;

                    /*   ↓  Consoante o patamar em que se está, são definidos diferentes valores para o dinheiro garantido quando o jogador perde e para o valor ganho por resposta certa  ↓   */
                    if(numResposta == 0) // O 0 está associado com a resposta certa
                    {
                        if(numPergunta == 1)
                        {
                            garantido = 0;
                            valorPorCerta = 100;
                        }
                        if(numPergunta == 2)
                            valorPorCerta = 200;
                        if(numPergunta == 4)
                        {
                            printf("❰ PRIMEIRO PATAMAR DE SEGURANÇA -> 500 EUROS ❱\n");
                            garantido = 500;
                            valorPorCerta = 1500;
                        }
                        if(numPergunta == 7)
                        {
                            printf("❰ SEGUNDO PATAMAR DE SEGURANÇA -> 5000 EUROS ❱\n");
                            garantido = 5000;
                            valorPorCerta = 5000;
                        }

                        quantia += valorPorCerta; // à quantia é adicionado o valor da respetiva resposta certa
                    }
                    printf("\n");

                    /*   ↓  SUMÁRiO DO JOGO  ↓   */
                    printf("➙  SALDO ATUAL: %d EUROS.\n", quantia-valorPorCerta);
                    printf("➙  SE ACERTAR FICARÁ COM: %d euros\n", quantia);
                    printf("➙  SE ERRAR/DESISTIR FICARÁ COM: %d euros\n\n", garantido);
                    printf("* AJUDAS DISPONÍVEIS *\n");
                    printf(" ➙ TROCA DE PERGUNTA: %d\n", trocaDisponivel);
                    printf(" ➙ AJUDA DO 50:50: %d\n\n", cinquentaDisponivel);

                    /*   ↓  TRANSFORMAÇÃO PARA MAiÚSCULA (ESTÉTiCA)  ↓   */
                    if(strcmp(p[numPosPerguntaTXT].dificuldade, "facil") == 0)
                        strcpy(dif, "FÁCIL");
                    if(strcmp(p[numPosPerguntaTXT].dificuldade, "medio") == 0)
                        strcpy(dif, "MÉDIO");
                    if(strcmp(p[numPosPerguntaTXT].dificuldade, "dificil") == 0)
                        strcpy(dif, "DIFÍCIL");

                    printf("• PERGUNTA %d (%s): %s\n", numPergunta, dif, p[numPosPerguntaTXT].questao); // Faz a pergunta
        
                    Randoms(3, -1, resp, 4); // sorteia 4 números de 0 a 3 e coloca no array resp
                    
                    printf("\n");


                    /* A cada resposta possível (A,B,C,D) é atribuido cada número do array resp (constituido por 0, 1, 2, 3) */
                    /*
                        A - 1 (errada1)
                        B - 2 (errada2)
                        C - 0 (certa)
                        D - 3 (errada3)
                    
                    */
                    for(int k=0; k<4; k++)
                    {
                        printf("%c. ", ch);
                        /*Tirar comentário se pretender ver a ordem sorteada para as perguntas (0 = resposta certa)
                        printf("%d", resp[k]);*/
                        if(resp[k] == 0)
                            printf("%s", p[numPosPerguntaTXT].respostaCerta); // na letra que estiver associada com o número 0, é afixada a resposta certa
                        else if(resp[k] == 1)
                            printf("%s", p[numPosPerguntaTXT].respostaErrada1); // nas restantes letras que estievrem associadas com os restantes números (1, 2, 3), são imprimidas respostas erradas
                        else if(resp[k] == 2)                               
                            printf("%s", p[numPosPerguntaTXT].respostaErrada2);
                        else if(resp[k] == 3)
                            printf("%s", p[numPosPerguntaTXT].respostaErrada3);
                        printf("\n");
                        ch += 1;
                    }
                    printf("\nX. CASO QUEIRA DESISTIR\n");
                    if(trocaDisponivel == 1)
                        printf("1. CASO QUEIRA TROCAR DE PERGUNTA\n");
                    if(cinquentaDisponivel == 1)
                        printf("2. CASO QUEIRA AJUDA DO 50:50\n\n");

                    /*   ↓  Faz a validação da opção escolhida pelo user, aceitanto apenas A, B, C, D ou X (Case insensitive para facilitar o user) ↓   */
                    do
                    {
                        printf("↪ OPÇÃO: ");
                        fgets(resposta, 257, stdin);
                        pos = strchr(resposta, '\n');
                        *pos = '\0';
                        tam = strlen(resposta);
                        minuscula(resposta, respostaJogador);
                        opInvalida = 0;
                        if (tam == 0)
                            printf(" ✘ Opção vazia!!\n");
                        if(trocaDisponivel == 1 && cinquentaDisponivel == 1)
                        {
                            if(strcmp(respostaJogador, "a") != 0 && strcmp(respostaJogador, "b") != 0 && strcmp(respostaJogador, "c") != 0 && strcmp(respostaJogador, "d") != 0 && strcmp(respostaJogador, "x") != 0 && strcmp(respostaJogador, "1") != 0 && strcmp(respostaJogador, "2") != 0) 
                            {    
                                opInvalida = 1;
                                printf(" ✘ Opção inválida!!\n");
                            }
                        }
                        else if(trocaDisponivel == 1 && cinquentaDisponivel == 0)
                        {
                            if(strcmp(respostaJogador, "a") != 0 && strcmp(respostaJogador, "b") != 0 && strcmp(respostaJogador, "c") != 0 && strcmp(respostaJogador, "d") != 0 && strcmp(respostaJogador, "x") != 0 && strcmp(respostaJogador, "1") != 0) 
                            {    
                                opInvalida = 1;
                                printf(" ✘ Opção inválida!!\n");
                            }
                        }
                        else if(trocaDisponivel == 0 && cinquentaDisponivel == 1)
                        {
                            if(strcmp(respostaJogador, "a") != 0 && strcmp(respostaJogador, "b") != 0 && strcmp(respostaJogador, "c") != 0 && strcmp(respostaJogador, "d") != 0 && strcmp(respostaJogador, "x") != 0 && strcmp(respostaJogador, "2") != 0) 
                            {    
                                opInvalida = 1;
                                printf(" ✘ Opção inválida!!\n");
                            }
                        }
                        else
                        {
                            if(strcmp(respostaJogador, "a") != 0 && strcmp(respostaJogador, "b") != 0 && strcmp(respostaJogador, "c") != 0 && strcmp(respostaJogador, "d") != 0 && strcmp(respostaJogador, "x") != 0) 
                            {    
                                opInvalida = 1;
                                printf(" ✘ Opção inválida!!\n");
                            }
                        }
                    } while (opInvalida == 1);
                    opInvalida = 0;

                    /*   ↓  VERiFiCA-SE QUAL É O NÚMERO ASSOCiADO À LETRA RESPONDiDA E, CONSEQUENTEMENTE SE É OU NÃO A RESPOSTA CERTA  ↓   */
                    // Se numResposta = 0, então o user deu a resposta certa!
                    if(strcmp(respostaJogador, "a") == 0)
                        numResposta = resp[0]; 
                    else if(strcmp(respostaJogador, "b") == 0)
                        numResposta = resp[1];
                    else if(strcmp(respostaJogador, "c") == 0)
                        numResposta = resp[2];
                    else if(strcmp(respostaJogador, "d") == 0)
                        numResposta = resp[3];
                    else if(strcmp(respostaJogador, "1") == 0) // TROCA DE PERGUNTA
                    {
                        // NOTA: A explicação para o que está dentro deste else if é semelhante ao que foi feito acima, portanto, só que difere bastante será comentado

                        ajudaTrocaDePergunta:
                        trocaDisponivel = 0; // A partir do momento que esta ajuda (TROCA) é usada não se pode voltar a usar a mesma

                        if(i >= 0 && i<= 2) // Se estivermos em alguma pergunda fácil, ao pedir ajuda, vamos buscar a pergunta que está na posição 3 do array
                            posAjuda = 3;
                        else if(i >= 4 && i<= 6)
                            posAjuda = 7;
                        else
                            posAjuda = 11;

                        numPosPerguntaTXT = LinhasPerguntas[posAjuda] - 1;

                        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                        printf("\n* AJUDA - TROCA DE PERGUNTA *\n\n");
                        printf("➙  SALDO ATUAL: %d EUROS.\n", quantia-valorPorCerta);
                        printf("➙  SE ACERTAR FICARÁ COM: %d euros\n", quantia);
                        printf("➙  SE ERRAR/DESISTIR FICARÁ COM: %d euros\n\n", garantido);
                        printf("* AJUDAS DISPONÍVEIS *\n");
                        printf(" ➙ TROCA DE PERGUNTA: %d\n", trocaDisponivel);
                        printf(" ➙ AJUDA DO 50:50: %d\n\n", cinquentaDisponivel);
                        printf("• PERGUNTA %d (%s): %s\n", numPergunta, dif, p[numPosPerguntaTXT].questao); 
                        
                        Randoms(3, -1, respAJUDA, 4);

                        ch = 65;
                        for(int k=0; k<4; k++)
                        {
                            printf("%c. ", ch);
                            /* Tirar comentário se pretender ver a ordem sorteada para as perguntas (0 = resposta certa)
                            printf("%d ", respAJUDA[k]);*/
                            if(respAJUDA[k] == 0)
                                printf("%s", p[numPosPerguntaTXT].respostaCerta); 
                            else if(respAJUDA[k] == 1)
                                printf("%s", p[numPosPerguntaTXT].respostaErrada1); 
                            else if(respAJUDA[k] == 2)                               
                                printf("%s", p[numPosPerguntaTXT].respostaErrada2);
                            else if(respAJUDA[k] == 3)
                                printf("%s", p[numPosPerguntaTXT].respostaErrada3);
                            printf("\n");
                            ch += 1;
                        }
                        printf("\nX. CASO QUEIRA DESISTIR\n");
                        if(cinquentaDisponivel == 1)
                            printf("2. CASO QUEIRA AJUDA DO 50:50\n");

                        do
                        {
                            printf("\n↪ OPÇÃO: ");
                            fgets(resposta, 257, stdin);
                            pos = strchr(resposta, '\n');
                            *pos = '\0';
                            tam = strlen(resposta);
                            minuscula(resposta, respostaJogador);
                            opInvalida = 0;
                            if (tam == 0)
                                printf(" ✘ Opção vazia!!\n");
                            if(trocaDisponivel == 1 && cinquentaDisponivel == 1)
                            {
                                if(strcmp(respostaJogador, "a") != 0 && strcmp(respostaJogador, "b") != 0 && strcmp(respostaJogador, "c") != 0 && strcmp(respostaJogador, "d") != 0 && strcmp(respostaJogador, "x") != 0 && strcmp(respostaJogador, "1") != 0 && strcmp(respostaJogador, "2") != 0) 
                                {    
                                    opInvalida = 1;
                                    printf(" ✘ Opção inválida!!\n");
                                }
                            }
                            else if(trocaDisponivel == 1 && cinquentaDisponivel == 0)
                            {
                                if(strcmp(respostaJogador, "a") != 0 && strcmp(respostaJogador, "b") != 0 && strcmp(respostaJogador, "c") != 0 && strcmp(respostaJogador, "d") != 0 && strcmp(respostaJogador, "x") != 0 && strcmp(respostaJogador, "1") != 0) 
                                {    
                                    opInvalida = 1;
                                    printf(" ✘ Opção inválida!!\n");
                                }
                            }
                            else if(trocaDisponivel == 0 && cinquentaDisponivel == 1)
                            {
                                if(strcmp(respostaJogador, "a") != 0 && strcmp(respostaJogador, "b") != 0 && strcmp(respostaJogador, "c") != 0 && strcmp(respostaJogador, "d") != 0 && strcmp(respostaJogador, "x") != 0 && strcmp(respostaJogador, "2") != 0) 
                                {    
                                    opInvalida = 1;
                                    printf(" ✘ Opção inválida!!\n");
                                }
                            }
                            else
                            {
                                if(strcmp(respostaJogador, "a") != 0 && strcmp(respostaJogador, "b") != 0 && strcmp(respostaJogador, "c") != 0 && strcmp(respostaJogador, "d") != 0 && strcmp(respostaJogador, "x") != 0) 
                                {    
                                    opInvalida = 1;
                                    printf(" ✘ Opção inválida!!\n");
                                }
                            }
                        } while (opInvalida == 1);
                        opInvalida = 0;

                        if(strcmp(respostaJogador, "a") == 0)
                            numResposta = respAJUDA[0]; 
                        else if(strcmp(respostaJogador, "b") == 0)
                            numResposta = respAJUDA[1];
                        else if(strcmp(respostaJogador, "c") == 0)
                            numResposta = respAJUDA[2];
                        else if(strcmp(respostaJogador, "d") == 0)
                            numResposta = respAJUDA[3];
                        else if(strcmp(respostaJogador, "2") == 0)
                            goto ajudaCinquenta;
                        else
                            desistiu = 1;
                    }
                    else if(strcmp(respostaJogador, "2") == 0)
                    {
                        ajudaCinquenta:
                        cinquentaDisponivel = 0;

                        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                        printf("\n* AJUDA - 50:50 *\n\n");
                        printf("➙  SALDO ATUAL: %d EUROS.\n", quantia-valorPorCerta);
                        printf("➙  SE ACERTAR FICARÁ COM: %d euros\n", quantia);
                        printf("➙  SE ERRAR/DESISTIR FICARÁ COM: %d euros\n\n", garantido);
                        printf("* AJUDAS DISPONÍVEIS *\n");
                        printf(" ➙ TROCA DE PERGUNTA: %d\n", trocaDisponivel);
                        printf(" ➙ AJUDA DO 50:50: %d\n\n", cinquentaDisponivel);
                        printf("• PERGUNTA %d (%s): %s\n", numPergunta, dif, p[numPosPerguntaTXT].questao);

                        Randoms(3, 0, eliminaCinquenta, 2); // Sorteia 2 números do conjunto {1, 2, 3}, que serão 2 das 3 respostas erradas a eliminar

                        ch = 65;
                        for(int k=0; k<4; k++)
                        {
                            printf("%c. ", ch);
                            /* Tirar comentário se pretender ver a ordem sorteada para as perguntas (0 = resposta certa)
                            printf("%d ", resp[k]);*/
                            if(resp[k] == 0)
                                printf("%s", p[numPosPerguntaTXT].respostaCerta); 
                            else if(resp[k] == 1)
                            {
                                if(estaNoArray(1, eliminaCinquenta, 2) == 1) // Se 1 foi sorteado, então elimina-se a resposta errada 1
                                    printf(" ");
                                else
                                    printf("%s", p[numPosPerguntaTXT].respostaErrada1); 
                            }
                            else if(resp[k] == 2)    
                            {
                                if(estaNoArray(2, eliminaCinquenta, 2) == 1) // Se 2 foi sorteado, então elimina-se a resposta errada 2
                                    printf(" ");
                                else
                                    printf("%s", p[numPosPerguntaTXT].respostaErrada2);
                            }                           
                            else if(resp[k] == 3)
                            {
                                if(estaNoArray(3, eliminaCinquenta, 2) == 1) // Se 3 foi sorteado, então elimina-se a resposta errada 3
                                    printf(" ");
                                else
                                    printf("%s", p[numPosPerguntaTXT].respostaErrada3);
                            }
                            printf("\n");
                            ch += 1;
                        }
                        printf("\nX. CASO QUEIRA DESISTIR\n");
                        if(trocaDisponivel == 1)
                            printf("1. CASO QUEIRA TROCAR DE PERGUNTA\n");

                        do
                        {
                            printf("\n↪ OPÇÃO: ");
                            fgets(resposta, 257, stdin);
                            pos = strchr(resposta, '\n');
                            *pos = '\0';
                            tam = strlen(resposta);
                            minuscula(resposta, respostaJogador);
                            opInvalida = 0;
                            if (tam == 0)
                                printf(" ✘ Opção vazia!!\n");
                            if(trocaDisponivel == 1 && cinquentaDisponivel == 1)
                            {
                                if(strcmp(respostaJogador, "a") != 0 && strcmp(respostaJogador, "b") != 0 && strcmp(respostaJogador, "c") != 0 && strcmp(respostaJogador, "d") != 0 && strcmp(respostaJogador, "x") != 0 && strcmp(respostaJogador, "1") != 0 && strcmp(respostaJogador, "2") != 0) 
                                {    
                                    opInvalida = 1;
                                    printf(" ✘ Opção inválida!!\n");
                                }
                            }
                            else if(trocaDisponivel == 1 && cinquentaDisponivel == 0)
                            {
                                if(strcmp(respostaJogador, "a") != 0 && strcmp(respostaJogador, "b") != 0 && strcmp(respostaJogador, "c") != 0 && strcmp(respostaJogador, "d") != 0 && strcmp(respostaJogador, "x") != 0 && strcmp(respostaJogador, "1") != 0) 
                                {    
                                    opInvalida = 1;
                                    printf(" ✘ Opção inválida!!\n");
                                }
                            }
                            else if(trocaDisponivel == 0 && cinquentaDisponivel == 1)
                            {
                                if(strcmp(respostaJogador, "a") != 0 && strcmp(respostaJogador, "b") != 0 && strcmp(respostaJogador, "c") != 0 && strcmp(respostaJogador, "d") != 0 && strcmp(respostaJogador, "x") != 0 && strcmp(respostaJogador, "2") != 0) 
                                {    
                                    opInvalida = 1;
                                    printf(" ✘ Opção inválida!!\n");
                                }
                            }
                            else
                            {
                                if(strcmp(respostaJogador, "a") != 0 && strcmp(respostaJogador, "b") != 0 && strcmp(respostaJogador, "c") != 0 && strcmp(respostaJogador, "d") != 0 && strcmp(respostaJogador, "x") != 0) 
                                {    
                                    opInvalida = 1;
                                    printf(" ✘ Opção inválida!!\n");
                                }
                            }
                        }while (opInvalida == 1);
                        opInvalida = 0;

                        if(strcmp(respostaJogador, "a") == 0)
                            numResposta = resp[0]; 
                        else if(strcmp(respostaJogador, "b") == 0)
                            numResposta = resp[1];
                        else if(strcmp(respostaJogador, "c") == 0)
                            numResposta = resp[2];
                        else if(strcmp(respostaJogador, "d") == 0)
                            numResposta = resp[3];
                        else if(strcmp(respostaJogador, "1") == 0)
                            goto ajudaTrocaDePergunta;
                        else
                            desistiu = 1;
                    }
                    else
                        desistiu = 1;

                    printf("\n");
                    linha();
                    
                    // Saltam-se as perguntas que estão "guardadas" para a ajuda da TROCA DE PERGUNTA, a não ser que o user decida usar essa mesma ajuda
                    if (i == 2)
                        i = 4;
                    else if (i == 6)
                        i = 8;
                    else
                        i++;
                }
            }
            printf("\n");

            /*   ↓  Imprime mensangens consoante rumo do jogo  ↓   */
            if(desistiu == 1)
            {
                quantia = garantido;
                printf("➤  %s DESISTIU. LEVA PARA CASA: %d EUROS\n", nomeJogador, garantido);
                printf("✓  RESPOSTA CERTA: '%s'.\n", p[numPosPerguntaTXT].respostaCerta);
            }
            else if(numResposta != 0)
            {
                quantia = garantido;
                printf("➤  %s ERROU A PERGUNTA. LEVA PARA CASA: %d EUROS\n", nomeJogador, garantido);
                printf("✓  RESPOSTA CERTA: '%s'.\n", p[numPosPerguntaTXT].respostaCerta);
            }
            else if(suficientes == 0)
            {
                linha();
                printf("\n➤  NÃO HÁ PERGUNTAS SUFICIENTES PARA INICIAR O CONCURSO (MÍNIMO é 4 DE CADA DIFICULDADE)!\n");
            }
            else
                printf(" ♛  PARABÉNS, %s! GANHOU O PRÉMIO MÁXIMO! RECEBE: 20.000 EUROS !!! ♛\n", nomeJogador);
            
            adicionaJogadorIO(j, nomeJogador, quantia);
            gravaTXTJOGADOR(j, "resultados.txt");
        }
    }while(gerirOuiniciar != 0);

    printf("*\t\t\t     Trabalho elaborado por:\t\t\t\t   *\n");
    printf("\t        Guilherme Teixeira (45667) e Marco Bernardes (45703)\n");
    printf("\t     ENGENHARIA INFORMÁTICA - PROGRAMAÇÃO - 1ºANO - 2020/2021\n");
    linha();

    return 0;
}