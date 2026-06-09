#pragma once
#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename T>
struct SequentialContainer {
    SequentialContainer() : m_size{0}, m_region{nullptr} {};
    ~SequentialContainer() {
        delete[] m_region;
    };
    SequentialContainer(const SequentialContainer& container) = delete;
    SequentialContainer& operator=(const SequentialContainer& other) = delete;

    std::size_t size() const {
        return m_size;
    }

    T& operator[](std::size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("Index is out of range!");
        }
        return m_region[index];
    }

    const T& operator[](std::size_t index) const {
        if (index >= m_size) {
            throw std::out_of_range("Index is out of range!");
        }
        return m_region[index];
    }
    void push_back(const T& value) {
        T* new_region = new T[m_size + 1];
        for (std::size_t i = 0; i < m_size; ++i) {
            new_region[i] = m_region[i];
        }
        new_region[m_size] = value;
        delete[] m_region;
        m_region = new_region;
        ++m_size;
    };

    void insert(std::size_t index, const T& value) {
        if (index > m_size) {
            throw std::out_of_range("Index is out of range!");
        }
        T* new_region = new T[m_size + 1];
        for (std::size_t i = 0; i < index; ++i) {
            new_region[i] = m_region[i];
        }
        new_region[index] = value;
        for (std::size_t i = index; i < m_size; ++i) {
            new_region[i + 1] = m_region[i];
        }
        delete[] m_region;
        m_region = new_region;
        ++m_size;
    }

    void erase(std::size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("Index is out of range!");
        }
        if (m_size == 1) {
            delete [] m_region;
            m_size = 0;
            return;
        }
        T* new_region = new T[m_size - 1];
        for (std::size_t i = 0; i < index; ++i) {
            new_region[i] = m_region[i];
        }
        for (std::size_t i = index+1; i < m_size; ++i) {
            new_region[i - 1] = m_region[i];
        }
        delete[] m_region;
        m_region = new_region;
        --m_size;
    }

   private:
    std::size_t m_size;
    T* m_region;
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, const SequentialContainer<T>& container) {
    for (std::size_t i = 0; i < container.size(); ++i) {
        stream << container[i] << " ";
    }
    return stream;
}
