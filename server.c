#include <stdio.h>
#include <errno.h>
#include <string.h>


#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/file.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <pthread.h>

#include "util.h"
#include "oracle.h"
#include "socket_rw.h"
#include "server.h"

char sDaemonInitDir[256];
char sLogInitDir[256];
char sErrInitDir[256];
char sCfgFileName[256];
char sLogFileName[256];
char sErrFileName[256];
int  SPNodeID;

servcfg serverinfo;

void printBuffer(char* pBuffer, int dwBufLen)
{
        int     nRowLen = 16;
        int i = 0;
        if (NULL == pBuffer)
                return;
        for (i = 0; i < dwBufLen; i++)
        {
                if (0 == i)
                {
                }
                else if( 0 == (i % nRowLen))
                {
                        printf("\r\n");
                }
                else if (0 == (i % (nRowLen / 2)))
                {
                        printf("    ");
                }
                printf(" %.2x", pBuffer[i]);
        }
        printf("\r\n\r\n");
}

void reaper(int sig)
{
  pid_t pid;
  int status;
  while((pid=waitpid(-1,&status,WNOHANG))>0||((-1==pid)&&(errno==EINTR)))
  {
    if(pid>0)
    {
       write_log(sLogFileName,"%s%d%s%d","child: ",pid," died: ",WEXITSTATUS(status));
    }
  }
  return;
}


void * ProcessSmgMsg(void *arg)
{
  SGIP *psgip = (SGIP *)arg;
  SGIP_HEADER *psgip_header_body = NULL;
  SGIP_DELIVER_BODY sgip_deliver_body;
  SGIP_DELIVER_RESP_BODY sgip_deliver_resp_body;
  SGIP_BIND_BODY sgip_bind_body;
  SGIP_BIND_RESP_BODY sgip_bind_resp_body;
  SGIP_REPORT_BODY sgip_report_body;
  SGIP_REPORT_RESP_BODY sgip_report_resp_body;
  
  psgip_header_body = psgip->getSgipHeader();
  switch(psgip_header_body->Command_Id)
  {
    case SGIP_BIND:
      write_log(sLogFileName,"%s","receive SGIP_BIND msg from smg");
      memset((char *)&sgip_bind_body, 0, sizeof(sgip_bind_body));
      psgip->SGIP_BIND_Recv(&sgip_bind_body);
      //abort smg auth
      memset((char *)&sgip_bind_resp_body, 0, sizeof(sgip_bind_resp_body));
      sgip_bind_resp_body.Result = 0;
      if(psgip->SGIP_BIND_RESP_Send(&sgip_bind_resp_body)!=0)
      {
        write_log(sLogFileName,"%s","send SGIP_BIND_RESP failed");
      }
      break;
    
    case SGIP_DELIVER:
      write_log(sLogFileName,"%s","receive SGIP_DELIVER msg from smg");
      memset((char *)&sgip_deliver_body, 0, sizeof(sgip_deliver_body));
      psgip->SGIP_DELIVER_Recv(&sgip_deliver_body);
      char tmpbuf[1024];
      memcpy(tmpbuf,(char *)&sgip_deliver_body,sizeof(sgip_deliver_body));
      printBuffer(tmpbuf,sizeof(sgip_deliver_body));
      memset((char *)&sgip_deliver_resp_body, 0, sizeof(sgip_deliver_resp_body));
      sgip_deliver_resp_body.Result = 0;
      if(psgip->SGIP_DELIVER_RESP_Send(&sgip_deliver_resp_body)!=0)
      {
        write_log(sLogFileName, "%s", "send SGIP_DELIVER_RESP failed");
      }
      process_deliver(&sgip_deliver_body);
      break;
    
    case SGIP_REPORT:
      //write_log(sLogFileName, "%s", "receive SGIP_REPORT msg from smg");
      memset((char *)&sgip_report_body, 0, sizeof(sgip_report_body));
      psgip->SGIP_REPORT_Recv(&sgip_report_body);
      memset((char *)&sgip_report_resp_body, 0, sizeof(sgip_report_resp_body));
      sgip_report_resp_body.Result = 0;
      if(psgip->SGIP_REPORT_RESP_Send(&sgip_report_resp_body)!=0)
      {
        write_log(sLogFileName,"%s","send SGIP_REPORT_RESP failed");
      }
      break;
    
    default:
      write_log(sLogFileName,"receive UNKONOWN msg from smg!msg code:%d", psgip_header_body->Command_Id);
      break;
  }    
  
  pthread_exit(NULL); 
}

int ReadConfigInfo()
{
  char config_str[32];
  DB_INFO db_info;
  DB_QUERY_INFO db_query_info;

  strcpy(sCfgFileName,CONF_FILE_NAME);
  if(access(sCfgFileName, R_OK|W_OK|F_OK)==-1)
  {
    printf("\n%s %s\n",sCfgFileName,"doesn't exist, program exit!\n");
    return -1;
  }

  //read config info
  if(read_config_string(sCfgFileName,"DAEMONDIR",sDaemonInitDir)!=0)
  {
    strcpy(sDaemonInitDir,DAEMON_INIT_DIR);
  }
  if(access(sDaemonInitDir, F_OK)!=0)
  {
    if(mkdir(sDaemonInitDir,0700)!=0)
    {
      printf("\ndaemon dir:%s created failed, program exit!\n",sDaemonInitDir);
      return -1;
    }
  }
  
  if(read_config_string(sCfgFileName,"LOGDIR",sLogInitDir)!=0)
  {
    strcpy(sLogInitDir,LOG_INIT_DIR);
  }
  if(access(sLogInitDir, F_OK)!=0)
  {
    if(mkdir(sLogInitDir,0700)!=0)
    {
      printf("\nlog dir:%s created failed, program exit!\n",sLogInitDir);
      return -1;
    }
  }

  if(read_config_string(sCfgFileName,"ERRDIR",sErrInitDir)!=0)
  {
    strcpy(sErrInitDir,ERR_INIT_DIR);
  }
  if(access(sErrInitDir, F_OK)!=0)
  {
    if(mkdir(sErrInitDir,0700)!=0)
    {
      printf("\nerr dir:%s created failed, program exit!\n",sErrInitDir);
      return -1;
    }
  }
 
  if(read_config_string(sCfgFileName,"LOGFILE",sLogFileName)!=0)
  {
    strcpy(sLogFileName,LOG_FILE_NAME);
  }

  if(read_config_string(sCfgFileName,"ERRFILE",sErrFileName)!=0)
  {
    strcpy(sErrFileName,ERR_FILE_NAME);
  }
 
  memset((char *)&serverinfo,0,sizeof(serverinfo));
  //read database config info
  if(read_config_string(sCfgFileName,"DBNAME",serverinfo.DBName)!=0)
  {
    printf("\n%s%s\n",sCfgFileName," doesn't have DBNAME, program exit!");
    return -1;
  }
  if(read_config_string(sCfgFileName,"DBUSER",serverinfo.DBUser)!=0)
  {
    printf("\n%s%s\n",sCfgFileName," doesn't have DBUSER, program exit!");
    return -1;
  }
  if(read_config_string(sCfgFileName,"DBPASSWORD",serverinfo.DBPassword)!=0)
  {
    printf("\n%s%s\n",sCfgFileName," doesn't have DBPASSWORD, program exit!");
    return -1;
  }
  //verify database connect success
  memset((char *)&db_info,0,sizeof(db_info));
  memset((char *)&db_query_info,0,sizeof(db_query_info));
  if(db_init(&db_info)!=0)
  {
    printf("\n%s\n","**ORACLE DATABASE OCI Env Init Failed, program exit!***");
    return -1;
  } 
  if(db_connect(&db_info,serverinfo.DBName,serverinfo.DBUser,serverinfo.DBPassword)!=TRUE)
  {
    printf("\n%s\n","***ORACLE DATABASE OCI Connect Failed, program exit!***");
    db_exit(&db_info);
    return -1;
  }
  db_close(&db_info);
  db_exit(&db_info);
  
  //read self bind address and port info
  if(read_config_string(sCfgFileName,"SELFIP",serverinfo.SelfIP)!=0)
  {
    strcpy(serverinfo.SelfIP,"INADDR_ANY");
  }
  if(read_config_string(sCfgFileName,"SELFPORT",config_str)!=0)
  {
    serverinfo.SelfPort = 0;
  }
  else
  {
    serverinfo.SelfPort = atoi(config_str);
  }
  
  //read SMG Config Info
  if(read_config_string(sCfgFileName,"SPNUMBER",serverinfo.SPNumber)!=0)
  {
    printf("\n%s%s\n",sCfgFileName," doesn't have SPNUMBER, program exit!");
    return -1;
  }
  if(read_config_string(sCfgFileName,"SPCORPID",serverinfo.SPCorpID)!=0)
  {
    printf("\n%s%s\n",sCfgFileName," doesn't have SPCORPID, program exit!");
    return -1;
  }
  SPNodeID = 300000 + atoi(serverinfo.SPCorpID);
  printf("nid=%d\n",SPNodeID);
  if(read_config_string(sCfgFileName,"SMGIP",serverinfo.SMG_IP)!=0)
  {
    strcpy(serverinfo.SMG_IP,"220.195.192.85");
  } 
  if(read_config_string(sCfgFileName,"MTPORT",config_str)==0)
  {
    serverinfo.MT_Port = atoi(config_str);
  }
  else
  {
    serverinfo.MT_Port = 8801;
  }
  if(read_config_string(sCfgFileName,"MTBINDUSER",serverinfo.MT_Bind_User)!=0)
  {
    printf("\n%s%s\n",sCfgFileName," doesn't have MTBINDUSER, program exit!");
    return -1;
  } 
  if(read_config_string(sCfgFileName,"MTBINDPASSWORD",serverinfo.MT_Bind_Password)!=0)
  {
    printf("\n%s%s\n",sCfgFileName," doesn't have MTBINDPASSWORD, program exit!");
    return -1;
  }

  if(read_config_string(sCfgFileName,"MOIP",serverinfo.MO_IP)!=0)
  {
    strcpy(serverinfo.MO_IP,"INADDR_ANY");
  } 
  if(read_config_string(sCfgFileName,"MOPORT",config_str)==0)
  {
    serverinfo.MO_Port = atoi(config_str);
  }
  else
  {
    serverinfo.MO_Port= 5188;
  }
  if(read_config_string(sCfgFileName,"MOBINDUSER",serverinfo.MO_Bind_User)!=0)
  {
    printf("\n%s%s\n",sCfgFileName," doesn't have MOBINDUSER, program exit!");
    return -1;
  }
  if(read_config_string(sCfgFileName,"MOBINDPASSWORD",serverinfo.MO_Bind_Password)!=0)
  {
    printf("\n%s%s\n",sCfgFileName," doesn't have MOBINDPASSWORD, program exit!");
    return -1;
  }
  
  return 0;
}

void PrintConfigInfo()
{
  printf("\n*** Print Config Info  ***\n");
  printf("***DAEMONDIR=%s***\n",sDaemonInitDir);
  printf("***LOGFILENAME=%s***\n",sLogFileName);
  printf("***ERRFILENAME=%s***\n",sErrFileName);
  printf("***DBNAME=%s***\n",serverinfo.DBName);
  printf("***DBUSER=%s***\n",serverinfo.DBUser);  
  printf("***DBPASSWORD=%s***\n",serverinfo.DBPassword);
  printf("***SELFIP=%s***\n",serverinfo.SelfIP);
  printf("***SELFPORT=%d***\n",serverinfo.SelfPort);
  printf("***SMGIP=%s***\n",serverinfo.SMG_IP);
  printf("***MTPORT=%d***\n",serverinfo.MT_Port);
  printf("***SPNUMBER=%s***\n",serverinfo.SPNumber);
  printf("***SPCORPID=%s***\n",serverinfo.SPCorpID);
  printf("***MTBINDUSER=%s***\n",serverinfo.MT_Bind_User);
  printf("***MTBINDPASSWORD=%s***\n",serverinfo.MT_Bind_Password); 
  printf("***MOIP=%s***\n",serverinfo.MO_IP);
  printf("***MOPORT=%d***\n",serverinfo.MO_Port);
  printf("***MOBINDUSER=%s***\n",serverinfo.MO_Bind_User);
  printf("***MOBINDPASSWORD=%s***\n",serverinfo.MO_Bind_Password); 
  printf("*****************************\n");    
}

int init_sgip(SGIP **psgip, int *psockfd)
{
  SGIP_HEADER sgip_header_body;
  SGIP_BIND_BODY sgip_bind_body;
  SGIP_BIND_RESP_BODY sgip_bind_resp_body;
  SGIP_SUBMIT_BODY sgip_submit_body;

  *psockfd = tcpip_connect_to_server(serverinfo.SMG_IP, serverinfo.MT_Port);
  if(*psockfd<0)
  {
    write_log(sErrFileName, "connect smg failed,error:%s", strerror(errno));
    return -1;
  }
  
  printf("SMGIP=%s,MTPort=%d\n",serverinfo.SMG_IP,serverinfo.MT_Port);

  *psgip = new SGIP(*psockfd,SMGID,NATIONALCODE,SPNodeID,serverinfo.SPNumber);
  if(*psgip==NULL)
  {
    write_log(sErrFileName, "%s", "alocate SGIP memory failed");
    return -1;
  }
 
  /*send BIND message*/
  memset((char *)&sgip_bind_body, 0, sizeof(sgip_bind_body));
  sgip_bind_body.Login_Type = 1;
  strcpy(sgip_bind_body.Login_Name,serverinfo.MT_Bind_User);
  strcpy(sgip_bind_body.Login_Password,serverinfo.MT_Bind_Password);
  if((*psgip)->SGIP_BIND_Send(&sgip_bind_body)!=0)
  {
    write_log(sErrFileName, "%s", "send SGIP failed");
    return -1;
  }

  /*read BINDRESP message*/
  memset((char *)&sgip_header_body, 0, sizeof(sgip_header_body));
  memset((char *)&sgip_bind_resp_body, 0, sizeof(sgip_bind_resp_body));
  sgip_bind_resp_body.Result = 1;
  if((*psgip)->SGIP_HeaderRecv(&sgip_header_body)!=0)
  {
    write_log(sErrFileName,"%s","receive BINDRESP error");
    return -1;
  }

  (*psgip)->SGIP_BIND_RESP_Recv(&sgip_bind_resp_body);
  if(sgip_bind_resp_body.Result!=0)
  {
    write_log(sErrFileName,"BIND failed,Result=%d",sgip_bind_resp_body.Result);
    return -1;
  }
 
  return 0;
}

void close_sgip(SGIP *psgip, int *psockfd)
{
  close(*psockfd);

  if(psgip!=NULL)
  {
    delete psgip;
    psgip = NULL;
  }
}

int send_sms(char *mobile, char *content, char *servicetype, SGIP *psgip, char *SendSPNumber)
{
  SGIP_SUBMIT_BODY sgip_submit_body;
  SGIP_SUBMIT_RESP_BODY sgip_submit_resp_body;
  SGIP_HEADER sgip_header_body;
  char tstr[6];

  if(psgip==NULL)
    write_log(sLogFileName, "null");
  /*send SUBMIT message*/
  if(SendSPNumber!=NULL)
  {
    strcpy(sgip_submit_body.SPNumber,SendSPNumber);
  }
  else
  {
    strcpy(sgip_submit_body.SPNumber,serverinfo.SPNumber);
  }
  strcpy(sgip_submit_body.ChargeNumber,FREECHARGENUMBER);
  sgip_submit_body.UserCount = 1;
  substring(mobile,tstr,0,2);
  if(strncmp(tstr,"86",2)==0)
  {
    strcpy(sgip_submit_body.UserNumber,mobile);
  }
  else
  {
    strcpy(sgip_submit_body.UserNumber,"86");
    strcat(sgip_submit_body.UserNumber,mobile);
  }
  strcpy(sgip_submit_body.CorpID,serverinfo.SPCorpID);
  strcpy(sgip_submit_body.ServiceType,servicetype);
  sgip_submit_body.FeeType =0;
  strcpy(sgip_submit_body.FeeValue,"0");
  strcpy(sgip_submit_body.GivenValue,"0");
  sgip_submit_body.AgentFlag = 1;
  sgip_submit_body.MorelatetoMTFlag = 1;
  sgip_submit_body.Priority = 9;
  strcpy(sgip_submit_body.ExpireTime,"");
  strcpy(sgip_submit_body.ScheduleTime,"");
  sgip_submit_body.ReportFlag = 1;
  sgip_submit_body.TP_pid = 0;
  sgip_submit_body.TP_udhi = 0;     
  sgip_submit_body.MessageCoding = 15; 
  sgip_submit_body.MessageType = 0;
  strcpy(sgip_submit_body.MessageContent,content);
  sgip_submit_body.MessageLength = strlen(sgip_submit_body.MessageContent); 
  strcpy(sgip_submit_body.Reserve,"");

  if(psgip->SGIP_SUBMIT_Send(&sgip_submit_body)!=0)
  {
    write_log(sErrFileName, "%s", "sendsms send SGIP_SUBMIT failed");
    return -1;
  }

  /*read SUBMITRESP message*/
  sgip_submit_resp_body.Result = 5;
  if(psgip->SGIP_HeaderRecv(&sgip_header_body)!=0)
  {
    write_log(sErrFileName, "%s", "sendsms receive SGIP_SUBMIT_RESP failed");
    return -1;
  }
  psgip->SGIP_SUBMIT_RESP_Recv(&sgip_submit_resp_body);
  if(sgip_submit_resp_body.Result!=0)
  {
    write_log(sErrFileName, "sendms SGIP_SUBMIT_RESP result error,code:%d",sgip_submit_resp_body.Result);
    return -1;
  }
 
  return 0;  
}

int main()
{
  int sockfd;
  char msg[256];

  /*error when open the lock file.*/
  if(!IsProcConflict("server"))
  {
    printf("\nserver already Run!\n");
    exit(0);
  } 

  /*read config info*/
  memset((char *)&serverinfo,0,sizeof(serverinfo));
  if(ReadConfigInfo()<0)
  {
    exit(-1);
  }

  PrintConfigInfo();

  if(daemon_init(sDaemonInitDir)<0)
  {
    printf("%s\n","daemon init failed!");
    exit(1);
  }
  
  sockfd = make_server_socket(serverinfo.MO_Port);
  if(sockfd<0)
  {
    sprintf(msg,"create server socket server failed:%s",strerror(errno));
    write_log(sLogFileName,"%s",msg);
    exit(1);
  }
 
  printf("\n/***Server Start Success!***/\n"); 
  write_log(sLogFileName,"%s","server start success!");

  signal(SIGCHLD, reaper);

  //MO服务进程启动：处理用户开户、销户和用户指令交互
  MOServerProcess(sockfd);

  return 0;
}


void MOServerProcess(int sockfd)
{
  int addrlen;
  struct sockaddr_in cliaddr;
  int cfd;
  char cliip[32];

  addrlen = sizeof(struct sockaddr);
  while(1)
  {
    signal(SIGCHLD, reaper);
    cfd = accept(sockfd,(struct sockaddr *)&cliaddr,(socklen_t *)&addrlen);
    if((cfd<0)&&(errno==EWOULDBLOCK||errno==ECONNABORTED||errno==EPROTO||errno==EINTR))
    {
      write_log(sErrFileName,"%s","moserver accept error!");
      continue; 
    }
    strcpy(cliip,inet_ntoa(cliaddr.sin_addr));
    if(strcmp(cliip,serverinfo.SMG_IP)!=0)
    {
      write_log(sErrFileName,"msg isn't from smg,from ip:%s,abort this msg!",cliip);
      close(cfd);
      continue;
    }

    if(fork()==0)
    {
      pthread_t thread;
      fd_set rfds;
      int maxfd,retval;
      struct timeval tv;
      SGIP *psgip = NULL;
      SGIP_HEADER sgip_header_body;
 
      close(sockfd);
      pthread_create( &thread,NULL,active_sms,NULL);
      pthread_detach(thread);
      int flags = fcntl(cfd,F_GETFL,0);
      if(flags&O_NONBLOCK)
      {
        fcntl(cfd,F_SETFL,flags-O_NONBLOCK);
        write_log(sLogFileName,"%s","BLOCK!!!");
        exit(0);
        continue;
      }
      psgip = new SGIP(cfd,SMGID,NATIONALCODE,SPNodeID,serverinfo.SPNumber); 
      if(psgip==NULL)
      {
        write_log(sErrFileName,"%s","allocate SGIP memory failed, exit child!");
        close(cfd);
        exit(-1);
      }
      signal(SIGCLD,SIG_IGN);

      while(1)
      {
        memset((char *)&rfds, 0, sizeof(rfds));
        FD_SET(cfd,&rfds);
        maxfd = cfd;
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        retval = select(maxfd+1, &rfds, NULL,NULL, &tv);
        if(retval==-1)
        {
          write_log(sErrFileName,"select error! ERR:%s",strerror(errno));
          close(cfd);
          exit(-1);
        }
        else if(retval==0)
        {
          //write_log(sLogFileName,"%s","select time out!no message from smg!");
          continue;
        }
        else
        {
          if(FD_ISSET(cfd,&rfds))
          {
            retval = psgip->SGIP_HeaderRecv(&sgip_header_body);
            if(retval!=0)
            {
              write_log(sErrFileName, "SGIP receive data from msg error!retval=%d,error:%s",retval,strerror(errno));
              delete psgip;
              psgip = NULL;
              close(cfd);
              exit(-1);  
            }
            //close socket and exit child
            if(sgip_header_body.Command_Id==SGIP_UNBIND)
            {
              write_log(sLogFileName, "%s", "receive SGIP_UNBIND msg from smg");
              psgip->SGIP_UNBIND_RESP_Send();
              delete psgip;
              psgip = NULL;
              close(cfd); 
              exit(9);
            }
            //printf("id=%d\n",sgip_header_body.Command_Id); 
            pthread_t lthread;
            if(pthread_create(&lthread,NULL,ProcessSmgMsg,(void *)psgip)!=0)
            {
              write_log(sErrFileName,"SMGMSG msgcode:%x, THREAD Create Failed!",\
		      sgip_header_body.Command_Id);
              continue;
            }
            pthread_detach(lthread); 
          }//if FD
        }//else
      }//while  
      exit(9);
    }//if fork
    //else 
      //close(cfd);
    
  }//while
 
}

int process_deliver(SGIP_DELIVER_BODY *pdeliverbody)
{
  char str[256],mobile[16],password[16],content[256],spnumber[16];
  int retval = -1;
  UserInfo userinfo;
  UserInfoHis userinfohis;
  SGIP *psgip = NULL;
  int tsockfd;

  write_log(sLogFileName,"receive sms coding:%d,mobile:%s\n", pdeliverbody->MessageCoding,pdeliverbody->UserNumber);
  
  strcpy(str,pdeliverbody->MessageContent);
  upper_case(str);
  substring(pdeliverbody->UserNumber,mobile,0,11);

  if(strcmp(str,"KTZL")==0)//KTZL是业务的短信开通指令
  {
    //insert user order into database
    memset((char *)&userinfo,0,sizeof(userinfo));
    strncpy(userinfo.mobile,mobile,strlen(mobile));
    retval = GetUserInfo(userinfo);
    if(retval<0)
    {
      //send register failed sms

      return -1;
    }
    else if(retval==RECORD_EXIST)
    {
      //send user has been registed 
      switch(userinfo.service[0])
      {
        case 'Y':
          write_log(sLogFileName,"%s 已经注册过XX业务!",mobile);
          //给用户发送已经定购XX业务的短信提醒
          sprintf(content,"%s","您已经定购过XX业务业务!");
          init_sgip(&psgip, &tsockfd);
          send_sms(mobile, content, FREESERVICETYPE, psgip);
          close_sgip(psgip, &tsockfd);
          break;

        case 'N'://开通过其他业务的一种
          userinfo.service[0]='Y';
          userinfo.care_regtype[0]='S';
          get_full_time(userinfo.service_date);
          retval = UpdateUserInfo(userinfo);//UpdateUserInfo函数负责修改用户的产品订购状态，retval=0表示成功，其他表示失败
          if(retval==0)
          {
            write_log(sLogFileName,"%s开通XX业务业务成功(已开通过其他业务)！",mobile);
          }
          else
          {
            write_log(sLogFileName,"%s开通XX业务业务失败，号码:%s,代码:%d (已开通过其他业务)!",mobile,retval);
          }
          break;

        case 'P'://前台小代理人预开通
          userinfo.service[0]='Y';
          retval = UpdateUserInfo(userinfo);
          if(retval==0)
          {
            write_log(sLogFileName,"%s通过小代理人预开通的XX业务正式开通",mobile);
          }
          else
          {
            write_log(sLogFileName,"%s通过小代理人预开通的XX业务正式开通时失败，错误代码:%d",mobile,retval);
          }
          break;

        case 'T'://体验营销
          //密码不修改
          userinfo.service[0]='Y';
          if(userinfo.care_regtype[0]=='H')
          {
            userinfo.care_regtype[0] = 'S';
          }
          retval = UpdateUserInfo(userinfo);
          if(retval==0)
          {
            write_log(sLogFileName,"%s后台批开体验的XX业务正式开通成功",mobile);
         }
          else
          {
            write_log(sLogFileName,"%s后台批开体验的XX业务开通时失败,错误代码:%d",mobile,retval);
          }
          break;

        default:
          write_log(sLogFileName,"%s 用户状态:%c错误!",mobile,userinfo.service[0]);
      }
      return 1;
    }
    else if(retval==RECORD_NOT_EXIST)
    {
      strcpy(userinfo.name,mobile);
      srand(time(NULL));
      sprintf(userinfo.password,"%06d",rand()%999999);
      userinfo.service[0]='Y';//经过VAC鉴权，不需要二次确认，直接插入生成定制关系
      userinfo.care_regtype[0]='S';
      retval=InsertCUserInfo(userinfo);
      if(retval==0)
      {
        write_log(sLogFileName,"%s开通XX业务业务成功(未开通过其他业务)！",mobile);
      }
      else
      {
        write_log(sLogFileName,"%s开通XX业务业务失败，号码:%s,代码:%d (未开通过其他业务)!",mobile,retval);
      }
    }
  }
  //取消指令
  else if(strcmp(str,"QXZL")==0)//QXZL是业务取消的短信指令
  {
    memset((char *)&userinfo,0,sizeof(userinfo));
    strncpy(userinfo.mobile,mobile,strlen(mobile));
    retval = GetUserInfo(userinfo);//GetUserInfo是获取用户状态的代码
    if(retval<0)
    {
      //用户未注册业务，此处添加用户取消业务失败的代码

      return -1;
    }
    else if(retval==RECORD_EXIST)
    {
      //cancel user register info
      memset((char *)&userinfohis,0,sizeof(userinfohis));
      strcpy(userinfohis.mobile,userinfo.mobile);
      strcpy(userinfohis.name,userinfo.name);
      userinfohis.kind[0] = 'C';
      userinfohis.regtype[0]=userinfo.care_regtype[0];
      strcpy(userinfohis.accept_date,userinfo.service_date);
      //此处添加用户取消业务的代码
			.............
    }
    else if(retval==RECORD_NOT_EXIST)
    {
      //send user register doesn't exist sms info
      sprintf(content,"%s","您未定购XX业务业务");
      init_sgip(&psgip, &tsockfd);
      send_sms(mobile, content, FREESERVICETYPE, psgip);
      close_sgip(psgip, &tsockfd);
      return 2;
    }
  }
  else if(strcmp(str,"0000")==0||strcmp(str,"00000")==0)//注销接入号码下面的全部业务
  {
    memset((char *)&userinfo,0,sizeof(userinfo));
    strncpy(userinfo.mobile,mobile,strlen(mobile));
    retval = GetUserInfo(userinfo);
    if(retval==RECORD_EXIST)
    {
       //cancel user register info
      memset((char *)&userinfohis,0,sizeof(userinfohis));
      strcpy(userinfohis.mobile,userinfo.mobile);
      strcpy(userinfohis.name,userinfo.name);

      //此处添加取消所有业务的代码
      ..........
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
  
  return 0;
}

void *active_sms(void* sig)
{
  int sockfd;
  SGIP_HEADER sgip_header_body;
  SGIP_BIND_BODY sgip_bind_body;
  SGIP_BIND_RESP_BODY sgip_bind_resp_body;
  SGIP_SUBMIT_BODY sgip_submit_body;
  SGIP_SUBMIT_RESP_BODY sgip_submit_resp_body;
  char mobile[16],tstr[8];
  char content[32];
  SGIP *psgip = NULL;

  strcpy(mobile, "8613018982331");
  strcpy(content, "active sms test");
  while(1)
  {
    //write_log(sLogFileName,"%s","ACTIVE SMS TEST!");
    sockfd = tcpip_connect_to_server(serverinfo.SMG_IP, serverinfo.MT_Port);
    if(sockfd<0)
    {
      write_log(sErrFileName, "connect smg failed,error:%s", strerror(errno));
      goto ACTIVESMSEXIT;
    } 
    psgip = new SGIP(sockfd,SMGID,NATIONALCODE,SPNodeID,serverinfo.SPNumber);
    if(psgip==NULL)
    {
      write_log(sErrFileName, "%s", "alocate SGIP memory failed");
      goto ACTIVESMSEXIT;
    }

    /*send BIND message*/
    memset((char *)&sgip_bind_body, 0, sizeof(sgip_bind_body));
    sgip_bind_body.Login_Type = 1;
    strcpy(sgip_bind_body.Login_Name,serverinfo.MT_Bind_User);
    strcpy(sgip_bind_body.Login_Password,serverinfo.MT_Bind_Password);
    if(psgip->SGIP_BIND_Send(&sgip_bind_body)!=0)
    {
      write_log(sErrFileName, "%s", "send SGIP failed");
      goto ACTIVESMSEXIT;
    }

    /*read BINDRESP message*/
    memset((char *)&sgip_header_body, 0, sizeof(sgip_header_body));
    memset((char *)&sgip_bind_resp_body, 0, sizeof(sgip_bind_resp_body));
    sgip_bind_resp_body.Result = 1;
    if(psgip->SGIP_HeaderRecv(&sgip_header_body)!=0)
    {
      write_log(sErrFileName,"%s","receive BINDRESP error");
      goto ACTIVESMSEXIT;
    }

    psgip->SGIP_BIND_RESP_Recv(&sgip_bind_resp_body);
    if(sgip_bind_resp_body.Result!=0)
    {
      write_log(sErrFileName,"BIND failed,Result=%d",sgip_bind_resp_body.Result);
      goto ACTIVESMSEXIT;
    }

    /*send SUBMIT message*/
    strcpy(sgip_submit_body.SPNumber,serverinfo.SPNumber);
    strcpy(sgip_submit_body.ChargeNumber,FREECHARGENUMBER);
    sgip_submit_body.UserCount = 1;
    substring(mobile,tstr,0,2);
    if(strncmp(tstr,"86",2)==0)
    {
      strcpy(sgip_submit_body.UserNumber,mobile);
    }
    else
    {
      strcpy(sgip_submit_body.UserNumber,"86");
      strcat(sgip_submit_body.UserNumber,mobile);
    }
    strcpy(sgip_submit_body.CorpID,serverinfo.SPCorpID);
    strcpy(sgip_submit_body.ServiceType,FREESERVICETYPE);
    sgip_submit_body.FeeType =0;
    strcpy(sgip_submit_body.FeeValue,"0");
    strcpy(sgip_submit_body.GivenValue,"0");
    sgip_submit_body.AgentFlag = 1;
    sgip_submit_body.MorelatetoMTFlag = 1;
    sgip_submit_body.Priority = 9;
    strcpy(sgip_submit_body.ExpireTime,"");
    strcpy(sgip_submit_body.ScheduleTime,"");
    sgip_submit_body.ReportFlag = 1;
    sgip_submit_body.TP_pid = 0;
    sgip_submit_body.TP_udhi = 0;
    sgip_submit_body.MessageCoding = 15;
    sgip_submit_body.MessageType = 0;
    strcpy(sgip_submit_body.MessageContent,content);
    sgip_submit_body.MessageLength = strlen(sgip_submit_body.MessageContent);
    strcpy(sgip_submit_body.Reserve,"");
 
    if(psgip->SGIP_SUBMIT_Send(&sgip_submit_body)!=0)
    {
      write_log(sErrFileName, "%s", "sendsms send SGIP_SUBMIT failed");
      goto ACTIVESMSEXIT;
    }

    /*read SUBMITRESP message*/
    sgip_submit_resp_body.Result = 5;
    if(psgip->SGIP_HeaderRecv(&sgip_header_body)!=0)
    {
      write_log(sErrFileName, "%s", "sendsms receive SGIP_SUBMIT_RESP failed");
      goto ACTIVESMSEXIT;
    }
    psgip->SGIP_SUBMIT_RESP_Recv(&sgip_submit_resp_body);
    if(sgip_submit_resp_body.Result!=0)
    {
      write_log(sErrFileName, "sendms SGIP_SUBMIT_RESP result error,code:%d",sgip_submit_resp_body.Result);
      goto ACTIVESMSEXIT;
    }
    
    psgip->SGIP_UNBIND_Send();
    close(sockfd); 
    delete psgip;
    psgip = NULL;
     
    sleep(1);
  }

ACTIVESMSEXIT:
  write_log(sErrFileName,"%s","exit active sms thread");
  close_sgip(psgip, &sockfd);
  pthread_exit(NULL);
}
