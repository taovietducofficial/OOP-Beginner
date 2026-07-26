/*
 * Ngôn ngữ: Java
 * Công dụng: Employee minh họa THAM CHIẾU DÙNG CHUNG (shared reference) —
 * Department được tạo BÊN NGOÀI rồi truyền vào constructor của Employee,
 * KHÔNG bị sao chép. Nhiều Employee có thể cùng giữ tham chiếu tới đúng MỘT
 * Department; đổi Department qua một Employee thì mọi Employee khác cùng
 * phòng ban đều "thấy" thay đổi đó ngay lập tức.
 * Tại sao cần học: bài 11 (Car/Engine) là composition — Engine bị Car tạo ra
 * và SỞ HỮU riêng, không ai khác đụng tới. Bài 17 (Playlist) chủ động CẮT
 * ĐỨT tham chiếu (defensive copy) để bảo vệ dữ liệu nội bộ khỏi bị sửa từ
 * ngoài. Bài này làm điều NGƯỢC LẠI có chủ đích: GIỮ NGUYÊN tham chiếu, vì
 * đó chính là mục đích — nhiều object cùng phản ánh một nguồn dữ liệu dùng
 * chung (Department, Team, cấu hình hệ thống...).
 */
class Department { // class phụ trợ — phòng ban, được tạo và sống ĐỘC LẬP với bất kỳ Employee nào
    private String name; // tên phòng ban — CÓ THỂ đổi qua rename(), không như các thuộc tính final đã gặp ở nhiều bài trước

    public Department(String name) { // constructor — chạy khi tạo một phòng ban
        if (name == null || name.isEmpty()) throw new IllegalArgumentException("Tên phòng ban không được rỗng"); // validate ở biên
        this.name = name; // gán tên ban đầu
    }

    public String getName() { // getter — xem tên phòng ban hiện tại
        return name;
    }

    public void rename(String newName) { // đổi tên phòng ban — mọi Employee đang giữ tham chiếu tới object này đều thấy thay đổi
        if (newName == null || newName.isEmpty()) throw new IllegalArgumentException("Tên phòng ban không được rỗng"); // validate ở biên
        name = newName; // cập nhật tại chỗ — chính là lý do mọi tham chiếu dùng chung đều "thấy" thay đổi
    }
}

public class Employee { // khai báo class — khuôn mẫu để tạo ra các object Employee

    private final String name;             // tên nhân viên — riêng cho từng object, không đổi sau khi tạo
    private final Department department;   // THAM CHIẾU DÙNG CHUNG — Employee không tạo, không copy Department; chỉ giữ tham chiếu tới object được truyền vào

    public Employee(String name, Department department) { // constructor — nhận Department đã tồn tại sẵn từ BÊN NGOÀI
        if (name == null || name.isEmpty()) throw new IllegalArgumentException("Tên nhân viên không được rỗng"); // validate ở biên
        this.name = name;             // gán tên
        this.department = department; // gán THẲNG tham chiếu — không "new Department(...)" (khác composition ở bài 11), không copy dữ liệu (khác defensive copy ở bài 17)
    }

    public String getName() { // getter — xem tên nhân viên
        return name;
    }

    public Department getDepartment() { // getter — trả THẲNG tham chiếu Department dùng chung (cố ý, không defensive copy — xem README)
        return department;
    }

    public String getDepartmentName() { // ủy quyền: hỏi thẳng Department hiện tại tên là gì
        return department.getName();
    }

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình khi gõ "java Employee"
        Department eng = new Department("Engineering"); // tạo phòng ban BÊN NGOÀI, độc lập với bất kỳ Employee nào
        Employee e1 = new Employee("An", eng);   // An thuộc phòng eng
        Employee e2 = new Employee("Binh", eng); // Binh CŨNG thuộc CHÍNH phòng eng — cùng một object Department

        check(e1.getDepartment() == e2.getDepartment(), "hai nhân viên cùng phòng phải giữ CHUNG một object Department (reference equality)");
        check(e1.getDepartmentName().equals("Engineering"), "tên phòng ban đọc qua Employee phải đúng ban đầu");

        eng.rename("Platform Engineering"); // đổi tên phòng ban CHỈ MỘT LẦN, qua chính object Department
        check(e1.getDepartmentName().equals("Platform Engineering"), "đổi tên Department phải phản ánh qua e1 (cùng tham chiếu)");
        check(e2.getDepartmentName().equals("Platform Engineering"), "đổi tên Department phải phản ánh qua e2 (cùng tham chiếu)");

        Department hr = new Department("HR"); // phòng ban KHÁC — object hoàn toàn riêng biệt
        Employee e3 = new Employee("Chi", hr); // Chi thuộc phòng hr, không liên quan gì tới eng
        eng.rename("Something Else"); // đổi tiếp phòng eng
        check(e3.getDepartmentName().equals("HR"), "đổi Department eng không được ảnh hưởng tới Employee thuộc Department khác");

        boolean blocked = false; // cờ đánh dấu: tên nhân viên rỗng có bị chặn không
        try { new Employee("", eng); } catch (IllegalArgumentException e) { blocked = true; }
        check(blocked, "tên nhân viên rỗng phải bị chặn");

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng
    }
}
