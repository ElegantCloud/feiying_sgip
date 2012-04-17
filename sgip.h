#ifndef _SGIP_H_
#define _SGIP_H_

#include "util.h"
#include "socket_rw.h"
#include "common.h"
#include "protocol.h"

// Command ID
#define SGIP_BIND	  	0x00000001
#define SGIP_BIND_RESP 		0x80000001
#define SGIP_UNBIND	  	0x00000002
#define SGIP_UNBIND_RESP	0x80000002
#define SGIP_SUBMIT		0x00000003
#define SGIP_SUBMIT_RESP	0x80000003
#define SGIP_DELIVER		0x00000004
#define SGIP_DELIVER_RESP	0x80000004
#define SGIP_REPORT             0x00000005
#define SGIP_REPORT_RESP        0x80000005
#define SGIP_ADDSP              0x00000006
#define SGIP_ADDSP_RESP         0x80000006
#define SGIP_MODIFYSP	        0x00000007
#define SGIP_MODIFYSP_RESP      0x80000007
#define SGIP_DELETESP           0x00000008
#define SGIP_DELETESP_RESP      0x80000008
#define SGIP_QUERYROUTE         0x00000009
#define SGIP_QUERYROUTE_RESP    0x80000009
#define SGIP_ADDTELESEG         0x0000000a
#define SGIP_ADDTELESEG_RESP    0x8000000a
#define SGIP_MODIFYTELESEG      0x0000000b
#define SGIP_MODIFYTELESEG_RESP 0x8000000b
#define SGIP_DELETETELESEG      0x0000000c
#define SGIP_DELETETELESEG_RESP 0x8000000c
#define SGIP_ADDSMG             0x0000000d
#define SGIP_ADDSMG_RESP        0x8000000d
#define SGIP_MODIFYSMG          0x0000000e
#define SGIP_MODIFYSMG_RESP     0x8000000e
#define SGIP_DELETESMG          0x0000000f
#define SGIP_DELETESMG_RESP     0x8000000f
#define SGIP_CHECKUSER          0x00000010
#define SGIP_CHECKUSER_RESP     0x80000010
#define SGIP_USERRPT            0x00000011
#define SGIP_USERRPT_RESP       0x80000011
#define SGIP_TRACE              0x00001000
#define SGIP_TRACE_RESP         0x80001000 
  

// Header Length
#define LEN_SGIP_HEADER			20

// Body Length
#define LEN_SGIP_BIND			41
#define LEN_SGIP_BIND_RESP		9
#define LEN_SGIP_UNBIND			0
#define LEN_SGIP_UNBIND_RESP		0
#define LEN_SGIP_SUBMIT			123	// + 21*User_Count + Message_Length
#define LEN_SGIP_SUBMIT_RESP		9
#define LEN_SGIP_DELIVER		57	// + Message_Length
#define LEN_SGIP_DELIVER_RESP		9
#define LEN_SGIP_REPORT         	44
#define LEN_SGIP_REPORT_RESP    	9 
#define LEN_SGIP_ADDSP          	50
#define LEN_SGIP_ADDSP_RESP     	9
#define LEN_SGIP_MODIFYSP       	81
#define LEN_SGIP_MODIFYSP_RESP  	9
#define LEN_SGIP_DELETESP       	45
#define LEN_SGIP_DELETESP_RESP 	 	9
#define LEN_SGIP_QUERYROUTE     	40
#define LEN_SGIP_QUERYROUTE_RESP 	5 // + 87*Count
#define LEN_SGIP_ADDTELESEG      	26
#define LEN_SGIP_ADDTELESEG_RESP 	9
#define LEN_SGIP_MODIFYTELESEG   	33
#define LEN_SGIP_MODIFYTELESEG_RESP 	9
#define LEN_SGIP_DELETETELESEG    	21
#define LEN_SGIP_DELETETELESEG_RESP 	9
#define LEN_SGIP_ADDSMG           	50
#define LEN_SGIP_ADDSMG_RESP      	9
#define LEN_SGIP_MODIFYSMG        	56
#define LEN_SGIP_MODIFYSMG_RESP   	9
#define LEN_SGIP_DELETESMG        	14
#define LEN_SGIP_DELETESMG_RESP   	9
#define LEN_SGIP_CHECKUSER        	61
#define LEN_SGIP_CHECKUSER_RESP   	10
#define LEN_SGIP_USERRPT          	51
#define LEN_SGIP_USERRPT_RESP     	9
#define LEN_SGIP_TRACE            	41
#define LEN_SGIP_TRACE_RESP       	1// + 47*Count

#define SGIP_MAX_MES_LEN        LEN_SGIP_SUBMIT+2100+MAXLENGTH

typedef struct 
{
	unsigned int Message_Length;
	unsigned int Command_Id;
	unsigned int Sequence_Number[3];
}SGIP_HEADER;
 
typedef struct 
{
	unsigned char Login_Type;
	char Login_Name[16+1];
	char Login_Password[16+1];
	char Reserve[8+1];
}SGIP_BIND_BODY;

typedef struct 
{
	unsigned char Result;
	char Reserve[8+1];
}SGIP_BIND_RESP_BODY;


typedef struct
{
	char SPNumber[21+1];
	char ChargeNumber[21+1];
	unsigned char UserCount;
	char UserNumber[2100];
	char CorpID[5+1];
	char ServiceType[10+1];
	unsigned char FeeType;
	char FeeValue[6+1];
	char GivenValue[6+1];
	unsigned char AgentFlag;
	unsigned char MorelatetoMTFlag;
	unsigned char Priority;
	char ExpireTime[16+1];
	char ScheduleTime[16+1];
	unsigned char ReportFlag;
	unsigned char TP_pid;
	unsigned char TP_udhi;
	unsigned char MessageCoding;
	unsigned char MessageType;
	unsigned int MessageLength;
	char MessageContent[MAXLENGTH];
	char Reserve[8+1];
}SGIP_SUBMIT_BODY;

typedef struct 
{
	unsigned char Result;
	char Reserve[8+1];
}SGIP_SUBMIT_RESP_BODY;
 
typedef struct 
{
	char UserNumber[21+1];
	char SPNumber[21+1];
	unsigned char TP_pid;
	unsigned char TP_udhi;
	unsigned char MessageCoding;
	unsigned int MessageLength;
	char MessageContent[MAXLENGTH];
	char Reserve[8+1];
}SGIP_DELIVER_BODY;
 
typedef struct
{
	unsigned char Result;
	char Reserve[8+1];
}SGIP_DELIVER_RESP_BODY;

typedef struct 
{
	unsigned int SubmitSequenceNumber[3];
	unsigned char ReportType;
	char UserNumber[21+1];
	unsigned char State;
	unsigned char ErrorCode;
	char Reserve[8+1];
}SGIP_REPORT_BODY;

typedef struct 
{
	unsigned char Result;
	char Reserve[8+1];
}SGIP_REPORT_RESP_BODY;

typedef struct 
{
	char SMGId[6+1];
	char SPNumber[21+1];
	char ServiceTag[10+1];
	char CorpId[5+1];
	char Reserve[8+1];
}SGIP_ADDSP_BODY;

typedef struct
{
	unsigned char Result;
	char Reserve[8+1];
}SGIP_ADDSP_RESP_BODY;

typedef struct
{
	char SMGId[6+1];
	char OldSPNumber[21+1];
	char OldServiceTag[10+1];
	char NewSPNumber[21+1];
	char NewServiceTag[10+1];
	char CorpId[5+1];
	char Reserve[8+1];
}SGIP_MODIFYSP_BODY;

typedef struct
{
	unsigned char Result;
	char Reserve[8+1];
}SGIP_MODIFYSP_RESP_BODY;

typedef struct
{
	char SMGId[6+1];
	char SPNumber[21+1];
	char ServiceTag[10+1];
	char Reserve[8+1];
}SGIP_DELETESP_BODY;

typedef struct
{
	unsigned char Result;
	char Reserve[8+1];
}SGIP_DELETESP_RESP_BODY;

typedef struct
{
	unsigned char QueryType;
	char Number[21+1];
	char ServiceTag[10+1];
	char Reserve[8+1];
}SGIP_QUERYROUTE_BODY;

typedef struct 
{
	unsigned char Type;
	char Number[21];
	char Mark[10];
	char Code[5];
	char SMGId[6];
	unsigned int SMGIP;
	char LoginUser[16];
	char Password[16];
	char Reserve[8];
}SGIP_ROUTEITEM;

typedef struct
{
	unsigned char Result;
	unsigned int Count;
	SGIP_ROUTEITEM Route_Result[20];	
}SGIP_QUERYROUTE_RESP_BODY;

typedef struct
{
	char SMGId[6+1];
	char TeleSeg[7+1];
	char TeleType[1+1];
	char AreaCode[4+1];
	char Reserve[8+1];
}SGIP_ADDTELESEG_BODY;

typedef struct 
{
	unsigned char Result;
	char Reserve[8+1];
}SGIP_ADDTELESEG_RESP_BODY;

typedef struct
{
	char SMGId[6+1];
	char OldTeleSeg[7+1];
	char NewTeleSeg[7+1];
	char NewTeleType[1+1];
	char NewAreaCode[4+1];
	char Reserve[8+1];
}SGIP_MODIFYTELESEG_BODY;

typedef struct 
{
	unsigned char Result;
	char Reserve[8+1];
}SGIP_MODIFYTELESEG_RESP_BODY;

typedef struct
{
	char SMGId[6+1];
	char TeleSeg[7+1];
	char Reserve[8+1];
}SGIP_DELETETELESEG_BODY;

typedef struct
{
	unsigned char Result;
	char Reserve[8+1];
}SGIP_DELETETELESEG_RESP_BODY;

typedef struct
{
	char SMGId[6+1];
	unsigned int SMGIP;
	char LoginName[16+1];
	char LoginPassword[16+1];
	char Reserve[8+1];
}SGIP_ADDSMG_BODY;

typedef struct 
{
	unsigned char Result;
	char Reserve[8+1];
}SGIP_ADDSMG_RESP_BODY;

typedef struct
{
	char OldSMGId[6+1];
	char NewSMGId[6+1];
	unsigned int SMGIP;
	char LoginName[16+1];
	char LoginPassword[16+1];
	char Reserve[8+1];
}SGIP_MODIFYSMG_BODY;

typedef struct
{
	unsigned char Result;
	char Reserve[8+1];
}SGIP_MODIFYSMG_RESP_BODY;

typedef struct
{
	char SMGId[6+1];
	char Reserve[8+1];
}SGIP_DELETESMG_BODY;

typedef struct
{
	unsigned char Result;
	char Reserve[8+1];
}SGIP_DELETESMG_RESP_BODY;

typedef struct
{
	char UserName[16+1];
	char Password[16+1];
	char UserNumber[21+1];
	char Reserve[8+1];
}SGIP_CHECKUSER_BODY;

typedef struct
{
	unsigned char Result;
	unsigned char Status;
	char Reserve[8+1];
}SGIP_CHECKUSER_RESP_BODY;

typedef struct
{
	char SPNumber[21+1];
	char UserNumber[21+1];
	unsigned char UserCondition;
	char Reserve[8+1];
}SGIP_USERRPT_BODY;

typedef struct
{
	unsigned char Result;
	char Reserve[8+1];
}SGIP_USERRPT_RESP_BODY;

typedef struct
{
	unsigned int SubmitSequenceNumber[3];
	char UserNumber[21+1];
	char Reserve[8+1];
}SGIP_TRACE_BODY;

typedef struct 
{
	unsigned char Result;
	char NodeId[6];
	char ReceiveTime[16];
	char SendTime[16];
	char Reserve[8];
}SGIP_TRACEITEM;

typedef struct
{
	unsigned char Count;
	SGIP_TRACEITEM Trace_Result[3];	
}SGIP_TRACE_RESP_BODY;

typedef enum
{
	SGIP_BYTE ,
    	SGIP_INT,
	SGIP_LONG,
	SGIP_STRING,
	SGIP_USERNUM,
	SGIP_CONTENT,
	SGIP_ROUTERESULT,
	SGIP_TRACERESULT
} SGIPTYPE;

    typedef struct
    {
    	SGIPTYPE Field_Type;
    	int Field_Length;
    	char Field_Name[25];
    }SGIP_FIELD;

    typedef struct 
    {
    	int Field_Count;
    	SGIP_FIELD *Fields;
    }SGIP_MSG_FIELD;

class SGIP
{
private:
    int m_sockfd;
    int m_timeout;
    unsigned int m_ipaddress;
    int m_bodylength;
    char m_buffer[sizeof(SGIP_SUBMIT_BODY)];
    char m_sockbuf[SOCKBUFLEN];
    int m_bufindex;
    unsigned int m_send_sequenceid[3];
    unsigned int m_recv_sequenceid[3];
    unsigned int m_smg_node_id, m_cp_smg_id;
    char m_national_code[21];
    char m_cp_phone[28], m_is_cp; 
    SGIP_HEADER m_header, curSgipHeader;
    unsigned int recv_seqno_buf[32], recv_seqno_index;

    int SGIP_BodyRecv(unsigned int commandid,void *body1,int bodylength);
    int SGIP_Send(unsigned int commandid,void *body,int bodylength, SGIP_HEADER *myheader = NULL);
    int SGIP_Generate_Header(char *buffer,SGIP_HEADER *header);
    void Generate_Sequence_Number(unsigned int *Sequence_Number);	
    unsigned int GetFieldLen(unsigned int length); 
    int IdtoIndex(unsigned int commandid, unsigned int *structlength);
    int CheckOneField(char *field);
    int CheckTimeFormat(char *src);
    int CheckInScope(char *src);
    int CheckSeqNum(unsigned int seqnum);
    int VerifyNumberLength(char *src);
    int VerifyNumberHeader(char *src);
    int CheckAllZero(char *src);
    int CheckPhoneNumberValid(char *src);
    int SeparateUserNumber(char *src);

    int SGIP_SUBMIT_Check(SGIP_SUBMIT_BODY *submit_body);
    int SGIP_DELIVER_Check(SGIP_DELIVER_BODY *deliver_body);
    int SGIP_REPORT_Check(SGIP_REPORT_BODY *report_body);

    int storePackFlag;
    char bufPackage[SGIP_MAX_MES_LEN];
    unsigned int packCmdId;
    int packLength;
public:
    SGIP(int sockfd, unsigned int smg_node_id,const char *national_code, 
            unsigned int cp_smg_id, const char *cp_phone = NULL);
    ~SGIP();
    void setTimeoutValue(int timeout);
    void GetSendSeqNum(unsigned int *seqnum);
    int SGIP_HeaderRecv(SGIP_HEADER *header);

    int SGIP_BIND_Send(SGIP_BIND_BODY *bind_body);
    int SGIP_BIND_Recv(SGIP_BIND_BODY *bind_body);
    int SGIP_BIND_RESP_Send(SGIP_BIND_RESP_BODY *bind_resp_body);
    int SGIP_BIND_RESP_Recv(SGIP_BIND_RESP_BODY *bind_resp_body);

    int SGIP_SUBMIT_Send(SGIP_SUBMIT_BODY *submit_body,SGIP_HEADER *header = NULL);
    int SGIP_SUBMIT_Recv(SGIP_SUBMIT_BODY *submit_body);
    int SGIP_SUBMIT_RESP_Send(SGIP_SUBMIT_RESP_BODY *submit_resp_body);
    int SGIP_SUBMIT_RESP_Recv(SGIP_SUBMIT_RESP_BODY *submit_resp_body);

    int SGIP_DELIVER_Send(SGIP_DELIVER_BODY *deliver_body,SGIP_HEADER *header = NULL);
    int SGIP_DELIVER_Recv(SGIP_DELIVER_BODY *deliver_body);
    int SGIP_DELIVER_RESP_Send(SGIP_DELIVER_RESP_BODY *deliver_resp_body);
    int SGIP_DELIVER_RESP_Recv(SGIP_DELIVER_RESP_BODY *deliver_resp_body);

    int SGIP_UNBIND_Send();
    int SGIP_UNBIND_RESP_Send();

    int SGIP_REPORT_Send(SGIP_REPORT_BODY *report_body,SGIP_HEADER *header = NULL);
    int SGIP_REPORT_Recv(SGIP_REPORT_BODY *report_body);
    int SGIP_REPORT_RESP_Send(SGIP_REPORT_RESP_BODY *report_resp_body);
    int SGIP_REPORT_RESP_Recv(SGIP_REPORT_RESP_BODY *report_resp_body);

    int SGIP_ADDSP_Send(SGIP_ADDSP_BODY *addsp_body);
    int SGIP_ADDSP_Recv(SGIP_ADDSP_BODY *addsp_body);
    int SGIP_ADDSP_RESP_Send(SGIP_ADDSP_RESP_BODY *addsp_resp);
    int SGIP_ADDSP_RESP_Recv(SGIP_ADDSP_RESP_BODY *addsp_resp);

    int SGIP_MODIFYSP_Send(SGIP_MODIFYSP_BODY *modifysp_body);
    int SGIP_MODIFYSP_Recv(SGIP_MODIFYSP_BODY *modifysp_body);
    int SGIP_MODIFYSP_RESP_Send(SGIP_MODIFYSP_RESP_BODY *modifysp_resp);
    int SGIP_MODIFYSP_RESP_Recv(SGIP_MODIFYSP_RESP_BODY *modifysp_resp);

    int SGIP_DELETESP_Send(SGIP_DELETESP_BODY *deletesp_body);
    int SGIP_DELETESP_Recv(SGIP_DELETESP_BODY *deletesp_body);
    int SGIP_DELETESP_RESP_Send(SGIP_DELETESP_RESP_BODY *deletesp_resp);
    int SGIP_DELETESP_RESP_Recv(SGIP_DELETESP_RESP_BODY *deletesp_resp);

    int SGIP_QUERYROUTE_Send(SGIP_QUERYROUTE_BODY *queryroute_body);
    int SGIP_QUERYROUTE_Recv(SGIP_QUERYROUTE_BODY *queryroute_body);
    int SGIP_QUERYROUTE_RESP_Send(SGIP_QUERYROUTE_RESP_BODY *queryroute_resp);
    int SGIP_QUERYROUTE_RESP_Recv(SGIP_QUERYROUTE_RESP_BODY *queryroute_resp);

    int SGIP_ADDTELESEG_Send(SGIP_ADDTELESEG_BODY *addteleseg_body);
    int SGIP_ADDTELESEG_Recv(SGIP_ADDTELESEG_BODY *addteleseg_body);
    int SGIP_ADDTELESEG_RESP_Send(SGIP_ADDTELESEG_RESP_BODY *addteleseg_resp);
    int SGIP_ADDTELESEG_RESP_Recv(SGIP_ADDTELESEG_RESP_BODY *addteleseg_resp);

    int SGIP_MODIFYTELESEG_Send(SGIP_MODIFYTELESEG_BODY *modifyteleseg_body);
    int SGIP_MODIFYTELESEG_Recv(SGIP_MODIFYTELESEG_BODY *modifyteleseg_body);
    int SGIP_MODIFYTELESEG_RESP_Send(SGIP_MODIFYTELESEG_RESP_BODY *modifyteleseg_resp);
    int SGIP_MODIFYTELESEG_RESP_Recv(SGIP_MODIFYTELESEG_RESP_BODY *modifyteleseg_resp);

    int SGIP_DELETETELESEG_Send(SGIP_DELETETELESEG_BODY *deleteteleseg_body);
    int SGIP_DELETETELESEG_Recv(SGIP_DELETETELESEG_BODY *deleteteleseg_body);
    int SGIP_DELETETELESEG_RESP_Send(SGIP_DELETETELESEG_RESP_BODY *deleteteleseg_resp);
    int SGIP_DELETETELESEG_RESP_Recv(SGIP_DELETETELESEG_RESP_BODY *deleteteleseg_resp);

    int SGIP_ADDSMG_Send(SGIP_ADDSMG_BODY *addsmg_body);
    int SGIP_ADDSMG_Recv(SGIP_ADDSMG_BODY *addsmg_body);
    int SGIP_ADDSMG_RESP_Send(SGIP_ADDSMG_RESP_BODY *addsmg_resp);
    int SGIP_ADDSMG_RESP_Recv(SGIP_ADDSMG_RESP_BODY *addsmg_resp);

    int SGIP_MODIFYSMG_Send(SGIP_MODIFYSMG_BODY *modifysmg_body);
    int SGIP_MODIFYSMG_Recv(SGIP_MODIFYSMG_BODY *modifysmg_body);
    int SGIP_MODIFYSMG_RESP_Send(SGIP_MODIFYSMG_RESP_BODY *modifysmg_resp);
    int SGIP_MODIFYSMG_RESP_Recv(SGIP_MODIFYSMG_RESP_BODY *modifysmg_resp);

    int SGIP_DELETESMG_Send(SGIP_DELETESMG_BODY *deletesmg_body);
    int SGIP_DELETESMG_Recv(SGIP_DELETESMG_BODY *deletesmg_body);
    int SGIP_DELETESMG_RESP_Send(SGIP_DELETESMG_RESP_BODY *deletesmg_resp);
    int SGIP_DELETESMG_RESP_Recv(SGIP_DELETESMG_RESP_BODY *deletesmg_resp);

    int SGIP_CHECKUSER_Send(SGIP_CHECKUSER_BODY *checkuser_body);
    int SGIP_CHECKUSER_Recv(SGIP_CHECKUSER_BODY *checkuser_body);
    int SGIP_CHECKUSER_RESP_Send(SGIP_CHECKUSER_RESP_BODY *checkuser_resp);
    int SGIP_CHECKUSER_RESP_Recv(SGIP_CHECKUSER_RESP_BODY *checkuser_resp);

    int SGIP_USERRPT_Send(SGIP_USERRPT_BODY *userrpt_body);
    int SGIP_USERRPT_Recv(SGIP_USERRPT_BODY *userrpt_body);
    int SGIP_USERRPT_RESP_Send(SGIP_USERRPT_RESP_BODY *userrpt_resp);
    int SGIP_USERRPT_RESP_Recv(SGIP_USERRPT_RESP_BODY *userrpt_resp);

    int SGIP_TRACE_Send(SGIP_TRACE_BODY *trace_body);
    int SGIP_TRACE_Recv(SGIP_TRACE_BODY *trace_body);
    int SGIP_TRACE_RESP_Send(SGIP_TRACE_RESP_BODY *trace_resp);
    int SGIP_TRACE_RESP_Recv(SGIP_TRACE_RESP_BODY *trace_resp);	

    SGIP_HEADER *getSgipHeader();
    /* 
     * whether to store package for dump
     * param : storeFlag --> 1: store, others : not store
     */
	void storePackage(int storeFlag);

    /* 
     * dump current package 
     * param : dest --> return the dump result
     */
	void dump(char *dest);

};

#endif
