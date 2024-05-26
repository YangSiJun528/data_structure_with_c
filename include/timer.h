//
// Created by sijun yang on 2024. 5. 26.
//

#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <os/log.h>

#define START_TIMER(start) do { \
    (start) = clock(); \
} while (0)

#define END_TIMER(start, elapsed) do { \
    clock_t end = clock(); \
    (elapsed) = ((double) (end - (start))) / CLOCKS_PER_SEC; \
} while (0)

#define MEASURE_TIME_NOARGS_VOID(operation_name, data_size, func) do { \
    clock_t start; \
    double elapsed; \
    START_TIMER(start); \
    (func)(); \
    END_TIMER(start, elapsed); \
    log_operation(operation_name, data_size, elapsed); \
} while (0)

#define MEASURE_TIME_NOARGS_RETURN(operation_name, data_size, result, func) do { \
    clock_t start; \
    double elapsed; \
    START_TIMER(start); \
    (result) = (func)(); \
    END_TIMER(start, elapsed); \
    log_operation(operation_name, data_size, elapsed); \
} while (0)

#define MEASURE_TIME_ARGS_VOID(operation_name, data_size, func, ...) do { \
    clock_t start; \
    double elapsed; \
    START_TIMER(start); \
    (func)(__VA_ARGS__); \
    END_TIMER(start, elapsed); \
    log_operation(operation_name, data_size, elapsed); \
} while (0)

#define MEASURE_TIME_ARGS_RETURN(operation_name, data_size, result, func, ...) do { \
    clock_t start; \
    double elapsed; \
    START_TIMER(start); \
    (result) = (func)(__VA_ARGS__); \
    END_TIMER(start, elapsed); \
    log_operation(operation_name, data_size, elapsed); \
} while (0)

void log_operation(const char* operation_name, int data_size, double duration);

void init_logger(const os_log_t* logger);

#endif // TIMER_H
