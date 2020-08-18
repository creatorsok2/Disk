# MFC Document 
아래의 순서에 따라하면 MFC Document 에 접근이 가능하다. 
1. __google search "microsoft docs"__, [Microsoft Docs](https://docs.microsoft.com/ko-kr/)
2. __Docs 디렉터리 > C++__, [C++](https://docs.microsoft.com/ko-kr/cpp/?view=vs-2019)
3. __언어 및 프레임워크 > MFC(Microsoft Foundation Class)__, [MFC](https://docs.microsoft.com/ko-kr/cpp/mfc/mfc-desktop-applications?view=vs-2019)

# MFC 개념
## 용어 
- DAO(Data Access Object)
- ODBC(Open Databaase Connectivity)
- DDE(Dynamic Data Exchange)
- MAPI(Messaging Application Programming Interface)
- WMS(Window Messaging System)
- ATL(Active Template Library)
- COM(Component Object Model)
- HTML(HyperText Markup language)
- DDX(Dialog data exchange)
- DDV(Dialog data validation)

## 일반 MFC 항목
### 마법사 및 리소스 편집기
프로그래밍 작업의 큰 부분은 어떤 객체에 매핑할 메시지를 선택한 다음 해당 매핑을 구현하는 것입니다. 

```html
<HTML>
<HEAD>
<TITLE>Top HTML Tags</TITLE>
</HEAD>
</HTML>
```

# MSBuild
- build tools download, [Build Tools](https://visualstudio.microsoft.com/ko/visual-cpp-build-tools/)
- msbuild.exe 환경변수 등록
```sh
# path 환경변수 확인 
path

# path 환경변수 등록(임시)
set path = %path%;<new_path>
## new_path : 추가할 경로 

# path 환경변수 등록 
setx path "%path%;<new_path>"
## new_path : 추가할 경로 

# msbuild 15.0 등록 
setx path "%path%;C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\MSBuild\15.0\Bin"
```
- msbuild 를 이용해서 빌드
```sh
msbuild.exe "C:\Disk\Share\TEST\SimpleMFC\SimpleMFC.sln" -t:build -p:Configuration=Release;Platform=x64;VisualStudioVersion=15.0
```






