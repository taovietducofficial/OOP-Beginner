/*
 * Ngôn ngữ: C++
 *
 * Công dụng: Rectangle gói dữ liệu (width, height) và hành vi (area, perimeter)
 * vào chung một class — bài đầu tiên minh họa Class & Object.
 *
 * Tại sao cần học: đây là viên gạch nền của toàn bộ OOP. Mọi hệ thống thực tế
 * (đơn hàng, tài khoản, sản phẩm...) đều được mô hình hóa bằng class/object
 * như thế này. Không nắm chắc bước "gom dữ liệu + hành vi vào 1 class" thì
 * không thể hiểu các bài sau về đóng gói, kế thừa, đa hình.
 */
#include <cstdlib>   // thư viện chuẩn: std::exit để dừng chương trình khi self-check thất bại
#include <iostream>  // thư viện chuẩn: std::cout/std::cerr để in ra màn hình
#include <stdexcept> // thư viện chuẩn: std::invalid_argument để báo lỗi dữ liệu sai
#include <string>    // thư viện chuẩn: std::string cho thông điệp lỗi

class Rectangle { // khai báo class — khuôn mẫu để tạo ra các object Rectangle
private:                 // private: dữ liệu bên trong, bên ngoài class không đụng trực tiếp được
    const double width;  // thuộc tính: chiều rộng — riêng cho từng object, const = không đổi sau khi tạo (như final của Java)
    const double height; // thuộc tính: chiều cao — riêng cho từng object, không đổi sau khi tạo

public: // public: phần giao tiếp với bên ngoài — constructor và các phương thức
    Rectangle(double width, double height) : width(width), height(height) { // constructor — chạy khi tạo object; C++ gán field const bằng danh sách khởi tạo "field(giá trị)" sau dấu ":"
        if (width <= 0 || height <= 0) throw std::invalid_argument("Cạnh phải > 0"); // validate ở biên: chặn dữ liệu sai ngay lúc tạo object
    }

    double area() const { // hàm tính diện tích — "const" cuối hàm: cam kết không sửa dữ liệu của object
        return width * height; // công thức diện tích hình chữ nhật = rộng * cao
    }

    double perimeter() const { // hàm tính chu vi — cũng là hành vi thao tác trên dữ liệu riêng của object
        return 2 * (width + height); // công thức chu vi = 2 * (rộng + cao)
    }
};

// ---- Self-check ----
static void check(bool ok, const std::string& msg) { // hàm phụ trợ: nếu điều kiện "ok" sai thì báo lỗi kèm thông điệp "msg"
    if (!ok) { std::cerr << "FAIL: " << msg << "\n"; std::exit(1); } // in chỗ sai rồi dừng ngay khi self-check thất bại
}

int main() { // điểm bắt đầu chạy chương trình (entry point) sau khi biên dịch
    Rectangle r(4, 5); // tạo object Rectangle với rộng=4, cao=5 — C++ không cần từ khóa "new" khi tạo trên stack
    check(r.area() == 20, "diện tích 4x5 phải là 20");   // kiểm tra area() tính đúng: 4*5=20
    check(r.perimeter() == 18, "chu vi 4x5 phải là 18"); // kiểm tra perimeter() tính đúng: 2*(4+5)=18

    Rectangle square(3, 3); // tạo thêm 1 object khác — hình vuông là trường hợp đặc biệt của hình chữ nhật (rộng = cao)
    check(square.area() == 9, "diện tích hình vuông cạnh 3 phải là 9"); // kiểm tra diện tích: 3*3=9

    std::cout << "OK\n"; // in "OK" nếu mọi check ở trên đều đúng (không có check nào dừng chương trình)
    return 0; // trả về 0 báo cho hệ điều hành: chương trình kết thúc thành công
}
