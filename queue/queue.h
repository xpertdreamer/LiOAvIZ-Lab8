//
// Created by IWOFLEUR on 20.09.2025.
//

#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>

template<typename E>
class Queue {
    private:
    struct Node {
        E data;
        Node* next;

        explicit Node(const E& d) : data(d), next(nullptr) {}
        explicit Node(E&& d) : data(static_cast<E&&>(d)), next(nullptr) {}
        ~Node() = default;
    };
    size_t size;
    Node* head;

    public:
    // Constructor
    explicit Queue() : size(0), head(nullptr) {}
    // Destructor
    ~Queue() {
        while (head != nullptr) {
            const Node* temp = head;
            head = head->next;
            delete temp;
        }
        head = nullptr;
    }
    // Prohibit assignment and movement
    Queue& operator=(const Queue&) = delete;
    Queue(const Queue&) = delete;
    Queue& operator=(Queue&&) = delete;
    Queue(Queue&&) = delete;

    // == Basic operations ==
    [[nodiscard]] bool is_empty() const { return size == 0; }

    [[nodiscard]] size_t get_size() const { return size; }

    [[maybe_unused]] const E& peek_head() const {
        if (is_empty()) throw std::out_of_range("Queue is empty");
        return head->data;
    }

    void push(E&& e) {
        auto newNode = new Node(static_cast<E&&>(e));
        if (is_empty()) head = newNode;
        else {
            auto curr = head;
            while (curr->next != nullptr) curr = curr->next;
            curr->next = newNode;
        }
        ++size;
    }

    void push(const E& e) {
        auto newNode = new Node(e);
        if (is_empty()) head = newNode;
        else {
            auto curr = head;
            while (curr->next != nullptr) curr = curr->next;
            curr->next = newNode;
        }
        ++size;
    }

    /*
        * Theoretically we can store pointer to tail
        * and check if element closer to head or to tail
        * but its more dequeue style
    */
    [[maybe_unused]] E pop() {
        if (is_empty()) throw std::out_of_range("Queue is empty");
        auto temp = head;
        E res = static_cast<E&&>(temp->data);
        head = head->next;
        delete temp;
        --size;
        return res;
    }

    void remove_from(E value) {
        if (is_empty()) throw std::out_of_range("Queue is empty");
        auto curr = head;
        while (curr->next->data != value && curr != nullptr) {
            curr = curr->next;
        }
        if (curr != nullptr) {
            auto toDel = curr->next;
            curr->next = nullptr;
            while (toDel != nullptr) {
                auto temp = toDel;
                toDel = toDel->next;
                delete temp;
            }
        }
    }

    void peek_q() const {
        if (is_empty()) throw std::out_of_range("Queue is empty");
        for (auto current = head; current != nullptr; current = current->next) {
            std::cout << current->data << " ";
        }
    }
};

#endif //QUEUE_H
