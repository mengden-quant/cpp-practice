#pragma once
#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename T>
struct SequentialContainerCap {
    SequentialContainerCap() : m_size{0}, m_region{nullptr}, m_capacity{0}, m_alpha{2.0} {};
    ~SequentialContainerCap() {
        delete[] m_region;
    };
    SequentialContainerCap(const SequentialContainerCap& container) = delete;
    SequentialContainerCap& operator=(const SequentialContainerCap& other) = delete;

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
        if (m_size == m_capacity) {
            std::size_t new_capacity = (m_capacity == 0 ? 1 : m_capacity * m_alpha);
            T* new_region = new T[new_capacity];
            for (std::size_t i = 0; i < m_size; ++i) {
                new_region[i] = m_region[i];
            }
            delete[] m_region;
            m_region = new_region;
            m_capacity = new_capacity;
            m_region[m_size] = value;
            ++m_size;
            return;
        }
        m_region[m_size] = value;
        ++m_size;
    };

    void insert(std::size_t index, const T& value) {
        if (index > m_size) {
            throw std::out_of_range("Index is out of range!");
        }
        if (m_size == m_capacity) {
            std::size_t new_capacity = (m_capacity == 0 ? 1 : m_capacity * m_alpha);
            T* new_region = new T[new_capacity];
            for (std::size_t i = 0; i < index; ++i) {
                new_region[i] = m_region[i];
            }
            for (std::size_t i = index; i < m_size; ++i) {
                new_region[i + 1] = m_region[i];
            }
            delete[] m_region;
            m_region = new_region;
            m_capacity = new_capacity;
            m_region[index] = value;
            ++m_size;
            return;
        } else {
            for (std::size_t i = m_size; i > index; --i) {
                m_region[i] = m_region[i - 1];
            }
        }
        m_region[index] = value;
        ++m_size;
    }

    void erase(std::size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("Index is out of range!");
        }
        for (std::size_t i = index + 1; i < m_size; ++i) {
            m_region[i - 1] = m_region[i];
        }
        --m_size;
    }

   private:
    std::size_t m_size;
    T* m_region;
    std::size_t m_capacity;
    const double m_alpha;
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, const SequentialContainerCap<T>& container) {
    for (std::size_t i = 0; i < container.size(); ++i) {
        stream << container[i] << " ";
    }
    return stream;
}
