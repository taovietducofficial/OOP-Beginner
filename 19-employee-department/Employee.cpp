/*
 * Ngôn ngữ: C++
 * Công dụng: Employee minh họa THAM CHIẾU DÙNG CHUNG (shared reference) —
 * Department được tạo BÊN NGOÀI rồi truyền vào constructor của Employee dưới
 * dạng "Department&" (tham chiếu), KHÔNG bị sao chép. Nhiều Employee có thể
 * cùng giữ tham chiếu tới đúng MỘT Department; đổi Department qua một
 * Employee thì mọi Employee khác cùng phòng ban đều "thấy" thay đổi ngay.
 * Tại sao cần học: bài 17 (Playlist) dạy rằng C++ trả về BẰNG GIÁ TRỊ là tự
 * động copy — an toàn. Bài này là MẶT TRÁI của bài học đó: nếu Employee lưu
 * "Department department;" (thành viên KIỂU GIÁ TRỊ, không phải tham chiếu),
 * constructor sẽ ÂM THẦM COPY Department vào trong — mỗi Employee có bản sao
 * riêng, rename() qua object gốc sẽ KHÔNG lan tới Employee nào cả. Muốn chia
 * sẻ thật sự, phải khai báo tường minh "Department&" (hoặc con trỏ/smart
 * pointer) — C++ không tự cho tham chiếu dùng chung như Java/Python.
 */
#include <cstdlib>   // thư viện chuẩn: std::exit để dừng chương trình khi self-check thất bại
#include <iostream>  // thư viện chuẩn: std::cout/std::cerr để in ra màn hình
#include <stdexcept> // thư viện chuẩn: std::invalid_argument để báo lỗi dữ liệu sai
#include <string>    // thư viện chuẩn: std::string cho tên

class Department { // class phụ trợ — phòng ban, được tạo và sống ĐỘC LẬP với bất kỳ Employee nào
private:
    std::string name; // tên phòng ban — CÓ THỂ đổi qua rename(), không như nhiều thuộc tính const đã gặp ở các bài trước

public:
    explicit Department(std::string name) { // constructor — chạy khi tạo một phòng ban
        if (name.empty()) throw std::invalid_argument("Tên phòng ban không được rỗng"); // validate ở biên
        this->name = std::move(name); // gán tên ban đầu
    }

    const std::string& getName() const { // getter — xem tên phòng ban hiện tại
        return name;
    }

    void rename(const std::string& newName) { // đổi tên phòng ban — mọi Employee đang giữ tham chiếu tới object này đều thấy thay đổi
        if (newName.empty()) throw std::invalid_argument("Tên phòng ban không được rỗng"); // validate ở biên
        name = newName; // cập nhật tại chỗ — chính là lý do mọi tham chiếu dùng chung đều "thấy" thay đổi
    }
};

class Employee { // khai báo class — khuôn mẫu để tạo ra các object Employee
private:
    std::string name;      // tên nhân viên — riêng cho từng object, không đổi sau khi tạo
    Department& department; // THAM CHIẾU DÙNG CHUNG — bắt buộc khai báo "&" để không copy Department khi gán vào; Department phải sống lâu hơn Employee này

public:
    Employee(std::string name, Department& department) : department(department) { // constructor — nhận Department đã tồn tại sẵn từ BÊN NGOÀI qua tham chiếu
        if (name.empty()) throw std::invalid_argument("Tên nhân viên không được rỗng"); // validate ở biên
        this->name = std::move(name); // gán tên
    }

    const std::string& getName() const { // getter — xem tên nhân viên
        return name;
    }

    Department& getDepartment() const { // trả THẲNG tham chiếu Department dùng chung (cố ý, không copy — xem README)
        return department;
    }

    const std::string& getDepartmentName() const { // ủy quyền: hỏi thẳng Department hiện tại tên là gì
        return department.getName();
    }
};

// ---- Self-check ----
static void check(bool ok, const std::string& msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
    if (!ok) { std::cerr << "FAIL: " << msg << "\n"; std::exit(1); } // in chỗ sai rồi dừng ngay
}

int main() { // điểm bắt đầu chạy chương trình sau khi biên dịch
    Department eng("Engineering"); // tạo phòng ban BÊN NGOÀI, sống suốt phần đời của main()
    Employee e1("An", eng);   // An thuộc phòng eng — giữ tham chiếu, không copy
    Employee e2("Binh", eng); // Binh CŨNG thuộc CHÍNH phòng eng — cùng một object Department

    check(&e1.getDepartment() == &e2.getDepartment(), "hai nhân viên cùng phòng phải giữ CHUNG một object Department (so địa chỉ)");
    check(e1.getDepartmentName() == "Engineering", "tên phòng ban đọc qua Employee phải đúng ban đầu");

    eng.rename("Platform Engineering"); // đổi tên phòng ban CHỈ MỘT LẦN, qua chính object Department
    check(e1.getDepartmentName() == "Platform Engineering", "đổi tên Department phải phản ánh qua e1 (cùng tham chiếu)");
    check(e2.getDepartmentName() == "Platform Engineering", "đổi tên Department phải phản ánh qua e2 (cùng tham chiếu)");

    Department hr("HR"); // phòng ban KHÁC — object hoàn toàn riêng biệt
    Employee e3("Chi", hr); // Chi thuộc phòng hr, không liên quan gì tới eng
    eng.rename("Something Else"); // đổi tiếp phòng eng
    check(e3.getDepartmentName() == "HR", "đổi Department eng không được ảnh hưởng tới Employee thuộc Department khác");

    bool blocked = false; // cờ đánh dấu: tên nhân viên rỗng có bị chặn không
    try { Employee bad("", eng); } catch (const std::invalid_argument&) { blocked = true; }
    check(blocked, "tên nhân viên rỗng phải bị chặn");

    std::cout << "OK\n"; // in "OK" nếu mọi check ở trên đều đúng
    return 0; // báo chương trình kết thúc thành công
}
