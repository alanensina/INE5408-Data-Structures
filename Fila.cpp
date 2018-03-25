#include <iostream>
#include <stdexcept>

using namespace std;

/* Variáveis de controle da Fila: front e back. */
int front, back;

/* Criando uma Fila com tamanho estático de 100 posições. */
int const maxtam = 100;
int Fila[maxtam];

/* Construtor da fila. */
void Fila_Construtor()
{
    front = 0;
    back = -1;
}

/* Método que verifica se a fila está vazia. */
bool Fila_vazia()
{
    return front > back;
}

/* Método que verifica se a fila está cheia. */
bool Fila_cheia()
{
    return back >= maxtam-1;
}

/* Método que insere um valor na fila.
- Verificar se a fila está cheia
- Caso não esteja cheia, incremente uma posição no fim da fila (back)
- Por fim, insira o valor dado por parâmetro na posição back no vetor.
 */
void Fila_Inserir(int valor)
{
    if(Fila_cheia())
    {
        throw std::out_of_range("Fila cheia.");
    }
    back++;
    Fila[back] = valor;
}

/* Método que remove um valor da fila.
- Verifica se a fila está vazia
- Incremente uma posição na frente da fila para setar qual será a nova posição da frente da fila (front)
- Por fim, retorne o valor da fila na posição front-1, pois era essa a posição que estava na frente da fila antes de o front ter sido incrementado.
*/
int Fila_Remove()
{
    if(Fila_vazia())
    {
        throw std::out_of_range("Fila vazia.");
    }
    front++;
    return Fila[front-1];
}

/* Método que informa qual o elemento está na frente da fila, ou seja, qual será o prximo a sair dela. */
int Fila_Consulta()
{
    if(Fila_vazia())
    {
        throw std::out_of_range("Fila vazia.");
    }
    return Fila[front];
}

/* Método que informa o tamanho atual da fila */
int Fila_Tamanho_Atual()
{
    return (back-front)+1;
}

void Fila_Limpar()
{
    front = 0;
    back = -1;
}


/* Testando a fila. */
int main()
{

    Fila_Construtor();
    int valor; // Receberá o valor presente na frente da fila
    int qtd; // Quantidade de posições utilizadas na fila

    Fila_Inserir(5);
    Fila_Inserir(2);
    Fila_Inserir(4);
    Fila_Inserir(5);
    Fila_Inserir(9);
    Fila_Inserir(59);
    Fila_Inserir(15);
    Fila_Inserir(90);

    valor = Fila_Consulta();
    qtd = Fila_Tamanho_Atual();

    cout<<(valor);
    //cout<<(qtd);

    return 0;
}
