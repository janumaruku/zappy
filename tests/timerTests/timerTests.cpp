#include <cstddef>
#include <gtest/gtest.h>
#include "BasicWaitableTimer.hpp"
#include "Timer.hpp"
#include "IoContext.hpp"

TEST(TimerTests, HandlerIsCalledAfterDuration)
{
    network::IOContext ioContext;
    SteadyTimer timer(ioContext, 1);
    bool handlerCalled = false;

    timer.asyncWait(std::chrono::milliseconds(100),[&handlerCalled]() {
        handlerCalled = true;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(150));

    ioContext.pollAll();
    EXPECT_TRUE(handlerCalled);
}

TEST(TimerTests, CancellationPreventsHandlerCall)
{
    network::IOContext ioContext;
    SteadyTimer timer2(ioContext, 2);
    bool handler2Called = false;

    timer2.asyncWait(std::chrono::milliseconds(50), [&handler2Called]() {
        handler2Called = true;
    });
    timer2.cancel();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    ioContext.pollAll();
    EXPECT_FALSE(handler2Called);
}

TEST(TimerTests, ChainCalls)
{
    network::IOContext ioContext;
    SteadyTimer timer(ioContext, 1);
    bool hasBeenCalled = false;

    timer.expiresAfter(std::chrono::milliseconds(100));
    timer.asyncWait(std::chrono::milliseconds(0), [&]() {
        hasBeenCalled = true;
    });
    ioContext.pollAll();

    auto now = std::chrono::steady_clock::now().time_since_epoch().count();
    EXPECT_TRUE(hasBeenCalled);
    EXPECT_LE(now - timer.expiry().time_since_epoch().count(), 500'000'000LL);
}