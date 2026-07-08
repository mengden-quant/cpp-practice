#include <gtest/gtest.h>

#include <cstddef>
#include <stdexcept>
#include <utility>

#include "sequential_container.hpp"

struct SequentialContainerTest : public testing::Test {
    const std::size_t element_count = 10;
    SequentialContainer<double> container;
    void SetUp() override {
        for (std::size_t i = 0; i < element_count; ++i) {
            container.push_back(static_cast<double>(i));
        }
    }
};

TEST(sequential_type_container, default_constructor) {
    SequentialContainer<double> container;
    const std::size_t expected = 0;
    EXPECT_EQ(container.size(), expected);
}

TEST_F(SequentialContainerTest, push_back_one_element) {
    const double new_value = 100.0;
    container.push_back(new_value);
    ASSERT_EQ(container.size(), element_count + 1);
    EXPECT_EQ(container[container.size() - 1], new_value);
}

TEST_F(SequentialContainerTest, insert_at_begin) {
    const double new_value = 100;
    container.insert(0, new_value);
    ASSERT_EQ(container.size(), element_count + 1);
    EXPECT_EQ(container[0], new_value);
    EXPECT_EQ(container[1], 0.0);
}

TEST_F(SequentialContainerTest, insert_at_middle) {
    const double new_value = 100;
    const std::size_t index = container.size() / 2;
    container.insert(index, new_value);
    ASSERT_EQ(container.size(), element_count + 1);
    EXPECT_EQ(container[index], new_value);
}

TEST_F(SequentialContainerTest, erase_from_end) {
    container.erase(container.size() - 1);
    ASSERT_EQ(container.size(), element_count - 1);
    EXPECT_EQ(container[container.size() - 1], static_cast<double>(element_count - 2));
}

TEST_F(SequentialContainerTest, erase_from_begin) {
    container.erase(0);
    ASSERT_EQ(container.size(), element_count - 1);
    EXPECT_EQ(container[0], 1.0);
}

TEST_F(SequentialContainerTest, erase_from_middle) {
    const std::size_t index = container.size() / 2;
    container.erase(index);
    ASSERT_EQ(container.size(), element_count - 1);
    EXPECT_EQ(container[index - 1], 4.0);
    EXPECT_EQ(container[index], 6.0);
}

TEST_F(SequentialContainerTest, operator_square_brackets_returns_element) {
    EXPECT_EQ(container[0], 0.0);
    EXPECT_EQ(container[container.size() - 1], static_cast<double>(element_count - 1));
}

TEST_F(SequentialContainerTest, size_after_setup) {
    EXPECT_EQ(container.size(), element_count);
}

TEST_F(SequentialContainerTest, operator_square_brackets_allows_modification) {
    container[0] = 42.0;
    EXPECT_EQ(container[0], 42.0);
}

TEST_F(SequentialContainerTest, invalid_index_throws) {
    EXPECT_THROW(container[container.size()], std::out_of_range);
    EXPECT_THROW(container.erase(container.size()), std::out_of_range);
    EXPECT_THROW(container.insert(container.size() + 1, 100.0), std::out_of_range);
}

TEST(sequential_type_container, copy_constructor_creates_independent_copy) {
    SequentialContainer<double> original;
    for (std::size_t i = 0; i <= 5; ++i) {
        original.push_back(static_cast<double>(i));
    }
    SequentialContainer<double> copy{original};
    ASSERT_EQ(copy.size(), original.size());
    for (std::size_t i = 0; i < original.size(); ++i) {
        EXPECT_EQ(copy[i], original[i]);
    }
    original[0] = 100.0;
    EXPECT_EQ(copy[0], 0.0);
}

TEST(sequential_type_container, copy_assignment_creates_independent_copy) {
    SequentialContainer<double> original;
    for (std::size_t i = 0; i <= 5; ++i) {
        original.push_back(static_cast<double>(i));
    }
    SequentialContainer<double> copy;
    copy.push_back(999.0);
    copy = original;
    ASSERT_EQ(copy.size(), original.size());
    for (std::size_t i = 0; i < original.size(); ++i) {
        EXPECT_EQ(copy[i], original[i]);
    }
    original[0] = 100.0;
    EXPECT_EQ(copy[0], 0.0);
}

TEST(sequential_type_container, copy_assignment_handles_self_assignment) {
    SequentialContainer<double> original;
    for (std::size_t i = 0; i <= 5; ++i) {
        original.push_back(static_cast<double>(i));
    }
    original = original;
    ASSERT_EQ(original.size(), 6);
    for (std::size_t i = 0; i < original.size(); ++i) {
        EXPECT_EQ(original[i], static_cast<double>(i));
    }
}

TEST(sequential_type_container, move_constructor_transfers_elements) {
    SequentialContainer<double> source;
    source.push_back(1.0);
    source.push_back(2.0);
    SequentialContainer<double> destination = std::move(source);
    ASSERT_EQ(source.size(), 0);
    ASSERT_EQ(destination.size(), 2);
    EXPECT_EQ(destination[0], 1.0);
    EXPECT_EQ(destination[1], 2.0);
    source.push_back(3.0);
    EXPECT_EQ(source.size(), 1);
    EXPECT_EQ(source[0], 3.0);
}

TEST(sequential_type_container, move_assignment_transfers_elements) {
    SequentialContainer<double> source;
    source.push_back(1.0);
    source.push_back(2.0);
    SequentialContainer<double> destination;
    destination.push_back(99.0);
    destination = std::move(source);
    ASSERT_EQ(source.size(), 0);
    ASSERT_EQ(destination.size(), 2);
    EXPECT_EQ(destination[0], 1.0);
    EXPECT_EQ(destination[1], 2.0);
    source.push_back(3.0);
    EXPECT_EQ(source.size(), 1);
    EXPECT_EQ(source[0], 3.0);
}
