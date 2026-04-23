# Dự án Basic of Artificial Intelligent

## Giới thiệu

Dự án này chứa một số bài tập C++ cơ bản liên quan đến các thuật toán tìm kiếm và tối ưu trong lĩnh vực trí tuệ nhân tạo (AI), đặc biệt là các bài toán tổ hợp như TSP, tìm đường và lập lịch.

## Cấu trúc dự án

- `TH1-01.cpp`: Giải bài toán TSP bằng phương pháp tham lam cho điểm xuất phát cố định.
- `TH1-02.cpp`: Giải bài toán TSP cho nhiều điểm xuất phát, chọn lời giải tốt nhất.
- `GTS2meta.cpp`: Triển khai thuật toán TSP cải tiến bằng cách sử dụng phương pháp 2-opt/heuristic trên dữ liệu `tspx.txt`.
- `TH4-01.cpp`: Cài đặt thuật toán tìm đường A* với dữ liệu đồ thị và heuristic từ `pathx.txt`.
- `TH5-01.cpp`: Giải bài toán TSP bằng thuật toán di truyền (genetic algorithm) với dữ liệu từ `tspx.txt`.
- `TH2-01.cpp`, `TH2-02.cpp`, `TH3-02.cpp`, `TH3-03.cpp`: Các bài toán bổ sung thuộc chương 2 và chương 3 (có thể liên quan đến giải thuật đồ thị, lập lịch hoặc bài toán tối ưu).

## Dữ liệu mẫu

- `GTS1x.txt`, `GTS2x.txt`: Dữ liệu đầu vào cho các thuật toán TSP.
- `tspx.txt`: Ma trận khoảng cách cho các bài toán TSP.
- `pathx.txt`: Dữ liệu đồ thị và heuristic cho bài toán tìm đường A*.
- `Johnsonx.txt`, `schedulex.txt`, `inputDSA.txt`, `inputWP.txt`: Các file dữ liệu khác có thể dùng cho bài toán đồ thị, lập lịch hoặc các bài toán tối ưu khác.

## Yêu cầu

- Hệ điều hành: Windows
- Trình biên dịch: `g++` (MinGW) hoặc bất kỳ bộ biên dịch C++ hỗ trợ C++11 trở lên.

## Cách biên dịch

Mở terminal trong thư mục dự án và chạy lệnh:

```powershell
C:\MinGW\bin\g++.exe -std=c++11 TH1-01.cpp -o TH1-01.exe
```

Hoặc biên dịch nhanh với file khác:

```powershell
C:\MinGW\bin\g++.exe -std=c++11 TH4-01.cpp -o TH4-01.exe
```

## Cách chạy

Trong terminal, chạy file `.exe` tương ứng:

```powershell
.\TH1-01.exe
```

Hoặc:

```powershell
.\TH4-01.exe
```

Lưu ý: Các chương trình tìm kiếm dữ liệu đầu vào từ file mặc định như `GTS1x.txt`, `GTS2x.txt`, `tspx.txt` và `pathx.txt` nên cần giữ các file đó trong cùng thư mục với file thực thi.

## Ghi chú

- Nếu muốn thử nghiệm với dữ liệu khác, bạn có thể sửa trực tiếp tên file trong mã nguồn hoặc tạo file dữ liệu mới.
- Các file `.exe` hiện có trong thư mục là các bản đã biên dịch sẵn từ các file `.cpp`.
