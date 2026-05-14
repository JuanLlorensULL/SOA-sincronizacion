#include "Consumer.hpp"

#include "Log.hpp"
#include "Operations.hpp"

#include <cstddef>
#include <iostream>
#include <thread>

namespace {

void print_vector(const std::vector<int>& v) {
    std::cout << '[';
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (i) std::cout << ',';
        std::cout << v[i];
    }
    std::cout << ']';
}

}  // namespace

Consumer::Consumer(Buffer& buffer,
                   int id,
                   std::chrono::milliseconds sleep_per_item,
                   const std::vector<int>& initial_vector)
    : buffer_(buffer),
      id_(id),
      sleep_per_item_(sleep_per_item),
      vector_(initial_vector) {}

void Consumer::operator()() {
    int iter = 0;
    while (auto v = buffer_.remove()) {
        consumidos_.push_back(*v);
        process(*v, iter++);
        std::this_thread::sleep_for(sleep_per_item_);
    }
}

void Consumer::process(int value, int iter) {
    switch (id_) {
        case 1: {
            const ModaResult r = restar_y_calcular_moda(vector_, value);
            std::lock_guard<std::mutex> lk(cout_mtx);
            std::cout << "[C1] iter=" << iter << " read=" << value
                      << " moda=" << r.moda << " top3=";
            print_vector(r.top3);
            std::cout << " vector=";
            print_vector(vector_);
            std::cout << '\n';
            break;
        }
        case 2: {
            const double sigma = promediar_y_calcular_desviacion(vector_, value);
            std::lock_guard<std::mutex> lk(cout_mtx);
            std::cout << "[C2] iter=" << iter << " read=" << value
                      << " desviacion=" << sigma << " vector=";
            print_vector(vector_);
            std::cout << '\n';
            break;
        }
        case 3: {
            const long long sum = sumatoria_por(vector_, value);
            std::lock_guard<std::mutex> lk(cout_mtx);
            std::cout << "[C3] iter=" << iter << " read=" << value
                      << " sumatoria=" << sum << " vector=";
            print_vector(vector_);
            std::cout << '\n';
            break;
        }
    }
}
