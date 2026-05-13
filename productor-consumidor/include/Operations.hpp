#pragma once

#include <vector>

struct ModaResult {
    int moda;                  // valor que aparece con mayor frecuencia
    std::vector<int> top3;     // hasta 3 valores con mayor frecuencia (orden descendente)
};

// Consumidor 1.
// Resta 'leido' a cada elemento de v (in-place) y devuelve la moda del
// vector resultante junto con sus 3 valores más frecuentes.
// En empate por frecuencia, se prefiere el valor numérico menor.
ModaResult restar_y_calcular_moda(std::vector<int>& v, int leido);

// Consumidor 2.
// Para cada i: v[i] = (v[i] + leido) / 2 (in-place, división entera).
// Devuelve la desviación estándar poblacional del vector resultante.
double promediar_y_calcular_desviacion(std::vector<int>& v, int leido);

// Consumidor 3.
// Devuelve la suma de los elementos de v multiplicada por 'leido'.
// NO muta el vector.
long long sumatoria_por(const std::vector<int>& v, int leido);
