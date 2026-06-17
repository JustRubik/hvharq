import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Thiết lập style cho đồ thị nhìn chuẩn học thuật (Báo cáo Bách Khoa)
sns.set_theme(style="whitegrid")
plt.rcParams.update({'font.size': 12, 'axes.titlesize': 14})

# 1. Đọc dữ liệu từ file CSV
try:
    df = pd.read_csv('./csv/results_kb3_kb35.csv')
except FileNotFoundError:
    print("Không tìm thấy file CSV. Hãy đảm bảo đường dẫn '../docs/results_kb3_kb35.csv' là chính xác.")
    exit()

# Phân tách dữ liệu theo kịch bản
df_kb3 = df[df['scenario'] == 'KB3']
df_kb35 = df[df['scenario'] == 'KB3.5']

# Tạo figure với 3 biểu đồ
fig, axes = plt.subplots(1, 3, figsize=(18, 6))

# ==============================================================================
# BIỂU ĐỒ 1: KỊCH BẢN 3 - SỰ PHỤ THUỘC VÀO MẪU DỮ LIỆU (THROUGHPUT)
# ==============================================================================
sns.lineplot(
    data=df_kb3, 
    x='BER', 
    y='throughput', 
    hue='scheme', 
    style='message_label', 
    markers=True, 
    dashes=False, 
    ax=axes[0]
)
axes[0].set_title('KB3: Throughput vs BER (Data Pattern)')
axes[0].set_xlabel('Tỷ lệ lỗi bit (BER)')
axes[0].set_ylabel('Thông lượng (bps)')
axes[0].set_xscale('log') # Dùng thang log cho trục X vì BER quét dải rộng

# ==============================================================================
# BIỂU ĐỒ 2: KỊCH BẢN 3.5 - ẢNH HƯỞNG CỦA KÍCH THƯỚC KHUNG LÊN THROUGHPUT
# ==============================================================================
sns.barplot(
    data=df_kb35, 
    x='msg_length', 
    y='throughput', 
    hue='scheme', 
    capsize=.1,
    ax=axes[1]
)
axes[1].set_title('KB3.5: Throughput vs Input Size (Fixed BER=0.02)')
axes[1].set_xlabel('Kích thước thông điệp (Bytes)')
axes[1].set_ylabel('Thông lượng (bps)')

# ==============================================================================
# BIỂU ĐỒ 3: KỊCH BẢN 3.5 - ẢNH HƯỞNG CỦA KÍCH THƯỚC KHUNG LÊN HIỆU SUẤT
# ==============================================================================
sns.barplot(
    data=df_kb35, 
    x='msg_length', 
    y='efficiency', 
    hue='scheme', 
    capsize=.1,
    ax=axes[2]
)
axes[2].set_title('KB3.5: Efficiency vs Input Size (Fixed BER=0.02)')
axes[2].set_xlabel('Kích thước thông điệp (Bytes)')
axes[2].set_ylabel('Hiệu suất truyền (%)')

# Tối ưu layout và hiển thị
plt.tight_layout()

# Lưu đồ thị ra file hình ảnh (để dán vào báo cáo)
plt.savefig('../docs/simulation_results.png', dpi=300)
print("Đã lưu đồ thị thành công tại '../docs/simulation_results.png'")

# Hiển thị đồ thị lên màn hình
plt.show()