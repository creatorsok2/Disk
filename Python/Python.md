# 파이썬의 기본적인 개발자 도구 IDLE

## IDLE 이란?
- 파이썬을 설치하면 함께 설치되는 가장 기본적인 개발자 도구
- 다른 개발자 도구는 기능이 많아서 좋지만 기본적인 환경에서 사용하는 IDLE을 사용하는 방법을 익혀두면 어떤 파이썬 환경에서도 파이썬을 원하는 대로 실행 가능
- 기능은 많이 없음
- 파이썬에는 셀(shell) 모드와 에디터(Editor) 모드가 존재
- 셀 모드는 사용자와 상호동작할 수 있어 한 줄 단위로 코드를 입력하고 실시간으로 결과 확인 가능 
- 그러나 셀모드는 코드를 저장하지 않기 때문에 별도의 메모를 하지 않으면 재사용 불가능
- 에디터 모드는 직접 텍스트로 py 파일을 저장하고 파이썬을 사용해 전체 내용을 한 번에 실행 
- 파일을 저장하여 실행하기 때문에 재사용이 가능
- 'ctrl + n' 키를 사용하여 에디터 모드 실행

# 파이썬 기본 문법

## 들여쓰기 (indent)
- 파이썬은 다른 언어들과 달리 들여쓰기에 매우 민감
- 다른 언어들은 중괄호({,}) 등을 통해 코드를 묶음
- 파일썬은 들여 쓰기를 통해 코드를 묶음

```py
def add(a, b): # 함수 add 선언
    return a+b # 함수 add 내용
result = add(1, 2) # 함수 실행
print(result) 
```
## 변수
- 값이 변하는 수
- 한 순간에 하나의 데이터 값을 가짐
- 이 값을 다른 데이터로 바꿀 수 있음
- 다양한 데이터를 임시로 저장
- 변수를 선언하는데 다음과 같은 규칙이 필요
    - 대소문자, 숫자, 밑줄문자(_)를 조합하여 구성
    - 첫자는 반드시 영문자, 밑줄 문자로 시작
    - 구분 공백 및 특수문자 포함 불가능
- 변수의 대한 타입은 type(변수) 함수를 사용하여 확인 가능

## 숫자형 데이터 
- 계산 부호(+,-,*,/)를 통해 코드에서 직접 연산 가능
```py
a = 3
type(a)
10 // 4 # 목
10 % 4 # 나머지 
```

## 문자열
- 싱글 쿼터(')나 더블 쿼터(")를 사용하여 문자열을 입력
- 두 가지 쿼터를 번갈아 사용하거나, 백 슬러시(\)를 사용하여 싱글 쿼터와 더블 쿼터를 문자열의 일부로 사용가능 
```py
'i like you' # 'i like you'
"i like you" # 'i like you'
```
- '\n'을 사용하여 새로운 줄을 삽입
- 문자열 앞에 'r'을 삽입하여 raw strings으로 사용
```py
print(r'c:\new_folder') # c:\new_folder
``` 
- 다수의 새로운 줄을 삽입할 시에는 """...""" 나 "..." 를 활용하면 편리 
- 이 문구 내에서 엔터를 삽입하면 자동으로 새로운 줄로 인식하여 출력
- \ 를 삽입하면 엔터가 무시
```py
# Usage things [OPTIONS]
#   -h      Display this usage message
#   -H      Hostname to connect

print("""\
    Usage: things [OPTIONS]
        -h      Display this usage message
        -H      Hostname to connect to
    """)
```
- 곱하기 연산(*)을 사용하여 문자를 여러 번 출력
- 더하기 연산(+)을 사용하여 문자열을 붙임

# 파이썬 입력과 출력

## print를 사용한 변수 출력
- print는 입력한 데이터를 출력하는 기능을 가짐
```py
a = 1
print(a) # 1
```
- 콤마를 입력하면 변수를 여러 개 입력해서 사용 가능
- 데이터는 형이 달라도 상관 없음
```py
a = 1
b = 'str1'
print(a, b) # 1 str1 

# 1 str1\n1 str1
print(a, b, end = '\n')
print(a, b, end = '\n') 

# 1 str1 1 str1 
print(a, b, end = '\r')
print(a, b, end = '\r')
```
- 데이터 변수들과 함께 형식화된 문자열을 출력하고 싶은 경우에는 format 스트링을 사용
- 일반적인 언어들에서 사용하는 포맷 스트링은 데이터 형과 매칭을 시켜주어야 한다. 
```py
print("우리집 주소는 %s 아파트 %d동 %d호"%('꿈나무', 101, 101)) # 우리집 주소는 꿈나무 아파트 101동 101호 
```
- 파이썬에서는 포맷스트링을 무시하고 사용할 수 있는 문법도 존재
- 중괄호를 사용하면 데이터 형에 상관없이 원하는 데이터를 전달
```py
print("우리집 주소는 {} 아파트 {}동 {}호".format('꿈나무', 101, 101)) # 우리집 주소는 꿈나무 아파트 101동 101호 
```
## 파이썬 데이터 입력
- input: 사용자 입력을 받는 함수
- 변수로는 안내 문구를 적음 
```py
input("원하는 데이터를 넣어주세요:") 
int(input("원하는 정수를 넣어주세요:"))
_ # shell 에서 마지막으로 나온 결과를 출력해준다. 
```
- 데이터를 여러 개 받을 때는 split을 사용한다
- split은 문자열을 조각 낼 때 사용하는 함수다.
```py
number = input("숫자 여러 개를 공백으로 구분해서 넣어주세요:")
> 1 2 3 4 5 # ['1' '2' '3' '4' '5']
a, b, c, d, e = number.split(' ')
a # '1'
int(a) # 1
```
## 강제 형변환 하기 
- int(): 문자형 데이터나 실수 형 데이터를 정수로 변환(실패 시 에러)
- str(): 각종 데이터를 문자열로 변환
- float(): 문자형 데이터나 정수형 데이터를 부동소수점으로 변환

## 연습문제 

```py
# 다중 문자열을 이용하여 문자출력
print("""\
    **
   *  *
  *    *
 *      *
*        *""");

# 계산기 
a = int(input("a: = ")) # input 2
b = int(input("b: = ")) # input 3
print("{} + {} = {}".format(a, b, a+b)) # 2 + 3 = 5
print("a + b = {}".format(int(input("a: = ")) + int(input("b: = ")))) # 한줄로 표현
```

# 다양한 데이터 타입

## 부울(bool)
- 논리형식으로 다루는 데이터 
- 참(True) 와 거짓(False) 두가지
- bool(x) 함수를 사용하여  True와 False를 리턴
- x의 값이 0이거나 None(데이터가 없는 경우)인 경우 False
- 0이 아니거나 데이터가 존재할 경우 True를 반환한다
- 주로 if, while, for 등의 조건문에서 프로그래머의 가독성을 위하여 사용
- 데이터가 참인 경우
    - 데이터가 있는 경우
    - 0이 아닌 모든 숫자(음수 포함)
    - 배열에 데이터가 있는 경우
- 데이터가 거짓인 경우
    - 데이터가 없거나 0인 경우

## 비교 연산 
- 데이터를 비교함으로써 참과 거짓을 판별 가능
- 부등호 사용

## 논리 연사
- 다수의 부울을 사용해 하나 이상의 논리를 결합하여 복합된 연산을 수행

```py
bool(1) # True
bool(-1) # True
bool(0) # False
bool(None) # False
bool([]) # False
bool(['123']) # True

1 == 2 # False
1 != 2 # True
1 >= 2 # False
1 <- 2 # True 

True and False # False, &
True or False # True, |
not True # False, !
```

## 리스트(list)
- list는 여러 데이터 타입 중 가장 다양하게 사용
- list에는 여러 가지 타입을 담을 수 있음
- [] 형식과 :를 활용하여 데이터 조회
- in 문법을 사용하면 list 안에 특정 데이터가 있는지 없는지 확인 가능
- .index를 사용하여 데이터 위치 조회 (없는 경우 에러 출력)

```py
a = [1, 2, 3, 4, 5] # [1, 2, 3, 4, 5]
a[-1] # 5
a[-3:] # [3, 4, 5]

1 in a # True
8 in a # False

a.index(2) # 1
```
- 등호 연산(=)을 활용하여 임의의 list에 숫자를 집어 넣거나 더하기 연산(+)을 활용하여 임의로 list를 추가 
- 하지만 더하기 연산(+)은 임의적인 추가이기 때문에 a 리스트는 변하지 않음
- 영구적인 추가를 위해 append 함수 사용
```py
a[3] = 100 # [1, 2, 3, 100, 5]
a + [6, 7, 8] # [1, 2, 3, 100, 5, 6, 7, 8]
a # [1, 2, 3, 100, 5]
a.append(6) # [1, 2, 3, 100, 5, 6]
a.append(7) # [1, 2, 3, 100, 5, 6, 7]
```
- split : 문자열을 전달을 원하는 단위로 잘라서 리스트로 반환
```py
str = "Hello World Python"
str.split(' ') # ['Hello', 'World', 'Python']
```

## 연습문제 
```py
a = [1, 2, 3, 'string'] # list 생성
a += ['a', 'b', 'c', 1, 2, 3] # list 추가
a[1:4] # list 1~3 조회
a.index('string') # list index 
a.count(1) # list find count

a = "i love you, john!" # 문자열
a = a.split(' ') # 문자열 list로 변경
a.index('john!') # list index
len(a) # list 사이즈
```

## 튜플(tuple)
- 튜플은 리스트와 다르게 서로 다른 형식의 데이터를 집합으로 생성 가능 
```py
tp1 = 1, 2, 3 #(1, 2, 3)
tp2 = tp1, ('a', 'b', 'c') # ((1, 2, 3), ('a', 'b', 'c'))
```
- 튜플의 요소는 변조하거나 삭제 불가
- 새로운 값을 넣으려 하면 오류 구문 출력
- 하지만 튜플은 가변하는 list는 포함 가능

## 세트(set)
- 중복된 요소가 없는 정렬되지 않은 집합
- 기본적으로 멤버를 검사하고 중복 항목을 제거
- union, intersection, difference, symmetric difference 와 같은 수학적 연산 지원
- 중괄호나 set() 함수를 사용하여 set을 생성
- 리스트 [], 튜플 (), 세트 {}

## 세트(set) 연습문제
```py
a = set('abcdefgh') # {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'}
b = set('cdef') # {'c', 'd', 'e', 'f'}
c = set('efgh') # {'e', 'f', 'g', 'h'}
print("a | b : ", a | b) # {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'}
print("a - c : ", a - c) # {'a', 'b', 'c', 'd'}
print("a & b & c : ", a & b & c) # {'e', 'f'}

a = input("입력 :")
print(set(a.split()))

# 집합연산
a = set('1234567') # { '1', '2', '3', '4', '5', '6', '7' }
b = set('4567890') # { '4', '5', '6', '7', '8', '9', '0' }
a | b # {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'} 합집합
a - b # {'1', '2', '3'} 차집합
a & b # {'4', '5', '6', '7'} 교집합
a ^ b # {'1', '2', '3', '8', '9', '0'} xor

c = list(a | b)
c.sort() # list 정렬
sorted(c) # list 정렬
```

## 딕셔너리(dictionary)
- dict는 딕셔너리의 약자로 값과 속성으로 이루어짐
- 값은 문자열, 정수, 배열, dict 등 삽입 가능
- key를 사용하여 value를 인텍스
- 키는 strings나 number가 될 수 있으나, 변하지 않아야 함
- 키는 고유한 성질을 가져야 함
- 정렬되지 않은 key:value 쌍
- {} 를 활용하여 dictionary를 만들고, 그 안에 :를 사용하여 key와 value를 구분
- key를 사용하여 value를 저장
- 딕셔너리의 keys 함수를 사용하면 딕셔너리의 키만 확인
- 딕셔너리의 values 함수를 사용하면 딕셔너리의 값만 확인
- 딕셔너리의 items 함수를 사용하면 딕셔너리 전체를 확인
```py
a = { 'a' : 'b', 'b': 'e' } # {'a' : 'b', 'b': 'e'}
a['a'] = 'c' # {'a' : 'c', 'b': 'e'}
a.keys() # ['a', 'b']
a.valus() # ['c', 'e']
a.items() # [('a', 'c'), ('b', 'e')]
```
- 전체 내용을 확인하려면 data의 keys를 통해서 내용 확인 가능 
```py
for i in a.keys():
    print(i, ':', a[i])
```

## 딕셔너리(dictionary) 연습문제
```py
a = {'name' : 'john', 
'phone' : '01012345678',
'email' : 'test@test.com',
'birth' : 1111 }

print("name :", a['name']) # john

a['birth'] = 1010
print("birth :", a['birth']) # 1010

a['city'] = 'seoul'
print("a :", a) # { 'name' : 'john', 'phone' : '01012345678', 'email' : 'test@test.com', 'birth' : 1010, 'city' : 'seoul' }

del a['email']
print("a :", a) # { 'name' : 'john', 'phone' : '01012345678', 'birth' : 1010, 'city' : 'seoul' }
```

# 파이썬에서 존재하는 다양한 데이터 형
## JSON 웹 데이터 처리하기
- IP 주소나 도메인 이름을 위치 정보로 바꿔주는 서비스, [ip-api](https://ip-api.com/docs/api:json)
- Url을 통해 ip나 도메인 이름을 전달 
```sh
pip install requests # requests lib install
```
```py
import requests
import json

# http://ip-api.com/json/naver.com
domain_name = input("domain name :")
url = 'http://ip-api.com/json/' + domain_name
req = requests.get(url) # ip 위치 정보 query
domain_dic = json.loads(req.text) # json parse
for i in sorted(domain_dic.keys()):
    print(i, ':', domain_dic[i])
```

# 파이썬 함수 선언과 활용
## 함수가 무엇이죠?
- 첫 번째 집합의 임의의 한 원소를 두 번째 집합의 오직 한 원소에 대응시키는 대응 관계이다. 

## 함수의 리턴이란?
- 어떤 x 값에 대한 함수의 결과 f(x)에 대한 결과(리턴)

```py
# a와 b를 삽입하면 두 수를 더한 값을 리턴
def add(a, b):
    return a + b

print('add :', add(1, 2)) 
```

## 파이썬 함수 선언과 활용 연습 문제
```py
# 1. 사용자의 입력을 받아 다음과 같은 출력 형태를 갖는 add_num2()를 작성하십시오.
def add_num2:
    a = input('input :')
    a = a.split()
    b = 0
    for i in a:
        b += int(i)
    
    return b

print(add_num2())

# 2. IP 주소로 실제 위치 찾기 프로그램을 함수로 만들기
import requests
import json

def getlocation(domain):
    url = 'http://ip-api.com/json/' + domain
    req = requests.get(url)
    dic = json.loads(req.text)
    return dic

url = input('input :')
dic = getlocation(url)
for i in dic.keys():
    print(i, ' : ', dic[i])
```

# 프로그램 흐름 제어
## if, elif, else
- if문은 가장 잘 알려진 프로그래밍 구문
- if 조건 외에 해당하면 else를 사용하여 프로그램의 흐름을 제어
- elif를 사용하여 조건을 추가적으로 검사
- 앞에 있는 if나 elif문에서 조건이 만족하지 않는 경우에만 검사
- if나 elif에서 조건이 일치하는 경우가 있으면 하위에 있는 elif와 else는 모두 무시
- else와 elif는 선택적으로 사용가능
```py
num = 1
if num > 0: # 양수 
    print('+')
elif num == 0: # 0
    print('zero')
else: # 음수
    print('-')
```

## 연습문제
```py
def robot_action(x):
    if x == 0:
        print('우회전')
    elif x > 1:
        print('점프')
    else x < -1:
        print('유턴')
    else:
        print('전진')

x = input('input :')
robot_action(x)
```
## for 루프
- for 루프는 반복문의 일종
- 코드가 반복적으로 수행
- 다른 언어의 for문과 달리 배열이나 문자열 사용하여 실행
- 숫자를 반복하여 쓰는 것뿐 아니라 list와 string까지도 for문에 사용가능
- 다음 코드는 list로부터 값을 하나씩 읽어 word라는 변수에 넣어서 for문 안에 있는 print함수를 실행
```py
for i in [0, 1, 2, 3, 4]:
    print(i) # 0 1 2 3 4

for i in 'strings':
    print(i) # s t r i n g s

for i in ['hello', 'world']
    print(i) # hello world
```

## 리스트 생성기 range
- for문을 만 번 돌리려면 이걸 리스트로 다 만들어야 하나!
- 사용 형태 : range(시작 숫자, 끝 숫자, 연산할 숫자)
- 끝 숫자는 생략 불가
- 시작 숫자와 연산할 숫자는 생략 가능 
- 시작 숫자를 생략할 시 기본값으로 0으로 지정되고, 연산할 숫자는 1로 지정

```py
range(10) # [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
range(1, 10, 2) #[1, 3, 5, 7, 9]
```

## for 루프 - range 연습문제
```py
# 구구단 2단 출력
for i in range(1, 10):
    print('{} * {} = {}'.format(2, i, 2 * i))

# 블러그 조회수 올리기 
import webbrowser # 웹브라우저를 여는 프로그램
import time # 시간조절

url = input('input :') # naver.com
webbrowser.open(url) # url open
time.sleep(2) # sleep 2sec
```

## 이중 for루프 
```py
res = ''
for i in range(2, 21):
    res += '{} 단\n'.format(i)
    for j in range(1, 21):
        res += '{} * {} = {}\n'.format(i, j, i * j)

print res
``` 

## 이중 for 루프 연습문제 
```py
# 구글 입사 문제 풀어보기
# 1부터 10,000까지 8이라는 숫자가 총 몇 번 나오는가?

cnt = 0
for i in range(1, 10001):
    for j in str(i):
        if j == '8':
            cnt += 1

print('Count :', cnt)
```

## while 루프
- while문은 for문과 같이 일정한 코드를 반복할 때 사용
- 사용 형식 : while(조건문)
- 조건문이 참일 경우에만 구문 실행
```py
a = 0
while(a < 5>):
    a += 1
```

## while 루프 - break와 continue, pass
- break : 구문을 탈출하고자 할 때 사용
- continue : 아래의 코드를 무시하고 for문을 처음부터 시작할 때 사용
- pass는 아무런 실행도 원하지 않을 때 정상적인 구문으로 처리 
- pass도 역시 break와 continue와 같이 while, for, if, 함수, class 등에서 활용 가능

```py
for a in range(100):
    if a == 10:
        continue
    elif a > 90
        break
    else 
        pass


# while 
a = 0
while(a < 5): # 1, 2, 3, 4, 5
    a += 1
    print(a)

a = 0
while(True):
    if a % 2 == 0: # 짝수
        pass
    elif a == 100:
        break
    else: # 홀수
        print(a)    

# for
for i in range(100) # 1, 2, 3 ... 99
    print(i) 
```

## while 루프 연습문제
```py
while(True):
    a = input('input :')
    if a == 'help':
        print('echo code')
    elif a == 'quit':
        b = input('y/n :')
        if b == 'y':
            break
        else:
            continue 
    else:
        a += ' '
        print(a * 3)
```

# 파이썬을 활용한 파일 입출력

## 파일 입출력 기본 방법
- 파일을 입출력하는 것은 프로그래밍의 기본
- 파일을 입출력할 때 단 세가지만 기억하라
- 열고 쓰고 닫고, 열고 읽고 닫고
- 파일 다루기 기본 (읽기에는 'r', 쓰기에는 'w')
```py
# 파일 쓰기
f = open('파일명', 'w')
f.write('데이터')
f.close()

# 파일 읽기
f = open('파일명', 'r')
a = f.read()
f.close()
```
- 파일에 내용 추가하기 
- 'add'의 a를 사용
- 파일의 내용이 바이너리의 경우 binary로 읽도록 b를 추가
: data의 내용을 바이너리에서 한글로 바꿀 때는 data.decode('cp949')를 실행한다.
```py
# 파일 추가 쓰기
f = open('파일명', 'a')
f.write('데이터')
f.close()

# 바이너리 파일 읽기
f = open('파일명', 'rb')
a = f.read()
f.close()
```

## 상대 경로와 절대 경로
- 절대 경로: 처음부터 모든 경로의 이름이 적혀있는 경로
    - 리눅스는 '/'로 시작: /etc/passwd
    - 윈도우는 '<알파벳>:/'로 시작: c:/windows/notepad.exe
- 상대 경로: 실행 중인 프로그램 위치에서 바라보는 상대적인 위치
    - 현재 경로: ./
    - 상위 경로: ../
    - 파일명만 있는 경우: "파일명"
    - './파일명': 현재 경로에 있는 파일명
    - '../파일명': 상위 경로에 있는 파일명
    - '../../파일명': 상위 경로의 상위 경로에 있는 파일명

## with를 사용한 파일 읽기 쓰기
- 파이썬은 사용 후 반드시 제거해야 하는 객체의 경우에는 with를 사용하는 것이 좋음(소켓 등)
- 파일 핸들의 경우에 닫아주지 않는 상태가 중복되면 메모리 누수(leak)이 발생하여 프로그램이 비정상 종료
- 파일의 객체를 열어주었다면 반드시 닫아서 메모리 누수가 발생하지 않도록 주의하자

```py
import os 
os.getcwd() # 현재 경로

f = open('파일명.txt', 'w')
f.write('1번\n')
f.close()

f = open('파일명.txt', 'a')
f.write('2번\n')
f.close()

f = open('파일명.txt', 'r')
print(f.read())
f.close()

f = open('파일명.txt', 'rb')
a = f.read()
print(a.decode('cp949'))
f.close()

with open('파일명', 'w') as f:
    f.write('1번\n')

with open('파일명', 'a') as f:
    f.write('2번\n')

with open('파일명', 'r') as f:
    a = f.read()    

with open('파일명', 'rb') as f:
    a = f.read()
    a.decode('cp949')
```

# 터틀 Graphic 다루기 

```py
import turtle as t # turtle 을 nameing을 t 로 사용

# 1. 정사각형 그리기
for i in range(4):
    t.forward(100) # t.fd(100)
    t.left(90)
    print(t.pos())

# 2. 평행사변형 그리기
t.up() # draw unset
t.goto(200, 0)
t.down() # draw set

for i in range(2):
    t.fd(120)
    t.left(120)
    t.fd(80)
    t.left(60)
    print(t.pos())

# 3. 별 모양 그리기
t.up()
t.goto(-200, 0)
t.down()

for i in range(5):
    t.fd(100)
    t.right(360*2 // 5)

# 4. 기하학적인 도형 그리기
t.up()
t.goto(0, 300)
t.down()

t.color('red', 'yellow')
t.begin_fill() # 채우기 시작 

while(True):
    t.forward(100)
    t.left(170)
    x, y = t.pos()
    if int(x) == 0 and int(y) == 300:
        print(t.pos())
        print(abs(t.pos()))
        break

t.end_fill() # 채우기 종료
t.done() 
```
# 거북이 경주 시뮬레이션 만들기
```py
import time
from turtle import *
from random import randint

speed(30)
up()
goto(-140, 140)

for i in range(16):
    write(i, align='center') # text 
    right(90)
    fd(10)
    down()
    fd(150)
    up()
    bk(160)
    left(90)
    fd(20)

finish_line = xcor() - 20
print('finish line :', finish_line)

tutle_color = ['red', 'blue', 'green', 'gold']
tutle_list = []

for i in range(len(tutle_color)):
    t = Turtle() # 거북이 선수 생성
    t.color(tutle_color[i]) # 거북이 선수 색상
    t.shape('turtle') # 거북이 모양
    t.up() # 팬을 업
    t.goto(-160, 140 - 30 * (i + 1))
    t.down()
    tutle_list.append(t)

def start_game():
    while(True):
        for t in tutle_list:
            dist = randint(5, 10)
            t.fd(dist)
            if t.xcor() >= finish_line:
                return t

t = start_game()

for i in range(1, 10):
    t.shapesize(i, i)
    time.sleep(0.1)

for i in range(18 * 3):
    t.right(20)

goto(0, 0)
color_name = str(t.color()[0])
write('Congratulation ' + color_name, align='center', font=('Arial', 20, 'normal'))
```

# What's the next!
- c > window API > socket
- 파이썬 : 해킹 방어 대회(CTF)
    - GUI 프로그래밍
    - 웹 프로그래밍
    - 데이터분석 > 머신러닝 > 딥러닝
    - 사물인터넷 : 라즈베리파이 파이썬 
    - 업무자동화 프로그래밍 (데이터베이스, 시스템 유틸리티)