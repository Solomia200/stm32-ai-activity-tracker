#ifndef ACTIVITY_STORAGE_H
#define ACTIVITY_STORAGE_H

#include <stdint.h>
#include <stdbool.h>


#define STORAGE_FLASH_START      0x08040000U
#define STORAGE_FLASH_SECTOR     FLASH_SECTOR_5
#define STORAGE_SECTOR_SIZE      (128 * 1024U)



typedef struct __attribute__((packed, aligned(4))) {
    uint32_t timestamp;
    uint8_t  activity_id;
    uint8_t  padding[3];
} ActivityRecord;

#define ACTIVITY_RECORD_SIZE     (sizeof(ActivityRecord))

#define STORAGE_MAX_RECORDS      (STORAGE_SECTOR_SIZE / ACTIVITY_RECORD_SIZE)


void Storage_Init(void);


bool Storage_SaveRecord(uint32_t timestamp, uint8_t activity_id);


bool Storage_ReadRecord(uint32_t index, ActivityRecord *out);


uint32_t Storage_GetRecordCount(void);


void Storage_ClearAll(void);

#endif
