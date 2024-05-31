//
// Created by sijun yang on 2024. 5. 30.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "log_write_to_file.h"

char* LOG_DIRECTORY = "/Users/sijunyang/CLionProjects/data_structure_with_c/tests/logs/";

// 로그를 파일에 저장하는 함수
void save_logs_to_file(const char *subsystem) {
    FILE *fp;
    char path[1024];
    char command[256];
    char filename[512];

    // 파일 이름을 logs 디렉토리와 결합하여 생성합니다.
    snprintf(filename, sizeof(filename), "%s%s.log", LOG_DIRECTORY, subsystem);

    // 명령어 문자열을 구성합니다.
    snprintf(command, sizeof(command), "log show --predicate 'subsystem == \"%s\"' --info", subsystem);

    // 로그 파일을 생성하고 쓰기 모드로 엽니다.
    FILE *log_file = fopen(filename, "w");
    if (log_file == NULL) {
        printf("Failed to open file for writing: %s\n", filename);
        exit(1);
    }

    // 구성된 명령어를 사용하여 로그를 읽습니다.
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        fclose(log_file);
        exit(1);
    }

    // 명령어의 출력을 읽고 파일에 씁니다.
    while (fgets(path, sizeof(path), fp) != NULL) {
        fputs(path, log_file);
    }

    // 파일 포인터를 닫습니다.
    pclose(fp);
    fclose(log_file);
}

int save_log(char* subsystem) {

    // 로그를 파일에 저장합니다.
    save_logs_to_file(subsystem);

    printf("Logs have been saved to %s\n", subsystem);
    return 0;
}
