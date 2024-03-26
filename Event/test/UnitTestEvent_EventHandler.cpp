/*
 * Copyright 2020 Vilaversoftware IVS (http://vilaversoftware.dk/)
 * Author: Mikkel Nøhr Løvgreen (ml@vilaversoftware.dk)
 * ------------------------------------------------------------------------
 * Licensed to Vilaversoftware IVS who licenses this file to you under the
 * Apache License, Version 2.0 (the "License"); you may not use this file
 * except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma warning(push, 0)
#include <gtest/gtest.h>
#pragma warning(pop)

#include <functional>

#include <VLS/Event/Bind.h>
#include <VLS/Event/EventHandler.h>
#include <VLS/Event/EventLoop.h>

using namespace VLS;

static int sEventValue = 0;

void SetEventValue() { sEventValue = 42; }

void SetEventValue1(int v1) { sEventValue = v1; }

void SetEventValue2(int v1, int v2) { sEventValue = v1 + v2; }

class EventRetriever {
 public:
  void SetValue() { value = 42; }
  void SetValue1(int v1) { value = v1; }
  void SetValue2(int v1, int v2) { value = v1 + v2; }
  int value = 0;
};

TEST(VLSEventHandler0, SuccessLamda) {
  Event::EventHandler<> eventHandler;
  int value = 0;
  auto u = eventHandler.Subscribe([&value]() { value = 42; });
  EXPECT_EQ(value, 0);
  eventHandler.Trigger();
  EXPECT_EQ(value, 42);
}

TEST(VLSEventHandler0, SuccessMember) {
  Event::EventHandler<> eventHandler;
  EventRetriever cr;
  auto u = eventHandler.Subscribe(
      VLS::Event::Func::Bind(&cr, &EventRetriever::SetValue));
  EXPECT_EQ(cr.value, 0);
  eventHandler.Trigger();
  EXPECT_EQ(cr.value, 42);
}

TEST(VLSEventHandler0, SuccessFree) {
  Event::EventHandler<> eventHandler;
  SetEventValue1(0);
  auto u = eventHandler.Subscribe(&SetEventValue);
  EXPECT_EQ(sEventValue, 0);
  eventHandler.Trigger();
  EXPECT_EQ(sEventValue, 42);
}

TEST(VLSEventHandler0, ScopeUnsubscribe1) {
  Event::EventHandler<> eventHandler;
  int value = 0;
  {
    // The Unsubscriber is not kept alive so it unsubscribes before the
    // eventHandler is triggered
    auto u = eventHandler.Subscribe([&value] { value = 42; });
  }
  eventHandler.Trigger();
  EXPECT_EQ(value, 0);
}

TEST(VLSEventHandler0, ScopeUnsubscribe2) {
  Event::Subscriber::UPtr u;
  {
    Event::EventHandler<> eventHandler;
    int value = 0;
    u = eventHandler.Subscribe([&value]() { value = 42; });
    EXPECT_EQ(u->PublisherCount(), 1);
  }
  // Event function handler is deleted before the unsubscribe object
  EXPECT_EQ(u->PublisherCount(), 0);
}

TEST(VLSEventHandler0, ManualUnsubscribe) {
  Event::EventHandler<> eventHandler;
  int value = 0;
  auto u = eventHandler.Subscribe([&value]() { value = 42; });
  u->UnsubscribeAll();
  eventHandler.Trigger();
  EXPECT_EQ(value, 0);
}

TEST(VLSEventHandler0, EventLoop) {
  std::string name = "Test Thread";
  Event::EventLoop eventLoop;
  eventLoop.Start(name);
  Event::EventHandler<> eventHandler;
  Event::Subscriber sub;
  std::string threadName = VLS::Event::EventLoop::ThreadName();
  int value = 0;
  EXPECT_TRUE(eventHandler.Subscribe(sub,
                                     [&value, &threadName]() {
                                       value = 42;
                                       threadName =
                                           VLS::Event::EventLoop::ThreadName();
                                     },
                                     &eventLoop));
  EXPECT_EQ(value, 0);
  eventHandler.Trigger();
  eventLoop.Stop();
  EXPECT_EQ(threadName, name);
  EXPECT_EQ(value, 42);
}

TEST(VLSEventHandler1, SuccessLamda) {
  Event::EventHandler<int> eventHandler;
  int value = 0;
  auto u = eventHandler.Subscribe([&value](int i) { value = i; });
  EXPECT_EQ(value, 0);
  eventHandler.Trigger(42);
  EXPECT_EQ(value, 42);
}

TEST(VLSEventHandler1, SuccessMember) {
  Event::EventHandler<int> eventHandler;
  EventRetriever cr;
  auto u = eventHandler.Subscribe(
      Event::Func::Bind(&cr, &EventRetriever::SetValue1));
  EXPECT_EQ(cr.value, 0);
  eventHandler.Trigger(42);
  EXPECT_EQ(cr.value, 42);
}

TEST(VLSEventHandler1, SuccessFree) {
  Event::EventHandler<int> eventHandler;
  SetEventValue1(0);
  auto u = eventHandler.Subscribe(&SetEventValue1);
  EXPECT_EQ(sEventValue, 0);
  eventHandler.Trigger(42);
  EXPECT_EQ(sEventValue, 42);
}

TEST(VLSEventHandler1, ScopeUnsubscribe1) {
  Event::EventHandler<int> eventHandler;
  int value = 0;
  {
    // The Unsubscriber is not kept alive so it unsubscribes before the
    // eventHandler is triggered
    auto u = eventHandler.Subscribe([&value](int i) { value = i; });
  }
  eventHandler.Trigger(42);
  EXPECT_EQ(value, 0);
}

TEST(VLSEventHandler1, ScopeUnsubscribe2) {
  Event::Subscriber::UPtr u;
  {
    Event::EventHandler<int> eventHandler;
    int value = 0;
    u = eventHandler.Subscribe([&value](int i) { value = i; });
  }
  // Event function handler is deleted before the unsubscribe object
  EXPECT_EQ(u->PublisherCount(), 0);
}

TEST(VLSEventHandler1, ManualUnsubscribe) {
  Event::EventHandler<int> eventHandler;
  int value = 0;
  auto u = eventHandler.Subscribe([&value](int i) { value = i; });
  u->UnsubscribeAll();
  eventHandler.Trigger(42);
  EXPECT_EQ(value, 0);
}

TEST(VLSEventHandler2, SuccessLamda) {
  Event::EventHandler<int, int> eventHandler;
  int value = 0;
  auto u =
      eventHandler.Subscribe([&value](int v1, int v2) { value = v1 + v2; });
  EXPECT_EQ(value, 0);
  eventHandler.Trigger(20, 22);
  EXPECT_EQ(value, 42);
}

TEST(VLSEventHandler2, SuccessMember) {
  Event::EventHandler<int, int> eventHandler;
  EventRetriever cr;
  auto u = eventHandler.Subscribe(
      Event::Func::Bind(&cr, &EventRetriever::SetValue2));
  EXPECT_EQ(cr.value, 0);
  eventHandler.Trigger(5, 37);
  EXPECT_EQ(cr.value, 42);
}

TEST(VLSEventHandler2, SuccessFree) {
  Event::EventHandler<int, int> eventHandler;
  SetEventValue1(0);
  auto u = eventHandler.Subscribe(&SetEventValue2);
  EXPECT_EQ(sEventValue, 0);
  eventHandler.Trigger(50, -8);
  EXPECT_EQ(sEventValue, 42);
}

TEST(VLSEventHandler2, Persistent) {
  Event::EventHandler<int, int> eventHandler;
  int value = 0;
  eventHandler.SubscribePersistent(
      [&value](int v1, int v2) { value = v1 + v2; });
  EXPECT_EQ(value, 0);
  eventHandler.Trigger(20, 22);
  EXPECT_EQ(value, 42);
}

TEST(VLSEventHandler2, SuppliedSubsriber) {
  Event::EventHandler<int, int> eventHandler;
  Event::Subscriber sub;
  int value = 0;
  EXPECT_TRUE(eventHandler.Subscribe(
      sub, [&value](int v1, int v2) { value = v1 + v2; }));
  EXPECT_EQ(value, 0);
  eventHandler.Trigger(20, 22);
  EXPECT_EQ(value, 42);
  sub.UnsubscribeAll();
  eventHandler.Trigger(4, 12);
  EXPECT_EQ(value, 42);
}

TEST(VLSEventHandler2, EventLoop) {
  std::string name = "Test Thread";
  Event::EventLoop eventLoop;
  eventLoop.Start(name);
  Event::EventHandler<int, int> eventHandler;
  Event::Subscriber sub;
  std::string threadName = VLS::Event::EventLoop::ThreadName();
  int value = 0;
  EXPECT_TRUE(eventHandler.Subscribe(sub,
                                     [&value, &threadName](int v1, int v2) {
                                       value = v1 + v2;
                                       threadName =
                                           VLS::Event::EventLoop::ThreadName();
                                     },
                                     &eventLoop));
  EXPECT_EQ(value, 0);
  eventHandler.Trigger(20, 22);
  eventLoop.Stop();
  EXPECT_EQ(threadName, name);
  EXPECT_EQ(value, 42);
}

TEST(VLSEventHandler2, MultipeSubscribers) {
  Event::EventHandler<int, int> eventHandler;

  int value1, value2, value3;
  Event::Subscriber sub1;
  eventHandler.Subscribe(sub1, [&value1](int v1, int v2) { value1 = v1 + v2; });
  auto sub2 =
      eventHandler.Subscribe([&value2](int v1, int v2) { value2 = v1 - v2; });
  eventHandler.SubscribePersistent(
      [&value3](int v1, int v2) { value3 = v1 * v2; });

  eventHandler.Trigger(22, 20);
  EXPECT_EQ(value1, 42);
  EXPECT_EQ(value2, 2);
  EXPECT_EQ(value3, 440);

  sub1.UnsubscribeAll();
  eventHandler.Trigger(4, 12);
  EXPECT_EQ(value1, 42);
  EXPECT_EQ(value2, -8);
  EXPECT_EQ(value3, 48);
}

TEST(VLSEventHandler7, Success1) {
  Event::EventHandler<int, unsigned int, double, unsigned short, size_t, long,
                      char>
      eventHandler;
  int value = 0;
  auto u = eventHandler.Subscribe([&value](int v1, unsigned int v2, double v3,
                                           unsigned short v4, size_t v5,
                                           long v6, char v7) {
    value = (int)v1 + (int)v2 + (int)v3 + (int)v4 + (int)v5 + (int)v6 + (int)v7;
  });
  EXPECT_EQ(value, 0);
  eventHandler.Trigger(6, 6, 6, 6, 6, 6, 6);
  EXPECT_EQ(value, 42);
}

TEST(VLSEventHandlerGeneral, UnsubscribeDuringCallback) {
  Event::EventHandler<> eventHandler;
  Event::Subscriber subscriber;
  int value = 0;
  eventHandler.Subscribe(subscriber, [&value, &subscriber]() {
    value += 42;
    subscriber.UnsubscribeAll();
  });
  // State before triggering the event
  EXPECT_EQ(value, 0);
  EXPECT_EQ(subscriber.PublisherCount(), 1);

  // Triggere the call back function that unsubscribe from the event
  eventHandler.Trigger();
  EXPECT_EQ(value, 42);
  EXPECT_EQ(subscriber.PublisherCount(), 0);
}
