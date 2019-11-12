#include <Windows.h>
#include <wininet.h> 
#include <iostream>
#pragma comment(lib, "Wininet")

/// FTP SERVER SETTINGS ///
const char* SERVER_ADDRESS="SERVER_ADDRESS";
const char* ID = "ID";
const char* PW = "PASSWORD";

std::string RemotePath = "./"; // Upload/Download Path
HINTERNET hInternet;
HINTERNET hFtpSession;
int SERVER_STATUS=0; // 0= Offline 1=Online

void ConnectFtp()
{
	hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (hInternet == NULL)
	{
		std::cout << "Internet Open Error: " << GetLastError() << std::endl;
		return;
	}
	else
	{
		hFtpSession = InternetConnect(hInternet, SERVER_ADDRESS, INTERNET_DEFAULT_FTP_PORT, ID, PW, INTERNET_SERVICE_FTP, 0, 0);
		if (!hFtpSession)
		{
			std::cout << "Internet Connect Error: " << GetLastError() << std::endl;
			return;
		}
		else 
		{
			SERVER_STATUS = 1;
			std::cout << "Server Connected..." << std::endl;
			std::cout << "SERVER_ADDRESS : " << SERVER_ADDRESS << std::endl;
			std::cout << "SERVER_STATUS : "<< SERVER_STATUS << std::endl;
		}
	}
	return;
}

void CloseFtp()
{
	if (hInternet)
	{
		InternetCloseHandle(hInternet);
		hInternet = NULL;
	}

	if (hFtpSession)
	{
		InternetCloseHandle(hFtpSession);
		hFtpSession = NULL;
	}
	std::cout << "Connection Closed..."<< std::endl;
}

void FileSubmit(char* Destfilename) // Upload File to FTP Server
{
	if (SERVER_STATUS)
	{
		std::string tDestFile = RemotePath + Destfilename;
		const char* DestPath = tDestFile.c_str();
		if (!FtpPutFile(hFtpSession, DestPath, Destfilename, FTP_TRANSFER_TYPE_BINARY, 0))
		{
			std::cout << "File Upload Error: " << GetLastError() << std::endl;
		}
		else 
		{
			std::cout << "File Upload Complete" << std::endl;
		}
	}
}

void FileDown(char* Destfilename) // Download File from FTP Server
{
	if (SERVER_STATUS)
	{
		std::string tDestFile = RemotePath + Destfilename;
		const char* DestPath = tDestFile.c_str();
		printf("Download Path : %s\n", DestPath);
		if (!FtpGetFile(hFtpSession, DestPath, Destfilename, FALSE, NULL, FTP_TRANSFER_TYPE_BINARY, NULL))
		{
			std::cout << "File Download Error: " << GetLastError();
		}
		else
		{
			std::cout << "File Downloaded" << std::endl;
		}
	}
}

void FileRemove(char* filename) // Remove File
{
	if (SERVER_STATUS)
	{
		if (!FtpDeleteFile(hFtpSession, filename)) {
			std::cout << "File Remove Error: " << GetLastError();
		}
		else
		{
			std::cout << "File Removed..." << std::endl;
		}
	}
}

int main()
{
	ConnectFtp(); // Connect to Server
	//FileSubmit("FTP_1105.zip"); // File Upload
	//FileDown("FTP_1105.zip"); // File Download
	//FileRemove("appserver1.cap");
	CloseFtp();
	return 0;
}