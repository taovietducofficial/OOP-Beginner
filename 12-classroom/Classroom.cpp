/*
 * Ngôn ngữ: C++
 * Công dụng: Classroom minh họa một class QUẢN LÝ TẬP HỢP nhiều object khác
 * cùng loại (std::vector<Student>) — thêm phần tử, và tính toán tổng hợp
 * (average, top) bằng cách duyệt qua cả tập hợp.
 * Tại sao cần học: dữ liệu thật hiếm khi chỉ có 1 object đơn lẻ — một lớp có
 * nhiều học sinh, một đơn hàng có nhiều sản phẩm, một giỏ hàng có nhiều món.
 * Biết cách một class "chứa nhiều object con" và tổng hợp dữ liệu từ chúng
 * là kỹ năng nền cho hầu hết hệ thống thực tế.
 */
#include <cstdlib>   // thư viện chuẩn: std::exit để dừng chương trình khi self-check thất bại
#include <iostream>  // thư viện chuẩn: std::cout/std::cerr để in ra màn hình
#include <stdexcept> // thư viện chuẩn: std::invalid_argument, std::runtime_error để báo lỗi
#include <string>    // thư viện chuẩn: std::string cho tên
#include <vector>    // thư viện chuẩn: std::vector — danh sách động, thêm phần tử không cần khai báo trước kích thước

class Student { // class phụ trợ — mỗi học sinh có tên và điểm
private:
    std::string name; // tên học sinh — riêng cho từng object, không đổi sau khi tạo
    double score;     // điểm số — riêng cho từng object, không đổi sau khi tạo

public:
    Student(std::string name, double score) : name(std::move(name)), score(score) { // constructor — chạy khi tạo một học sinh
        if (score < 0 || score > 10) throw std::invalid_argument("Điểm phải trong khoảng 0-10"); // validate ở biên: điểm phải hợp lệ
    }

    const std::string& getName() const { // getter — xem tên học sinh
        return name; // trả về tên
    }

    double getScore() const { // getter — xem điểm học sinh
        return score; // trả về điểm
    }
};

class Classroom { // khai báo class — khuôn mẫu để tạo ra các object Classroom
private:
    std::string name;             // tên lớp — riêng cho từng object, không đổi sau khi tạo
    std::vector<Student> students; // TẬP HỢP: Classroom chứa nhiều Student, mỗi lớp giữ danh sách riêng của mình

public:
    explicit Classroom(std::string name) : name(std::move(name)) { // constructor — chạy khi tạo một lớp học, ban đầu chưa có học sinh nào
    }

    const std::string& getName() const { // getter — xem tên lớp
        return name; // trả về tên lớp
    }

    void addStudent(const Student& s) { // thêm một học sinh vào lớp
        students.push_back(s); // đưa vào cuối danh sách (vector tự copy Student vào bộ nhớ của nó)
    }

    std::size_t size() const { // đếm số học sinh hiện có trong lớp
        return students.size(); // kích thước vector
    }

    double averageScore() const { // tính điểm trung bình cả lớp — TỔNG HỢP dữ liệu từ nhiều object con
        if (students.empty()) return 0; // lớp rỗng: quy ước trung bình là 0, tránh chia cho 0
        double sum = 0; // biến cộng dồn điểm
        for (const Student& s : students) sum += s.getScore(); // duyệt qua từng học sinh, cộng điểm của nó vào tổng
        return sum / static_cast<double>(students.size()); // trung bình = tổng điểm / số học sinh
    }

    std::string topStudent() const { // tìm tên học sinh điểm cao nhất — TỔNG HỢP dữ liệu bằng cách so sánh qua từng object con
        if (students.empty()) throw std::runtime_error("Lớp chưa có học sinh nào"); // không có gì để tìm nếu lớp rỗng
        const Student* top = &students[0]; // giả định học sinh đầu tiên đang dẫn đầu (dùng con trỏ để tránh copy)
        for (const Student& s : students) { // duyệt qua từng học sinh còn lại
            if (s.getScore() > top->getScore()) top = &s; // học sinh nào điểm cao hơn thì thay vào vị trí dẫn đầu
        }
        return top->getName(); // trả về tên học sinh điểm cao nhất
    }
};

// ---- Self-check ----
static void check(bool ok, const std::string& msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
    if (!ok) { std::cerr << "FAIL: " << msg << "\n"; std::exit(1); } // in chỗ sai rồi dừng ngay
}

int main() { // điểm bắt đầu chạy chương trình sau khi biên dịch
    Classroom room("10A"); // tạo lớp 10A, ban đầu rỗng
    check(room.getName() == "10A", "tên lớp phải giữ đúng như lúc tạo"); // getter trả đúng dữ liệu đã gán
    check(room.size() == 0, "lớp mới tạo chưa có học sinh nào"); // chưa addStudent lần nào

    room.addStudent(Student("An", 8.0));    // thêm học sinh An, điểm 8.0
    room.addStudent(Student("Binh", 9.5));  // thêm học sinh Binh, điểm 9.5
    room.addStudent(Student("Chi", 7.0));   // thêm học sinh Chi, điểm 7.0

    check(room.size() == 3, "lớp phải có 3 học sinh"); // đếm đúng số phần tử đã thêm
    check(room.averageScore() > 8.1666 && room.averageScore() < 8.1667, "điểm trung bình tính sai"); // (8.0+9.5+7.0)/3, so sánh gần đúng vì số thực
    check(room.topStudent() == "Binh", "học sinh điểm cao nhất phải là Binh"); // 9.5 là điểm cao nhất

    std::cout << "OK\n"; // in "OK" nếu mọi check ở trên đều đúng
    return 0; // báo chương trình kết thúc thành công
}
