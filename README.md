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

## FTP 구축하기
이 프로젝트는 Windows에서 지원하는 IIS(인터넷 정보 서비스) 관리자를 통해 서버를 구축하였습니다. <br>
IIS는 마이크로소프트 윈도우를 사용하는 서버들을 위한 인터넷 기반 서비스의 모임으로 FTP 뿐만 아니라 ASP.NET, PHP등 <br>
다양한 포로토콜 서비스도 지원합니다. <br>

* 공유기의 경우 포트포워딩 또는 DMZ/Twin IP를 설정해서 외부 접속이 가능한 상태가 되어야 합니다. 이 부분은 [사이트](https://blog.naver.com/btdays/220589344195)를 참고해주시기 바랍니다.

1. IIS 관리자 설치

	* 제어판 > 모든 제어판 항목 > 프로그램 및 기능의 왼쪽 메뉴에 **Windows 기능 켜기/끄기**<br>
	* (Windows 10 기준) 인터넷 정보 서비스 하위에 있는 **FTP 서비스와 IIS 관리 콘솔 체크** 후 확인 <br>
	* 설치 완료

2. FTP 사이트 생성

	* 제어판 > 모든 제어판 항목 > 관리 도구 > **IIS 관리자** 실행 <br>
	* 왼쪽 연결 탭에 있는 서버명을 오른쪽 클릭 후 **FTP 사이트 추가** 클릭 <br>
	* 사이트 이름과 경로(파일이 업로드, 다운로드 될 경로) 설정 후 다음 <br>
	* <u>모두 그대로 두고</u> **SSL 사용 안 함** 체크 후 다음 <br>
	* 인증 : **기본** 체크, 엑세스 허용 : **모든 사용자**, 사용 권한 : **읽기, 쓰기** 체크<br>
	* 생성 완료

3. 방화벽 설정

	* 제어판 > 모든 제어판 항목 > 관리 도구 > **고급 보안이 포함된 Windows 방화벽** 실행 <br>
	* 인바운드 규칙 > **FTP 서버 보안, FTP 서버 수동, FTP 서버**를 다중 선택(Shift+클릭)후 오른쪽 클릭하여 **규칙 사용** <br>
	* (초록색 v 체크가 생기면 성공) <br>
	* 아웃바운드 규칙 > **FTP 서버 보안, FTP 서버**를 다중 선택 후 오른쪽 클릭하여 **규칙 사용**<br>
	* 설정 완료

4. FTP 사용자 추가

	* 제어판 > 모든 제어판 항목 > 관리 도구 > **컴퓨터 관리** 실행 <br>
	* 왼쪽 탭에서 시스템 도구 > 로컬 사용자 및 그룹 > 사용자에서 **새 사용자** 추가 <br>
	**(이 기능이 없는 경우)** [여기](https://support.microsoft.com/ko-kr/help/4026923/windows-10-create-a-local-user-or-administrator-account)를 참고해주세요<br>
	* 사용할 **사용자 이름 작성, 사용자가 암호를 변경할 수 없음, 암호 사용 기간 제한 없음 체크** 후 만들기 <br>

5. 개통 작업

	* 제어판 > 모든 제어판 항목 > 관리 도구 > **서비스** 실행 <br>
	* **Microsoft FTP Service** 오른쪽 클릭 후 **다시 시작** <br>

6. FTP 사이트 접속

	* Win+R 로 실행창 띄우고 cmd 입력
	* ipconfig 입력해서 IP 확인
	* 웹 브라우저에 **"ftp://본인ip"** 입력해서 접속
	* 새로 추가한 사용자 id와 pw 입력해서 확인
	
(참고 출처: [웹사이트](https://m.blog.naver.com/btdays/220593691357) )

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
```c++
int main() { ConnectFtp(); }
```
###### *SERVER_ADDRESS: FTP 서버 주소 *ID, PW: FTP 서버 아이디, 비밀번호

[파일 업로드]
```c++
FtpPutFile(hFtpSession, DestPath, Destfilename, FTP_TRANSFER_TYPE_BINARY, 0)
```
```c++
int main() { FileSubmit(./abc.txt); } 
```
[파일 다운로드]
```c++
FtpGetFile(hFtpSession, DestPath, Destfilename, FALSE, NULL, FTP_TRANSFER_TYPE_BINARY, NULL)
```
```c++
int main() { FileDown(./abc.txt); } 
```

###### *DestPath: 업로드 할 FTP 디렉토리 경로 *Destfilename: 업로드 할 파일명

[파일 삭제]
```c++
FtpDeleteFile(hFtpSession, filename)
```
```c++
int main() { FileRemove(./abc.txt); } 
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
```c++
int main() { CloseFtp(); }
```
[업로드 예시]
```c++
int main() {
	ConnectFtp();
	FileSubmit(./abc.txt);
	CloseFtp();
}
```

## Technologies
Project is created with:
* Visual Studio 2017


