from pathlib import Path
import numpy as np
from numpy.typing import NDArray


class DatParser:
    CSV_HEADER = "timestamp,activityID,heart_rate,hand_temp,hand_acc16_1,hand_acc16_2,hand_acc16_3,hand_acc6_1,hand_acc6_2,hand_acc6_3,hand_gyro_1,hand_gyro_2,hand_gyro_3,hand_mag_1,hand_mag_2,hand_mag_3,hand_orient_1,hand_orient_2,hand_orient_3,hand_orient_4,chest_temp,chest_acc16_1,chest_acc16_2,chest_acc16_3,chest_acc6_1,chest_acc6_2,chest_acc6_3,chest_gyro_1,chest_gyro_2,chest_gyro_3,chest_mag_1,chest_mag_2,chest_mag_3,chest_orient_1,chest_orient_2,chest_orient_3,chest_orient_4,ankle_temp,ankle_acc16_1,ankle_acc16_2,ankle_acc16_3,ankle_acc6_1,ankle_acc6_2,ankle_acc6_3,ankle_gyro_1,ankle_gyro_2,ankle_gyro_3,ankle_mag_1,ankle_mag_2,ankle_mag_3,ankle_orient_1,ankle_orient_2,ankle_orient_3,ankle_orient_4"
    
    @staticmethod
    def read_dat_file(path_to_file: str) -> NDArray:
        data = []
        with open(path_to_file, mode="r", encoding="utf-8") as file:
            for line in file:
                line = line.strip().split()
                data.append(np.asarray(line))
        
        return np.asarray(data)
    
    @classmethod
    def write_to_csv(cls, path_to_write: str, data: NDArray) -> NDArray:
        np.savetxt(path_to_write, data, delimiter=",", fmt="%s", header=cls.CSV_HEADER, comments='')


if __name__ == "__main__":
    file = "/home/bohdan/code/poc/human-activity-recognition/stm32-ai-activity-tracker/firmware/resources/datasets/pamap2/PAMAP2_Dataset/Protocol/subject101.dat"
    data = DatParser.read_dat_file(file)
    out_file = "/home/bohdan/code/poc/human-activity-recognition/stm32-ai-activity-tracker/firmware/resources/datasets/pamap2/PAMAP2_Dataset/test.csv"
    DatParser.write_to_csv(out_file, data)