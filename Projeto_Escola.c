// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>
#include <limits.h>

/*------------------------------------------------------------------------------------------------------------*/
// Constantes globais

#define tamNome 100
#define tamData 10
#define tamCPF 11
#define tamSexo 2
#define tamAlunos 10000
#define tamProfessores 100
#define tamDisciplinas 1000

/*------------------------------------------------------------------------------------------------------------*/
// Structs globais

// Data
typedef struct {
    int dia;
    int mes;
    int ano;
} data;

// Cadastro de pessoas
typedef struct {
    int *matricula; // Alocação dinâmica
    char nome[tamNome];
    char CPF[tamCPF + 1]; //+1 para o terminador nulo
    char genero[3]; //+1 para o terminador nulo
    data nascimento;
} pessoa;

pessoa aluno[tamAlunos];
pessoa professor[tamAlunos];

// Cadastro das disciplinas
typedef struct {
    int *matricula; // Alocação dinâmica
    char *codigo; // Alocação dinâmica
    int semestre;
} listaDisciplinas;

listaDisciplinas disciplina[tamDisciplinas];

/*------------------------------------------------------------------------------------------------------------*/
// Subfunções

// Limpa a tela
void limparTela() {
    #if defined(_WIN32) || defined(_WIN64) // Windows
        system("cls");
        system("pause");

    #elif defined(__linux__) || defined(__unix__) || defined(__APPLE__) || defined(__MACH__) // Linux e macOS
        system("clear");
        
    #endif
}

//Pausa a tela
void pausarTela() {
    #if defined(_WIN32) || defined(_WIN64) // Windows
        system("pause");

    #elif defined(__linux__) || defined(__unix__) || defined(__APPLE__) || defined(__MACH__) // Linux e macOS
        printf("Pressione qualquer tecla para continuar...");

        // Limpa o buffer de entrada antes do getchar()
        int c;
        while ((c = getchar()) != '\n' && c != EOF);  // Limpa caracteres pendentes
        getchar();  // Aguarda o Enter
    
        system("clear"); // Limpa a tela

    #endif
}

// Valida números inteiros
int validarInteiroPositivo(int *endereco) {
    
    long long n;
    int retorno = -1;
    int caractere;

    // Retorna 1 se conseguiu coletar uma entrada válida e 0 caso contrário
    retorno = scanf("%lld", &n); 

    // Limpar o buffer e impede o loop infinito
    while ((caractere = getchar()) != '\n' && caractere != EOF);
    
    // Verifica se caracteres não numéricos foram digitados
    if (retorno == 0 || retorno == EOF) {
        printf("Erro: caractere não numérico digitado.\n");
        return 1;
    }
    
    // Verifica se o número é maior que INT_MAX
    if (n > INT_MAX) {
        printf("Erro: o número excede o limite de %d.\n", INT_MAX);
        return 1;
    }
    
    // Verifica se o número é negativo
    if (n <= 0) {
        printf("Erro: o número deve ser positivo e maior que 0.\n");
        return 1;
    }
    
    // Converte n para inteiro e armazena no endereço guardado em "endereco"
    *endereco = (int)n;  
    return 0;
}

// Alocando dinamicamente espaços de memória para cada aluno, professor ou disciplina
void alocarMemoria(int tamMatricula) {
    for (int i = 0; i < tamAlunos; i++) {
        aluno[i].matricula = (int*)malloc(tamMatricula * sizeof(int));
        if (aluno[i].matricula == NULL) {
            printf("Erro ao alocar memória para aluno %d\n", i);
            exit(1);
        }
    }

    for (int i = 0; i < tamProfessores; i++) {
        professor[i].matricula = (int*)malloc(tamMatricula * sizeof(int));
        if (professor[i].matricula == NULL) {
            printf("Erro ao alocar memória para professor %d\n", i);
            exit(1);
        }
    }

    for (int i = 0; i < tamDisciplinas; i++) {
        disciplina[i].matricula = (int*)malloc(tamMatricula * sizeof(int));
        if (disciplina[i].matricula == NULL) {
            printf("Erro ao alocar memória para disciplina %d\n", i);
            exit(1);
        }
    }
}

// Valida a matrícula
int validarMatricula (long long matricula, int tamMatricula) {
    long long auxMatricula = matricula;
    int digMatricula = 0;

    
    
    
    
    
    
    
    
    
    
    
    
    // Calcula a quantidade de dígitos da matrícula informada
    while (auxMatricula > 0){
        auxMatricula /= 10; //Remove o último dígito
        digMatricula++; //Quant. de dígitos da matrícula informada
    }

    // Verifica se a matrícula é negativa
    if (matricula < 0){
        printf("\nErro: a matrícula não pode ser um número negativo.");
        return 1;
    }

    // Verifica se a matrícula tem a quantidade correta de dígitos
    if (digMatricula == tamMatricula){
        printf("\nErro: a matrícula deve conter %d dígitos.", tamMatricula);
        return 1;
    }

    return 0; // Matrícula válida
}

// Valida o nome
int validarNome(char nome[tamNome]) {
    int len = strlen(nome);

    // Verifica se o nome não está vazio
    if (len == 0) {
        printf("\nNome inválido. O nome não pode estar vazio.");
        return 1;  // Retorna 1 para indicar erro
    }

    for (int i = 0; i < len; i++){
        // Permite letras, espaços e caracteres acentuados
        if (!(isalpha(nome[i]) || nome[i] == ' ')) {
            printf("\nNome inválido. O nome contém caracteres inválidos.");
            return 1;
        }
    }
    
    return 0; // Nome válido
}

// Verifica se o ano é bissexto
int bissexto(int ano) {
    if(((ano % 4 == 0) && (ano % 100 != 0)) || (ano % 400 == 0)){
        return 1; // é bissexto
    }
    else {
        return 0; // Não é bissexto
    }
}

// Valida a data de nascimento
int validarData(int dia, int mes, int ano) {
    int flagBissexto = bissexto(ano);
    int diasMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Valida o ano
    if (ano < 1900 || ano > 2100) {
        printf("\nAno inválido. O ano deve estar entre 1900 e 2100.");
        return 1;
    }
    
    // Valida o mês
    if (mes < 1 || mes > 12) {
        printf("\nMês inválido. O mês deve estar entre 1 e 12.");
        return 1; // Mês inválido
    }

    // Atualiza a qtd de dias em fevereiro se o ano for bissexto
    if (flagBissexto == 1) {
        diasMes[1] = 29; // Fevereiro
    }

    // Valida o dia
    if (dia < 1 || dia > diasMes[mes - 1]) {
        printf("\nDia inválido. O dia deve estar entre 1 e %d.", diasMes[mes - 1]);
        return 1; // Dia inválido
    }
    
    // Calcula a quantidade de segundos entre a data/horário atual e a data referencial (01/01/1970)
    // e armazena na variável tipo time_z
    time_t agora = time(NULL);

    // Cria e zera a variável nascimento, do tipo tm, que contém campos para data e hora
    struct tm nascimento = {0};

    // Armazena a data de nascimento
    nascimento.tm_mday = dia;
    nascimento.tm_mon = mes - 1; // Janeiro = 0
    nascimento.tm_year = ano - 1900; // Anos desde 1900
    nascimento.tm_isdst = -1; // Auto-detecta horário de verão

    // Converte a data de nascimento de tm (data/hora em campos separados) para time_t (segundos desde o referencial)
    time_t nasc_seg = mktime(&nascimento);

    // Verifica se a conversão foi bem-sucedida
    if (nasc_seg == (time_t) - 1) {
        printf("\nErro: Data inválida ou impossível.");
        return 1;
    }

    // Verifica se a data é futura
    if (difftime (agora, nasc_seg) < 0) {
        printf("\nA data de nascimento é posterior à data atual.");
        return 1;
    }

    return 0; // Data válida
}

// Valida o CPF
int validarCPF (char CPF[tamCPF + 1]) { //+1 para o terminador nulo

    // Verifica se o CPF tem 11 dígitos
    if (strlen(CPF) != 11) {
        printf("\nCPF inválido. O CPF deve conter %d dígitos.", tamCPF);
        return 1;
    }

    // Verifica se o CPF só contém números
    for (int i = 0; i < tamCPF; i++) {
        if (!isdigit(CPF[i])) {
            printf("\nCPF inválido. O CPF deve conter apenas números.");
            return 1;
        }
    }

    // Verifica se todos os dígitos são iguais
    int todosIguais = 1;
    for (int i = 1; i < tamCPF; i++) {
        if (CPF[i] != CPF[0]) {
            todosIguais = 0;
            break;
        }
    }
    if (todosIguais == 1) {
        printf("\nCPF inválido. Os dígitos do CPF não podem ser todos iguais.");
        return 1;
    }

    // Verifica o 10º dígito (1º verificador)
    int soma = 0;
    for (int i = 0; i < 9; i++) { //Percorre do 1º ao 9º dígito
        soma += (CPF[i] - '0') * (10 - i);
    }
    int resto = soma % 11;

    // Calcula o 1º dígito verificador
    int digito1 = (resto < 2) ? 0 : (11 - resto);

    // Verifica se o 10º dígito é igual ao dígito verificador
    if (CPF[9] - '0' != digito1) {
        printf("\nCPF inválido. O 10º dígito deveria ser %d.", digito1);
        return 1;
    }

    // Verifica o 11º dígito (2º verificador)
    soma = 0;
    for (int i = 0; i < 10; i++) { // Percorre do 1º ao 10º dígito
        soma += (CPF[i] - '0') * (11 - i);
    }
    resto = soma % 11;

    // Calcula o 2º dígito verificador
    int digito2 = (resto < 2) ? 0 : (11 - resto);

    // Verifica se o 11º dígito é igual ao dígito verificador
    if (CPF[10] - '0' != digito2) {
        printf("\nCPF inválido. O 11º dígito deveria ser %d.", digito1);
        return 1;
    }
        
    return 0; // CPF válido
}

// Valida o sexo
int validarSexo(char sexo[tamSexo]) {
    if (!(strcmp(sexo, "M") == 0 || strcmp(sexo, "F") == 0)) {
        printf("\nSexo inválido. O sexo só pode ser M ou F.");
        return 1;
    }

    return 0; // Sexo válido
}

/*------------------------------------------------------------------------------------------------------------*/
//Função principal
int main (){

    //Configurando a codificação de caracteres
    setlocale(LC_ALL, "Portuguese"); //Windows
    //setlocale(LC_ALL, "pt_BR.UTF-8"); //Linux

    //Declarações
    int opcao;
    int contAluno = 0, contProfessor = 0, contDisciplina = 0;

    int flagInteiro = 0;
    int tamMatricula = 0;
    // Recebe o tamanho da matrícula e valida
    do {
        printf("Quantos dígitos tem uma matrícula (apenas inteiros positivos)? ");
        flagInteiro = validarInteiroPositivo(&tamMatricula);
        printf("\n");

    } while (flagInteiro != 0);
    
    printf("Tamanho da matrícula: %d\n", tamMatricula);
    
    // Alocação dinâmica de espaços para cada aluno, professor e disciplina
    alocarMemoria(tamMatricula);
    
    //Solicita ao usuário o tamanho padrão do código de uma disciplina
    /*int tamCodigo = 0;
    printf("Quantos caracteres tem o código de uma disciplina?\n");
    scanf("%d", &tamCodigo);

    //Alocando dinamicamente o tamanho do vetor código
    for (int i = 0; i < tamDisciplinas; i++){
        //"(char*)" converte o ponteiro do tipo void*, retornado por malloc, para um ponteiro tipo char, mesmo tipo do campo "codigo"
        disciplina[i].codigo = (char*)malloc(tamCodigo * sizeof(char));
    }*/

    pausarTela();
    limparTela();

    do {
        //Menu de opções
        printf("### Menu principal ###");
        printf("\nInforme o número da opção desejada: ");
        printf("\n0 - Sair");
        printf("\n1 - Alunos");
        printf("\n2 - Professores");
        printf("\n3 - Disciplinas\n");
    
        //Entrada de dados: Opção
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
                    //Menu de opções
                    printf("### Módulo Alunos ###");
                    printf("\nInforme o número da opção desejada: ");
                    printf("\n0 - Voltar ao menu anterior");
                    printf("\n1 - Cadastrar aluno");
                    printf("\n2 - Listar aluno");
                    printf("\n3 - Atualizar aluno");
                    printf("\n4 - Excluir aluno");
                    printf("\n");
                    
                    //Entrada de dados: Opção do Módulo de alunos
                    scanf("%d",&opcaoAluno);
                    
                    limparTela();
    
                    //Switch 2
                    switch(opcaoAluno){

                        //Voltar ao menu anterior
                        case 0: {
                            limparTela();
                            break;
                        } // Fim do switch 2, case 0: voltar ao menu anteior

                        // Inserir aluno
                        case 1: {
                            
                            int achou = 0; // Flag
                            
                            printf("### Módulo Alunos - Inserir aluno ###\n");

                            int flagMatricula = 0;
                            long long matricula;
                            // Recebe e valida a matrícula
                            do {
                                printf("Informe a matrícula do aluno: ");
                                scanf("%lld", &matricula);                            

                                flagMatricula = validarMatricula(matricula, tamMatricula);
                                //printf("%d", flagMatricula);

                                if (flagMatricula != 0)
                                    printf("\n");
                            } while (flagMatricula != 0);
                            
                            // Lista de alunos cheia
                            if (contAluno > tamAlunos){
                                printf("\nCadastro de alunos cheio.\n");
                                pausarTela();
                                limparTela();
                            }
                            
                            // Lista de alunos não cheia
                            else{
                                // Verifica se a matrícula já está cadastrada
                                for (int i = 0; i < contAluno; i++){
                                    if (matricula == aluno[i].matricula){ // Matrícula já cadastrada
                                        printf("\nMatrícula já cadastrada no sistema.\n");
                                        achou = 1;
                                        pausarTela();
                                        limparTela();
                                        break; //Sai do for
                                    }
                                }
                                
                                // Matrícula ainda não cadastrada
                                if (achou == 0){
                                    // Armazena matrícula
                                    aluno[contAluno].matricula = matricula;
                                                                    
                                    int flagNome = 0;
                                    char nome[tamNome];
                                    // Recebe e valida o nome
                                    do {
                                        printf("Informe o nome do aluno: ");
                                        scanf(" %99[^\n]", nome);
                                        /*' ' (espaço) antes do '%' para ignorar caracteres deixados no buffer de entrada anteriormente.
                                        '99' para limitar a quantidade de caracteres, evitando buffer overflow.
                                        '[^/n]' para ler qualquer caractere até encontrar uma quebra de linha (enter).*/

                                        flagNome = validarNome(nome);
                                        //printf("%d", flagNome);

                                        if (flagNome != 0)
                                            printf("\n");
                                    } while (flagNome != 0);
                                    
                                    // Armazena o nome
                                    if (flagNome == 0){ // if desnecessário. Apenas por precaução
                                        strcpy(aluno[contAluno].nome, nome);
                                    }

                                    int flagData = 0;
                                    int dia, mes, ano;
                                    // Recebe e valida a data
                                    do {
                                        printf("Informe a de nascimento do aluno (DD/MM/AAAA): ");
                                        if(scanf("%d/%d/%d", &dia, &mes, &ano) != 3) {
                                            // Limpa o buffer de entrada
                                            while (getchar() != '\n');  // Limpa o buffer até encontrar a quebra de linha

                                            printf("\nFormato inválido! A data deve ser no formato dd/mm/aaaa.\n");
                                            flagData = 1;
                                            continue; // Pula as próximas linhas do código e vai para o próximo loop
                                        }

                                        flagData = validarData(dia, mes, ano);
                                        //printf("%d", flagData);

                                        if (flagData != 0)
                                            printf("\n");
                                    } while (flagData != 0);

                                    int flagCPF = 0;
                                    char CPF[tamCPF + 1]; //+1 para o terminador nulo
                                    // Recebe e valida o CPF
                                    do {
                                        printf("Informe o CPF (apenas números): ");
                                        scanf(" %11s", CPF);
                                        flagCPF = validarCPF(CPF);
                                        //printf("%d", flagCPF);

                                        if (flagCPF != 0)
                                            printf("\n");
                                    } while (flagCPF != 0);

                                    int flagSexo = 0;
                                    char sexo[tamSexo];
                                    // Recebe e valida o sexo
                                    do {
                                        printf("Informe o sexo (M ou F): ");
                                        scanf(" %1s", sexo);

                                        // Converte os caracteres para maiúsculo
                                        for (int i = 0; i <= strlen(sexo) - 1; i++) {
                                            sexo[i] = toupper(sexo[i]);
                                        }

                                        flagSexo = validarSexo(sexo);
                                        //printf("%d", flagSexo);

                                        if (flagSexo != 0)
                                            printf("\n");
                                    } while (flagSexo != 0);
                                    
                                    contAluno++; // Incrementa a quantidade de alunos

                                    printf("\nAluno cadastrado com sucesso!\n");
                                    pausarTela();
                                    limparTela();
                                }
                            } // Fim do else
                            break; // Sai do case 1
                        } // Fim do switch 2, case 1: Inserir aluno
                        
                        // Listar aluno
                        case 2: {
                            printf("### Módulo Alunos - Listar alunos ###");
                            break; // Sai do case 2
                        } // Fim do switch 2, case 2: Listar aluno
        
                        // Atualizar aluno
                        case 3: {
                            printf("### Módulo Alunos - Atualizar aluno ###");
                            break; // Sai do case 3
                        } // Fim do switch 2, case 3: Atualizar aluno
        
                        // Excluir aluno
                        case 4: {
                            printf("### Módulo Alunos - Excluir aluno ###");
                            break; // Sai do case 4 
                        } // Fim do switch 2, case 4: Excluir aluno
                                
                        // Opção inválida
                        default: {
                            printf("Opção inválida.\n");
                            pausarTela();
                            limparTela();
                            break; // Sai do default
                        } // Fim do switch 2, default: opção inválida

                    } // Fim do switch 2

                } while(opcaoAluno != 0);

                break;
            } // Fim do case 1

            // Professores
            case 2: {
                printf("\nMódulo Professores:\n");
                break;
            } // Fim do case 2

            // Disciplinas
            case 3: {
                printf("\nMódulo Disciplinas:\n");
                break;
            } // Fim do case 3

            default: {
                printf("Opção inválida.");
                pausarTela();
                limparTela();
                break;
            } // Fim do case default

        } // Fim do switch 1

    } while (opcao != 0);

    // Libera a memória alocada
    for (int i = 0; i < tamAlunos; i++) {
        free(aluno[i].matricula);
    }

    for (int i = 0; i < tamProfessores; i++) {
        free(professor[i].matricula);
    }

    for (int i = 0; i < tamDisciplinas; i++) {
        free(disciplina[i].matricula);
    }

} // Fim do programa