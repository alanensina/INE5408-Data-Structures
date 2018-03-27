#include <iostream>
using namespace std;

int main()
{

    /*
    Um ponteiro é uma variável capaz de armazenar um endereço de memória ou o endereço de outra
    variável.
    Quando criamos um ponteiro, setamos qual o tipo dele, e o mesmo deve apontar para outra variável que seja do mesmo tipo,
    ou seja, um ponteiro de inteiro deve apontar para uma outra variável que seja do tipo inteiro.
    */

    int *ptr; // Criando um ponteiro que aponta para um inteiro
    int valor = 500;

    ptr = &valor; // Ponteiro está apontando para o valor referenciado da variável valor
    cout << "O valor antigo era: "<< *ptr << endl;

    *ptr = 1000; // Através da derreferência, atribui-se um novo valor na variável "valor"
    cout << "O novo valor agora é: " << valor << endl;
    cout << "O endereço de memória do ponteiro é: " << ptr << endl;

    /* Trabalhando com vetores: */
    /* O ponteiro para inteiro "vetor" irá apontar para cada uma das posições do vetor*/
    int *vetor; // Criando um ponteiro que aponta para um vetor
    vetor = new int[5];
    vetor[0] = 5, vetor[1] = 12,  vetor[2] = 3,  vetor[3] = 19,  vetor[4] = 76;

    for(int i = 0 ; i < 5 ; i++)
    {
        cout << "vetor[" << i << "] : " << vetor[i] << endl;
    }

    cout << "O vetor está ocupando o espaço na memória: " << vetor << endl;

    delete[] vetor; // Desaloca a memória ocupada pelo vetor.

    return 0;
}
