#include "crb/ringbuffer.hpp"
#include <optional>

// template <typename T>
// FastRB<T>::FastRB(size_t size) : 
//   capacity(size), 
//   mask(size - 1), 
//   head(0),
//   tail(0) 
// {
//   buffer.resize(capacity);
// }


// template <typename T>
// bool FastRB<T>::push(T item) {
//   if ((head - tail) >= capacity) {
//     return false;
//   }
//
//   size_t physical_index = head & mask;
//   buffer[physical_index] = item;
//   head++;
//   return true;
// }

// template <typename T>
// std::optional<T> FastRB<T>::pop() {
//   if (tail == head) {
//     return std::nullopt;
//   }
//
//   size_t physical_index = tail & mask;
//   T item = buffer[physical_index];
//   tail++;
//   return item;
// }

// template <typename T>
// size_t FastRB<T>::count() const {
//   return head - tail;
// }
