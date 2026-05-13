#include "Buffer.hpp"

Buffer::Buffer(std::size_t capacity)
    : data_(capacity), capacity_(capacity) {}

void Buffer::add(int value) {
    std::unique_lock<std::mutex> lk(m_);
    not_full_.wait(lk, [this] { return count_ < capacity_; });
    data_[rear_] = value;
    rear_ = (rear_ + 1) % capacity_;
    ++count_;
    not_empty_.notify_one();
}

std::optional<int> Buffer::remove() {
    std::unique_lock<std::mutex> lk(m_);
    not_empty_.wait(lk, [this] { return count_ > 0 || producer_done_; });
    if (count_ == 0) {
        return std::nullopt;
    }
    int value = data_[front_];
    front_ = (front_ + 1) % capacity_;
    --count_;
    not_full_.notify_one();
    return value;
}

void Buffer::mark_done() {
    {
        std::lock_guard<std::mutex> lk(m_);
        producer_done_ = true;
    }
    not_empty_.notify_all();
}
