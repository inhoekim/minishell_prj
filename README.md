# minishell_prj
This is Interactive-shell prj - *from 42Cursus - Circle 3*<br/><br/>
## Team Members - Available Language Stacks<br/>
### Inhoe<br/>
![Anurag's GitHub stats](https://github-readme-stats.vercel.app/api?username=inhoekim&show_icons=true&theme=dark&card_width=5&card_height=5)<br/>
### daegeun<br/>
![Anurag's GitHub stats](https://github-readme-stats.vercel.app/api?username=songdaegeun&show_icons=true&theme=dark&card_width=5&card_height=5)<br/>
### nayoung<br/>
![Anurag's GitHub stats](https://github-readme-stats.vercel.app/api?username=wwwlnyy&show_icons=true&theme=dark&card_width=5&card_height=5)
### seyeon<br/>
![Anurag's GitHub stats](https://github-readme-stats.vercel.app/api?username=seyeon22222&show_icons=true&theme=dark&card_width=5&card_height=5)

이게 근데 팀원들 github링크로 이어지면 더 좋을것같은데

### 개요
<br/>
전체 미니쉘 설명과 기능

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

