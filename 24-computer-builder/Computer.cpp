/*
 * Ngôn ngữ: C++
 * Công dụng: Computer/ComputerBuilder minh họa BUILDER PATTERN — ComputerBuilder
 * là một object TẠM THỜI, riêng biệt, dùng để gom dữ liệu cấu hình qua nhiều
 * bước (setCpu, setRam, setSsd, theo thứ tự bất kỳ). Computer THẬT SỰ chưa
 * tồn tại cho tới khi gọi build() — lúc đó nó được tạo MỘT LẦN, đầy đủ, và
 * bất biến từ đầu.
 * Tại sao cần học: bài 18 (PizzaOrder) dùng fluent interface — object đã tồn
 * tại từ đầu, mỗi lần gọi addTopping() là SỬA NGAY chính nó. Bài này khác:
 * Computer KHÔNG có setter nào cả, không thể sửa sau khi build(); mọi việc
 * "sửa dần" chỉ xảy ra trên ComputerBuilder tạm thời, không phải trên chính
 * Computer.
 */
#include <cstdlib>   // thư viện chuẩn: std::exit để dừng chương trình khi self-check thất bại
#include <iostream>  // thư viện chuẩn: std::cout/std::cerr để in ra màn hình
#include <stdexcept> // thư viện chuẩn: std::invalid_argument, std::logic_error để báo lỗi
#include <string>    // thư viện chuẩn: std::string

class Computer { // sản phẩm cuối — BẤT BIẾN, chỉ có getter, không setter (giống Fraction ở bài 16)
private:
    std::string cpu;
    int ram;
    bool ssd;

    friend class ComputerBuilder; // CHỈ ComputerBuilder được gọi constructor riêng tư bên dưới — ép mọi nơi khác đi qua Builder

    Computer(std::string cpu, int ram, bool ssd) // constructor PRIVATE — không public để bên ngoài không tạo trực tiếp
        : cpu(std::move(cpu)), ram(ram), ssd(ssd) {}

public:
    const std::string& getCpu() const { return cpu; } // getter — xem cpu đã cấu hình
    int getRam() const { return ram; }                   // getter — xem dung lượng RAM (GB)
    bool hasSsd() const { return ssd; }                   // getter — có ổ SSD hay không
};

class ComputerBuilder { // object TẠM THỜI — gom dữ liệu qua nhiều bước, chưa phải Computer thật
private:
    std::string cpu;      // chuỗi rỗng nghĩa là "chưa set" — build() phải kiểm tra bắt buộc
    int ram = 8;            // giá trị mặc định nếu người dùng không gọi setRam()
    bool ssd = false;       // giá trị mặc định nếu người dùng không gọi setSsd()

public:
    ComputerBuilder& setCpu(const std::string& cpuIn) { // mỗi bước trả về "*this" để có thể gọi tiếp (giống fluent interface bài 18), nhưng KHÔNG sửa Computer nào — vì Computer chưa tồn tại
        if (cpuIn.empty()) throw std::invalid_argument("CPU khong duoc rong"); // validate ở biên
        cpu = cpuIn;
        return *this;
    }

    ComputerBuilder& setRam(int ramIn) {
        if (ramIn <= 0) throw std::invalid_argument("RAM phai duong"); // validate ở biên
        ram = ramIn;
        return *this;
    }

    ComputerBuilder& setSsd(bool ssdIn) {
        ssd = ssdIn;
        return *this;
    }

    Computer build() const { // chốt lại — tạo MỘT Computer bất biến, đây là lần DUY NHẤT dữ liệu được "đóng băng"
        if (cpu.empty()) throw std::logic_error("Phai setCpu(...) truoc khi build()"); // validate: trường bắt buộc chưa có
        return Computer(cpu, ram, ssd);
    }
};

// ---- Self-check ----
static void check(bool ok, const std::string& msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
    if (!ok) { std::cerr << "FAIL: " << msg << "\n"; std::exit(1); } // in chỗ sai rồi dừng ngay
}

int main() { // điểm bắt đầu chạy chương trình sau khi biên dịch
    Computer full = ComputerBuilder() // dựng qua nhiều bước, thứ tự bất kỳ
                         .setCpu("Intel i7")
                         .setRam(16)
                         .setSsd(true)
                         .build();
    check(full.getCpu() == "Intel i7", "cpu phai dung gia tri da set");
    check(full.getRam() == 16, "ram phai dung gia tri da set");
    check(full.hasSsd(), "hasSsd phai dung gia tri da set");

    Computer defaults = ComputerBuilder().setCpu("AMD Ryzen").build(); // chỉ set cpu — ram và hasSsd dùng giá trị mặc định
    check(defaults.getRam() == 8, "khong setRam() thi phai dung mac dinh 8");
    check(!defaults.hasSsd(), "khong setSsd() thi phai dung mac dinh false");

    bool blockedNoCpu = false; // cờ đánh dấu: build() thiếu cpu bắt buộc có bị chặn không
    try { ComputerBuilder().setRam(32).build(); } catch (const std::logic_error&) { blockedNoCpu = true; }
    check(blockedNoCpu, "build() khong co setCpu(...) truoc do phai bi chan");

    bool blockedBadRam = false; // cờ đánh dấu: RAM không dương có bị chặn không
    try { ComputerBuilder().setRam(0); } catch (const std::invalid_argument&) { blockedBadRam = true; }
    check(blockedBadRam, "setRam(0) phai bi chan");

    std::cout << "OK\n"; // in "OK" nếu mọi check ở trên đều đúng
    return 0; // báo chương trình kết thúc thành công
}
