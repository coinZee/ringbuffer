# [Fast ring buffer]()

lightweight header-only spsc lock free ring buffer for c++
Features

- Thread safe: safe for single producer, single consumer.

- Lock free: uses std::atomic for low latency.

- Fast: uses bitwise operation (requires a power of 3 for buffer size).

## #Requirements

    C++17 (for std::optional)

## #Integration
### 1. The CMake way (Recommended)

Just drop this repo in your project (like in libs/) and add this to your CMakeLists.txt:
CMake

Add the subdirectory
```
add_subdirectory(path/to/crb)
```
Link it
```
target_link_libraries(your_app PRIVATE crb)

```
Now you can just #include <crb/ringbuffer.hpp>


### 2. The Manual way

It's header-only, so you can literally just copy the include/crb folder into your project and make sure your compiler sees it.
```Bash
g++ -std=c++17 -I./include main.cpp
```

## #Usage
```C++

#include <crb/ringbuffer.hpp>
#include <thread>
#include <iostream>

int main() {
    // make buffer (size must be power of 2)
    crb::FastRB<int> rb(1024);

    // producer
    std::thread producer([&]() {
        for (int i = 0; i < 100; ++i) {
            while (!rb.push(i)); // spin if full
        }
    });

    // consumer
    std::thread consumer([&]() {
        int count = 0;
        while (count < 100) {
            if (auto val = rb.pop()) {
                std::cout << "consumed: " << *val << "\n";
                count++;
            }
        }
    });

    producer.join();
    consumer.join();
    return 0;
}
```
