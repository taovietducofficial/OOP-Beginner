/*
 * Ngôn ngữ: C++
 * Công dụng: Temperature minh họa STATIC FACTORY METHOD — constructor để
 * private, object chỉ được tạo qua các phương thức static có TÊN RÕ NGHĨA
 * (fromCelsius, fromFahrenheit) thay vì qua "Temperature(...)" mù mờ.
 * Tại sao cần học: bài 07 overload nhiều constructor cùng tên khi THAM SỐ
 * khác kiểu/số lượng. Nhưng ở đây fromCelsius(double) và fromFahrenheit(double)
 * có CÙNG kiểu tham số (double) — không thể overload constructor vì trùng
 * chữ ký. Static factory method giải quyết đúng vấn đề này: tên phương thức
 * tự nói lên ý nghĩa, còn constructor bị khóa private để ép mọi người đi
 * qua factory.
 */
#include <cstdlib>   // thư viện chuẩn: std::exit để dừng chương trình khi self-check thất bại
#include <iostream>  // thư viện chuẩn: std::cout/std::cerr để in ra màn hình
#include <stdexcept> // thư viện chuẩn: std::invalid_argument để báo lỗi dữ liệu sai
#include <string>    // thư viện chuẩn: std::string cho thông điệp lỗi

class Temperature { // khai báo class — khuôn mẫu để tạo ra các object Temperature
private:
    static constexpr double ABSOLUTE_ZERO_C = -273.15; // hằng số CLASS: 0 tuyệt đối theo độ C — dùng chung cho mọi object, không đổi

    double celsius; // nhiệt độ lưu trữ nội bộ luôn theo độ C — chọn 1 đơn vị chuẩn để tính toán, quy đổi khi cần hiển thị

    explicit Temperature(double celsius) : celsius(celsius) { // constructor PRIVATE — bên ngoài không tạo trực tiếp được, phải đi qua factory method static
        if (celsius < ABSOLUTE_ZERO_C) throw std::invalid_argument("Nhiệt độ không thể thấp hơn 0 tuyệt đối"); // validate ở biên: chặn giá trị vô lý về mặt vật lý
    }

public:
    static Temperature fromCelsius(double celsius) { // FACTORY METHOD: tạo Temperature từ độ C — tên tự giải thích, khỏi cần đoán tham số là đơn vị gì
        return Temperature(celsius); // độ C đã là đơn vị chuẩn nội bộ, không cần quy đổi; static method cùng class được phép gọi constructor private
    }

    static Temperature fromFahrenheit(double fahrenheit) { // FACTORY METHOD: tạo Temperature từ độ F — quy đổi sang độ C rồi mới gọi constructor
        return Temperature((fahrenheit - 32) * 5 / 9); // công thức quy đổi F sang C
    }

    double toCelsius() const { // đọc nhiệt độ theo độ C
        return celsius; // đơn vị chuẩn nội bộ, trả thẳng ra
    }

    double toFahrenheit() const { // đọc nhiệt độ theo độ F
        return celsius * 9 / 5 + 32; // công thức quy đổi C sang F
    }
};

// ---- Self-check ----
static void check(bool ok, const std::string& msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
    if (!ok) { std::cerr << "FAIL: " << msg << "\n"; std::exit(1); } // in chỗ sai rồi dừng ngay
}

int main() { // điểm bắt đầu chạy chương trình sau khi biên dịch
    Temperature boiling = Temperature::fromCelsius(100); // tạo qua factory "fromCelsius" — rõ ràng đây là 100 độ C
    check(boiling.toFahrenheit() == 212, "100°C phải bằng 212°F"); // nước sôi: mốc quy đổi kinh điển

    Temperature freezing = Temperature::fromFahrenheit(32); // tạo qua factory "fromFahrenheit" — rõ ràng đây là 32 độ F
    check(freezing.toCelsius() == 0, "32°F phải bằng 0°C"); // nước đóng băng: mốc quy đổi kinh điển

    bool blocked = false; // cờ đánh dấu: nhiệt độ dưới 0 tuyệt đối có bị chặn không
    try { Temperature::fromCelsius(-300); } catch (const std::invalid_argument&) { blocked = true; } // -300°C thấp hơn 0 tuyệt đối (-273.15°C) — phải bị chặn
    check(blocked, "nhiệt độ dưới 0 tuyệt đối phải bị chặn"); // xác nhận validate hoạt động dù tạo qua factory nào

    std::cout << "OK\n"; // in "OK" nếu mọi check ở trên đều đúng
    return 0; // báo chương trình kết thúc thành công
}
