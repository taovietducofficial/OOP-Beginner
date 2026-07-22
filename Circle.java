/*
 * Ngôn ngữ: Java
 *
 * Công dụng: Circle làm quen với `static final` (hằng số PI thuộc về CLASS,
 * dùng chung cho mọi object) khác với field thường như `radius` (thuộc về
 * TỪNG object, mỗi object một giá trị riêng).
 *
 * Tại sao cần học: nhầm lẫn giữa static và instance field là lỗi rất phổ biến
 * của người mới, gây ra bug khó tìm (dữ liệu bị "dùng chung" ngoài ý muốn giữa
 * các object). Hiểu đúng khái niệm này là điều kiện bắt buộc trước khi học
 * static method, singleton, hay biến đếm toàn cục.
 */
public class Circle { // khai báo class — khuôn mẫu để tạo ra các object Circle

    private static final double PI = 3.14159; // hằng số CLASS: chỉ có 1 bản duy nhất, mọi object Circle dùng chung

    private final double radius; // thuộc tính INSTANCE: mỗi object Circle có bán kính riêng của mình

    public Circle(double radius) { // constructor — chạy khi gọi "new Circle(...)"
        if (radius <= 0) throw new IllegalArgumentException("Bán kính phải > 0"); // validate ở biên: chặn bán kính không hợp lệ
        this.radius = radius; // gán tham số truyền vào cho thuộc tính radius của object
    }

    public double area() { // hàm tính diện tích — dùng hằng số chung PI + dữ liệu riêng radius
        return PI * radius * radius; // công thức diện tích hình tròn = PI * r^2
    }

    public double circumference() { // hàm tính chu vi
        return 2 * PI * radius; // công thức chu vi hình tròn = 2 * PI * r
    }

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình khi gõ "java Circle"
        Circle c = new Circle(2); // tạo object Circle với bán kính = 2
        check(Math.abs(c.area() - 12.56636) < 1e-5, "diện tích bán kính 2 sai"); // so sánh gần đúng vì số thực có sai số dấu phẩy động
        check(Math.abs(c.circumference() - 12.56636) < 1e-5, "chu vi bán kính 2 sai"); // tương tự, kiểm tra chu vi gần đúng

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng
    }
}
