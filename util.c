#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <fnmatch.h>
#include <dirent.h>
#include "util.h"
#include "err.h"

int write_file(char *file, char *format, ...)
{
  va_list args;
  char temp[6000];
  FILE *fp =NULL;
  time_t t;
  struct tm *ptm;

  time(&t);
  ptm =localtime(&t);

  if((fp =fopen(file, "a")) ==NULL)
    return EOPENFILE;

  va_start(args, format);
  vsprintf(temp, format, args);
  va_end(args);
  if(temp[0] && temp[strlen(temp)-1] =='\n')
    temp[strlen(temp)-1] =0;
  fprintf(fp, "%s\n",temp);
  fclose(fp);

  return 0;

}

void ucs2_decoding(char *str,int len)
{
  wchar_t wstr_dest[256] = {0};
  unsigned short *wsrc = (unsigned short *)str;
  int wstrlen = len>>1;
  unsigned short hi,lo;
  for(int i=0;i<wstrlen;++i)
  {
    hi = (wsrc[i] & 0x00FF)<<8;
    lo = (wsrc[i] & 0xFF00)>>8;
    wstr_dest[i] = hi|lo;
  }
  wstr_dest[wstrlen] = 0;
  memset(str,0,len);
  wcstombs(str, wstr_dest, len);
}

/*
int code_convert(char *from_charset,char *to_charset,char *inbuf,int inlen,\
		char *outbuf,int outlen)
{
  iconv_t cd;
  int rc;
  char **pin = &inbuf;
  char **pout = &outbuf;
  
  cd = iconv_open(to_charset,from_charset);
  if(cd==0)
  {
    return -1;
  }
  memset(outbuf,0,outlen);
  if(iconv(cd,pin,(size_t *)&inlen,pout,(size_t *)&outlen)==-1)
  {
    return -1;
  }
  iconv_close(cd);

  return 0;
}
*/

void gen_rand_str(char s[],int number)
{
  char str[64]="00123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  int i;
  char ss[2];
  
  strcpy(s,"");
  srand((unsigned int)time((time_t *)NULL));
  for(i=0;i<number;i++)
  {
    sprintf(ss,"%c",str[(rand()%62)+1]);
    strcat(s,ss);
  }
  printf("s=%s\n",s);
}

void dumpMemory(unsigned char * buf, int len,char *str)
{
   int i;
   FILE * fp;
   char timestr[32]; 
   fp = fopen("dump.txt","at+");
   if( fp == NULL ){
     fp = fopen("dump.txt","wt+");
   }
   if( fp == NULL ){
     perror("fopen");
     return; 
   }
   get_full_time_str(timestr);
   fprintf(fp,"DumpMemory(%s:%d),%s\n",str,len,timestr);
   for( i = 0 ; i < len; i++)
   {
     fprintf(fp,"%02X ",buf[i]);
     if( i%10==9)fprintf(fp," --- ");
     if( i%20==19)fprintf(fp,"\n");
   } 
   fprintf(fp,"\n");
   fprintf(fp,"\n");
   fclose(fp);
} 

int diff_month(char *time1,char *time2)
{
  int year1,year2,month1,month2;
  int result;

  sscanf(time1,"%4d-%2d",&year1,&month1);
  sscanf(time2,"%4d-%2d",&year2,&month2);
  if(year1==year2)
  {
    return (month2-month1);
  }
  else if(year1>year2)
  {
     return 0; 
  }
  else
  {
    result=(12-month1)+(year2-year1-1)*12+month2;
    return result;
  }
  return 1;   
}

bool IsProcConflict(string prog_name)
{
	string ps;
	char buf[512];
	FILE *ptr;

	ps = "ps -ef | grep -v \\\\.sh | grep -v grep |grep -v vi | grep -c " + prog_name;
	if((ptr = popen(ps.c_str(), "r")) != NULL) {
		while (fgets(buf, 512, ptr) != NULL) {
			if(atoi(buf) >= 2) {
				pclose(ptr);
				return false;
			}
		}
		pclose(ptr);
	}
	return true;
}

char *GetFilePath(char *file, char *path)
{
  int i, len =strlen(file);

  for(i =len-1; i >-1; i--)
    if(file[i] =='\\' || file[i] =='/' || file[i] ==':') break;
  if(i ==0) strcpy(path, ".");
  else
  {
    strcpy(path, file);
    path[i] =0;
  }
  return path;
}

char *GetFileName(char *file)
{
  int i, len =strlen(file);

  for(i =len-1; i >-1; i--)
    if(file[i] =='\\' || file[i] =='/' || file[i] ==':') break;
  if(i ==0) return file;
  else return &file[i+1];
}

char *del_all_spaces(char *p)
{
  char buf[2000];
  char *p1 =&buf[0], *pp =p;

  while(*pp)
  {
    if(*pp !=' ') *p1++ =*pp;
    pp++;
  }
  *p1 =0;
  strcpy(p, buf);
  return p;
}

char *del_lr_spaces(char *pbuf)
{
  char *p =pbuf;
  int i =0;

  i =0;
  while(*p ==' ') p++;
  strcpy(pbuf, p);

  i =strlen(pbuf);
  while(i >=0 && *(p + i-1) ==' ') i--;
  *(p+i) =0;

  return pbuf;
}

char *del_rn1(char *pbuf)
{
  char *p;

  if((p =strchr(pbuf, '\r')) !=NULL) *p =' ';
  if((p =strchr(pbuf, '\n')) !=NULL) *p =' ';

  return pbuf;
}

char *del_rn(char *pbuf)
{
  char *p;

  if((p =strchr(pbuf, '\r')) !=NULL) *p =0;
  if((p =strchr(pbuf, '\n')) !=NULL) *p =0;

  return pbuf;
}

void getmydate(DATETYPE *d)
{
	time_t ti;
	struct tm *tm;
	time(&ti);
	tm = localtime(&ti);
	d->year = tm->tm_year + 1900;
	d->month = tm->tm_mon + 1;
	d->day = tm->tm_mday;
}

void getlastmonth(char *pbuf)
{
  DATETYPE d;
  time_t ti;
  struct tm *tm;
  time(&ti);
  tm=localtime(&ti);
  d.year=tm->tm_year + 1900;
  d.month=tm->tm_mon + 1;
  d.month=d.month-1;
  if(d.month<=0)
  {
    d.month=12;
    d.year=d.year-1;
  }
  sprintf(pbuf,"%4d%02d",d.year,d.month);
}

void getmytime(TIMETYPE *t)
{
 	time_t ti;
	struct tm *tm;
	time(&ti);
	tm = localtime(&ti);
	t->hour = tm->tm_hour;
	t->min = tm->tm_min;
	t->sec = tm->tm_sec;
}

void get_full_time(char *pbuf)
{
  time_t ti;
  struct tm *tm;
  time(&ti);
  tm=localtime(&ti);
  sprintf(pbuf,"%4d-%02d-%02d %02d:%02d:%02d",(tm->tm_year+1900),\
	(tm->tm_mon+1),tm->tm_mday,tm->tm_hour,tm->tm_min,tm->tm_sec);  
}
/*
int weekofday()
{
  time_t ti;
  struct tm *tm;
  int year,month,day,y,c;
  int ret;
  char buf[8],ybuf[4],cbuf[4];

  time(&ti);
  tm=localtime(&ti);
  
  year= tm->tm_year+1900;
  sprintf(buf,"%d",year);
  substring(buf,cbuf,0,2);
  c = atoi(cbuf);
  //printf("cbuf=%s\n",cbuf);
  substring(buf,ybuf,2,2);
  //printf("ybuf=%s\n",ybuf);
  y = atoi(ybuf);
  month = tm->tm_mon+1;
  day = tm->tm_mday;
  if(month<=2)
    month = month + 12;
  
  ret = (y+((int)(y/4))+((int)(c/4))-2*c+((int)(26*(month+1)/10))+day-1)%7;
  //printf("ret=%d\n",ret); 
  return ret;
}
*/
//dayofweek:return current day of week eg. Mon Tue...
void dayofweek(char *daystr)
{
    time_t t = time(0); 
    strftime( daystr, sizeof(daystr), "%a",localtime(&t) ); 
}

void get_sequence_str(char *pbuf)
{
  DATETYPE d;
  TIMETYPE t;
  memset((char *)&d, 0,  sizeof(d));
  getmydate(&d);
  memset((char *)&t, 0, sizeof(t));
  getmytime(&t);
  sprintf(pbuf, "%02d%02d%02d%02d%02d",d.month, d.day, t.hour, t.min, t.sec);
}

void get_date2_str(char *pbuf)
{
  	DATETYPE d;
        memset((char *)&d, 0,  sizeof(d));
        getmydate(&d);
        sprintf(pbuf, "%4d-%02d-%02d", d.year, d.month, d.day);
}

void get_date_str(char *pbuf)
{
	DATETYPE d;
	memset((char *)&d, 0,  sizeof(d));
	getmydate(&d);
	sprintf(pbuf, "%4d%02d%02d", d.year, d.month, d.day);
}

void get_time_str(char *pbuf)
{
	TIMETYPE t;
	memset((char *)&t, 0, sizeof(t));
	getmytime(&t);
	sprintf(pbuf,"%02d%02d%02d", t.hour, t.min, t.sec);
}

void get_full_time_str(char *pbuf)
{
	char pbuf1[16], pbuf2[16];
	get_date_str(pbuf1);
	get_time_str(pbuf2);
	strcpy(pbuf, pbuf1);
	strcat(pbuf,pbuf2);
}

int month_day(int year, int month )
{
  int i, da, j;
  static int sc4[2][13]={{31,28,31,30,31,30,31,31,30,31,30,31},
                         {31,29,31,30,31,30,31,31,30,31,30,31} };

  i = year%4==0&&year%100!=0||year%400==0;
  j = month - 1;
  da = sc4[i][j];
  return( da );
}

int is_date(char *value)
{
	int year=0, month=0, day=0;
  	char newvalue[11], tmpbuf[16],strTmp[20];
 	short	i,j;

	/* david cai update date format judge condition  98/9/03 */

  	if( (i=strlen( value ))>10 || i<6 ){
		//show_help( "日期格式为:YYYY/MM/DD 或 YYYYMMDD 或 YYMMDD 或YY/MM/DD" );
    		return( 0 );
  	}

  	for(j=0;value[j]!=0;j++){
		if( value[j]=='/'){
			j=10000;
			break;
		} else
			continue;
	}

	if( j==10000 ) {/* with  */
  		sscanf( value, "%d/%d/%d", &year, &month, &day ); 
		if( year<100 )
			year+=1900;
	} else if( i==8 ){
  		sscanf( value, "%4d%2d%2d", &year, &month, &day ); 
	} else if( i==6 ){
  		sscanf( value, "%2d%2d%2d", &year, &month, &day ); 
		year+=1900;
	} else {
  		//show_help( "日期格式为:YYYY/MM/DD 或 YYYYMMDD 或 YYMMDD 或YY/MM/DD" );
    		return( 0 );
	}
  
  	
  	if( year < 1900 || year > 9999 ) {
    		//show_help( "2日期格式为:YYYY/MM/DD 或 YYYYMMDD 或 YYMMDD 或YY/MM/DD" );
    		return( 0 );
  	}
  	if( month < 1 || month > 12 ) {
    		//show_help( "3日期格式为:YYYY/MM/DD 或 YYYYMMDD 或 YYMMDD 或YY/MM/DD" );
    		return( 0 );
  	}
  	if( day < 1 || day > 31 ) {
    		//show_help( "4日期格式为:YYYY/MM/DD 或 YYYYMMDD 或 YYMMDD 或YY/MM/DD" );
    		return( 0 );
  	}
  	if( day > month_day( year, month ) ) {
    		//show_help( "5日期格式为:YYYY/MM/DD 或 YYYYMMDD 或 YYMMDD 或YY/MM/DD" );
    		return( 0 );
  	}

  	return( 1 );	
}

int is_time(char *value)
{
	int hour, minute,second;
  	char tmpbuf[16], new_value[16];

 	 hour = -1;
  	minute = -1;
  	sscanf( value, "%2d%2d%2d", &hour, &minute ,&second);
  	if( hour < 0 || hour > 23 ) {
    		//show_help( "时间格式为:HHMMSS" );
    		return( 0 );
  	}
  	if( minute < 0 || minute > 59 ) {
    		//show_help( "时间格式为:HHMMSS" );
    		return( 0 );
  	}
  	if(second < 0 || second > 59 ) {
    		//show_help( "时间格式为:HHMMSS" );
    		return( 0 );
  	}
 
  	return( 1 );  
}

int is_date_time(char *value)
{
	char date_value[16], time_value[16];

  	sscanf( value, "%8s%6s", date_value, time_value );
  	
  	if( is_date( date_value ) != 1 ) {
    		//show_help( "日期时间格式为:YYYY/MM/DD HH:MM" );
    		return( 0 );
  	}
  	if( is_time( time_value ) != 1 ) {
    		//show_help( "日期时间格式为:YYYY/MM/DD HH:MM" );
    		return( 0 );
  	}
 	/* sprintf( value, "%s %s", date_value, time_value );  */
  	return( 1 );
}

void date_to_datestr(DATETYPE *d, char *pbuf)
{
	sprintf(pbuf, "%4d%02d%02d", d->year, d->month, d->day);
}

void time_to_timestr(TIMETYPE *t, char *pbuf)
{
	sprintf(pbuf,"%02d%02d%02d", t->hour, t->min, t->sec);
}

void datestr_to_date(char *datestr, DATETYPE *d) 
{
	sscanf( datestr, "%4d%2d%2d", &d->year, &d->month, &d->day );
}

void timestr_to_time(char *timestr, TIMETYPE *t)
{
	sscanf( timestr, "%2d%2d%2d", &t->hour, &t->min, &t->sec );
}

int isnumstr(char *s)
{
	char *p = s;
	if(*p=='\0')
	{
		return 0;
	}
	else
	{
		if(*p<=48 || *p>57)
		{
			return 0;
		}
	}
	p++;
	
	while(*p!='\0')
   	{
       		if (*p<48 || *p>57) 
       		{
			return 0;
		}
		else
		{
			 p++;
		}
   	}
		
	return 1;
}

int isfloatstr(char *s)
{
	char *p = s;
	int dotnum = 0;
	int flag = 0;
	if(*p=='\0')
	{
		printf("failed 0!\n");
		return 0;
	}
	
	if(!strcmp(p,"-.") || !strcmp(p, "."))
	{
		printf("failed 1!\n");
		return 0;
	}

	while(*p!='\0')
	{
		if(*p=='.')
		{
			dotnum++;
		}
		p++;
	}
	if(dotnum>1)
	{
		printf("failed 2!\n");
		return 0;
	}
	
	p = s;
	if(*p=='.' || *p=='-' || ((*p>=48)&&(*p<=57)))
	{	
		if(*p=='.')
		{
			flag = 1;
		}
		p++;
		while(*p!='\0')
		{
			if(flag==1)
			{
				if(*p=='-')	
				{
					printf("failed 3!\n");
					return 0;
				}	
			}
			else
			{
				if((!((*p>=48)&&(*p<=57)))&&(*p!='.'))
				{
					printf("p=%c failed 4!\n",*p);	
					return 0;
				}
			}	
			p++;	
		}
	}
	else if((*p!='-')&&(*p!='.')&&((*p<48)||(*p>57)))
	{
		printf("failed 5!\n");	
		return 0;
	}

	return 1;
}

int move_file(char *filename, char *src_path, char *dest_path, char *suffix)
{
	char dest_file[255], src_file[255];
	char full_time_str[32];	

	get_full_time_str(full_time_str);	
	sprintf(src_file,"%s%s",src_path, filename);
	sprintf(dest_file,"%s%s%s.%s", dest_path, filename, full_time_str, suffix);
	printf("src_file:%s\n",src_file);	
	printf("dest_file:%s\n",dest_file);
	if(rename(src_file, dest_file) != 0) {
		return (-1);
	}
	
	return 0;
}

int del_tmpfile(char *filename)
{
	int ret = unlink(filename); 
	return 0;
}

int check_dir(char *dir, char **file_list)
{
	DIR *dp;
    	struct dirent *dirp;
     	int filenum = 0;
	
	dp=opendir(dir);
     	if (dp==NULL)  
     	{
        	return (-1);
     	}
	while(dp)
	{
		if((dirp=readdir(dp))!=NULL)
		{
			if((strcmp(dirp->d_name, ".")!=0)&&(strcmp(dirp->d_name, "..")!=0))
			{
				strcpy(file_list[filenum], dirp->d_name);
				del_all_spaces(file_list[filenum]);
				filenum++;
			}
		}
		else
		{
			closedir(dp);
			break;
		}
	}

	return filenum;
}


int daemon_init(char *dirstr)
{
   struct sigaction act;
  int i;
  char pbuf[10];
                                                                                                               
  i=fork();
  if(i<0) return -1;
  if(i) exit(0);
                                                                                                               
  chdir(dirstr);
  umask(027);
  setpgrp();
  setsid();
                                                                                                               
  i=fork();
  if(i<0) return -1;
  if(i) exit(0);
                                                                                                               
  open("dev/null",O_RDWR);
  dup(0);
  dup(1);
  dup(2);
                                                                                                               
  sprintf(pbuf,"%6d\n",getpid());
  //write(lf,pbuf,strlen(pbuf));
                                                                                                               
  return 0;

}

int write_log(char *log_file, char *format, ...)
{
  va_list args;
  char temp[6000];
  FILE *fp =NULL;
  time_t t;
  struct tm *ptm;

  time(&t);
  ptm =localtime(&t);

  if((fp =fopen(log_file, "a")) ==NULL)
    return EOPENFILE;

  va_start(args, format);
  vsprintf(temp, format, args);
  va_end(args);
  if(temp[0] && temp[strlen(temp)-1] =='\n')
    temp[strlen(temp)-1] =0;
  fprintf(fp, "%4d.%02d.%02d %02d:%02d:%02d - %s\n",ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday, ptm->tm_hour,\
		 ptm->tm_min, ptm->tm_sec, temp);
  fclose(fp);

  return 0;
}

int read_config_string(char *config_file, char *item, char *str_buf)
{
  FILE *fp =NULL;
  char buf[256], *p;

  if((fp =fopen(config_file, "r")) ==NULL)
  {
    
    printf("open file %s failed! %s\n", config_file, item);
    return EOPENFILE;
  }
  while(!feof(fp) && fgets(buf, sizeof(buf), fp) !=NULL)
  {
    if(buf[0] =='#') continue;
    if(!strncmp(buf, item, strlen(item)))
    {
      del_rn(buf);
      p =strchr(buf, '=');
      if(p ==NULL) continue;
      p++;
      p =del_lr_spaces(p);
      fclose(fp);
      strcpy(str_buf, p);
      return 0;
    }
  }
  fclose(fp);
  return ENOTFOUND;
}

int read_config_int(char *config_file, char *item, int *int_buf)
{
  char buf[256];

  if(read_config_string(config_file, item, buf) <0) return ENOTFOUND;
  else
    *int_buf =atoi(buf);
  return *int_buf;
}

int write_config_string(char *config_file, char *item, char *str_buf)
{
  FILE *fp, *fp1;
  char file_temp[128], buf[2000];
  int flag = 0; 
 
  sprintf(file_temp, "%s.T", config_file);

  if((fp =fopen(config_file, "r")) ==NULL)
  {
    if((fp =fopen(config_file, "w")) ==NULL)
      return EOPENFILE;
    return 0;
  }
  if((fp1 =fopen(file_temp, "a")) ==NULL)
  {
    fclose(fp);
    return ECREATEFILE;
  }
  while(!feof(fp) && fgets(buf, sizeof(buf), fp) !=NULL)
  {
    if((!strncmp(buf, item, strlen(item)))&&(buf[strlen(item)]=='='))
    {
	  fprintf(fp1, "%s=%s\n", item, str_buf);
   	  flag = 1;
    }
    else fprintf(fp1, buf);
  }
  if(flag == 0)
  {
	fprintf(fp1, "%s=%s\n", item, str_buf);
  }	
  fclose(fp);
  fclose(fp1);
  if(remove(config_file) !=0)
    return EREMOVEFILE;
  if(rename(file_temp, config_file) !=0)
    return ERENAMEFILE;

  return 0;
}

int write_config_int(char *config_file, char *item, int i)
{
  char temp[20];
  sprintf(temp, "%d", i);
  return write_config_string(config_file, item, temp);
}

char *upper_case(char *str)
{
  char *p =str;

  while(*p)
  {
    if(*p >='a' && *p <='z') *p =*p -'a'+'A';
    p++;
  }
  return str;
}

char *lower_case(char *str)
{
  char *p =str;

  while(*p)
  {
    if(*p >='A' && *p <='Z') *p =*p-'A' +'a';
    p++;
  }
  return str;  
}

int strcmpi(char *s1, char *s2)
{
 char ls1[2000], ls2[2000];

  strcpy(ls1, s1);
  strcpy(ls2, s2);
  return strcmp(lower_case(ls1), lower_case(ls2));
}

int substring(char *instr, char *outstr, int start, int fieldlen)
{
    int i,j;
    char *p;

    if (fieldlen == 0)
    {
        *outstr = '\0';
        return(0);
    }

    p = instr+start;

    for (i=0;i<fieldlen;i++)
    {
        *outstr = *p;
        p++;
        outstr++;
    } 
    *outstr = '\0';
    return(0);
}

int readline(FILE *fp, char *pbuf)
{
	char buf[2560];
	int len;

	if(fp==NULL)
	{
		return -1;
	}
	if((!feof(fp))&&(fgets(buf, sizeof(buf), fp)!=NULL))
	{
		del_rn(buf);
		len = strlen(buf);
		strcpy(pbuf, buf);
		return len;	
	}	
	else
	{
		return -1;
	}
}
