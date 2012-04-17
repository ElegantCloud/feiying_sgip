#ifndef __UTIL_H_
#define __UTIL_H_
#include <string.h>
#include <stdio.h>
#include <iconv.h>

using namespace std;
#include <string>

typedef struct
{
	int year;
	int month;
	int day;
}DATETYPE;
//date struct

typedef struct
{
	unsigned char hour;
	unsigned char min;
	unsigned char sec;
}TIMETYPE;
//time struct

#ifdef __cplusplus
extern "C"
{
#endif

int write_file(char *file, char *format, ...);
void ucs2_decoding(char *str,int len);
int code_convert(char *from_charset,char *to_charset,char *inbuf,int inlen,\
		char *outbuf,int outlen);
void gen_rand_str(char s[],int length=6);
void dumpMemory(unsigned char * buf, int len,char *str);
bool IsProcConflict(string prog_name);
char *GetFilePath(char *file, char *path); /* get path from full path name */
char *GetFileName(char *file);    /* get file name from full path name */
char *del_all_spaces(char *p);    /* del all spaces */
char *del_lr_spaces(char *pbuf);  /* del left and right spaces */
char *del_rn(char *pbuf);         /* del \r and \n */
char *del_rn1(char *pbuf);         /* del \r and \n */

void getmydate(DATETYPE *d);/*get date time*/
void getmytime(TIMETYPE *t);/*get hour time*/
void getlastmonth(char *pbuf);/*get last month string*/
void get_full_time(char *pbuf);
void dayofweek(char *);
void get_sequence_str(char *pbuf);
void get_date_str(char *pbuf);/*get date string,include year,month,day*/
void get_date2_str(char *pbuf);
void get_time_str(char *pbuf);/*get time string,include hour,minute,second*/
void get_full_time_str(char *pbuf);/*get full time string,include year,month,day,hour,minute,second*/
int month_day(int year, int month );/*calculate month included day num*/
int is_date(char *value);/*if value string is a date string*/
int is_time(char *value);/*if value string is a time string*/
int is_date_time(char *value);/*if value string is a date and time string*/
void datestr_to_date(char *datestr, DATETYPE *d); 
void timestr_to_time(char *timestr, TIMETYPE *t);
void time_to_timestr(TIMETYPE *t, char *pbuf);
void date_to_datestr(DATETYPE *d, char *pbuf);  

int isnumstr(char *s);/*if string s is a number string*/
int isfloatstr(char *s);/*if string s is a float string*/

int move_file(char *filename, char *src_path, char *dest_path, char *suffix);/*move file to dest path*/
int del_tmpfile(char *filename);/*delete tmp file*/
int check_dir(char *dir, char **file_list);/*list a dir all file*/

int daemon_init(char *dirstr);//dameon

int write_log(char *file, char *format, ...);

int read_config_string(char *config_file, char *item, char *str_buf);
int read_config_int(char *config_file, char *item, int *int_buf);
int write_config_string(char *config_file, char *item, char *str_buf);
int write_config_int(char *config_file, char *item, int int_buf);

char *lower_case(char *);
char *upper_case(char *);

int strcmpi(char *, char *);

int substring(char *instr, char *outstr, int start, int fieldlen);

int readline(FILE *fp, char *pbuf);

int diff_month(char *time1,char *time2);

#ifdef __cplusplus
}
#endif

#endif

