#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

// declaraçao da struct com as propriedades
typedef struct item
{
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// declaraçao das funções
Item cadastrarItem(Item item);
void exibirItem(Item *item);
Item *buscarItem(Item mochila[], char nome[], int numItens);
int removerItem(Item mochila[], char nome[], int *numItens);
void imprimirLista(Item mochila[], int numItens);

// solicita e armazena os dados do item
Item cadastrarItem(Item item)
{
    printf("\nInforme o nome do item: ");
    scanf(" %[^\n]", item.nome);
    printf("Informe o tipo do item: ");
    scanf(" %[^\n]", item.tipo);
    printf("Informe a quantidade do item: ");
    scanf(" %d", &item.quantidade);

    return item;
}

// exibe os dados do item
void exibirItem(Item *item)
{
    // valida se item é vazio
    if (item == NULL)
    {
        printf("\nItem não encontrado.\n");
        return;
    }

    printf("\n------------------------------------------------\n");
    printf("Nome: %s\n", item->nome);
    printf("Tipo: %s\n", item->tipo);
    printf("Quantidade: %d\n", item->quantidade);
    printf("------------------------------------------------\n");
}

// busca um item na mochila
Item *buscarItem(Item mochila[], char nome[], int numItens)
{
    if (numItens == 0)
    {
        printf("\nNenhum item cadastrado.\n");
        return NULL;
    }

    for (int i = 0; i < numItens; i++)
    {
        if (strcmp(mochila[i].nome, nome) == 0)
        {
            // retorna item encontrado
            return &mochila[i];
        }
    }
    // retorna NULL se item não for encontrado
    return NULL;
}

// remove um item da mochila
int removerItem(Item mochila[], char nome[], int *numItens)
{
    if (*numItens == 0)
    {
        printf("\nNenhum item cadastrado.\n");
        return 0;
    }

    for (int i = 0; i < *numItens; i++)
    {
        if (strcmp(mochila[i].nome, nome) == 0)
        {
            // substitui o item removido pelo último item
            mochila[i] = mochila[*numItens - 1];
            // decrementa o contador de itens
            (*numItens)--;
            printf("\nItem removido com sucesso.\n");
            return 1;
        }
    }

    printf("\nItem não encontrado.\n");
    return 0;
}

// exibe todos os itens cadastrados
void imprimirLista(Item mochila[], int numItens)
{
    if (numItens == 0)
    {
        printf("\nNenhum item cadastrado.\n");
        return;
    }

    printf("\nExibindo todos os itens da mochila:\n");

    for (int i = 0; i < numItens; i++)
    {
        printf("\nItem %d:", i + 1);
        exibirItem(&mochila[i]);
    }
}

// exibe menu principal com as funções disponiveis
void menuPrincipal()
{
    // inicializa variáveis
    char opc = '\0';
    char opcao = 'S';
    Item mochila[10] = {0};
    int numItens = 0;
    char itemNome[30] = "\0";
    int result = 0;
    Item *itemBuscado = NULL;

    printf("\n***********************************************************");
    printf("\n                   Inventário da Mochila                   ");

    // laço para menu principal
    do
    {
        printf("\n***********************************************************\n");
        printf("\nSelecione uma opção: \n1. Adicionar item\n2. Remover item\n3. Listar todos os itens\n4. Buscar item\n0. Sair");
        printf("\nOpção: ");
        scanf(" %c", &opc);

        switch (opc)
        {
        case '1':
            printf("\n***********************************************************");
            printf("\n                     Cadastro do item                     \n");

            // laço para adicionar itens até o limite da mochila
            do
            {
                if (numItens > 9)
                {
                    printf("\nMochila cheia! Não é possível adicionar mais itens.\n");
                    break;
                }

                mochila[numItens] = cadastrarItem(mochila[numItens]);
                numItens++;
                imprimirLista(mochila, numItens);

                if (numItens > 9)
                {
                    printf("\nMochila cheia! Não é possível adicionar mais itens.\n");
                    break;
                }

                printf("\nCadastrar novo item? (Digite 'S' para Sim e 'N' para Não): ");
                scanf(" %c", &opcao);
            } while ((opcao == 'S' || opcao == 's') && numItens < 10);

            printf("\nVoltando ao menu anterior...\n");

            break;

        case '2':
            printf("\n***********************************************************");
            printf("\n                      Remoção de item                      \n");

            if (numItens == 0)
            {
                printf("\nNenhum item cadastrado.\n");
                printf("\nVoltando ao menu anterior...\n");
                break;
            }

            do
            {
                itemNome[30] = '\0';
                printf("\nInforme o nome do item a ser removido: ");
                scanf(" %[^\n]", itemNome);
                result = removerItem(mochila, itemNome, &numItens);
                imprimirLista(mochila, numItens);
            } while (itemNome[0] != '\0' && result != 1);

            printf("\nVoltando ao menu anterior...\n");
            break;

        case '3':
            printf("\n***********************************************************");
            printf("\n                  Listar todos os itens                   \n");

            imprimirLista(mochila, numItens);
            printf("\nVoltando ao menu anterior...\n");

            break;

        case '4':
            printf("\n***********************************************************");
            printf("\n                      Buscar item                         \n");

            if (numItens == 0)
            {
                printf("\nNenhum item cadastrado.\n");
                printf("\nVoltando ao menu anterior...\n");
                break;
            }
            else
            {
                do
                {
                    itemNome[30] = '\0';
                    printf("\nInforme o nome do item a ser buscado: ");
                    scanf(" %[^\n]", itemNome);
                    itemBuscado = buscarItem(mochila, itemNome, numItens);
                    exibirItem(itemBuscado);

                } while (itemNome[0] != '\0' && itemBuscado == NULL);
            }

            printf("\nVoltando ao menu anterior...\n");
            break;

        case '0':
            printf("\nEncerrando o jogo...\n\n");

            break;

        default:
            printf("\nOpção inválida.\n");

            break;
        }
    } while (opc != '0');
}

int main()
{
    menuPrincipal();

    return 0;
}
