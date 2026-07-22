/*
 * Ngôn ngữ: Java
 *
 * Công dụng: Classroom minh họa một class QUẢN LÝ TẬP HỢP nhiều object khác
 * cùng loại (List<Student>) — thêm phần tử, và tính toán tổng hợp
 * (average, top) bằng cách duyệt qua cả tập hợp.
 *
 * Tại sao cần học: dữ liệu thật hiếm khi chỉ có 1 object đơn lẻ — một lớp có
 * nhiều học sinh, một đơn hàng có nhiều sản phẩm, một giỏ hàng có nhiều món.
 * Biết cách một class "chứa nhiều object con" và tổng hợp dữ liệu từ chúng
 * là kỹ năng nền cho hầu hết hệ thống thực tế.
 */
import java.util.ArrayList; // thư viện chuẩn: danh sách động, thêm phần tử không cần khai báo trước kích thước
import java.util.List;      // thư viện chuẩn: kiểu interface cho danh sách

class Student { // class phụ trợ — mỗi học sinh có tên và điểm
    private final String name;  // tên học sinh — riêng cho từng object, không đổi sau khi tạo
    private final double score; // điểm số — riêng cho từng object, không đổi sau khi tạo

    Student(String name, double score) { // constructor — chạy khi tạo một học sinh
        if (score < 0 || score > 10) throw new IllegalArgumentException("Điểm phải trong khoảng 0-10"); // validate ở biên: điểm phải hợp lệ
        this.name = name;   // gán tên
        this.score = score; // gán điểm
    }

    String getName() { // getter — xem tên học sinh
        return name; // trả về tên
    }

    double getScore() { // getter — xem điểm học sinh
        return score; // trả về điểm
    }
}

public class Classroom { // khai báo class — khuôn mẫu để tạo ra các object Classroom

    private final String name;              // tên lớp — riêng cho từng object, không đổi sau khi tạo
    private final List<Student> students = new ArrayList<>(); // TẬP HỢP: Classroom chứa nhiều Student, mỗi lớp giữ danh sách riêng của mình

    public Classroom(String name) { // constructor — chạy khi tạo một lớp học, ban đầu chưa có học sinh nào
        this.name = name; // gán tên lớp
    }

    public String getName() { // getter — xem tên lớp
        return name; // trả về tên lớp
    }

    public void addStudent(Student s) { // thêm một học sinh vào lớp
        students.add(s); // đưa vào cuối danh sách
    }

    public int size() { // đếm số học sinh hiện có trong lớp
        return students.size(); // kích thước danh sách
    }

    public double averageScore() { // tính điểm trung bình cả lớp — TỔNG HỢP dữ liệu từ nhiều object con
        if (students.isEmpty()) return 0; // lớp rỗng: quy ước trung bình là 0, tránh chia cho 0
        double sum = 0; // biến cộng dồn điểm
        for (Student s : students) sum += s.getScore(); // duyệt qua từng học sinh, cộng điểm của nó vào tổng
        return sum / students.size(); // trung bình = tổng điểm / số học sinh
    }

    public String topStudent() { // tìm tên học sinh điểm cao nhất — TỔNG HỢP dữ liệu bằng cách so sánh qua từng object con
        if (students.isEmpty()) throw new IllegalStateException("Lớp chưa có học sinh nào"); // không có gì để tìm nếu lớp rỗng
        Student top = students.get(0); // giả định học sinh đầu tiên đang dẫn đầu
        for (Student s : students) { // duyệt qua từng học sinh còn lại
            if (s.getScore() > top.getScore()) top = s; // học sinh nào điểm cao hơn thì thay vào vị trí dẫn đầu
        }
        return top.getName(); // trả về tên học sinh điểm cao nhất
    }

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình khi gõ "java Classroom"
        Classroom room = new Classroom("10A"); // tạo lớp 10A, ban đầu rỗng
        check(room.getName().equals("10A"), "tên lớp phải giữ đúng như lúc tạo"); // getter trả đúng dữ liệu đã gán
        check(room.size() == 0, "lớp mới tạo chưa có học sinh nào"); // chưa addStudent lần nào

        room.addStudent(new Student("An", 8.0));   // thêm học sinh An, điểm 8.0
        room.addStudent(new Student("Binh", 9.5));  // thêm học sinh Binh, điểm 9.5
        room.addStudent(new Student("Chi", 7.0));   // thêm học sinh Chi, điểm 7.0

        check(room.size() == 3, "lớp phải có 3 học sinh"); // đếm đúng số phần tử đã thêm
        check(Math.abs(room.averageScore() - 24.5 / 3) < 1e-9, "điểm trung bình tính sai"); // (8.0+9.5+7.0)/3, so sánh gần đúng vì số thực
        check(room.topStudent().equals("Binh"), "học sinh điểm cao nhất phải là Binh"); // 9.5 là điểm cao nhất

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng
    }
}
