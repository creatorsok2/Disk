# Docker 따라하기
## Docker 참조문서
https://docs.microsoft.com/ko-kr/virtualization/windowscontainers/quick-start/set-up-environment?tabs=Windows-10-Client

## Docker 실행 
1. Docker Desktop 을 실행 
2. Window Containers 를 실행 ('Switch to Linux Containers...' 이 나오면 된다.)
3. Docker Volume Folder 에서 PowerShell 실행 
4. docker ps -a : image 검색 
5. docker exec -it win1903 powershell : powershell 을 이용하여 docker image 실행 

## Docker Command 
- & .\CIM.exe -cli TEST.xml : cim 에서 cli 모드로 test 실행 

# Dockerfile 작성 
원하는 텍스트 편집기를 사용하여 Dockerfile을 연 후 다음 콘텐츠를 추가합니다. 

```Dockerfile
FROM mcr.microsoft.com/dotnet/core/sdk:2.1 AS build-env
WORKDIR /app
```
컨테이너를 빌드하는데 사용할 기반이 되는 기본 이미지를 선언합니다. 로컬 시스템에 이 이미지가 없으면 docker가 자동으로 이미지를 가져오려고 시도합니다. 다음 명령은 컨테이너의 작업 디렉터리를 /app로 변경하므로 이 다음에 오는 모든 명령이 이 컨텍스트에서 실행됩니다. 

```Dockerfile
COPY *.csproj ./
RUN dotnet restore
```
.csproj 파일을 **build-env** 컨테이너의 **/app** 디렉터리로 복사합니다. 이 파일을 복사하면 .NET이 이 파일을 읽은 후 프로젝트에 필요한 모든 종속성과 도구를 가져옵니다. 

```Dockerfile
COPY . ./
RUN dotnet publish -c Release -o out
```