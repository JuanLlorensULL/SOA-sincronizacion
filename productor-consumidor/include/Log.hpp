#pragma once

#include <mutex>

// Mutex compartido para serializar la salida de los hilos por std::cout.
// Sin él, los mensajes del productor y de los 3 consumidores se interpolan
// y la traza es ilegible.
inline std::mutex cout_mtx;
