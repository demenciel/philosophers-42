# Dining Philosophers Problem

This repository contains a multithreaded implementation of the dining philosophers problem using the C programming language and the POSIX threads (pthreads) library.

## Problem Statement

The dining philosophers problem is a classic synchronization problem that illustrates the challenges of avoiding deadlock in a system with concurrent processes (or threads). 

The problem is defined as follows: Five silent philosophers sit at a round table with bowls of spaghetti. Forks are placed between each pair of adjacent philosophers. Each philosopher must alternately think and eat. However, a philosopher can only eat spaghetti when they have both left and right forks. Each fork can be held by only one philosopher and so a philosopher can use the fork only if it is not being used by another philosopher. After an individual philosopher finishes eating, they need to put down both forks so that the forks become available to others. A philosopher can only take the fork on their right or the one on their left as they become available and they cannot start eating before getting both forks.

The goal is to come up with a design such that no philosopher will starve, i.e., each can eventually eat.

## Implementation Details

This implementation of the dining philosophers problem uses threads to represent philosophers and mutexes to represent forks. 

## Getting Started

### Prerequisites

- GCC
- Make
- POSIX threads library (should be pre-installed on most Unix-like systems)

### Building

To build the project, navigate to the directory containing the source code and Makefile, and then type the following command:

```bash
make
```

#### Running

After building the project, you can run it with the following command:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [<number_of_times_each_philosopher_must_eat>]
```

Where:

- <number_of_philosophers>: The number of philosophers and also the number of forks.
- <time_to_die>: If a philosopher doesn’t start eating <time_to_die> milliseconds after starting his last meal or the beginning of the simulation, it dies.
- <time_to_eat>: The time it takes for a philosopher to eat. During that time he will need to keep the two forks.
- <time_to_sleep>: The time the philosopher will spend sleeping.
- <number_of_times_each_philosopher_must_eat>: If all philosophers eat at least <number_of_times_each_philosopher_must_eat> times, the simulation will stop. If not specified, the simulation will stop only if a philosopher dies.
