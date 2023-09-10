# Minishell 팀 프로젝트
<div align=center>
<img width="495" alt="asdasda" src="https://github.com/inhoekim/minishell_prj/assets/92151066/79126220-8e59-4522-aa98-c74def69eef6">

<br/>

해당 프로젝트의 목표는 유닉스 쉘을 직접 구현해보는 것입니다!

    This is our Interactive-shell project!
    (from 42Cursus - Circle 3)

</div><br/>

사용언어 :  &nbsp;&nbsp; <img src="https://img.shields.io/badge/C-3178C6?style=flat"/> &nbsp;<img src="https://img.shields.io/badge/Makefile-3178C6?style=flat"/>

사용환경 : &nbsp;&nbsp;<img src="https://img.shields.io/badge/UNIX-3178C6?style=flat"/>

개발 기간 : *2023-07-25 ~ 2023-09-07* 

팀 멤버 : *[seykim](https://github.com/seyeon22222),  [dasong](https://github.com/songdaegeun),  [naylee](https://github.com/wwwlnyy),  [inhkim](https://github.com/inhoekim) (42Cursus-Cardets)*

# 목차
1. [FlowChart](#프로그램-동작과정-flowchart)

2. [프로젝트 모듈요약](#project-file-tree-module-요약)

3. [사용 가능한 쉘기능](#사용-가능-쉘-메타문자-목록)

4. [기타기능 세부사항 && 외부 라이브러리](#기타기능-세부사항-및-사용한-외부-라이브러리)

5. [설치 및 사용법](#설치-및-사용)

<br/>

# 프로그램 동작과정 (FlowChart)

![image](https://github.com/inhoekim/minishell_prj/assets/92151066/d8e82ade-43af-499d-82eb-5069f68d525d)

<br/>

# Project File Tree (module 요약)

<img width="235" alt="스크린샷 2023-09-10 오후 4 08 50" src="https://github.com/inhoekim/minishell_prj/assets/90288195/a7962a52-bbfa-470e-a873-f572795385cb">

<br/>

**[parser](#parser---문법검사-및-트리생성), grammar** : 입력받은 Command의 문법을 검사하고 실행트리를 생성

**[execute](#execute---파싱된-트리를-실행)** : parser에서 만들어진 트리를 순회하며 노드들을 실행

**[builtin_func](#builtin_func---구현한-빌트인-함수-목록-no-option)** : export, cd, unset, pwd, echo, exit, env 쉘 빌트인 기능구현

**expansion** : Command에 들어온 따옴표 처리, 환경변수 확장, 와일드카드 확장 기능을 수행

**signal** : 쉘 구동중 특정 상황별로 sigint(2), sigquit(3) 이벤트처리를 알맞게 재설정하는 기능을 수행

**src** : 미니쉘 메인 시작

***


### parser - 문법검사 및 트리생성

- 문법검사 (grammar module)
  - <a href="https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html#tag_02_10_02">Bash Grammar</a> 를 준수하여 우리만의 문법을 작성

  - 입력된 문자열(Command)의 왼쪽에서부터 파싱을 시작하여(좌측유도) Rule을 적용

  - 적용 가능한 Rule이 여러 개인 상황(비결정적인 상황)을 피하기 위해 적절하게 문법을 수정 (left factoring, left recursion elimination하여 모호성을 제거)

  - Syntax Error -> 파싱 진행중 토큰에 적용할 알맞은 Rule이 없는 경우, 또는 파싱이 끝났으나 아직 검사해야할 토큰이 남은 경우


- 트리 생성
  - 파서는 문법 유효성을 검사하는 동시에 실행부에 넘겨줄 트리를 같이 생성

  - Rule rhs의 앞의 symbol이 child가 되고 뒤의 symbol이 parent가 되어, parent의 왼쪽 자식에 child가 삽입되게끔 트리를 생성 (전위순회 방식)

<br/>    

#### 트리 예시
       
<br/>
<div align=center>

![image](https://github.com/inhoekim/minishell_prj/assets/90288195/0a094c66-5902-4ac1-9ee2-ac65849f8352)
</div>


     ex) cat < a.txt < b.txt | ls -al 

    실행순서 (leaf 기준)

    1. b.txt OPEN
    2. a.txt OPEN
    3. cat   FORK
    4. ls    FORK (arvs : -al)


        
#### 문법
<div align=center>

![image](https://github.com/inhoekim/minishell_prj/assets/90288195/b08ab349-f187-45a6-9a84-4821e7e3b78f)

</div>


***

### execute - 파싱된 트리를 실행
- 일반적인 경우, 트리의 루트에서 왼쪽부터 내려가며 각 노드들을 실행 (전위 순회 - 재귀)

- 단, 오른쪽 자식이 파일인 경우에만 오른쪽 자식을 먼저 방문(입출력 재지정시에만)

- 쉘 메타문자별로 노드의 타입을 구분함 (ex. pipe_type(|),  input_type(<),  heredoc_type(<<),  etc.. )

- 쉘 메타문자 타입을 제외한 모든 것은 특정 파일 혹은 명령어와 관련된 문자 -> word_type

***

### builtin_func - 구현한 빌트인 함수 목록 (No Option)
    export : 환경변수 추가 및 업데이트, 갱신
    cd : 절대경로 및 상대경로를 통한 디렉토리 이동
    unset : 등록된 환경변수를 제거
    pwd : 현재 작업중인 디렉토리 표시
    echo : echo 구현(-n옵션)
    exit : 현재 프로세스를 종료
    env : 환경변수의 리스트를 출력

# 사용 가능 쉘 메타문자 목록

**$ (Shell Environment Variables)** : 시스템 환경변수 및 쉘 환경변수를 등록하고 참조가 가능 (시스템 환경변수는 참조만 가능, 추가적인 등록 X)

**| (Pipe)** : 병렬적인 프로세스 실행 및 파이프를 이용한 프로세스간 통신이 가능

**<, >, >> (Redirect)** : 프로세스의 입출력 스트림 재지정이 가능
- < : 실행 프로세스의 입력 재지정
- \> : 실행 프로세스의 출력 재지정(덮어쓰기)
- \>\> : 실행 프로세스의 출력 재지정(이어쓰기)

**<< (HereDoc)** : 파일 리터럴을 생성. 사용자는 실행 프로세스 입력을 인라인한 방식으로 재지정이 가능

**&& (And)** : CMD1 && CMD2 처럼 사용하며, CMD1이 명령어 실행에 성공했을 때, CMD2를 실행(CMD1이 실행에 실패했을 때, CMD2 실행 X)

**|| (Or)** : CMD1 || CMD2 처럼 사용하며, CMD1이 명령어 실행에 실패했을 때, CMD2를 실행(반대의 경우 CMD1이 실행에 성공했을 때, CMD2는 실행 X)

**\*, ? (WildCard)** : 와일드카드 문자 확장이 가능. \*은 0글자 이상의 모든 문자와 매칭되며, ?는 한글자만 매칭 (ex. \*a -> ba,?a,aaa  / ?a -> ba, ca etc..)

<br/>

# 기타기능 세부사항 및 사용한 외부 라이브러리

- **[Readline(GNU)](https://tiswww.case.edu/php/chet/readline/rltop.html) 라이브러리** : histroy 기능, 표준입력 처리 및 프롬프트 커서 처리를 위해 사용함
    - histroy 기능 : 사용자가 기존에 입력한 키워드(history)를 기억하여 키보드 입력(↑ , ↓)시 이전 키워드를 찾을수 있도록 하는 기능

- **시그널 이벤트 변경** : sigint(2)과 sigquit(3)에 대한 시그널 핸들러가 재지정되어 있음. 해당 시그널들은 참고한 쉘(Bash)과 동작이 동일하게끔 설정함
    - Sigint(2) : 새로운 프롬프트를 출력
    - Sigquit(3) : 아무런 동작을 수행하지 않음

- **quote(", ') 처리기능** : quote로 감싸진 Command문의 처리는 기존의 쉘(Bash)과 동일함

- **wait_process관련 세부사항** : fork를 통해 생성한 프로세스들의 정상종료를 대기하기 위한 자료구조(wait_list)를 만들어 사용함. 프로그램은 wait_list를 반복적으로 순회하여 좀비와 고아프로세스의 생성을 최대한 방지함

- **pipe관련 세부사항** : 프로세스 통신시 sigpipe 경우에 대한 처리가 정상적으로 이루어지도록 pipe()로 생성한 파일디스크럽터를 주기적으로 관리함 

<br/>

# 설치 및 사용

### 1. Git Clone

    git clone https://github.com/inhoekim/minishell_prj.git 폴더이름


### 2. 컴파일 및 빌드 (Makefile)

    git clone 받은 파일경로로 이동
    make 또는 make all 입력 (Make Build Tool 프로그램 이용)

### 3. 프로그램 실행
    설치폴더 경로에서 ./minishell 입력
    또는
    생성된 실행파일 더블클릭

### 4. 파일 삭제
    make clean(실행파일만 남겨두고 오브젝트 파일 삭제)
    또는
    make fclean(실행파일 및 오브젝트 파일 삭제)
