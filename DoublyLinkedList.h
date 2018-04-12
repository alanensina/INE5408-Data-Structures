  //! Tarefa de Estruturas de Dados - Lista Duplamente Encadeada
 /*
   \author Alan Vinicius Cezar Ensina - Matrícula 16206354
   \since 08/04/2018
   \version 1.0
   \copyright @ Alan Ensina
    */
#ifndef STRUCTURES_DOUBLY_LINKED_LIST_H
#define STRUCTURES_DOUBLY_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>
#include <algorithm>

namespace structures {

template<typename T>
//! Declaração da classe da Lista Duplamente Encadeada
class DoublyLinkedList {
 public:
    //! Construtor padrão da classe
    DoublyLinkedList(): head{nullptr}, size_{0} {}

    //! Destrutor
    ~DoublyLinkedList() {
        clear();
    }

    //! Método que limpa lista
    void clear() {
        Node *atual, *anterior;
        atual = head;
        while (atual != nullptr) {
            anterior = atual;
            atual = atual->next();
            delete anterior;
        }
        size_ = 0u;
        head = nullptr;
    }

    //! Método que insere no fim da lista
    void push_back(const T& data) {
        insert(data, size_);
    }

    //! Método que insere no início da lista
    void push_front(const T& data) {
        Node *novoElemento = new Node(data, nullptr, head);
        if (novoElemento == nullptr) {
            throw std::out_of_range("A lista está cheia");
        }
        head = novoElemento;
        if (novoElemento->next() != nullptr) {
            novoElemento->next()->prev(novoElemento);
        }
        ++size_;
    }

    //! Método que insere o elemento na posição
    void insert(const T& data, std::size_t index) {
        Node *anterior, *novoElemento;
        if (index > size_) {
            throw std::out_of_range("Posição inválida.");
        } else if (index == 0) {
            return push_front(data);
        } else {
            novoElemento = new Node(data);
            if (novoElemento == nullptr) {
                throw std::out_of_range("A lista está cheia");
            } else {
                anterior = head;
                for (auto i = 1u; i < index; ++i) {
                    anterior = anterior->next();
                }
                novoElemento->next(anterior->next());
                if (novoElemento->next() != nullptr) {
                    novoElemento->next()->prev(novoElemento);
                }
                anterior->next(novoElemento);
                ++size_;
            }
        }
    }

    //! Método que insere um elemento ordenado na lista
    void insert_sorted(const T& data) {
        Node* atual;
        std::size_t indice;
        if (empty()) {
            return push_front(data);
        } else {
            atual = head;
            indice = 0;
            while (atual->next() != nullptr && data > atual->data()) {
                atual = atual->next();
                ++indice;
            }
            if (data > atual->data()) {
                return insert(data, indice +1);
            } else {
                return insert(data, indice);
            }
        }
    }

    //! Método que retira da posição desejada
    T pop(std::size_t index) {
        Node *anterior, *deleta;
        T elementoRetirado;
        if (index >= size_) {
            throw std::out_of_range("Posição inválida.");
        } else if (empty()) {
            throw std::out_of_range("Lista vazia.");
        } else if (index == 0) {
            return pop_front();
        } else {
            anterior = head;
            for (auto i = 1u; i < index; ++i) {
                anterior = anterior->next();
            }
            deleta = anterior->next();
            elementoRetirado = deleta->data();
            anterior->next(deleta->next());
            if (deleta->next() != nullptr) {
                deleta->next()->prev(anterior);
            }
            --size_;
            delete deleta;
            return elementoRetirado;
        }
    }

    //! Método que retira do fim
    T pop_back() {
        return pop(size() - 1);
    }

    //! Método que retira do início
    T pop_front() {
        Node *esquerda = head;
        T dadoRetirado;
        if (empty()) {
            throw std::out_of_range("A lista está vazia.");
        }
        dadoRetirado = esquerda->data();
        head = esquerda->next();
        if (head != nullptr) {
            head->prev(nullptr);
        }
        --size_;
        delete esquerda;
        return dadoRetirado;
    }

    //! Método que retira elemento dado por parâmetro
    void remove(const T& data) {
        pop(find(data));
    }

    //! Método que informa se a lista está vazia
    bool empty() const {
        return size_ == 0;
    }

    //! Método que informa se o elemento está na lista
    bool contains(const T& data) const {
        if (empty()) {
            throw std::out_of_range("A lista está vazia");
        }
        auto aux = head;
        while (aux != nullptr) {
            if (aux->data() == data) {
                return true;
            }
            aux = aux->next();
        }
        return false;
    }

    //! Método que retorna o elemento dado pelo indíce
    T& at(std::size_t index) {
        auto aux = head;
        if (empty()) {
            throw std::out_of_range("A lista está vazia.");
        } else if (index > size() - 1) {
            throw std::out_of_range("Posição inválida.");
        }
        for (auto i = 0u; i < index; ++i) {
            aux = aux->next();
        }
        return aux->data();
    }

    //! Método que acessa um elemento contante dado pelo parâmetro
    const T& at(std::size_t index) const {
        auto aux = head;
        if (empty()) {
            throw std::out_of_range("A lista está vazia.");
        } else if (index > size() - 1) {
            throw std::out_of_range("Posição inválida.");
        }
        for (auto i = 0u; i < index; ++i) {
            aux = aux->next();
        }
        return aux->data();
    }

    //! Método que retorna o índice de um elemento
    std::size_t find(const T& data) const {
        if (empty()) {
            return -1;
        }
        auto aux = head;
        auto indice = 0u;
        while (aux->data() != data) {
            aux = aux->next();
            ++indice;
            if (aux == nullptr) {
                break;
            }
        }
        return indice;
    }

    //! Método que retorna o tamanho atual da lista
    std::size_t size() const {
        return size_;
    }

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data}, next_{next}
        {}

        Node(const T& data, Node* prev, Node* next):
            data_{data}, prev_{prev}, next_{next}
        {}

        T& data() {
            return data_;
        }
        const T& data() const {
            return data_;
        }

        Node* prev() {
            return prev_;
        }
        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
        }

        Node* next() {
            return next_;
        }

        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* head;
    std::size_t size_;
};

}  //! namespace structures

#endif
