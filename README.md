# Simple FTP
using VC++ 2017 On Windows10

## Update
### 11/20
#### 파일 이름 파싱 (확장명 포함) 
char* GetFilename(char* Destfilename) 

### 11/12
#### 서버 종료 함수 
void CloseFtp()

### 11/05 
#### 서버 연결 함수
void ConnectFtp()
#### 파일 업로드
void FileSubmit(char* Destfilename)
#### 파일 다운로드
void FileDown(char* Destfilename)
#### 파일 삭제
void FileRemove(char* filename)

## 기술 설명
C++ WinINet을 이용한 FTP 클라이언트 기능 구현
	
WinINet enables applications to navigate and manipulate directories and files on an ftp server.                                           
(출처: https://docs.microsoft.com/en-us/windows/win32/wininet/ftp-sessions)

FTP session을 시작하기 위해 InternetOpen을 통한 WinINet 기능 사용을 위한 초기화. <br>
InternetConnect을 통한 세션 생성. <br>
HINTERNET 타입 핸들을 통한 FTP 기능을 수행한다. <br>

![image](https://user-images.githubusercontent.com/48272857/70436815-7f9f8500-1acd-11ea-9335-eab50a2059a6.png)

다음과 같은 다이어그램 형태를 가진다. <br>
세션이 만들어지면 서버와의 업로드, 다운로드등이 가능하다.

```c++
HINTERNET hInternet; // WinINet 초기화
HINTERNET hFtpSession; // FTP 세션 생성

hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
hFtpSession = InternetConnect(hInternet, 
	          SERVER_ADDRESS,
	          INTERNET_DEFAULT_FTP_PORT, // 21
	          ID, 
	          PW, 
	          INTERNET_SERVICE_FTP, 
	          0, 0);
```
###### *SERVER_ADDRESS: FTP 서버 주소 *ID, PW: FTP 서버 아이디, 비밀번호

[파일 업로드]
```c++
FtpPutFile(hFtpSession, DestPath, Destfilename, FTP_TRANSFER_TYPE_BINARY, 0)
```
[파일 다운로드]
```c++
FtpGetFile(hFtpSession, DestPath, Destfilename, FALSE, NULL, FTP_TRANSFER_TYPE_BINARY, NULL)
```

###### *DestPath: 업로드 할 FTP 디렉토리 경로 *Destfilename: 업로드 할 파일명

[파일 삭제]
```c++
FtpDeleteFile(hFtpSession, filename)
```
###### *filename: 삭제할 파일명

[세션 종료]
```c++
if (hInternet) {
	InternetCloseHandle(hInternet);
	hInternet = NULL;
}
if (hFtpSession) {
	InternetCloseHandle(hFtpSession);
	hFtpSession = NULL;
}
```
## Technologies
Project is created with:
* Visual Studio 2017
