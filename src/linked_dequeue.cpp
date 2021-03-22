#include "linked_dequeue.hpp"

#include <stdexcept>  // logic_error

namespace itis {

    void LinkedDequeue::Enqueue(Element e) {
        if (size_ == 0) {
            front_ = new DoublyNode(e, nullptr, nullptr);
            back_ = front_;

        } else {
            auto node = new DoublyNode(e, back_, nullptr);
            back_->next = node;
            back_ = node;
        }
        size_++;
    }

    void LinkedDequeue::EnqueueFront(Element e) {
        if (size_ == 0) {
            front_ = new DoublyNode(e, nullptr, nullptr);
            back_ = front_;

        } else {
            auto node = new DoublyNode(e, nullptr, front_);
            front_->previous = node;
            front_ = node;
        }
        size_++;
    }

    void LinkedDequeue::Dequeue() {
        if (size_ == 0) {
            throw std::logic_error("cannot not dequeue from empty queue");
        }
        auto node = front_;
        front_ = front_->next;
        if (!front_){
            back_ = nullptr;
        }
        size_--;
        delete node;
    }

    void LinkedDequeue::DequeueBack() {
        if (size_ == 0) {
            throw std::logic_error("cannot not dequeue from empty queue");
        }
        auto node = back_;
        back_ = back_->previous;
        if (!back_){
            front_ = nullptr;
        }
        size_--;
        delete node;
    }

    void LinkedDequeue::Clear() {
        auto node = front_;
        for (int i = 0; i < size_; i++) {
            auto node_node = node->next;
            delete node;
            node = node_node;
        }
        front_ = nullptr;
        back_ = nullptr;
        size_ = 0;
    }

// === РЕАЛИЗОВАНО ===

    LinkedDequeue::~LinkedDequeue() {
        Clear();
    }

    std::optional<Element> LinkedDequeue::front() const {
        return front_ == nullptr ? std::nullopt : std::make_optional(front_->data);
    }

    std::optional<Element> LinkedDequeue::back() const {
        return back_ == nullptr ? std::nullopt : std::make_optional(back_->data);
    }

    bool LinkedDequeue::IsEmpty() const {
        return size_ == 0;
    }

    int LinkedDequeue::size() const {
        return size_;
    }

// === НЕОБХОДИМО ДЛЯ ТЕСТИРОВАНИЯ ===

    std::ostream &operator<<(std::ostream &os, const LinkedDequeue &queue) {
        os << "size: " << queue.size_ << '\n';
        for (auto current_node = queue.front_; current_node != nullptr; current_node = current_node->previous) {
            if (current_node == queue.front_) os << "[FRONT] ";
            if (current_node == queue.back_) os << "[BACK] ";
            os << enum2str(current_node->data) << '\n';
        }
        return os;
    }

}  // namespace itis
