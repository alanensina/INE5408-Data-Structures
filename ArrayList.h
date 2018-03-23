  //! Tarefa de Estruturas de Dados - Listas
 /*
   \author Alan Vinicius Cezar Ensina - Matrícula 16206354
   \since 16/03/2018
   \version 1.0
   \copyright @ Alan Ensina
    */

#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>
#include <stdexcept>
#include <algorithm>

namespace structures {

template<typename T>
  //! Declaração da classe ArrayList
class ArrayList {
 public:
  //! Construtor sem parâmetro
  ArrayList();
  //! Construtor parametrizado
  explicit ArrayList(std::size_t max_size);
  //! Destrutor
    ~ArrayList();

  //! Método que limpa a lista
    void clear();
  //! Método que empurra a lista para trás
    void push_back(const T& data);
  //! Método que empurra a lista para frente
    void push_front(const T& data);
  //! Método que adiciona um elemento na lista
    void insert(const T& data, std::size_t index);
  //! Método que adiciona um elemento
    void insert_sorted(const T& data);
  //! Método que retira um elemento da lista em uma determinada posição
    T pop(std::size_t index);
  //! Método que retira o último elemento da lista
    T pop_back();
  //! Método que retira o primeiro elemento da lista
    T pop_front();
  //! Método que retira da lista elemento parametrizado
    void remove(const T& data);
  //! Método que informa se a lista está cheia
    bool full() const;
  //! Método que informa se a lista está vazia
    bool empty() const;
  //! Método que informa se o elemento dado por parâmetro se encontra na lista
    bool contains(const T& data) const;
  //! Método que encontra na lista o elemento dado por parâmetro
    std::size_t find(const T& data) const;
  //! Define o tamanho da lista
    std::size_t size() const;
  //! Define o tamanho máximo da lista
    std::size_t max_size() const;
  //! Método que retorna o dado que se encontra no índice dado por parâmetro
    T& at(std::size_t index);
  //! Retorna o elemento que se encontra no índice dado por parâmetro
    T& operator[](std::size_t index);
  //! Retorna o elemento que se encontra no índice dado por parâmetro
    const T& at(std::size_t index) const;
  //! Retorna o elemento que se encontra no índice dado por parâmetro
    const T& operator[](std::size_t index) const;

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    int last;

    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures

#endif

template<typename T>
structures::ArrayList<T>::ArrayList() {
    size_ = max_size_ = 0;
    contents = new T[0];
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
    size_ =  0;
    max_size_ = max_size;
    contents = new T[max_size_];
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete[] contents;
}

template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full())
        throw std::out_of_range("Lista cheia");
    if (index > size_)
        throw std::out_of_range("Indice nao valido");
    auto temp = contents[index];
    contents[index] = data;
    for (int i = index + 1 ; i <= size_; i++)
        std::swap(temp, contents[i]);
    size_++;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full())
        throw std::out_of_range("Lista cheia");
    contents[size_++] = data;
}

template<typename T>
bool structures::ArrayList<T>::empty() const {
    return size_ == 0;
}

template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    if (full())
        throw std::out_of_range("Lista cheia");
    if (size_ > 0) {
        for (int i = size_; i > 0; i--)
            contents[i] = contents[i-1];
    }
    contents[0] = data;
    size_++;
}

template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    contents[size_++] = data;
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            if (contents[i] < contents[j])
                std::swap(contents[i], contents[j]);
        }
    }
}

template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    int index = find(data);
    if (index > -1) {
        contents[index] = 0;
        for (int i = index; i < max_size_; i++)
            contents[i - 1] = 1;
        size_--;
    }
}

template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}

template<typename T> std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (empty())
       throw std::out_of_range("Lista vazia");
    if (index > size_-1)
        throw std::out_of_range("Indice nao valido");
    auto data = contents[index];
    for (int i = index; i < size_; i++)
        contents[i - 1] = contents[i];
    size_--;
    return data;
}

template<typename T>
T structures::ArrayList<T>::pop_back() {
    if (empty())
       throw std::out_of_range("Lista vazia");
    auto data = contents[--size_];
    contents[size_] = 0;
    return data;
}

template<typename T>
T structures::ArrayList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("Lista vazia");
    auto data = contents[0];
    for (int i = 1; i < max_size_; i++)
        contents[i - 1] = contents[i];
    size_--;
    return data;
}

template<typename T>
bool structures::ArrayList<T>::full() const {
    return size_ == max_size_;
}

template<typename T> T& structures::ArrayList<T>::at(std::size_t index) {
    if (index > size_)
        throw std::out_of_range("Lista vazia");
    return contents[index];
}

template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    for (int i = 0; i < size_; i++) {
        if (contents[i] == data)
            return true;
    }
    return false;
}

template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    if (index > size_)
        throw std::out_of_range("Lista vazia");
    return contents[index];
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    for (int i = 0; i < size_; i++) {
        if (contents[i] == data)
            return i;
    }
    return size_;
}

template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    if (index > size_)
        throw std::out_of_range("Lista vazia");
    return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    if (index > size_)
        throw std::out_of_range("Lista vazia");
    return contents[index];
}
