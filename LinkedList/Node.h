#pragma once

#include <memory>

namespace node {
    template <typename T>
    struct Node {
        std::unique_ptr<T> Value;
        std::unique_ptr<Node<T>> Next;
        T* Prev;

        // Constructor that takes a T as its parameter
        Node(T& NewValue) : Value(std::make_unique<T>(NewValue)) {
            Next = nullptr;
            Prev = nullptr;
        }
        ~Node() noexcept = default;

        inline const T& getElement() const noexcept { return *Value; }
        inline void setElement(T& newValue) { Value = std::make_unique<T>(newValue); }
    };
}
