#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <ctype.h>
#include <stdbool.h>


typedef struct {
    int id;
    char nome[150];
    char email[150];
    int idade;
    char genero;
    float peso;
    float altura;
    char senha[150];    
} User;

int checkPassword(char senha[]){
    int comprimento = strlen(senha);
    int temMinuscula = 0;
    int temMaiuscula = 0;
    int temNumero = 0;
    int temEspecial = 0;
    
    if (comprimento < 8) {
        return 0; // Senha muito curta
    }
    
    for (int i = 0; i < comprimento; i++) {
        if (islower(senha[i])) {
            temMinuscula = 1;
        } else if (isupper(senha[i])) {
            temMaiuscula = 1;
        } else if (isdigit(senha[i])) {
            temNumero = 1;
        } else {
            temEspecial = 1;
        }
    }
    
    if (temMinuscula && temMaiuscula && temNumero && temEspecial) {
        return 1; // Senha forte
    } else {
        return 0; // Senha fraca
    }
}

void bdUser() {
    FILE *arquivo;
    arquivo = fopen("usuarios.csv", "r"); // Abrindo o arquivo no modo de leitura
    if (arquivo == NULL) {
        arquivo = fopen("usuarios.csv", "a"); // Abrindo o arquivo no modo de escrita (append)
        if (arquivo == NULL) {
            printf("Erro ao criar o arquivo.");
            exit(1);
        }
        fprintf(arquivo, "ID,Nome,Email,Idade,Genero,Peso,Altura,Senha\n"); // Escrevendo cabeçalho no arquivo
        fclose(arquivo);
    } else {
        fclose(arquivo); 
    }
}

//Adiciona o usuario 
void addUserBd(User usuario) {
    FILE *arquivo;
    arquivo = fopen("usuarios.csv", "a"); // Abrindo o arquivo no modo de escrita (append)
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }
    fprintf(arquivo, "%d,%s,%s,%d,%c,%.2f,%.2f,%s\n", usuario.id, usuario.nome, usuario.email, usuario.idade, usuario.genero, usuario.peso, usuario.altura, usuario.senha); // Escrevendo os dados do usuário no arquivo
    fclose(arquivo);
}

//Lê o arquivo usuarios.csv
void viewUser() {
    FILE *arquivo;
    char linha[256]; 
    arquivo = fopen("usuarios.csv", "r"); 
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }

    printf("Dados dos usuarios:\n");
    // Lendo e exibindo cada linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha);
    }

    fclose(arquivo);
}

//Cria o ID
int userID() {
    FILE *arquivo;
    arquivo = fopen("usuarios.csv", "r"); 
    if (arquivo == NULL) {
        return 1; // Retorna 1 se o arquivo não existir, indicando que este será o primeiro ID
    }

    // Variável para armazenar o maior ID encontrado
    int maxId = 0;

    // Lendo e analisando cada linha do arquivo
    char linha[256]; 
    while (fgets(linha, sizeof(linha), arquivo)) {
        // Usando sscanf para extrair o ID da linha
        int id;
        sscanf(linha, "%d,", &id);
        if (id > maxId) {
            maxId = id;
        }
    }

    fclose(arquivo);

    // Incrementando o maior ID encontrado em 1 para obter um novo ID único
    return maxId + 1;
}

//Cadastrar usuario
void registerUser() {
    User novoUsuario;
    printf("Nome:\n");
    scanf("%s", novoUsuario.nome);
    printf("Email:\n");
    scanf("%s", novoUsuario.email);
    printf("Idade:\n");
    scanf("%d", &novoUsuario.idade);
    do {
        printf("Genero (M/F):\n");
        scanf(" %c", &novoUsuario.genero);
        novoUsuario.genero = toupper(novoUsuario.genero); // Convertendo para maiúsculas
    } while (novoUsuario.genero != 'M' && novoUsuario.genero != 'F');
    printf("Peso:\n");
    scanf("%f", &novoUsuario.peso);
    printf("Altura:\n");
    scanf("%f", &novoUsuario.altura);
    do {     
        printf("Senha (A senha tem que conter no minimo 8 caracteres, 1 letra minuscula, 1 maiuscula, 1 caracter especial e 1 numero):\n");
        scanf("%s", novoUsuario.senha);
    } while (checkPassword(novoUsuario.senha) == 0);

    novoUsuario.id = userID(); 

    addUserBd(novoUsuario);
    printf("Usuário registrado\n");
}

//Editar usuario 
void editUser(int id) {
    FILE *arquivo;
    FILE *temp;
    char linha[256];
    User usuario;

    arquivo = fopen("usuarios.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }

    temp = fopen("temp.csv", "w");
    if (temp == NULL) {
        printf("Erro ao abrir o arquivo temporario.");
        exit(1);
    }

    bool encontrado = false;
    while (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "%d,%[^,],%[^,],%d,%c,%f,%f,%s", &usuario.id, usuario.nome, usuario.email, &usuario.idade, &usuario.genero, &usuario.peso, &usuario.altura, usuario.senha);
        if (usuario.id == id) {
            encontrado = true;
            printf("Dados atuais do usuario:\n");
            printf("Nome: %s\n", usuario.nome);
            printf("Email: %s\n", usuario.email);
            printf("Idade: %d\n", usuario.idade);
            printf("Genero: %c\n", usuario.genero);
            printf("Peso: %.2f\n", usuario.peso);
            printf("Altura: %.2f\n", usuario.altura);
            printf("Senha: %s\n", usuario.senha);

            printf("Novos dados do usuario:\n");
            printf("Nome:\n");
            scanf("%s", usuario.nome);
            printf("Email:\n");
            scanf("%s", usuario.email);
            printf("Idade:\n");
            scanf("%d", &usuario.idade);
            do {
                printf("Genero (M/F):\n");
                scanf(" %c", &usuario.genero);
                usuario.genero = toupper(usuario.genero);
            } while (usuario.genero != 'M' && usuario.genero != 'F');
            printf("Peso:\n");
            scanf("%f", &usuario.peso);
            printf("Altura:\n");
            scanf("%f", &usuario.altura);
            do {     
                printf("Senha (A senha tem que conter no minimo 8 caracteres, 1 letra minuscula, 1 maiuscula, 1 caracter especial e 1 numero):\n");
                scanf("%s", usuario.senha);
            } while (checkPassword(usuario.senha) == 0);

            fprintf(temp, "%d,%s,%s,%d,%c,%.2f,%.2f,%s\n", usuario.id, usuario.nome, usuario.email, usuario.idade, usuario.genero, usuario.peso, usuario.altura, usuario.senha);
        } else {
            fprintf(temp, "%s", linha);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("usuarios.csv");
    rename("temp.csv", "usuarios.csv");

    if (!encontrado) {
        printf("Usuario não encontrado.\n");
    } else {
        printf("Usuario editado com sucesso.\n");
    }
}

//excluir usuario
void deleteUser(int id) {
    FILE *arquivo;
    FILE *temp;
    char linha[256];
    User usuario;

    arquivo = fopen("usuarios.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }

    temp = fopen("temp.csv", "w");
    if (temp == NULL) {
        printf("Erro ao abrir o arquivo temporário.");
        exit(1);
    }

    bool encontrado = false;
    while (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "%d,%[^,],%[^,],%d,%c,%f,%f,%s", &usuario.id, usuario.nome, usuario.email, &usuario.idade, &usuario.genero, &usuario.peso, &usuario.altura, usuario.senha);
        if (usuario.id == id) {
            encontrado = true;
            printf("Usuario excluido com sucesso:\n");
        } else {
            fprintf(temp, "%s", linha);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("usuarios.csv");
    rename("temp.csv", "usuarios.csv");

    if (!encontrado) {
        printf("Usuario não encontrado.\n");
    }
}
//mMenu principal 
void menu() {
    int y;
    int opc; 
    printf("================\nMenu:\n 1:Visualizar usuario\n 2:Cadastrar usuario\n 3:Editar usuario\n 4:Excluir usuario \n 0:Sair\nDigite o numero para acessar a opcao desejada\n");

    if (scanf("%d", &opc) != 1) {
        while (getchar() != '\n');
        printf("Entrada invalida. Por favor, insira um numero.\n");

        menu();
    } else {
        switch (opc) {
            case 0:
                exit(1);
                break;
            case 1:
                printf("==============\nVisualizar Usuarios\n==============\n");
                viewUser();
                menu();
                break;
            case 2:
                printf("==============\nCadastro\n==============\n");
                registerUser();
                menu();
                break;

            case 3:
                printf("==============\nEditar usuario\n==============\n");
                printf("Digite o ID:\n");
                scanf("%d",&y);
                editUser(y);
                menu();
                break;
            case 4:
                printf("==============\nExcluir usuario\n==============\n");
                printf("Digite o ID:\n");
                scanf("%d",&y);     
                deleteUser(y);     
                menu();  
                break;

            default:
                menu();
        }
    }
}

int main() {
    bdUser();
    menu();
    return 0;
}