#include <gtest/gtest.h>

#include <cstddef>
#include <stdexcept>
#include <utility>

#include "list_type_container.hpp"

struct ListTypeContainerTest : public testing::Test {
    const std::size_t element_count = 10;
    ListTypeContainer<double> list;
    void SetUp() override {
        for (std::size_t i = 0; i < element_count; ++i) {
            list.push_back(static_cast<double>(i));
        }
    }
};

TEST(list_type_container, default_constructor) {
    ListTypeContainer<double> list;
    const std::size_t expected = 0;
    EXPECT_EQ(list.size(), expected);
}

TEST_F(ListTypeContainerTest, push_back_one_element) {
    const double new_value = 100.0;
    list.push_back(new_value);
    ASSERT_EQ(list.size(), element_count + 1);
    EXPECT_EQ(list[list.size() - 1], new_value);
}

TEST_F(ListTypeContainerTest, insert_at_begin) {
    const double new_value = 100;
    list.insert(0, new_value);
    ASSERT_EQ(list.size(), element_count + 1);
    EXPECT_EQ(list[0], new_value);
    EXPECT_EQ(list[1], 0.0);
}

TEST_F(ListTypeContainerTest, insert_at_middle) {
    const double new_value = 100;
    const std::size_t index = list.size() / 2;
    list.insert(index, new_value);
    ASSERT_EQ(list.size(), element_count + 1);
    EXPECT_EQ(list[index], new_value);
}

TEST_F(ListTypeContainerTest, erase_from_end) {
    list.erase(list.size() - 1);
    ASSERT_EQ(list.size(), element_count - 1);
    EXPECT_EQ(list[list.size() - 1], static_cast<double>(element_count - 2));
}

TEST_F(ListTypeContainerTest, erase_from_begin) {
    list.erase(0);
    ASSERT_EQ(list.size(), element_count - 1);
    EXPECT_EQ(list[0], 1.0);
}

TEST_F(ListTypeContainerTest, erase_from_middle) {
    const std::size_t index = list.size() / 2;
    list.erase(index);
    ASSERT_EQ(list.size(), element_count - 1);
    EXPECT_EQ(list[index - 1], 4.0);
    EXPECT_EQ(list[index], 6.0);
}

TEST_F(ListTypeContainerTest, operator_square_brackets_returns_element) {
    EXPECT_EQ(list[0], 0.0);
    EXPECT_EQ(list[list.size() - 1], static_cast<double>(element_count - 1));
}

TEST_F(ListTypeContainerTest, size_after_setup) {
    EXPECT_EQ(list.size(), element_count);
}

TEST_F(ListTypeContainerTest, operator_square_brackets_allows_modification) {
    list[0] = 42.0;
    EXPECT_EQ(list[0], 42.0);
}

TEST_F(ListTypeContainerTest, invalid_index_throws) {
    EXPECT_THROW(list[list.size()], std::out_of_range);
    EXPECT_THROW(list.erase(list.size()), std::out_of_range);
    EXPECT_THROW(list.insert(list.size() + 1, 100.0), std::out_of_range);
}

TEST(list_type_container, copy_constructor_creates_independent_copy) {
    ListTypeContainer<double> original;
    for (std::size_t i = 0; i <= 5; ++i) {
        original.push_back(static_cast<double>(i));
    }
    ListTypeContainer<double> copy{original};
    ASSERT_EQ(copy.size(), original.size());
    for (std::size_t i = 0; i < original.size(); ++i) {
        EXPECT_EQ(copy[i], original[i]);
    }
    original[0] = 100.0;
    EXPECT_EQ(copy[0], 0.0);
}

TEST(list_type_container, copy_assignment_creates_independent_copy) {
    ListTypeContainer<double> original;
    for (std::size_t i = 0; i <= 5; ++i) {
        original.push_back(static_cast<double>(i));
    }
    ListTypeContainer<double> copy;
    copy.push_back(999.0);
    copy = original;
    ASSERT_EQ(copy.size(), original.size());
    for (std::size_t i = 0; i < original.size(); ++i) {
        EXPECT_EQ(copy[i], original[i]);
    }
    original[0] = 100.0;
    EXPECT_EQ(copy[0], 0.0);
}

TEST(list_type_container, copy_assignment_handles_self_assignment) {
    ListTypeContainer<double> original;
    for (std::size_t i = 0; i <= 5; ++i) {
        original.push_back(static_cast<double>(i));
    }
    original = original;
    ASSERT_EQ(original.size(), 6);
    for (std::size_t i = 0; i < original.size(); ++i) {
        EXPECT_EQ(original[i], static_cast<double>(i));
    }
}

TEST(list_type_container, move_constructor_transfers_elements) {
    ListTypeContainer<double> source;
    source.push_back(1.0);
    source.push_back(2.0);
    ListTypeContainer<double> destination = std::move(source);
    ASSERT_EQ(source.size(), 0);
    ASSERT_EQ(destination.size(), 2);
    EXPECT_EQ(destination[0], 1.0);
    EXPECT_EQ(destination[1], 2.0);
    source.push_back(3.0);
    EXPECT_EQ(source.size(), 1);
    EXPECT_EQ(source[0], 3.0);
}

TEST(list_type_container, move_assignment_transfers_elements) {
    ListTypeContainer<double> source;
    source.push_back(1.0);
    source.push_back(2.0);
    ListTypeContainer<double> destination;
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
