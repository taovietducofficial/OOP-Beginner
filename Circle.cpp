/*
 * Ngôn ngữ: C++
 *
 * Công dụng: Circle làm quen với `static constexpr` (hằng số PI thuộc về CLASS,
 * dùng chung cho mọi object) khác với field thường như `radius` (thuộc về
 * TỪNG object, mỗi object một giá trị riêng).
 *
 * Tại sao cần học: nhầm lẫn giữa static và instance field là lỗi rất phổ biến
 * của người mới, gây ra bug khó tìm (dữ liệu bị "dùng chung" ngoài ý muốn giữa
 * các object). Hiểu đúng khái niệm này là điều kiện bắt buộc trước khi học
 * static method, singleton, hay biến đếm toàn cục.
 */
#include <cmath>     // thư viện chuẩn: std::abs cho số thực khi so sánh gần đúng
#include <cstdlib>   // thư viện chuẩn: std::exit để dừng chương trình khi self-check thất bại
#include <iostream>  // thư viện chuẩn: std::cout/std::cerr để in ra màn hình
#include <stdexcept> // thư viện chuẩn: std::invalid_argument để báo lỗi dữ liệu sai
#include <string>    // thư viện chuẩn: std::string cho thông điệp lỗi

class Circle { // khai báo class — khuôn mẫu để tạo ra các object Circle
private:
    static constexpr double PI = 3.14159; // hằng số CLASS: chỉ có 1 bản duy nhất, mọi object Circle dùng chung — "static constexpr" của C++ tương đương "static final" của Java

    const double radius; // thuộc tính INSTANCE: mỗi object Circle có bán kính riêng của mình

public:
    explicit Circle(double radius) : radius(radius) { // constructor — "explicit" chặn C++ tự đổi ngầm số thành Circle ngoài ý muốn
        if (radius <= 0) throw std::invalid_argument("Bán kính phải > 0"); // validate ở biên: chặn bán kính không hợp lệ
    }

    double area() const { // hàm tính diện tích — dùng hằng số chung PI + dữ liệu riêng radius
        return PI * radius * radius; // công thức diện tích hình tròn = PI * r^2
    }

    double circumference() const { // hàm tính chu vi
        return 2 * PI * radius; // công thức chu vi hình tròn = 2 * PI * r
    }
};

// ---- Self-check ----
static void check(bool ok, const std::string& msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
    if (!ok) { std::cerr << "FAIL: " << msg << "\n"; std::exit(1); } // in chỗ sai rồi dừng ngay
}

int main() { // điểm bắt đầu chạy chương trình sau khi biên dịch
    Circle c(2); // tạo object Circle với bán kính = 2
    check(std::abs(c.area() - 12.56636) < 1e-5, "diện tích bán kính 2 sai"); // so sánh gần đúng vì số thực có sai số dấu phẩy động
    check(std::abs(c.circumference() - 12.56636) < 1e-5, "chu vi bán kính 2 sai"); // tương tự, kiểm tra chu vi gần đúng

    std::cout << "OK\n"; // in "OK" nếu mọi check ở trên đều đúng
    return 0; // báo chương trình kết thúc thành công
}
