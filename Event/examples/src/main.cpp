#include "EventHandlerExample.h"

#include <iostream>
#include <memory>

int main()
{
    BookPublisher publisher;
    auto subscriber = std::make_unique<BookSubscriber>(publisher);

    std::cout << "Trigger a new book event from the publisher" << std::endl;

    // Trigger a new book event
    publisher.AddBook("Hello world");

    // Clear the subscriber and trigger the new book event again to show the subscription has been removed
    subscriber.reset();
    publisher.AddBook("Hello world (No subscription)");
}