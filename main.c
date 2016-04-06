/* Include-------------------------------------------------------------------*/
#include "hal_lib.h"

/* Global Variables----------------------------------------------------------*/
uint32_t 	g_ulBluetoothTickCount = 0;
uint8_t		g_ucBluetoothFlag = 0;

/* Function prototype */
void vBluetoothTick(void);
void vSendDataOverBluetooth(void);

int main(void)
{
	uint8_t ucRxBuf[50];
	vHalInit();
	vAdcStart();
	vInitPiezo(PIEZO);

	/* Register callBack */
	vSetInterruptCallback(SYS_TICK_TIMER, eOCFxAInterrupt, vBluetoothTick);

    while(1)
    {
    	vHalProcess();
		vSendDataOverBluetooth();

		/* Listen to uart line to see if we received something */
		if(UsartRead(50,&ucRxBuf[0]) > 0)
		{
			if(strcmp((char const*)&ucRxBuf[0], "buzzer") == 0)
			{
				vTurnPiezoOnForSec(1);
			}
		}

    }
    return 0;
}

/* This function set a flag for sending data over Bluetooth (Serial) */
void vBluetoothTick(void)
{
	g_ulBluetoothTickCount ++;
	if( (g_ulBluetoothTickCount % 250) == 0)
	{
		g_ucBluetoothFlag = 1;
	}
}

/* This Function Send data over Bluetooth */
void vSendDataOverBluetooth(void)
{
	if(g_ucBluetoothFlag == 1)
	{
		uint8_t txBuffer[20];
		uint8_t len;

		uint16_t usPadX = usAdcGetChanValue(PADX);
		uint16_t usPadY = usAdcGetChanValue(PADY);

		memset(&txBuffer[0], 0, sizeof(txBuffer));
		len = sprintf( (char *) &txBuffer[0], "X: %d Y: %d\n", usPadX, usPadY);
		UsartSend(len,&txBuffer[0]);
		g_ucBluetoothFlag = 0;
	}

}

