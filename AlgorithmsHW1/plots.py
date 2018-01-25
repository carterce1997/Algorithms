import matplotlib.pyplot as plt
import pandas as pd

f = input("Data Filename: ")
df = pd.read_csv(f)

x = df["Size"]

plt.plot(x, df["NaiveCost"], label="Naive Search")
plt.plot(x, df["RecursiveCost"], label="Recursive Search")
plt.plot(x, df["IterativeCost"], label="Iterative Search")
plt.title("Naive vs. Divide-and-Conquer Searches")
plt.xlabel("Size")
plt.ylabel("Cost")
plt.legend()

plt.savefig("cost.png")
