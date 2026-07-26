/*
 * Ngôn ngữ: Java
 * Công dụng: Point minh họa NHIỀU CONSTRUCTOR cùng tên khác tham số
 * (overloading) và kỹ thuật this(...) — constructor rỗng ủy quyền cho
 * constructor đầy đủ thay vì chép lại code khởi tạo.
 * Tại sao cần học: overloading constructor xuất hiện khắp thư viện chuẩn
 * (new ArrayList<>() / new ArrayList<>(100)). Kỹ thuật this(...) dồn logic
 * khởi tạo về MỘT chỗ — chép code ra nhiều constructor là nguồn bug khi
 * hai bản bị chỉnh lệch nhau.
 */
public class Point { // khai báo class — khuôn mẫu để tạo ra các object Point

    private final double x; // hoành độ — riêng cho từng object
    private final double y; // tung độ — riêng cho từng object

    public Point(double x, double y) { // constructor "chính" — nhận đầy đủ tọa độ
        this.x = x; // gán hoành độ truyền vào cho object
        this.y = y; // gán tung độ truyền vào cho object
    }

    public Point() { // constructor rỗng — tạo điểm gốc tọa độ (0, 0)
        this(0, 0); // ủy quyền cho constructor chính — KHÔNG chép lại code khởi tạo
    }

    public double distanceTo(Point other) { // khoảng cách Euclid tới điểm khác — nhận object Point khác làm tham số
        double dx = x - other.x; // chênh lệch hoành độ giữa hai điểm
        double dy = y - other.y; // chênh lệch tung độ giữa hai điểm
        return Math.sqrt(dx * dx + dy * dy); // công thức Pythagoras: căn(dx² + dy²) — dùng Math.sqrt của thư viện chuẩn
    }

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình khi gõ "java Point"
        Point origin = new Point();      // dùng constructor rỗng — điểm gốc (0, 0)
        Point p = new Point(3, 4);       // dùng constructor đầy đủ — điểm (3, 4)

        check(Math.abs(origin.distanceTo(p) - 5) < 1e-9, "khoảng cách (0,0)-(3,4) phải là 5"); // tam giác 3-4-5 kinh điển; so sánh gần đúng vì số thực
        check(Math.abs(p.distanceTo(origin) - 5) < 1e-9, "khoảng cách phải đối xứng");         // đo xuôi hay ngược đều cùng kết quả
        check(p.distanceTo(p) == 0, "khoảng cách tới chính mình phải là 0");                    // điểm cách chính nó 0

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng
    }
}
