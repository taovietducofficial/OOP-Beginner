/*
 * Ngôn ngữ: Java
 * Công dụng: Person minh họa một object nhận OBJECT KHÁC làm tham số
 * (greet(Person other)) và gọi phương thức trên object đó (other.getName()).
 * Tại sao cần học: đây là cách các object THỰC SỰ cộng tác với nhau trong hệ
 * thống thực tế — vd. order.applyDiscount(coupon), account.transferTo(otherAccount).
 * Nắm được cách 1 object thao tác dựa trên dữ liệu của object khác là bước đệm
 * bắt buộc trước khi học kế thừa và đa hình ở các tầng tiếp theo.
 */
public class Person { // khai báo class — khuôn mẫu để tạo ra các object Person

    private final String name; // thuộc tính: tên — riêng cho từng object

    public Person(String name) { // constructor — chạy khi gọi "new Person(...)"
        if (name == null || name.isEmpty()) throw new IllegalArgumentException("Tên không được rỗng"); // validate: tên không được thiếu
        this.name = name; // gán tham số truyền vào cho thuộc tính name
    }

    public String getName() { // getter — cho object khác đọc được tên, không cho sửa trực tiếp
        return name; // trả về tên của object hiện tại
    }

    // Nhận một Person khác làm tham số — hai object tương tác với nhau.
    public String greet(Person other) { // hàm nhận object Person khác làm tham số
        return name + " chào " + other.getName(); // dùng tên của chính mình (name) + gọi getName() trên object "other"
    }

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình khi gõ "java Person"
        Person an = new Person("An");     // tạo object thứ nhất
        Person binh = new Person("Binh"); // tạo object thứ hai

        check(an.greet(binh).equals("An chào Binh"), "An chào Binh sai");   // "an" chào "binh" — truyền binh làm tham số
        check(binh.greet(an).equals("Binh chào An"), "Binh chào An sai");   // ngược lại — truyền an làm tham số

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng
    }
}
