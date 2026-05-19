*This project has been created as part of the 42 curriculum by jbordeli*

# Codexion

> Concurrency simulation project developed as part of the 42 curriculum.

---

# 📌 Description

**Codexion** is a multithreaded concurrency simulation written in C.  
The project models a shared development workspace where multiple coders compete for a limited number of USB dongles in order to compile their code.

Each coder repeatedly performs the following cycle:

- compile
- debug
- refactor

The main challenge of the project is to synchronize POSIX threads while avoiding:

- deadlocks
- starvation
- data races
- coder burnout

The project also implements two scheduling strategies for resource management:

- **FIFO** (*First In First Out*)
- **EDF** (*Earliest Deadline First*)

The entire architecture is built using POSIX threads (`pthread`), mutexes, and a custom priority queue implementation.

---

# ⚙️ Compilation

The project is compiled using the provided `Makefile`.

```bash
make
```

Compilation flags:

```bash
-Wall -Wextra -Werror -pthread
```

---

# ▶️ Usage

```bash
./codexion number_of_coders \
            time_to_burnout \
            time_to_compile \
            time_to_debug \
            time_to_refactor \
            number_of_compiles_required \
            dongle_cooldown \
            scheduler
```

---

# 📥 Arguments

| Argument | Description |
|---|---|
| `number_of_coders` | total number of coders |
| `time_to_burnout` | maximum time before a coder burns out |
| `time_to_compile` | compilation duration |
| `time_to_debug` | debugging duration |
| `time_to_refactor` | refactoring duration |
| `number_of_compiles_required` | required number of compilations |
| `dongle_cooldown` | cooldown time after releasing a dongle |
| `scheduler` | scheduling policy (`fifo` or `edf`) |

---

# ✅ Constraints

- `number_of_coders > 0`
- `number_of_compiles_required > 0`
- all timing values must be `>= 0`
- `scheduler` must be:
  - `fifo`
  - `edf`

Argument validation is fully handled during parsing.

---

# 🧠 Project Architecture

## Main Structures

### `t_data`

Stores all global simulation data:

- simulation parameters
- mutexes
- coders array
- dongles array
- simulation state

---

### `t_coder`

Represents a coder thread:

- unique identifier
- compilation counter
- last compilation timestamp
- references to both dongles

---

### `t_dongle`

Represents a shared resource:

- dedicated mutex
- busy state
- cooldown tracking
- request queue

---

### `t_request`

Represents a scheduler request:

- coder reference
- priority
- arrival order

---

# 🔄 Coder Lifecycle

Each thread continuously performs the following routine:

1. take dongles
2. compile
3. debug
4. refactor
5. increment compilation count

The lifecycle is split into dedicated routines:

- `compile_routine`
- `debug_routine`
- `refactor_routine`

---

# 🧵 Thread Management

## Thread Creation

Each coder owns a dedicated POSIX thread created dynamically using:

```c
pthread_create(...)
```

An additional monitor thread supervises the global simulation state.

---

# 🔒 Synchronization

## Mutex Usage

The project uses several mutexes:

| Mutex | Purpose |
|---|---|
| `print_mutex` | protects terminal output |
| `state_mutex` | protects shared simulation state |
| `dongle->mutex` | protects dongle access |

---

# 🛡️ Concurrency Safety

## ✅ Deadlock Prevention

Dongles are always locked in a strict global order:

```c
if (coder->left < coder->right)
```

This resource hierarchy prevents circular waits and eliminates deadlocks.

---

## ✅ Starvation Prevention

A custom scheduler manages dongle requests through a priority queue.

Two scheduling strategies are available:

### FIFO

Coders are served according to arrival order.

### EDF (Earliest Deadline First)

The coder closest to burnout receives the highest priority.

EDF priority formula:

```c
priority = last_compile_start + time_to_burnout;
```

When priorities are identical, arrival order is used as a deterministic tie-breaker.

---

# 📚 Custom Scheduler

The scheduler system is built around:

- request queues
- sorted insertions
- dynamic priorities

Main scheduler functions:

| Function | Role |
|---|---|
| `request_dongles` | request resources |
| `release_dongles` | release resources |
| `enqueue_fifo` | FIFO insertion |
| `enqueue_edf` | EDF insertion |

---

# ⏱️ Burnout Detection

A dedicated monitor thread continuously checks:

- whether a coder exceeded `time_to_burnout`
- whether all coders completed their required compilations

Checks are performed every 1 millisecond:

```c
usleep(1000);
```

This guarantees precise burnout detection within the expected tolerance window.

---

# 🧩 Dongle Cooldown System

After being released, each dongle enters a cooldown state:

```c
cooldown_until
```

The scheduler prevents any coder from reusing the dongle before the cooldown expires.

---

# 🗂️ File Organization

| File | Purpose |
|---|---|
| `main.c` | program entry point |
| `parsing.c` | argument parsing and validation |
| `init.c` | memory and mutex initialization |
| `threads.c` | thread management |
| `routines.c` | coder actions |
| `scheduler.c` | resource reservation/release |
| `utils_scheduler.c` | EDF/FIFO scheduling logic |
| `queue_scheduler.c` | queue management |
| `monitor.c` | simulation monitoring |
| `utils.c` | utility functions |
| `codexion.h` | structures and prototypes |

---

# 🧪 Example

```bash
./codexion 5 800 200 150 150 5 100 edf
```

Simulation with:

- 5 coders
- burnout after 800ms
- compilation time of 200ms
- EDF scheduling
- 100ms dongle cooldown

---

# 📖 Concepts Covered

This project explores:

- POSIX threads
- mutex synchronization
- concurrent programming
- race condition prevention
- scheduling algorithms
- custom data structures
- precise timing management
- real-time simulation

---

# 📚 Resources

- POSIX Threads documentation
- `pthread` manual pages
- `gettimeofday` documentation
- Linux synchronization primitives documentation

---

# 🤖 AI Usage

AI tools were used as technical assistance for:

- discussing scheduler architecture
- validating deadlock prevention strategies
- clarifying POSIX mutex behavior
- improving project modularization

All implementation, debugging, and final design decisions were made manually.
