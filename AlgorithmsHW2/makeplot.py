import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv("out.csv")

N = df["size"]

for i in range(1, 7):
    plt.plot(N, np.log(df.iloc[:,i]), label=df.columns[i])
plt.legend()
plt.xlabel("Size")
plt.ylabel("log Cost")
plt.show()
