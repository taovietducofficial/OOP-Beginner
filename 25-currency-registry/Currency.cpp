/*
 * Ngôn ngữ: C++
 * Công dụng: Currency minh họa CACHED/INTERNED FACTORY — Currency::of(code)
 * tra một std::map nội bộ trước: nếu "code" đã từng được tạo, TRẢ LẠI THAM
 * CHIẾU tới object cũ thay vì tạo mới; nếu chưa, tạo một lần rồi lưu vào map
 * để lần sau dùng lại. Gọi of("USD") nhiều lần luôn trả về CÙNG MỘT object
 * (so địa chỉ bằng nhau), không phải hai bản sao.
 * Tại sao cần học: bài 13 (Temperature) dùng static factory nhưng mỗi lần
 * gọi vẫn tạo một object mới. Bài này thêm một lớp: factory còn NHỚ LẠI kết
 * quả trước đó theo khóa (code). Vì Currency là kiểu giá trị (bài 17/19),
 * of() phải trả về THAM CHIẾU ("Currency&"), không phải giá trị — trả theo
 * giá trị sẽ ÂM THẦM COPY và phá vỡ tính "dùng chung" mà bài này muốn dạy.
 * Ghi chú kỹ thuật: registry và supportedSymbols khai báo "static" NGAY
 * TRONG hàm (Construct On First Use idiom) thay vì static member thông
 * thường, để tránh "static initialization order fiasco" — thứ tự khởi tạo
 * các biến static ở nhiều file khác nhau không được C++ đảm bảo.
 */
#include <cstdlib>   // thư viện chuẩn: std::exit để dừng chương trình khi self-check thất bại
#include <iostream>  // thư viện chuẩn: std::cout/std::cerr để in ra màn hình
#include <map>       // thư viện chuẩn: std::map làm "sổ đăng ký"
#include <stdexcept> // thư viện chuẩn: std::invalid_argument để báo lỗi dữ liệu sai
#include <string>    // thư viện chuẩn: std::string

class Currency { // đại diện một loại tiền tệ — chỉ tạo được qua of(code), constructor riêng tư
private:
    std::string code;   // mã tiền tệ, ví dụ "USD"
    std::string symbol; // ký hiệu tương ứng, ví dụ "$"

    Currency(std::string code, std::string symbol) // constructor PRIVATE — không ai new Currency(...) trực tiếp, chỉ of() được gọi
        : code(std::move(code)), symbol(std::move(symbol)) {}

public:
    static Currency& of(const std::string& code) { // static factory CÓ CACHE, trả về THAM CHIẾU — trái tim của bài này
        static std::map<std::string, Currency> registry;                                  // "sổ đăng ký" dùng chung — lưu MỌI Currency đã từng tạo, theo khóa code
        static const std::map<std::string, std::string> supportedSymbols = {              // danh sách mã tiền tệ hợp lệ và ký hiệu tương ứng
            {"USD", "$"}, {"VND", "₫"}, {"EUR", "€"}};

        auto found = registry.find(code);
        if (found != registry.end()) return found->second; // đã từng tạo trước đó — trả THAM CHIẾU tới object cũ, KHÔNG tạo mới

        auto symbolIt = supportedSymbols.find(code);
        if (symbolIt == supportedSymbols.end()) throw std::invalid_argument("Ma tien te khong duoc ho tro: " + code); // validate ở biên

        auto inserted = registry.emplace(code, Currency(code, symbolIt->second)); // CHỈ tạo mới khi thật sự chưa có trong sổ đăng ký
        return inserted.first->second; // trả THAM CHIẾU tới object VỪA lưu trong map — lần sau of(cùng code) sẽ trả đúng object này
    }

    const std::string& getCode() const { return code; }     // getter — xem mã tiền tệ
    const std::string& getSymbol() const { return symbol; } // getter — xem ký hiệu
};

// ---- Self-check ----
static void check(bool ok, const std::string& msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
    if (!ok) { std::cerr << "FAIL: " << msg << "\n"; std::exit(1); } // in chỗ sai rồi dừng ngay
}

int main() { // điểm bắt đầu chạy chương trình sau khi biên dịch
    Currency& usd1 = Currency::of("USD");
    Currency& usd2 = Currency::of("USD"); // gọi lần thứ hai với CÙNG code
    check(&usd1 == &usd2, "goi of(\"USD\") hai lan phai tra ve CUNG MOT object (so dia chi), khong phai hai ban sao");
    check(usd1.getSymbol() == "$", "ky hieu USD phai la $");

    Currency& vnd = Currency::of("VND");
    check(&vnd != &usd1, "hai code khac nhau phai la hai object khac nhau");
    check(vnd.getSymbol() == "₫", "ky hieu VND phai dung");

    bool blocked = false; // cờ đánh dấu: mã tiền tệ không hỗ trợ có bị chặn không
    try { Currency::of("XYZ"); } catch (const std::invalid_argument&) { blocked = true; }
    check(blocked, "ma tien te khong duoc ho tro phai bi chan");

    std::cout << "OK\n"; // in "OK" nếu mọi check ở trên đều đúng
    return 0; // báo chương trình kết thúc thành công
}
