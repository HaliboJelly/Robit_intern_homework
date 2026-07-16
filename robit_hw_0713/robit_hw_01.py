# 로봇 상태 데이터 (이름, 배터리, 위치, 장애물까지 거리)
robot_status = [
{"name": "mobilebot", "battery": 82, "position": (1.2, 0.5), "distance": 0.8},
{"name": "drone", "battery": 18, "position": (0.3, 1.5), "distance": 0.4},
{"name": "manipulator", "battery": 45, "position": (2.0, 1.0), "distance": 1.2},
]

class RobotStatus:
    def __init__(self, robot_status):
        self.robot_status = robot_status  # 로봇 정보 리스트 저장

    def robot_name(self, i):
        return self.robot_status[i]["name"]  # i번째 로봇 이름

    def robot_battery(self, i):
        # 배터리 잔량에 따라 상태 문자열 반환
        battery_level = self.robot_status[i]["battery"]
        if battery_level < 20:
            return "충전필요"
        elif 20 <= battery_level < 60:
            return "배터리 주의"
        elif battery_level >= 60:
            return "배터리 충분"

    def robot_position(self, i):
        # (x, y) 좌표 반환
        pos = self.robot_status[i]["position"]
        x = pos[0]
        y = pos[1]
        return (x, y)

    def robot_distance(self, i):
        # 장애물까지 거리 기준으로 전진 가능 여부 판단
        distance = self.robot_status[i]["distance"]
        if distance < 0.5:
            return "장애물 감지"
        elif 0.5 <= distance:
            return "전진 가능"
    

    def print_all(self):
            # 모든 로봇 상태를 순서대로 출력
            for i in range(len(self.robot_status)):
                print(f"[{self.robot_name(i)}]")
                print(f"배터리: {self.robot_battery(i)}")
                print(f"위치: x={self.robot_position(i)[0]}, y={self.robot_position(i)[1]}")
                print(f"상태: {self.robot_distance(i)}")
                print("-----------------------------")


rs = RobotStatus(robot_status)  # 객체 생성
rs.print_all()  # 전체 출력 실행