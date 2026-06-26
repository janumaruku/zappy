#include <cstddef>
#include <gtest/gtest.h>
#include "BasicWaitableTimer.hpp"
#include "Timer.hpp"
#include "ContainerUtils.hpp"
#include "IoContext.hpp"

TEST(TimerTests, HandlerIsCalledAfterDuration)
{
    network::IOContext ioContext;
    SteadyTimer timer(ioContext);
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
    SteadyTimer timer2(ioContext);
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
    SteadyTimer timer(ioContext);
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

TEST(TimerTests, OrderedByExpiry)
{
    network::IOContext ioContext;
    SteadyTimer timer1(ioContext);
    SteadyTimer timer2(ioContext);
    SteadyTimer timer3(ioContext);
    SteadyTimer timer4(ioContext);

    std::vector<int> callOrder;

    timer1.asyncWait(std::chrono::milliseconds(100), [&callOrder]() {
        callOrder.push_back(1);
    });
    timer2.asyncWait(std::chrono::milliseconds(50), [&callOrder]() {
        callOrder.push_back(2);
    });
    timer3.asyncWait(std::chrono::milliseconds(150), [&callOrder]() {
        callOrder.push_back(3);
    });
    timer4.asyncWait(std::chrono::milliseconds(200), [&callOrder]() {
        callOrder.push_back(4);
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    ioContext.pollAll();
    EXPECT_EQ(callOrder, (std::vector<int>{2, 1, 3, 4}));

}