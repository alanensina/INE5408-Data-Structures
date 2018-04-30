  //!  Tarefa de Estruturas de Dados - Lista Circular Dupla
 /*
   \author Alan Vinicius Cezar Ensina - Matrícula 16206354
   \since 15/04/2018
   \version 1.0
   \copyright @ Alan Ensina
    */
#ifndef STRUCTURES_DOUBLY_CIRCULAR_LIST_H
#define STRUCTURES_DOUBLY_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {
//! Declaração da classe lista circular dupla
template<typename T>
class DoublyCircularList {
 public:
    //! Construtor padrão
    DoublyCircularList() {
        size_ = 0u;
        head = nullptr;
    }

    //! Destrutor de objetos
    ~DoublyCircularList() {
        clear();
    }

    //! Método que limpa a lista
    void clear() {
        Node *atual, *anterior;
        atual = head;
        auto i = 0u;
        while (i < size_) {
            anterior = atual;
            atual = atual->next();
            delete anterior;
            ++i;
        }
        size_ = 0u;
        head = nullptr;
    }

    //! Método que insere no fim da lista
    void push_back(const T& data) {
        if (empty()) {
            return push_front(data);
        }
        auto novoElemento = new Node(data, head);
        if (novoElemento == nullptr) {
            throw std::out_of_range("Erro: a lista está cheia!");
        }
        auto aux = end();
        aux->next(novoElemento);
        novoElemento->prev(aux);
        head->prev(novoElemento);
        ++size_;
    }

    //! Método que insere no início
    void push_front(const T& data) {
        auto novoElemento = new Node(data);
        if (novoElemento == nullptr) {
            throw std::out_of_range("Erro: a lista está cheia!");
        }
        if (empty()) {
            head = novoElemento;
            head->next(head);
            head->prev(head);
            ++size_;
        } else {
            novoElemento->next(head);
            novoElemento->prev(end());
            head = novoElemento;
            end()->next(head);
            ++size_;
        }
    }

    //! Método que insere na posição dada pelo index
    void insert(const T& data, std::size_t index) {
        if (index > size_) {
            throw std::out_of_range("Erro: posição inválida!");
        }
        if (index == 0) {
            return push_front(data);
        }
        auto aux = head;
        for (auto i = 1u; i < index; ++i) {
            aux = aux->next();
        }
        auto novoElemento = new Node(data, aux, aux->next());
        if (novoElemento == nullptr) {
            throw std::out_of_range("Erro: a lista está cheia!");
        }
        aux->next()->prev(novoElemento);
        aux->next(novoElemento);
        ++size_;
    }

    //! Método que insere em ordem
    void insert_sorted(const T& data) {
        if (empty()) {
            return push_front(data);
        }
        auto aux = head;
        auto indice = 0u;
        while (indice < size_ && data > aux->data()) {
            aux = aux->next();
            ++indice;
        }
        return insert(data, indice);
    }

    //! Método que retira da posição dada por index
    T pop(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Erro: a lista está vazia!");
        }
        if (index == 0) {
            return pop_front();
        }
        if (index == size_ - 1) {
            return pop_back();
        }
        auto aux = head;
        for (auto i = 1u; i < index; ++i) {
            aux = aux->next();
        }
        auto deletar = aux->next();
        auto data = deletar->data();
        aux->next(deletar->next());
        deletar->next()->prev(aux);
        delete deletar;
        --size_;
        return data;
    }

    //! Método que retira do fim
    T pop_back() {
        if (empty()) {
            throw std::out_of_range("Erro: a lista está vazia!");
        }
        if (size_ == 1) {
            return pop_front();
        }
        auto elemento = end()->data();
        auto deletar = end();
        deletar->prev()->next(head);
        head->prev(deletar->prev());
        delete deletar;
        --size_;
        return elemento;
    }

    //! Método que retira do início
    T pop_front() {
        T elemento;
        if (empty()) {
            throw std::out_of_range("Erro: a lista está vazia!");
        }
        auto deletar = head;
        elemento = deletar->data();
        head = deletar->next();
        head->prev(end());
        end()->next(head);
        delete deletar;
        --size_;
        return elemento;
    }

    //! Método que remove elemento dado pelo index
    void remove(const T& data) {
        pop(find(data));
    }

    //! Método que informa se a lista está vazia
    bool empty() const {
        return size_ == 0;
    }

    //! Método que informa se a lista contém determinado elemento
    bool contains(const T& data) const {
        if (empty()) {
            throw std::out_of_range("Erro: a lista está vazia!");
        }
        if (find(data) == size_) {
            return false;
        }
        return true;
    }

    //! Método que acessa elemento dado pelo index
    T& at(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("Erro: a lista está vazia!");
        }
        if (index >= size_) {
            throw std::out_of_range("Erro: posição inválida!");
        }
        auto aux = head;
        for (auto i = 0u; i < index; ++i) {
            aux = aux->next();
        }
        return aux->data();
    }

    //! Método que acessa elemento const dado pelo index
    const T& at(std::size_t index) const {
        auto aux = head;
        for (auto i = 0u; i < index; ++i) {
            aux = aux->next();
        }
        return aux->data();
    }

    //! Método que encontra elemento dado pelo index
    std::size_t find(const T& data) const {
        if (empty()) {
            throw std::out_of_range("Erro: a lista está vazia!");
        }
        auto aux = head;
        for (auto i = 0u; i < size_; ++i) {
            if (aux->data() == data) {
                return i;
            }
            aux = aux->next();
        }
        return size_;
    }

    //! Método que informa o tamanho atual da lista
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
            data_{data},
            next_{next}
        {}

        Node(const T& data, Node* prev, Node* next):
            data_{data},
            prev_{prev},
            next_{next}
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

    Node* end() {  // último nodo da lista
        return head->prev();
    }
    Node* head;
    std::size_t size_;
};

}  // namespace structures

#endif