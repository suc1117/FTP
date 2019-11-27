# Simple FTP
using VC++ 2017 On Windows10

## General info
Simple FTP Function using WinINET API
	
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

## Technologies
Project is created with:
* Visual Studio 2017
	
## Setup
```
$ git clone https://github.com/suc1117/FTP.git
```
