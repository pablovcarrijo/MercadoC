#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct{
    char name[50];
    int cod;
    float price;
}Product; 

typedef struct{
    Product product;
    int quantidade;
}Carrinho;

void menu();
void cadastrarProduto();
void listarProduto();
void comprarProduto();
void visualizarCarrinho();
Product pegarProdutoPorCodigo(int codigo);
int * temNoCarrinho(int codigo);
void fecharPedido();

static int count = 0;
static Product produtos[50];
static Carrinho carrinho[50];
static int countCarrinho = 0;

void infoProduto(Product prod){
    printf("Código: %d\nNome: %s\nPreco: %.2f\n", prod.cod, strtok(prod.name, "\n"), prod.price);
}

int main(){
    menu();
    return 0;
}

void menu(){

    int opc = 0;
    while(opc != 6){
        printf("=============================\n");
        printf("==========BEM VINDO==========\n");
        printf("==========Geek shop==========\n");
        printf("=============================\n");

        printf("Selecione uma opcão abaixo: \n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Comprar produto\n");
        printf("4 - Visualizar carrinho\n");
        printf("5 - Fechar pedido\n");
        printf("6 - Sair do programa\n");
        scanf("%d%*c", &opc);

        switch (opc)
        {
        case 1:
            cadastrarProduto();
            break;
        case 2:
            listarProduto();
            break;
        case 3:
            comprarProduto();
            break;
        case 4:
            visualizarCarrinho();
            break;
        case 5:
            fecharPedido();
            break;
        case 6:
            printf("Saindo do programa...\n");
            sleep(1.4);
            exit(0);
            break;
        default:
            printf("Opcao invalida!\n");
            sleep(1.4);
            menu();
            break;
        }

    }

}

void cadastrarProduto(){

    printf("CADASTRO DE PRODUTO\n");
    printf("===================\n");

    printf("Didite o nome do produto: ");
    fgets(produtos[count].name, 50, stdin);

    printf("Digite o preço do produto: ");
    scanf("%f", &produtos[count].price);

    produtos[count].cod = (count + 1);
    count ++;
    printf("Cadastrando...\n");
    sleep(1.4);
    menu();

}
void listarProduto(){

    if(count == 0){
        printf("Nehhum produto listado\n");
        sleep(2);
        menu();
    }
    else{
        printf("\n");
        for(int i = 0; i < count; i++){
            infoProduto(produtos[i]);
            printf("------------------\n");
            sleep(1.4);

        }
    }

}
void comprarProduto(){
    
    if(count <= 0){
        printf("Nenhum produto listado para comprar\n");
        sleep(1.4);
        menu();
    }
    else if(count > 0){

        printf("=============Produtos disponíveis=============\n");
        for(int i = 0; i < count; i++){
            infoProduto(produtos[i]);
            printf("================\n");
            sleep(1);
        }

        int codComprar;
        printf("Digite o código do produto a comprar: ");
        scanf("%d%*c", &codComprar);
        int tem_mercado = 0;
        for(int i = 0; i < count; i++){
            if(produtos[i].cod == codComprar){
                tem_mercado = 1;
                if(countCarrinho > 0){
                    int * retorna = temNoCarrinho(codComprar);
                    if(retorna[0] == 1){
                        carrinho[retorna[1]].quantidade++;
                        printf("Aumentei a quantidade do produto %s já existente no carrinho\n",
                        strtok(carrinho[retorna[1]].product.name, "\n"));
                        sleep(1.4);
                        menu();
                    }
                    else{
                        Product p = pegarProdutoPorCodigo(codComprar);
                        carrinho[countCarrinho].product = p;
                        carrinho[countCarrinho].quantidade = 1;
                        countCarrinho++;
                        printf("Adicionando o produto %s ao carrinho!\n", strtok(p.name, "\n"));
                        sleep(1.5);
                        menu();
                    }
                }else{
                    Product p = pegarProdutoPorCodigo(codComprar);
                    carrinho[countCarrinho].product = p;
                    carrinho[countCarrinho].quantidade = 1;
                    countCarrinho++;
                    printf("Adionando o produto %s ao carrinho!\n", strtok(p.name, "\n"));
                    sleep(1.5);
                    menu();
                }
            }
        }if(tem_mercado < 1){
            printf("Não foi encontrado o produto com o codigo %d\n", codComprar);
            sleep(1.3);
            menu();
        }
    
    }else{
        printf("Ainda não existem produtos para vender \n");
        sleep(2);
        menu();
    }
}
void visualizarCarrinho(){

    if(countCarrinho == 0){
        printf("Nenhum elemento cadastrado para visualizar\n");
        sleep(1.4);
        menu();
    }
    else{
        printf("===========CARRINHO DE COMPRAS===========\n");
        for(int i = 0; i < countCarrinho; i++){
            infoProduto(carrinho[i].product);
            printf("=================\n");
            sleep(1.4);
        }
        menu();
    }

}

Product pegarProdutoPorCodigo(int codigo){
    Product p;
    for(int i = 0; i < count; i++){
        if(produtos[i].cod == codigo){
            p = produtos[i];
        }
    }
    return p;
}

int * temNoCarrinho(int codigo){
    int static retorno[] = {0, 0};
    for(int i = 0; i < countCarrinho; i++){
        if(carrinho[i].product.cod == codigo){
            retorno[0] = 1; //tem o produto no stock
            retorno[1] = i; //guarda a sua posição
        }
    }
    return retorno;
}

void fecharPedido(){

    if(countCarrinho == 0){
        printf("Nenhum elemento no carrinho para fechar pedido\n");
        sleep(1.4);
        menu();
    }
    else{
        float valorTotal = 0;

        printf("==========PRODUTOS DO CARRINHO==========\n");

        for(int i = 0; i < countCarrinho; i++){
            Product p = carrinho[i].product;
            int quantidade = carrinho[i].quantidade;
            valorTotal += p.price * quantidade;
            infoProduto(p);
            printf("Quantidade: %d\n", quantidade);
            printf("==========================\n");
            sleep(1);
        }
        printf("Sua fatura é: %.2f\n", valorTotal);
        countCarrinho = 0;
        printf("Obrigado pela preferência!\n");
        sleep(1);
        menu();
    }

}