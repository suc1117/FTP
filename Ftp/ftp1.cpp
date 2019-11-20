#include <Windows.h>
#include <wininet.h> 
#include <iostream>
#include <string.h>
#pragma comment(lib, "Wininet")

/// FTP SERVER SETTINGS ///
const char* SERVER_ADDRESS= "SERVER_ADDRESS";
const char* ID = "ID";
const char* PW = "PASSWORD";
char* mfilename;

std::string RemotePath = "./"; // Remote Server Path
HINTERNET hInternet;
HINTERNET hFtpSession;
int SERVER_STATUS=0; // 0= Offline 1=Online

char* GetFilename(std::string DestFile) // parsing filename include extension
{
	mfilename = new char[DestFile.length() + 1];
	char* pch;
	char* result;
	strcpy(mfilename, DestFile.c_str());
	pch = strtok(mfilename, "/");
	while (pch != NULL)
	{
		result = pch;
		pch = strtok(NULL, "/");
	}
	return result;
}

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
		char* filename= GetFilename(Destfilename);
		if (!FtpPutFile(hFtpSession, Destfilename, filename, FTP_TRANSFER_TYPE_BINARY, 0))
		{
			std::cout << "\nFile Upload Error: " << GetLastError() << std::endl;
		}
		else
		{
			std::cout << "File Upload Complete" << std::endl;
		}
	}
	delete[] mfilename;
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
	//FileSubmit("C:/example/test.jpg"); // File Upload
	//FileDown("server_file.zip"); // File Download
	//FileRemove("server_file.zip");
	CloseFtp();
	return 0;
}