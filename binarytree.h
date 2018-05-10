//! Tarefa de Estruturas de Dados - Árvore binária
 /*
   \author Alan Vinicius Cezar Ensina - Matrícula 16206354
   \since 09/05/2018
   \version 1.0
   \copyright @ Alan Ensina
    */

#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H

#include <cstdint>
#include <vector>
#include <stdexcept>
#include "array_list.h"

namespace structures {
/**Implementação da classe Árvore Binária*/
template <typename T>
class BinaryTree {
public:
    ~BinaryTree();
    BinaryTree()= default;

    void insert(const T& data);  // Insere um elemento

    void remove(const T& data);  // Remove um elemento

    bool contains(const T& data) const;  // Informa se o elemento está na árvore

    bool empty() const;  // Informa se a árvore está vazia
std::size_t size() const;  // Informa o tamanho da árvore
    /**Visita a raiz da árvore*/
    ArrayList<T> pre_order() const {
        ArrayList<T> l{size_};
        if (!empty())
            root->pre_order(l);
        return l;
    }
    /**Visita as subárvores*/
    ArrayList<T> in_order() const {
        ArrayList<T> l{size_};
        if (!empty())
            root->in_order(l);
        return l;
}
    /**Visita a raiz após as subárvores*/
    ArrayList<T> post_order() const {
        ArrayList<T> l{size_};
        if (!empty())
            root->post_order(l);
        return l;
    }

private:
    struct Node {
        explicit Node(const T& data_) :
        data(data_), left(nullptr), right(nullptr) {}
        T data;
        Node* left;
        Node* right;

        void insert(const T& data_) {
            Node* new_node;
            if (data_ < this->data) {
                if (this->left == nullptr) {
                    new_node = new Node(data_);
                    new_node->left = nullptr;
                    new_node->right = nullptr;
                    this->left = new_node;
                } else {
                    left->insert(data_);
                }
            } else {
                if (this->right == nullptr) {
                    new_node = new Node(data_);
                    new_node->left = nullptr;
                    new_node->right = nullptr;
                    this->right = new_node;
                } else {
                    right->insert(data_);
                }
            }
        }

        bool remove(const T& data_) {
            bool temp = false;
            if (data_ == this->data) {
                Node* new_node;
                if ((this->left != nullptr) && (this->right != nullptr)) {
                    new_node = this->right;
                    while (new_node->left != nullptr)
                        new_node = new_node->left;
                    this->data = new_node->data;
                    temp = right -> remove(this->data);
                } else {
                    if (this->right != nullptr) {
                        this->data = right->data;
                        temp = right -> remove(this->data);
                    } else {
                        if (this->left != nullptr) {
                        this->data = left->data;
                        temp = left->remove(this->data);
                        } else {
                            delete this;
                            temp = true;
                        }
                    }
                }
            } else {
            if ((this->left != nullptr) && (data_ < this->data))
                temp = left->remove(data_);
            if ((this->right != nullptr) && (data_ > this->data))
                temp = right->remove(data_);
            }
            return temp;
        }

        bool contains(const T& data_) const {
            bool temp = false;
            if (data_ == this->data) {
                temp = true;
            } else {
                if ((this->left != nullptr) && (data_ < this->data)) {
                    temp = left->contains(data_);
                } else if ((this->right != nullptr) && (data_ > this->data)) {
                    temp = right->contains(data_);
                }
            }
            return temp;
        }

        void pre_order(ArrayList<T>& v) const {
            v.push_back(this->data);
            if (this->left != nullptr)
                left->pre_order(v);
            if (this->right != nullptr)
                right->pre_order(v);
        }

        void in_order(ArrayList<T>& v) const {
            if (this->left != nullptr)
                left->in_order(v);
            v.push_back(this->data);
            if (this->right != nullptr)
                right->in_order(v);
        }

        void post_order(ArrayList<T>& v) const {
             if (this->left != nullptr)
                left->post_order(v);
            if (this->right != nullptr)
                right->post_order(v);
            v.push_back(this->data);
        }
    };


Node* root{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif
/**Destrutor*/
template<typename T>
structures::BinaryTree<T>::~BinaryTree() {
    size_= 0;
    delete root;
}
/**Método que insere um elemento na árvore*/
template<typename T>
void structures::BinaryTree<T>::insert(const T& data) {
    if (empty())
        root= new Node(data);
    else
        root->insert(data);
    size_++;
}
/**Método que remove um elemento da árvore*/
template<typename T>
void structures::BinaryTree<T>::remove(const T& data) {
    if (empty())
        throw std::out_of_range("A árvore está vazia!");
    if (contains(data)) {
        size_--;
        root->remove(data);
    }
}
/**Método que informa se o elemento está ou nao na árvore*/
template<typename T>
bool structures::BinaryTree<T>::contains(const T& data) const {
    bool aux = false;
    if (!empty())
        aux= root->contains(data);
    return aux;
}
/**Método que verifica se a árvore está vazia*/
template<typename T>
bool structures::BinaryTree<T>::empty() const {
    return size_ == 0;
}
/**Método que informa o tamanho da árvore*/
template<typename T>
std::size_t structures::BinaryTree<T>::size() const {
    return size_;
}

