#include "Buffer.hpp"
#include "Consumer.hpp"
#include "Log.hpp"
#include "Producer.hpp"

#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <vector>

namespace {

struct Config {
    int items = 30;
    std::size_t buffer = 5;
    std::chrono::milliseconds prod_sleep{100};
    std::chrono::milliseconds cons_sleep{300};
    unsigned seed_producer = 42;
    unsigned seed_vector = 1;
    std::size_t vector_size = 100;
};

void print_usage(const char* prog) {
    std::cerr
        << "Uso: " << prog << " [opciones]\n"
        << "  --items N        número de items a producir        (def. 30)\n"
        << "  --buffer M       capacidad del ring buffer         (def. 5)\n"
        << "  --prod-sleep ms  sleep del productor entre items   (def. 100)\n"
        << "  --cons-sleep ms  sleep de cada consumidor entre items (def. 300)\n"
        << "  --seed N         semilla del productor             (def. 42)\n"
        << "  --vec-seed N     semilla del vector inicial        (def. 1)\n"
        << "  --vec-size N     tamaño del vector inicial         (def. 100)\n"
        << "  -h, --help       muestra esta ayuda\n";
}

bool parse_int(const char* s, int& out) {
    char* end = nullptr;
    const long v = std::strtol(s, &end, 10);
    if (end == s || *end != '\0') return false;
    out = static_cast<int>(v);
    return true;
}

bool parse_size(const char* s, std::size_t& out) {
    char* end = nullptr;
    const long v = std::strtol(s, &end, 10);
    if (end == s || *end != '\0' || v < 0) return false;
    out = static_cast<std::size_t>(v);
    return true;
}

bool parse_unsigned(const char* s, unsigned& out) {
    char* end = nullptr;
    const long v = std::strtol(s, &end, 10);
    if (end == s || *end != '\0' || v < 0) return false;
    out = static_cast<unsigned>(v);
    return true;
}

bool parse_args(int argc, char** argv, Config& cfg) {
    for (int i = 1; i < argc; ++i) {
        const std::string a = argv[i];
        if (a == "-h" || a == "--help") {
            print_usage(argv[0]);
            std::exit(0);
        }
        auto need = [&](const char* name) -> const char* {
            if (i + 1 >= argc) {
                std::cerr << "Falta valor para " << name << '\n';
                std::exit(2);
            }
            return argv[++i];
        };
        if (a == "--items") {
            if (!parse_int(need("--items"), cfg.items) || cfg.items < 0) return false;
        } else if (a == "--buffer") {
            if (!parse_size(need("--buffer"), cfg.buffer) || cfg.buffer == 0) return false;
        } else if (a == "--prod-sleep") {
            int ms;
            if (!parse_int(need("--prod-sleep"), ms) || ms < 0) return false;
            cfg.prod_sleep = std::chrono::milliseconds(ms);
        } else if (a == "--cons-sleep") {
            int ms;
            if (!parse_int(need("--cons-sleep"), ms) || ms < 0) return false;
            cfg.cons_sleep = std::chrono::milliseconds(ms);
        } else if (a == "--seed") {
            if (!parse_unsigned(need("--seed"), cfg.seed_producer)) return false;
        } else if (a == "--vec-seed") {
            if (!parse_unsigned(need("--vec-seed"), cfg.seed_vector)) return false;
        } else if (a == "--vec-size") {
            if (!parse_size(need("--vec-size"), cfg.vector_size) || cfg.vector_size == 0) return false;
        } else {
            std::cerr << "Argumento desconocido: " << a << '\n';
            return false;
        }
    }
    return true;
}

std::vector<int> make_initial_vector(std::size_t n, unsigned seed) {
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(1, 20);
    std::vector<int> v;
    v.reserve(n);
    for (std::size_t i = 0; i < n; ++i) v.push_back(dist(rng));
    return v;
}

}  // namespace

int main(int argc, char** argv) {
    Config cfg;
    if (!parse_args(argc, argv, cfg)) {
        print_usage(argv[0]);
        return 2;
    }

    const std::vector<int> initial_vector = make_initial_vector(cfg.vector_size, cfg.seed_vector);

    {
        std::lock_guard<std::mutex> lk(cout_mtx);
        std::cout << "[MAIN] items=" << cfg.items
                  << " buffer=" << cfg.buffer
                  << " prod_sleep=" << cfg.prod_sleep.count() << "ms"
                  << " cons_sleep=" << cfg.cons_sleep.count() << "ms"
                  << " vec_size=" << cfg.vector_size
                  << " seed_prod=" << cfg.seed_producer
                  << " seed_vec=" << cfg.seed_vector << '\n';
    }

    Buffer buffer(cfg.buffer);

    std::thread t_prod{Producer{buffer, cfg.items, cfg.prod_sleep, cfg.seed_producer}};
    std::thread t_c1{Consumer{buffer, 1, cfg.cons_sleep, initial_vector}};
    std::thread t_c2{Consumer{buffer, 2, cfg.cons_sleep, initial_vector}};
    std::thread t_c3{Consumer{buffer, 3, cfg.cons_sleep, initial_vector}};

    t_prod.join();
    t_c1.join();
    t_c2.join();
    t_c3.join();

    return 0;
}
