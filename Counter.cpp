/*
 * Ngôn ngữ: C++
 *
 * Công dụng: Counter minh họa object có TRẠNG THÁI (state) thay đổi qua thời
 * gian — mỗi lần gọi increment()/decrement() làm dữ liệu bên trong object đổi,
 * và mỗi object Counter giữ trạng thái độc lập với object khác cùng class.
 *
 * Tại sao cần học: đây là ý tưởng lõi của MỌI object có trạng thái trong thực
 * tế — giỏ hàng, phiên đăng nhập, kết nối mạng. Nếu không hiểu rõ mỗi object
 * có state riêng, độc lập, rất dễ viết bug chia sẻ dữ liệu ngoài ý muốn khi
 * hệ thống lớn lên (đặc biệt trong môi trường nhiều luồng/nhiều người dùng).
 */
#include <cstdlib>   // thư viện chuẩn: std::exit để dừng chương trình khi self-check thất bại
#include <iostream>  // thư viện chuẩn: std::cout/std::cerr để in ra màn hình
#include <stdexcept> // thư viện chuẩn: std::logic_error để báo thao tác sai trạng thái
#include <string>    // thư viện chuẩn: std::string cho thông điệp lỗi

class Counter { // khai báo class — khuôn mẫu để tạo ra các object Counter
private:
    int value; // thuộc tính: giá trị đếm hiện tại — đây là "trạng thái" thay đổi theo thời gian (KHÔNG const vì nó đổi)

public:
    Counter() : value(0) { // constructor không tham số — giá trị khởi tạo luôn bắt đầu từ 0
    }

    void increment() { // hàm tăng — thay đổi trạng thái của object (không có "const" cuối hàm vì nó SỬA dữ liệu)
        value++; // cộng thêm 1 vào giá trị hiện tại
    }

    void decrement() { // hàm giảm — thay đổi trạng thái, có kiểm tra ràng buộc
        if (value == 0) throw std::logic_error("Không thể giảm dưới 0"); // validate: chặn giảm xuống âm
        value--; // trừ 1 khỏi giá trị hiện tại
    }

    void reset() { // hàm đưa trạng thái về ban đầu
        value = 0; // gán lại giá trị về 0
    }

    int getValue() const { // getter — cho phép đọc trạng thái hiện tại từ bên ngoài, không cho sửa trực tiếp
        return value; // trả về giá trị hiện tại của object
    }
};

// ---- Self-check ----
static void check(bool ok, const std::string& msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
    if (!ok) { std::cerr << "FAIL: " << msg << "\n"; std::exit(1); } // in chỗ sai rồi dừng ngay
}

int main() { // điểm bắt đầu chạy chương trình sau khi biên dịch
    Counter c; // tạo object Counter, value bắt đầu = 0
    check(c.getValue() == 0, "khởi tạo phải là 0"); // kiểm tra giá trị khởi tạo

    c.increment(); // tăng lần 1 -> value = 1
    c.increment(); // tăng lần 2 -> value = 2
    c.increment(); // tăng lần 3 -> value = 3
    check(c.getValue() == 3, "sau 3 lần tăng phải là 3"); // kiểm tra sau 3 lần tăng

    c.decrement(); // giảm 1 lần -> value = 2
    check(c.getValue() == 2, "sau 1 lần giảm phải là 2"); // kiểm tra sau khi giảm

    c.reset(); // đưa value về 0
    check(c.getValue() == 0, "sau reset phải là 0"); // kiểm tra sau reset

    // Object khác của cùng class có trạng thái độc lập.
    Counter other; // tạo object thứ hai, hoàn toàn tách biệt với "c"
    other.increment(); // tăng riêng trên object "other" -> other.value = 1
    check(other.getValue() == 1 && c.getValue() == 0, "hai object phải độc lập nhau"); // "c" không bị ảnh hưởng bởi "other"

    std::cout << "OK\n"; // in "OK" nếu mọi check ở trên đều đúng
    return 0; // báo chương trình kết thúc thành công
}
