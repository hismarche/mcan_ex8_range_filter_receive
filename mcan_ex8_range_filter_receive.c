// Modified MCAN Example with Console Print and UART Init for RS485 Output
#include "driverlib.h"
#include "device.h"
#include "inc/stw_types.h"
#include "inc/stw_dataTypes.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "lwiplib.h"
#include "ethernet.h"
#include "lwip/sockets.h"
#include "lwip/inet.h"
#include "lwip/opt.h"
#include "lwip/udp.h"

#define NUM_OF_MSG                      (1U)
#define MCAN_STD_ID_FILTER_NUM          (0U)
#define MCAN_EXT_ID_FILTER_NUM          (1U)
#define MCAN_FIFO_0_NUM                 (0U)
#define MCAN_FIFO_0_ELEM_SIZE           (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_FIFO_1_NUM                 (NUM_OF_MSG)
#define MCAN_FIFO_1_WATERMARK           (NUM_OF_MSG)
#define MCAN_FIFO_1_ELEM_SIZE           (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_RX_BUFF_NUM                (0U)
#define MCAN_RX_BUFF_ELEM_SIZE          (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_TX_BUFF_SIZE               (0U)
#define MCAN_TX_FQ_SIZE                 (0U)
#define MCAN_TX_BUFF_ELEM_SIZE          (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_TX_EVENT_SIZE              (0U)
#define MCAN_EXT_ID_AND_MASK            (0x1FFFFFFFU)

#define MCAN_STD_ID_FILT_START_ADDR     (0x0U)
#define MCAN_EXT_ID_FILT_START_ADDR     (MCAN_STD_ID_FILT_START_ADDR + ((MCAN_STD_ID_FILTER_NUM * MCANSS_STD_ID_FILTER_SIZE_WORDS * 4U)))
#define MCAN_FIFO_0_START_ADDR          (MCAN_EXT_ID_FILT_START_ADDR + ((MCAN_EXT_ID_FILTER_NUM * MCANSS_EXT_ID_FILTER_SIZE_WORDS * 4U)))
#define MCAN_FIFO_1_START_ADDR          (MCAN_FIFO_0_START_ADDR + (MCAN_getMsgObjSize(MCAN_FIFO_0_ELEM_SIZE) * 4U * MCAN_FIFO_0_NUM))
#define MCAN_RX_BUFF_START_ADDR         (MCAN_FIFO_1_START_ADDR + (MCAN_getMsgObjSize(MCAN_FIFO_1_ELEM_SIZE) * 4U * MCAN_FIFO_1_NUM))
#define MCAN_TX_BUFF_START_ADDR         (MCAN_RX_BUFF_START_ADDR + (MCAN_getMsgObjSize(MCAN_RX_BUFF_ELEM_SIZE) * 4U * MCAN_RX_BUFF_NUM))
#define MCAN_TX_EVENT_START_ADDR        (MCAN_TX_BUFF_START_ADDR + (MCAN_getMsgObjSize(MCAN_TX_BUFF_ELEM_SIZE) * 4U * (MCAN_TX_BUFF_SIZE + MCAN_TX_FQ_SIZE)))

int32_t     error = 0;
MCAN_RxBufElement rxMsg[NUM_OF_MSG], rxMsg1;
MCAN_RxFIFOStatus RxFS;
int32_t loopCnt = 0U;

static void MCANConfig(void);
static void MCANIntrConfig(void);
static void initUART(void);
static void initLED(void);
static void toggleLED(void);
__interrupt void MCANIntr1ISR(void);

// Add UART redirection function
int fputc(int ch, FILE *f)
{
    SCI_writeCharBlockingFIFO(SCIA_BASE, (uint16_t)ch);
    return ch;
}

void main()
{
    uint32_t ipAddr = 0x0A000A32;     // 10.0.10.50
    uint32_t netmask = 0xFFFFFF00;   // 255.255.255.0
    uint32_t gateway = 0x0A000A01;   // 10.0.10.1

    lwIPInit(0, ipAddr, netmask, gateway);
    int i = 0;
    uint32_t dataBytes = 64;

    Device_init();
    Device_initGPIO();
    initUART();
    initLED();

    SysCtl_allocateSharedPeripheral(SYSCTL_PALLOCATE_MCAN_A,0x0U);
    SysCtl_setMCANClk(SYSCTL_MCANCLK_DIV_5);
    MCANIntrConfig();
    GPIO_setPinConfig(DEVICE_GPIO_CFG_MCANRXA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_MCANTXA);

    rxMsg[loopCnt].id = 0U;
    rxMsg[loopCnt].rtr = 0U;
    rxMsg[loopCnt].xtd = 1U;
    rxMsg[loopCnt].esi = 0U;
    rxMsg[loopCnt].rxts = 0U;
    rxMsg[loopCnt].dlc = 0U;
    rxMsg[loopCnt].brs = 0U;
    rxMsg[loopCnt].fdf = 0U;
    rxMsg[loopCnt].fidx = 0U;
    rxMsg[loopCnt].anmf = 0U;
    for(i = 0; i < dataBytes; i++)
    {
        rxMsg[loopCnt].data[i]  = 0;
    }

    MCANConfig();
    MCAN_enableIntr(MCANA_DRIVER_BASE, MCAN_INTR_MASK_ALL, 1U);
    MCAN_selectIntrLine(MCANA_DRIVER_BASE, MCAN_INTR_MASK_ALL, MCAN_INTR_LINE_NUM_1);
    MCAN_enableIntrLine(MCANA_DRIVER_BASE, MCAN_INTR_LINE_NUM_1, 1U);

    while(1)
    {
        // idle loop; LED toggling handled on SCI message receive
    }
}

static void MCANIntrConfig(void)
{
    Interrupt_initModule();
    Interrupt_initVectorTable();
    Interrupt_register(INT_MCANA_1, &MCANIntr1ISR);
    Interrupt_enable(INT_MCANA_1);
    Interrupt_enableGlobal();
}

static void MCANConfig(void)
{
    // ... (same as before)
}

static void initUART(void)
{
    GPIO_setPinConfig(GPIO_29_SCIA_TX);
    GPIO_setPinConfig(GPIO_28_SCIA_RX);

    SCI_performSoftwareReset(SCIA_BASE);
    SCI_setConfig(SCIA_BASE, DEVICE_LSPCLK_FREQ, 115200,
                  (SCI_CONFIG_WLEN_8 | SCI_CONFIG_STOP_ONE | SCI_CONFIG_PAR_NONE));
    SCI_enableModule(SCIA_BASE);
    SCI_enableFIFO(SCIA_BASE);
    setvbuf(stdout, NULL, _IONBF, 0);
}

static void initLED(void)
{
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);
    GPIO_writePin(DEVICE_GPIO_PIN_LED1, 0);
}

static void toggleLED(void)
{
    GPIO_togglePin(DEVICE_GPIO_PIN_LED1);
}

__interrupt void MCANIntr1ISR(void)
{
    static int udpSocket = -1;
    static struct sockaddr_in destAddr;
#ifndef _SOCKLEN_T_DECLARED
#define _SOCKLEN_T_DECLARED
    typedef int socklen_t;
#endif
    static socklen_t socklen = sizeof(destAddr);

    if (udpSocket == -1) {
        udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (udpSocket >= 0) {
            memset(&destAddr, 0, sizeof(destAddr));
            destAddr.sin_family = AF_INET;
            destAddr.sin_port = PP_HTONS(5005);  // Laptop listening port
            destAddr.sin_addr.s_addr = PP_HTONL(0x0A000A64); // 10.0.10.100
        }
    }

    uint32_t intrStatus;
    intrStatus = MCAN_getIntrStatus(MCANA_DRIVER_BASE);
    MCAN_clearIntrStatus(MCANA_DRIVER_BASE, intrStatus);
    MCAN_clearInterrupt(MCANA_DRIVER_BASE, 0x2);

    if((MCAN_INTR_SRC_RX_FIFO1_NEW_MSG & intrStatus) == MCAN_INTR_SRC_RX_FIFO1_NEW_MSG)
    {
        GPIO_togglePin(DEVICE_GPIO_PIN_LED1);

        MCAN_readMsgRam(MCANA_DRIVER_BASE, MCAN_MEM_TYPE_FIFO, 1U, 0U, &rxMsg1);
        rxMsg[loopCnt] = rxMsg1;

        MCAN_getRxFIFOStatus(MCANA_DRIVER_BASE, &RxFS);

        uint16_t rawU = (rxMsg1.data[1] << 8) | rxMsg1.data[0];
        uint16_t rawV = (rxMsg1.data[3] << 8) | rxMsg1.data[2];
        uint16_t rawW = (rxMsg1.data[5] << 8) | rxMsg1.data[4];

        float voltageU = rawU * 0.1f;
        float voltageV = rawV * 0.1f;
        float voltageW = rawW * 0.1f;

        char buffer[64];
        snprintf(buffer, sizeof(buffer), "{\"U\":%.2f,\"V\":%.2f,\"W\":%.2f}\n", voltageU, voltageV, voltageW);
        if (udpSocket >= 0) {
            sendto(udpSocket, buffer, strlen(buffer), 0, (struct sockaddr *)&destAddr, socklen);
        }

        MCAN_writeRxFIFOAck(MCANA_DRIVER_BASE, MCAN_RX_FIFO_NUM_1);
    }
    else
    {
        error++;
    }

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}
