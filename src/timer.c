//
// Created by sijun yang on 2024. 5. 26.
//

#include <assert.h>
#include <os/log.h>
#include "timer.h"

os_log_t LOGGER = NULL;
unsigned long long id = 0;

void init_logger(const os_log_t* logger) {
    LOGGER = *logger;
}

void log_operation(const char* operation_name, int data_size, double duration) {
    assert(LOGGER != NULL);
    id++;
    os_log(LOGGER, "Id: %llu, Operation: %s, Data Size: %d, Duration: %.8f seconds", id, operation_name, data_size, duration);
}
