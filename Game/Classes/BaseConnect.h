#define _CRT_SECURE_NO_WARNINGS
#ifndef __BASE_CONNECT_H__  
#define __BASE_CONNECT_H__  
#include "cocos2d.h"  
#include <WinSock2.h>  
#pragma comment(lib, "WS2_32.lib")  
USING_NS_CC;

class BaseConnect : public Ref
{
public:
	BaseConnect()
	{
		Init = false; 
		WORD wVersionRequested;
		wVersionRequested = MAKEWORD(2, 0);
		WSADATA wsaData;
		int nRet = WSAStartup(wVersionRequested, &wsaData);
		if (nRet != 0)
		{
			return;
		}
		Init = true;
	}
	~BaseConnect()
	{
		if (Init)
		{
			WSACleanup();
		} 
	}

protected:
	void closeConnect(SOCKET socket)
	{
		closesocket(socket);
	}
	bool error(SOCKET socket)
	{
		return socket == SOCKET_ERROR;
	}

private:
	bool Init;
};

#endif  