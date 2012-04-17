#ifndef _DXGJ_SGIP_SERVER_H_
#define _DXGJ_SGIP_SERVER_H_

#include "sgip.h" 

#define DAEMON_INIT_DIR 	"./"
#define LOG_INIT_DIR		"./log"
#define ERR_INIT_DIR		"./err"
#define CONF_FILE_NAME 		"./server.cfg"
#define LOG_FILE_NAME 		"./log/server.log"
#define ERR_FILE_NAME		"./err/server.err"

#define SMGID			30551
#define NATIONALCODE		"86"
#define FREECHARGENUMBER	"000000000000000000000"
#define FREESERVICETYPE		"YXBZ"

#define CONNECTED		0
#define CONNTESTING		1
#define DISCONNECTED		-1

typedef struct
{
  char		SelfIP[32];
  int		SelfPort;
  char          DBName[16];
  char          DBUser[16];
  char          DBPassword[16];
  char          SPNumber[21];
  char          SPCorpID[6];
  char          MO_IP[32];
  int           MO_Port;
  char          MO_Bind_User[16];
  char          MO_Bind_Password[16];
  char          SMG_IP[32];
  int           MT_Port;
  char          MT_Bind_User[16];
  char          MT_Bind_Password[16];
}servcfg;

void * ProcessSmgMsg(void *arg);
void ShowVerInfo();
int ReadConfigInfo();
void PrintConfigInfo();
void reaper(int sig);
int init_sgip(SGIP **psgip, int *psockfd);
void close_sgip(SGIP *psgip, int *psockfd);
int send_sms(char *mobile, char *content, char *servicetype, SGIP *psgip, char *SendSPNumber=NULL);
void *active_sms(void *sig);
int process_deliver(SGIP_DELIVER_BODY *pdeliverbody);
void MOServerProcess(int sockfd);
void printBuffer(char* pBuffer, int dwBufLen);

#endif
