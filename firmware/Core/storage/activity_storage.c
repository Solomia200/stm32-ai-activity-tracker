#include "activity_storage.h"
#include "stm32l4xx_hal.h"
#include <string.h>



#define STORAGE_FLASH_START   0x08040000U
#define STORAGE_SIZE_BYTES    (64U * 1024U)
#define FLASH_PAGE_SIZE       2048U

#define RECORD_SIZE           (sizeof(ActivityRecord))
#define MAX_RECORDS           (STORAGE_SIZE_BYTES / RECORD_SIZE)


static uint32_t write_address = STORAGE_FLASH_START;



void Storage_Init(void)
{
    write_address = STORAGE_FLASH_START;


    while (write_address < (STORAGE_FLASH_START + STORAGE_SIZE_BYTES))
    {
        const ActivityRecord *rec = (const ActivityRecord *)write_address;

        if (rec->timestamp == 0xFFFFFFFFu)
        {

            break;
        }

        write_address += RECORD_SIZE;
    }
}

uint32_t Storage_GetRecordCount(void)
{
    return (write_address - STORAGE_FLASH_START) / RECORD_SIZE;
}



bool Storage_SaveRecord(uint32_t timestamp, uint8_t activity_id)
{

    if (write_address >= (STORAGE_FLASH_START + STORAGE_SIZE_BYTES))
    {
        return false;
    }

    ActivityRecord rec;
    rec.timestamp   = timestamp;
    rec.activity_id = activity_id;
    rec.padding[0]  = 0xFF;
    rec.padding[1]  = 0xFF;
    rec.padding[2]  = 0xFF;


    uint64_t data64 = 0xFFFFFFFFFFFFFFFFULL;
    memcpy(&data64, &rec, sizeof(ActivityRecord));

    HAL_FLASH_Unlock();

    HAL_StatusTypeDef status =
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,
                          write_address,
                          data64);

    HAL_FLASH_Lock();

    if (status != HAL_OK)
    {

        return false;
    }

    write_address += RECORD_SIZE;
    return true;
}



bool Storage_ReadRecord(uint32_t index, ActivityRecord *out)
{
    uint32_t count = Storage_GetRecordCount();
    if (index >= count)
    {
        return false;
    }

    uint32_t addr = STORAGE_FLASH_START + index * RECORD_SIZE;

    const ActivityRecord *rec_in_flash = (const ActivityRecord *)addr;
    memcpy(out, rec_in_flash, RECORD_SIZE);

    return true;
}



void Storage_ClearAll(void)
{
    FLASH_EraseInitTypeDef erase;
    uint32_t page_error = 0;


    uint32_t first_page = (STORAGE_FLASH_START - FLASH_BASE) / FLASH_PAGE_SIZE;
    uint32_t num_pages  = STORAGE_SIZE_BYTES / FLASH_PAGE_SIZE;

    erase.TypeErase = FLASH_TYPEERASE_PAGES;
    erase.Page      = first_page;
    erase.NbPages   = num_pages;

    HAL_FLASH_Unlock();

    if (HAL_FLASHEx_Erase(&erase, &page_error) != HAL_OK)
    {

    }

    HAL_FLASH_Lock();


    write_address = STORAGE_FLASH_START;
}
