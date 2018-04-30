  //! Tarefa de Estruturas de Dados - Lista Circular
 /*
   \author Alan Vinicius Cezar Ensina - Matrícula 16206354
   \since 15/04/2018
   \version 1.0
   \copyright @ Alan Ensina
    */
#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {
//! Declaração da classe lista circular
template<typename T>
class CircularList {
 public:
    //! Construtor padrão
    CircularList() {
        size_ = 0;
        head = new Node((T)NULL, nullptr);
        head->next(head);
    }

    //! Destrutor de objetos
    ~CircularList() {
        clear();
        delete head;
    }

    //! Método que limpa a lista circular
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    //! Método que insere um elemento no fim
    void push_back(const T& data) {
        if (empty()) {
            return push_front(data);
        } else {
            Node* novoElemento = new Node(data, head);
            if (novoElemento == nullptr) {
                throw std::out_of_range("Erro: a lista está cheia!");
            }
            end()->next(novoElemento);
            ++size_;
        }
    }

    //! Método que insere um elemento no início da lista
    void push_front(const T& data) {
        head->next(new Node(data, head->next()));
        ++size_;
    }

    //! Método que insere um elemento na posição desejada
    void insert(const T& data, std::size_t index) {
        if (index > size_) {
            throw std::out_of_range("Erro: posição inválida!");
        } else if (index == size_) {
            return push_back(data);
        } else if (index == 0) {
            return push_front(data);
        } else {
            Node* novoElemento = new Node(data);
            if (novoElemento == nullptr) {
                throw std::out_of_range("Erro: a lista está cheia!");
            }
            auto anterior = head->next();
            for (auto i = 1u; i < index; ++i) {
                anterior = anterior->next();
            }
            novoElemento->next(anterior->next());
            anterior->next(novoElemento);
            ++size_;
        }
}

    //! Método que insere um novo elemento na ordem
    void insert_sorted(const T& data) {
        if (empty()) {
            return push_front(data);
        }
        Node* atual = head->next();
        auto i = 0u;
        while (i < size_ && atual->data() < data) {
            atual = atual->next();
            ++i;
        }
        return insert(data, i);
    }

    //! Método que verifica um elemento no índice dado por parâmetro
    T& at(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("Erro: a lista está vazia!");
        } else if (index >= size_) {
            throw std::out_of_range("Erro: posição inválida!");
        } else {
            auto aux = head->next();
            for (auto i = 0u; i < index; ++i) {
                aux = aux->next();
            }
            return aux->data();
        }
    }

    //! Método que verifica um elemento const no índice dado por parâmetro
    const T& at(std::size_t index) const {
        auto aux = head->next();
        for (auto i = 0u; i < index; ++i) {
            aux = aux->next();
        }
        return aux->data();
    }

    //! Método que retira um elemento da posição dada por parâmetro
     T pop(std::size_t index) {
        if (index >= size()) {
            throw std::out_of_range("Erro: posição inválida!");
        }
        if (index == 0) {
            return pop_front();
        }
        auto aux = head->next();
        for (auto i = 1u; i < index; ++i) {
            aux = aux->next();
        }
        auto del = aux->next();
        auto data = del->data();
        aux->next(del->next());
        --size_;
        delete del;
        return data;
    }

    //! Método que remove um elemento no fim da lista
    T pop_back() {
        if (size() == 1) {
            return pop_front();
        }
        return pop(size() - 1);
    }

    //! Método que remove um elemento no início da lista
    T pop_front() {
        if (empty()) {
            throw std::out_of_range("Erro: a lista está vazia!");
        }
        T dado = head->next()->data();
        auto deleta = head->next();
        head->next(deleta->next());
        delete deleta;
        --size_;
        return dado;
    }

    //!  Método que remove um elemento específico da lista
    void remove(const T& data) {
        pop(find(data));
    }

    //! Método que informa se a listá está vazia.
    bool empty() const {
        return size_ == 0;
    }

    //! Método que informa se a listá contém determinado elemento.
    bool contains(const T& data) const {
        if (find(data) == size()) {
            return false;
        }
        return true;
    }

    //! Método que retorna a posição de um elemento na lista
    std::size_t find(const T& data) const {
        if (empty()) {
            throw std::out_of_range("Erro lista vazia!");
        }
        auto aux = head->next();
        for (auto i = 0u; i < size(); ++i) {
            if (aux->data() == data) {
                return i;
            }
            aux = aux->next();
        }
        return size_;
    }

    //! Método que informa o tamanho da lista.
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

    Node* end() {  // último nodo da lista
        auto it = head->next();
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }
    Node* head;
    std::size_t size_;
};

}  // namespace structures

#endif