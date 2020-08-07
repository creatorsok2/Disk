# Docker for Linux
## linux 환경 설정 
- VirtualBox 를 이용하여 Ubuntu 설치 
    - Ubuntu 설치, [Download](https://ubuntu.com/download/desktop)
    - Hyper-V 옵션 비활성화, [Microsoft Docs](https://docs.microsoft.com/ko-kr/virtualization/hyper-v-on-windows/quick-start/enable-hyper-v)
    ```sh
    # Hyper-V 옵션 상태
    dism.exe /Online /Get-FeatureInfo:Microsoft-Hyper-V
    # Hyper-V 옵션 켜기
    dism.exe /Online /Enable-Feature:Microsoft-Hyper-V
    # Hyper-V 옵션 끄기
    dism.exe /Online /Disable-Feature:Microsoft-Hyper-V
    ```
## linux 명령어/단축키 
- **ctrl + alt + t** : 터미널 실행
- docker 설치 
```sh
# 관리자 권한
sudo -i
# docker 설치
apt install docker.io
# os 재시작, ubuntu update 가 background 에서 돌아가고 있을 os 재시작 후 설치 가능 
reboot
```

# Docker for Windows
## 참고문서
- Docker for Window, [Microsoft Docs](https://docs.microsoft.com/ko-kr/virtualization/windowscontainers/quick-start/set-up-environment?tabs=Windows-10-Client)

## Docker 실행 
1. Docker Desktop 을 실행 
2. Window Containers 를 실행 ('Switch to Linux Containers...' 이 나오면 된다.)
3. Docker Volume Folder 에서 PowerShell 실행 
4. docker ps -a : image 검색 
5. docker exec -it win1903 powershell : powershell 을 이용하여 docker image 실행 

## Docker Command 
- & .\CIM.exe -cli TEST.xml : cim 에서 cli 모드로 test 실행 

## Dockerfile 작성 
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

# Docker Tutorial 
```Dockerfile
# 원하는 이미지 검색
docker search tomcat 

# Tomcat 설치 및 실행 
docker run -d -p 8080:8080 --name tc consol/tomcat-7.0
```