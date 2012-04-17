#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "oracle.h"
#include "util.h"

#define DEBUG 0

extern char *del_lr_spaces(char *pbuf);
extern char *upper_case(char *);

int db_init(DB_INFO *pdb)
{
  HRESULT hr;

  pdb->m_hpEnv = NULL;
  pdb->m_hpErr = NULL;
  pdb->m_hpServer = NULL;
  pdb->m_hpContext = NULL;
  pdb->m_szError[0] =0;
  pdb->m_hpSession =NULL;
  pdb->m_pOracleTypes =NULL;
  pdb->m_auto_commit =0;

  CheckErr(pdb, (hr=OCIInitialize( OCI_OBJECT, NULL, NULL, NULL, NULL ) ));
  if(FAILED(hr))
    return -1;

  CheckErr(pdb, (hr =OCIEnvInit( &pdb->m_hpEnv, OCI_DEFAULT, 0, NULL )) );
  if ( FAILED(hr) )
  {
    //printf("OCIEnvInit failed!\n");
    return -2;
  }

  // Allocate error, server, and service context handles
  OCIHandleAlloc( pdb->m_hpEnv, (void**)&pdb->m_hpErr, OCI_HTYPE_ERROR, 0, NULL );
  OCIHandleAlloc( pdb->m_hpEnv, (void**)&pdb->m_hpServer, OCI_HTYPE_SERVER, 0, NULL );
  OCIHandleAlloc( pdb->m_hpEnv, (void**)&pdb->m_hpContext, OCI_HTYPE_SVCCTX, 0, NULL );
  OCIHandleAlloc( pdb->m_hpEnv, (void**)&pdb->m_hpSession, OCI_HTYPE_SESSION, 0, NULL);
  return 0;
}

int db_exit(DB_INFO *pdb)
{
  HRESULT hr;

  db_close(pdb);

  if(pdb->m_hpSession)
    OCIHandleFree(pdb->m_hpSession, OCI_HTYPE_SESSION);
  // Free server handle
  if (pdb->m_hpServer)
    CheckErr(pdb, (hr =OCIHandleFree(pdb->m_hpServer, OCI_HTYPE_SERVER)));

  // Free service context
  if (pdb->m_hpContext)
    OCIHandleFree( pdb->m_hpContext, OCI_HTYPE_SVCCTX);

  // Free error handle
  if (pdb->m_hpErr)
    OCIHandleFree( pdb->m_hpErr, OCI_HTYPE_ERROR );

  int i =0;
  if(pdb->m_pOracleTypes)
  {
    while(pdb->m_pOracleTypes[i] !=NULL)
      free(pdb->m_pOracleTypes[i++]);
    free(pdb->m_pOracleTypes);
    pdb->m_pOracleTypes =NULL;
  }
}

int db_set_auto_commit(DB_INFO *pdb, int if_auto)
{
  pdb->m_auto_commit =if_auto;
  return 0;
}

void CheckErr(DB_INFO *pdb, HRESULT status )
{
  static struct CErrorPair
  {
    sword w;
    const char* szText;
  }epaErrors[] =
  {
    OCI_SUCCESS, "SUCCESS",
    OCI_SUCCESS_WITH_INFO, "SUCCESS_WITH_INFO",
    OCI_NEED_DATA, "NEED_DATA",
    OCI_NO_DATA, "NO_DATA",
    OCI_INVALID_HANDLE, "INVALID_HANDLE",
    OCI_STILL_EXECUTING, "STILL_EXECUTE",
    OCI_CONTINUE, "CONTINUE",
  };

  if ( status == OCI_ERROR )
  {
    sb4 errcode = 0;
    OCIErrorGet(pdb->m_hpErr, 1, NULL, &errcode, (unsigned char*)pdb->m_szError, sizeof(pdb->m_szError), OCI_HTYPE_ERROR);
  }
  else
  {
    // Look for description in static array
    unsigned int nTotalResultCodes = sizeof(epaErrors) / sizeof(struct CErrorPair);
    for ( int iPos = 0; iPos < sizeof(epaErrors); ++ iPos )
    {
      if ( epaErrors[iPos].w == status )
      {
        strcpy( pdb->m_szError, epaErrors[iPos].szText );
        break;
      }
    }
  }
}

char *db_get_error_string(DB_INFO *pdb)
{
  return pdb->m_szError;
}

int db_connect(DB_INFO *pdb, char *server, char *user, char *pass)
{
  HRESULT hr;

  // Associate TNS with server handle
  CheckErr(pdb, (hr =OCIServerAttach( pdb->m_hpServer,	pdb->m_hpErr,
	(unsigned char*)(char*)server, strlen(server),0 )));
  if ( FAILED(hr) )
  {
    //printf("OCIServerAttach failed!\n");
    return -3;
  }

  // Get server version string
  char version[1024];
  CheckErr(pdb, (hr =OCIServerVersion( pdb->m_hpServer, pdb->m_hpErr,
    (text*)version, sizeof(version), OCI_HTYPE_SERVER )));
  if ( FAILED(hr) )
    return -4;
  //m_csLog += csVersion + "\n";

  // Specify server handle to service context
  CheckErr(pdb, (hr =OCIAttrSet( pdb->m_hpContext,	OCI_HTYPE_SVCCTX,
	pdb->m_hpServer,	0, OCI_ATTR_SERVER,	pdb->m_hpErr )));
  if ( FAILED(hr) )
     return -5;

  // Allocate a session handle

  // Associate username with session handle
  OCIAttrSet( pdb->m_hpSession, OCI_HTYPE_SESSION, (void*)(const char*)user,
  strlen(user),	OCI_ATTR_USERNAME, pdb->m_hpErr);

  // Associate password with session handle
  OCIAttrSet( pdb->m_hpSession, OCI_HTYPE_SESSION, (void*)(const char*)pass,
    strlen(pass), OCI_ATTR_PASSWORD, pdb->m_hpErr);

  // Open session using service context and session handle
  CheckErr(pdb, (hr =OCISessionBegin( pdb->m_hpContext, pdb->m_hpErr,
	pdb->m_hpSession, OCI_CRED_RDBMS, OCI_DEFAULT )));
  if ( FAILED(hr) )
    return -6;

  // Specify session handle to service context
  OCIAttrSet( pdb->m_hpContext, OCI_HTYPE_SVCCTX, pdb->m_hpSession,
	0, OCI_ATTR_SESSION, pdb->m_hpErr);

  // Change date format
  if ( SUCCEEDED(hr) )
  {
    char *csSQL = "alter session set nls_date_format = 'yyyy-mm-dd hh24:mi:ss'";
    if(db_exec(pdb, csSQL ) <0)
      return -7;
  }
  else return -8;

  return TRUE;
}

int db_close(DB_INFO *pdb)
{
  HRESULT hr;

  if(pdb->m_auto_commit) db_commit(pdb);
  // Free select statement handle

  // Detach server from server handle
  if(pdb->m_hpSession)
  {
    OCISessionEnd(pdb->m_hpContext, pdb->m_hpErr, pdb->m_hpSession, OCI_DEFAULT);
  }

  if (pdb->m_hpServer)
    OCIServerDetach( pdb->m_hpServer, pdb->m_hpErr, OCI_DEFAULT );


  if(FAILED(hr)) return FALSE;

  return TRUE;
}

int db_exec(DB_INFO *pdb, char *stmt)
{
  HRESULT hr;

  OCIStmt *hpStatement = NULL;
  CheckErr(pdb, (hr =OCIHandleAlloc( pdb->m_hpEnv,(void**)&hpStatement, OCI_HTYPE_STMT, 0, NULL )));
  if(FAILED(hr))
    return -1;
  // Associate statement string with handle
  CheckErr(pdb, (hr =OCIStmtPrepare( hpStatement,	pdb->m_hpErr,
     (text *)stmt, strlen(stmt),	OCI_NTV_SYNTAX,	OCI_DEFAULT )));

  if(FAILED(hr))
  {
    if(hpStatement)
      OCIHandleFree( hpStatement, OCI_HTYPE_STMT );
    return -2;
  }
  // Execute statement
  CheckErr(pdb, (hr =OCIStmtExecute( pdb->m_hpContext,	hpStatement,
	pdb->m_hpErr,1,	0, // row offset
	NULL, NULL, // snapshot in/out
	OCI_DEFAULT )));
  // Free statement handle

  if(FAILED(hr))
  {
    OCIHandleFree( hpStatement, OCI_HTYPE_STMT );
    return -3;
  }

  if(pdb->m_auto_commit) db_commit(pdb);
  int row_count =0;

  CheckErr(pdb, (hr=OCIAttrGet(hpStatement, OCI_HTYPE_STMT, (ub2 *)&row_count, (ub4 *)0, OCI_ATTR_ROW_COUNT, pdb->m_hpErr)));

  OCIHandleFree( hpStatement, OCI_HTYPE_STMT );

  if(FAILED(hr))
    return 0;
  else return row_count;
}

#if defined(__STDC__) || defined(__cplusplus)
int db_begin_trans(DB_INFO *pdb)
#else
int db_begin_trans(pdb)
DB_INFO *pdb;
#endif
{
  if(FAILED(OCITransStart(pdb->m_hpContext, pdb->m_hpErr, 10, OCI_TRANS_NEW)))
    return -1;
  return 0;
}

#if defined(__STDC__) || defined(__cplusplus)
int db_roll_back(DB_INFO *pdb)
#else
int db_roll_back(pdb)
DB_INFO *pdb;
#endif
{
  if(FAILED(OCITransRollback(pdb->m_hpContext, pdb->m_hpErr, 0)))
    return -1;
  return 0;
}

#if defined(__STDC__) || defined(__cplusplus)
int db_commit(DB_INFO *pdb)
#else
int db_commit(DB_INFO *pdb)
DB_INFO *pdb;
#endif 
{
  if(FAILED(OCITransCommit(pdb->m_hpContext, pdb->m_hpErr, 0)))
    return -1;
  return 0;
}

int db_query_init(DB_QUERY_INFO *pquery, DB_INFO *pdb)
{
  pquery->pdb=pdb;
  pquery->m_hpSelect =NULL;
  pquery->m_BindFields =NULL;
  pquery->FieldValues =NULL;
}

void db_query_close(DB_QUERY_INFO *pquery)
{
  if(pquery->m_hpSelect)
    OCIHandleFree( pquery->m_hpSelect, OCI_HTYPE_STMT );
  pquery->m_hpSelect =NULL;
  if(pquery->m_BindFields)
  {
    for(int i =0; i<pquery->FieldCount; i++)
    {
      if(pquery->m_BindFields[i])
      {
        if(pquery->m_BindFields[i]->pBuffer)
        free(pquery->m_BindFields[i]->pBuffer);
        free(pquery->m_BindFields[i]);
      }
    }
    free(pquery->m_BindFields);
    pquery->m_BindFields =NULL;
  }
  if(pquery->FieldValues) free(pquery->FieldValues);
  pquery->FieldValues =NULL;
}

int db_query_select(DB_QUERY_INFO *pquery, char *stmt)
{
  HRESULT hr;

  pquery->RecCount =pquery->FieldCount =0;
  if(pquery->m_hpSelect)
  {
    OCIHandleFree( pquery->m_hpSelect, OCI_HTYPE_STMT );
    pquery->m_hpSelect =NULL;
  }
  CheckErr(pquery->pdb, (hr =OCIHandleAlloc( pquery->pdb->m_hpEnv,
	(void**)&pquery->m_hpSelect, // ref to statement handle pointer
	OCI_HTYPE_STMT, // type of handle being allocated
	0,	NULL )));
  if(FAILED(hr))
    return -1;
  // Associate statement string with handle
  CheckErr(pquery->pdb, (hr =OCIStmtPrepare( pquery->m_hpSelect,
	pquery->pdb->m_hpErr, // error handle pointer
	(text *)stmt, // statement string
	strlen(stmt),
	OCI_NTV_SYNTAX, // specify native syntax
	OCI_DEFAULT )));
  if(FAILED(hr))
  {
    db_query_close(pquery);
    return -1;
  }
  // Execute but don't fetch yet
  CheckErr(pquery->pdb, (hr =(OCIStmtExecute( pquery->pdb->m_hpContext,
	pquery->m_hpSelect, // prepared by previous function calls
	pquery->pdb->m_hpErr,
	0, // 'iters' i.e. max rows to fetch during this call
	0, NULL, NULL, OCI_DEFAULT ))));
  // If it returns OCI_NO_DATA then no need to define recordset
  if ( hr == OCI_NO_DATA)
  {
    db_query_close(pquery);
    return 0;
  }
  if(FAILED(hr) )
  {
    db_query_close(pquery);
    return -1;
  }

  // Load the types into recordset
  pquery->FieldCount = 0;
  while ( hr == OCI_SUCCESS )
  {
    // Get pointer to column
    void* pFieldAttr = NULL;
    HRESULT hrGetNext;
    hrGetNext = OCIParamGet( pquery->m_hpSelect, OCI_HTYPE_STMT,
	pquery->pdb->m_hpErr,
	&pFieldAttr,
	pquery->FieldCount+1 // position
    );
    if ( hrGetNext != OCI_SUCCESS )
      break;

    // Increment column count and allocate an OdbField structure
    ++pquery->FieldCount;
    BindField* pField = (BindField *)malloc(sizeof(BindField));
    pField->pBuffer =NULL;

    if(pquery->m_BindFields ==NULL)
      pquery->m_BindFields =(BindField **)malloc(pquery->FieldCount*sizeof(BindField *));
    else
      pquery->m_BindFields =(BindField **)realloc(pquery->m_BindFields, pquery->FieldCount*sizeof(BindField *));
    pquery->m_BindFields[pquery->FieldCount-1] =pField;

    if(pquery->FieldValues ==NULL)
      pquery->FieldValues =(char **)malloc(pquery->FieldCount*sizeof(char *));
    else
      pquery->FieldValues =(char **)realloc(pquery->FieldValues, pquery->FieldCount*sizeof(char *));
    pquery->FieldValues[pquery->FieldCount-1] =NULL;

    // Get data type
    CheckErr(pquery->pdb, (hr =OCIAttrGet( pFieldAttr, OCI_DTYPE_PARAM,
	&pField->wType,
	0,
	OCI_ATTR_DATA_TYPE,
	pquery->pdb->m_hpErr )));
    if(FAILED(hr))
    {
      db_query_close(pquery);
      return -1;
    }
    // Get data size
    CheckErr(pquery->pdb, (hr =OCIAttrGet( pFieldAttr, OCI_DTYPE_PARAM,
	&pField->wSize,
	0,
	OCI_ATTR_DATA_SIZE,
	pquery->pdb->m_hpErr )));
    if(FAILED(hr))
    {
      db_query_close(pquery);
      return -1;
    }
    // Type conversions
    pField->m_type =SQL_TYPE_STR;
    if ( pField->wType == SQLT_LNG )
    {
      // LONG size
      pField->wSize = 32760;
    }
    else if ( pField->wType == SQLT_DAT )
    {
      // String is bound to DATE
      pField->wType = SQLT_STR;
      pField->wSize = 50;
      pField->m_type =SQL_TYPE_DATE;
    }
    else if ( pField->wType == SQLT_NUM )
    {
      // String is bound to NUMBER
      pField->wType = SQLT_STR;
      pField->wSize = 30; // allow for null-terminator
    }
    // Get column name
    ub4 nNameLen =0;
text *p =NULL;
    CheckErr(pquery->pdb, (hr =OCIAttrGet( pFieldAttr, OCI_DTYPE_PARAM,
	(void**)&p,
	&nNameLen,
	OCI_ATTR_NAME,
	pquery->pdb->m_hpErr )));

strncpy((char *)pField->name, (char *)p, nNameLen);
pField->name[nNameLen] =0;
//printf("name=%s, size=%d\n", pField->name,pField->wSize); 

//printf("debug:oracle.c:db_query_select:field name %s, \tnNameLen=%d\n",pField->name, nNameLen);

    upper_case(pField->name);

    // Set size and name
    pField->pBuffer =(dvoid *)malloc( pField->wSize+1 );
    memset(pField->pBuffer, 0, pField->wSize+1);
    //pField->csName.Format( "%.*s", nNameLen, pName );
    //FieldValues[FieldCount-1] =(char *)malloc(pField->wSize+1);
    //memset(FieldValues[FieldCount-1], 0, pField->wSize+1);
    pquery->FieldValues[pquery->FieldCount-1] =(char *)pField->pBuffer; 
  }

  // Bind storage for receiving input variables
  OCIDefine *pDefn; // to hold pointer to field definition
  int iField;
  for ( iField=0; iField<pquery->FieldCount; ++iField )
  {
    // Get pointer to field structure
    BindField* pField = pquery->m_BindFields[iField];

    // Bind
    pDefn = NULL;
    CheckErr(pquery->pdb, (hr =OCIDefineByPos( pquery->m_hpSelect,
	&pDefn, // function allocs and gives back a pointer to field definition
	pquery->pdb->m_hpErr,
	iField+1, // position in select starting at 1
	pField->pBuffer, // storage area for field result
	pField->wSize, // sizeof storage area
	pField->wType, // field type
	&pField->nInd, // indp, null indicator
	&pField->wLen, // rlenp
	NULL,
	OCI_DEFAULT )));
    if(FAILED(hr))
    {
      db_query_close(pquery);
      return -1;
    }
  }

  // Fetch
  //FetchNext();

  return pquery->FieldCount;
}

int db_query_fetch(DB_QUERY_INFO *pquery)
{
  HRESULT hr;

  CheckErr(pquery->pdb, (hr =OCIStmtFetch( pquery->m_hpSelect,
		pquery->pdb->m_hpErr,
		1, // 'nrows' i.e. max rows
		OCI_FETCH_NEXT, 
		OCI_DEFAULT )));

  // Set result to 0 if no data returned
  if ( SUCCEEDED(hr) && hr != OCI_NO_DATA )
  {
    pquery->RecCount ++;
    for(int i=0; i<pquery->FieldCount; i++)
    {
      pquery->FieldValues[i][pquery->m_BindFields[i]->wLen] =0;
      del_lr_spaces(pquery->FieldValues[i]);
    }
  }
  else if(hr ==OCI_NO_DATA)
    return 0;
  else return -1;

  return 1;
}

int db_query_is_eos(DB_QUERY_INFO *pquery)
{
	return FALSE;
}

char *get_field_value(DB_QUERY_INFO *pquery, int field_num)
{
  if(field_num >=pquery->FieldCount) return NULL;
  return pquery->FieldValues[field_num];
}

char *get_field_value2(DB_QUERY_INFO *pquery, int field_num, char *buf)
{
  *buf =0;
  if(field_num >=pquery->FieldCount) return NULL;
  strcpy(buf, pquery->FieldValues[field_num]);
  return buf;
}

char *get_field_value_by_name(DB_QUERY_INFO *pquery, char *field_name)
{
  char pstr[32];

  strcpy(pstr, field_name);

  upper_case(pstr);
  for(int i =0; i<pquery->FieldCount; i++)
  {
    if(!strcmp(pstr, pquery->m_BindFields[i]->name))
    {
      return pquery->FieldValues[i];
    }
  }
  return NULL;
}

char *get_field_value_by_name2(DB_QUERY_INFO *pquery, char *field_name, char *buf)
{
  *buf =0;
  if(field_name ==NULL) return NULL;

  upper_case(field_name);
  for(int i =0; i<pquery->FieldCount; i++)
  {
    if(!strcmp(field_name, pquery->m_BindFields[i]->name))
    {
      strcpy(buf, pquery->FieldValues[i]);
      return buf;
    }
  }
  return NULL;
}

int db_exec_bind_long(DB_INFO *pdb, char *sql_stmt, int count, char **long_values, int *long_sizes)
{
  HRESULT hr;
  OCIStmt *hpstmt;

  CheckErr(pdb, (hr =OCIHandleAlloc( pdb->m_hpEnv,
	(void**)&hpstmt, // ref to statement handle pointer
	OCI_HTYPE_STMT, // type of handle being allocated
	0, NULL )));
  if(FAILED(hr))
  {
    //printf("OCIHandleAlloc failed!\n");
    return -1;
  }
  // Associate statement string with handle
  CheckErr(pdb, (hr =OCIStmtPrepare( hpstmt,
	pdb->m_hpErr, // error handle pointer
	(text *)sql_stmt, // statement string
	strlen(sql_stmt),
	OCI_NTV_SYNTAX, // specify native syntax
	OCI_DEFAULT )));
  if(FAILED(hr))
  {
    OCIHandleFree( hpstmt, OCI_HTYPE_STMT );
    return -1;
  }
  
  int i;
  OCIBind *pbind[20];

  memset(pbind, 0, sizeof(pbind));
  for(i=0; i<count && i<20; i++)
  {
    if(OCIBindByPos(hpstmt,&pbind[i], pdb->m_hpErr, i+1,
        (dvoid *)long_values[i], (ub4)long_sizes[i],
        SQLT_LNG/*LBI long binary type */, NULL, NULL, NULL, 0,
        NULL, OCI_DEFAULT) !=0)
    {
      OCIHandleFree(hpstmt, OCI_HTYPE_STMT);
      return -1;
    }
  }
  // Execute but don't fetch yet
  CheckErr(pdb, (hr =(OCIStmtExecute( pdb->m_hpContext,
	hpstmt, // prepared by previous function calls
	pdb->m_hpErr,
	1, // 'iters' i.e. max rows to fetch during this call
	0, NULL, NULL, OCI_DEFAULT ))));


  if (FAILED(hr))
  {
  OCIHandleFree(hpstmt, OCI_HTYPE_STMT);
    return -1;
  }

  //if(pdb->m_auto_commit) db_commit(pdb);

  OCIHandleFree(hpstmt, OCI_HTYPE_STMT);
  return 0;
}

//new query function 
int db_query_select_bind_long(DB_QUERY_INFO *pquery, char *stmt, int count, char **long_values, int *long_sizes)
{
  HRESULT hr;

  pquery->RecCount =pquery->FieldCount =0;
  if(pquery->m_hpSelect)
  {
    OCIHandleFree( pquery->m_hpSelect, OCI_HTYPE_STMT );
    pquery->m_hpSelect =NULL;
  }
  CheckErr(pquery->pdb, (hr =OCIHandleAlloc( pquery->pdb->m_hpEnv,
	(void**)&pquery->m_hpSelect, // ref to statement handle pointer
	OCI_HTYPE_STMT, // type of handle being allocated
	0,	NULL )));
  if(FAILED(hr))
    return -1;
  // Associate statement string with handle
  CheckErr(pquery->pdb, (hr =OCIStmtPrepare( pquery->m_hpSelect,
	pquery->pdb->m_hpErr, // error handle pointer
	(text *)stmt, // statement string
	strlen(stmt),
	OCI_NTV_SYNTAX, // specify native syntax
	OCI_DEFAULT )));
  if(FAILED(hr))
  {
    db_query_close(pquery);
    return -1;
  }

    int i;
  OCIBind *pbind[20];

  memset(pbind, 0, sizeof(pbind));
  for(i=0; i<count && i<20; i++)
  {
    if(OCIBindByPos(pquery->m_hpSelect,&pbind[i], pquery->pdb->m_hpErr, i+1,
        (dvoid *)long_values[i], (ub4)long_sizes[i],
        SQLT_LNG/*LBI long binary type */, NULL, NULL, NULL, 0,
        NULL, OCI_DEFAULT) !=0)
    {
      OCIHandleFree(pquery->m_hpSelect, OCI_HTYPE_STMT);
      return -1;
    }
  }
	
  // Execute but don't fetch yet
  CheckErr(pquery->pdb, (hr =(OCIStmtExecute( pquery->pdb->m_hpContext,
	pquery->m_hpSelect, // prepared by previous function calls
	pquery->pdb->m_hpErr,
	0, // 'iters' i.e. max rows to fetch during this call
	0, NULL, NULL, OCI_DEFAULT ))));
  // If it returns OCI_NO_DATA then no need to define recordset
  if ( hr == OCI_NO_DATA)
  {
    db_query_close(pquery);
    return 0;
  }
  if(FAILED(hr) )
  {
    db_query_close(pquery);
    return -1;
  }

  // Load the types into recordset
  pquery->FieldCount = 0;
  while ( hr == OCI_SUCCESS )
  {
    // Get pointer to column
    void* pFieldAttr = NULL;
    HRESULT hrGetNext;
    hrGetNext = OCIParamGet( pquery->m_hpSelect, OCI_HTYPE_STMT,
	pquery->pdb->m_hpErr,
	&pFieldAttr,
	pquery->FieldCount+1 // position
    );
    if ( hrGetNext != OCI_SUCCESS )
      break;

    // Increment column count and allocate an OdbField structure
    ++pquery->FieldCount;
    BindField* pField = (BindField *)malloc(sizeof(BindField));
    pField->pBuffer =NULL;

    if(pquery->m_BindFields ==NULL)
      pquery->m_BindFields =(BindField **)malloc(pquery->FieldCount*sizeof(BindField *));
    else
      pquery->m_BindFields =(BindField **)realloc(pquery->m_BindFields, pquery->FieldCount*sizeof(BindField *));
    pquery->m_BindFields[pquery->FieldCount-1] =pField;

    if(pquery->FieldValues ==NULL)
      pquery->FieldValues =(char **)malloc(pquery->FieldCount*sizeof(char *));
    else
      pquery->FieldValues =(char **)realloc(pquery->FieldValues, pquery->FieldCount*sizeof(char *));
    pquery->FieldValues[pquery->FieldCount-1] =NULL;

    // Get data type
    CheckErr(pquery->pdb, (hr =OCIAttrGet( pFieldAttr, OCI_DTYPE_PARAM,
	&pField->wType,
	0,
	OCI_ATTR_DATA_TYPE,
	pquery->pdb->m_hpErr )));
    if(FAILED(hr))
    {
      db_query_close(pquery);
      return -1;
    }
    // Get data size
    CheckErr(pquery->pdb, (hr =OCIAttrGet( pFieldAttr, OCI_DTYPE_PARAM,
	&pField->wSize,
	0,
	OCI_ATTR_DATA_SIZE,
	pquery->pdb->m_hpErr )));
    if(FAILED(hr))
    {
      db_query_close(pquery);
      return -1;
    }
    // Type conversions
    pField->m_type =SQL_TYPE_STR;
    if ( pField->wType == SQLT_LNG )
    {
      // LONG size
      pField->wSize = 32760;
    }
    else if ( pField->wType == SQLT_DAT )
    {
      // String is bound to DATE
      pField->wType = SQLT_STR;
      pField->wSize = 50;
      pField->m_type =SQL_TYPE_DATE;
    }
    else if ( pField->wType == SQLT_NUM )
    {
      // String is bound to NUMBER
      pField->wType = SQLT_STR;
      pField->wSize = 30; // allow for null-terminator
    }
    // Get column name
    ub4 nNameLen =0;
text *p =NULL;
    CheckErr(pquery->pdb, (hr =OCIAttrGet( pFieldAttr, OCI_DTYPE_PARAM,
	(void**)&p,
	&nNameLen,
	OCI_ATTR_NAME,
	pquery->pdb->m_hpErr )));

strncpy(pField->name, (char *)p, nNameLen);
pField->name[nNameLen] =0;
//printf("name=%s, size=%d\n", pField->name,pField->wSize); 

//printf("debug:oracle.c:db_query_select:field name %s, \tnNameLen=%d\n",pField->name, nNameLen);

    upper_case(pField->name);

    // Set size and name
    pField->pBuffer =(dvoid *)malloc( pField->wSize+1 );
    memset(pField->pBuffer, 0, pField->wSize+1);
    //pField->csName.Format( "%.*s", nNameLen, pName );
    //FieldValues[FieldCount-1] =(char *)malloc(pField->wSize+1);
    //memset(FieldValues[FieldCount-1], 0, pField->wSize+1);
    pquery->FieldValues[pquery->FieldCount-1] =(char *)pField->pBuffer; 
  }

  // Bind storage for receiving input variables
  OCIDefine *pDefn; // to hold pointer to field definition
  int iField;
  for ( iField=0; iField<pquery->FieldCount; ++iField )
  {
    // Get pointer to field structure
    BindField* pField = pquery->m_BindFields[iField];

    // Bind
    pDefn = NULL;
    CheckErr(pquery->pdb, (hr =OCIDefineByPos( pquery->m_hpSelect,
	&pDefn, // function allocs and gives back a pointer to field definition
	pquery->pdb->m_hpErr,
	iField+1, // position in select starting at 1
	pField->pBuffer, // storage area for field result
	pField->wSize, // sizeof storage area
	pField->wType, // field type
	&pField->nInd, // indp, null indicator
	&pField->wLen, // rlenp
	NULL,
	OCI_DEFAULT )));
    if(FAILED(hr))
    {
      db_query_close(pquery);
      return -1;
    }
  }

  // Fetch
  //FetchNext();

  return pquery->FieldCount;
}
