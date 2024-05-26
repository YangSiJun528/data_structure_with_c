# 테스트 파일 추가
add_executable(test_timer_file test_timer.c)

# src 디렉토리의 타겟 링크
target_link_libraries(test_timer_file data_structure_with_c_lib)

# 테스트 추가
add_test(NAME test_timer COMMAND test_timer_file)