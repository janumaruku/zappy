/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** timerTests.cpp
*/

#include <gtest/gtest.h>
#include "BasicWaitableTimer.hpp"
#include "IoContext.hpp"

TEST(TimerTests, HandlerIsCalledAfterDuration)
{
    network::IOContext ioContext;
    network::BasicWaitableTimer<std::chrono::steady_clock> timer(ioContext, 1, std::chrono::milliseconds(100));
    bool handlerCalled = false;

    timer.asyncWait(timer.expiry(), [&handlerCalled]() {
        handlerCalled = true;
    });

    ioContext.run();

    EXPECT_TRUE(handlerCalled);
}

TEST(TimerTests, CancellationPreventsHandlerCall)
{
    network::IOContext ioContext;
    network::BasicWaitableTimer<std::chrono::steady_clock> timer1(ioContext, 1, std::chrono::milliseconds(50));
    network::BasicWaitableTimer<std::chrono::steady_clock> timer2(ioContext, 2, std::chrono::milliseconds(200));
    bool handler1Called = false;
    bool handler2Called = false;


    timer1.asyncWait(timer1.expiry(), [&handler1Called]() {
        handler1Called = true;
    });
    timer2.asyncWait(timer2.expiry(), [&handler2Called]() {
        handler2Called = true;
    });
    timer2.cancel();

    ioContext.run();

    EXPECT_TRUE(handler1Called);
    EXPECT_FALSE(handler2Called);
}

TEST(TimerTests, ChainCalls)
{
    network::IOContext ioContext;
    network::BasicWaitableTimer<std::chrono::steady_clock> timer(ioContext, 1, std::chrono::milliseconds(200));
    bool hasBeenCalled = false;

    timer.expiresAfter(std::chrono::milliseconds(100));
    timer.asyncWait(timer.expiry(), [&]() {
        hasBeenCalled = true;
    });

    ioContext.run();
    EXPECT_TRUE(hasBeenCalled && std::chrono::steady_clock::now().time_since_epoch().count() - timer.expiry().count() <= 100);
}