//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>

/*------------------------------------------------------------------------------------------------------------*/
//Constantes

#define tamNome 100
#define tamData 10
#define tamCPF 11
#define tamGenero 3
#define tamAlunos 10000
#define tamProfessores 100
#define tamDisciplinas 1000

/*------------------------------------------------------------------------------------------------------------*/
//Structs

//Data
typedef struct {
    int dia;
    int mes;
    int ano;
} data;

//Cadastro dos alunos
typedef struct {
    long long int matricula;
    char nome[tamNome];
    char CPF[tamCPF + 1]; //+1 para o terminador nulo
    char genero[3]; //+1 para o terminador nulo
    data nascimento;
} listaAlunos;

listaAlunos aluno[tamAlunos];

//Cadastro dos professores
typedef struct {
    long long int matricula;
    char nome[tamNome];
    char CPF[tamCPF + 1]; //+1 para o terminador nulo
    char genero[3]; //+1 para o terminador nulo
    data nascimento;
} listaProfessores;

listaProfessores professor[tamProfessores];

//Cadastro das disciplinas
typedef struct {
    long long int matricula;
    char *codigo; //Aloca��o din�mica
    int semestre;
} listaDisciplinas;

listaDisciplinas disciplina[tamDisciplinas];

/*------------------------------------------------------------------------------------------------------------*/
//Subfun��es

//Limpa a tela
void limparTela() {
    #ifdef _WIN32
        system("cls"); //Windows
    #else
        system("clear"); //Linux
    #endif
}

//Valida a matr�cula
int validarMatricula (long long int matricula, long long int maxMatricula, int tamMatricula) {
    long long int auxMatricula = matricula;
    int digMatricula = 0, flagMatricula = 0;

    //Calcula a quantidade de d�gitos da matr�cula informada
    while (auxMatricula > 0){
        auxMatricula /= 10; //Remove o �ltimo d�gito
        digMatricula++; //Qtd de d�gitos da m�tricula informada
    }

    //Valida��o
    if (!(matricula >= 0 && matricula <= maxMatricula && digMatricula == tamMatricula)){
        flagMatricula = 1;
    }
    return flagMatricula;
}

//Valida o nome
int validarNome(char nome[tamNome]) {
    int len = strlen(nome);
    int flagNome = 0;

    // Verifica se o nome n�o est� vazio
    if (len == 0) {
        printf("Nome n�o pode estar vazio.\n");
        return 1;  //Retorna 1 para indicar erro
    }

    for (int i = 0; i < len; i++){
        //Permite letras, espa�os e caracteres acentuados
        if (!(isalpha(nome[i]) || nome[i] == ' ')) {
            flagNome = 1; //Nome inv�lido
            break;
        }
    }
    return flagNome;
}

//Verifica se o ano � bissexto
int bissexto(int ano) {
    if(((ano % 4 == 0) && (ano % 100 != 0)) || (ano % 400 == 0)){
        return 1; //� bissexto
    }
    else {
        return 0; //N�o � bissexto
    }
}

//Valida a data de nascimento
int validarData(int dia, int mes, int ano) {
    int flagBissexto = bissexto(ano);
    int diasMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    //Valida o ano
    if (ano < 1900 || ano > 2100) {
        return 1; //Ano inv�lido
    }

    //Valida o m�s
    if (mes < 1 || mes > 12) {
        return 1; //M�s inv�lido
    }

    //Atualiza a qtd de dias em fevereiro se o ano for bissexto
    if (flagBissexto == 1) {
        diasMes[1] = 29; //Fevereiro
    }

    //Valida o dia
    if (dia < 1 || dia > diasMes[mes - 1]) {
        return 1; //Dia inv�lido
    }

    return 0; //Data v�lida
}

//Valida o CPF
int validarCPF (char CPF[tamCPF + 1]) { //+1 para o terminador nulo
    int digCPF = 0;

    //Quantidade de d�gitos do CPF
    digCPF = strlen(CPF);

    //Verifica se o CPF s� cont�m n�meros
    for (int i = 0; i < tamCPF; i++) {
        if (!(CPF[i] >= '0' && CPF[i] <= '9')) {
            return 1; //CPF inv�lido (n�o cont�m apenas n�meros)
        }
    }

    //Verifica se o CPF tem 11 d�gitos
    if (digCPF != 11) {
        return 1; //CPF inv�lido
    }  
    
    //Verifica se todos os d�gitos s�o iguais
    int todosIguais = 1;
    for (int i = 1; i < 11; i++) {
        if (CPF[i] != CPF[0]) {
            todosIguais = 0;
            break;
        }
    }
    if (todosIguais == 1) return 1;

    //Verifica o 10� d�gito
    int soma1 = 0;
    for (int i = 0; i < 9; i++) { //Percorre do 1� ao 9� d�gito
        soma1 += (CPF[i] - '0') * (10 - i);
    }
    int resto1 = soma1 % 11;

    if (!((resto1 < 2 && CPF[9] == '0') || (CPF[9] == (11 - resto1))))
        return 1; //CPF inv�lido

    //Verifica o 11� d�gito
    int soma2 = 0;
    for (int i = 0; i < 10; i++) { //Percorre do 1� ao 10� d�gito
        soma2 += (CPF[i] - '0') * (11 - i);
    }
    int resto2 = soma2%11;

    if (!((resto2 < 2 && CPF[10] == '0') || (CPF[10] == (11 - resto2)))) {
        return 1; //CPF inv�lido
    }
        
    return 0; //CPF v�lido
}

//Valida a identidade de g�nero
int validarGenero(char genero[tamGenero]) {
    if (!(strcmp(genero, "M") == 0 || strcmp(genero, "F") == 0 || strcmp(genero, "NB") == 0 || strcmp(genero, "ND") == 0)) {
        return 1; //G�nero inv�lido
    }
    return 0; //G�nero v�lido
}

/*------------------------------------------------------------------------------------------------------------*/
//Fun��o principal
int main (){

    //Configurando a codifica��o de caracteres
    setlocale(LC_ALL, "Portuguese"); //Windows
    //setlocale(LC_ALL, "pt_BR.UTF-8"); //Linux

    //Declara��es
    int opcao;
    int tamCodigo = 0;
    long long int maxMatricula; //Maior n�mero que a matr�cula pode ter (Ex.: 99999999999)
    int contAluno = 0, contProfessor = 0, contDisciplina = 0;

    //Solicita ao usu�rio a maior matr�cula poss�vel
    printf("\nQual a maior matr�cula poss�vel para uma pessoa? (Ex.: 9999999)\n");
    scanf("%lld", &maxMatricula);

    //Calcula a quantidade de d�gitos da matr�cula padr�o
    long long int auxMatricula = maxMatricula;
    int tamMatricula = 0; //Qtd de d�gitos
    while (auxMatricula > 0){
        auxMatricula /= 10; //Remove o �ltimo d�gito
        tamMatricula++; //Qtd de d�gitos da matr�cula padr�o
    }

    //Solicita ao usu�rio o tamanho padr�o do c�digo de uma disciplina
    /*printf("Quantos caracteres tem o c�digo de uma disciplina?\n");
    scanf("%d", &tamCodigo);*/

    //Alocando dinamicamente o tamanho do vetor c�digo
    for (int i = 0; i < tamDisciplinas; i++){
        //"(char*)" converte o ponteiro do tipo void*, retornado por malloc, para um ponteiro tipo char, mesmo tipo do campo "codigo"
        disciplina[i].codigo = (char*)malloc(tamCodigo * sizeof(char));
    }

    limparTela();

    do {
        //Menu de op��es
        printf("### Menu principal ###");
        printf("\nInforme o n�mero da op��o desejada: ");
        printf("\n0 - Sair");
        printf("\n1 - Alunos");
        printf("\n2 - Professores");
        printf("\n3 - Disciplinas\n");
    
        //Entrada de dados: opc�o
        scanf("%d",&opcao);

        limparTela();

        //Switch 1
        switch (opcao){

            case 0: {
                printf("Programa encerrado.");
                return 1;
            }
            
            //Alunos
            case 1: {
                int opcaoAluno;
                
                do{
                    //Menu de op��es
                    printf("### M�dulo Alunos ###");
                    printf("\nInforme o n�mero da op��o desejada: ");
                    printf("\n0 - Voltar ao menu anterior");
                    printf("\n1 - Cadastrar aluno");
                    printf("\n2 - Listar aluno");
                    printf("\n3 - Atualizar aluno");
                    printf("\n4 - Excluir aluno");
                    printf("\n");
                    
                    //Entrada de dados: opc�o do m�dulo de alunos
                    scanf("%d",&opcaoAluno);
                    
                    limparTela();
    
                    //Switch 2
                    switch(opcaoAluno){

                        //Voltar ao menu anterior
                        case 0: {
                            limparTela();
                            break;
                        } //Fim do switch 2, case 0: voltar ao menu anteior

                        //Inserir aluno
                        case 1: {
                            
                            int achou = 0; //Flag
                            
                            printf("### M�dulo Alunos - Inserir aluno ###\n");

                            int flagMatricula = 0;
                            long long int matricula;
                            //Recebe e valida a matr�cula
                            do {
                                printf("Informe a matr�cula do aluno: ");
                                scanf("%lld", &matricula);
                                flagMatricula = validarMatricula(matricula, maxMatricula, tamMatricula);
                                //printf("%d", flagMatricula);

                                if (flagMatricula != 0)
                                    printf("\nMatr�cula inv�lida.\n");
                            } while (flagMatricula != 0);
                            
                            //Lista de alunos cheia
                            if (contAluno > tamAlunos){
                                printf("\nCadastro de alunos cheio.\n");
                                system("pause");
                                limparTela();
                            }
                            
                            //Lista de alunos n�o cheia
                            else{
                                //Verifica se a matr�cula j� est� cadastrada
                                for (int i = 0; i < contAluno; i++){
                                    if (matricula == aluno[i].matricula){ //Matr�cula j� cadastrada
                                        printf("\nAluno j� cadastrado no sistema.\n");
                                        achou = 1;
                                        system("pause");
                                        limparTela();
                                        break; //Sai do for
                                    }
                                }
                                
                                //Matr�cula ainda n�o cadastrada
                                if (achou == 0){
                                    //Armazena matr�cula
                                    aluno[contAluno].matricula = matricula;
                                                                    
                                    int flagNome = 0;
                                    char nome[tamNome];
                                    //Recebe e valida o nome
                                    do {
                                        printf("Informe o nome do aluno: ");
                                        scanf(" %[^\n]", nome);
                                        flagNome = validarNome(nome);
                                        //printf("%d", flagNome);

                                        if (flagNome != 0)
                                            printf("\nNome inv�lido. Apenas letras, com ou sem acento, e espa�os s�o permitidas.\n");
                                    } while (flagNome != 0);
                                    
                                    //Armazena o nome
                                    if (flagNome == 0){ //if desnecess�rio. Apenas por precau��o
                                        strcpy(aluno[contAluno].nome, nome);
                                    }

                                    int flagData = 0;
                                    int dia, mes, ano;
                                    //Recebe e valida a data
                                    do {
                                        printf("Informe a de nascimento do aluno (DD/MM/AAAA): ");
                                        scanf("%d/%d/%d", &dia, &mes, &ano);
                                        flagData = validarData(dia, mes, ano);
                                        //printf("%d", flagData);

                                        if (flagData != 0)
                                            printf("\nData inv�lida.\n");
                                    } while (flagData != 0);

                                    int flagCPF = 0;
                                    char CPF[tamCPF + 1]; //+1 para o terminador nulo
                                    //Recebe e valida o CPF
                                    do {
                                        printf("Informe o CPF (apenas n�meros): ");
                                        scanf(" %s", CPF);
                                        flagCPF = validarCPF(CPF);
                                        //printf("%d", flagCPF);

                                        if (flagCPF != 0)
                                            printf("\nData inv�lida.\n");
                                    } while (flagCPF != 0);

                                    int flagGenero = 0;
                                    char genero[tamGenero];
                                    //Recebe e valida a identidade de g�nero
                                    do {
                                        printf("Informe a identidade de g�nero: ");
                                        printf("\nM - Masculino");
                                        printf("\nF - Feminino");
                                        printf("\nNB - N�o bin�rio");
                                        printf("\nND - N�o declarado\n");
                                        scanf(" %s", genero);

                                        //Converte os caracteres para mai�sculo
                                        for (int i = 0; i <= strlen(genero) - 1; i++) {
                                            genero[i] = toupper(genero[i]);
                                        }

                                        flagGenero = validarGenero(genero);
                                        //printf("%d", flagGenero);

                                        if (flagGenero != 0)
                                            printf("\nIdentidade de g�nero inv�lida.\n");
                                    } while (flagGenero != 0);
                                    
                                    contAluno++; //Incrementa a quantidade de alunos

                                    printf("\nAluno cadastrado com sucesso!\n");
                                    system("pause");
                                    limparTela();
                                }
                            } //Fim do else
                            break; //Sai do case 1
                        } //Fim do switch 2, case 1: Inserir aluno
                        
                        //Listar aluno
                        case 2: {
                            printf("### M�dulo Alunos - Listar alunos ###");
                            break; //Sai do case 2
                        } //Fim do switch 2, case 2: Listar aluno
        
                        //Atualizar aluno
                        case 3: {
                            printf("### M�dulo Alunos - Atualizar aluno ###");
                            break; //Sai do case 3
                        } //Fim do switch 2, case 3: Atualizar aluno
        
                        //Excluir aluno
                        case 4: {
                            printf("### M�dulo Alunos - Excluir aluno ###");
                            break; //Sai do case 4 
                        } //Fim do switch 2, case 4: Excluir aluno
                                
                        //Op��o inv�lida
                        default: {
                            printf("\nOpc�o inv�lida.\n");
                            system("pause");
                            limparTela();
                            break; //Sai do default
                        } //Fim do switch 2, default: Op��o inv�lida
                    } //Fim do switch 2

                } while(opcaoAluno != 0);

                break;
            } //Fim do case 1

            //Professores
            case 2: {
                printf("\nM�dulo Professores:\n");
                break;
            } //Fim do case 2

            //Disciplinas
            case 3: {
                printf("\nM�dulo Disciplinas:\n");
                break;
            } //Fim do case 3

            default: {
                printf("\nOpc�o inv�lida.");
                break;
            }
        } //Fim do switch 1
    } while (opcao != 0);
} //Fim do programa