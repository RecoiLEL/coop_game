#ifndef CLIENT_H
#define CLIENT_H

/* client_window.c */
extern int InitWindows(int clientID,int num,char name[]);
extern void DestroyWindow(void);

/* client_command.c */
extern int ExecuteCommand(char command);

#endif