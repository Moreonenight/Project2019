#ifndef __SOCKET_CLIENT_H__  
#define __SOCKET_CLIENT_H__  
#include "BaseConnect.h"  
#include "Command.h"
#include <mutex>
#define COMMON_SIZE 40
#define HERO_SIZE 1
#define CONNECT_TO_INTERNET 1
#define DISCONNECTED 0
#define YASE 0
#define DAJI 1
#define HOUYI 2
#define RED_PLAYER 1
#define BLUE_PLAYER 0
#define SHOECALL 1
#define HATCALL 2
#define SWORDCALL 3

class SocketClient : public BaseConnect
{
public:
	SocketClient(void);
	~SocketClient(void);
	INT32 playerNumber;
	INT32 my_hero;
	INT32 rival_hero;
	bool connectServer(const char* serverIP, unsigned short port);
	void CommonMessage();
	void HeroMessage();
	bool is_sent;
	bool is_client_dead;
	Command wcommand;
	Command rcommand;
	SOCKET _socektClient;
	std::mutex _mutex;

private:
	bool initClient();
	char wclient[COMMON_SIZE];
	char rclient[COMMON_SIZE];
	char wheroBuf[HERO_SIZE];
	char rheroBuf[HERO_SIZE];

private:
	SOCKET _socketServer;
};






#endif  