/*
 * Ngôn ngữ: C++
 * Công dụng: Car minh họa KẾT HỢP (composition) — Car tự tạo ra Engine của
 * riêng mình ngay trong constructor, Engine sống chết theo Car (không object
 * nào khác nắm giữ Engine này). Car "ủy quyền" (delegate) các phương thức
 * start()/isRunning() cho engine bên trong thay vì tự làm hết.
 * Tại sao cần học: bài 05 cho object khác làm THAM SỐ (aggregation — hai
 * object độc lập, không sở hữu nhau). Bài này khác: Car SỞ HỮU Engine —
 * quan hệ "toàn thể - bộ phận" (whole-part). Đây là cách OOP mô hình hóa vật
 * thật gồm nhiều bộ phận: Car có Engine, Order có Address, Computer có CPU.
 */
#include <cstdlib>   // thư viện chuẩn: std::exit để dừng chương trình khi self-check thất bại
#include <iostream>  // thư viện chuẩn: std::cout/std::cerr để in ra màn hình
#include <stdexcept> // thư viện chuẩn: std::invalid_argument để báo lỗi dữ liệu sai
#include <string>    // thư viện chuẩn: std::string cho tên xe và thông điệp lỗi

class Engine { // class phụ trợ — chỉ Car (cùng file) cần biết tới; thế giới bên ngoài chỉ làm việc với Car
private:
    int horsepower;  // mã lực — riêng cho từng động cơ, không đổi sau khi tạo
    bool running = false; // trạng thái chạy/tắt — riêng cho từng động cơ, thay đổi được qua start()

public:
    explicit Engine(int horsepower) : horsepower(horsepower) { // constructor — chạy khi Car tạo Engine bên trong nó
        if (horsepower <= 0) throw std::invalid_argument("Mã lực phải > 0"); // validate ở biên: động cơ không thể có mã lực âm hoặc 0
    }

    void start() { // khởi động động cơ
        running = true; // chuyển trạng thái sang đang chạy
    }

    bool isRunning() const { // kiểm tra động cơ có đang chạy không
        return running; // trả về trạng thái hiện tại
    }

    int getHorsepower() const { // getter — xem mã lực động cơ
        return horsepower; // trả về mã lực
    }
};

class Car { // khai báo class — khuôn mẫu để tạo ra các object Car
private:
    std::string model; // tên dòng xe — riêng cho từng object, không đổi sau khi tạo
    Engine engine;      // KẾT HỢP: Car giữ MỘT Engine theo giá trị (không phải con trỏ) — Engine sống chết cùng Car

public:
    Car(std::string model, int horsepower) // constructor — nhận thông tin xe VÀ thông tin động cơ để tự tạo Engine bên trong
        : model(std::move(model)), engine(horsepower) { // Car TỰ TẠO Engine của mình ngay trong danh sách khởi tạo — đây chính là composition
        if (this->model.empty()) throw std::invalid_argument("Tên xe không được rỗng"); // validate ở biên: tên xe bắt buộc phải có
    }

    void start() { // khởi động xe — Car không tự biết cách nổ máy, nó NHỜ Engine của mình làm việc đó
        engine.start(); // ủy quyền (delegate) hành vi cho object bên trong
    }

    bool isRunning() const { // kiểm tra xe có đang chạy không
        return engine.isRunning(); // ủy quyền: hỏi thẳng Engine bên trong, Car không tự giữ trạng thái này
    }

    std::string describe() const { // mô tả xe — kết hợp dữ liệu của Car và dữ liệu của Engine bên trong nó
        return model + " (" + std::to_string(engine.getHorsepower()) + "hp)"; // ví dụ: "Toyota Vios (120hp)"
    }
};

// ---- Self-check ----
static void check(bool ok, const std::string& msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
    if (!ok) { std::cerr << "FAIL: " << msg << "\n"; std::exit(1); } // in chỗ sai rồi dừng ngay
}

int main() { // điểm bắt đầu chạy chương trình sau khi biên dịch
    Car car("Toyota Vios", 120); // tạo xe — Engine(120) được tạo tự động bên trong constructor của Car
    check(!car.isRunning(), "xe chưa start thì chưa được chạy"); // trạng thái ban đầu: chưa nổ máy
    check(car.describe() == "Toyota Vios (120hp)", "describe phải ghép đúng tên xe và mã lực"); // dữ liệu Car + Engine ghép lại đúng

    car.start(); // khởi động xe — thực chất là gọi engine.start() bên trong
    check(car.isRunning(), "sau start xe phải đang chạy"); // trạng thái đã đổi, dù Car không tự giữ biến "running"

    std::cout << "OK\n"; // in "OK" nếu mọi check ở trên đều đúng
    return 0; // báo chương trình kết thúc thành công
}
