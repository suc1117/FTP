#include <Windows.h>
#include <wininet.h> 
#include <iostream>

#pragma comment(lib, "Wininet")
using namespace std;

const char* SERVER_ADDRESS="ip_address";
const char* UID = "id";
const char* PASS = "pw";

string StdPath = "./"; // Upload/Download Path
HINTERNET hInternet;
HINTERNET hFtpSession;
int SERVER_STATUS=0; // 0= Offline 1=Online

int ConnectFtp()
{
	hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (hInternet == NULL)
	{
		cout << "Error: InternetOpen = " << GetLastError() << endl;
		return 0;
	}
	else
	{
		hFtpSession = InternetConnect(hInternet, SERVER_ADDRESS, INTERNET_DEFAULT_FTP_PORT, UID, PASS, INTERNET_SERVICE_FTP, 0, 0);
		if (!hFtpSession)
		{
			cout << "Error: InternetConnect = " << GetLastError() << endl;
			return 0;
		}
		else 
		{
			cout << "Server Connected..." << endl;
			SERVER_STATUS= 1;
		}
	}
	return 1;
}

void FileSubmit(char* Destfilename) // Upload File to FTP Server
{
	if (SERVER_STATUS)
	{
		string tDestFile = StdPath + Destfilename;
		const char* DestPath = tDestFile.c_str();
		if (!FtpPutFile(hFtpSession, DestPath, Destfilename, FTP_TRANSFER_TYPE_BINARY, 0)) // ���� ����, ���� �̸�
		{
			cout << "Error: FtpPutFile = " << GetLastError() << endl; 
		}
		else 
		{
			cout << "File Upload Complete" << endl;
			InternetCloseHandle(hFtpSession);
		}
		InternetCloseHandle(hInternet);
	}
}

void FileDown(char* Destfilename) // Download File from FTP Server
{
	if (SERVER_STATUS)
	{
		string tDestFile = StdPath + Destfilename;
		const char* DestPath = tDestFile.c_str();
		printf("Download Path : %s\n", DestPath);
		if (!FtpGetFile(hFtpSession, DestPath, Destfilename, FALSE, NULL, FTP_TRANSFER_TYPE_BINARY, NULL))
		{
			cout << "Error: " << GetLastError();
		}
		else
		{
			cout << "File Downloaded" << endl;
			InternetCloseHandle(hFtpSession);
		}
		InternetCloseHandle(hInternet);
	}
}

void FileRemove(char* filename) // Remove File
{
	if (SERVER_STATUS)
	{
		if (!FtpDeleteFile(hFtpSession, filename)) {
			cout << "Error: " << GetLastError();
		}
		else
		{
			cout << "File Removed..." << endl;
			InternetCloseHandle(hFtpSession);
		}
		InternetCloseHandle(hInternet);
	}
}

int main()
{
	ConnectFtp(); // Connect to Server
	//FileSubmit("FTP_1105.zip"); // File Upload
	//FileDown("FTP_1105.zip"); // File Download
	//FileRemove("appserver1.cap");
	return 0;
}