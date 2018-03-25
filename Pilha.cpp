#include <iostream>
#include <stdlib.h>
#include <stdexcept>

using namespace std;

/* Tamanho em que a pilha será inicializada */
int const maxtam = 1000;


/* Inicializando a pilha */
int Pilha[maxtam];

/* Topo da pilha */
int topo;

/* Construtor da pilha setando o tamanho dela como -1. */
void Pilha_Construtor()
{
    topo = -1;
}

/* Método que verifica se a pilha está vazia */
bool Pilha_vazia()
{
    return topo == -1; // O retorno desse método é booleano, ele retornará true ou false caso o topo seja ou não -1.
}

/* Metodo que verifica se a pilha está cheia. */
bool Pilha_cheia()
{
    return topo >= maxtam-1; // O retorno desse método é booleano, ele retornará true ou false caso o topo seja ou não maior ou igual ao tamanho máximo da pilha.
}

/* Método de empilhar.
Procedimento:
- Verificar se a pilha está cheia, caso esteja, lançar uma exceção informando que a pilha está cheia.
- Caso a pilha não esteja cheia, incremente o topo em uma posição e por fim adicione o valor no vetor referente ao topo incrementado.
*/
void Pilha_Push(int valor)
{

    if(Pilha_cheia())
    {
        throw std::out_of_range("Pilha cheia.");
    }
    topo++;
    Pilha[topo] = valor;
}

/* Método de desempilhar.
Procedimento:
- Verificar se a pilha está vazia, caso esteja, lançar uma exceção informando que a pilha está vazia.
- Caso a pilha não esteja vazia, reduza o topo em uma posição e em segudia retorne o valor da pilha uma posição acima do topo.
*/
int Pilha_Pop()
{
    if( Pilha_vazia() )
    {
        throw std::out_of_range("Pilha vazia.");
    }
    topo--;
    return Pilha[topo+1];
}

/* Método que consulta o valor do topo da pilha */
int Pilha_consulta()
{
    if( Pilha_vazia() )
    {
        throw std::out_of_range("Pilha vazia.");
    }
    return Pilha[topo];
}

/* Método que diz qual o tamanho atual da pilha */
int Pilha_topo()
{
    if ( Pilha_vazia() )
    {
        throw std::out_of_range("Pilha vazia.");
    }
    return topo;
}

/* Limpar a pilha. */
void Pilha_limpar(){
 topo = -1;   
}

int main()
{
    /* Testando a pilha */
    Pilha_Construtor();

    int valor_topo;
    int index;

    Pilha_Push(10);
    Pilha_Push(1);
    Pilha_Push(14);
    Pilha_Push(19);
    Pilha_Push(17);

    valor_topo = Pilha_consulta();
    index = Pilha_topo(); // Verifica qual o index está o topo da pilha

    cout<<(valor_topo);
    //cout<<(index);

    return 0;
}
