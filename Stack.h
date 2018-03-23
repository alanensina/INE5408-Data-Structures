//! Tarefa de Estruturas de Dados - Pilha
/*
  \author Alan Vinicius Cezar Ensina - Matrícula 16206354
  \since 09/03/2018
  \version 1.0
  \copyright @ Alan Ensina
*/

#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>   // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template<typename T>

    //! Declaração da classe ArrayStack
class ArrayStack {
    //! Construtor sem parâmetro
 public:
    ArrayStack();

    //! Construtor com parâmetro
  explicit ArrayStack(std::size_t max);

    //! Destrutor
    ~ArrayStack();

    //! Método de empilhar com parâmetro de entrada
    void push(const T& data);   // empilha

    //! Método de desempilhar
    T pop();   // desempilha

    //! Método que retorna o valor no topo da pilha
    T& top();

    //! Método que limpa a pilha
    void clear();   // limpa

    //! Método que retorna o tamanho  atual da pilha
    std::size_t size();   // tamanho

    //! Método que retorna o tamanho total da pilha
    std::size_t max_size();

    //! Retorna true ou false se a pilha estiver vazia
    bool empty();   // vazia

    //! Retorna true ou false se a pilha estiver cheia
    bool full();   // cheia

 private:
    T* contents;
    int top_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

#endif

template<typename T>
bool structures::ArrayStack<T>::empty() {
    if (top_ == -1) {
        return true;
    }
    return false;
}

template<typename T>
bool structures::ArrayStack<T>::full() {
    if (top_ == max_size_-1) {
        return true;
    }
    return false;
}

template<typename T>
void structures::ArrayStack<T>::clear() {
    top_ = -1;
}

template<typename T>
T structures::ArrayStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Pilha vazia");
    } else {
        top_ = top_-1;
        return contents[top_+1];
    }
}

template<typename T>
void structures::ArrayStack<T>::push(const T& data) {
  if (full())  {
       throw std::out_of_range("Pilha cheia");
  } else {
       top_ = top_ + 1;
       contents[top_] = data;
    }
}

template<typename T>
T& structures::ArrayStack<T>::top() {
  if (empty()) {
  throw std::out_of_range("Pilha vazia");
    } else {
        return contents[top_];
    }
}

template<typename T>
structures::ArrayStack<T>::ArrayStack(std::size_t max) {
    top_ = -1;
    max_size_ = max;
    contents = new T[max_size_];
}

template<typename T>
structures::ArrayStack<T>::ArrayStack() {
    contents = new T[DEFAULT_SIZE];
    top_ = -1;
}

template<typename T> structures::ArrayStack<T>::~ArrayStack() {
    delete[] contents;
}

template<typename T> size_t structures::ArrayStack<T>::size() {
    return top_ + 1;
}

template<typename T> size_t structures::ArrayStack<T>::max_size() {
    return max_size_;
}
