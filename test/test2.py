import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# =====================
# Đọc dữ liệu
# =====================
filename = "./csv/test2.csv"
df = pd.read_csv(filename)

# Xóa khoảng trắng nếu có
df["scheme"] = df["scheme"].str.strip()

# =====================
# Chọn cấu hình muốn xem
# =====================
FRAME_SIZE = 40     # sửa lại
CRC_SIZE = 8        # sửa lại

filtered = df[
    (df["frame_size"] == FRAME_SIZE)
    & (df["crc_size"] == CRC_SIZE)
]

# =====================
# Tính trung bình efficiency
# =====================
grouped = (
    filtered
    .groupby(["BER", "scheme"])["efficiency"]
    .mean()
    .unstack()
)

# Nếu thiếu ARQ hoặc HARQ thì thêm vào
if "ARQ" not in grouped.columns:
    grouped["ARQ"] = 0

if "HARQ" not in grouped.columns:
    grouped["HARQ"] = 0

# =====================
# Chuẩn bị dữ liệu
# =====================
bers = grouped.index.astype(str)

arq_eff = grouped["ARQ"]
harq_eff = grouped["HARQ"]

x = np.arange(len(bers))
width = 0.35

# =====================
# Vẽ
# =====================
plt.figure(figsize=(10,6))

bars1 = plt.bar(
    x - width/2,
    arq_eff,
    width,
    label="ARQ"
)

bars2 = plt.bar(
    x + width/2,
    harq_eff,
    width,
    label="HARQ"
)

# Hiển thị giá trị trên cột
for bar in bars1:
    height = bar.get_height()
    plt.text(
        bar.get_x() + bar.get_width()/2,
        height,
        f"{height:.3f}",
        ha='center',
        va='bottom',
        fontsize=8
    )

for bar in bars2:
    height = bar.get_height()
    plt.text(
        bar.get_x() + bar.get_width()/2,
        height,
        f"{height:.3f}",
        ha='center',
        va='bottom',
        fontsize=8
    )

plt.xticks(x, bers)

plt.xlabel("BER")
plt.ylabel("Average Efficiency")
plt.title(
    f"Efficiency Comparison (Frame={FRAME_SIZE}, CRC={CRC_SIZE})"
)

plt.grid(axis='y')
plt.legend()

plt.tight_layout()
plt.show()