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
- ctrl + n 카를 사용하여 에디터 모드 실행

# 파이썬 기본 문법

## 들여쓰기 (ident)
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
- 다수의 새로운 줄을 삽입할 시에는 """..."""" 나 "..." 를 활용하면 편리 
- 이 문구 내에서 엔터를 삽입하면 자동으로 새로운 줄로 인식하여 출력
- '\'를 삽입하면 엔터가 무시
```py
# UsageL things [OPTIONS]
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
print("우리집 주소는 {} 아파트 {}동 {}호".format('꿈나무', 101, 101)); # 우리집 주소는 꿈나무 아파트 101동 101호 
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
a # 1
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
a = int(input("a: = ")) # 2
b = int(input("b: = ")) # 3
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
- ex) ip-api.com/json/naver.com
