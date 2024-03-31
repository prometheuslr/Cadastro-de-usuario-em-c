#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <ctype.h>
#include <stdbool.h>

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

void bdUser(){
    // dados dos usuario em csv ou .xlsx
}

void login(){
    
}

void registerUser(){
    char nome[150];
    char email[150];
    char senha[150];
    char confSenha[150];
    int idade;
    float pesso, altura;
    int x = 0;
    bool y = false;

    printf("Nome:\n");
    scanf("%s",nome);
    printf("Email:\n");
    scanf("%s",email);
    printf("Idade:\n");
    scanf("%d",&idade);
    printf("Pesso:\n");
    scanf("%f",&pesso);
    printf("Altura:\n");
    scanf("%f",&altura);

    do
    {     
        printf("Senha(A senha tem que conter no minimo 8 caracters, 1 letra minuscula, 1 maiuscula, 1 caracter especial e 1 numero):\n");
        scanf("%s",senha);
        x = checkPassword(senha);
    } while (x==0);


    do
    {
        printf("Digite a senha novamente:\n");
        scanf("%s",confSenha); 
        if(strcmp(senha,confSenha)==0){
            y = true;
        }
        else{
            printf("Senha incorreta");
        }
    } while (y == false);
    
    printf("Usuario registrado\n %s %s %d %f %f %s %s", nome, email, idade, pesso, altura, senha, confSenha);


}


void menu() {
    int opc; 
    printf("================\nMenu:\n 1:Login\n 2:Cadastrar\n 0:Sair\nDigite o numero para acessar a opcao desejada\n");

    if (scanf("%d", &opc) != 1) {
        while (getchar() != '\n');
        printf("Entrada invalida. Por favor, insira um numero.\n");

        menu();
    } else {
        switch (opc) {
            case 0:
                break;
            case 1:
                printf("Login");
                login();
                break;
            case 2:
                printf("==============\nCadastro\n==============\n");
                registerUser();
                break;

            default:
                menu();
        }
    }
}

int main() {
    menu();
    return 0;
}