#pragma once
#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename T>
struct SinglyListTypeContainer {
    SinglyListTypeContainer() : m_size{0}, m_first{nullptr}, m_last{nullptr} {};

    ~SinglyListTypeContainer() {
        Node* current = m_first;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    SinglyListTypeContainer(const SinglyListTypeContainer& container) = delete;
    SinglyListTypeContainer& operator=(const SinglyListTypeContainer& other) = delete;

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
        Node* new_node = new Node;
        new_node->next = nullptr;
        new_node->data = value;
        if (m_size == 0) {
            m_first = new_node;
            m_last = new_node;
            m_size = 1;
        } else {
            m_last->next = new_node;
            m_last = new_node;
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
            new_node->next = m_first;
            new_node->data = value;
            m_first = new_node;
        } else {
            Node* node_prev = m_first;
            for (std::size_t i = 0; i < index - 1; ++i) {
                node_prev = node_prev->next;
            }
            Node* new_node = new Node;
            new_node->next = node_prev->next;
            node_prev->next = new_node;
            new_node->data = value;
        }
        ++m_size;
    }

    void erase(std::size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("Index is out of range!");
        }
        if (m_size == 1) {
            delete m_first;
            m_first = nullptr;
            m_last = nullptr;
            m_size = 0;
            return;
        }
        if (index == 0) {
            Node* new_first = m_first->next;
            Node* old_first = m_first;
            m_first = new_first;
            delete old_first;
            --m_size;
            return;
        }
        if (index == m_size - 1) {
            Node* node_prev = m_first;
            for (std::size_t i = 0; i < m_size - 2; ++i) {
                node_prev = node_prev->next;
            }
            Node* new_last = node_prev;
            Node* old_last = m_last;
            m_last = new_last;
            m_last->next = nullptr;
            delete old_last;
            --m_size;
            return;
        }
        Node* node_prev = m_first;
        for (std::size_t i = 0; i < index - 1; ++i) {
            node_prev = node_prev->next;
        }
        Node* del_node = node_prev->next;
        node_prev->next = del_node->next;
        delete del_node;
        --m_size;
    }

   private:
    struct Node {
        Node* next;
        T data;
    };
    Node* m_first;
    Node* m_last;
    std::size_t m_size;
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, const SinglyListTypeContainer<T>& container) {
    for (std::size_t i = 0; i < container.size(); ++i) {
        stream << container[i] << " ";
    }
    return stream;
}
