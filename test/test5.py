import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

sns.set_theme(style="whitegrid")
plt.rcParams.update({
    'font.size': 12,
    'axes.titlesize': 14
})

# ============================
# Đọc các file của KB5
# ============================
files = {
    24: "./csv/results_kb5_fs24.csv",
    40: "./csv/results_kb5_fs40.csv",
    72: "./csv/results_kb5_fs72.csv",
    80: "./csv/results_kb5_fs80.csv",
    136: "./csv/results_kb5_fs136.csv"
}

dfs = []

for frame_size, filename in files.items():

    df = pd.read_csv(filename)

    df["frame_size"] = frame_size

    dfs.append(df)

df = pd.concat(dfs, ignore_index=True)

# ============================
# Lấy giá trị trung bình
# ============================
df_plot = (
    df.groupby(
        ["frame_size", "msg_length", "scheme"]
    )
    .mean(numeric_only=True)
    .reset_index()
)


# ============================
# Vẽ
# ============================
fig, axes = plt.subplots(1, 3, figsize=(21, 6))

# Throughput
sns.barplot(
    data=df_plot,
    x="frame_size",
    y="throughput",
    hue="scheme",
    errorbar=None,
    ax=axes[0]
)

axes[0].set_title(
    "KB5: Throughput vs Frame Size"
)

axes[0].set_xlabel(
    "Frame size (bits)"
)

axes[0].set_ylabel(
    "Throughput (bps)")


# Efficiency
sns.barplot(
    data=df_plot,
    x="frame_size",
    y="efficiency",
    hue="scheme",
    errorbar=None,
    ax=axes[1]
)

axes[1].set_title(
    "KB5: Efficiency vs Frame Size"
)

axes[1].set_xlabel(
    "Frame size (bits)"
)

axes[1].set_ylabel(
    "Efficiency")


# Time
sns.barplot(
    data=df_plot,
    x="frame_size",
    y="time(ms)",
    hue="scheme",
    errorbar=None,
    ax=axes[2]
)

axes[2].set_title(
    "KB5: Execution Time vs Frame Size"
)

axes[2].set_xlabel(
    "Frame size (bits)"
)

axes[2].set_ylabel(
    "Time (ms)")


plt.tight_layout()

plt.savefig(
    "./csv/plot_KB5.png",
    dpi=300
)

print("Da luu plot_KB5.png")

plt.show()