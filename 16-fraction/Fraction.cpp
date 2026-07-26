/*
 * Ngôn ngữ: C++
 * Công dụng: Fraction minh họa OBJECT BẤT BIẾN (immutable) — không có
 * setter nào, mọi phép toán (add, multiply) không sửa object đang có mà
 * TRẢ VỀ MỘT OBJECT MỚI. Tử số/mẫu số được rút gọn và chuẩn hóa dấu ngay
 * trong constructor, chạy đúng một lần.
 * Tại sao cần học: bài 04 (Counter) và bài 06 (BankAccount) đều là object
 * CÓ TRẠNG THÁI THAY ĐỔI — phương thức sửa dữ liệu ngay trên chính object.
 * Bài này đối lập hoàn toàn: object bất biến an toàn hơn khi chia sẻ giữa
 * nhiều nơi trong chương trình (không ai vô tình sửa được nó) — nền tảng
 * của kiểu const value như std::chrono::duration.
 */
#include <cstdlib>   // thư viện chuẩn: std::exit để dừng chương trình khi self-check thất bại
#include <iostream>  // thư viện chuẩn: std::cout/std::cerr để in ra màn hình
#include <numeric>   // thư viện chuẩn: std::gcd (C++17) — ước chung lớn nhất, không cần tự viết thuật toán Euclid
#include <sstream>   // thư viện chuẩn: std::ostringstream để ghép chuỗi từ nhiều kiểu dữ liệu
#include <stdexcept> // thư viện chuẩn: std::invalid_argument để báo lỗi dữ liệu sai
#include <string>    // thư viện chuẩn: std::string cho chuỗi mô tả

class Fraction { // khai báo class — khuôn mẫu để tạo ra các object Fraction
private:
    int numerator;   // tử số — gán một lần trong constructor, không đổi sau đó
    int denominator; // mẫu số — luôn dương sau khi chuẩn hóa, không đổi sau đó

public:
    Fraction(int numerator, int denominator) { // constructor — chạy khi tạo object
        if (denominator == 0) throw std::invalid_argument("Mẫu số không được bằng 0"); // validate ở biên

        if (denominator < 0) { // chuẩn hóa dấu: mẫu số luôn dương, dấu âm (nếu có) dồn hết về tử số
            numerator = -numerator;
            denominator = -denominator;
        }

        int g = std::gcd(numerator, denominator); // std::gcd tự lấy giá trị tuyệt đối, luôn trả về ước chung không âm
        this->numerator = numerator / g;     // rút gọn tử số
        this->denominator = denominator / g; // rút gọn mẫu số
    }

    int getNumerator() const { // getter — xem tử số hiện tại (đã rút gọn)
        return numerator;
    }

    int getDenominator() const { // getter — xem mẫu số hiện tại (đã rút gọn)
        return denominator;
    }

    Fraction add(const Fraction& other) const { // cộng phân số — KHÔNG sửa this hay other, trả về Fraction MỚI
        return Fraction(
            numerator * other.denominator + other.numerator * denominator,
            denominator * other.denominator
        ); // a/b + c/d = (ad + bc) / bd — constructor mới tự rút gọn kết quả
    }

    Fraction multiply(const Fraction& other) const { // nhân phân số — KHÔNG sửa this hay other, trả về Fraction MỚI
        return Fraction(numerator * other.numerator, denominator * other.denominator); // a/b * c/d = ac / bd
    }

    std::string toString() const { // object tự mô tả chính nó, vd. "1/2"
        std::ostringstream out; // luồng ghép chuỗi — cách chuẩn của C++ để nối chữ và số
        out << numerator << "/" << denominator; // ghép tử số và mẫu số
        return out.str(); // lấy chuỗi kết quả ra khỏi luồng
    }
};

// ---- Self-check ----
static void check(bool ok, const std::string& msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
    if (!ok) { std::cerr << "FAIL: " << msg << "\n"; std::exit(1); } // in chỗ sai rồi dừng ngay
}

int main() { // điểm bắt đầu chạy chương trình sau khi biên dịch
    Fraction a(2, 4); // 2/4 phải tự rút gọn
    check(a.toString() == "1/2", "2/4 phải tự rút gọn thành 1/2");

    Fraction b(-1, -2); // cả tử lẫn mẫu âm — phải chuẩn hóa thành dương
    check(b.toString() == "1/2", "cả tử lẫn mẫu âm phải chuẩn hóa thành dương");

    Fraction c(1, -2); // mẫu âm — dấu phải dồn về tử số
    check(c.toString() == "-1/2", "dấu âm phải dồn về tử số, mẫu số luôn dương");

    Fraction sum = a.add(Fraction(1, 3)); // 1/2 + 1/3 = 5/6
    check(sum.toString() == "5/6", "1/2 + 1/3 phải bằng 5/6");
    check(a.toString() == "1/2", "add() không được sửa object gốc — object bất biến"); // a giữ nguyên sau add()

    Fraction product = a.multiply(Fraction(2, 3)); // 1/2 * 2/3 = 2/6 = 1/3
    check(product.toString() == "1/3", "1/2 * 2/3 phải rút gọn thành 1/3");

    bool blocked = false; // cờ đánh dấu: mẫu số 0 có bị chặn không
    try { Fraction bad(1, 0); } catch (const std::invalid_argument&) { blocked = true; } // mẫu số 0 phải bị chặn
    check(blocked, "mẫu số bằng 0 phải bị chặn");

    std::cout << "OK\n"; // in "OK" nếu mọi check ở trên đều đúng
    return 0; // báo chương trình kết thúc thành công
}
