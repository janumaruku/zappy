#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cctype>
#include "AISession.hpp"


using AISession = zappy::server::AISession;

TEST(SanitizedSplit, EmptyString)
{
    EXPECT_EQ(AISession::sanitizedSplit(""), std::vector<std::string>{});
}

TEST(SanitizedSplit, OnlyNewline)
{
    EXPECT_EQ(AISession::sanitizedSplit("\n"), std::vector<std::string>{"\n"});
}

TEST(SanitizedSplit, SingleWordWithNewline)
{
    EXPECT_EQ(AISession::sanitizedSplit("Forward\n"), (std::vector<std::string>{"Forward"}));
}

TEST(SanitizedSplit, TwoWordsWithNewline)
{
    EXPECT_EQ(AISession::sanitizedSplit("Take linemate\n"),
              (std::vector<std::string>{"Take", "linemate"}));
}

TEST(SanitizedSplit, MultipleSpacesBetweenWords)
{
    EXPECT_EQ(AISession::sanitizedSplit("Take    linemate     \n"),
              (std::vector<std::string>{"Take", "linemate"}));
}

TEST(SanitizedSplit, LeadingAndTrailingSpaces)
{
    EXPECT_EQ(AISession::sanitizedSplit("   Forward   \n"),
              (std::vector<std::string>{"Forward"}));
}

TEST(SanitizedSplit, DigitsAreSeparators)
{
    EXPECT_EQ(AISession::sanitizedSplit("Take Object 12\n"),
              (std::vector<std::string>{"Take", "Object"}));
}

TEST(SanitizedSplit, ManyWords)
{
    EXPECT_EQ(AISession::sanitizedSplit("Broadcast hello world\n"),
              (std::vector<std::string>{"Broadcast", "hello", "world"}));
}

TEST(SanitizedSplit, MixedSeparators)
{
    EXPECT_EQ(AISession::sanitizedSplit("mix\t \n\tof   \tseparators"),
              (std::vector<std::string>{"mix", "of", "separators"}));
}

TEST(SanitizedSplit, GetResultSizeMatchesVectorSize)
{
    std::string s = "Set name value\n";
    EXPECT_EQ(AISession::getResultSize(s), AISession::sanitizedSplit(s).size());
}