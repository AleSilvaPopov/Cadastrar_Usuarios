#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

typedef struct{
    unsigned int cdg;
    char nome[100];
    unsigned int idade;
    char sexo;
}Pdados;

//Modulos.
void criar_arquivo();
void cadastrar();
void ver_cadastrados();
void menu(int);
int vereficar_arv();
void remover_cadastro();
void procura();
unsigned int busca(int);
void erro();
void novo_arquivo(int, unsigned int);

int main(){
    setlocale(LC_ALL, "Portuguese"); // Deixar em Português.
    int escolha; // Variavel para a escolha do usuário.
    
    // verificar se já existe um arquivo .txt se não existir cria um.
    if(vereficar_arv() == 1){
        criar_arquivo();
    }
    else{
        printf("|Arquivo já existe.|\n");
        Sleep(1000);
    }

    do{
        system("cls");
        menu(1); 
        escolha = getche(); // lê a escolha do usuário, getche lê tabela ASCII.
        //Acessa a escolha.
        switch (escolha){
            case '1':
                cadastrar(); // Cadastra novo nome na lista.
                break;
            case '2':
                ver_cadastrados(); // Imprime a lista.
                break;
            case '3':
                remover_cadastro(); //Remove nome da lista.
                break;
            case '4':
                procura(); //Procura na lista, de acordo com a escolha do usuário(Ex: Um nome, Sexo, Idade etc.)
                break;
            case '5':
                //??????
                break;
            case '6':
            //Finaliza o código.
                system("cls");
                printf("fi");
                Sleep(500);
                printf("na");
                Sleep(500);
                printf("li");
                Sleep(500);
                printf("zan");
                Sleep(500);
                printf("do");
                Sleep(500);
                printf(".");
                Sleep(500);
                printf(".");
                Sleep(500);
                printf(".\n");
                Sleep(200);
                break;
            default:
                //Tratamento de erro caso o usuário digite algo inválido.
                erro();
                break;
        }
    } while(escolha != '6'); //Se escolha for diferente de 6 ele continua o programa.

    return 0;
}

//Menu com todas as opções.
void menu(int n){
    if(n == 1){
        printf("-----------------------------------------");
    printf("\n|\t    Menu Principal\t        |\n");
    printf("-----------------------------------------");
    printf("\n|\t[1]Adicionar nome a lista.\t|\n");
    printf("|\t[2]Ver lista.\t                |\n");
    printf("|\t[3]Tirar nome da lista\t        |\n");
    printf("|\t[4]Procurar na lista.\t        |\n");
    printf("|\t[5]?????????????????.\t        |\n");
    printf("|\t[6]Sair do programa.\t        |\n");
    printf("-----------------------------------------");
    printf("\n\tDigite sua escolha: ");

    }
    if(n == 2){
        system("cls");
        printf("\tO que deseja procurar: \n");
        printf("\t[1] Femininos.\n\t[2] Masculinos.\n\t[3] Código\n\t[4] Idade\n\t[5] Voltar\n");
        printf("\tSua esolha: ");
    }
}

void criar_arquivo(){
    /*
        Não recebe nenhum escopo.
        Cria o arquivo onde será armazenado os dados caso ele não existe.
    */

    FILE *aqv;
    aqv = fopen("ListaUsuarios.txt", "w");
    if(aqv == NULL){
        printf("\nErro ao abrir o arquivo.\n");
        Sleep(2000);
        return;
    }
    else{
        printf("\nSucesso ao abrir o arquivo.\n");
        Sleep(2000);
    }

    fclose(aqv);
}

void ver_cadastrados(){
    /*
        Não recebe escopo.
        Mostra uma lista com todos os dados cadastrados.
    */
    FILE *aqv;

    aqv = fopen("ListaUsuarios.txt", "r");
    if(aqv == NULL){
        printf("\nErro ao abrir arquivo para leitura.\n");
        Sleep(2000);
        return;
    }

    Pdados pessoa;
    char linha[100];

    system("cls");
    printf("Num. Nome\t\t\t\t| Idade | Sexo |\n");
    printf("------------------------------------------------------\n");
    while(fgets(linha, sizeof(linha), aqv) != NULL){
        if(sscanf(linha, "%u %[^0-9] %u %[^\n]c", &pessoa.cdg, pessoa.nome, &pessoa.idade, &pessoa.sexo) == 4){
            printf("%-4d %-30s\t| %4d  |%3c   |\n", pessoa.cdg, pessoa.nome, pessoa.idade, pessoa.sexo);
        }
    }   
    fclose(aqv);
    system("pause");
}

void cadastrar(){
    /*
        Não recebe escopo.
        Cadastra na lista os dados informado pelo usuário.
        Já adiciona o código.
     */
    Pdados pessoa;
    char linha[100];
    FILE *aqv;

    pessoa.cdg = 0;

    aqv = fopen("ListaUsuarios.txt", "r");
    if(aqv != NULL){
        while(fgets(linha, sizeof(linha), aqv) != NULL){
            sscanf(linha, "%u", &pessoa.cdg);
        }
        pessoa.cdg += 1;
        fclose(aqv);
    }
    else{
        pessoa.cdg = 1;
    }

    aqv = fopen("ListaUsuarios.txt", "a");
    if(aqv == NULL){
        printf("Erro ao abrir arquivo.\n");
        Sleep(2000);
        return;
    }
    fflush(stdin);
    printf("\nNome: ");
    fgets(pessoa.nome, sizeof(pessoa.nome), stdin);
    pessoa.nome[strcspn(pessoa.nome, "\n")] = 0;

    printf("Idade: ");
    scanf("%u", &pessoa.idade);

    printf("Sexo[M/F]");
    scanf(" %c", &pessoa.sexo);

    fprintf(aqv, "%d %s %d %c\n",pessoa.cdg, pessoa.nome, pessoa.idade, pessoa.sexo);


    printf("[%d %s %d %c] --> adicionado com sucesso.", pessoa.cdg, pessoa.nome, pessoa.idade, pessoa.sexo);
    
    fclose(aqv);
    system("PAUSE");
}

int vereficar_arv(){
    /*
        Não recebe escopo.
        Verifica se já existe um arquivo com dados salvos.
     */
    FILE *a;
    a = fopen("ListaUsuarios.txt", "r");
    if(a == NULL){
        fclose(a);
        return 1;
    }
    else{
        fclose(a);
        return 0;
    }
}

void remover_cadastro(){
    /*
        Não receve escopo.
        Remove um certo dado da lista de acordo com a escolha do usuário.
    */
    Pdados pessoa;
    char linha[100];
    unsigned int remover;

    ver_cadastrados();

    printf("Digite o código de quem deseja remover da lista: ");
    scanf("%u", &remover);

    FILE *a, *b;
    a = fopen("ListaUsuarios.txt", "r");
    if(a == NULL){
        printf("Erro, ao abrir o arquivo .txt.\n");
        return;
    }
    b = fopen("temp.txt", "w");
    if(b == NULL){
        printf("Erro, ao abrir o arquivo temporario .txt.\n");
        fclose(a);
        return;
    }

    while(fgets(linha, sizeof(linha), a) != NULL){
        sscanf(linha, "%u %[^0-9] %u %c", &pessoa.cdg, pessoa.nome, &pessoa.idade, &pessoa.sexo);
        if(remover != pessoa.cdg){
             fprintf(b, "%u %s%u %c\n", pessoa.cdg, pessoa.nome, pessoa.idade, pessoa.sexo);
         }
    }
    fclose(a);
    fclose(b);

    remove("ListaUsuarios.txt");
    rename("temp.txt", "ListaUsuarios.txt");

    printf("Cadastro removido com sucesso.\n");
    system("PAUSE");
}

void procura(){
    /*
        Da novas opçôes de busca para o usuário.
    */
    unsigned int escolha, r;
    char Narq;

    do{
        menu(2);
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            //Buscar todos do sexo Feminino.
            system("cls");
            r = busca(1);
            break;
        case 2:
            //Buscar todos do sexo Masculino.
            system("cls");
            r = busca(2);
            break;
        case 3:
            //Buscar uma unica pessoa com o codigo informado.
            system("cls");
            r = busca(3);
            break;
        case 4:
            //Buscar todos com a idade informada.
            system("cls");
            r = busca(4);
            break;
        case 5:
            system("cls");
            printf("Voltando pro menu principal.\n");
            Sleep(1000);
            break;
        
        default:
            erro();
            break;
        }
        if(escolha != 5){
            printf("Deseja um arquivo com essa lista:[S/N]: ");
            scanf(" %c", &Narq);
            if(Narq == 'S' || Narq == 's'){
            novo_arquivo(escolha, r);
            }
        }
    }while(escolha != 5);

}

unsigned int busca(int n){
    /*
        Busca algo na lista de acordo com a escolha do usuario.
    */
    FILE *a;
    char linha[100];
    Pdados pessoa;
    unsigned int cdg, flag = 0, flag2 = 0;

    a = fopen("ListaUsuarios.txt", "r");
    if(a == NULL){
        printf("Erro!\n");
        return 1;
    }
    else{
        while(fgets(linha, sizeof(linha), a) != NULL){
            sscanf(linha, "%u %[^0-9] %d %c", &pessoa.cdg, pessoa.nome, &pessoa.idade, &pessoa.sexo);
            if(n == 1){
            //Busca Feminina
                if(pessoa.sexo == 'F' || pessoa.sexo == 'f'){
                    if(flag2 == 0){
                        printf("Mulheres encontradas: \n");
                        flag2++;
                    }
                    printf("%d %s %d %c\n", pessoa.cdg, pessoa.nome, pessoa.idade, pessoa.sexo);
                    flag++;
                }
            }
            if(n == 2){
                //Busca Masculina
                if(pessoa.sexo == 'M' || pessoa.sexo == 'm'){
                    if(flag2 == 0){
                        printf("Homens encontrados: \n");
                        flag2++;
                    }
                        printf("%d %s %d %c\n", pessoa.cdg, pessoa.nome, pessoa.idade, pessoa.sexo);
                        flag++;
                }
            }
            if(n == 3){
                //Busca pelo codigo.
                if(flag2 == 0){
                    printf("Informe o codigo: ");
                    scanf("%u", &cdg);
                    flag2++;
                }
                if(pessoa.cdg == cdg){
                    printf("Usuario: %d %s %d %c\n", pessoa.cdg, pessoa.nome, pessoa.idade, pessoa.sexo);
                    flag++;
                }
            }
            if(n == 4){
                //Busca pela Idade.
                if(flag2 == 0){
                    printf("Informe a idade: ");
                    scanf("%u", &cdg);
                    flag2++;
                }
                if(pessoa.idade == cdg){
                    if(flag == 0){
                        printf("Pessoas de %u anos encontradas: \n", cdg);
                        flag++;
                    }
                    printf("Codigo: %d | Nome --> %s | Sexo --> %c\n", pessoa.cdg, pessoa.nome, pessoa.sexo);
                }
            }
        }
    }
    if(flag == 0){
        printf("Ninguém com essas informações encontrado.\n");
    }
    system("pause");
    if(n == 4){
        return cdg;
    }
    else{
        return 0;
    }
}

void erro(){
    int cont;
    system("cls");
                cont = 3;
                printf("Erro ao digitar.\nTente novamente em %d segundo. \n", cont);
                Sleep(1000);
                system("cls");
                cont--;
                printf("Erro ao digitar.\nTente novamente em %d segundo. \n", cont);
                Sleep(1000);
                system("cls");
                cont--;
                printf("Erro ao digitar.\nTente novamente em %d segundo. \n", cont);
                Sleep(1000);
}

void novo_arquivo(int n, unsigned int cdg){
    FILE *a, *b;
    char linha[100];
    Pdados pessoa;
    unsigned int flag2 = 0;

    // Abre o arquivo de saída uma vez, fora do loop
    if (n == 1) {
        b = fopen("Feminos.txt", "a");
    } else if (n == 2) {
        b = fopen("Masculinos.txt", "a");
    } else if (n == 4) {
        b = fopen("Idade.txt", "a");
    }
    if(b == NULL){
        printf("Erro!\n");
        return;
    }

    a = fopen("ListaUsuarios.txt", "r");
    if(a == NULL){
        printf("Erro!\n");
        fclose(b);
        return;
    }
    else{
        while(fgets(linha, sizeof(linha), a) != NULL){
            sscanf(linha, "%u %[^0-9] %d %c", &pessoa.cdg, pessoa.nome, &pessoa.idade, &pessoa.sexo);
            if(n == 1){
                if(pessoa.sexo == 'F' || pessoa.sexo == 'f'){
                    if(flag2 == 0){
                        fprintf(b, "Mulheres encontradas: \n");
                        flag2++;
                    }
                    fprintf(b, "%d %s %d %c\n", pessoa.cdg, pessoa.nome, pessoa.idade, pessoa.sexo);
                }
            }
            if(n == 2){
                if(pessoa.sexo == 'M' || pessoa.sexo == 'm'){
                    if(flag2 == 0){
                        fprintf(b, "Homens encontrados: \n");
                        flag2++;
                    }
                    fprintf(b, "%d %s %d %c\n", pessoa.cdg, pessoa.nome, pessoa.idade, pessoa.sexo);
                }
            }
            if(n == 4){
                if(pessoa.idade == cdg){
                    if(flag2 == 0){
                        fprintf(b, "Pessoas de %u anos encontradas: \n", cdg);
                        flag2++;
                    }
                    fprintf(b, "Codigo: %d | Nome --> %s | Sexo --> %c\n", pessoa.cdg, pessoa.nome, pessoa.sexo);
                }
            }
        }
    }
    fclose(a);
    fclose(b);
}