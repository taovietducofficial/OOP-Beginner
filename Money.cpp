/*
 * Ngôn ngữ: C++
 *
 * Công dụng: Money minh họa sự khác nhau giữa so sánh ĐỊA CHỈ (&a == &b — có
 * phải cùng một object trong bộ nhớ) và so sánh NỘI DUNG (a == b qua nạp chồng
 * operator== — hai object có cùng giá trị nghiệp vụ không), kèm quy ước đi cùng:
 * muốn bỏ Money vào unordered_set/unordered_map thì phải cung cấp hàm băm
 * (std::hash) nhất quán với operator==.
 *
 * Tại sao cần học: khác Java (== có sẵn nhưng so địa chỉ), C++ KHÔNG tự sinh
 * operator== cho class — quên nạp chồng là code không biên dịch; còn nạp chồng
 * lệch với hàm băm làm object "biến mất" trong unordered_set/unordered_map.
 */
#include <cstdint>    // thư viện chuẩn: std::int64_t — số nguyên 64 bit cho tiền
#include <cstdlib>    // thư viện chuẩn: std::exit để dừng chương trình khi self-check thất bại
#include <functional> // thư viện chuẩn: std::hash để sinh mã băm
#include <iostream>   // thư viện chuẩn: std::cout/std::cerr để in ra màn hình
#include <stdexcept>  // thư viện chuẩn: std::invalid_argument để báo lỗi dữ liệu sai
#include <string>     // thư viện chuẩn: std::string cho loại tiền

class Money { // khai báo class — khuôn mẫu để tạo ra các object Money
private:
    const std::int64_t amount;  // số tiền (đơn vị nhỏ nhất) — dùng số nguyên, không dùng double cho tiền
    const std::string currency; // loại tiền, vd. "VND", "USD"

public:
    Money(std::int64_t amount, const std::string& currency) : amount(amount), currency(currency) { // constructor — chạy khi tạo object
        if (amount < 0) throw std::invalid_argument("Số tiền không được âm"); // validate: chặn tiền âm
        if (currency.empty()) throw std::invalid_argument("Loại tiền không được rỗng"); // validate: loại tiền bắt buộc
    }

    bool operator==(const Money& other) const { // nạp chồng == : so sánh NỘI DUNG — C++ không tự sinh, phải tự viết
        return amount == other.amount && currency == other.currency; // bằng nhau khi CÙNG số tiền và CÙNG loại tiền
    }

    bool operator!=(const Money& other) const { // nạp chồng != cho đủ cặp — luôn định nghĩa qua == để hai toán tử không lệch nhau
        return !(*this == other); // phủ định của == (*this = object hiện tại)
    }

    std::size_t hashValue() const { // mã băm — hai object == nhau PHẢI trả về cùng mã băm (như quy ước equals/hashCode của Java)
        return std::hash<std::int64_t>{}(amount) ^ (std::hash<std::string>{}(currency) << 1); // kết hợp mã băm của đúng các field mà operator== so sánh
    }
};

// ---- Self-check ----
static void check(bool ok, const std::string& msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
    if (!ok) { std::cerr << "FAIL: " << msg << "\n"; std::exit(1); } // in chỗ sai rồi dừng ngay
}

int main() { // điểm bắt đầu chạy chương trình sau khi biên dịch
    Money a(100'000, "VND"); // tạo object thứ nhất
    Money b(100'000, "VND"); // tạo object thứ hai — CÙNG giá trị nhưng KHÁC object trong bộ nhớ

    check(&a != &b, "hai lần khai báo phải tạo hai object khác nhau");        // so địa chỉ (&) : hai object riêng biệt trong bộ nhớ
    check(a == b, "cùng số tiền + loại tiền phải bằng nhau");                  // operator== so nội dung: cùng giá trị nghiệp vụ
    check(a.hashValue() == b.hashValue(), "bằng nhau phải cùng mã băm");       // quy ước ==/hash: bằng nhau thì băm giống nhau
    check(a != Money(100'000, "USD"), "khác loại tiền không được bằng nhau");  // 100k VND khác 100k USD
    check(a != Money(50'000, "VND"), "khác số tiền không được bằng nhau");     // 100k khác 50k

    std::cout << "OK\n"; // in "OK" nếu mọi check ở trên đều đúng
    return 0; // báo chương trình kết thúc thành công
}
