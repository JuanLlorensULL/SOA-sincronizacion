#pragma once

#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <optional>
#include <vector>

class Buffer {
public:
    explicit Buffer(std::size_t capacity);

    void add(int value);

    // Devuelve nullopt cuando el productor ha terminado y el buffer está vacío.
    std::optional<int> remove();

    // Llamar UNA sola vez desde el productor al terminar; despierta a los
    // consumidores bloqueados para que vean la condición de terminación.
    void mark_done();

private:
    std::vector<int> data_;
    std::size_t capacity_;
    std::size_t front_ = 0;
    std::size_t rear_ = 0;
    std::size_t count_ = 0;
    bool producer_done_ = false;

    std::mutex m_;
    std::condition_variable not_full_;
    std::condition_variable not_empty_;
};
