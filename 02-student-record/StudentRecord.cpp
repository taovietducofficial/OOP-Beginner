/*
 * Ngôn ngữ: C++
 * Công dụng: StudentRecord có nhiều thuộc tính (name, age, score) và cho thấy
 * một phương thức (summary) gọi lại phương thức khác (isPassed) trên cùng object.
 * Tại sao cần học: dữ liệu thực tế (user, order, product...) luôn có nhiều field
 * liên quan với nhau, và quy tắc nghiệp vụ (vd. "điểm >= 5 là đậu") phải nằm
 * TRONG class, dùng lại qua gọi hàm nội bộ — thay vì lặp lại điều kiện đó ở
 * nhiều nơi trong code. Đây là thói quen giúp code dễ sửa, ít bug khi quy tắc đổi.
 */
#include <cstdlib>   // thư viện chuẩn: std::exit để dừng chương trình khi self-check thất bại
#include <iostream>  // thư viện chuẩn: std::cout/std::cerr để in ra màn hình
#include <sstream>   // thư viện chuẩn: std::ostringstream để ghép chuỗi từ nhiều kiểu dữ liệu
#include <stdexcept> // thư viện chuẩn: std::invalid_argument để báo lỗi dữ liệu sai
#include <string>    // thư viện chuẩn: std::string cho tên và thông điệp

class StudentRecord { // khai báo class — khuôn mẫu để tạo ra các object StudentRecord
private:
    const std::string name; // thuộc tính: tên học sinh — riêng cho từng object
    const int age;          // thuộc tính: tuổi — riêng cho từng object
    const double score;     // thuộc tính: điểm số — riêng cho từng object

public:
    StudentRecord(const std::string& name, int age, double score) : name(name), age(age), score(score) { // constructor — field const gán qua danh sách khởi tạo sau dấu ":"
        if (name.empty()) throw std::invalid_argument("Tên không được rỗng"); // validate: tên không được thiếu
        if (age <= 0) throw std::invalid_argument("Tuổi phải > 0"); // validate: tuổi phải hợp lệ
        if (score < 0 || score > 10) throw std::invalid_argument("Điểm phải trong [0,10]"); // validate: điểm phải nằm trong thang điểm
    }

    bool isPassed() const { // hàm kiểm tra đậu/rớt — hành vi dựa trên dữ liệu score của chính object
        return score >= 5; // quy tắc nghiệp vụ: đậu nếu điểm >= 5
    }

    std::string summary() const { // hàm tạo chuỗi mô tả tổng hợp — gọi lại isPassed() thay vì viết lại điều kiện
        std::ostringstream out; // luồng ghép chuỗi — cách chuẩn của C++ để nối chữ và số
        out << name << " (" << age << " tuổi) - điểm " << score << " - " << (isPassed() ? "Đậu" : "Rớt"); // ghép các thuộc tính + kết quả isPassed() thành 1 chuỗi
        return out.str(); // lấy chuỗi kết quả ra khỏi luồng
    }
};

// ---- Self-check ----
static void check(bool ok, const std::string& msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
    if (!ok) { std::cerr << "FAIL: " << msg << "\n"; std::exit(1); } // in chỗ sai rồi dừng ngay
}

int main() { // điểm bắt đầu chạy chương trình sau khi biên dịch
    StudentRecord an("An", 20, 7.5); // tạo object An, điểm 7.5 (đậu)
    check(an.isPassed(), "điểm 7.5 phải đậu"); // kiểm tra isPassed() trả về true
    check(an.summary() == "An (20 tuổi) - điểm 7.5 - Đậu", "summary sai"); // kiểm tra summary() ghép chuỗi đúng

    StudentRecord binh("Binh", 21, 3.0); // tạo object Binh, điểm 3.0 (rớt)
    check(!binh.isPassed(), "điểm 3.0 phải rớt"); // kiểm tra isPassed() trả về false

    std::cout << "OK\n"; // in "OK" nếu mọi check ở trên đều đúng
    return 0; // báo chương trình kết thúc thành công
}
