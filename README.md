# 미니쉘 팀 프로젝트
This is Interactive-shell prj - *from 42Cursus - Circle 3*<br/><br/>
## 팀 멤버<br/>
### 인회<br/>
<a href="https://github.com/inhoekim">![Anurag's GitHub stats](https://github-readme-stats.vercel.app/api?username=inhoekim&locale=kr&show_icons=true&theme=dark&card_width=5&card_height=5) </a><br/>
### 대근<br/>
<a href="https://github.com/songdaegeun">![Anurag's GitHub stats](https://github-readme-stats.vercel.app/api?username=songdaegeun&locale=kr&show_icons=true&theme=dark&card_width=5&card_height=5)</a><br/>
### 나영<br/>
<a href="https://github.com/wwwlnyy">![Anurag's GitHub stats](https://github-readme-stats.vercel.app/api?username=wwwlnyy&locale=kr&show_icons=true&theme=dark&card_width=5&card_height=5)</a><br/>
### 세연<br/>
<a href="https://github.com/seyeon22222">![Anurag's GitHub stats](https://github-readme-stats.vercel.app/api?username=seyeon22222&locale=kr&show_icons=true&theme=dark&card_width=5&card_height=5)</a><br/>


# 프로젝트 개요
- 구현목표 : 유닉스 쉘을 직접 최소구현 해보는 것<br/>
- 구현 목차   
    - 유닉스 쉘의 문법 - LL파서 구현
    - 빌트인 함수 - export, cd, unset, pwd, echo, exit, env 구현
    - 실행부
    - 구현하면서 생긴 이슈


## 구현 결과 
문서화한 그림 첨부 



=== 

구현한 빌트인 함수 목록들
export, cd, unset, pwd, echo, exit, env

=== 
구현한 쉘 메타문자 목록

&&, || (and , or) : 어쩌고 저쩌고

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


2. 파싱부의 중점

문법과 LL파서 소개

파싱 그림 첨부

3. 실행부의 중점

fork()와 pipe()를 이용한 프로세스 실행법과 올바른 프로세스 관리 wait()에 대해서 소개

4. 프로젝트를 진행하며 생긴 이슈들

