import matplotlib.pyplot as plt
import pandas as pd

file = "/home/bohdan/code/poc/human-activity-recognition/stm32-ai-activity-tracker/firmware/resources/datasets/pamap2/PAMAP2_Dataset/test.csv"
df = pd.read_csv(file)

counts = df["activityID"].value_counts()

counts.plot(kind="bar")
# plt.show()
print(counts)