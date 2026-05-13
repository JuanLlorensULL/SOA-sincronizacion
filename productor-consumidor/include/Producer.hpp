#pragma once

#include "Buffer.hpp"

#include <chrono>

class Producer {
public:
    Producer(Buffer& buffer,
             int total_items,
             std::chrono::milliseconds sleep_per_item,
             unsigned seed);

    void operator()();

private:
    Buffer& buffer_;
    int total_items_;
    std::chrono::milliseconds sleep_per_item_;
    unsigned seed_;
};
