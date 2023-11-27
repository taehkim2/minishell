# minishell

bash와 비슷한 동작을 하는 shell을 직접 구현해보자

## 코드 작성 규칙

### 1. 모든 함수 및 파일은 1개의 기능을 할 수 있어야 한다.
- 파일 1개가 1개의 기능을 가지는 것은 가능하다.
```
ft_split.c
-> 해당 파일은 문자열을 특정 문자를 기준으로 나누는 기능을 수행한다.
```

### 2. 모든 함수 및 파일은 맨 앞에 사용될 목적을 적고 뒤에 기능을 적어야 한다.
```
pars_strlen
-> parsing에 쓰이며, str의 길이를 세는 기능을 가지고 있다.

pars_strjoin
-> parsing에 쓰이며, 두 개의 문자열을 합쳐 1개로 만들어주는 기능을 가지고 있다.
```

### 3. 모든 함수에서 쓰이는 변수들의 이름에는 명확한 목적이 담겨 있어야 한다.
- i, j, k와 같이 의미 없는 변수명 보다는 idx, len, cnt 와 같이 해당 변수가 어떤 역할을 하고 있는지 잘 알아볼 수 있도록 적어야 한다.
```
p_idx : p 문자열의 인덱스
p_len : p 문자열의 길이
p_cnt : p 문자의 개수
```

### 4. 함수를 1개 만들때 마다 의도대로 기능이 구현 되었는지 테스트를 진행해야 한다.
- 테스트는 main 문을 만들어 진행한다.

### 5. 구현을 끝낸 후 함께 코드를 합치는 과정을 진행한다.
- 아래의 과정으로 프로젝트가 진행된다
```
step 1. 각자 구현해야할 파트 할당
step 2. 함수 구현 및 리팩토링 진행
step 3. 각자 구현한 함수들을 합친 후 정상적으로 작동하는지 확인
```
---
