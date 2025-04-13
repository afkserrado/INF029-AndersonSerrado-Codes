//Bibliotecas
#include <stdio.h>
#include <string.h>
#include <locale.h>

/*------------------------------------------------------------------------------------------------------------*/
//Constantes

#define tamNome 100
#define tamData 10
#define tamCPF 11
#define tamAlunos 10000
#define tamProfessores 100
#define tamDisciplinas 1000

/*------------------------------------------------------------------------------------------------------------*/
//Structs

//Cadastro dos alunos
typedef struct {
    long long matricula;
    char nome[tamNome];
    char data[tamData];
    char CPF[tamCPF];
    char sexo;
} listaAlunos;

listaAlunos aluno[tamAlunos];

//Cadastro dos professores
typedef struct {
    long long matricula;
    char nome[tamNome];
    char data[tamData];
    char CPF[tamCPF];
    char sexo;
} listaProfessores;

listaProfessores professor[tamProfessores];

//Cadastro das disciplinas
typedef struct {
    long long matricula;
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

/*------------------------------------------------------------------------------------------------------------*/
//Fun��o principal
int main (){

    //Configurando a codifica��o de caracteres
    setlocale(LC_ALL, "Portuguese"); //Windows
    //setlocale(LC_ALL, "pt_BR.UTF-8"); //Linux

    //Declara��es
    int opcao;
    int tamCodigo;
    long long matricula;
    long long maxMatricula; //Maior n�mero que a matr�cula pode ter (Ex.: 99999999999)
    int tamMatricula = 0; //Maior quantidade de d�gitos que a matr�cula pode ter (Ex.: 11)
    int contAluno = 0, contProfessor = 0, contDisciplina = 0;

    //Solicita ao usu�rio a maior matr�cula poss�vel
    printf("\nQual a maior matr�cula poss�vel para uma pessoa? (Ex.: 9999999)\n");
    scanf("%lld", &maxMatricula);

    //Calcula a quantidade de d�gitos da matr�cula padr�o
    long long auxMatricula;
    auxMatricula = maxMatricula;
    while (auxMatricula > 0){
        auxMatricula /= 10; //Remove o �ltimo d�gito
        tamMatricula++; //Qtd de d�gitos da matr�cula padr�o
    }

    //Solicita ao usu�rio o tamanho padr�o do c�digo de uma disciplina
    printf("Quantos caracteres tem o c�digo de uma disciplina?\n");
    scanf("%d", &tamCodigo);

    //Alocando dinamicamente o tamanho do vetor c�digo
    for (int i = 0; i < tamDisciplinas; i++){
        disciplina[i].codigo = malloc(tamCodigo * sizeof(char));
    }

    limparTela();

    do {
        //Menu de op��es
        printf("Informe o n�mero da op��o desejada: ");
        printf("\n0 - Sair");
        printf("\n1 - Alunos");
        printf("\n2 - Professores");
        printf("\n3 - Disciplinas\n");
    
        //Entrada de dados: opc�o
        scanf("%d",&opcao);

        limparTela();

        switch (opcao){

            case 0: {
                printf("\nPrograma encerrado.");
                return 1;
            }
            
            //Alunos
            case 1: {
                int opcaoAluno;
                //Menu de op��es
                printf("### M�dulo Alunos ###\n");
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
                printf("### M�dulo Alunos - Inserir aluno ###");

                switch(opcaoAluno){
                    
                    //Flag
                    int achou = 0;

                    //Inserir aluno
                    case 1: {
                        //Entrada de dados: matr�cula
                        printf("\nInforme a matr�cula do aluno: ");
                        scanf("%lld", &matricula);

                        //Calcula a quantidade de d�gitos da matr�cula informada
                        int digMatricula = 0;
                        auxMatricula = matricula;
                        while (auxMatricula > 0){
                            auxMatricula /= 10; //Remove o �ltimo d�gito
                            digMatricula++; //Qtd de d�gitos da m�tricula informada
                        }

                        //Valida��o 1: formato da matr�cula
                        if (!(matricula >= 0 && matricula <= maxMatricula && digMatricula == tamMatricula)){
                            printf("\nMatr�cula inv�lida.");
                            printf("\n");
                            break;
                        }
                        
                        if (contAluno > tamAlunos){
                            printf("\nCadastro de alunos cheio.");
                        }
                        else{
                            //Verifica se a matr�cula j� est� cadastrada
                            //N�o est� funcionando ################################
                            for (int i = 0; i < contAluno; i++){
                                if (matricula == aluno[i].matricula){ //Matr�cula j� cadastrada
                                    printf("\nAluno j� cadastrado no sistema.");
                                    achou = 1;
                                    break; //Sai do for
                                }
                            }
    
                            if (!achou){ //Se achou diferente de 1
                                aluno[contAluno].matricula = matricula;
                                contAluno++;
                                printf("\nAluno cadastrado com sucesso!");
                            }
                        }

                        break;
                    } //Fim do case 1: Inserir aluno

                    limparTela();

                    //Listar aluno
                    case 2: {

                        break;
                    } //Fim do case 2: Listar aluno

                    //Atualizar aluno
                    case 3: {

                        break;
                    } //Fim do case 3: Atualizar aluno

                    //Excluir aluno
                    case 4: {

                        break;
                    } //Fim do case 4: Excluir aluno

                    default: {
                        printf("\nOpc�o inv�lida.");
                        break;
                    }
                } //Fim do switch

                break;
            } //Fim do case 1
            
            //Professores
            case 2: {
                printf("\nModulo Professores:\n");
                break;
            } //Fim do case 2

            //Disciplinas
            case 3: {
                printf("\nModulo Disciplinas:\n");
                break;
            } //Fim do case 3

            default: {
                printf("\nOpc�o inv�lida.");
                break;
            }
        }
    } while (opcao != 0);
} //Fim do programa