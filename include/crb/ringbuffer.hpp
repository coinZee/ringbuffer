#pragma once
#include <atomic>
#include <cstddef>
// #include <iterator>
#include <optional>
#include <stdexcept>
#include <vector>

template <typename T>
class FastRB {
public:
  std::vector<T> buffer; // 24 bytes
  size_t capacity; // 8 bytes
  size_t mask;  // 8 bytes
                // 40 bytes!!

  char pad1[24]; 
  // padding 24 bytes to make it 64 bytes to fit in the first cache line 
  // so that the head and tail can start fresh on new cache line to prevent false sharing;

  alignas(64) std::atomic<size_t> head{0};
  alignas(64) std::atomic<size_t> tail{0};

  bool push(T item){
    size_t current_head = head.load(std::memory_order_relaxed);
    size_t current_tail = tail.load(std::memory_order_acquire);

    if((current_head - current_tail) >= capacity) return false;

    buffer[current_head & mask] = item;
    head.store(current_head + 1, std::memory_order_release);
    return true;
  }

  std::optional<T> pop(){
    size_t current_tail = tail.load(std::memory_order_acquire);
    size_t current_head = head.load(std::memory_order_acquire);

    if (current_tail == current_head) return std::nullopt;

    T item = buffer[current_tail & mask];
    tail.store(current_tail + 1, std::memory_order_release);
    return item;
  }

  FastRB(size_t size) : 
    head(0),
    tail(0) 
  {
    if (size < 2 || (size & (size - 1)) != 0) {
      throw std::invalid_argument("size must be a power of 2");
    }
    capacity = size;
    mask = size - 1;
    buffer.resize(capacity);
  }

  ~FastRB() = default;
  
};

