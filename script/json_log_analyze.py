import json
import pandas as pd
import matplotlib.pyplot as plt
from dateutil import parser

def read_json_log(json_file_path):
    with open(json_file_path, 'r') as json_file:
        log_entries = json.load(json_file)

    # Timestamp를 datetime 타입으로 변환
    for entry in log_entries:
        entry["Timestamp"] = parser.parse(entry["Timestamp"])

    return log_entries

def plot_percentiles(log_entries):
    df = pd.DataFrame(log_entries)
    operations = df['Operation'].unique()
    percentiles = [1, 10, 50, 90, 99]

    # 각 연산에 대한 백분위 수 계산
    percentile_data = []
    for operation in operations:
        subset = df[df['Operation'] == operation]['Duration'].astype(float)
        percentile_values = [subset.quantile(p/100) for p in percentiles]
        percentile_data.append([operation] + percentile_values)

    # DataFrame 생성
    percentile_df = pd.DataFrame(percentile_data, columns=['Operation'] + [f'P{p}' for p in percentiles])
    percentile_df.set_index('Operation', inplace=True)

    # 막대 그래프 그리기
    ax = percentile_df.plot(kind='bar', figsize=(14, 8), width=0.75)

    plt.xlabel('Operation')
    plt.ylabel('Duration (seconds)')
    plt.title('Operation Duration Percentiles')
    plt.xticks(rotation=45, ha='right')
    plt.legend(title='Percentile')
    plt.grid(axis='y', linestyle='--', alpha=0.7)

    # y축 범위를 전체 데이터를 잘 볼 수 있도록 조정, 최소값을 0으로 설정
    plt.ylim(bottom=0)

    plt.tight_layout()
    plt.show()

# 파일 경로 설정
LOG_DIRECTORY = "/Users/sijunyang/CLionProjects/data_structure_with_c/tests/logs/"
log_file_name = 'test.dynamic_array.2024-05-31_13-11-01'  # 매번 바꾸기
json_file_path = LOG_DIRECTORY + log_file_name + '.json'

# JSON 로그 파일 읽기
log_entries = read_json_log(json_file_path)

# 각 연산별로 시간 순으로 시각화
plot_percentiles(log_entries)
