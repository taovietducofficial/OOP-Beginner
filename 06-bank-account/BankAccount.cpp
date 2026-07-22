/*
 * Ngôn ngữ: C++
 *
 * Công dụng: BankAccount minh họa ĐÓNG GÓI (encapsulation) — số dư để private,
 * mọi thay đổi bắt buộc đi qua deposit/withdraw, nơi các quy tắc nghiệp vụ
 * (tiền > 0, không rút quá số dư) được kiểm tra.
 *
 * Tại sao cần học: đóng gói là trụ cột đầu tiên của OOP. Nếu field để public,
 * bất kỳ dòng code nào cũng có thể gán balance = -1000 và phá hỏng dữ liệu —
 * bug kiểu này cực khó truy vết vì chỗ gãy nằm xa chỗ gán sai.
 */
#include <cstdint>   // thư viện chuẩn: std::int64_t — số nguyên 64 bit, tương đương long của Java
#include <cstdlib>   // thư viện chuẩn: std::exit để dừng chương trình khi self-check thất bại
#include <iostream>  // thư viện chuẩn: std::cout/std::cerr để in ra màn hình
#include <stdexcept> // thư viện chuẩn: std::invalid_argument để báo lỗi dữ liệu sai
#include <string>    // thư viện chuẩn: std::string cho thông điệp lỗi

class BankAccount { // khai báo class — khuôn mẫu để tạo ra các object BankAccount
private:
    std::int64_t balance; // số dư (đơn vị: đồng) — private: bên ngoài KHÔNG gán trực tiếp được; dùng số nguyên thay vì double để tránh sai số dấu phẩy động với tiền

public:
    explicit BankAccount(std::int64_t initialBalance) : balance(initialBalance) { // constructor — chạy khi tạo object
        if (initialBalance < 0) throw std::invalid_argument("Số dư ban đầu không được âm"); // validate ở biên: chặn số dư âm ngay từ lúc tạo
    }

    void deposit(std::int64_t amount) { // nạp tiền — cách HỢP LỆ duy nhất để tăng số dư
        if (amount <= 0) throw std::invalid_argument("Tiền nạp phải > 0"); // quy tắc nghiệp vụ: không nạp số âm hoặc 0
        balance += amount; // cộng tiền vào số dư
    }

    void withdraw(std::int64_t amount) { // rút tiền — cách HỢP LỆ duy nhất để giảm số dư
        if (amount <= 0) throw std::invalid_argument("Tiền rút phải > 0"); // quy tắc nghiệp vụ: không rút số âm hoặc 0
        if (amount > balance) throw std::invalid_argument("Số dư không đủ"); // quy tắc nghiệp vụ: không cho rút quá số dư
        balance -= amount; // trừ tiền khỏi số dư
    }

    std::int64_t getBalance() const { // getter — cho bên ngoài XEM số dư, nhưng không SỬA được
        return balance; // trả về số dư hiện tại
    }
};

// ---- Self-check ----
static void check(bool ok, const std::string& msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
    if (!ok) { std::cerr << "FAIL: " << msg << "\n"; std::exit(1); } // in chỗ sai rồi dừng ngay
}

int main() { // điểm bắt đầu chạy chương trình sau khi biên dịch
    BankAccount acc(100'000); // tạo tài khoản với 100.000đ — C++ dùng dấu ' phân tách hàng nghìn (Java dùng _)
    acc.deposit(50'000); // nạp thêm 50.000đ
    check(acc.getBalance() == 150'000, "nạp tiền sai"); // 100k + 50k = 150k
    acc.withdraw(70'000); // rút 70.000đ
    check(acc.getBalance() == 80'000, "rút tiền sai"); // 150k - 70k = 80k

    bool blocked = false; // cờ đánh dấu: việc rút lố có bị chặn không
    try { acc.withdraw(1'000'000); } catch (const std::invalid_argument&) { blocked = true; } // cố rút 1 triệu khi chỉ còn 80k — phải bị ném lỗi
    check(blocked, "rút quá số dư phải bị chặn"); // xác nhận quy tắc "không rút lố" hoạt động
    check(acc.getBalance() == 80'000, "số dư không được đổi khi giao dịch bị chặn"); // giao dịch lỗi thì số dư giữ nguyên

    std::cout << "OK\n"; // in "OK" nếu mọi check ở trên đều đúng
    return 0; // báo chương trình kết thúc thành công
}
