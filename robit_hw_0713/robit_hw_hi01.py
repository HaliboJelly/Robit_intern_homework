def compress(text):
    # 연속된 같은 문자를 "문자+개수"로 압축 (런렝스 인코딩)
    count = 1
    result = ""
    for i in range(len(text) - 1):
        if text[i + 1] == text[i]:
            count += 1
        else:
            result += text[i] + str(count)
            count = 1
    result += text[-1] + str(count)  # 마지막 문자 처리

    # 압축했는데 오히려 길어지면 원본 그대로 반환
    if len(result) >= len(text):
        return text
    return result

def is_valid_code(code):
    # "문자+숫자" 패턴이 반복되는 유효한 압축 코드인지 검사
    if code == "":
        return False
    i = 0
    while i < len(code):
        if not code[i].isalpha():          # 문자로 시작해야 함
            return False
        i += 1
        if i >= len(code) or not code[i].isdigit():  # 뒤에 숫자 있어야 함
            return False
        num_start = i
        while i < len(code) and code[i].isdigit():   # 숫자 자릿수 이어붙이기
            i += 1
        count = int(code[num_start:i])
        if count < 1:                      # 개수는 1 이상이어야 함
            return False
    return True


def decompress(code):
    if not is_valid_code(code):
        return "ERROR"
    result = ""
    i = 0
    while i < len(code):
        char = code[i]
        i += 1
        num_start = i
        while i < len(code) and code[i].isdigit():
            i += 1
        count = int(code[num_start:i])
        result += char * count  # 문자를 개수만큼 반복해서 복원
    return result

print(compress("aaabbccccd"))
print(decompress("a3b2c4d1"))
print(decompress("a12b3"))
print(decompress("a0"))
print(decompress("3a"))
print(compress("abcde"))