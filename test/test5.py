import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# ==========================================================
# Style
# ==========================================================
sns.set_theme(style="whitegrid")

plt.rcParams.update({
    'font.size': 12,
    'axes.titlesize': 14
})

# ==========================================================
# Đọc dữ liệu
# ==========================================================
files = {
    24: "./csv/results_kb5_fs24.csv",
    40: "./csv/results_kb5_fs40.csv",
    72: "./csv/results_kb5_fs72.csv",
    80: "./csv/results_kb5_fs80.csv",
    136: "./csv/results_kb5_fs136.csv"
}

dfs = []

for frame_size, filename in files.items():

    try:
        df = pd.read_csv(filename)

        df["frame_size"] = frame_size

        dfs.append(df)

    except FileNotFoundError:

        print(f"Khong tim thay {filename}")

if len(dfs) == 0:

    print("Khong co file csv nao!")
    exit()

df = pd.concat(dfs, ignore_index=True)

# ==========================================================
# Tính trung bình
# ==========================================================
df_plot = (
    df.groupby(
        ["frame_size", "msg_length", "scheme"]
    )
    .mean(numeric_only=True)
    .reset_index()
)


# ==========================================================
# Throughput
# ==========================================================
def plot_throughput():

    plt.figure(figsize=(8, 6))

    sns.barplot(
        data=df_plot,
        x="frame_size",
        y="throughput",
        hue="scheme",
        errorbar=None
    )

    plt.title("KB5: Throughput vs Frame Size")

    plt.xlabel("Frame size (bits)")

    plt.ylabel("Throughput (bps)")

    plt.tight_layout()

    plt.savefig(
        "./csv/plot_kb5_throughput.png",
        dpi=300
    )

    print("Da luu plot_kb5_throughput.png")

    plt.show()


# ==========================================================
# Efficiency
# ==========================================================
def plot_efficiency():

    plt.figure(figsize=(8, 6))

    sns.barplot(
        data=df_plot,
        x="frame_size",
        y="efficiency",
        hue="scheme",
        errorbar=None
    )

    plt.title("KB5: Efficiency vs Frame Size")

    plt.xlabel("Frame size (bits)")

    plt.ylabel("Efficiency")

    plt.tight_layout()

    plt.savefig(
        "./csv/plot_kb5_efficiency.png",
        dpi=300
    )

    print("Da luu plot_kb5_efficiency.png")

    plt.show()


# ==========================================================
# Time
# ==========================================================
def plot_time():

    plt.figure(figsize=(8, 6))

    sns.barplot(
        data=df_plot,
        x="frame_size",
        y="time(ms)",
        hue="scheme",
        errorbar=None
    )

    plt.title("KB5: Execution Time vs Frame Size")

    plt.xlabel("Frame size (bits)")

    plt.ylabel("Time (ms)")

    plt.tight_layout()

    plt.savefig(
        "./csv/plot_kb5_time.png",
        dpi=300
    )

    print("Da luu plot_kb5_time.png")

    plt.show()


# ==========================================================
# Plot tổng hợp
# ==========================================================
def plot_all():

    fig, axes = plt.subplots(
        1,
        3,
        figsize=(18, 6)
    )

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
        "Throughput vs Frame Size"
    )

    axes[0].set_xlabel(
        "Frame size (bits)"
    )

    axes[0].set_ylabel(
        "Throughput (bps)"
    )


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
        "Efficiency vs Frame Size"
    )

    axes[1].set_xlabel(
        "Frame size (bits)"
    )

    axes[1].set_ylabel(
        "Efficiency"
    )


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
        "Execution Time vs Frame Size"
    )

    axes[2].set_xlabel(
        "Frame size (bits)"
    )

    axes[2].set_ylabel(
        "Time (ms)"
    )

    plt.tight_layout()

    plt.savefig(
        "./csv/plot_kb5_all.png",
        dpi=300
    )

    print("Da luu plot_kb5_all.png")

    plt.show()


# ==========================================================
# Menu
# ==========================================================
while True:

    print()
    print("==========================================")
    print("      KB5 VISUALIZATION TOOL")
    print("==========================================")
    print("1. Throughput vs Frame Size")
    print("2. Efficiency vs Frame Size")
    print("3. Execution Time vs Frame Size")
    print("4. Plot all")
    print("0. Exit")
    print("==========================================")

    choice = input("Nhap lua chon (0-4): ")

    if choice == '1':

        plot_throughput()

    elif choice == '2':

        plot_efficiency()

    elif choice == '3':

        plot_time()

    elif choice == '4':

        plot_all()

    elif choice == '0':

        print("Tam biet!")

        break

    else:

        print("Lua chon khong hop le!")