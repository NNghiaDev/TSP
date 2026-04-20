# Traveling Salesman Problem (TSP)

## 📌 Giới thiệu  
Cho một tập các đỉnh và trọng số giữa chúng, tìm **chu trình ngắn nhất** đi qua mỗi đỉnh đúng một lần và quay lại đỉnh xuất phát.

## ⚙️ Phương pháp sử dụng
Dự án này cài đặt thuật toán:

### 🔹 Backtracking + Branch and Bound
- Duyệt tất cả các khả năng
- Cắt tỉa nhánh không tối ưu bằng **lower bound**
- Tăng tốc đáng kể so với brute force(Sinh hoán vị thông thường)
