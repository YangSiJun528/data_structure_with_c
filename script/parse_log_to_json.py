import json
from datetime import datetime
import os


def parse_log_line(line):
    try:
        parts = line.split()

        timestamp_str = parts[0] + ' ' + parts[1]
        timestamp = datetime.strptime(timestamp_str, "%Y-%m-%d %H:%M:%S.%f%z")

        # 메시지의 시작 부분을 찾기 위해 적절한 인덱스를 설정합니다.
        message_index = line.index('Id: ')
        message = line[message_index:]

        id_str = message.split('Id: ')[1].split(',')[0]
        operation = message.split('Operation: ')[1].split(',')[0]
        data_size_str = message.split('Data Size: ')[1].split(',')[0]
        duration_str = message.split('Duration: ')[1].split(' ')[0]

        return {
            "Timestamp": timestamp,
            "Id": int(id_str),
            "Operation": operation,
            "DataSize": int(data_size_str),
            "Duration": "{:.6f}".format(float(duration_str))
        }
    except (IndexError, ValueError) as e:
        print(f"Error parsing line: {line}\nError: {e}")
        return None


def log_to_json(log_file_path, json_file_path):
    if not os.path.exists(log_file_path):
        print(f"File not found: {log_file_path}")
        return

    log_entries = []

    with open(log_file_path, 'r') as file:
        lines = file.readlines()
        for line in lines[1:]:  # 첫 번째 줄을 건너뛰기
            if line.strip():
                log_entry = parse_log_line(line)
                if log_entry:
                    log_entries.append(log_entry)

    with open(json_file_path, 'w') as json_file:
        json.dump(log_entries, json_file, default=str, indent=4)


LOG_DIRECTORY = "/Users/sijunyang/CLionProjects/data_structure_with_c/tests/logs/"
log_file_name = 'test.dynamic_array.2024-05-31_13-11-01'  # 매번 바꾸기
log_file_path = LOG_DIRECTORY + log_file_name + '.log'
json_file_path = LOG_DIRECTORY + log_file_name + '.json'

log_to_json(log_file_path, json_file_path)
