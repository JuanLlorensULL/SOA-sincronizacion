# SOA — Problemas de Sincronización

Implementación y comparativa de los problemas clásicos **productor-consumidor** y **lector-escritor** sobre un ring buffer, para la asignatura **Sistemas Operativos Avanzados** (ULL — ESIT).

## Configuración del enunciado

- **Productor-consumidor:** 1 productor, 3 consumidores.
- **Lector-escritor:** 1 escritor, 3 lectores (adaptación broadcast sobre ring buffer — cada elemento escrito debe ser leído por los 3 lectores antes de avanzar `front`).
- Vector de **N = 100** números aleatorios. Cada consumidor/lector mantiene su propia copia.
- Operaciones por consumidor/lector:
  1. **Moda** del vector tras restarle el número leído (más los 3 más repetidos).
  2. **Desviación estándar** tras actualizar `vector[i] = (vector[i] + leído) / 2`.
  3. **Sumatoria** del vector multiplicada por el número leído.

## Estructura del repositorio

```
.
├── productor-consumidor/      Implementación C++ del productor-consumidor
│   ├── include/               Cabeceras (Buffer, Producer, Consumer, Operations)
│   ├── src/                   Fuentes
│   ├── docs/                  Diagrama de flujo (Mermaid), salida Valgrind
│   └── Makefile
└── lector-escritor/           (pendiente)
```

## Tecnología

- **Lenguaje:** C++17.
- **Sincronización:** `std::thread`, `std::mutex`, `std::condition_variable` (patrón monitor con predicados).
- **Build:** GNU Make.
- **Verificación de memoria:** Valgrind.

## Compilación y ejecución

> Pendiente — se completará a medida que las implementaciones estén disponibles.

```bash
cd productor-consumidor
make
./prodcons --items 30 --buffer 5 --prod-sleep 100 --cons-sleep 300   # Caso 1: productor rápido
./prodcons --items 30 --buffer 5 --prod-sleep 300 --cons-sleep 100   # Caso 2: consumidores rápidos
make valgrind
```

## Estado

- [ ] `productor-consumidor/` — scaffold creado, implementación en curso.
- [ ] `lector-escritor/` — pendiente.
- [ ] Informe comparativo respondiendo a las preguntas de reflexión del enunciado.
