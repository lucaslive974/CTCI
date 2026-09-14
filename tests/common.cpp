#include "chapter.hpp"
#include "chapters.hpp"
#include "utils.hpp"
#include "gtest/gtest.h"

TEST(COMMON, CHAPTER_NAME_ATTR) {
    Chapter chapter{"Test Chapter"};

    EXPECT_EQ(chapter.name(), "Test Chapter");
}

TEST(COMMON, CHAPTER_IX_NAME) {
    CTCI::IX chapter;

    EXPECT_EQ(chapter.name(), "CTCI::IX::Exercises");
}

TEST(COMMON, LIST_INITIALIZER_LIST_INIT) {
    CTCI::List<int> list{0, 1, 2, 3, 4};

    EXPECT_FALSE(list.empty());

    auto head = list.head;
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(head->val, i);
        head = head->next;
    }
}

TEST(COMMON, LIST_INITIALIZE_VECTOR_INIT) {
    std::vector<int> vec{5, 4, 3, 2, 1};
    CTCI::List<int> list{vec};

    auto head = list.head;
    for (int val : vec) {
        EXPECT_EQ(head->val, val);
        head = head->next;
    }
}

TEST(COMMON, LIST_EMPTY) {
    CTCI::List<int> list;

    EXPECT_TRUE(list.empty());

    list.appendToTail(5);
    EXPECT_FALSE(list.empty());
}

TEST(COMMON, LIST_APPEND_ITENS) {
    CTCI::List<int> list;

    list.appendToTail(5);
    EXPECT_EQ(list.head->val, 5);

    list.appendToTail(4);
    EXPECT_EQ(list.head->next->val, 4);
}

TEST(UTILS, PrintTitleOutputsFormattedMessage) {
    testing::internal::CaptureStdout();

    CTCI::utils::printTitle("Chapter Test");

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "[Chapter Test]\n");
}

TEST(UTILS, BreakLineOutputsNewLine) {
    testing::internal::CaptureStdout();

    CTCI::utils::breakLine();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "\n");
}
