# 테스트 파일 추가
add_executable(dummy_test_file test_dummy.c)

# 테스트 추가
add_test(NAME dummy_test_name COMMAND dummy_test_file)