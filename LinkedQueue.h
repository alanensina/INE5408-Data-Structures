  //! Tarefa de Estruturas de Dados - Fila encadeada
 /*
   \author Alan Vinicius Cezar Ensina - Matrícula 16206354
   \since 11/04/2018
   \version 1.0
   \copyright @ Alan Ensina
    */

#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <stdexcept>
#include <cstdint>

namespace structures {

template<typename T>
    //!  Classe da fila encadeada
class LinkedQueue {
 public:
    //!  Construtor sem parâmetros
    LinkedQueue(): head{nullptr}, tail{nullptr}, size_{0} {}

    //!  Destrutor de objetos
    ~LinkedQueue() {
        clear();
    }

    //!  Método que limpa a lista
    void clear() {
        Node *before, *atual;
        atual = head;
        while (atual != nullptr) {
            before = atual;
            atual = atual->next();
            delete before;
        }
        size_ = 0u;
        head = nullptr;
        tail = nullptr;
    }

    //!  Método que insere um elemento dado por parâmetro na fila
    void enqueue(const T& data) {
        Node *novoElemento = new Node(data, nullptr);
        if (empty()) {
            head = novoElemento;
            tail = novoElemento;
        } else {
            tail->next(novoElemento);
        }
        tail = novoElemento;
        ++size_;
    }

    //!  Método que remove um elemento da fila
    T dequeue() {
        T retorno;
        Node *elimina;
        if (empty()) {
            throw std::out_of_range("Erro: A lista está vazia.");
        } else {
            elimina = head;
            retorno = elimina->data();
            head = elimina->next();
            if (size_ == 1) {
                tail = nullptr;
            }
            --size_;
            delete elimina;
            return retorno;
        }
    }

    //!  Método que informa o primeiro elemento da fila
    T& front() const {
        if (empty()) {
            throw std::out_of_range("Erro: A lista está vazia.");
        }
        return head->data();
    }

    //!  Método que informa o último elemento da fila
    T& back() const {
        if (empty()) {
            throw std::out_of_range("Erro: A lista está vazia.");
        }
        return  tail->data();
    }

    //!  Método que verifica se a fila está vazia
    bool empty() const {
        return size_ == 0;
    }

    //!  Método que verifica o tamanho atual da fila
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
        Node* next_{nullptr};
    };

 private:
    Node* head;  // nodo-cabeça
    Node* tail;  // nodo-fim
    std::size_t size_;  // tamanho
};

}  //! namespace structures

#endif

