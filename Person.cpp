/*
 * Ngôn ngữ: C++
 *
 * Công dụng: Person minh họa một object nhận OBJECT KHÁC làm tham số
 * (greet(const Person& other)) và gọi phương thức trên object đó (other.getName()).
 *
 * Tại sao cần học: đây là cách các object THỰC SỰ cộng tác với nhau trong hệ
 * thống thực tế — vd. order.applyDiscount(coupon), account.transferTo(otherAccount).
 * Nắm được cách 1 object thao tác dựa trên dữ liệu của object khác là bước đệm
 * bắt buộc trước khi học kế thừa và đa hình ở các tầng tiếp theo.
 */
#include <cstdlib>   // thư viện chuẩn: std::exit để dừng chương trình khi self-check thất bại
#include <iostream>  // thư viện chuẩn: std::cout/std::cerr để in ra màn hình
#include <stdexcept> // thư viện chuẩn: std::invalid_argument để báo lỗi dữ liệu sai
#include <string>    // thư viện chuẩn: std::string cho tên và chuỗi chào

class Person { // khai báo class — khuôn mẫu để tạo ra các object Person
private:
    const std::string name; // thuộc tính: tên — riêng cho từng object

public:
    explicit Person(const std::string& name) : name(name) { // constructor — "explicit" chặn tự đổi ngầm chuỗi thành Person
        if (name.empty()) throw std::invalid_argument("Tên không được rỗng"); // validate: tên không được thiếu
    }

    const std::string& getName() const { // getter — cho object khác đọc được tên, không cho sửa trực tiếp
        return name; // trả về tên của object hiện tại
    }

    // Nhận một Person khác làm tham số — hai object tương tác với nhau.
    std::string greet(const Person& other) const { // "const Person&" = mượn object khác để đọc, không sao chép, không sửa
        return name + " chào " + other.getName(); // dùng tên của chính mình (name) + gọi getName() trên object "other"
    }
};

// ---- Self-check ----
static void check(bool ok, const std::string& msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
    if (!ok) { std::cerr << "FAIL: " << msg << "\n"; std::exit(1); } // in chỗ sai rồi dừng ngay
}

int main() { // điểm bắt đầu chạy chương trình sau khi biên dịch
    Person an("An");     // tạo object thứ nhất
    Person binh("Binh"); // tạo object thứ hai

    check(an.greet(binh) == "An chào Binh", "An chào Binh sai");   // "an" chào "binh" — truyền binh làm tham số
    check(binh.greet(an) == "Binh chào An", "Binh chào An sai");   // ngược lại — truyền an làm tham số

    std::cout << "OK\n"; // in "OK" nếu mọi check ở trên đều đúng
    return 0; // báo chương trình kết thúc thành công
}
