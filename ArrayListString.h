/* Tarefa de Estruturas de Dados - Aplicação de lista de ponteiros para Strings
   \author Alan Vinicius Cezar Ensina - Matrícula 16206354
   \since 31/03/2018
   \version 1.0
   \copyright @ Alan Ensina
    */
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>
#include <stdexcept>  //  C++ exceptions
#include <cstring>
#include <algorithm>

namespace structures {

/** Declaração da classe ArrayList */
template<typename T>
class ArrayList {
 public:
    ArrayList();
    explicit ArrayList(std::size_t max_size);
    ~ArrayList();

    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool full() const;
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    T& at(std::size_t index);
    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;
    const T& operator[](std::size_t index) const;

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

/** Construtor sem parâmetro */
template<typename T>
structures::ArrayList<T>::ArrayList() {
    size_ = max_size_ = 0;
    contents = new T[0];
}

/** Construtor com parâmetro */
template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
    size_ =  0;
    max_size_ = max_size;
    contents = new T[max_size_];
}

/** Destrutor */
template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete[] contents;
}

/** Método que limpa a lista */
template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

/** Método que adiciona um elemento no final da lista */
template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full())
        throw std::out_of_range("Lista cheia");
    contents[size_++] = data;
}

/** Método que adiciona um elemento no início da lista */
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

/** Método que adiciona um elemento na posição dada por parâmetro */
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

/** Método que adiciona um elemento de forma ordenada */
template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full()) {
		throw std::out_of_range("Lista cheia.");
	} else {
		std::size_t atual = 0;
		while ((atual < size())
			&& (strncmp(at(atual), data, 3) < 0)) {
				atual += 1;
			}
			insert(data, atual);
	}
}

/** Método que retira e retorna o elemento dado por parâmetro */
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

/** Método que retira e retorna o elemento o último elemento da lista */
template<typename T>
T structures::ArrayList<T>::pop_back() {
    if (empty())
       throw std::out_of_range("Lista vazia");
    auto data = contents[--size_];
    contents[size_] = 0;
    return data;
}

/** Método que retira e retorna o elemento o primeiro elemento da lista */
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

/** Método que retira o elemento dado por parâmetro */
template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    int index = find(data);
    if (index > -1) {
        contents[index] = nullptr;
        for (int i = index; i < max_size_; i++)
            contents[i] = contents[i + 1];
        size_--;
    }
}

/** Método que verifica se a lista está cheia */
template<typename T>
bool structures::ArrayList<T>::full() const {
    return size_ == max_size_;
}

/** Método que verifica se a lista está vazia */
template<typename T>
bool structures::ArrayList<T>::empty() const {
    return size_ == 0;
}

/** Método que verifica se a lista contém o elemento dado por parâmetro */
template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    for (int i = 0; i < size_; i++) {
        if (contents[i] == data)
            return true;
    }
    return false;
}

/** Método que retorna o índice do elemento dado por parâmetro */
template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    for (int i = 0; i < size_; i++) {
        if (contents[i] == data)
            return i;
    }
    return size_;
}

/** Método que retorna o tamanho atual da lista */
template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}

/** Método que retorna o tamanho máximo da lista */
template<typename T> std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

/** Método que retorna o elemento do índice dado por parâmetro */
template<typename T> T& structures::ArrayList<T>::at(std::size_t index) {
    if (index > size_)
        throw std::out_of_range("Lista vazia");
    return contents[index];
}

/** Método que retorna o elemento do índice dado por parâmetro */
template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    if (index > size_)
        throw std::out_of_range("Lista vazia");
    return contents[index];
}

/** Método que retorna o elemento do índice dado por parâmetro */
template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    if (index > size_)
        throw std::out_of_range("Lista vazia");
    return contents[index];
}

/** Método que retorna o elemento do índice dado por parâmetro */
template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    if (index > size_)
        throw std::out_of_range("Lista vazia");
    return contents[index];
}

//--------------------------------------------------------------------

/** Declaração da classe ArrayListString */
class ArrayListString {
 public:
    ArrayListString();
    explicit ArrayListString(std::size_t max_size);
    ~ArrayListString();

    void clear();
    void push_back(const char *data);
    void push_front(const char *data);
    void insert(const char *data, std::size_t index);
    void insert_sorted(const char *data);
    char *pop(std::size_t index);
    char *pop_back();
    char *pop_front();
    void remove(const char *data);
    bool full() const;
    bool empty() const;
    bool contains(const char *data) const;
    std::size_t find(const char *data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    char *at(std::size_t index);
    char *operator[](std::size_t index);
    const char *at(std::size_t index) const;
    const char *operator[](std::size_t index) const;

 private:
    ArrayList<char *> *list;
    static const auto DEFAULT_MAX = 100u;
};

/** Construtor */
structures::ArrayListString::ArrayListString(std::size_t max_size) {
    list = new ArrayList<char*>(max_size);
}

/** Destrutor */
structures::ArrayListString::~ArrayListString() {
    delete list;
}

/** Método que limpa a lista */
void structures::ArrayListString::clear() {
    list->clear();
}

/** Método que adiciona um elemento no final da lista */
void structures::ArrayListString::push_back(const char* data) {
    list->push_back(const_cast<char*>(data));
}

/** Método que adiciona um elemento no início da lista */
void structures::ArrayListString::push_front(const char* data) {
    list->push_front(const_cast<char*>(data));
}

/** Método que adiciona um elemento na posição dada por parâmetro */
void structures::ArrayListString::insert(const char* data, std::size_t index) {
    list->insert(const_cast<char*>(data), index);
}

/** Método que adiciona um elemento de forma ordenada */
void structures::ArrayListString::insert_sorted(const char* data) {
    list->insert_sorted(const_cast<char*>(data));
}

/** Método que retira e retorna o elemento dado por parâmetro */
char* structures::ArrayListString::pop(std::size_t index) {
    return list->pop(index);
}

/** Método que retira e retorna o elemento o último elemento da lista */
char* structures::ArrayListString::pop_back() {
    return list->pop_back();
}

/** Método que retira e retorna o elemento o primeiro elemento da lista */
char* structures::ArrayListString::pop_front() {
    return list->pop_front();
}

/** Método que retira o elemento dado por parâmetro */
void structures::ArrayListString::remove(const char* data) {
    list->remove(const_cast<char*>(data));
}

/** Método que verifica se a lista está cheia */
bool structures::ArrayListString::full() const {
    return list->full();
}

/** Método que verifica se a lista está vazia */
bool structures::ArrayListString::empty() const {
    return list->empty();
}

/** Método que verifica se a lista contém o elemento dado por parâmetro */
bool structures::ArrayListString::contains(const char* data) const {
    return list->contains(const_cast<char*>(data));
}

/** Método que retorna o índice do elemento dado por parâmetro */
std::size_t structures::ArrayListString::find(const char* data) const {
    return list->find(const_cast<char*>(data));
}

/** Método que retorna o tamanho atual da lista */
std::size_t structures::ArrayListString::size() const {
    return list->size();
}

/** Método que retorna o tamanho máximo da lista */
std::size_t structures::ArrayListString::max_size() const {
    return list->max_size();
}

/** Método que retorna o elemento do índice dado por parâmetro */
char* structures::ArrayListString::at(std::size_t index) {
    return list->at(index);
}

/** Método que retorna o elemento do índice dado por parâmetro */
char* structures::ArrayListString::operator[](std::size_t index) {
    return list->at(index);
}

/** Método que retorna o elemento do índice dado por parâmetro */
const char* structures::ArrayListString::at(std::size_t index) const {
    return list->at(index);
}

/** Método que retorna o elemento do índice dado por parâmetro */
const char* structures::ArrayListString::operator[](std::size_t index) const {
    return list->at(index);
}

}  // namespace structures

#endif

