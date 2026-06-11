import pandas as pd
import matplotlib.pyplot as plt

# đọc dữ liệu
df = pd.read_csv("./docs/results.csv")

# lấy trung bình theo scheme và BER
summary = (
    df.groupby(["scheme", "BER"])
      .mean(numeric_only=True)
      .reset_index()
)

# tách ARQ và HARQ
arq = summary[summary["scheme"] == "ARQ"]
harq = summary[summary["scheme"] == "HARQ"]


# ========================
# Efficiency vs BER
# ========================
plt.figure()

plt.plot(arq["BER"],
         arq["efficiency"],
         marker='o',
         label="ARQ")

plt.plot(harq["BER"],
         harq["efficiency"],
         marker='o',
         label="HARQ")

plt.xlabel("BER")
plt.ylabel("Efficiency")
plt.title("Efficiency vs BER")
plt.grid()
plt.legend()

plt.savefig("./docs/images/efficiency.png")


# ========================
# Throughput vs BER
# ========================
plt.figure()

plt.plot(arq["BER"],
         arq["throughput"],
         marker='o',
         label="ARQ")

plt.plot(harq["BER"],
         harq["throughput"],
         marker='o',
         label="HARQ")

plt.xlabel("BER")
plt.ylabel("Throughput")
plt.title("Throughput vs BER")
plt.grid()
plt.legend()

plt.savefig("./docs/images/throughput.png")


# ========================
# Retransmission vs BER
# ========================
plt.figure()

plt.plot(arq["BER"],
         arq["retransmission"],
         marker='o',
         label="ARQ")

plt.plot(harq["BER"],
         harq["retransmission"],
         marker='o',
         label="HARQ")

plt.xlabel("BER")
plt.ylabel("Average Retransmission")
plt.title("Retransmission vs BER")
plt.grid()
plt.legend()

plt.savefig("./docs/images/retransmission.png")

plt.show()


# Time vs number of iterations
plt.figure()

plt.plot(arq["ID"],
         arq["time(ms)"],
         marker='o',
         label="ARQ")

plt.plot(arq["ID"],
         arq["time(ms)"],
         marker='o',
         label="HARQ")

plt.xlabel("Number of Iterations")
plt.ylabel("Total time")
plt.title("Total time vs Number of Iterations")
plt.grid()
plt.legend()

plt.savefig("./docs/images/time.png")

plt.show()