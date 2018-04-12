  //! Tarefa de Estruturas de Dados - Pilha encadeada
 /*
   \author Alan Vinicius Cezar Ensina - Matrícula 16206354
   \since 11/04/2018
   \version 1.0
   \copyright @ Alan Ensina
    */

#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <cstdint>
#include <stdexcept>

namespace structures {

  //! Template da classe da pilha encadeada
template<typename T>
class LinkedStack {
 public:
    //! Construtor padrão
    LinkedStack() {
        size_ = 0u;
        top_ = nullptr;
    }
    //! Destrutor de objetos
    ~LinkedStack() {
        clear();
    }
    //! Método que limpar a pilha encadeada
    void clear() {
        Node *atual, *anterior;
        atual = top_;
        while (atual != nullptr) {
            anterior = atual;
            atual = atual->next();
            delete anterior;
            }
            size_ = 0u;
            top_ = nullptr;
    }
    //! Método que insere um elemento no topo da pilha encadeada
    void push(const T& data) {
        if (empty()) {
            Node *novoElemento = new Node(data, top_);
            if (novoElemento == nullptr) {
                throw std::out_of_range("Erro: a pilha está cheia!");
            } else {
                top_ = novoElemento;
                size_ += 1;
            }
        } else {
            Node *novoElemento;
            novoElemento = new Node(data, top_);
            if (novoElemento == nullptr) {
               throw std::out_of_range("Erro: a pilha está cheia!");
            } else {
                top_ = novoElemento;
                size_ += 1;
            }
        }
    }

    //! Método que retira um elemento da pilha encadeada
    T pop() {
        if (empty()) {
            throw std::out_of_range("Erro: a pilha está vazia!");
        } else if (size() == 1) {
            Node* retirado = top_;
            T valor = retirado->data();
            top_ = nullptr;
            delete retirado;
            size_ -= 1;
            return valor;
            } else {
                Node *retirado, *anterior;
            T valor;
            retirado = top_;
            anterior = retirado->next();
            valor = retirado->data();
            top_ = anterior;
            size_ -= 1;
            delete retirado;
            return valor;
        }
    }
    //! Método que informa o elemento no topo da pilha
    T& top() const {
        if (empty()) {
            throw std::out_of_range("Erro: a pilha está vazia!");
        }
        return top_->data();
    }
    //! Verifica se a pilha está vazia
    bool empty() const {
        return (size_ == 0u);
    }
    //! Informa o tamanho atual da pilha
    std::size_t size() const {
        return size_;
    }

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
            {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_;
    };

    Node* top_;  // nodo-topo
    std::size_t size_;  // tamanho
};

}  // namespace structures

#endif
