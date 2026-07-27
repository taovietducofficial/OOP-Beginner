/*
 * Ngôn ngữ: Java
 * Công dụng: Customer/Address minh họa NULL OBJECT PATTERN — thay vì biểu
 * diễn "khách chưa có địa chỉ" bằng null rồi rải if (address == null) khắp
 * nơi, ta tạo một Address ĐẶC BIỆT (UNKNOWN) đại diện cho sự vắng mặt đó.
 * UNKNOWN vẫn là một Address thật — vẫn gọi được getDisplayText() bình
 * thường, tự nó biết trả lời "chưa có địa chỉ" thay vì bắt nơi gọi phải
 * kiểm tra null trước mỗi lần dùng.
 * Tại sao cần học: bài 13 (Temperature) dùng static factory để tạo object
 * đại diện cho một GIÁ TRỊ CÓ THẬT. Bài này dùng đúng kỹ thuật đó nhưng cho
 * mục đích ngược lại — tạo object đại diện cho SỰ VẮNG MẶT của giá trị.
 */
class Address { // đại diện một địa chỉ giao hàng — hoặc "chưa có địa chỉ nào"
    public static final Address UNKNOWN = new Address("", "", true); // hằng số dùng chung — MỘT object duy nhất đại diện "chưa có địa chỉ"

    private final String street; // tên đường — rỗng nếu là UNKNOWN
    private final String city;   // thành phố — rỗng nếu là UNKNOWN
    private final boolean unknown; // cờ đánh dấu đây có phải Address đặc biệt (UNKNOWN) hay không

    private Address(String street, String city, boolean unknown) { // constructor riêng tư — chỉ dùng nội bộ (bởi UNKNOWN và of())
        this.street = street;
        this.city = city;
        this.unknown = unknown;
    }

    public static Address of(String street, String city) { // static factory — tạo địa chỉ CỤ THỂ, có thật
        if (street == null || street.isEmpty()) throw new IllegalArgumentException("Tên đường không được rỗng"); // validate ở biên
        if (city == null || city.isEmpty()) throw new IllegalArgumentException("Thành phố không được rỗng"); // validate ở biên
        return new Address(street, city, false); // false: không phải UNKNOWN
    }

    public boolean isUnknown() { // kiểm tra: đây có phải Address "chưa có gì" hay không
        return unknown;
    }

    public String getDisplayText() { // TỰ BIẾT hiển thị đúng cách — nơi gọi không cần kiểm tra null/unknown trước
        if (unknown) return "Chưa có địa chỉ giao hàng"; // hành vi an toàn khi không có dữ liệu thật
        return street + ", " + city; // hành vi bình thường khi có dữ liệu thật
    }
}

public class Customer { // khai báo class — khuôn mẫu để tạo ra các object Customer

    private final String name;    // tên khách hàng — riêng cho từng object
    private final Address address; // KHÔNG BAO GIỜ null — luôn là Address.UNKNOWN hoặc một Address cụ thể

    public Customer(String name) { // constructor — khách CHƯA có địa chỉ, tự gán Address.UNKNOWN thay vì null
        this(name, Address.UNKNOWN); // ủy quyền sang constructor đầy đủ (giống this(...) ở bài 07)
    }

    public Customer(String name, Address address) { // constructor — khách có địa chỉ cụ thể ngay từ đầu
        if (name == null || name.isEmpty()) throw new IllegalArgumentException("Tên khách hàng không được rỗng"); // validate ở biên
        this.name = name;
        this.address = address; // luôn có giá trị hợp lệ — không cần kiểm tra null ở đây hay bất kỳ đâu khác
    }

    public boolean hasAddress() { // có địa chỉ THẬT hay không — hỏi thẳng Address thay vì so sánh với null
        return !address.isUnknown();
    }

    public String getShippingLabel() { // nhãn giao hàng — KHÔNG cần if (address == null): address.getDisplayText() tự lo phần đó
        return name + ": " + address.getDisplayText();
    }

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình khi gõ "java Customer"
        Customer guest = new Customer("An"); // chưa cung cấp địa chỉ — tự động là Address.UNKNOWN, không phải null
        check(!guest.hasAddress(), "khách chưa cung cấp địa chỉ thì hasAddress() phải là false");
        check(guest.getShippingLabel().equals("An: Chưa có địa chỉ giao hàng"), "nhãn giao hàng khi chưa có địa chỉ phải đúng thông báo mặc định");

        Address home = Address.of("123 Lê Lợi", "Đà Nẵng"); // địa chỉ cụ thể, có thật
        Customer binh = new Customer("Binh", home);
        check(binh.hasAddress(), "khách có địa chỉ cụ thể thì hasAddress() phải là true");
        check(binh.getShippingLabel().equals("Binh: 123 Lê Lợi, Đà Nẵng"), "nhãn giao hàng khi có địa chỉ phải in đúng street, city");

        check(Address.UNKNOWN.isUnknown(), "Address.UNKNOWN phải tự nhận là unknown");
        check(!home.isUnknown(), "Address cụ thể không được coi là unknown");

        boolean blockedStreet = false; // cờ đánh dấu: đường rỗng có bị chặn không
        try { Address.of("", "Hà Nội"); } catch (IllegalArgumentException e) { blockedStreet = true; }
        check(blockedStreet, "tên đường rỗng phải bị chặn khi tạo Address cụ thể");

        boolean blockedName = false; // cờ đánh dấu: tên khách hàng rỗng có bị chặn không
        try { new Customer(""); } catch (IllegalArgumentException e) { blockedName = true; }
        check(blockedName, "tên khách hàng rỗng phải bị chặn");

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng
    }
}
