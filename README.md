# HVHARQ

Mô phỏng cơ chế **Automatic Repeat reQuest (ARQ)** và **Hybrid Automatic Repeat reQuest (HARQ)** sử dụng ngôn ngữ **C++**, kết hợp với **Python** để phân tích và trực quan hóa kết quả.

## Giới thiệu

HVHARQ là một dự án mô phỏng quá trình truyền dữ liệu qua kênh truyền có lỗi (Binary Symmetric Channel - BSC), cho phép so sánh hiệu năng giữa:

* ARQ (Automatic Repeat reQuest)
* HARQ (Hybrid Automatic Repeat reQuest)

Dự án được xây dựng nhằm mục đích học tập và nghiên cứu, tập trung vào:

* Mã phát hiện lỗi CRC-8.
* Mã chập (Convolutional Code).
* Thuật toán giải mã Viterbi.
* Cơ chế truyền lại dữ liệu.
* Đánh giá hiệu năng của ARQ và HARQ.

---

## Cấu trúc thư mục

```
HVHARQ/
│
├── include/        # Header files
├── src/            # Source files
├── test/           # Chương trình kiểm thử
├── results/        # File CSV kết quả
│
├── CMakeLists.txt
└── README.md
```

---

## Mô hình hệ thống

```
Sender
   │
   ├── Segmentation
   ├── CRC-8
   ├── Convolutional Encoder (HARQ)
   │
   ▼
Binary Symmetric Channel (BSC)
   │
   ▼
Receiver
   ├── Viterbi Decoder (HARQ)
   ├── CRC Check
   └── Data Reassembly
```

---

## Các thành phần chính

### Sender

Thực hiện:

* Chuyển đổi chuỗi thành bit.
* Chia dữ liệu thành các frame.
* Gắn CRC.
* Mã hóa chập (HARQ).

### Receiver

Thực hiện:

* Giải mã Viterbi.
* Kiểm tra CRC.
* Loại bỏ CRC.
* Ghép lại dữ liệu nhận được.

### Channel

Mô phỏng kênh truyền BSC với xác suất lỗi bit (BER) cho trước.

### Protocols

Bao gồm:

#### ARQ

* Truyền frame.
* Kiểm tra CRC.
* Nếu lỗi → gửi lại frame.

#### HARQ

* Mã hóa chập.
* Giải mã Viterbi.
* Kiểm tra CRC.
* Nếu vẫn lỗi → truyền lại frame.

---

## Các thông số đánh giá

Dự án ghi kết quả ra file CSV với định dạng:

```
ID,scheme,BER,state,total_frames,retransmission,time(ms),efficiency,throughput
```

Trong đó:

| Trường         | Ý nghĩa                      |
| -------------- | ---------------------------- |
| ID             | Số thứ tự lần mô phỏng       |
| scheme         | ARQ hoặc HARQ                |
| BER            | Bit Error Rate               |
| state          | Trạng thái truyền thành công |
| total_frames   | Tổng số frame                |
| retransmission | Số lần truyền lại            |
| time(ms)       | Thời gian thực thi           |
| efficiency     | Hiệu suất truyền             |
| throughput     | Thông lượng                  |

---

## Biên dịch

### Windows (MinGW)

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Chạy:

```bash
main.exe
```

---

## Trực quan hóa dữ liệu

Dự án sử dụng Python để đọc file CSV và vẽ biểu đồ.

Cài đặt thư viện:

```bash
pip install pandas matplotlib
```

Chạy:

```bash
python plot.py
```

## Công nghệ sử dụng

* C++11
* Python

---

## Thuật toán sử dụng

* CRC-8
* Convolutional Code
* Viterbi Decoder
* Binary Symmetric Channel (BSC)
* ARQ
* HARQ

---

## Mục tiêu của dự án

* Mô phỏng quá trình truyền dữ liệu có lỗi.
* So sánh ARQ và HARQ.
* Quan sát ảnh hưởng của BER tới hiệu năng hệ thống.
* Làm cơ sở cho các nghiên cứu sâu hơn về:

  * FEC
  * Turbo Code
  * LDPC
  * Wireless Communication
  * IoT
  * 5G/6G

---

## Tác giả

JustRubik

GitHub:

https://github.com/JustRubik

---

## Giấy phép

MIT
Dự án được phát hành cho mục đích học tập và nghiên cứu.
