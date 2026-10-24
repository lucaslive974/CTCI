# Cracking the Coding Interview (CTCI) — Modern C++23 Engineering Showcase

[![Language](https://img.shields.io/badge/Language-C%2B%2B23-blue.svg)](https://en.cppreference.com/w/cpp/23)
[![Build Tool](https://img.shields.io/badge/Build-CMake%20%7C%20Ninja-success.svg)](https://cmake.org)
[![Tests](https://img.shields.io/badge/Tests-314%20Passed-brightgreen.svg)](#testing--verification)
[![Coverage](https://img.shields.io/badge/Coverage-100%25%20(Lines%20%2F%20Branches)-brightgreen.svg)](#code-coverage)
[![Memory Safety](https://img.shields.io/badge/Valgrind-0%20Leaks%20%7C%20Clean-brightgreen.svg)](#memory-safety--valgrind)
[![Linter](https://img.shields.io/badge/Clang--Tidy-Automated-blueviolet.svg)](#developer-tooling)

A high-performance, production-grade **C++23** implementation of classic algorithms and data structures inspired by *Cracking the Coding Interview* (Gayle Laakmann McDowell).

Rather than relying on the standard library, this repository is built on a **custom, handcrafted standard-library foundation**—including custom allocators, smart pointers with full polymorphic semantics, dynamic vectors, hash maps, arbitrary-sized bitsets, and graph/tree containers. Every component is engineered for zero-cost abstractions, strict RAII memory safety, and 100% unit-tested branch and line coverage.

---

## Key Highlights

- **Custom Memory Management & Smart Pointers**: Handcrafted [`Allocator<T>`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/memory.hpp#L10), [`UniquePtr<T>`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/memory.hpp#L129), and [`SharedPtr<T>`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/memory.hpp#L40) with atomic reference counting, custom allocator rebinding, and runtime RTTI casts (`dynamicPointerCast`, `staticPointerCast`).
- **Bespoke Container Library**: Self-contained implementations of [`Vector<T>`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/vector.hpp#L20), [`HashMap<K, V>`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/associative_containers.hpp#L216), [`Set<K>`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/associative_containers.hpp#L217), [`Bitset<Size>`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/bitset.hpp#L11), [`Array<T, N>`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/array.hpp#L11), [`List<T>`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/list.hpp#L21), [`Deque<T>`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/deque.hpp#L21), [`Stack<T>`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/stack.hpp#L10), [`Tree<T>`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/tree.hpp#L28), and [`Graph<T>`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/graph.hpp#L16).
- **Modern C++23 Idioms**: Extensive use of Concepts (`std::integral`, `concepts::Hashable`, `concepts::Allocator`), Range views (`std::views::iota`, `std::views::zip`, `std::views::enumerate`), and C++23 **Deducing `this`** for clean recursive lambdas.
- **100.00% Test Coverage**: Verified across **314 unit tests** covering every line, branch, function, and region with LLVM / GCC profiling.
- **Zero Memory Leaks**: 100% clean Valgrind Memcheck verification (over 9,700 dynamic allocations and deallocations with 0 leaks and 0 errors).

---

## Architecture Overview

```
CTCI/
├── include/                          # Public Header API
│   ├── memory.hpp                    # Allocator, SharedPtr, UniquePtr, makeShared, makeUnique
│   ├── vector.hpp                    # Vector<T> with geometric resizing, move-only, & range support
│   ├── associative_containers.hpp    # Generic Map, HashMap, and Set with bucket chaining
│   ├── bitset.hpp                    # Multi-word BitsetImpl with bitwise operations & shifts
│   ├── array.hpp                     # Fixed-capacity Array with random access iterators
│   ├── iterators.hpp                 # ContiguousIteratorImpl for standard range compatibility
│   ├── list.hpp                      # Singly-linked List & Queue
│   ├── deque.hpp                     # Doubly-linked Deque
│   ├── stack.hpp                     # LIFO container adapter
│   ├── tree.hpp                      # Binary Search Tree (BST) with rank & depth tracking
│   ├── graph.hpp                     # Directed & Undirected Adjacency Graph
│   ├── concepts.hpp                  # C++20/23 concepts (Movable, Copyable, Hashable, Allocator)
│   ├── matrix.hpp                    # Matrix and Row aliases
│   ├── exceptions.hpp                # Domain exceptions (OutOfRange, CircularReferenceError)
│   ├── data_structures.hpp           # Aggregator header for all containers
│   └── chapters.hpp                  # Interview solutions (Chapters I through VI)
├── src/                              # Algorithm Implementations
│   ├── i.cpp                         # Chapter 1: Arrays and Strings
│   ├── ii.cpp                        # Chapter 2: Linked Lists
│   ├── iii.cpp                       # Chapter 3: Stacks and Queues
│   ├── iv.cpp                        # Chapter 4: Trees and Graphs
│   ├── v.cpp                         # Chapter 5: Bit Manipulation
│   ├── vi.cpp                        # Chapter 6: Math and Logic Puzzles
│   ├── chapter.cpp                   # Chapter base class
│   └── utils.cpp                     # Console formatting utilities
├── tests/                            # Comprehensive GoogleTest Suites (314 Tests)
│   ├── memory.cpp                    # Smart pointer lifecycle, conversions, and polymorphism
│   ├── vector.cpp                    # Dynamic resizing, move-only types, range operations
│   ├── associative_containers.cpp    # Hash collision handling, resizing, iterators
│   ├── bitset.cpp                    # Bitwise arithmetic, bit shifts, word boundary tests
│   ├── array.cpp                     # Range iterators, boundary access, non-trivial destruction
│   ├── list.cpp & deque.cpp          # Node insertion, reversal, popping
│   ├── stack.cpp & graph.cpp & tree.cpp
│   └── [i - vi].cpp                  # Algorithmic problem verification
└── cmake/                            # Modular CMake Build System
    ├── language_standard.cmake       # C++23 enforcement
    ├── tests.cmake                   # CTest, coverage targets, Valgrind integration
    ├── gtest.cmake                   # FetchContent GoogleTest dependency
    └── utils.cmake                   # Toolchain helpers
```

---

## Data Structures Engineering

### 1. Memory Management & Smart Pointers ([`include/memory.hpp`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/memory.hpp))

- **[`Allocator<T>`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/memory.hpp#L10)**: Custom stateless allocator decoupling raw memory allocation (`::operator new`) from object construction (placement `new`), with selective destruction based on `std::is_trivially_destructible_v<T>` and member type re-binding (`rebind<U>()`).
- **[`UniquePtr<T>`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/memory.hpp#L129)**: Strict exclusive ownership smart pointer with zero overhead. Supports custom allocators, explicit resource release, move semantics, and safe upcasting to base pointers via `requires(std::is_base_of_v<U, T>)`.
- **[`SharedPtr<T>`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/memory.hpp#L40)**: Thread-safe, atomic reference-counted (`std::atomic_uint`) shared ownership smart pointer. Supports:
  - Copy and move construction/assignment.
  - Polymorphic base conversion operator.
  - Safe cast helpers: [`dynamicPointerCast<U>`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/memory.hpp#L198) and [`staticPointerCast<U>`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/memory.hpp#L201) preserving shared reference count ownership.

### 2. Dynamic Vector ([`include/vector.hpp`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/vector.hpp))

A dynamic contiguous array that mirrors `std::vector`, engineered from low-level memory primitives:
- **Bitwise geometric growth**: Automatically adjusts capacity through bit-shifts (`_capacity <<= 1`).
- **Type-trait optimizations**: Uses `std::memcpy` and `std::memmove` for trivially copyable/movable types while cleanly falling back to placement move construction for complex types.
- **Move-only type support**: Fully compatible with move-only objects (e.g. `Vector<UniquePtr<T>>`).
- **STL & Range Compatibility**: Implements random-access iterator semantics (`begin()`, `end()`, `operator[]`, `data()`, `cdata()`), supporting `std::ranges` pipelines and structured bindings.

### 3. Associative Containers ([`include/associative_containers.hpp`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/associative_containers.hpp))

- **[`Map<IsSet, Key, ValueType>`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/associative_containers.hpp#L12)**: Unified hash table architecture using bucket chaining with custom [`Vector`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/vector.hpp#L20) and [`List`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/list.hpp#L21).
  - Aliased into [`HashMap<Key, Value>`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/associative_containers.hpp#L216) and [`Set<Key>`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/associative_containers.hpp#L217).
  - Automated rehashing when load factor exceeds 0.80.
  - Forward iterator navigating non-empty buckets sequentially across chains.

### 4. Arbitrary Multi-Word Bitset ([`include/bitset.hpp`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/bitset.hpp))

- **[`BitsetImpl<Ty, Size>`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/bitset.hpp#L11)**: Stack-allocated bit collection spanning multiple storage words of any unsigned integral type.
  - Full bitwise operator overloads (`~`, `&`, `|`, `^`, `&=`, `|=`, `^=`, `<<`, `>>`).
  - Cross-word bit shifting with boundary zeroing and carry propagation.
  - Safe conversion operators to integral types and `bool`.

### 5. Trees & Graphs ([`include/tree.hpp`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/tree.hpp), [`include/graph.hpp`](file:///mnt/21e4e1ed-356a-4b18-8400-3239c575d986/CTCI/include/graph.hpp))

- **Binary Search Tree**: Node parent tracking, depth/rank measurement, and breadth-first iterative destructors preventing stack overflow during destruction of deep trees.
- **Adjacency Graph**: Generic directed/undirected graph supporting arbitrary hashable node types with edge construction and node retrieval.

---

## Solved Algorithm Chapters

| Chapter | Title | Key Problems Implemented |
| :--- | :--- | :--- |
| **I** | **Arrays & Strings** | `isUnique`, `checkPermutation`, `urlify`, `palindromePerm`, `oneAway`, `stringCompression`, `rotateMatrix` (Square & Non-Square), `zeroMatrix`, `stringRotation` |
| **II** | **Linked Lists** | `removeDups`, `kthLast`, `deleteMiddleNode`, `partition`, `sumLists`, `palindrome` (fast/slow pointers), `intersection`, `loopDetection` (Floyd's Cycle-Finding) |
| **III** | **Stacks & Queues** | `sortStack` (two-stack sort), `SetOfStacks` (capacity rollover & `popAt`), `Queue` (2-stack simulation), `AnimalShelter` ($O(1)$ dual-queue timestamp-sequenced dequeue) |
| **IV** | **Trees & Graphs** | `routeBetweenNodes` (BFS), `minimalTree` (C++23 deducing-this recursive BST), `listOfDepths`, `checkBalanced`, `validateBST`, `sucessor`, `buildOrder` (Topological Sort with in-degree tracking), `findCommonAncestor`, `checkSubtree`, `pathsWithSum` |
| **V** | **Bit Manipulation** | `insertion`, `flipBitToWin`, `nextNumber` (same bit count min/max), `conversion` (Hamming distance), `pairwiseSwap`, `Screen::drawLine` (monochrome rasterization) |
| **VI** | **Math & Logic Puzzles** | `theHeavyPill` (fractional offset scaling), `theApocalypse` (Monte Carlo gender ratio simulation), `poison` (10-strip binary test matrix) |

---

## Verification & Code Quality

### Testing & Verification
The project features **314 comprehensive unit tests** written with GoogleTest, thoroughly validating boundary conditions, move-only types, non-trivial object destruction, hash collisions, and edge cases.

```bash
[==========] Running 314 tests from 43 test suites.
[  PASSED  ] 314 tests.
```

### Code Coverage (100.00%)
Instrumented with LLVM source-based code coverage (`-fprofile-instr-generate -fcoverage-mapping`) and GCC `lcov`:

| Target / Header | Lines Cover | Branches Cover | Functions Cover | Regions Cover |
| :--- | :---: | :---: | :---: | :---: |
| `include/memory.hpp` | **100.00%** | **100.00%** | **100.00%** | **100.00%** |
| `include/vector.hpp` | **100.00%** | **100.00%** | **100.00%** | **100.00%** |
| `include/associative_containers.hpp` | **100.00%** | **100.00%** | **100.00%** | **100.00%** |
| `include/bitset.hpp` | **100.00%** | **100.00%** | **100.00%** | **100.00%** |
| `include/list.hpp` & `deque.hpp` | **100.00%** | **100.00%** | **100.00%** | **100.00%** |
| `include/tree.hpp` & `graph.hpp` | **100.00%** | **100.00%** | **100.00%** | **100.00%** |
| `src/i.cpp` through `src/vi.cpp` | **100.00%** | **100.00%** | **100.00%** | **100.00%** |
| **TOTAL** | **100.00%** (1,656/1,656) | **100.00%** (528/528) | **100.00%** (345/345) | **100.00%** (985/985) |

### Memory Safety & Valgrind
Every test runs clean under Valgrind Memcheck with zero memory leaks and zero invalid reads/writes:

```text
== Memcheck, a memory error detector ==
HEAP SUMMARY:
    in use at exit: 0 bytes in 0 blocks
  total heap usage: 9,767 allocs, 9,767 frees, 1,325,143 bytes allocated

All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 0 errors from 0 contexts
```

### Developer Tooling
- **Clang-Tidy**: Parallelized static analysis target (`ninja lint-and-format`) utilizing all CPU cores.
- **Clang-Format**: Formatted to strict LLVM coding standards with 4-space indentation and 125-column limits.
- **Git Hygiene**: 100% adherence to the Conventional Commits specification (`[feat]:`, `[refactor]:`, `[fix]:`).

---

## Build & Run Guide

### Prerequisites
- **Compiler**: Clang (>= 17) or GCC (>= 13) with full C++23 support (`-std=gnu++23`)
- **Build System**: CMake (>= 3.10) & Ninja
- **Tools** (optional): `valgrind`, `llvm-profdata`, `llvm-cov`, `lcov`, `genhtml`, `run-clang-tidy`

### 1. Configure and Build
```bash
# Clone the repository
git clone https://github.com/lucaslive974/CTCI.git
cd CTCI

# Configure with Ninja build system
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON

# Compile the library and tests
ninja -C build
```

### 2. Run Test Suite
```bash
# Execute GoogleTest suite with CTest
ctest --test-dir build --output-on-failure
```

### 3. Generate Coverage Report
```bash
# Generates textual and lcov coverage reports
ninja -C build generate-coverage-report

# (For HTML report on Clang)
llvm-cov show ./build/CTCI_TEST \
  -instr-profile=./build/coverage.profdata \
  --format=html -output-dir=./build/coverage-html
```

### 4. Run Memory Leak Analysis (Valgrind)
```bash
ninja -C build memory-leak-analyze-report
```

### 5. Automated Lint & Format
```bash
ninja -C build lint-and-format
```

---

## Author

Developed by **Lucas Lima** ([@lucaslive974](https://github.com/lucaslive974)) — Software Engineer specializing in modern C++, memory-efficient data structures, and algorithmic engineering.
