"""
도서 대출 관리 시스템 (개선판)
명령어: add / borrow / return / status / user / list / exit  (대소문자 구별 없음)
책 이름도 대소문자 구별 없이 동일 책으로 취급
"""

books = {}       # 책이름(소문자) -> 총 등록 수량
book_names = {}  # 책이름(소문자) -> 화면에 표시할 원래 이름(최초 등록 시 표기 기준)
borrowed = {}    # 책이름(소문자) -> 현재 대출중인 사용자 집합(set)


def add_book(name, qty):
    """책 등록. 대소문자 구분 없이 이미 있으면 수량 추가"""
    key = name.lower()
    if key not in book_names:
        book_names[key] = name  # 최초로 입력된 표기를 화면 출력용으로 저장

    books[key] = books.get(key, 0) + qty
    return f"{book_names[key]} 등록 완료 (총 수량: {books[key]})"


def available_qty(key):
    """대출 가능한 남은 수량 계산 (key는 소문자 기준)"""
    total = books.get(key, 0)
    lent_out = len(borrowed.get(key, set()))
    return total - lent_out


def borrow_book(user, name):
    # 책 존재 -> 중복 대출 -> 재고 순으로 검사 (key는 소문자로 통일)
    key = name.lower()
    if key not in books:
        return f"ERROR: '{name}' 책이 존재하지 않습니다"

    display = book_names[key]
    if user in borrowed.get(key, set()):
        return f"ERROR: {user}님은 이미 '{display}'을(를) 대출 중입니다"
    if available_qty(key) <= 0:
        return f"ERROR: '{display}'의 남은 수량이 없습니다"

    borrowed.setdefault(key, set()).add(user)
    return f"{user}님이 '{display}'을(를) 대출했습니다"


def return_book(user, name):
    key = name.lower()
    if key not in books or user not in borrowed.get(key, set()):
        return f"ERROR: {user}님은 '{name}'을(를) 대출 중이 아닙니다"

    display = book_names[key]
    borrowed[key].remove(user)
    return f"{user}님이 '{display}'을(를) 반납했습니다"


def status_book(name):
    key = name.lower()
    if key not in books:
        return f"ERROR: '{name}' 책이 존재하지 않습니다"
    return f"'{book_names[key]}' 남은 수량: {available_qty(key)}"


def user_status(user):
    # 해당 유저가 빌린 모든 책의 원래 표기명 나열
    loans = [book_names[key] for key, users in borrowed.items() if user in users]
    return ", ".join(loans) if loans else "EMPTY"


def list_books():
    return ", ".join(book_names.values()) if books else "EMPTY"


def is_nonneg_int(s):
    return s.isdigit()  # 음수 부호가 없으므로 isdigit()이면 0 이상의 정수


def process_command(line):
    # 입력 한 줄을 파싱해서 알맞은 함수 호출, 형식 오류는 여기서 검증
    tokens = line.split()
    if not tokens:
        return None

    cmd, args = tokens[0].lower(), tokens[1:]  # 명령어 대소문자 구별 없이 처리

    if cmd == "add":
        if len(args) != 2 or not is_nonneg_int(args[1]):
            return "ERROR: 잘못된 명령어 형식입니다 (add 책이름 수량)"
        return add_book(args[0], int(args[1]))

    elif cmd == "borrow":
        if len(args) != 2:
            return "ERROR: 잘못된 명령어 형식입니다 (borrow 사용자 책이름)"
        return borrow_book(args[0], args[1])

    elif cmd == "return":
        if len(args) != 2:
            return "ERROR: 잘못된 명령어 형식입니다 (return 사용자 책이름)"
        return return_book(args[0], args[1])

    elif cmd == "status":
        if len(args) != 1:
            return "ERROR: 잘못된 명령어 형식입니다 (status 책이름)"
        return status_book(args[0])

    elif cmd == "user":
        if len(args) != 1:
            return "ERROR: 잘못된 명령어 형식입니다 (user 사용자)"
        return user_status(args[0])

    elif cmd == "list":
        if len(args) != 0:
            return "ERROR: 잘못된 명령어 형식입니다 (list)"
        return list_books()

    elif cmd == "exit":
        return "EXIT"

    else:
        return f"ERROR: 알 수 없는 명령어입니다 ({tokens[0]})"


def main():
    # 한 줄씩 입력받아 처리, exit이면 종료
    while True:
        try:
            line = input().strip()
        except EOFError:
            break

        if not line:
            continue

        result = process_command(line)
        if result == "EXIT":
            break
        if result is not None:
            print(result)


if __name__ == "__main__":
    main()