import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# ===============================
# Cấu hình đồ thị
# ===============================
sns.set_theme(style="whitegrid")
plt.rcParams.update({
    'font.size': 12,
    'axes.titlesize': 14
})


# ===============================
# Hàm đọc file csv
# ===============================
def load_csv(path):
    try:
        return pd.read_csv(path)
    except FileNotFoundError:
        print(f"❌ Không tìm thấy {path}")
        return None


# ===============================
# KB1
# ===============================
def plot_kb1():

    df = load_csv("./csv/results_kb1.csv")
    if df is None:
        return

    df_plot = (
        df.groupby(["BER", "scheme"])
        .mean(numeric_only=True)
        .reset_index()
    )

    plt.figure(figsize=(8, 6))

    sns.barplot(
        data=df_plot,
        x="BER",
        y="efficiency",
        hue="scheme"
    )

    plt.title("KB1: Efficiency vs BER")
    plt.xlabel("BER")
    plt.ylabel("Efficiency")

    plt.tight_layout()
    plt.savefig("./csv/plot_KB1.png", dpi=300)

    print("✅ Đã lưu plot_KB1.png")

    plt.show()


# ===============================
# KB2
# ===============================
def plot_kb2():

    df = load_csv("./csv/results_kb2.csv")
    if df is None:
        return

    df_plot = (
        df.groupby(["BER", "scheme"])
        .mean(numeric_only=True)
        .reset_index()
    )

    plt.figure(figsize=(8, 6))

    sns.lineplot(
        data=df_plot,
        x="BER",
        y="efficiency",
        hue="scheme",
        marker="o"
    )

    plt.title("KB2: Efficiency in High Noise Environment")
    plt.xlabel("BER")
    plt.ylabel("Efficiency")

    plt.tight_layout()
    plt.savefig("./csv/plot_KB2.png", dpi=300)

    print("✅ Đã lưu plot_KB2.png")

    plt.show()


# ===============================
# KB3
# ===============================
def plot_kb3():

    df = load_csv("./csv/results_kb3.csv")
    if df is None:
        return

    df_plot = (
        df.groupby(["BER", "scheme"])
        .mean(numeric_only=True)
        .reset_index()
    )

    plt.figure(figsize=(8, 6))

    sns.lineplot(
        data=df_plot,
        x="BER",
        y="efficiency",
        hue="scheme",
        marker="o"
    )

    plt.xscale("log")

    plt.title("KB3: Efficiency vs BER")
    plt.xlabel("BER")
    plt.ylabel("Efficiency")

    plt.tight_layout()
    plt.savefig("./csv/plot_KB3.png", dpi=300)

    print("✅ Đã lưu plot_KB3.png")

    plt.show()


# ===============================
# KB4
# ===============================
def plot_kb4():

    df = load_csv("./csv/results_kb4.csv")
    if df is None:
        return

    df_plot = (
        df.groupby(["msg_length", "scheme"])
        .mean(numeric_only=True)
        .reset_index()
    )

    fig, axes = plt.subplots(1, 2, figsize=(14, 6))

    sns.barplot(
        data=df_plot,
        x="msg_length",
        y="throughput",
        hue="scheme",
        ax=axes[0]
    )

    axes[0].set_title("Throughput vs Input Size")
    axes[0].set_xlabel("Message length (Bytes)")
    axes[0].set_ylabel("Throughput (bps)")


    sns.barplot(
        data=df_plot,
        x="msg_length",
        y="efficiency",
        hue="scheme",
        ax=axes[1]
    )

    axes[1].set_title("Efficiency vs Input Size")
    axes[1].set_xlabel("Message length (Bytes)")
    axes[1].set_ylabel("Efficiency")

    plt.tight_layout()

    plt.savefig("./csv/plot_KB4.png", dpi=300)

    print("✅ Đã lưu plot_KB4.png")

    plt.show()


# ===============================
# Vẽ tổng hợp
# ===============================
def plot_all():

    df1 = load_csv("./csv/results_kb1.csv")
    df2 = load_csv("./csv/results_kb2.csv")
    df3 = load_csv("./csv/results_kb3.csv")
    df4 = load_csv("./csv/results_kb4.csv")

    if any(df is None for df in [df1, df2, df3, df4]):
        return


    df1 = (
        df1.groupby(["BER", "scheme"])
        .mean(numeric_only=True)
        .reset_index()
    )

    df2 = (
        df2.groupby(["BER", "scheme"])
        .mean(numeric_only=True)
        .reset_index()
    )

    df3 = (
        df3.groupby(["BER", "scheme"])
        .mean(numeric_only=True)
        .reset_index()
    )

    df4 = (
        df4.groupby(["msg_length", "scheme"])
        .mean(numeric_only=True)
        .reset_index()
    )


    fig, axes = plt.subplots(2, 2, figsize=(16, 12))


    sns.barplot(
        data=df1,
        x="BER",
        y="efficiency",
        hue="scheme",
        ax=axes[0, 0]
    )

    axes[0, 0].set_title("KB1")


    sns.lineplot(
        data=df2,
        x="BER",
        y="efficiency",
        hue="scheme",
        marker="o",
        ax=axes[0, 1]
    )

    axes[0, 1].set_title("KB2")


    sns.lineplot(
        data=df3,
        x="BER",
        y="efficiency",
        hue="scheme",
        marker="o",
        ax=axes[1, 0]
    )

    axes[1, 0].set_xscale("log")
    axes[1, 0].set_title("KB3")


    sns.barplot(
        data=df4,
        x="msg_length",
        y="efficiency",
        hue="scheme",
        ax=axes[1, 1]
    )

    axes[1, 1].set_title("KB4")


    plt.tight_layout()

    plt.savefig("./csv/plot_ALL.png", dpi=300)

    print("✅ Đã lưu plot_ALL.png")

    plt.show()


# ===============================
# Menu
# ===============================
while True:

    print("\n===================================")
    print(" TOOL VE DO THI - NHOM 10")
    print("===================================")
    print("1. KB1")
    print("2. KB2")
    print("3. KB3")
    print("4. KB4")
    print("5. Tong hop")
    print("0. Thoat")
    print("===================================")

    choice = input("Nhap lua chon: ")

    if choice == '1':
        plot_kb1()

    elif choice == '2':
        plot_kb2()

    elif choice == '3':
        plot_kb3()

    elif choice == '4':
        plot_kb4()

    elif choice == '5':
        plot_all()

    elif choice == '0':
        break

    else:
        print("Lua chon khong hop le.")