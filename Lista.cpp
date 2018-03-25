#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std;

int const maxtam = 100;
int back;
int Lista[maxtam];

/* Construtor da lista */
void Lista_Construtor()
{
    back = -1;
}

/* Método que limpa a lista */
void Lista_limpar()
{
    back = -1;
}

/* Método que verifica se a lista está vazia */
bool Lista_vazia()
{
    return back <= -1;
}

/* Método que verifica se a lista está cheia */
bool Lista_cheia()
{
    return back == maxtam-1;
}

/* Método que retorna o tamanho atual da lista. */
int Lista_tamanho()
{
    return back+1;
}

/*Método que insere um valor no início da lista.
- Verifica se a lista está cheia
- Deve-se incrementar o fim da lista em uma posição e em seguida "puxar" os elementos da lista até o fim da lista
- Depois de mover todos os elementos da lista até o fim dela, insira o valor dado por parâmetro na posição zero do vetor
*/
void Lista_Inserir_Inicio(int valor)
{
    int position; //Auxiliará a "empurrar" os elementos

    if( Lista_cheia())
    {
        throw std::out_of_range("Lista cheia");
    }

    back++; // Incremento da lista
    position = back; // Posição receberá o valor do index do fim da lista

    /* Puxando os elementos da lista */
    while (position > 0)
    {
        Lista[position] = Lista[position-1]; // Posição receber o valor que está na posição anterior
        position--;  // Posição decrementa e vai para o próximo elemento
    }
    Lista[0] = valor;
}

/* Método que insere no fim da lista
- Verifica se há espaço na lista
- Caso haja espaço, incremente uma posição no fim da lista
- Por fim, adicione o valor dado por parâmetro na posição do fim da lista no vetor
*/
void Lista_Inserir_Fim(int valor)
{
    if( Lista_cheia())
    {
        throw std::out_of_range("Lista cheia");
    }
    back++;
    Lista[back] = valor;
}

int Lista_Retira_Fim()
{
    if(Lista_vazia())
    {
        throw std::out_of_range("Lista vazia");
    }
    back--;
    return Lista[back+1];
}

/* Método que retira um elemento do início da lista.
- Verifica se a lista está vazia.
- O fim da lista é decrementado em uma posição e a posição zero do vetor será armazenada em uma variável temporária
- Uma variável posicao criada com o valor zero, ela auxiliará a "puxar" os elementos no vetor
- Puxe os elementos no vetor
- Retorne o valor armazenado na variável temporária
*/
int Lista_retira_Inicio()
{
    if( Lista_vazia())
    {
        throw std::out_of_range("Lista vazia.");
    }

    int valor, posicao;

    back--; // Decrementa a lista em uma posição
    valor = Lista[0]; // Armazena o valor que será retirado da lista em uma variável temporária para que não corra risco de sobreescrevê-la
    posicao = 0;

    /* Puxa os elementos do vetor */
    while (posicao <= back)
    {
        Lista[posicao] = Lista[posicao+1];
        posicao++;
    }

    return valor; // Retorna valor armazenado.
}

/* Método que adiciona um elemento na posição desejada
- Verifica se a lista está cheia e se a posição desejada existe na lista.
- Adiciona uma posição na lista
- Uma variável temporária "atual" é criada e será utilizada para mover as posições do vetor
- Por fim, o valor dado por parâmetro é inserido no index dado também por parâmetro.
*/
void Lista_Adiciona_na_Posicao(int valor, int index)
{
    if( Lista_cheia())
    {
        throw std::out_of_range("Lista cheia.");
    }
    else if(index < 0 || index > back+1)
    {
        throw std::out_of_range("Posição inválida.");
    }

    int atual; // Variável temporária utilizada para mover os elementos

    /* Move os elementos da lista afim de que deixe o índice dado por parâmetro esteja "livre" para ser modificado. */
    back++;
    atual = back;

    while (atual > index)
    {
        Lista[atual] = Lista[atual-1];
        atual--;
    }

    Lista[index] = valor; // Valor é inserido no parâmetro desejado.
}

/* Método que retira o elemento em determinada posição
- Verifica se a lista está vazia e se a posição é válida
- Decrementa a lista em uma posição
- Uma variável temporária (valor) é criada onde o valor do índice dado por parâmetro será armazenada
- Outra variável temporária é criada (atual), essa variável armazenará o índice dado por parâmetro e será utilizada na ordenação do vetor.
- Puxe os elementos
- Retorne o valor armazenado na variável temporária "valor"
*/
int Lista_Retira_da_Posicao(int index)
{
    if( Lista_vazia())
    {
        throw std::out_of_range("Lista vazia.");
    }
    else if(index < 0 || index > back)
    {
        throw std::out_of_range("Posição inválida.");
    }

    int atual, valor;

    back--;
    valor = Lista[index];
    atual = index;

    while(atual <= back)
    {
        Lista[atual] = Lista[atual + 1];
        atual++;
    }
    return valor;
}

/* Método que adiciona de maneira ordenada dentro do vetor
- Verifica se a lista está vazia
- Uma variável temporária é criada (atual) e atribuida o valor zero. Elá irá auxiliar a "varrer" o vetor e encontrar uma posição vazia.
- Após varrer o vetor e encontrar uma posição vazia, retorne o método chamando o método Lista_Adiciona_na_Posicao com o valor de paramentro e o valor "atual"
*/
void Lista_Adiciona_Ordenado(int valor)
{
    if( Lista_cheia())
    {
        throw std::out_of_range("Lista cheia.");
    }

    int atual = 0;

    while (atual <= back && valor < Lista[atual])
    {
        atual++;
    }

    return Lista_Adiciona_na_Posicao(valor,atual);
}

/* Método que informa se o elemento está ou não na lista
- Verifica se a lista está vazia
- Varre todas as posições do vetor verificando uma a uma se é o mesmo valor com o parâmetro de entrada
- Retorna true ou false
*/
bool Lista_Contem(int valor)
{
    if( Lista_vazia())
    {
        throw std::out_of_range("Lista vazia.");
    }

    int posicao = 0;

    while (posicao <= back)
    {
        if( Lista[posicao] == valor)
        {
            return true;
        }
        else
        {
            posicao++;
        }
    }
    return false;
}

int main()
{

Lista_Construtor();

Lista_Inserir_Inicio(10);
Lista_Adiciona_Ordenado(90);
//Lista_Retira_da_Posicao(0);
Lista_Adiciona_na_Posicao(50,2);


cout<<(Lista_tamanho());

    return 0;
}
