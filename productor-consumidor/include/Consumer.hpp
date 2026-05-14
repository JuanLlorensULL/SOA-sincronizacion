#pragma once

#include "Buffer.hpp"

#include <chrono>
#include <vector>

class Consumer {
public:
    Consumer(Buffer& buffer,
             int id,                                       // 1, 2 o 3 — selecciona la operación
             std::chrono::milliseconds sleep_per_item,
             const std::vector<int>& initial_vector);

    void operator()();

private:
    void process(int value, int iter);

    Buffer& buffer_;
    int id_;
    std::chrono::milliseconds sleep_per_item_;
    std::vector<int> vector_;       // copia mutable propia de este consumidor
    std::vector<int> consumidos_;   // historial de números leídos
};
