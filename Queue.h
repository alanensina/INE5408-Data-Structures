  //! Tarefa de Estruturas de Dados - Fila
  /* 
  \author Alan Vinicius Cezar Ensina - Matrícula 16206354
  \since 10/03/2018
  \version 1.0
  \copyright @ Alan Ensina
  */

  #ifndef STRUCTURES_ARRAY_QUEUE_H
  #define STRUCTURES_ARRAY_QUEUE_H

  #include <cstdint>   // std::size_t
  #include <stdexcept>   // C++ Exceptions
namespace structures {

template<typename T>
        //! Declaração da classe ArrayQueue
class ArrayQueue {
 public:
      //! Construtor sem parâmetro
      ArrayQueue();
      //! Construtor com parâmetro
      explicit  ArrayQueue(std::size_t max);
      //! Destrutor
      ~ArrayQueue();
      //! Método que adiciona um elemento na fila
      void enqueue(const T& data);
      //! Método que remove um elemento na fila
      T dequeue();
      //! Método que retorna o primeiro elemento da fila
      T& back();
      //! Método que limpa a fila
      void clear();
      //! Método que retorna o tamanho da fila atual
      std::size_t size();
      //! Método que retorna o valor total da fila
      std::size_t max_size();
      //! Método que retorna se a fila está vazia
      bool empty();
      //! Método que retorna se a fila está cheia
      bool full();

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

#endif

template<typename T>
bool structures::ArrayQueue<T>::empty() {
    if (size_ == 0) {
        return true;
    }
    return false;
}

template<typename T>
bool structures::ArrayQueue<T>::full() {
    if (size_ == max_size_) {
        return true;
    }
    return false;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::size() {
    return size_;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::max_size() {
    return max_size_;
}

template<typename T>
void structures::ArrayQueue<T>::clear() {
    size_ = 0;
}

template<typename T>
structures::ArrayQueue<T>::ArrayQueue(std::size_t max) {
    size_ = 0;
    max_size_ = max;
    contents = new T[max_size_];
}

template<typename T>
structures::ArrayQueue<T>::~ArrayQueue() {
    delete[] contents;
}

template<typename T>
void structures::ArrayQueue<T>::enqueue(const T& data) {
    if (full())
        throw std::out_of_range("Lista cheia");
    else
        contents[size_++] = data;
}

template<typename T>
T structures::ArrayQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    } else {
        auto aux = contents[0];
        size_--;
        for (int i = 0; i < size_; i++)
            contents[i] = contents[i+1];
        return aux;
    }
}

template<typename T>
T& structures::ArrayQueue<T>::back() {
    if (empty())
        throw std::out_of_range("Lista vazia");
    return contents[size_ - 1];
}
