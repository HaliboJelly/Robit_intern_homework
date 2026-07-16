import csv
import json
import numpy as np

try:
    with open("students.csv", "r", encoding="utf-8") as file, \
         open("clean_students.csv", "w", encoding="utf-8", newline="") as clean_file:
         
        reader = csv.reader(file)
        writer = csv.writer(clean_file)
        
        header = next(reader)  # header row 스킵
        writer.writerow(header) # clean_file header 적기
        
        for row in reader:  # 열만큼 반복
            name = row[0]
            try:    # 점수를 int로 변환 시도 하기
                score = int(row[1])
            except ValueError:  # 값오류시 에러메세지 출력 후 컨틴유
                print(f"Invalid score format for {name}: {row[1]}")
                continue

            if score < 0 or score > 100:    #지정된 범위 밖으로 가면 에러메세지 출력 후 컨틴유
                print(f"Invalid score for {name}: {score}")
                continue
            
            print(name, score)
            writer.writerow(row)    # clean_file에 적기 반복

    scores_list =[]
    with open("clean_students.csv", "r", encoding="utf-8") as clean_file_read:
        clean_reader = csv.reader(clean_file_read)
        header = next(clean_reader)
        for row in clean_reader:
            scores_list.append(int(row[1]))
    scores_arr = np.array(scores_list)

    average_score = float(np.mean(scores_arr))  # 평균 점수
    total_count = int(len(scores_arr))         # 총 인원수
    max_score = int(np.max(scores_arr))        # 최고 점수
    
    data = {
        "total_students": total_count,
        "average_score": round(average_score, 2),  # 소수점 둘째 자리까지 반올림
        "max_score": max_score
    }

    print("NumPy로 계산된 요약 데이터:", data)

    with open("summary.json", "w", encoding="utf-8") as summary_file:
        json.dump(data, summary_file,ensure_ascii=False, indent=2)

            

    






except FileNotFoundError:   #file을 찾지 못 했을 경우
    print("File not found")