#include "crb/ringbuffer.hpp"
#include <iostream>
#include <memory>
#include <optional>
#include <thread>

void worker(std::shared_ptr<FastRB<int>> rb){
  for(int i = 0; i < 1024; ++i){
      rb->push(i + 1);
  }
}

void consumer(std::shared_ptr<FastRB<int>> rb){
  for(int i = 0; i < 1024; ++i){
    std::optional<int> data = rb->pop();
    if (data) {
      std::cout << "consumed: " << *data << "\n";
    }
  }
}

int main () {
  constexpr size_t size = 1024;
  std::shared_ptr<FastRB<int>> frb_ptr = std::make_shared<FastRB<int>>(size);
  std::cout << "Size of: " << sizeof(*frb_ptr) << "\n";
  std::thread t1(worker, frb_ptr);
  std::thread t3(consumer, frb_ptr);

  t1.join();
  t3.join();

  std::cout << "Size of: " << sizeof(*frb_ptr) << "\n";

  return 0;
}
