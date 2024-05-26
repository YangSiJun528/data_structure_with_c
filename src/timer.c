//
// Created by sijun yang on 2024. 5. 26.
//

#include <assert.h>
#include <os/log.h>
#include "timer.h"

os_log_t LOGGER = NULL;

void init_logger(const os_log_t* logger) {
    LOGGER = *logger;
}

void log_operation(const char* operation_name, int data_size, double duration) {
    assert(LOGGER != NULL);
    os_log(LOGGER, "Operation: %s, Data Size: %d, Duration: %.8f seconds", operation_name, data_size, duration);
}
