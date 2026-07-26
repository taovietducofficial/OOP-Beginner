/*
 * Ngôn ngữ: Java
 * Công dụng: StudentRecord có nhiều thuộc tính (name, age, score) và cho thấy
 * một phương thức (summary) gọi lại phương thức khác (isPassed) trên cùng object.
 * Tại sao cần học: dữ liệu thực tế (user, order, product...) luôn có nhiều field
 * liên quan với nhau, và quy tắc nghiệp vụ (vd. "điểm >= 5 là đậu") phải nằm
 * TRONG class, dùng lại qua gọi hàm nội bộ — thay vì lặp lại điều kiện đó ở
 * nhiều nơi trong code. Đây là thói quen giúp code dễ sửa, ít bug khi quy tắc đổi.
 */
public class StudentRecord { // khai báo class — khuôn mẫu để tạo ra các object StudentRecord

    private final String name;  // thuộc tính: tên học sinh — riêng cho từng object
    private final int age;      // thuộc tính: tuổi — riêng cho từng object
    private final double score; // thuộc tính: điểm số — riêng cho từng object

    public StudentRecord(String name, int age, double score) { // constructor — chạy khi gọi "new StudentRecord(...)"
        if (name == null || name.isEmpty()) throw new IllegalArgumentException("Tên không được rỗng"); // validate: tên không được thiếu
        if (age <= 0) throw new IllegalArgumentException("Tuổi phải > 0"); // validate: tuổi phải hợp lệ
        if (score < 0 || score > 10) throw new IllegalArgumentException("Điểm phải trong [0,10]"); // validate: điểm phải nằm trong thang điểm
        this.name = name;   // gán tham số truyền vào cho thuộc tính name
        this.age = age;     // gán tham số truyền vào cho thuộc tính age
        this.score = score; // gán tham số truyền vào cho thuộc tính score
    }

    public boolean isPassed() { // hàm kiểm tra đậu/rớt — hành vi dựa trên dữ liệu score của chính object
        return score >= 5; // quy tắc nghiệp vụ: đậu nếu điểm >= 5
    }

    public String summary() { // hàm tạo chuỗi mô tả tổng hợp — gọi lại isPassed() thay vì viết lại điều kiện
        return name + " (" + age + " tuổi) - điểm " + score + " - " + (isPassed() ? "Đậu" : "Rớt"); // ghép các thuộc tính + kết quả isPassed() thành 1 chuỗi
    }

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình khi gõ "java StudentRecord"
        StudentRecord an = new StudentRecord("An", 20, 7.5); // tạo object An, điểm 7.5 (đậu)
        check(an.isPassed(), "điểm 7.5 phải đậu"); // kiểm tra isPassed() trả về true
        check(an.summary().equals("An (20 tuổi) - điểm 7.5 - Đậu"), "summary sai"); // kiểm tra summary() ghép chuỗi đúng

        StudentRecord binh = new StudentRecord("Binh", 21, 3.0); // tạo object Binh, điểm 3.0 (rớt)
        check(!binh.isPassed(), "điểm 3.0 phải rớt"); // kiểm tra isPassed() trả về false

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng
    }
}
