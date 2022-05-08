#pragma once

#include <memory>

namespace VLS::Variant {

struct vtable {
    bool (is_const)(void *ptr);
    void (*op_assing)(void* ptr1, void* ptr2);
    //void (*destroy_)(void* ptr);
    //void* (*clone_)(void* ptr);
    //void* (*move_)(void* ptr);
    
};

template<class T>
constexpr vtable vtable_for{
    [] (void* ptr) -> bool { return std::is_const<T>; }
    [](void* ptr1, void* ptr) {
        
    }

    //[](void* ptr) { static_cast<T*>(ptr)->speak(); },
    //[](void* ptr) { delete static_cast<T*>(ptr); },
    //[](void* ptr) -> void* { return new T(*static_cast<T*>(ptr)); },
    //[](void* ptr) -> void* { return new T(std::move(*static_cast<T*>(ptr))); }
};

class MetaRef
{
    void* t_;
    vtable const* vtable_;

public:
    template<class T>
    MetaRef(T t)
        : t_(t)
        , vtable_(&vtable_for<T>)
    {
        // TODO: Add compile time checks
    }

    MetaRef& operator=(MetaRef const& value) {
        
        return *this;
    }

};





//struct vtable {
//    void (*speak)(void* ptr);
//    void (*destroy_)(void* ptr);
//    void* (*clone_)(void* ptr);
//    void* (*move_)(void* ptr);
//};
//
//template<class T>
//constexpr vtable vtable_for{
//    [] (void* ptr) { static_cast<T*>(ptr)->speak(); },
//    [] (void* ptr) { delete static_cast<T*>(ptr); },
//    [] (void* ptr) -> void* { return new T(*static_cast<T*>(ptr)); },
//    [] (void* ptr) -> void* { return new T(std::move(*static_cast<T*>(ptr))); }
//};
//
//class animal
//{
//    void* t_;
//    vtable const* vtable_;
//
//public:
//    template<class T>
//    animal(T const& t)
//        : t_(new T(t))
//        , vtable_(&vtable_for<T>)
//    {
//        // TODO: Add compile time checks
//    }
//
//    animal(animal const& value)
//        : t_(value.vtable_->clone_(value.t_)),
//          vtable_(value.vtable_) {
//    }
//
//    animal(animal const&& value)
//        : t_(value.vtable_->move_(value.t_)),
//        vtable_(value.vtable_) {
//    }
//
//    ~animal() { vtable_->destroy_(t_); }
//
//    animal& operator=(animal const& value) {
//        t_ = value.vtable_->clone_(value.t_);
//        vtable_ = value.vtable_;
//        return *this;
//    }
//
//    animal& operator=(animal && value) {
//        t_ = value.vtable_->move_(value.t_);
//        vtable_ = value.vtable_;
//        return *this;
//    }
//
//    void speak() { vtable_->speak(t_); }
//};
}
