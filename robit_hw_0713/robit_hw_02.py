def add_log(robot_name, battery, logs=None):
    log = robot_name + " battery: " + str(battery) #TypeError 정수형과 문자형을 + 로 합쳐서 문제 -> str()로 battery를 문자형으로 변환
    
    if logs is None: #logs=[] 이면 함수 정의 시 리스트가 정의 시점에 한 번만 초기화 되고 이후 재생성이 아닌 같은 리스트 계속 참조(*리스트는 mutable 자료형이라 append 시 그 객체 자체가 직접 변형), 따라서 로그가 누적되는 문제 발생. 해결 방법으로 logs=None으로 바꾸어 새로운 리스트를 생성하도록 함.
        logs = []

    logs.append(log)
    return logs

print(add_log("frontbot", 80))
print(add_log("rearbot", 50))
print(add_log("armbot", 20))

