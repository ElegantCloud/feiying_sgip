#include "sgip.h"

char *mylltostr(long long num, char *endptr)
{
 long long tmpnum;
 endptr--;
 *endptr = (num%10) + '0';
 
 tmpnum = num/10;
 if ((tmpnum) > 0) endptr = mylltostr(tmpnum, endptr);
 return endptr;
}



SGIP_FIELD SGIP_BIND_FIELD[]={
	{SGIP_BYTE, 1,"Login_Type"},
	{SGIP_STRING,16,"Login_Name"},
	{SGIP_STRING,16,"Login_Password"},	
	{SGIP_STRING,8,"Reserve"}
};

SGIP_FIELD SGIP_BIND_RESP_FIELD[]={
	{SGIP_BYTE,1,"Result"},
	{SGIP_STRING,8,"Reserve"}
};

SGIP_FIELD SGIP_SUBMIT_FIELD[]={
	{SGIP_STRING,21,"SPNumber"},
	{SGIP_STRING,21,"ChargeNumber"},
	{SGIP_BYTE,1,"UserCount"},
	{SGIP_USERNUM,2100,"UserNumber"},
	{SGIP_STRING,5,"CorpId"},
	{SGIP_STRING,10,"ServiceType"},
	{SGIP_BYTE,1,"FeeType"},
	{SGIP_STRING,6,"FeeValue"},
	{SGIP_STRING,6,"GivenValue"},
	{SGIP_BYTE,1,"AgentFlag"},
	{SGIP_BYTE,1,"MorelatetoMTFlag"},
	{SGIP_BYTE,1,"Priority"},
	{SGIP_STRING,16,"ExpireTime"},
	{SGIP_STRING,16,"ScheduleTime"},
	{SGIP_BYTE,1,"ReportFlag"},
	{SGIP_BYTE,1,"TP_pid"},
	{SGIP_BYTE,1,"TP_udhi"},
	{SGIP_BYTE,1,"MessageCoding"},
	{SGIP_BYTE,1,"MessageType"},
	{SGIP_INT,4,"MessageLength"},
	{SGIP_CONTENT,160,"MessageContent"},
	{SGIP_STRING,8,"Reserve"}
};

SGIP_FIELD SGIP_SUBMIT_RESP_FIELD[]={
	{SGIP_BYTE,1,"Result"},
	{SGIP_STRING,8,"Reserve"}
};

SGIP_FIELD SGIP_DELIVER_FIELD[]={
	{SGIP_STRING,21,"UserNumber"},
	{SGIP_STRING,21,"SPNumber"},
	{SGIP_BYTE,1,"TP_pid"},
	{SGIP_BYTE,1,"TP_udhi"},
	{SGIP_BYTE,1,"MessageCoding"},
	{SGIP_INT,4,"MessageLength"},
	{SGIP_CONTENT,160,"MessageContent"},
	{SGIP_STRING,8,"Reserve"}
};

SGIP_FIELD SGIP_DELIVER_RESP_FIELD[]={
	{SGIP_BYTE,1,"Result"},
	{SGIP_STRING,8,"Reserve"}
};

SGIP_FIELD SGIP_REPORT_FIELD[]={
	{SGIP_LONG,12,"SubmitSequenceNumber"},
	{SGIP_BYTE,1,"ReportType"},
	{SGIP_STRING,21,"UserNumber"},
	{SGIP_BYTE,1,"State"},
	{SGIP_BYTE,1,"ErrorCode"},
	{SGIP_STRING,8,"Reserve"}
};

SGIP_FIELD SGIP_REPORT_RESP_FIELD[]={
	{SGIP_BYTE,1,"Result"},
	{SGIP_STRING,8,"Reserve"}
};

SGIP_FIELD SGIP_ADDSP_FIELD[]={
	{SGIP_STRING,6,"SMGId"},
	{SGIP_STRING,21,"SPNumber"},
	{SGIP_STRING,10,"ServiceTag"},
	{SGIP_STRING,5,"CorpId"},
	{SGIP_STRING,8,"Reserve"}
};

SGIP_FIELD SGIP_ADDSP_RESP_FIELD[]={
	{SGIP_BYTE,1,"Result"},
	{SGIP_STRING,8,"Reserve"}
};

SGIP_FIELD SGIP_MODIFYSP_FIELD[]={
	{SGIP_STRING,6,"SMGId"},
	{SGIP_STRING,21,"OldSPNumber"},
	{SGIP_STRING,10,"OldServiceTag"},
	{SGIP_STRING,21,"NewSPNumber"},
	{SGIP_STRING,10,"NewServiceTag"},
	{SGIP_STRING,5,"CorpId"},
	{SGIP_STRING,8,"Reserve"}
};

SGIP_FIELD SGIP_MODIFYSP_RESP_FIELD[]={
	{SGIP_BYTE,1,"Result"},
	{SGIP_STRING,8,"Reserve"}
};

SGIP_FIELD SGIP_DELETESP_FIELD[]={
	{SGIP_STRING,6,"SMGId"},
	{SGIP_STRING,21,"SPNumber"},
	{SGIP_STRING,10,"ServiceTag"},
	{SGIP_STRING,8,"Reserve"}
};

SGIP_FIELD SGIP_DELETESP_RESP_FIELD[]={
	{SGIP_BYTE,1,"Result"},
	{SGIP_STRING,8,"Reserve"}
};

SGIP_FIELD SGIP_QUERYROUTE_FIELD[]={
	{SGIP_BYTE,1,"QueryType"},
	{SGIP_STRING,21,"Number"},
	{SGIP_STRING,10,"ServiceTag"},
	{SGIP_STRING,8,"Reserve"}
};

SGIP_FIELD SGIP_QUERYROUTE_RESP_FIELD[]={
	{SGIP_BYTE,1,"Result"},
	{SGIP_INT,4,"Count"},
	{SGIP_ROUTERESULT,20,"Route_Result"}
};

SGIP_FIELD SGIP_ADDTELESEG_FIELD[]={
	{SGIP_STRING,6,"SMGId"},
	{SGIP_STRING,7,"TeleSeg"},
	{SGIP_STRING,1,"TeleType"},
	{SGIP_STRING,4,"AreaCode"},
	{SGIP_STRING,8,"Reserve"}
};

SGIP_FIELD SGIP_ADDTELESEG_RESP_FIELD[]={
	{SGIP_BYTE,1,"Result"},
	{SGIP_STRING,8,"Reserve"}	
};

SGIP_FIELD SGIP_MODIFYTELESEG_FIELD[]={
	{SGIP_STRING,6,"SMGId"},
	{SGIP_STRING,7,"OldTeleSeg"},
	{SGIP_STRING,7,"NewTeleSeg"},
	{SGIP_STRING,1,"NewTeleType"},
	{SGIP_STRING,4,"NewAreaCode"},
	{SGIP_STRING,8,"Reserve"}
};

SGIP_FIELD SGIP_MODIFYTELESEG_RESP_FIELD[]={
	{SGIP_BYTE,1,"Result"},
	{SGIP_STRING,8,"Reserve"}	
};

SGIP_FIELD SGIP_DELETETELESEG_FIELD[]={
	{SGIP_STRING,6,"SMGId"},
	{SGIP_STRING,7,"TeleSeg"},
	{SGIP_STRING,8,"Reserve"}
};

SGIP_FIELD SGIP_DELETETELESEG_RESP_FIELD[]={
	{SGIP_BYTE,1,"Result"},
	{SGIP_STRING,8,"Reserve"}	
};

SGIP_FIELD SGIP_ADDSMG_FIELD[]={
	{SGIP_STRING,6,"SMGId"},
	{SGIP_INT,4,"SMGIP"},
	{SGIP_STRING,16,"LoginName"},
	{SGIP_STRING,16,"LoginPassword"},
	{SGIP_STRING,8,"Reserve"}
};

SGIP_FIELD SGIP_ADDSMG_RESP_FIELD[]={
	{SGIP_BYTE,1,"Result"},
	{SGIP_STRING,8,"Reserve"}	
};

SGIP_FIELD SGIP_MODIFYSMG_FIELD[]={
	{SGIP_STRING,6,"OldSMGId"},
	{SGIP_STRING,6,"NewSMGId"},
	{SGIP_INT,4,"SMGIP"},
	{SGIP_STRING,16,"LoginName"},
	{SGIP_STRING,16,"LoginPassword"},
	{SGIP_STRING,8,"Reserve"}
};

SGIP_FIELD SGIP_MODIFYSMG_RESP_FIELD[]={
	{SGIP_BYTE,1,"Result"},
	{SGIP_STRING,8,"Reserve"}	
};

SGIP_FIELD SGIP_DELETESMG_FIELD[]={
	{SGIP_STRING,6,"SMGId"},
	{SGIP_STRING,8,"Reserve"}
};

SGIP_FIELD SGIP_DELETESMG_RESP_FIELD[]={
	{SGIP_BYTE,1,"Result"},
	{SGIP_STRING,8,"Reserve"}	
};

SGIP_FIELD SGIP_CHECKUSER_FIELD[]={
	{SGIP_STRING,16,"UserName"},
	{SGIP_STRING,16,"Password"},
	{SGIP_STRING,21,"UserNumber"},
	{SGIP_STRING,8,"Reserve"}
};

SGIP_FIELD SGIP_CHECKUSER_RESP_FIELD[]={
	{SGIP_BYTE,1,"Result"},
	{SGIP_BYTE,1,"Status"},
	{SGIP_STRING,8,"Reserve"}	
};

SGIP_FIELD SGIP_USERRPT_FIELD[]={
	{SGIP_STRING,21,"SPNumber"},
	{SGIP_STRING,21,"UserNumber"},
	{SGIP_BYTE,1,"UserCondition"},
	{SGIP_STRING,8,"Reserve"}
};

SGIP_FIELD SGIP_USERRPT_RESP_FIELD[]={
	{SGIP_BYTE,1,"Result"},
	{SGIP_STRING,8,"Reserve"}	
};

SGIP_FIELD SGIP_TRACE_FIELD[]={
	{SGIP_LONG,12,"SubmitSequenceNumber"},
	{SGIP_STRING,21,"UserNumber"},
	{SGIP_STRING,8,"Reserve"}
};

SGIP_FIELD SGIP_TRACE_RESP_FIELD[]={
	{SGIP_BYTE,1,"Count"},
	{SGIP_TRACERESULT,3,"Trace_Result"}
};

SGIP_MSG_FIELD SGIP_MESSAGE[]={
	{4,SGIP_BIND_FIELD},
	{2,SGIP_BIND_RESP_FIELD},
	{22,SGIP_SUBMIT_FIELD},
	{2,SGIP_SUBMIT_RESP_FIELD},
	{8,SGIP_DELIVER_FIELD},
	{2,SGIP_DELIVER_RESP_FIELD},
	{6,SGIP_REPORT_FIELD},
	{2,SGIP_REPORT_RESP_FIELD},
	{5,SGIP_ADDSP_FIELD},
	{2,SGIP_ADDSP_RESP_FIELD},
	{7,SGIP_MODIFYSP_FIELD},
	{2,SGIP_MODIFYSP_RESP_FIELD},
	{4,SGIP_DELETESP_FIELD},
	{2,SGIP_DELETESP_RESP_FIELD},
	{4,SGIP_QUERYROUTE_FIELD},
	{3,SGIP_QUERYROUTE_RESP_FIELD},
	{5,SGIP_ADDTELESEG_FIELD},
	{2,SGIP_ADDTELESEG_RESP_FIELD},
	{6,SGIP_MODIFYTELESEG_FIELD},
	{2,SGIP_MODIFYTELESEG_RESP_FIELD},
	{3,SGIP_DELETETELESEG_FIELD},
	{2,SGIP_DELETETELESEG_RESP_FIELD},
	{5,SGIP_ADDSMG_FIELD},
	{2,SGIP_ADDSMG_RESP_FIELD},
	{6,SGIP_MODIFYSMG_FIELD},
	{2,SGIP_MODIFYSMG_RESP_FIELD},
	{2,SGIP_DELETESMG_FIELD},
	{2,SGIP_DELETESMG_RESP_FIELD},
	{4,SGIP_CHECKUSER_FIELD},
	{3,SGIP_CHECKUSER_RESP_FIELD},
	{4,SGIP_USERRPT_FIELD},
	{2,SGIP_USERRPT_RESP_FIELD},
	{3,SGIP_TRACE_FIELD},
	{2,SGIP_TRACE_RESP_FIELD}
};
  

SGIP::SGIP(int sockfd, unsigned int smg_node_id,const char *national_code, 
	unsigned int cp_smg_id, const char *cp_phone)
{
	int i;
	
        m_sockfd=sockfd;
	m_timeout = 5;//5 seconds
	m_bufindex=0;
	m_smg_node_id = smg_node_id;
	m_cp_smg_id = cp_smg_id;
	strcpy(m_national_code,national_code);
	if (cp_phone == NULL)
	{
		m_is_cp = 0;
	}
	else
	{
		m_is_cp = 1;
		memset (m_cp_phone, 0, sizeof(m_cp_phone));
		strncpy (m_cp_phone, cp_phone, 28);
		//printf ("cp phnoe set: %s\n", m_cp_phone);
	}
        
	for (i=0; i<3; i++)
	{
		m_send_sequenceid[i] = 0;
		m_recv_sequenceid[i] = 0;
	}
	
	recv_seqno_index = 0;
	for (i=0; i<32; i++)
	{
		recv_seqno_buf [i] = 0;
	}

    	storePackFlag = 0;
}

SGIP::~SGIP()
{
  close(m_sockfd);
//	closesock(m_sockfd);
}
	 
void SGIP::setTimeoutValue(int timeout)
{
    if (timeout > 0)
        m_timeout = timeout;
}

int SGIP::IdtoIndex(unsigned int commandid, unsigned int *structlength)
{
	int ret;
	switch(commandid)
	{
	case SGIP_BIND:
		*structlength = sizeof(SGIP_BIND_BODY);
		ret = 0;
		break;
	case SGIP_BIND_RESP:
		*structlength = sizeof(SGIP_BIND_RESP_BODY);
		ret = 1;
		break;
	case SGIP_SUBMIT:
		*structlength = sizeof(SGIP_SUBMIT_BODY);
		ret = 2;
		break;
	case SGIP_SUBMIT_RESP:
		*structlength = sizeof(SGIP_SUBMIT_RESP_BODY);
		ret = 3;
		break;
	case SGIP_DELIVER:
		*structlength = sizeof(SGIP_DELIVER_BODY);
		ret = 4;
		break;
	case SGIP_DELIVER_RESP:
		*structlength = sizeof(SGIP_DELIVER_RESP_BODY);
		ret = 5;
		break;
	case SGIP_REPORT:
		*structlength = sizeof(SGIP_REPORT_BODY);
		ret = 6;
		break;
	case SGIP_REPORT_RESP:
		*structlength = sizeof(SGIP_REPORT_RESP_BODY);
		ret = 7;
		break;
	case SGIP_ADDSP:
		*structlength = sizeof(SGIP_ADDSP_BODY);
		ret = 8;
		break;
	case SGIP_ADDSP_RESP:
		*structlength = sizeof(SGIP_ADDSP_RESP_BODY);
		ret = 9;
		break;
	case SGIP_MODIFYSP:
		*structlength = sizeof(SGIP_MODIFYSP_BODY);
		ret = 10;
		break;
	case SGIP_MODIFYSP_RESP:
		*structlength = sizeof(SGIP_MODIFYSP_RESP_BODY);
		ret = 11;
		break;
	case SGIP_DELETESP:
		*structlength = sizeof(SGIP_DELETESP_BODY);
		ret = 12;
		break;
	case SGIP_DELETESP_RESP:
		*structlength = sizeof(SGIP_DELETESP_RESP_BODY);
		ret = 13;
		break;
	case SGIP_QUERYROUTE:
		*structlength = sizeof(SGIP_QUERYROUTE_BODY);
		ret = 14;
		break;
	case SGIP_QUERYROUTE_RESP:
		*structlength = LEN_SGIP_QUERYROUTE_RESP+sizeof(SGIP_ROUTEITEM)*20;
		ret = 15;
		break;
	case SGIP_ADDTELESEG:
		*structlength = sizeof(SGIP_ADDTELESEG_BODY);
		ret = 16;
		break;
	case SGIP_ADDTELESEG_RESP:
		*structlength = sizeof(SGIP_ADDTELESEG_RESP_BODY);
		ret = 17;
		break;
	case SGIP_MODIFYTELESEG:
		*structlength = sizeof(SGIP_MODIFYTELESEG_BODY);
		ret = 18;
		break;
	case SGIP_MODIFYTELESEG_RESP:
		*structlength = sizeof(SGIP_MODIFYTELESEG_RESP_BODY);
		ret = 19;
		break;
	case SGIP_DELETETELESEG:
		*structlength = sizeof(SGIP_DELETETELESEG_BODY);
		ret = 20;
		break;
	case SGIP_DELETETELESEG_RESP:
		*structlength = sizeof(SGIP_DELETETELESEG_RESP_BODY);
		ret = 21;
		break;
	case SGIP_ADDSMG:
		*structlength = sizeof(SGIP_ADDSMG_BODY);
		ret = 22;
		break;
	case SGIP_ADDSMG_RESP:
		*structlength = sizeof(SGIP_ADDSMG_RESP_BODY);
		ret = 23;
		break;
	case SGIP_MODIFYSMG:
		*structlength = sizeof(SGIP_MODIFYSMG_BODY);
		ret = 24;
		break;
	case SGIP_MODIFYSMG_RESP:
		*structlength = sizeof(SGIP_MODIFYSMG_RESP_BODY);
		ret = 25;
		break;
	case SGIP_DELETESMG:
		*structlength = sizeof(SGIP_DELETESMG_BODY);
		ret = 26;
		break;
	case SGIP_DELETESMG_RESP:
		*structlength = sizeof(SGIP_DELETESMG_RESP_BODY);
		ret = 27;
		break;
	case SGIP_CHECKUSER:
		*structlength = sizeof(SGIP_CHECKUSER_BODY);
		ret = 28;
		break;
	case SGIP_CHECKUSER_RESP:
		*structlength = sizeof(SGIP_CHECKUSER_RESP_BODY);
		ret = 29;
		break;
	case SGIP_USERRPT:
		*structlength = sizeof(SGIP_USERRPT_BODY);
		ret = 30;
		break;
	case SGIP_USERRPT_RESP:
		*structlength = sizeof(SGIP_USERRPT_RESP_BODY);
		ret = 31;
		break;
	case SGIP_TRACE:
		*structlength = sizeof(SGIP_TRACE_BODY);
		ret = 32;
		break;
	case SGIP_TRACE_RESP:
		*structlength = LEN_SGIP_TRACE_RESP+sizeof(SGIP_TRACEITEM)*3;
		ret = 33;
		break;
	default:
		return COMMANDID_NOT_EXIST;
		break;
	}
	return ret;
}

void SGIP::Generate_Sequence_Number(unsigned int *Sequence_Number)
{
	struct tm now;
	time_t current_time;

	// Get Current Time
	current_time = time(NULL);
	localtime_r(&current_time,&now);	
	
	m_send_sequenceid[2] ++;	

	// Generate Sequence Number 
	if(m_is_cp)
    	  Sequence_Number[0] = m_cp_smg_id;
	else
    	  Sequence_Number[0] = m_smg_node_id;
	Sequence_Number[1] = ((((now.tm_mon+1)*100+now.tm_mday)*100+now.tm_hour)*100+now.tm_min)*100+now.tm_sec;
	Sequence_Number[2] = m_send_sequenceid[2];
	
	for (int i=0; i<3; i++)
	{
		m_send_sequenceid[i] = Sequence_Number[i];
	}	
}

void SGIP::GetSendSeqNum(unsigned int *seqnum)
{
	// Get Sequence Number
	seqnum[0] =  m_send_sequenceid[0];
	seqnum[1] =  m_send_sequenceid[1];
	seqnum[2] = m_send_sequenceid[2];
}
	
int SGIP::SGIP_Generate_Header(char *buffer,SGIP_HEADER *header)
{
	int  offset = 0;
	unsigned int  temp = 0;

	// Total_Length : Integer(4)
	temp = htonl(header->Message_Length);
	memcpy(buffer+offset, (char *)&temp, 4);
	offset += 4;

	// Command_ID : Integer(4)
	temp = htonl(header->Command_Id);
	memcpy(buffer+offset, (char *)&temp, 4);
	offset += 4;

	// Sequence_Number : Integer(12)
	temp = htonl(header->Sequence_Number[0]);
	memcpy(buffer+offset, (char *)&temp, 4);
	offset += 4;

	temp = htonl(header->Sequence_Number[1]);
	memcpy(buffer+offset, (char *)&temp, 4);
	offset += 4;
	
	temp = htonl(header->Sequence_Number[2]);
	memcpy(buffer+offset, (char *)&temp, 4);
	offset += 4;

	return offset;
}

SGIP_HEADER *SGIP::getSgipHeader()
{
    return &curSgipHeader;
}

int SGIP::SGIP_HeaderRecv(SGIP_HEADER *header)
{
	int result=-1;
	int offset = 0;
	int offset1=0;
	unsigned int  temp = 0;
	int bound_break = 0;
	int field_length = 0; 
	unsigned int command_len = 0;

	memset (m_buffer, 0, sizeof(m_buffer));
	//Begin to receive message header
	result = read_all(m_sockfd, m_sockbuf, LEN_SGIP_HEADER);
	if(result < 0)
	{
          printf("result=%d,errno=%d,errstr:%s\n",result,errno,strerror(errno));  
      	  return result;
	}
	
        memcpy(header, m_sockbuf, LEN_SGIP_HEADER);

	m_header = *header;

    	if(storePackFlag)
    	{
           memcpy(bufPackage, header, LEN_SGIP_HEADER);
    	}

	recv_seqno_index++;
	if(recv_seqno_index >= 32)	
          recv_seqno_index = 0;

	recv_seqno_buf [recv_seqno_index ] = m_header.Sequence_Number[2];
	
        header->Message_Length = ntohl(header->Message_Length) & 0xffffffff;
	if((header->Message_Length < LEN_SGIP_HEADER)
		||(header->Message_Length > SGIP_MAX_MES_LEN))
	  return RECEIVE_DATA_FAILED;

	m_bodylength = header->Message_Length - LEN_SGIP_HEADER;

        memset (m_buffer, 0, sizeof(m_buffer));
        //Begin to receive message body 
        result = read_all(m_sockfd, m_sockbuf, m_bodylength);
        if(result < 0)
        {
          printf("result=%d,errno=%d,errstr:%s\n",result,errno,strerror(errno));        
          return result;
        }
       
	header->Command_Id = ntohl(header->Command_Id);

	packCmdId = header->Command_Id;
	packLength = header->Message_Length;

	for (int i=0; i<3; i++)
	{
		header->Sequence_Number[i] = ntohl(header->Sequence_Number[i]);
		m_recv_sequenceid[i] = header->Sequence_Number[i];
	}
	
	if((header->Command_Id != SGIP_UNBIND)&&(header->Command_Id != SGIP_UNBIND_RESP))
	{
	//Continue to receive message body
	char *buffer2 = NULL;
	offset=0;
	temp=0;
	int tempint=0;
	int index=0;
	int j=0,i2=0;
	unsigned int k = 0;

	// Allocate Message Buffer
	buffer2 = (char *)malloc(m_bodylength);
	if(buffer2 == NULL)
	  return MALLOC_FAILED;
	memset(buffer2, 0, m_bodylength);
	
	memcpy(buffer2, m_sockbuf, m_bodylength);

    	if (storePackFlag)
    	{
        	memcpy(bufPackage + LEN_SGIP_HEADER, buffer2, m_bodylength);
    	}

    	index = IdtoIndex(header->Command_Id,&command_len);
    	if(COMMANDID_NOT_EXIST == index)
       	  return COMMANDID_NOT_EXIST;

	for(int i=0;i<SGIP_MESSAGE[index].Field_Count;i++)
	{
		switch(SGIP_MESSAGE[index].Fields[i].Field_Type)
		{
		case SGIP_BYTE:
			field_length = SGIP_MESSAGE[index].Fields[i].Field_Length;
			if (((offset1+field_length) > sizeof(SGIP_SUBMIT_BODY))
				|| ((offset1+field_length) <= 0)
				|| ((offset + field_length) > header->Message_Length)
				|| ((offset + field_length) <= 0))
			{
				//printf("byte error!\n");
				//printf(" Recv:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
				bound_break = 1;
				break;
			}
			memcpy(m_buffer+offset1, buffer2+offset, SGIP_MESSAGE[index].Fields[i].Field_Length);
		   	offset += SGIP_MESSAGE[index].Fields[i].Field_Length;
			offset1+=SGIP_MESSAGE[index].Fields[i].Field_Length;
			break;
		case SGIP_INT:
			field_length = SGIP_MESSAGE[index].Fields[i].Field_Length;
			if (((offset + field_length) > header->Message_Length)
				|| ((offset+field_length) <= 0))
			{
				//printf("int error 1\n");
				//printf("header->Message_Length is %d,offset is %d,field_length is %d\n",header->Message_Length,offset ,field_length);
				//printf(" Recv:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
				bound_break = 1;
				break;
			}
			memcpy((char*)&temp, buffer2+offset, SGIP_MESSAGE[index].Fields[i].Field_Length);
			temp=ntohl(temp)&0xffffffff;
			offset1 = GetFieldLen(offset1);
			if (((offset1+field_length) > sizeof(SGIP_SUBMIT_BODY))
				|| ((offset1+field_length) <= 0))
			{
				//printf("int error 2\n");
				//printf(" Recv:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
				bound_break = 1;
				break;
			}
			memcpy(m_buffer+offset1,(char*)&temp,4);
			offset1+=SGIP_MESSAGE[index].Fields[i].Field_Length;
		    offset+= SGIP_MESSAGE[index].Fields[i].Field_Length;
			break;
		case SGIP_LONG:
			for(i2=0;i2<3;i2++)
			{
				if (((offset + 4) > header->Message_Length) || ((offset+4) <= 0))
				{
					//printf("long error 1\n");
				    	//printf(" Recv:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
					bound_break = 1;
				    break;
				}
				memcpy((char*)&temp, buffer2+offset, 4);
			    	temp=ntohl(temp)&0xffffffff;
			    	offset1 = GetFieldLen(offset1);
                				if (((offset1+4) > sizeof(SGIP_SUBMIT_BODY))  || ((offset1+4) <= 0))
				{
					//printf("long error 2\n");
				    //printf(" Recv:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
					bound_break = 1;
				    break;
				}
	    		memcpy(m_buffer+offset1,(char*)&temp,4);
	    		offset1+=4;
        		offset+= 4;
			}
			break;

		case SGIP_STRING:
			field_length = SGIP_MESSAGE[index].Fields[i].Field_Length;
			if (((offset1+field_length) > sizeof(SGIP_SUBMIT_BODY))
			 	|| ((offset1 + field_length) <= 0)
				|| ((offset + field_length) > header->Message_Length)
			 	|| ((offset + field_length) <= 0))
			{
				//printf("string error 1\n");
				//printf(" Recv:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
				bound_break = 1;
				break;
			}
			memcpy(m_buffer+offset1, buffer2+offset, SGIP_MESSAGE[index].Fields[i].Field_Length);
		    offset += SGIP_MESSAGE[index].Fields[i].Field_Length;
			offset1+=SGIP_MESSAGE[index].Fields[i].Field_Length;
			m_buffer[offset1] = '\0';
			offset1++;
			break;
		case SGIP_USERNUM:
			k=*(unsigned char*)(buffer2+offset-1);
			if (((offset1+MAXUSERNUMBERLENGTH) >= sizeof(SGIP_SUBMIT_BODY))
				|| ((offset1 + MAXUSERNUMBERLENGTH) <= 0)
				|| ((offset + k*21) >= header->Message_Length)
				|| ((offset + k*21) <= 0))
			{
				//printf("user_number error 1\n");
				//printf(" Recv:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
				bound_break = 1;
				break;
			}
			memcpy(m_buffer+offset1, buffer2+offset, k*21);
			offset1 += MAXUSERNUMBERLENGTH;			
			offset += k*21;
			break;
		case SGIP_CONTENT:
			k=*(unsigned int *)(m_buffer+offset1-4);
			if (((offset1+MAXLENGTH) > sizeof(SGIP_SUBMIT_BODY))
				|| ((offset1 + MAXLENGTH) <= 0)
				|| ((offset + k) > header->Message_Length)
				|| ((offset + k) <= 0))
			{
				//printf("content error 1\n");
				//printf(" Recv:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
				bound_break = 1;
				break;
			}
			memcpy(m_buffer+offset1, buffer2+offset,k);
			offset1 += MAXLENGTH;
			offset += k;			
			break;
		case SGIP_ROUTERESULT:
			k=*(unsigned int*)(m_buffer+offset1-4);
			for(j=0;j<k;j++)
			{
				if (((offset1 + 43) > sizeof(SGIP_SUBMIT_BODY))
					|| ((offset1 + 43) <= 0)
					|| ((offset + 43) > header->Message_Length)
					|| ((offset + 43) <= 0))
				{
					//printf("route error 1\n");
					//printf(" Recv:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
					bound_break = 1;
					break;
				}
			    	memcpy(m_buffer+offset1, buffer2+offset, 43);
			    	offset1+=43;
			    	offset+=43;
				if (((offset + 4) > header->Message_Length)
					|| ((offset + 4) <= 0))
				{
					//printf("route error 2\n");
				    	//printf(" Recv:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
					bound_break = 1;
				    	break;
				}
			    	memcpy((char*)&temp, buffer2+offset, 4);
			    	temp=ntohl(temp)&0xffffffff;
			    	offset1 = GetFieldLen(offset1);
				if (((offset1 + 4) > sizeof(SGIP_SUBMIT_BODY))
					|| ((offset1 + 4) <= 0))
				{
					//printf("route error 3\n");
				    	//printf(" Recv:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
					bound_break = 1;
					break;
				}
                memcpy(m_buffer+offset1,(char*)&temp,4);
                offset1+=4;
                offset+= 4;
				if (((offset1 + 40) > sizeof(SGIP_SUBMIT_BODY))
					|| ((offset1 + 40) <= 0)
					|| ((offset + 40) > header->Message_Length)
					|| ((offset + 40) <= 0))
				{
					//printf("route error 4\n");
				    	//printf(" Recv:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
					bound_break = 1;
				    break;
				}
                memcpy(m_buffer+offset1, buffer2+offset, 40);
                offset1+=40;
                offset+=40;
			}
			break;
		case SGIP_TRACERESULT:
			k=*(unsigned char*)(buffer2+offset-1);
			if (((offset1+k*47) > sizeof(SGIP_SUBMIT_BODY))
				|| ((offset1 + k*47) <= 0)
				|| ((offset + k*47) > header->Message_Length)
				|| ((offset + k*47) <= 0))
			{
				//printf("trace error 1\n");
				//printf(" Recv:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
				bound_break = 1;
				break;
			}
			for(j=0;j<k;j++)
			{
                memcpy(m_buffer+offset1, buffer2+offset, 47);
                offset1+=47;
                offset+=47;
			}
			break;
		}

		if (bound_break == 1)
		{
			free(buffer2);
			return 8;
		}
	}
	
	free(buffer2);
        buffer2 = NULL;
	}

    if((header->Command_Id == SGIP_QUERYROUTE_RESP)
        || (header->Command_Id == SGIP_TRACE_RESP))
	{
		if((offset1>command_len)||(offset != m_bodylength))
		{
			//printf("Recv: Total length check error 1!\n");
			//printf("offset1 = %d,command_len = %d\n",offset1,command_len);
			//printf("offset = %d,body_length = %d\n",offset,m_bodylength);	
			return 8;
		}
	}
	else
	{
		if((offset1 > command_len)||(offset1+3 < command_len)
			||(offset != m_bodylength))
		{
			//printf("Recv: Total length check error 2!\n");
			//printf("offset1 = %d,command_len = %d\n",offset1,command_len);
			//printf("offset = %d, body_length = %d\n",offset,m_bodylength);
			return 8;
		}
	}
	m_bodylength = command_len;
        
        curSgipHeader.Message_Length = header->Message_Length;  
        curSgipHeader.Command_Id = header->Command_Id;  
        for(int i=0; i<3; i++)      
        {       
          curSgipHeader.Sequence_Number[i] = header->Sequence_Number[i];
        }      
        //printf("id1=%d\n",header->Command_Id); 

	return 0;
}


unsigned int SGIP::GetFieldLen(unsigned int length)
{
	unsigned int newlen=0;

	if(length%4==0)
	{
		newlen=length;
	}
	else 
	{
		newlen=length+(4-length%4);
	}

	return newlen;
}


int SGIP::SGIP_BodyRecv(unsigned int commandid, void *body1, int bodylength)
{
	char *body=(char*)body1;
	memcpy(body,m_buffer,bodylength);	
	return 0;
}		

int SGIP::SGIP_Send(unsigned int commandid,void *body,int bodylength,SGIP_HEADER *myheader)
{
	int i=0,j=0,i2=0;
	unsigned int k =0;
	int result=-1;
	int offset = 0;
	int offset_body = 0;
	int index=0;
	unsigned int  temp = 0;
	int bound_break = 0;
	int field_length = 0;
	unsigned int command_len = 0;

	char *buffer = NULL;
	// Allocate Message Buffer
	buffer = (char *)malloc(bodylength);
	if(buffer == NULL)
	  return MALLOC_FAILED;
	memset(buffer, 0, bodylength);
	
	//Generate message header
	SGIP_HEADER *header = new SGIP_HEADER;
	header->Message_Length = bodylength;	
	header->Command_Id = commandid;

	packCmdId = header->Command_Id;
	packLength = header->Message_Length;
	
	if (commandid > 0x7fffffff)
	{
		for (int i=0; i<3; i++)
		{
			header->Sequence_Number[i] = m_recv_sequenceid[i];			
		}		
	}
	else
	{
		if(myheader == NULL)
		{
			Generate_Sequence_Number(header->Sequence_Number);			
		}
		else
		{
			for (int i=0; i<3; i++)
			{
				header->Sequence_Number[i] = myheader->Sequence_Number[i];
			}
		}	
	}
	
	offset=SGIP_Generate_Header(buffer, header);
	delete header;
	header = NULL;

	if((commandid!=SGIP_UNBIND)&&(commandid!=SGIP_UNBIND_RESP))
	{

	index = IdtoIndex(commandid, &command_len);
	if (COMMANDID_NOT_EXIST == index)
    	{
        	free(buffer);
        	buffer = NULL;
        	return COMMANDID_NOT_EXIST;
    	}

	char *ptr = (char *)body;
	for(int i=0;i<SGIP_MESSAGE[index].Field_Count;i++)
	{
	switch(SGIP_MESSAGE[index].Fields[i].Field_Type)
	{
		case SGIP_BYTE:
			 field_length = SGIP_MESSAGE[index].Fields[i].Field_Length;
			 if (((offset+field_length) > bodylength)
			 	|| ((offset + field_length) <= 0)
				|| ((offset_body + field_length) >command_len)
			 	|| ((offset_body + field_length) <= 0))
			 {
				 //printf("byte error\n");
				 //printf(" Send:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
				 bound_break = 1;
				 break;
			 }
			 memcpy(buffer+offset, ptr+offset_body, SGIP_MESSAGE[index].Fields[i].Field_Length);
			 offset += SGIP_MESSAGE[index].Fields[i].Field_Length;
			 offset_body += SGIP_MESSAGE[index].Fields[i].Field_Length;
 			 break;
		
		case SGIP_INT:
			 field_length = SGIP_MESSAGE[index].Fields[i].Field_Length;
			 offset_body = GetFieldLen((unsigned int)offset_body);
			 if (((offset_body + field_length) >command_len)
			 	|| ((offset_body + field_length) <= 0))
			 {
				 //printf("int error 1\n");
				 //printf(" Send:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
				 bound_break = 1;
				 break;
			 }
			 memcpy((char*)&temp, ptr+offset_body, SGIP_MESSAGE[index].Fields[i].Field_Length);
			 temp=htonl(temp);
			 if (((offset+field_length) > bodylength)
			 	|| ((offset + field_length) <= 0))
			 {
				 //printf("int error 2\n");
				 //printf(" Send:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
				 bound_break = 1;
				 break;
			 }
			 memcpy(buffer+offset,(char*)&temp,4);
			 offset += SGIP_MESSAGE[index].Fields[i].Field_Length;
			 offset_body+=SGIP_MESSAGE[index].Fields[i].Field_Length;
			 break;

		case SGIP_LONG:
			 for(i2=0;i2<3;i2++)
			 {
				 offset_body = GetFieldLen((unsigned int)offset_body);
				 if (((offset_body + 4) >command_len)
			 		|| ((offset_body + 4) <= 0))
				 {
					 //printf("long error 1\n");
					 //printf(" Send:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
					 bound_break = 1;
				     break;
				 }
			     	memcpy((char*)&temp, ptr+offset_body, 4);
			     	temp=htonl(temp);
				 if (((offset+4) > bodylength) || ((offset + 4) <= 0))
				 {
					//printf("long error 2\n");
					//printf(" Send:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
					bound_break = 1;
					break;
				 }
			     	memcpy(buffer+offset,(char*)&temp,4);
			     	offset += 4;
			     	offset_body+=4;
			 }
		     	break;
		
		case SGIP_STRING:
			 field_length = SGIP_MESSAGE[index].Fields[i].Field_Length;
			 if (((offset+field_length) > bodylength)
			 	|| ((offset + field_length) <= 0))
			 {
				 //printf("string error 1\n");
				 //printf(" Send:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
				 bound_break = 1;
				 break;
			 } 
			 if (((offset_body + field_length) >command_len)
			 	|| ((offset_body + field_length) <= 0))
			 {
				 //printf("string error 2\n");
				 //printf(" Send:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
				 bound_break = 1;
				 break;
			 } 
			 memcpy(buffer+offset, ptr+offset_body, SGIP_MESSAGE[index].Fields[i].Field_Length);
			 offset += SGIP_MESSAGE[index].Fields[i].Field_Length;
			 offset_body+=SGIP_MESSAGE[index].Fields[i].Field_Length+1;
			 break;
		
		case SGIP_USERNUM:
			 k=*(unsigned char*)(buffer+offset-1);
			 if (((offset+k*21) > bodylength)
			 	|| ((offset + k*21) <= 0)
				|| ((offset_body + MAXUSERNUMBERLENGTH) >command_len)
			 	|| ((offset_body +MAXUSERNUMBERLENGTH) <= 0))
			{
				//printf("usernum error\n");
				//printf(" Send:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
				bound_break = 1;
				break;
			}
			 memcpy(buffer+offset, ptr+offset_body, k*21);	
			 offset += k*21;
			 offset_body += MAXUSERNUMBERLENGTH;
			 break;
		
		case SGIP_CONTENT:
			 k=*(unsigned int*)(ptr+offset_body-4);
			 if (((offset+k) > bodylength)
			 	|| ((offset + k) <= 0)
				|| ((offset_body + MAXLENGTH) >command_len)
			 	|| ((offset_body + MAXLENGTH) <= 0))
			{
				//printf("content error\n");
				//printf(" Send:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
				bound_break = 1;
				break;
			}
		     	memcpy(buffer+offset, ptr+offset_body,k);
			offset_body += MAXLENGTH;
			offset += k;
			break;
		case SGIP_ROUTERESULT:
			k=*(unsigned int*)(ptr+offset_body-4);
			for(j=0;j<k;j++)
			{
				if (((offset + 43) > bodylength)
					|| ((offset + 43) <= 0)
					|| ((offset_body + 43) >command_len)
					|| ((offset_body + 43) <= 0))
				{
					//printf("routeresult error 1\n");
					//printf(" Send:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
					bound_break = 1;
					break;
				}
				memcpy(buffer+offset, ptr+offset_body, 43);
				offset_body+=43;
				offset+=43;
				offset_body = GetFieldLen((unsigned int)offset_body);
				if (((offset+4) > bodylength)
					|| ((offset + 4) <= 0)
				 	|| ((offset_body + 4) >command_len)
					|| ((offset_body + 4) <= 0))
				{
					//printf("route result error 2\n");
					//printf(" Send:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
					bound_break = 1;
					break;
				}
				memcpy((char*)&temp, ptr+offset_body, 4);
				temp=htonl(temp);
				memcpy(buffer+offset,(char*)&temp,4);
				offset += 4;
				offset_body+=4;
				if (((offset+40) > bodylength)
					|| ((offset + 40) <= 0)
				 	|| ((offset_body + 40) >command_len)
					|| ((offset_body + 40) <= 0))
				{
					//printf("route result error 3\n");
					//printf(" Send:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
					bound_break = 1;
					break;
				}
				memcpy(buffer+offset, ptr+offset_body, 40);
				offset_body+=40;
				offset+=40;
			}
			break;
		case SGIP_TRACERESULT:
			k=*(unsigned char*)(buffer+offset-1);
			if (((offset+k*47) > bodylength)
				|| ((offset + k*47) <= 0)
				|| ((offset_body + k*47) >command_len)
				|| ((offset_body + k*47) <= 0))
			{
				//printf("trace result error\n");
				//printf(" Send:Error field name is %s\n",SGIP_MESSAGE[index].Fields[i].Field_Name);
				bound_break = 1;
				break;
			}
			for(j=0;j<k;j++)
			{
				memcpy(buffer+offset, ptr+offset_body, 47);
				offset_body += 47;
				offset += 47;
			}
			break;
	} //switch

	if (bound_break == 1)
	{
		free(buffer);
		return 8;
	}

	}//for
	

	}

	if((commandid == SGIP_QUERYROUTE_RESP)
		||(commandid == SGIP_TRACE_RESP))
	{
		if((offset_body>command_len)||(offset != bodylength))
		{
			//printf(" Send:The total length check error 1 in SGIP_Send!\n");
			//printf("offset_body = %d,command_len = %d\n",offset_body,command_len);
			//printf("offset = %d,bodylength = %d\n",offset,bodylength);			
			free(buffer);
			return 8;
		}
	}
	else
	{
		if((offset_body > command_len)||(offset_body+3 < command_len)
			||(offset != bodylength))
		{
			//printf(" Send:The total length check error 2 in SGIP_Send!\n");
			//printf("offset_body = %d,command_len = %d\n",offset_body,command_len);
			//printf("offset = %d,bodylength = %d\n",offset,bodylength);			
			free(buffer);
			return 8;
		}
	}

	//Begin to send message
	result = write_all(m_sockfd,buffer,bodylength);

    if (storePackFlag)
    {
        memcpy(bufPackage, buffer, bodylength);
    }

    free(buffer);
    buffer = NULL;
    if(result != bodylength)
    {
	return SEND_DATA_FAILED;
    }
	return 0;

}

int SGIP::SGIP_BIND_Send(SGIP_BIND_BODY *bind_body)
{
	int ret;
	// Send Message Header and Body
    int totallength=LEN_SGIP_HEADER+LEN_SGIP_BIND;
	ret = SGIP_Send(SGIP_BIND, bind_body, totallength);
	return ret;
}

int SGIP::SGIP_BIND_RESP_Send(SGIP_BIND_RESP_BODY *bind_resp_body)
{
	// Send Message Header and Body
	int ret = -1;
	int totallength=LEN_SGIP_HEADER	+LEN_SGIP_BIND_RESP;
	ret = SGIP_Send(SGIP_BIND_RESP, bind_resp_body, totallength);
	return ret;
}

int SGIP::SGIP_SUBMIT_Send(SGIP_SUBMIT_BODY *submit_body,SGIP_HEADER *header)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_SUBMIT+submit_body->UserCount*21+submit_body->MessageLength;
        int ret = -1;
        int len = strlen(m_national_code);
        char national_code[21];
	strcpy(national_code,m_national_code);

	if ( (strlen (submit_body->ChargeNumber) != 0)
		&& (strncmp(submit_body->ChargeNumber, "000000000000000000000", 21) != 0)
		&& (strncmp(submit_body->ChargeNumber,m_national_code,len) != 0))
	{
		strcat(national_code,submit_body->ChargeNumber);
		strcpy(submit_body->ChargeNumber,national_code);
	}
        
	for(int i=0;i<submit_body->UserCount;i++)
	{
		strcpy(national_code,m_national_code);
		if(strncmp(submit_body->UserNumber,m_national_code,len) != 0)
		{
			strcat(national_code,submit_body->UserNumber);
			strcpy(submit_body->UserNumber,national_code);
		}
	}
	// Send Message Header and Body
	ret = SGIP_Send(SGIP_SUBMIT, submit_body,totallength, header);
	return ret;
}

int SGIP::SGIP_SUBMIT_RESP_Send(SGIP_SUBMIT_RESP_BODY *submit_resp_body)
{
	int ret = -1;
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_SUBMIT_RESP;
	ret = SGIP_Send(SGIP_SUBMIT_RESP, submit_resp_body, totallength);
	return ret;
}

int SGIP::SGIP_DELIVER_Send(SGIP_DELIVER_BODY *deliver_body,SGIP_HEADER *header)
{
	int totallength = LEN_SGIP_HEADER+LEN_SGIP_DELIVER+deliver_body->MessageLength;
	int ret = -1;
	int len = strlen(m_national_code);
	char national_code[21];
	strcpy(national_code,m_national_code);
	if(strncmp(deliver_body->UserNumber,m_national_code,len) != 0)
	{
		strcat(national_code,deliver_body->UserNumber);
		strcpy(deliver_body->UserNumber,national_code);
	}
	
	// Send Message Header and Body
	ret = SGIP_Send(SGIP_DELIVER, deliver_body,totallength,header);
	return ret;
}

int SGIP::SGIP_DELIVER_RESP_Send(SGIP_DELIVER_RESP_BODY *deliver_resp_body)
{
	int ret = -1;
	int totallength = LEN_SGIP_HEADER+LEN_SGIP_DELIVER_RESP;
	ret = SGIP_Send(SGIP_DELIVER_RESP, deliver_resp_body, totallength);
	return ret;
}

int SGIP::SGIP_UNBIND_Send()
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_UNBIND;
	int ret = -1;
	ret = SGIP_Send(SGIP_UNBIND, NULL, totallength);
	return ret;
}

int SGIP::SGIP_UNBIND_RESP_Send()
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_UNBIND_RESP;
	int ret = -1;
	ret = SGIP_Send(SGIP_UNBIND_RESP, NULL, totallength);
	return ret;
}

int SGIP::SGIP_REPORT_Send(SGIP_REPORT_BODY *report_body,SGIP_HEADER *header)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_REPORT;
	int ret = -1;
	int len = strlen(m_national_code);
	char national_code[21];
	strcpy(national_code,m_national_code);
	if(strncmp(report_body->UserNumber, m_national_code,len) != 0)
	{
		strcat(national_code, report_body->UserNumber);
		strcpy(report_body->UserNumber, national_code);
	}

	ret = SGIP_Send(SGIP_REPORT, report_body, totallength,header);
	return ret;
}
	
int SGIP::SGIP_REPORT_RESP_Send(SGIP_REPORT_RESP_BODY *report_resp_body)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_REPORT_RESP;
	int ret = -1;
	ret = SGIP_Send(SGIP_REPORT_RESP, report_resp_body, totallength);
	return ret;
}

int SGIP::SGIP_ADDSP_Send(SGIP_ADDSP_BODY *addsp_body)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_ADDSP;
	int ret = -1;
	ret = SGIP_Send(SGIP_ADDSP, addsp_body, totallength);
	return ret;
}

int SGIP::SGIP_ADDSP_RESP_Send(SGIP_ADDSP_RESP_BODY *addsp_resp)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_ADDSP_RESP;
	int ret = SGIP_Send(SGIP_ADDSP_RESP, addsp_resp, totallength);
	return ret;
}

int SGIP::SGIP_MODIFYSP_Send(SGIP_MODIFYSP_BODY *modifysp_body)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_MODIFYSP;
	int ret = SGIP_Send(SGIP_MODIFYSP, modifysp_body, totallength);
	return ret;
}

int SGIP::SGIP_MODIFYSP_RESP_Send(SGIP_MODIFYSP_RESP_BODY *modifysp_resp)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_MODIFYSP_RESP;
	int ret = SGIP_Send(SGIP_MODIFYSP_RESP, modifysp_resp, totallength);
	return ret;
}

int SGIP::SGIP_DELETESP_Send(SGIP_DELETESP_BODY *deletesp_body)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_DELETESP;
	int ret = SGIP_Send(SGIP_DELETESP, deletesp_body, totallength);
	return ret;
}

int SGIP::SGIP_DELETESP_RESP_Send(SGIP_DELETESP_RESP_BODY *deletesp_resp)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_DELETESP_RESP;
	int ret = SGIP_Send(SGIP_DELETESP_RESP, deletesp_resp, totallength);
	return ret;
}

int SGIP::SGIP_QUERYROUTE_Send(SGIP_QUERYROUTE_BODY *queryroute_body)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_QUERYROUTE;
	int ret = SGIP_Send(SGIP_QUERYROUTE, queryroute_body, totallength);
	return ret;
}

int SGIP::SGIP_QUERYROUTE_RESP_Send(SGIP_QUERYROUTE_RESP_BODY *queryroute_resp)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_QUERYROUTE_RESP+queryroute_resp->Count*87;
	int ret = SGIP_Send(SGIP_QUERYROUTE_RESP, queryroute_resp, totallength);
	return ret;
}

int SGIP::SGIP_ADDTELESEG_Send(SGIP_ADDTELESEG_BODY *addteleseg_body)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_ADDTELESEG;
	int ret = SGIP_Send(SGIP_ADDTELESEG, addteleseg_body, totallength);
	return ret;
}

int SGIP::SGIP_ADDTELESEG_RESP_Send(SGIP_ADDTELESEG_RESP_BODY *addteleseg_resp)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_ADDTELESEG_RESP;
	int ret = SGIP_Send(SGIP_ADDTELESEG_RESP, addteleseg_resp, totallength);
	return ret;
}

int SGIP::SGIP_MODIFYTELESEG_Send(SGIP_MODIFYTELESEG_BODY *modifyteleseg_body)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_MODIFYTELESEG;
	int ret = SGIP_Send(SGIP_MODIFYTELESEG, modifyteleseg_body, totallength);
	return ret;
}

int SGIP::SGIP_MODIFYTELESEG_RESP_Send(SGIP_MODIFYTELESEG_RESP_BODY *modifyteleseg_resp)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_MODIFYTELESEG_RESP;
	int ret = SGIP_Send(SGIP_MODIFYTELESEG_RESP, modifyteleseg_resp, totallength);
	return ret;
}

int SGIP::SGIP_DELETETELESEG_Send(SGIP_DELETETELESEG_BODY *deleteteleseg_body)
{
    int totallength=LEN_SGIP_HEADER+LEN_SGIP_DELETETELESEG;
	int ret = SGIP_Send(SGIP_DELETETELESEG, deleteteleseg_body, totallength);
	return ret;
}

int SGIP::SGIP_DELETETELESEG_RESP_Send(SGIP_DELETETELESEG_RESP_BODY *deleteteleseg_resp)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_DELETETELESEG_RESP;
	int ret = SGIP_Send(SGIP_DELETETELESEG_RESP, deleteteleseg_resp, totallength);
	return ret;
}

int SGIP::SGIP_ADDSMG_Send(SGIP_ADDSMG_BODY *addsmg_body)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_ADDSMG;
	int ret = SGIP_Send(SGIP_ADDSMG, addsmg_body, totallength);
	return ret;
}

int SGIP::SGIP_ADDSMG_RESP_Send(SGIP_ADDSMG_RESP_BODY *addsmg_resp)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_ADDSMG_RESP;
	int ret = SGIP_Send(SGIP_ADDSMG_RESP, addsmg_resp, totallength);
	return ret;
}

int SGIP::SGIP_MODIFYSMG_Send(SGIP_MODIFYSMG_BODY *modifysmg_body)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_MODIFYSMG;
	int ret = SGIP_Send(SGIP_MODIFYSMG, modifysmg_body, totallength);
	return ret;
}

int SGIP::SGIP_MODIFYSMG_RESP_Send(SGIP_MODIFYSMG_RESP_BODY *modifysmg_resp)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_MODIFYSMG_RESP;
	int ret = SGIP_Send(SGIP_MODIFYSMG_RESP, modifysmg_resp, totallength);
	return ret;
}

int SGIP::SGIP_DELETESMG_Send(SGIP_DELETESMG_BODY *deletesmg_body)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_DELETESMG;
	int ret = SGIP_Send(SGIP_DELETESMG, deletesmg_body, totallength);
	return ret;
}

int SGIP::SGIP_DELETESMG_RESP_Send(SGIP_DELETESMG_RESP_BODY *deletesmg_resp)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_DELETESMG_RESP;
	int ret = SGIP_Send(SGIP_DELETESMG_RESP, deletesmg_resp, totallength);
	return ret;
}

int SGIP::SGIP_CHECKUSER_Send(SGIP_CHECKUSER_BODY *checkuser_body)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_CHECKUSER;
	int ret = SGIP_Send(SGIP_CHECKUSER, checkuser_body, totallength);
	return ret;
}

int SGIP::SGIP_CHECKUSER_RESP_Send(SGIP_CHECKUSER_RESP_BODY *checkuser_resp)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_CHECKUSER_RESP;
	int ret = SGIP_Send(SGIP_CHECKUSER_RESP, checkuser_resp, totallength);
	return ret;
}

int SGIP::SGIP_USERRPT_Send(SGIP_USERRPT_BODY *userrpt_body)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_USERRPT;
	int ret = SGIP_Send(SGIP_USERRPT, userrpt_body, totallength);
	return ret;
}

int SGIP::SGIP_USERRPT_RESP_Send(SGIP_USERRPT_RESP_BODY *userrpt_resp)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_USERRPT_RESP;
	int ret = SGIP_Send(SGIP_USERRPT_RESP, userrpt_resp, totallength);
	return ret;
}

int SGIP::SGIP_TRACE_Send(SGIP_TRACE_BODY *trace_body)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_TRACE;
	int ret = SGIP_Send(SGIP_TRACE, trace_body, totallength);
	return ret;
}

int SGIP::SGIP_TRACE_RESP_Send(SGIP_TRACE_RESP_BODY *trace_resp)
{
	int totallength=LEN_SGIP_HEADER+LEN_SGIP_TRACE_RESP+trace_resp->Count*47;
	int ret = SGIP_Send(SGIP_TRACE_RESP, trace_resp, totallength);
	return ret;
}

int SGIP::SGIP_BIND_Recv(SGIP_BIND_BODY *bind_body)
{
	SGIP_BodyRecv(SGIP_BIND, bind_body,m_bodylength);
	return 0;		
}

int SGIP::SGIP_BIND_RESP_Recv(SGIP_BIND_RESP_BODY *bind_resp_body)
{
	SGIP_BodyRecv(SGIP_BIND_RESP, bind_resp_body,m_bodylength);
	return 0;
}

int SGIP::SGIP_SUBMIT_Recv(SGIP_SUBMIT_BODY *submit_body)
{
	int ret = -1;
	char buf[4096], log_buff[300];

	ret = SGIP_SUBMIT_Check((SGIP_SUBMIT_BODY *)m_buffer);
	if(ret != 0)
		return ret;

	SGIP_BodyRecv(SGIP_SUBMIT, submit_body, m_bodylength);

	int len = strlen(m_national_code);
	if(strncmp(submit_body->ChargeNumber,m_national_code,len) == 0)
	{
		memmove(submit_body->ChargeNumber,submit_body->ChargeNumber+len, 11);
	}
	submit_body->ChargeNumber[11] = '\0';
	
	for(int i=0;i<submit_body->UserCount;i++)
	{
		if(strncmp(submit_body->UserNumber+21*i,m_national_code,len) == 0)
		{
			memmove(submit_body->UserNumber+21*i,submit_body->UserNumber+21*i+len, 21-len);
		}
		submit_body->UserNumber[11 + 21*i] = '\0';
	}
	if ( submit_body->MessageCoding == 15)
	{
		submit_body->MessageContent[submit_body->MessageLength] = '\0';
		//暂时没添加，等放在linux后再添加
                 //submit_body->MessageLength = GBToUnicode(submit_body->MessageContent, buf);
		
        		if((submit_body->MessageLength>2048)  || (submit_body->MessageLength<= 0))
		{
//			sprintf (log_buff, "After change, MessageLength check error. MessageLength =%d; %sID[%d] ;\n",
//				submit_body->MessageLength, m_cp_or_smg, m_cp_smg_id);
//			mylogfile->write (log_buff, 1, "SGIP_SUBMIT_Recv");
			return 8;
		}
		memcpy (submit_body->MessageContent, buf, submit_body->MessageLength);
		submit_body->MessageCoding = 8;
	}
	return 0;
}

int SGIP::SGIP_SUBMIT_RESP_Recv(SGIP_SUBMIT_RESP_BODY *submit_resp_body)
{
	SGIP_BodyRecv(SGIP_SUBMIT_RESP, submit_resp_body,m_bodylength);
	return 0;
}

int SGIP::SGIP_DELIVER_Recv(SGIP_DELIVER_BODY *deliver_body)
{
	int ret = -1;
	ret = SGIP_DELIVER_Check((SGIP_DELIVER_BODY*)m_buffer);
	if(ret != 0)
		return ret;

	SGIP_BodyRecv(SGIP_DELIVER, deliver_body,m_bodylength);

	int len = strlen(m_national_code);
	if(strncmp(deliver_body->UserNumber,m_national_code,len) == 0)
	{
		memmove(deliver_body->UserNumber,deliver_body->UserNumber+len, 11);
	}
	deliver_body->UserNumber[11] = '\0';
	
	return 0;	
}

int SGIP::SGIP_DELIVER_RESP_Recv(SGIP_DELIVER_RESP_BODY *deliver_resp_body)
{
	SGIP_BodyRecv(SGIP_DELIVER_RESP, deliver_resp_body,m_bodylength);
	return 0;
}

int SGIP::SGIP_REPORT_Recv(SGIP_REPORT_BODY *report_body)
{
	int ret = -1;
	
	ret = SGIP_REPORT_Check((SGIP_REPORT_BODY*)m_buffer);
	if(ret != 0)
		return ret;

	SGIP_BodyRecv(SGIP_REPORT,report_body, m_bodylength);
	
	int len = strlen(m_national_code);
	if(strncmp(report_body->UserNumber,m_national_code, len) == 0)
	{
		memmove(report_body->UserNumber, report_body->UserNumber+len, 11);
	}
	report_body->UserNumber[11] = '\0';

	return 0;
}

int SGIP::SGIP_REPORT_RESP_Recv(SGIP_REPORT_RESP_BODY *report_resp_body)
{
	SGIP_BodyRecv(SGIP_REPORT_RESP,report_resp_body,m_bodylength);
	return 0;
}

int SGIP::SGIP_ADDSP_Recv(SGIP_ADDSP_BODY *addsp_body)
{
	SGIP_BodyRecv(SGIP_ADDSP,addsp_body,m_bodylength);
	return 0;
}

int SGIP::SGIP_ADDSP_RESP_Recv(SGIP_ADDSP_RESP_BODY *addsp_resp)
{
	SGIP_BodyRecv(SGIP_ADDSP_RESP,addsp_resp,m_bodylength);
	return 0;
}

int SGIP::SGIP_MODIFYSP_Recv(SGIP_MODIFYSP_BODY *modifysp_body)
{
	SGIP_BodyRecv(SGIP_MODIFYSP,modifysp_body,m_bodylength);
   	return 0;
}

int SGIP::SGIP_MODIFYSP_RESP_Recv(SGIP_MODIFYSP_RESP_BODY *modifysp_resp)
{
	SGIP_BodyRecv(SGIP_MODIFYSP_RESP,modifysp_resp,m_bodylength);
	return 0;
}

int SGIP::SGIP_DELETESP_Recv(SGIP_DELETESP_BODY *deletesp_body)
{
	SGIP_BodyRecv(SGIP_DELETESP,deletesp_body,m_bodylength);
	return 0;
}

int SGIP::SGIP_DELETESP_RESP_Recv(SGIP_DELETESP_RESP_BODY *deletesp_resp)
{
	SGIP_BodyRecv(SGIP_DELETESP_RESP,deletesp_resp,m_bodylength);
	return 0;
}

int SGIP::SGIP_QUERYROUTE_Recv(SGIP_QUERYROUTE_BODY *queryroute_body)
{
	SGIP_BodyRecv(SGIP_QUERYROUTE,queryroute_body,m_bodylength);
	return 0;
}

int SGIP::SGIP_QUERYROUTE_RESP_Recv(SGIP_QUERYROUTE_RESP_BODY *queryroute_resp)
{
	SGIP_BodyRecv(SGIP_QUERYROUTE_RESP,queryroute_resp,m_bodylength);
	return 0;
}

int SGIP::SGIP_ADDTELESEG_Recv(SGIP_ADDTELESEG_BODY *addteleseg_body)
{
	SGIP_BodyRecv(SGIP_ADDTELESEG,addteleseg_body,m_bodylength);
	return 0;
}

int SGIP::SGIP_ADDTELESEG_RESP_Recv(SGIP_ADDTELESEG_RESP_BODY *addteleseg_resp)
{
	SGIP_BodyRecv(SGIP_ADDTELESEG_RESP,addteleseg_resp,m_bodylength);
	return 0;
}

int SGIP::SGIP_MODIFYTELESEG_Recv(SGIP_MODIFYTELESEG_BODY *modifyteleseg_body)
{
	SGIP_BodyRecv(SGIP_MODIFYTELESEG,modifyteleseg_body,m_bodylength);
	return 0;
}

int SGIP::SGIP_MODIFYTELESEG_RESP_Recv(SGIP_MODIFYTELESEG_RESP_BODY *modifyteleseg_resp)
{
	SGIP_BodyRecv(SGIP_MODIFYTELESEG_RESP,modifyteleseg_resp,m_bodylength);
	
   	return 0;
}

int SGIP::SGIP_DELETETELESEG_Recv(SGIP_DELETETELESEG_BODY *deleteteleseg_body)
{
	SGIP_BodyRecv(SGIP_DELETETELESEG,deleteteleseg_body,m_bodylength);
	
   	return 0;
}

int SGIP::SGIP_DELETETELESEG_RESP_Recv(SGIP_DELETETELESEG_RESP_BODY *deleteteleseg_resp)
{
	SGIP_BodyRecv(SGIP_DELETETELESEG_RESP,deleteteleseg_resp,m_bodylength);
	return 0;
}

int SGIP::SGIP_ADDSMG_Recv(SGIP_ADDSMG_BODY *addsmg_body)
{
	SGIP_BodyRecv(SGIP_ADDSMG,addsmg_body,m_bodylength);
	
   	return 0;
}

int SGIP::SGIP_ADDSMG_RESP_Recv(SGIP_ADDSMG_RESP_BODY *addsmg_resp)
{
	SGIP_BodyRecv(SGIP_ADDSMG_RESP,addsmg_resp,m_bodylength);
	
   	return 0;
}

int SGIP::SGIP_MODIFYSMG_Recv(SGIP_MODIFYSMG_BODY *modifysmg_body)
{
	SGIP_BodyRecv(SGIP_MODIFYSMG,modifysmg_body,m_bodylength);
	
   	return 0;
}

int SGIP::SGIP_MODIFYSMG_RESP_Recv(SGIP_MODIFYSMG_RESP_BODY *modifysmg_resp)
{
	SGIP_BodyRecv(SGIP_MODIFYSMG_RESP,modifysmg_resp,m_bodylength);
	
   	return 0;
}

int SGIP::SGIP_DELETESMG_Recv(SGIP_DELETESMG_BODY *deletesmg_body)
{
	SGIP_BodyRecv(SGIP_DELETESMG,deletesmg_body,m_bodylength);
	
   	return 0;
}

int SGIP::SGIP_DELETESMG_RESP_Recv(SGIP_DELETESMG_RESP_BODY *deletesmg_resp)
{
	SGIP_BodyRecv(SGIP_DELETESMG_RESP,deletesmg_resp,m_bodylength);
	
   	return 0;
}

int SGIP::SGIP_CHECKUSER_Recv(SGIP_CHECKUSER_BODY *checkuser_body)
{
	SGIP_BodyRecv(SGIP_CHECKUSER,checkuser_body,m_bodylength);
	
   	return 0;
}

int SGIP::SGIP_CHECKUSER_RESP_Recv(SGIP_CHECKUSER_RESP_BODY *checkuser_resp)
{
	SGIP_BodyRecv(SGIP_CHECKUSER_RESP,checkuser_resp,m_bodylength);
	
   	return 0;
}

int SGIP::SGIP_USERRPT_Recv(SGIP_USERRPT_BODY *userrpt_body)
{
	SGIP_BodyRecv(SGIP_USERRPT,userrpt_body,m_bodylength);
	
   	return 0;
}

int SGIP::SGIP_USERRPT_RESP_Recv(SGIP_USERRPT_RESP_BODY *userrpt_resp)
{
	SGIP_BodyRecv(SGIP_USERRPT_RESP,userrpt_resp,m_bodylength);
	
   	return 0;
}

int SGIP::SGIP_TRACE_Recv(SGIP_TRACE_BODY *trace_body)
{
	SGIP_BodyRecv(SGIP_TRACE,trace_body,m_bodylength);
	
   	return 0;
}

int SGIP::SGIP_TRACE_RESP_Recv(SGIP_TRACE_RESP_BODY *trace_resp)
{
	SGIP_BodyRecv(SGIP_TRACE_RESP,trace_resp,m_bodylength);
	
   	return 0;
}

int SGIP::VerifyNumberLength(char *src)
{
	if ((strlen(src) != 13 ) && (strlen(src) != 11))
	{
		return -1;
	}
	return 0;
}

int SGIP::VerifyNumberHeader(char *src)
{
	if (strlen(src) == 13)
	{
		if((strncmp(src, "8613", 4) != 0)&&(strncmp(src, "8615", 4)!=0))
		{
			return -1;
		}
	}
	else
	{
		if((strncmp(src, "13", 2) != 0)&&(strncmp(src, "15", 2)!=0))
		{
			return -1;
		}
	}
	
	return 0;
}

int SGIP::CheckAllZero(char *src)
{
	char charge[22];
	memset(charge,'0',21);
	charge[21]='\0';
	if(strcmp(src,charge) == 0)
		return 0;
	return -1;
}

int SGIP::CheckPhoneNumberValid(char *src)
{
	int ret = -1;
	ret = VerifyNumberLength(src);
	if(ret == -1)
	{
		return -1;
	}
	ret = VerifyNumberHeader(src);
	if(ret == -1)
	{
		return -1;
	}
	return 0;
}

int SGIP::SeparateUserNumber(char *src)
{
	int ret = -1;
	int count = 0;
	char strNumber[14];	

	for(;;)
	{
		memcpy(strNumber, src+21*count, 13);
		strNumber[13] = '\0';
		if(CheckPhoneNumberValid(strNumber) != 0)
		{
			break;
		}
		count ++;
	}
	return count;
}

int SGIP::CheckOneField(char *field)
{
	char *stopstring;
	long value = strtol( field, &stopstring, 10 );
	if((value<0)||(value>99999))
		return -1;
	if(value == 0)
	{
		if(errno==EINVAL)
			return -1;
	}
	return 0;
}

int SGIP::CheckInScope(char *src)
{
	int scope[15] = {9,9,1,9,3,9,2,9,5,9,5,9,9,4,9};
	int value;
	for(int i=0;i<15;i++)
	{
		value = src[i]-'0';
		if((value < 0)||(value >scope[i]))
			return -1;
	}
	if((src[15] !='+')&&(src[15] != '-'))
		return -1;
	return 0;		
}

int SGIP::CheckTimeFormat(char *src)
{
	int len=strlen(src);
	if((len!=0)&&(len!=16))
		return -1;
	if((len!=0) && (CheckInScope(src) != 0))
		return -1;
	return 0;
}

int SGIP::CheckSeqNum(unsigned int seqnum)
{
	int scope[15] = {9,9,1,9,3,9,2,9,5,9,5,9,9,4,9};
	char src[11],*p;
	p = mylltostr(seqnum,src+10);
	src[10]='\0';
	
	if((strlen(p) != 9)&&(strlen(p) != 10))
		return -1;
	
	int off,index;
	unsigned int num = 1000000000;
	if(seqnum<num)
	{
		index = 9;
		off=3;
	}
	else 
	{
		index = 10;
		off =2;
	}
	
	int value;
	for(int i=0;i<index;i++)
	{
		value = p[i]-'0';
		if((value < 0)||(value >scope[i+off]))
			return -1;
	}
	return 0;
}

int SGIP::SGIP_REPORT_Check(SGIP_REPORT_BODY *report_body)
{
	char log_buff[500];
	char tmp_usernum[22];
	
	memcpy (tmp_usernum, report_body->UserNumber, 21);
	tmp_usernum[21] = '\0';
	if(CheckSeqNum(report_body->SubmitSequenceNumber[1]) != 0)
	{
//		sprintf (log_buff, "SubmitSequenceNumber check error. SubmitSequenceNumber[0] = 0x%x SSN[1] = 0x%x; SSN[2] = 0x%x; ReportType=%u; UserNumber=%s; State=%u; ErrorCode=%u; %sID[%d];\n",
//			 report_body->SubmitSequenceNumber[0], report_body->SubmitSequenceNumber[2], report_body->SubmitSequenceNumber[2],
//			 report_body->ReportType, tmp_usernum, report_body->State, report_body->ErrorCode,
//			 m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_REPORT_Check");
		return 9;
	}
	
	int type = report_body->ReportType;
	if((type != 0)&&(type != 1))
	{
//		sprintf (log_buff, "ReportType check error. SubmitSequenceNumber[0] = 0x%x SSN[1] = 0x%x; SSN[2] = 0x%x; ReportType=%u; UserNumber=%s; State=%u; ErrorCode=%u; %sID[%d];\n",
//			 report_body->SubmitSequenceNumber[0], report_body->SubmitSequenceNumber[2], report_body->SubmitSequenceNumber[2],
//			 report_body->ReportType, tmp_usernum, report_body->State, report_body->ErrorCode,
//			 m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_REPORT_Check");
		return 5;
	}
	
	if(CheckPhoneNumberValid(report_body->UserNumber) != 0)
	{
//		sprintf (log_buff, "UserNumber check error. SubmitSequenceNumber[0] = 0x%x SSN[1] = 0x%x; SSN[2] = 0x%x; ReportType=%u; UserNumber=%s; State=%u; ErrorCode=%u; %sID[%d];\n",
//			 report_body->SubmitSequenceNumber[0], report_body->SubmitSequenceNumber[2], report_body->SubmitSequenceNumber[2],
//			 report_body->ReportType, tmp_usernum, report_body->State, report_body->ErrorCode,
//			 m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_REPORT_Check");
		return 5;
	}
	
	int state = report_body->State;
	if((state != 0)&&(state != 1)&&(state != 2))
	{
//		sprintf (log_buff, "State check error. SubmitSequenceNumber[0] = 0x%x SSN[1] = 0x%x; SSN[2] = 0x%x; ReportType=%u; UserNumber=%s; State=%u; ErrorCode=%u; %sID[%d];\n",
//			 report_body->SubmitSequenceNumber[0], report_body->SubmitSequenceNumber[2], report_body->SubmitSequenceNumber[2],
//			 report_body->ReportType, tmp_usernum, report_body->State, report_body->ErrorCode,
//			 m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_REPORT_Check");
		return 5;
	}
	
	if((state == 0)||(state == 1))
	{
		if(report_body->ErrorCode != 0)
		{
//			sprintf (log_buff, "ErrorCode check error.  SubmitSequenceNumber[0] = 0x%x SSN[1] = 0x%x; SSN[2] = 0x%x; ReportType=%u; UserNumber=%s; State=%u; ErrorCode=%u; %sID[%d];\n",
//			 	report_body->SubmitSequenceNumber[0], report_body->SubmitSequenceNumber[2], report_body->SubmitSequenceNumber[2],
//			 	report_body->ReportType, tmp_usernum, report_body->State, report_body->ErrorCode,
//			 	m_cp_or_smg, m_cp_smg_id);
//			mylogfile->write (log_buff, 1, "SGIP_REPORT_Check");
			return 5;
		}
	}
	return 0;
	
}

int SGIP::SGIP_SUBMIT_Check(SGIP_SUBMIT_BODY *submit_body)
{
	struct tm now;
	time_t current_time;
	unsigned int cur_seq_no;
	char log_buff[300];

	//check sequence number
	current_time = time(NULL);
	localtime_r(&current_time, &now);	
	
	cur_seq_no = (now.tm_mon+1)*100000000+now.tm_mday*1000000+now.tm_hour*10000+now.tm_min*100+now.tm_sec;
	
	if ((m_is_cp == 1) && (m_header. Sequence_Number[0] != (m_cp_smg_id+300000)))
	{
//		sprintf (log_buff, "Sequence_Number check error. m_cp_node_id = %d, Sequence_Number[0] =%d; %sID[%d];\n",
//			m_cp_smg_id+300000, m_header. Sequence_Number[0], m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_SUBMIT_Check");
		return 9;
	}
	if (labs (cur_seq_no - m_header. Sequence_Number[1]) > 1000000)
	{
//		sprintf (log_buff, "Sequence_Number check error. Sequence_Number[1] =%d; %sID[%d];\n",
//			m_header. Sequence_Number[1], m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_SUBMIT_Check");
		return 9;
	}
	/*
	for (int i=0; i<32; i++)
	{
		if  ((m_header. Sequence_Number[2] == recv_seqno_buf[i]) 
			&& (i != recv_seqno_index ))
		{
			return 9;
		}
	}
	*/
	//check SPNumber
	if(strlen(submit_body->SPNumber) == 0)
	{
//		sprintf (log_buff, "SPNumber check error. SPNumber =%s; %sID[%d];\n",
//			submit_body->SPNumber, m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_SUBMIT_Check");
		return 5;
	}
	//printf ("spname check ok!\n");

	//check ChargeNumber
   	 int errflag = 1;
   	 
   	 if ((m_is_cp == 1)  && (strcmp (m_cp_phone,  submit_body->SPNumber) != 0))
   	 {
//		sprintf (log_buff, "SPNumber check error. SPNumber =%s; m_cp_phone=%s; %sID[%d];\n",
//			submit_body->SPNumber, m_cp_phone, m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_SUBMIT_Check");
   	 	return 5;
   	}
   	
	if(strlen(submit_body->ChargeNumber) == 0)
		errflag = 0;
	else if(CheckAllZero(submit_body->ChargeNumber) == 0)
		errflag = 0;
	else if(CheckPhoneNumberValid(submit_body->ChargeNumber) == 0)
		errflag = 0;
	
	if(errflag == 1)
	{
//		sprintf (log_buff, "ChargeNumber check error. ChargeNumber =%s; %sID[%d];\n",
//			submit_body->ChargeNumber, m_cp_phone, m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_SUBMIT_Check");
		return 6;
	}

	//check user count	
	int usercount=submit_body->UserCount;
	if((usercount<1)||(usercount>100))
	{
//		sprintf (log_buff, "UserCount check error. UserCount =%d; %sID[%d];\n",
//			submit_body->UserCount, m_cp_phone, m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_SUBMIT_Check");
		return 5;
	}
	//printf ("usercount check ok!\n");
	
	//check user number
	int cur_usercount = SeparateUserNumber(submit_body->UserNumber);
	if(cur_usercount != usercount)
	{
//		sprintf (log_buff, "UserCount check error. UserCount =%d; True UserCount=%d; %sID[%d];\n",
//			submit_body->UserCount, cur_usercount, m_cp_phone, m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_SUBMIT_Check");						
		return 5;
	}
	//printf ("seperate check ok!\n");

	//check corp ID
    	if(CheckOneField(submit_body->CorpID) != 0)
	{
///		sprintf (log_buff, "CorpID check error. CorpID =%s; %sID[%d];\n",
//			submit_body->CorpID, m_cp_phone, m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_SUBMIT_Check");
		return 5;
	}
	//printf ("corpid check ok!\n");

	//check fee type
	if((submit_body->FeeType != 0)
		&&(submit_body->FeeType != 1)
		&&(submit_body->FeeType != 2)
		&&(submit_body->FeeType != 3)
		&&(submit_body->FeeType != 4))
	{
//		sprintf (log_buff, "FeeType check error. FeeType =%d; %sID[%d];\n",
//			submit_body->FeeType, m_cp_phone, m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_SUBMIT_Check");
		return 5;
	}
	//printf ("feetype check ok!\n");

	//check fee value
	if(CheckOneField(submit_body->FeeValue) != 0)
	{
//		sprintf (log_buff, "FeeValue check error. FeeValue =%s; %sID[%d];\n",
//			submit_body->FeeValue, m_cp_phone, m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_SUBMIT_Check");
		return 5;
	}
	//printf ("feevalue check ok!\n");

	//check given value
	if(CheckOneField(submit_body->GivenValue) != 0)
	{
//		sprintf (log_buff, "GivenValue check error. GivenValue =%s; %sID[%d];\n",
//			submit_body->GivenValue, m_cp_phone, m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_SUBMIT_Check");
		return 5;
	}
	//printf ("givenvalue check ok!\n");
	
	//check agent flag
	int agentflag=submit_body->AgentFlag;
	if((agentflag!=0)&&(agentflag!=1))
	{
//		sprintf (log_buff, "AgentFlag check error. AgentFlag =%d; %sID[%d];\n",
//			submit_body->AgentFlag, m_cp_phone, m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_SUBMIT_Check");
		return 5;
	}
	//printf ("agentflag check ok!\n");

	//check mo relate to mt flag
	int motomt=submit_body->MorelatetoMTFlag;
	if((motomt!=0)&&(motomt!=1)&&(motomt!=2)&&(motomt!=3))
	{
//		sprintf (log_buff, "MorelatetoMTFlag check error. MorelatetoMTFlag =%d; %sID[%d];\n",
//			submit_body->MorelatetoMTFlag, m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_SUBMIT_Check");
		return 5;
	}
	//printf ("momt check ok!\n");

	//check priority
	int priority=submit_body->Priority;
	if((priority<0)||(priority>9))
	{
//		sprintf (log_buff, "Priority check error. Priority =%d; %sID[%d];\n",
//			submit_body->Priority, m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_SUBMIT_Check");
		return 5;
	}
	//printf ("priority check ok!\n");

	//check expire time
	if(CheckTimeFormat(submit_body->ExpireTime) != 0)
	{
//		sprintf (log_buff, "ExpireTime check error. ExpireTime =%s; %sID[%d];\n",
//			submit_body->ExpireTime,  m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_SUBMIT_Check");
		return 5;
	}
	//printf ("expiretime check ok!\n");

	//check schedule time
	if(CheckTimeFormat(submit_body->ScheduleTime) != 0)
	{
//		sprintf (log_buff, "ScheduleTime check error. ScheduleTime =%s; %sID[%d];\n",
//			submit_body->ScheduleTime,  m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_SUBMIT_Check");
		return 5;	
	}
	//printf ("scheduletime check ok!\n");

	//check message coding
	int msgcode = submit_body->MessageCoding;
	if((msgcode != 0) && (msgcode != 3 )
		&& (msgcode != 4) && (msgcode != 8)
		&& (msgcode != 15))
	{
//		sprintf (log_buff, "MessageCoding check error. MessageCoding =%d; %sID[%d];\n",
//			submit_body->MessageCoding,  m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_SUBMIT_Check");
		return 5;
	}

	//check message length
	int meslen=submit_body->MessageLength;
	if((meslen<=0)||(meslen>2048))
	{
//		sprintf (log_buff, "MessageLength check error. MessageLength =%d; %sID[%d];\n",
//			submit_body->MessageLength,  m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_SUBMIT_Check");
		return 8;	
	}
	
	return 0;
}

int SGIP::SGIP_DELIVER_Check(SGIP_DELIVER_BODY *deliver_body)
{
	char log_buff[300];
	//check user number
	if(CheckPhoneNumberValid(deliver_body->UserNumber) != 0)
	{
//		sprintf (log_buff, "UserNumber check error. UserNumber =%s; %sID[%d];\n",
//			deliver_body->UserNumber,  m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_DELIVER_Check");
		return 5;
	}

	//check sp number
	if(strlen(deliver_body->SPNumber) == 0)
	{
//		sprintf (log_buff, "SPNumber check error. SPNumber =%s; %sID[%d];\n",
//			deliver_body->SPNumber,  m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_DELIVER_Check");
		return 5;
	}
	
	//check message length
	int meslen=deliver_body->MessageLength;
	if((meslen<0)||(meslen>2048))
	{
//		sprintf (log_buff, "MessageLength check error. MessageLength =%d; %sID[%d];\n",
//			deliver_body->MessageLength,  m_cp_or_smg, m_cp_smg_id);
//		mylogfile->write (log_buff, 1, "SGIP_DELIVER_Check");
		return 8;	
	}
		
	return 0;
}

void SGIP::storePackage(int storeFlag)
{
    storePackFlag = storeFlag;
    if (storeFlag == 1)
        memset(bufPackage, 0, SGIP_MAX_MES_LEN);
}

void SGIP::dump(char *dest)
{
	if (storePackFlag == 1)
        dumpMemory((unsigned char *)bufPackage, packLength, dest);
    else
        dest[0] = '\0';
}

