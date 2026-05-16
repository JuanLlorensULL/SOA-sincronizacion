# SOA — Problemas de Sincronización

Implementación del problema clásico **productor-consumidor** sobre un ring buffer, para la asignatura **Sistemas Operativos Avanzados** (ULL — ESIT).

> El enunciado planteaba originalmente una comparativa con lector-escritor, pero el profesor confirmó que entregar solo productor-consumidor es suficiente. Por eso este repositorio no incluye `lector-escritor/`.

## Entregables

- **Informe:** [`informe.md`](informe.md) — respuesta a las preguntas de reflexión del enunciado con datos experimentales.
- **Código:** [`productor-consumidor/`](productor-consumidor/).
- **Diagramas de flujo (Mermaid):** [`productor-consumidor/docs/diagrama-flujo.md`](productor-consumidor/docs/diagrama-flujo.md).
- **Valgrind limpio:** [`productor-consumidor/docs/valgrind.log`](productor-consumidor/docs/valgrind.log) — 0 errores, 0 leaks.
- **Logs de los dos casos de tiempos:** [`caso1.log`](productor-consumidor/docs/caso1.log), [`caso2.log`](productor-consumidor/docs/caso2.log).

## Configuración del enunciado

- 1 productor, 3 consumidores.
- Vector de **N = 100** números aleatorios. Cada consumidor mantiene su propia copia.
- Operaciones por consumidor:
  1. **Moda** del vector tras restarle el número leído (más los 3 más repetidos).
  2. **Desviación estándar** tras actualizar `vector[i] = (vector[i] + leído) / 2`.
  3. **Sumatoria** del vector multiplicada por el número leído.

## Estructura del repositorio

```
.
├── informe.md                 Informe del entregable
└── productor-consumidor/      Implementación C++
    ├── include/               Cabeceras (Buffer, Producer, Consumer, Operations, Log)
    ├── src/                   Fuentes
    ├── docs/                  Diagrama de flujo, Valgrind, logs de los dos casos
    └── Makefile
```

## Tecnología

- **Lenguaje:** C++17.
- **Sincronización:** `std::thread`, `std::mutex`, `std::condition_variable` (patrón monitor con predicados).
- **Build:** GNU Make.
- **Verificación de memoria:** Valgrind.

## Compilación y ejecución

```bash
cd productor-consumidor
make
make run-caso1     # productor rápido (--prod-sleep 100 --cons-sleep 300)
make run-caso2     # consumidores rápidos (--prod-sleep 300 --cons-sleep 100)
make valgrind      # genera docs/valgrind.log
```
