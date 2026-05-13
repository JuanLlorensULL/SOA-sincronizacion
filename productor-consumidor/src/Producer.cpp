#include "Producer.hpp"

#include "Log.hpp"

#include <iostream>
#include <random>
#include <thread>

Producer::Producer(Buffer& buffer,
                   int total_items,
                   std::chrono::milliseconds sleep_per_item,
                   unsigned seed)
    : buffer_(buffer),
      total_items_(total_items),
      sleep_per_item_(sleep_per_item),
      seed_(seed) {}

void Producer::operator()() {
    std::mt19937 rng(seed_);
    std::uniform_int_distribution<int> dist(1, 20);

    for (int i = 0; i < total_items_; ++i) {
        const int value = dist(rng);
        buffer_.add(value);
        {
            std::lock_guard<std::mutex> lk(cout_mtx);
            std::cout << "[PROD] iter=" << i << " value=" << value << '\n';
        }
        std::this_thread::sleep_for(sleep_per_item_);
    }
    buffer_.mark_done();
}
