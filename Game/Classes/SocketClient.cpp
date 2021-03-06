#include "SocketClient.h" 


SocketClient::SocketClient(void) :
	_socektClient(0),
	is_client_dead(false),
	is_sent(true)
{

}

SocketClient::~SocketClient(void)
{
	if (_socektClient != 0)
	{
		this->closeConnect(_socektClient);
	}
}

bool SocketClient::initClient()
{
	if (_socektClient != 0)
	{
		this->closeConnect(_socektClient);
	}
	_socektClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	return true;
}

bool SocketClient::connectServer(const char* serverIP, unsigned short port)
{
	if (!initClient())
	{
		return false;
	}
	struct sockaddr_in* sin= new sockaddr_in;
	sin->sin_family = AF_INET;
	sin->sin_port = htons(port);
	sin->sin_addr.s_addr = inet_addr(serverIP);
	int ret;
	ret = connect(_socektClient, (LPSOCKADDR)sin, sizeof(*sin));
	if (SOCKET_ERROR == ret)
	{
		return false;
	}
	int timeout = 6000;
	setsockopt(_socektClient, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout));
	const char* WelcomeData = "Standing by to command offensive operations. Weapons free. Repeat, weapons free.\n";
	if (send(_socektClient, WelcomeData, strlen(WelcomeData)+1, 0) <= 0)
	{
		return false;
	}
	const char* ConfirmData = "Fleet action underway.\n";
	char WelData[24];
	memset(WelData, 0, 24);
	if (recv(_socektClient, WelData, 24, 0) ||strcmp(WelData,ConfirmData)!=0)
	{
		return false;
	}
	return true;
}

void SocketClient::CommonMessage()
{
	_mutex.lock();
	if (send(_socektClient, reinterpret_cast <char*>(&wcommand), COMMON_SIZE, 0) <= 0)
	{
		closeConnect(_socektClient);
		is_client_dead = true;
	}
	is_sent = true;
	memset(rclient,0,40);
	if (recv(_socektClient, rclient, COMMON_SIZE, 0) <= 0)
	{
		closeConnect(_socektClient);
		is_client_dead = true;
	}
	memcpy(&rcommand,rclient,sizeof(Command));
	_mutex.unlock();
}

void SocketClient::HeroMessage()
{
	wheroBuf[0] = my_hero;
	if (send(_socektClient, wheroBuf, HERO_SIZE, 0) <= 0)
	{
		closeConnect(_socektClient);
		is_client_dead = true;
	}
	if (recv(_socektClient, rheroBuf, HERO_SIZE, 0) <= 0)
	{
		closeConnect(_socektClient);
		is_client_dead = true;
	}
	if (rheroBuf[0] >= 10)
	{
		playerNumber = RED_PLAYER;
		rival_hero = rheroBuf[0] - 10;
	}
	else
	{
		playerNumber = BLUE_PLAYER;
		rival_hero = rheroBuf[0];
	}
}

