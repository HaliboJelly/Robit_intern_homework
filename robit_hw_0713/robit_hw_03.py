fruits = []   # 과일 목록 저장용 리스트

while True:
    commands = input()
    if commands.strip() == "exit":
        break

    parts = commands.split()
    command = parts[0]     # 명령어
    args = parts[1:]       # 명령어 인자들

    try:
        if command == "append":
            fruits.append(args[0])  # 끝에 추가

        elif command == "insert":
            idx, val = int(args[0]), args[1]
            if 0 <= idx <= len(fruits):
                fruits.insert(idx, val)  # 지정 인덱스에 삽입
            else:
                print("인덱스 범위를 벗어났습니다.")

        elif command == "remove":
            if args[0] in fruits:
                fruits.remove(args[0])  # 값으로 삭제
            else:
                print(f"{args[0]}은(는) 리스트에 없습니다.")

        elif command == "pop":
            if len(fruits) == 0:
                print("리스트가 비어있습니다.")
            elif args:
                idx = int(args[0])
                if 0 <= idx < len(fruits):
                    fruits.pop(idx)  # 지정 인덱스 삭제
                else:
                    print("인덱스 범위를 벗어났습니다.")
            else:
                fruits.pop()  # 인자 없으면 마지막 요소 삭제

        elif command == "len":
            print(len(fruits))

        elif command == "print":
            print(fruits)

        elif command == "clear":
            fruits.clear()

        else:
            print("알 수 없는 명령어입니다.")

    except (IndexError, ValueError):
        # 인자 개수 부족(IndexError)이나 숫자 변환 실패(ValueError) 처리
        print("명령어 형식이 올바르지 않습니다.")