/*****************************************************************
ファイル名	: client_func.h
機能	: クライアントの外部関数の定義
*****************************************************************/

#ifndef _CLIENT_FUNC_H_
#define _CLIENT_FUNC_H_

#include"constant.h"

/* client_net.c */
extern int SetUpClient(char* hostName,int *clientID,int *num,char clientName[]);
extern void CloseSoc(void);
extern int RecvIntData(int *intData);
extern void SendData(void *data,int dataSize);
extern int SendRecvManager(void);

/* client_window.c */
extern int InitWindows(int clientID,int num,char name[]);
extern void DestroyWindow(void);
extern void WindowEvent(int num);

/* client_command.c */
extern int ExecuteCommand(char command);

#endif
