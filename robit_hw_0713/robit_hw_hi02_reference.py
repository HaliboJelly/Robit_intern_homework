"""
도서 대출 관리 시스템
명령어: add / borrow / return / status / user / list / Exit
"""

books = {}      # 책이름 -> 등록된 총 수량 (dict는 등록 순서 유지)
borrowed = {}   # 책이름 -> 현재 대출중인 사용자 집합(set)


def add_book(name, qty):
    """책 등록. 이미 있으면 수량 추가"""
    books[name] = books.get(name, 0) + qty
    return f"{name} 등록 완료 (총 수량: {books[name]})"


def available_qty(name):
    """대출 가능한 남은 수량 계산"""
    total = books.get(name, 0)
    lent_out = len(borrowed.get(name, set()))
    return total - lent_out


def borrow_book(user, name):
    # 책 존재 -> 중복 대출 -> 재고 순으로 검사
    if name not in books:
        return f"ERROR: '{name}' 책이 존재하지 않습니다"
    if user in borrowed.get(name, set()):
        return f"ERROR: {user}님은 이미 '{name}'을(를) 대출 중입니다"
    if available_qty(name) <= 0:
        return f"ERROR: '{name}'의 남은 수량이 없습니다"

    borrowed.setdefault(name, set()).add(user)
    return f"{user}님이 '{name}'을(를) 대출했습니다"


def return_book(user, name):
    # 책이 없거나 해당 유저가 빌린 적 없으면 에러
    if name not in books or user not in borrowed.get(name, set()):
        return f"ERROR: {user}님은 '{name}'을(를) 대출 중이 아닙니다"

    borrowed[name].remove(user)
    return f"{user}님이 '{name}'을(를) 반납했습니다"


def status_book(name):
    if name not in books:
        return f"ERROR: '{name}' 책이 존재하지 않습니다"
    return f"'{name}' 남은 수량: {available_qty(name)}"


def user_status(user):
    # 해당 유저가 빌린 모든 책 이름 나열
    loans = [name for name, users in borrowed.items() if user in users]
    return ", ".join(loans) if loans else "EMPTY"


def list_books():
    return ", ".join(books.keys()) if books else "EMPTY"


def is_nonneg_int(s):
    return s.isdigit()  # 음수 부호가 없으므로 isdigit()이면 0 이상의 정수


def process_command(line):
    # 입력 한 줄을 파싱해서 알맞은 함수 호출, 형식 오류는 여기서 검증
    tokens = line.split()
    if not tokens:
        return None

    cmd, args = tokens[0], tokens[1:]

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

    elif cmd == "Exit":
        return "EXIT"

    else:
        return f"ERROR: 알 수 없는 명령어입니다 ({cmd})"


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