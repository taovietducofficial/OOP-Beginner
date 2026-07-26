/*
 * Ngôn ngữ: Java
 * Công dụng: Counter minh họa object có TRẠNG THÁI (state) thay đổi qua thời
 * gian — mỗi lần gọi increment()/decrement() làm dữ liệu bên trong object đổi,
 * và mỗi object Counter giữ trạng thái độc lập với object khác cùng class.
 * Tại sao cần học: đây là ý tưởng lõi của MỌI object có trạng thái trong thực
 * tế — giỏ hàng, phiên đăng nhập, kết nối mạng. Nếu không hiểu rõ mỗi object
 * có state riêng, độc lập, rất dễ viết bug chia sẻ dữ liệu ngoài ý muốn khi
 * hệ thống lớn lên (đặc biệt trong môi trường nhiều luồng/nhiều người dùng).
 */
public class Counter { // khai báo class — khuôn mẫu để tạo ra các object Counter

    private int value; // thuộc tính: giá trị đếm hiện tại — đây là "trạng thái" thay đổi theo thời gian

    public Counter() { // constructor không tham số — chạy khi gọi "new Counter()"
        this.value = 0; // giá trị khởi tạo luôn bắt đầu từ 0
    }

    public void increment() { // hàm tăng — thay đổi trạng thái của object
        value++; // cộng thêm 1 vào giá trị hiện tại
    }

    public void decrement() { // hàm giảm — thay đổi trạng thái, có kiểm tra ràng buộc
        if (value == 0) throw new IllegalStateException("Không thể giảm dưới 0"); // validate: chặn giảm xuống âm
        value--; // trừ 1 khỏi giá trị hiện tại
    }

    public void reset() { // hàm đưa trạng thái về ban đầu
        value = 0; // gán lại giá trị về 0
    }

    public int getValue() { // getter — cho phép đọc trạng thái hiện tại từ bên ngoài, không cho sửa trực tiếp
        return value; // trả về giá trị hiện tại của object
    }

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình khi gõ "java Counter"
        Counter c = new Counter(); // tạo object Counter, value bắt đầu = 0
        check(c.getValue() == 0, "khởi tạo phải là 0"); // kiểm tra giá trị khởi tạo

        c.increment(); // tăng lần 1 -> value = 1
        c.increment(); // tăng lần 2 -> value = 2
        c.increment(); // tăng lần 3 -> value = 3
        check(c.getValue() == 3, "sau 3 lần tăng phải là 3"); // kiểm tra sau 3 lần tăng

        c.decrement(); // giảm 1 lần -> value = 2
        check(c.getValue() == 2, "sau 1 lần giảm phải là 2"); // kiểm tra sau khi giảm

        c.reset(); // đưa value về 0
        check(c.getValue() == 0, "sau reset phải là 0"); // kiểm tra sau reset

        // Object khác của cùng class có trạng thái độc lập.
        Counter other = new Counter(); // tạo object thứ hai, hoàn toàn tách biệt với "c"
        other.increment(); // tăng riêng trên object "other" -> other.value = 1
        check(other.getValue() == 1 && c.getValue() == 0, "hai object phải độc lập nhau"); // "c" không bị ảnh hưởng bởi "other"

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng
    }
}
