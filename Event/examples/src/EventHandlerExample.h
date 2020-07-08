#include "VLS/Event/EventHandler.h"
#include <string>
#include <vector>
#include <iostream>

class IBookPublisher
{
public:
    virtual ~IBookPublisher() = default;

    // Event handler is exposed with a reference to its interface.
    // The interface do therefore not have to have any members and can be mocked.
    virtual VLS::Event::IEventHandler<std::string>& NewBookEvent() const = 0;
};


class BookPublisher : public IBookPublisher
{
public:
    void AddBook(const std::string& name) {
        m_books.push_back(name);
        m_newBookEvent.Trigger(name);
    }

    VLS::Event::IEventHandler<std::string>& NewBookEvent() const override { return m_newBookEvent; }
    
private:
    // Mutable is used because subscribing to changes to an object should never affect the functionality of the object
    // The EventHandler class manages subscriptions and can be used to trigger events using the template parameters as arguments
    mutable VLS::Event::EventHandler<std::string> m_newBookEvent;

    std::vector<std::string> m_books;
};


// Free function called when the NewBookEvent is triggered
void OnNewBookPublishedFree(const std::string& name)
{
    std::cout << "New book published(Free function): " << name.c_str() << std::endl;
}


class BookSubscriber : private VLS::Event::Subscriber
{
public:
    BookSubscriber(const IBookPublisher& bookPublisher)
    {
        // Subscribe with a member function
        bookPublisher.NewBookEvent().Subscribe(m_subscriber, VLS::Event::Func::Bind(this, &BookSubscriber::OnNewBookPublished));

        // Subscribe with a lambda function
        bookPublisher.NewBookEvent().Subscribe(m_subscriber, [](const std::string& name) {
            std::cout << "New book published(Lambda function): " << name.c_str() << std::endl;
        });

        // Subscribe with a free function
        bookPublisher.NewBookEvent().Subscribe(m_subscriber, &OnNewBookPublishedFree);
    }

private:
    void OnNewBookPublished(const std::string& name)
    {
        std::cout << "New book published(Member function): " << name.c_str() << std::endl;
    }

    // The subscriber class can hold event subscribtions and it will automaticly unsubscribe when dealocated.
    VLS::Event::Subscriber m_subscriber;
};
