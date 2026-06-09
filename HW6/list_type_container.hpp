#pragma once
#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename T>
struct ListTypeContainer {
    ListTypeContainer() : m_size{0}, m_first{nullptr}, m_last{nullptr} {};

    ~ListTypeContainer() {
        Node* current = m_first;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    ListTypeContainer(const ListTypeContainer& container) = delete;
    ListTypeContainer& operator=(const ListTypeContainer& other) = delete;

    std::size_t size() const {
        return m_size;
    }

    T& operator[](std::size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("Index is out of range!");
        }
        Node* current = m_first;

        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    const T& operator[](std::size_t index) const {
        if (index >= m_size) {
            throw std::out_of_range("Index is out of range!");
        }
        const Node* current = m_first;

        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    void push_back(const T& value) {
        if (m_size == 0) {
            Node* node = new Node;
            m_first = node;
            m_last = node;
            node->prev = nullptr;
            node->next = nullptr;
            node->data = value;
            m_size = 1;
        } else {
            Node* node_prev = m_last;
            Node* node_next = new Node;
            node_prev->next = node_next;
            m_last = node_next;
            node_next->next = nullptr;
            node_next->prev = node_prev;
            node_next->data = value;
            ++m_size;
        }
    }

    void insert(std::size_t index, const T& value) {
        if (index > m_size) {
            throw std::out_of_range("Index is out of range!");
        }
        if (index == m_size) {
            push_back(value);
            return;
        }
        if (index == 0) {
            Node* new_node = new Node;
            new_node->prev = nullptr;
            new_node->next = m_first;
            m_first->prev = new_node;
            new_node->data = value;
            m_first = new_node;
        } else {
            Node* node = m_first;
            for (std::size_t i = 0; i < index; ++i) {
                node = node->next;
            }
            Node* new_node = new Node;
            new_node->next = node;
            Node* node_prev = node->prev;
            new_node->prev = node_prev;
            node->prev = new_node;
            node_prev->next = new_node;
            new_node->data = value;
        }
        ++m_size;
    }

    void erase(std::size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("Index is out of range!");
        }
        Node* current = m_first;
        if (m_size == 1) {
            delete current;
            m_first = nullptr;
            m_last = nullptr;
            m_size = 0;
            return;
        }
        if (index == 0) {
            Node* new_first = m_first->next;
            Node* old_first = m_first;
            m_first = new_first;
            m_first->prev = nullptr;
            delete old_first;
            --m_size;
            return;
        }
        if (index == m_size - 1) {
            Node* new_last = m_last->prev;
            Node* old_last = m_last;
            m_last = new_last;
            m_last->next = nullptr;
            delete old_last;
            --m_size;
            return;
        }

        for (std::size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        Node* del_node = current;
        Node* node_prev = del_node->prev;
        Node* node_next = del_node->next;
        node_prev->next = node_next;
        node_next->prev = node_prev;
        delete del_node;
        --m_size;
    }

   private:
    struct Node {
        Node* next;
        Node* prev;
        T data;
    };
    Node* m_first;
    Node* m_last;
    std::size_t m_size;
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, const ListTypeContainer<T>& container) {
    for (std::size_t i = 0; i < container.size(); ++i) {
        stream << container[i] << " ";
    }
    return stream;
}
