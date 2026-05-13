#include "Operations.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <unordered_map>
#include <utility>

ModaResult restar_y_calcular_moda(std::vector<int>& v, int leido) {
    for (int& x : v) {
        x -= leido;
    }

    std::unordered_map<int, int> freq;
    freq.reserve(v.size());
    for (int x : v) {
        ++freq[x];
    }

    std::vector<std::pair<int, int>> pairs(freq.begin(), freq.end());
    std::sort(pairs.begin(), pairs.end(),
              [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                  if (a.second != b.second) return a.second > b.second;
                  return a.first < b.first;
              });

    ModaResult r;
    r.moda = pairs.front().first;
    const std::size_t k = std::min<std::size_t>(3, pairs.size());
    r.top3.reserve(k);
    for (std::size_t i = 0; i < k; ++i) {
        r.top3.push_back(pairs[i].first);
    }
    return r;
}

double promediar_y_calcular_desviacion(std::vector<int>& v, int leido) {
    for (int& x : v) {
        x = (x + leido) / 2;
    }

    double sum = 0.0;
    for (int x : v) {
        sum += x;
    }
    const double mean = sum / static_cast<double>(v.size());

    double sq_sum = 0.0;
    for (int x : v) {
        const double d = static_cast<double>(x) - mean;
        sq_sum += d * d;
    }
    return std::sqrt(sq_sum / static_cast<double>(v.size()));
}

long long sumatoria_por(const std::vector<int>& v, int leido) {
    long long sum = 0;
    for (int x : v) {
        sum += x;
    }
    return sum * static_cast<long long>(leido);
}
