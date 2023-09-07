# 미니쉘 팀 프로젝트
This is Interactive-shell prj - *from 42Cursus - Circle 3*<br/><br/>
## 팀 멤버<br/>
### 인회<br/>
<a href="https://github.com/inhoekim">![Anurag's GitHub stats](https://github-readme-stats.vercel.app/api?username=inhoekim&locale=kr&show_icons=true&theme=dark&card_width=5&card_height=5) </a><br/>

### 나영<br/>
<a href="https://github.com/wwwlnyy">![Anurag's GitHub stats](https://github-readme-stats.vercel.app/api?username=wwwlnyy&locale=kr&show_icons=true&theme=dark&card_width=5&card_height=5)</a><br/>

### 대근<br/>
<a href="https://github.com/songdaegeun">![Anurag's GitHub stats](https://github-readme-stats.vercel.app/api?username=songdaegeun&locale=kr&show_icons=true&theme=dark&card_width=5&card_height=5)</a><br/>

### 세연<br/>
<a href="https://github.com/seyeon22222">![Anurag's GitHub stats](https://github-readme-stats.vercel.app/api?username=seyeon22222&locale=kr&show_icons=true&theme=dark&card_width=5&card_height=5)</a><br/>


## 프로젝트 개요
- #### 구현목표 : 유닉스 쉘을 직접 구현 해보는 것<br/>
- #### 목차   
    - 파서 구현(LL Parser) -  입력받은 command로 트리를 생성 (<a href="https://pubs.opengroup.org/onlinepubs/9699919799.2018edition/utilities/V3_chap02.html#tag_18_10">Bash 문법</a>)    
    - Builtin 함수 구현- export, cd, unset, pwd, echo, exit, env
    - 트리 실행부 구현 - 파싱된 트리를 실행
    - 쉘 메타문자 기능 구현 - 쉘 메타 문자 ($, |, ||, &&, <, >, <<, >>)의 기능을 구현
    - 구현하면서 생긴 문제점 및 쉽게 간과할만한 문제점 정리

미니쉘 프롬프트 사진첨부 (img.png)

## 프로젝트 동작 과정
image.png (간단 버전)

<br/>

## 파서 구현
- ### LL파서 설명
    - 생성된 트리를 가장 아래의 왼쪽부터 순회하면서 실행
    - 각 root의 왼쪽에는 Command, 오른쪽에는 옵션 또는 목적 내용
- ### 간단한 명령어일 떄, 트리 구성그림 추가
    - image.png(간단한 트리예시/ 예.ls | cat etc.)

<br/>

## Builtin 함수 목록들
#### export
- 환경변수 추가 및 업데이트, 갱신
#### cd
- 절대경로 및 상대경로를 통한 디렉토리 이동
#### unset
- 등록된 환경변수를 제거
#### pwd
- 현재 작업중인 디렉토리 표시
#### echo
- -n옵션만 추가한 echo구현
#### exit
- 현재 프로세스를 종료
#### env
- 환경변수의 리스트를 출력
<br/>

## 트리 실행부 구현 - 파싱된 트리를 실행

<br/>

## 구현한 쉘 메타문자 목록
///&&, || (and , or) : /어쩌고 저쩌고

| (파이프) : 우리쉘은 파이프로 묶인 두쌍의 프로세스를 실행시키고 서로 통신이 가능하게끔 맺어주어야 함

<, >, >> (리다이렉트) : 프로세스의 입출력을 재지정해줄 수 있어야함

<< (히어독 리다이렉트) : 어쩌고 저쩌고

* (와일드카드) : 어쩌고 저쩌고 

$ (쉘 환경변수) : 사용자가 등록한 환경변수를 저장하고 사용자가 원하는때에 변환해줄 수 있어야함

===

기타 기능들


histroy 기능 : 사용자가 기존에 입력한 키워드(history)를 기억하여 키보드 입력(up, down)시 이전 키워드를 찾을수 있도록
환경변수 확장기능 :  (메타 문자 $)
시그널 이벤트 변경 : sigint, sigquit
quote(", ') 처리기능: quote로 감싸진 메타문자의 처리는 기존의 쉘과 동일해야함


3. 실행부의 중점

fork()와 pipe()를 이용한 프로세스 실행법과 올바른 프로세스 관리 wait()에 대해서 소개

4. 프로젝트를 진행하며 생긴 이슈들

