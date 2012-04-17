#ifndef _ORACLE_H
#define _ORACLE_H

#include <oci.h>

#define DWORD dword
#define HRESULT sword
#define BOOL boolean
#define SUCCEEDED(Status) ((HRESULT)(Status) >= 0)
#define FAILED(Status) ((HRESULT)(Status)<0)

#define SQL_TYPE_STR		'1'
#define SQL_TYPE_INT		'2'
#define SQL_TYPE_FLT		'3'
#define SQL_TYPE_DBL		'4'
#define SQL_TYPE_DATE		'5'

#define USER_ORDER_FORCE	'F'
#define USER_ORDER_TEST		'T'
#define USER_ORDER_YES		'Y'	
#define USER_ORDER_NO		'N'

typedef struct
{
  OCIEnv* m_hpEnv;
  OCIServer* m_hpServer;
  OCIError* m_hpErr;
  OCISvcCtx* m_hpContext;
  OCISession* m_hpSession;
  char m_szError[512];
  char **m_pOracleTypes;
  int m_auto_commit;
  //OdbContext *m_po;
}DB_INFO;

typedef struct
{
  char name[50];
  dvoid* pBuffer;
  ub2 wType;
  ub2 wSize;
  ub2 wLen;
  sb2 nInd;
  char m_type;
}BindField;

typedef struct
{
  int FieldCount, RecCount;
  char **FieldValues;
  OCIStmt *m_hpSelect;
  DB_INFO *pdb;
  BindField **m_BindFields;
}DB_QUERY_INFO;

int db_init(DB_INFO *pdb_info);
int db_exit(DB_INFO *pdb_info);
int db_set_auto_commit(DB_INFO *, int if_auto);

int db_connect(DB_INFO *pdb_info, char *server, char *user, char *pass);
int db_close(DB_INFO *pdb_info);
int db_exec(DB_INFO *pdb_info, char *stmt);
char *db_get_error_string(DB_INFO *pdb_info);
int db_begin_trans(DB_INFO *pdb_info);
int db_roll_back(DB_INFO *pdb_info);
int db_commit(DB_INFO *pdb_info);
void CheckErr(DB_INFO *pdb, HRESULT status );

int db_query_init( DB_QUERY_INFO *, DB_INFO *pdb);
void db_query_close( DB_QUERY_INFO *pquery);
int db_query_select(DB_QUERY_INFO *pquery, char *stmt);
int db_query_fetch(DB_QUERY_INFO *pquery);
BOOL db_query_is_eos(DB_QUERY_INFO *pquery);

/* bind long or varchar2 string */
int db_exec_bind_long(DB_INFO *pdb, char *sql_stmt, int count, char **long_values, int *long_sizes);

char *get_field_value(DB_QUERY_INFO *, int);
char *get_field_value2(DB_QUERY_INFO *, int, char *);
char *get_field_value_by_name(DB_QUERY_INFO *, char *);
char *get_field_value_by_name2(DB_QUERY_INFO *, char *fname, char *buf);

char *db_get_error_string(DB_INFO *);

int db_query_select_bind_long(DB_QUERY_INFO *pquery, char *stmt, int count, char **long_values, int *long_sizes);

#endif
