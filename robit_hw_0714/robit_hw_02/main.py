"""
main.py
-------
requests 라이브러리를 활용한 국제우주정거장(ISS) 실시간 위치 추적기.
(Real-Time ISS Location Tracker utilizing the requests library.)

기능 (Features):
1. Open Notify API에서 ISS의 현재 위경도(latitude, longitude)를 가져온다.
   (Fetches the current latitude and longitude of the ISS from the Open Notify API.)
2. BigDataCloud의 무료 역지오코딩(reverse geocoding) API로 그 위경도가
   어느 나라/바다 근처인지 실제 지명으로 변환한다.
   (Converts the latitude and longitude into an actual place name using the BigDataCloud free reverse geocoding API.)
3. Open Notify의 astros.json API로 현재 우주에 떠 있는 사람이 몇 명이고
   누가 어느 우주선(ISS 등)에 타고 있는지 가져온다.
   (Fetches the number of people currently in space and their respective spacecrafts using the Open Notify astros.json API.)
4. 위 정보를 일정 간격(기본 5초)으로 반복 조회하여 터미널에 출력한다.
   (Repeatedly tracks and prints the above information to the terminal at a set interval, default 5 seconds.)

외부 라이브러리 (External Library): requests (버전은 requirements.txt 참고 / Refer to requirements.txt for version)
사용 API (모두 인증키 불필요, 무료 공개 API) / Used APIs (All free, no API keys required):
- http://api.open-notify.org/iss-now.json       : ISS 현재 위치 (Current ISS Location)
- http://api.open-notify.org/astros.json        : 현재 우주 체류 인원 (People currently in space)
- https://api.bigdatacloud.net/data/reverse-geocode-client : 위경도 -> 지명 변환 (Latitude/Longitude -> Place name conversion)
"""

import time
import sys
from datetime import datetime, timezone

import requests

ISS_NOW_URL = "http://api.open-notify.org/iss-now.json"
ASTROS_URL = "http://api.open-notify.org/astros.json"
REVERSE_GEOCODE_URL = "https://api.bigdatacloud.net/data/reverse-geocode-client"

REQUEST_TIMEOUT = 10  # 초 (seconds)


def get_iss_location():
    """ISS의 현재 위경도와 타임스탬프를 반환한다.
    (Returns the current latitude, longitude, and timestamp of the ISS.)"""
    response = requests.get(ISS_NOW_URL, timeout=REQUEST_TIMEOUT)
    response.raise_for_status()
    data = response.json()

    position = data["iss_position"]
    latitude = float(position["latitude"])
    longitude = float(position["longitude"])
    timestamp = data["timestamp"]

    return latitude, longitude, timestamp


def get_location_name(latitude, longitude):
    """위경도를 사람이 읽을 수 있는 지명으로 변환한다.
    (Converts latitude and longitude into a human-readable place name.)

    ISS는 대부분 바다 위를 지나가기 때문에, 육지가 아니면
    '근처 국가 정보 없음(대양 상공)'처럼 처리한다.
    (Since the ISS mostly orbits over oceans, if it's not over land,
    it is handled as 'No land detected (Over the Ocean)'.)
    """
    params = {
        "latitude": latitude,
        "longitude": longitude,
        "localityLanguage": "ko",
    }
    try:
        response = requests.get(REVERSE_GEOCODE_URL, params=params, timeout=REQUEST_TIMEOUT)
        response.raise_for_status()
        data = response.json()
    except requests.RequestException:
        return "지명 조회 실패 (네트워크 오류) / Location lookup failed (Network error)"

    country = data.get("countryName")
    locality = data.get("locality") or data.get("city")

    if not country:
        return "육지 없음 (대양 또는 극지방 상공) / No land detected (Over the Ocean or Polar Regions)"

    if locality:
        return f"{country} / {locality} 부근 (Near {locality}, {country})"
    return f"{country} 부근 (Near {country})"


def get_astronauts_in_space():
    """현재 우주에 있는 사람 수와 이름, 탑승 우주선 목록을 반환한다.
    (Returns the number of people currently in space, their names, and their spacecrafts.)"""
    response = requests.get(ASTROS_URL, timeout=REQUEST_TIMEOUT)
    response.raise_for_status()
    data = response.json()

    number = data.get("number", 0)
    people = data.get("people", [])
    return number, people


def format_timestamp(unix_timestamp):
    """유닉스 타임스탬프를 사람이 읽기 좋은 UTC 문자열로 변환한다.
    (Converts a Unix timestamp into a human-readable UTC string.)"""
    dt = datetime.fromtimestamp(unix_timestamp, tz=timezone.utc)
    return dt.strftime("%Y-%m-%d %H:%M:%S UTC")


def print_header():
    print("=" * 70)
    print(" 🛰️  국제우주정거장(ISS) 실시간 위치 추적기 / Real-Time ISS Tracker")
    print("=" * 70)


def print_astronauts(number, people):
    print(f"\n현재 우주에 있는 사람: 총 {number}명 / People currently in space: Total {number}")
    for person in people:
        name = person.get("name", "이름 없음 / Unknown")
        craft = person.get("craft", "탑승선 정보 없음 / Unknown craft")
        print(f"  - {name} (탑승/Craft: {craft})")


def track_once():
    """ISS 위치와 우주인 정보를 1회 조회해서 출력한다.
    (Tracks and prints the ISS location and astronaut information once.)"""
    latitude, longitude, timestamp = get_iss_location()
    location_name = get_location_name(latitude, longitude)

    print(f"\n[{format_timestamp(timestamp)}]")
    print(f"  위도(latitude)  : {latitude:.4f}")
    print(f"  경도(longitude) : {longitude:.4f}")
    print(f"  현재 위치(Loc)  : {location_name}")


def main():
    print_header()

    # 실행 시 1회, 현재 우주인 정보 조회
    # (Fetch astronaut info once upon execution)
    try:
        number, people = get_astronauts_in_space()
        print_astronauts(number, people)
    except requests.RequestException as error:
        print(f"\n[경고/Warning] 우주인 정보를 가져오지 못했습니다(Failed to fetch astronaut info): {error}")

    # 반복 조회 횟수와 간격 설정 (원하는 대로 조절 가능)
    # (Configure iteration count and interval)
    iterations = 5
    interval_seconds = 5

    print(f"\n{interval_seconds}초 간격으로 ISS 위치를 {iterations}회 추적합니다. "
          f"(Ctrl+C로 중단 가능)")
    print(f"(Tracking ISS location {iterations} times at {interval_seconds}-second intervals. Press Ctrl+C to stop.)\n")

    try:
        for i in range(1, iterations + 1):
            print(f"--- {i}/{iterations}번째 조회 (Tracking {i}/{iterations}) ---")
            try:
                track_once()
            except requests.RequestException as error:
                print(f"[오류/Error] ISS 위치 조회 실패(Failed to track ISS): {error}")

            if i < iterations:
                time.sleep(interval_seconds)
    except KeyboardInterrupt:
        print("\n\n사용자에 의해 추적이 중단되었습니다. (Tracking stopped by the user.)")
        sys.exit(0)

    print("\n추적을 종료합니다. (Terminating tracker.) 🛰️")


if __name__ == "__main__":
    main()