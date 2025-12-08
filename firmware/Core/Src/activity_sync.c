#include "activity_sync.h"
#include "activity_storage.h"
#include "gatt_db.h"

#include <stdio.h>
#include "stm32l4xx_hal.h"


extern volatile int connected;
extern uint8_t  notification_enabled;
extern volatile uint8_t g_need_sync;
extern volatile int set_connectable;


void BLE_SyncStoredActivities(void)
{

    if (!connected || !notification_enabled)
    {
        printf("BLE sync: not connected or notifications disabled\r\n");
        return;
    }


    uint32_t count = Storage_GetRecordCount();
    printf("BLE sync: %lu records\r\n", (unsigned long)count);

    ActivityRecord rec;


    for (uint32_t i = 0; i < count; i++)
    {
        if (!Storage_ReadRecord(i, &rec))
        {
            printf("Read error at index %lu\r\n", (unsigned long)i);
            break;
        }

        printf("Sending record %lu: activity=%u\r\n",
               (unsigned long)i,
               rec.activity_id);


        uint8_t buff[8];

        HOST_TO_LE_32(buff, rec.timestamp);
        HOST_TO_LE_16(buff + 4, rec.activity_id);
        HOST_TO_LE_16(buff + 6, 0);

        aci_gatt_update_char_value(HWServW2STHandle, EnvironmentalCharHandle,
                                   0, 8, buff);



        HAL_Delay(30);
    }

    printf("BLE sync done\r\n");
}
