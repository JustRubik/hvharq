import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import sys

# Thiết lập phong cách đồ thị
sns.set_theme(style="whitegrid")
plt.rcParams.update({'font.size': 11, 'axes.titlesize': 13})

# Đọc dữ liệu
csv_path = './csv/results_final.csv'
try:
    df = pd.read_csv(csv_path)
except FileNotFoundError:
    print(f"❌ Không tìm thấy file {csv_path}. Hãy chạy code C++ để sinh dữ liệu trước!")
    sys.exit()

def plot_kb1():
    df_sub = df[df['scenario'] == 'KB1']
    if df_sub.empty:
        print("⚠️ File CSV hiện chưa có dữ liệu của KB1. Hãy chạy C++ KB1 trước!")
        return
    plt.figure(figsize=(8, 6))
    sns.barplot(data=df_sub, x='BER', y='efficiency', hue='scheme')
    plt.title('KB1: Kiểm tra chức năng (p=0 và p=1)')
    plt.xlabel('Xác suất lỗi bit (p)')
    plt.ylabel('Hiệu suất truyền')
    plt.savefig('./csv/plot_KB1.png', dpi=300)
    print("✅ Đã lưu ảnh plot_KB1.png")
    plt.show()

def plot_kb2():
    df_sub = df[df['scenario'] == 'KB2']
    if df_sub.empty:
        print("⚠️ File CSV hiện chưa có dữ liệu của KB2. Hãy chạy C++ KB2 trước!")
        return
    plt.figure(figsize=(8, 6))
    sns.barplot(data=df_sub, x='BER', y='efficiency', hue='scheme')
    plt.title('KB2: Hiệu năng tại môi trường nhiễu cao')
    plt.xlabel('Xác suất lỗi bit (p > 0.05)')
    plt.ylabel('Hiệu suất truyền')
    plt.savefig('./csv/plot_KB2.png', dpi=300)
    print("✅ Đã lưu ảnh plot_KB2.png")
    plt.show()

def plot_kb3():
    df_sub = df[df['scenario'] == 'KB3']
    if df_sub.empty:
        print("⚠️ File CSV hiện chưa có dữ liệu của KB3. Hãy chạy C++ KB3 trước!")
        return
    plt.figure(figsize=(8, 6))
    sns.lineplot(data=df_sub, x='BER', y='efficiency', hue='scheme', marker='o')
    plt.xscale('log') 
    plt.title('KB3: Đánh giá toàn diện (Thang đo Log)')
    plt.xlabel('Xác suất lỗi bit (p)')
    plt.ylabel('Hiệu suất truyền')
    plt.savefig('./csv/plot_KB3.png', dpi=300)
    print("✅ Đã lưu ảnh plot_KB3.png")
    plt.show()

def plot_kb4():
    df_sub = df[df['scenario'] == 'KB4']
    if df_sub.empty:
        print("⚠️ File CSV hiện chưa có dữ liệu của KB4. Hãy chạy C++ KB4 trước!")
        return
    
    fig, axes = plt.subplots(1, 2, figsize=(14, 6))
    
    # Throughput
    sns.barplot(data=df_sub, x='msg_length', y='throughput', hue='scheme', capsize=.1, ax=axes[0])
    axes[0].set_title('KB4: Thông lượng mô phỏng (Throughput)')
    axes[0].set_xlabel('Kích thước thông điệp (Bytes)')
    axes[0].set_ylabel('Thông lượng (bps)')
    
    # Efficiency
    sns.barplot(data=df_sub, x='msg_length', y='efficiency', hue='scheme', capsize=.1, ax=axes[1])
    axes[1].set_title('KB4: Hiệu suất sử dụng kênh (Efficiency)')
    axes[1].set_xlabel('Kích thước thông điệp (Bytes)')
    axes[1].set_ylabel('Hiệu suất truyền (%)')
    
    plt.tight_layout()
    plt.savefig('./csv/plot_KB4.png', dpi=300)
    print("✅ Đã lưu ảnh plot_KB4.png")
    plt.show()

def plot_all():
    print("Đang vẽ gộp 4 kịch bản (Yêu cầu file CSV phải chứa đủ dữ liệu của 4 KB)...")
    # (Bạn có thể bỏ qua phần này nếu chỉ muốn vẽ lẻ, nhưng để đây cho đủ bộ)
    try:
        fig, axes = plt.subplots(2, 2, figsize=(16, 12))
        sns.barplot(data=df[df['scenario'] == 'KB1'], x='BER', y='efficiency', hue='scheme', ax=axes[0, 0])
        axes[0, 0].set_title('KB1: Kiểm tra chức năng (p=0 và p=1)')
        
        sns.barplot(data=df[df['scenario'] == 'KB2'], x='BER', y='efficiency', hue='scheme', ax=axes[0, 1])
        axes[0, 1].set_title('KB2: Hiệu năng tại môi trường nhiễu cao')
        
        sns.lineplot(data=df[df['scenario'] == 'KB3'], x='BER', y='efficiency', hue='scheme', marker='o', ax=axes[1, 0])
        axes[1, 0].set_xscale('log')
        axes[1, 0].set_title('KB3: Đánh giá toàn diện (Thang đo Log)')
        
        sns.barplot(data=df[df['scenario'] == 'KB4'], x='msg_length', y='efficiency', hue='scheme', capsize=.1, ax=axes[1, 1])
        axes[1, 1].set_title('KB4: Ảnh hưởng kích thước đầu vào (p=0.02)')
        
        plt.tight_layout()
        plt.savefig('./csv/plot_ALL.png', dpi=300)
        print("✅ Đã lưu ảnh plot_ALL.png")
        plt.show()
    except Exception as e:
        print("⚠️ Lỗi khi vẽ gộp! Hãy đảm bảo bạn đã chọn chạy [5] trên C++ để có đủ dữ liệu. Lỗi:", e)

# MENU GIAO DIỆN
while True:
    print("\n==========================================")
    print("   TOOL VẼ ĐỒ THỊ BÁO CÁO - NHÓM 10")
    print("==========================================")
    print("1. Vẽ Kịch bản 1 (Kiểm tra chức năng)")
    print("2. Vẽ Kịch bản 2 (Nhiễu cao)")
    print("3. Vẽ Kịch bản 3 (Toàn dải nhiễu)")
    print("4. Vẽ Kịch bản 4 (Kích thước thông điệp)")
    print("5. Vẽ gộp 4 kịch bản vào 1 hình")
    print("0. Thoát")
    print("==========================================")
    
    choice = input("Nhập số để vẽ đồ thị (0-5): ")
    
    if choice == '1': plot_kb1()
    elif choice == '2': plot_kb2()
    elif choice == '3': plot_kb3()
    elif choice == '4': plot_kb4()
    elif choice == '5': plot_all()
    elif choice == '0': 
        print("Đã thoát Tool vẽ.")
        break
    else:
        print("Lựa chọn không hợp lệ!")