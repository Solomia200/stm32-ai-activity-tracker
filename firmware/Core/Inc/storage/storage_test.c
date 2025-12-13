#include "activity_storage.h"
#include "storage_test.h"
#include <stdio.h>

void Storage_RunTests(void)
{
    printf("=== STORAGE TEST START ===\n");

    // 1️⃣ Очистити всю память
    printf("Clearing flash...\n");
    Storage_ClearAll();

    Storage_Init();
    printf("Record count after clear: %lu\n", Storage_GetRecordCount());

    // 2️⃣ Додати кілька записів
    printf("Saving 3 test records...\n");
    Storage_SaveRecord(1000, 1);
    Storage_SaveRecord(2000, 3);
    Storage_SaveRecord(3000, 5);

    // 3️⃣ Перевірити кількість
    uint32_t count = Storage_GetRecordCount();
    printf("Record count = %lu (should be 3)\n", count);

    // 4️⃣ Прочитати кожен запис
    for (uint32_t i = 0; i < count; i++)
    {
        ActivityRecord rec;
        if (Storage_ReadRecord(i, &rec))
        {
            printf("Record %lu: timestamp=%lu  activity=%u\n",
                   i, rec.timestamp, rec.activity_id);
        }
        else
        {
            printf("Record %lu: read failed!\n", i);
        }
    }

    // 5️⃣ Очистити ще раз
    printf("Clearing flash again...\n");
    Storage_ClearAll();
    Storage_Init();

    printf("Record count after final clear: %lu (should be 0)\n",
           Storage_GetRecordCount());

    printf("=== STORAGE TEST END ===\n");
}
