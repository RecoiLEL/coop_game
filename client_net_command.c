#include "client_net.h"

int ExecuteCommand(char command){
    int endFlag = 1;
    switch(command){
		case END_COMMAND:
			endFlag = 0;
			break;
    }
    return endFlag;
}

void SendEndCommand(void)
{
    unsigned char	data[MAX_DATA];
    int			dataSize;

    dataSize = 0;
    SetCharData2DataBlock(data,END_COMMAND,&dataSize);

    SendData(data,dataSize);
}

void SetCharData2DataBlock(void *data,char charData,int *dataSize)
{
    assert(data!=NULL);
    assert(0<=(*dataSize));

    *(char *)(data + (*dataSize)) = charData;
    (*dataSize) += sizeof(char);
}