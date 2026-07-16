# ISS 실시간 위치 추적기

`requests` 라이브러리를 사용해서 국제우주정거장(ISS, International Space Station)의
현재 위치와 현재 우주에 떠 있는 사람 수를 실시간으로 조회하는 프로그램입니다.

## 사용 라이브러리

- **requests** `2.33.1`
  - 파이썬에서 HTTP 요청(GET/POST 등)을 아주 간단한 문법으로 보낼 수 있게 해주는
    라이브러리입니다. `urllib` 표준 라이브러리보다 훨씬 직관적이라 실무에서도
    가장 많이 쓰이는 HTTP 클라이언트 라이브러리 중 하나입니다.
  - 이 프로젝트에서는 외부 REST API 3개를 호출하는 데 사용했습니다.

### requests 라이브러리에 대한 이해

`requests.get(url, params=..., timeout=...)` 한 줄이면 서버에 GET 요청을 보내고,
`response.json()`으로 응답 바디를 파이썬 딕셔너리로 바로 파싱할 수 있습니다.
내부적으로는 소켓 연결, TCP 핸드셰이크, HTTP 헤더 구성, 인코딩 처리 등을
모두 대신 처리해주기 때문에, 개발자는 "어떤 데이터를 요청할지"에만 집중하면 됩니다.
`response.raise_for_status()`를 호출하면 4xx/5xx 에러 응답일 때 자동으로 예외를
발생시켜 에러 처리를 깔끔하게 할 수 있습니다.

## 실행 방법

```bash
pip install -r requirements.txt
python3 main.py
```

- 실행하면 우선 현재 우주에 있는 사람 명단을 한 번 출력합니다.
- 이후 5초 간격으로 총 5회, ISS의 위도/경도와 그 위치가 어느 나라(또는 대양) 근처인지
  출력합니다.
- 중간에 멈추고 싶으면 `Ctrl+C`를 누르면 됩니다.
- **인터넷 연결이 필요합니다** (외부 공개 API를 호출하기 때문).

## 코드 설명

| 함수 | 역할 |
|---|---|
| `get_iss_location()` | Open Notify API에서 ISS의 현재 위도/경도, 타임스탬프를 가져옴 |
| `get_location_name()` | 위경도를 BigDataCloud 역지오코딩 API로 실제 지명(국가/도시)으로 변환 |
| `get_astronauts_in_space()` | 현재 우주에 있는 사람 수와 이름, 탑승 우주선 목록을 가져옴 |
| `format_timestamp()` | 유닉스 타임스탬프를 사람이 읽기 좋은 UTC 문자열로 변환 |
| `track_once()` | 한 번의 조회 결과를 정리해서 출력 |
| `main()` | 전체 흐름 제어 (반복 조회, 예외 처리, 종료 처리) |

## 호출하는 외부 API (모두 무료, 인증키 불필요)

1. `http://api.open-notify.org/iss-now.json` — ISS 현재 위치
2. `http://api.open-notify.org/astros.json` — 현재 우주 체류 인원
3. `https://api.bigdatacloud.net/data/reverse-geocode-client` — 위경도 → 지명 변환

## 추가 구현 (자유 확장)

- 단순히 위경도 숫자만 보여주는 것에서 그치지 않고, 역지오코딩 API를 하나 더 붙여서
  "ISS가 지금 어느 나라 상공을 지나가는지"를 사람이 읽기 편한 형태로 보여주도록
  확장했습니다. ISS는 지구를 약 90분에 한 바퀴 도는데, 대부분 바다 위를 지나가기
  때문에 "육지 없음(대양 상공)"이 나오는 경우가 더 흔합니다. 몇 번 실행해보면
  실제로 그렇다는 걸 체감할 수 있습니다.
- 네트워크 오류가 나도 프로그램 전체가 죽지 않도록 각 API 호출마다 예외 처리를
  넣었습니다.
