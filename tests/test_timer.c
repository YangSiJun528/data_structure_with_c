#include <stdio.h>
#include <os/log.h>
#include "timer.h"


// 인자와 반환 값이 없는 테스트 함수
void test_function_1() {
    for (volatile int i = 0; i < 1000000; ++i); // 시간 소모용 루프
}

// 인자는 없고 반환 값이 있는 테스트 함수
int test_function_2() {
    int sum = 0;
    for (volatile int i = 0; i < 1000000; ++i) {
        sum += i;
    }
    return sum;
}

// 인자가 있고 반환 값이 없는 테스트 함수
void test_function_3(int x) {
    for (volatile int i = 0; i < x; ++i); // 시간 소모용 루프
}

// 인자가 있고 반환 값이 있는 테스트 함수
int test_function_4(int x, int y) {
    int sum = 0;
    for (volatile int i = 0; i < x * y; ++i) {
        sum += i;
    }
    return sum;
}

// 다양한 인자 타입을 가진 테스트 함수
double test_function_5(double a, int b, const char *msg) {
    double sum = 0.0;
    for (volatile int i = 0; i < b; ++i) {
        sum += a;
    }
    printf("%s \n", msg);
    return sum;
}

int main() {
    // 전역 로거 초기화
    int result_int;
    double result_double;

    os_log_t logger = os_log_create("test.timer.001", "default");
    // 로그 읽는 명령어: log show --predicate 'subsystem == "test.timer.001"' --info

    init_logger(&logger);

    // 인자와 반환 값이 없는 함수 테스트
    MEASURE_TIME_NOARGS_VOID("test_function_1", 0, test_function_1);

    // 인자는 없고 반환 값이 있는 함수 테스트
    MEASURE_TIME_NOARGS_RETURN("test_function_2", 0, result_int, test_function_2);
    printf("test_function_2 결과: %d \n", result_int);

    // 인자가 있고 반환 값이 없는 함수 테스트
    MEASURE_TIME_ARGS_VOID("test_function_3", 1000000, test_function_3, 1000000);

    // 인자가 있고 반환 값이 있는 함수 테스트
    MEASURE_TIME_ARGS_RETURN("test_function_4", 1000 * 1000, result_int, test_function_4, 1000, 1000);
    printf("test_function_4 결과: %d \n", result_int);

    // 다양한 인자 타입을 가진 함수 테스트
    MEASURE_TIME_ARGS_RETURN("test_function_5", 1000000, result_double, test_function_5, 3.14, 1000000, "메시지 출력");
    printf("test_function_5 결과: %f \n", result_double);

    return 0;
}
