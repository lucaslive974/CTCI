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