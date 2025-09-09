# Ring Buffer in C

A lightweight and efficient implementation of a circular buffer (ring buffer) data structure in C, designed for high-performance applications requiring fixed-size FIFO operations.

## 📋 Description

A **Ring Buffer** (also known as Circular Buffer) is a data structure that uses a single, fixed-size buffer as if it were connected end-to-end. This implementation provides an efficient way to handle continuous data streams with constant-time operations for both insertion and removal.

## ✨ Features

- **Fixed Size**: Predefined buffer size for optimal memory usage
- **FIFO Operations**: First In, First Out data access pattern
- **Constant Time**: O(1) push and pop operations
- **Memory Efficient**: No dynamic resizing, fixed allocation
- **Overflow Protection**: Prevents buffer overflow with error handling
- **Thread-Safe Ready**: Simple structure suitable for concurrent access (with proper locking)

## 🏗️ Project Structure

```
📁 ringbuffer_C/
├── 📄 ring_buffer.c        # Main implementation
├── 📄 ring_buffer.h        # Header file with structure and function declarations
├── 📄 example.c           # Usage example and demonstration
└── 📄 README.md           # This file
```

## 🔧 Implementation

### Data Structure
```c
typedef struct s_rb
{
    uint8_t    *buffer;     // Data storage array
    size_t     head;        // Write position (next insert)
    size_t     tail;        // Read position (next remove)
    size_t     maxlen;      // Maximum buffer size
} t_rb;
```

### Core Functions
- `rb_init()`: Initialize the ring buffer with specified size
- `rb_push()`: Add data to the buffer (write operation)
- `rb_pop()`: Remove data from the buffer (read operation)
- `rb_clean()`: Clean up and free allocated memory

## 🚀 How to Use

### Compilation
```bash
gcc -Wall -Wextra -Werror ring_buffer.c example.c -o ringbuffer_demo
```

### Basic Usage Example

```c
#include "ring_buffer.h"
#include <stdio.h>

int main(void)
{
    t_rb    rb;
    uint8_t data;
    
    // Initialize buffer with size 10
    rb_init(&rb, 10);
    
    // Push some data
    rb_push(&rb, 42);
    rb_push(&rb, 100);
    rb_push(&rb, 255);
    
    // Pop data in FIFO order
    while (rb_pop(&rb, &data) != -1)
        printf("Popped: %d\n", data);
    
    // Clean up
    rb_clean(&rb);
    
    return (0);
}
```

### Advanced Usage - Stream Processing
```c
#include "ring_buffer.h"

void process_data_stream(uint8_t *incoming_data, size_t len)
{
    t_rb buffer;
    uint8_t temp;
    
    rb_init(&buffer, 1024);  // 1KB buffer
    
    for (size_t i = 0; i < len; i++)
    {
        // Try to push new data
        if (rb_push(&buffer, incoming_data[i]) == -1)
        {
            // Buffer full, pop oldest data first
            rb_pop(&buffer, &temp);
            rb_push(&buffer, incoming_data[i]);
        }
    }
    
    // Process remaining data
    while (rb_pop(&buffer, &temp) != -1)
        process_byte(temp);
    
    rb_clean(&buffer);
}
```

## ⚙️ API Reference

### `void rb_init(t_rb *c, size_t size)`
Initializes the ring buffer with the specified size.
- **Parameters**: 
  - `c`: Pointer to ring buffer structure
  - `size`: Maximum number of elements the buffer can hold
- **Note**: Allocates memory internally

### `int rb_push(t_rb *c, uint8_t data)`
Adds a new element to the buffer.
- **Parameters**: 
  - `c`: Pointer to ring buffer structure
  - `data`: Data to be added
- **Returns**: 
  - `0` on success
  - `-1` if buffer is full

### `int rb_pop(t_rb *c, uint8_t *data)`
Removes and retrieves the oldest element from the buffer.
- **Parameters**: 
  - `c`: Pointer to ring buffer structure
  - `data`: Pointer to store the retrieved data
- **Returns**: 
  - `0` on success
  - `-1` if buffer is empty

### `void rb_clean(t_rb *c)`
Cleans up the buffer and frees allocated memory.
- **Parameters**: 
  - `c`: Pointer to ring buffer structure
- **Note**: Always call this when done with the buffer

## 🧪 Test Scenarios

### Buffer States
```c
// Test empty buffer
assert(rb_pop(&rb, &data) == -1);

// Test full buffer
for (int i = 0; i < buffer_size; i++)
    rb_push(&rb, i);
assert(rb_push(&rb, 255) == -1);  // Should fail

// Test FIFO behavior
rb_push(&rb, 10);
rb_push(&rb, 20);
rb_pop(&rb, &data);
assert(data == 10);  // First in, first out
```

## 📊 Performance Characteristics

- **Time Complexity**:
  - Push: O(1)
  - Pop: O(1)
  - Init: O(1)
  - Clean: O(1)

- **Space Complexity**: O(n) where n is the buffer size

## 🎯 Use Cases

### Perfect For:
- **Audio/Video Streaming**: Continuous data flow processing
- **Sensor Data**: IoT devices with constant data input
- **Network Buffers**: Packet processing and queuing
- **Producer-Consumer**: Classic multithreading scenarios
- **Real-time Systems**: Low-latency data handling

### Example Applications:
- UART communication buffers
- Audio sample processing
- Log message queuing
- Circular logging systems
- Data acquisition systems

## 🔍 Implementation Details

### Memory Layout
```
Buffer: [_|_|_|_|_|_|_|_]
         ^         ^
       tail      head
```

- **Empty**: `head == tail`
- **Full**: `(head + 1) % maxlen == tail`
- **Data Flow**: tail → head (FIFO)

### Edge Case Handling
- **Buffer Full**: `rb_push()` returns -1
- **Buffer Empty**: `rb_pop()` returns -1
- **Wraparound**: Automatic handling when head/tail reach buffer end
- **Memory Safety**: Proper allocation/deallocation

## 🛠️ Compilation Flags

```bash
# Debug build
gcc -Wall -Wextra -Werror -g -DDEBUG ring_buffer.c example.c

# Release build
gcc -Wall -Wextra -Werror -O2 ring_buffer.c example.c

# With address sanitizer
gcc -Wall -Wextra -Werror -fsanitize=address ring_buffer.c example.c
```

## 🧩 Integration Tips

### Thread Safety
For multi-threaded use, add mutex protection:
```c
#include <pthread.h>

typedef struct s_safe_rb
{
    t_rb            rb;
    pthread_mutex_t mutex;
} t_safe_rb;
```

### Custom Data Types
Modify `uint8_t` to handle different data types:
```c
// For integers
typedef struct s_rb_int
{
    int     *buffer;
    size_t  head;
    size_t  tail;
    size_t  maxlen;
} t_rb_int;
```

## 👤 Author

**Talen400**

## 📄 License

This project is an open-source implementation for educational and practical use.

---

*Efficient circular buffer implementation by Talen400*
