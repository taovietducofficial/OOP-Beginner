/*
 * Ngôn ngữ: C++
 * Công dụng: Customer/Address minh họa NULL OBJECT PATTERN — thay vì biểu
 * diễn "khách chưa có địa chỉ" bằng một con trỏ null rồi kiểm tra khắp nơi,
 * ta tạo một Address ĐẶC BIỆT (UNKNOWN) đại diện cho sự vắng mặt đó. UNKNOWN
 * vẫn là một Address thật — vẫn gọi được getDisplayText() bình thường, tự nó
 * biết trả lời "chưa có địa chỉ" thay vì bắt nơi gọi phải kiểm tra null.
 * Tại sao cần học: bài 13 (Temperature) dùng static factory để tạo object
 * đại diện cho một GIÁ TRỊ CÓ THẬT. Bài này dùng đúng kỹ thuật đó nhưng cho
 * mục đích ngược lại — tạo object đại diện cho SỰ VẮNG MẶT của giá trị, và vì
 * Address là kiểu GIÁ TRỊ (không phải con trỏ), không hề có nguy cơ null.
 */
#include <cstdlib>   // thư viện chuẩn: std::exit để dừng chương trình khi self-check thất bại
#include <iostream>  // thư viện chuẩn: std::cout/std::cerr để in ra màn hình
#include <stdexcept> // thư viện chuẩn: std::invalid_argument để báo lỗi dữ liệu sai
#include <string>    // thư viện chuẩn: std::string cho tên/địa chỉ

class Address { // đại diện một địa chỉ giao hàng — hoặc "chưa có địa chỉ nào"
private:
    std::string street; // tên đường — rỗng nếu là UNKNOWN
    std::string city;   // thành phố — rỗng nếu là UNKNOWN
    bool unknown;        // cờ đánh dấu đây có phải Address đặc biệt (UNKNOWN) hay không

    Address(std::string street, std::string city, bool unknown) // constructor riêng tư — chỉ dùng nội bộ (bởi unknown() và of())
        : street(std::move(street)), city(std::move(city)), unknown(unknown) {}

public:
    static Address unknown_address() { // "hằng số" — tạo Address đặc biệt đại diện "chưa có địa chỉ" (C++ không có static field khởi tạo phức tạp gọn như Java, nên dùng hàm)
        return Address("", "", true);
    }

    static Address of(std::string street, std::string city) { // static factory — tạo địa chỉ CỤ THỂ, có thật
        if (street.empty()) throw std::invalid_argument("Tên đường không được rỗng"); // validate ở biên
        if (city.empty()) throw std::invalid_argument("Thành phố không được rỗng"); // validate ở biên
        return Address(std::move(street), std::move(city), false); // false: không phải unknown
    }

    bool isUnknown() const { // kiểm tra: đây có phải Address "chưa có gì" hay không
        return unknown;
    }

    std::string getDisplayText() const { // TỰ BIẾT hiển thị đúng cách — nơi gọi không cần kiểm tra trước
        if (unknown) return "Chua co dia chi giao hang"; // hành vi an toàn khi không có dữ liệu thật
        return street + ", " + city; // hành vi bình thường khi có dữ liệu thật
    }
};

class Customer { // khai báo class — khuôn mẫu để tạo ra các object Customer
private:
    std::string name;  // tên khách hàng — riêng cho từng object
    Address address;    // KHÔNG BAO GIỜ là con trỏ null — luôn là Address::unknown_address() hoặc một Address cụ thể (kiểu giá trị)

public:
    explicit Customer(std::string name) // constructor — khách CHƯA có địa chỉ, tự gán Address unknown thay vì null
        : Customer(std::move(name), Address::unknown_address()) {} // ủy quyền sang constructor đầy đủ (giống this(...) ở bài 07)

    Customer(std::string name, Address address) // constructor — khách có địa chỉ cụ thể ngay từ đầu
        : address(std::move(address)) {
        if (name.empty()) throw std::invalid_argument("Ten khach hang khong duoc rong"); // validate ở biên
        this->name = std::move(name);
    }

    bool hasAddress() const { // có địa chỉ THẬT hay không — hỏi thẳng Address thay vì so sánh với null
        return !address.isUnknown();
    }

    std::string getShippingLabel() const { // nhãn giao hàng — KHÔNG cần kiểm tra null: address.getDisplayText() tự lo phần đó
        return name + ": " + address.getDisplayText();
    }
};

// ---- Self-check ----
static void check(bool ok, const std::string& msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
    if (!ok) { std::cerr << "FAIL: " << msg << "\n"; std::exit(1); } // in chỗ sai rồi dừng ngay
}

int main() { // điểm bắt đầu chạy chương trình sau khi biên dịch
    Customer guest("An"); // chưa cung cấp địa chỉ — tự động là Address unknown, không phải con trỏ null
    check(!guest.hasAddress(), "khach chua cung cap dia chi thi hasAddress() phai la false");
    check(guest.getShippingLabel() == "An: Chua co dia chi giao hang", "nhan giao hang khi chua co dia chi phai dung thong bao mac dinh");

    Address home = Address::of("123 Le Loi", "Da Nang"); // địa chỉ cụ thể, có thật
    Customer binh("Binh", home);
    check(binh.hasAddress(), "khach co dia chi cu the thi hasAddress() phai la true");
    check(binh.getShippingLabel() == "Binh: 123 Le Loi, Da Nang", "nhan giao hang khi co dia chi phai in dung street, city");

    check(Address::unknown_address().isUnknown(), "Address unknown phai tu nhan la unknown");
    check(!home.isUnknown(), "Address cu the khong duoc coi la unknown");

    bool blockedStreet = false; // cờ đánh dấu: đường rỗng có bị chặn không
    try { Address::of("", "Ha Noi"); } catch (const std::invalid_argument&) { blockedStreet = true; }
    check(blockedStreet, "ten duong rong phai bi chan khi tao Address cu the");

    bool blockedName = false; // cờ đánh dấu: tên khách hàng rỗng có bị chặn không
    try { Customer bad(""); } catch (const std::invalid_argument&) { blockedName = true; }
    check(blockedName, "ten khach hang rong phai bi chan");

    std::cout << "OK\n"; // in "OK" nếu mọi check ở trên đều đúng
    return 0; // báo chương trình kết thúc thành công
}
