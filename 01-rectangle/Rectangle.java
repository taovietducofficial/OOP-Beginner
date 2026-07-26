/*
 * Ngôn ngữ: Java
 * Công dụng: Rectangle gói dữ liệu (width, height) và hành vi (area, perimeter)
 * vào chung một class — bài đầu tiên minh họa Class & Object.
 * Tại sao cần học: đây là viên gạch nền của toàn bộ OOP. Mọi hệ thống thực tế
 * (đơn hàng, tài khoản, sản phẩm...) đều được mô hình hóa bằng class/object
 * như thế này. Không nắm chắc bước "gom dữ liệu + hành vi vào 1 class" thì
 * không thể hiểu các bài sau về đóng gói, kế thừa, đa hình.
 */
public class Rectangle { // khai báo class — khuôn mẫu để tạo ra các object Rectangle

    private final double width;  // thuộc tính: chiều rộng — riêng cho từng object, không đổi sau khi tạo
    private final double height; // thuộc tính: chiều cao — riêng cho từng object, không đổi sau khi tạo

    public Rectangle(double width, double height) { // constructor — chạy khi gọi "new Rectangle(...)" để khởi tạo object
        if (width <= 0 || height <= 0) throw new IllegalArgumentException("Cạnh phải > 0"); // validate ở biên: chặn dữ liệu sai ngay lúc tạo object
        this.width = width;   // gán tham số truyền vào cho thuộc tính của object (this = object đang được tạo)
        this.height = height; // tương tự, gán height truyền vào cho thuộc tính height
    }

    public double area() { // hàm tính diện tích — hành vi của object, dùng dữ liệu (width, height) của chính nó
        return width * height; // công thức diện tích hình chữ nhật = rộng * cao
    }

    public double perimeter() { // hàm tính chu vi — cũng là hành vi thao tác trên dữ liệu riêng của object
        return 2 * (width + height); // công thức chu vi = 2 * (rộng + cao)
    }

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu điều kiện "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai khi self-check thất bại
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình (entry point) khi gõ "java Rectangle"
        Rectangle r = new Rectangle(4, 5); // tạo object Rectangle với rộng=4, cao=5
        check(r.area() == 20, "diện tích 4x5 phải là 20");       // kiểm tra area() tính đúng: 4*5=20
        check(r.perimeter() == 18, "chu vi 4x5 phải là 18");     // kiểm tra perimeter() tính đúng: 2*(4+5)=18

        Rectangle square = new Rectangle(3, 3); // tạo thêm 1 object khác — hình vuông là trường hợp đặc biệt của hình chữ nhật (rộng = cao)
        check(square.area() == 9, "diện tích hình vuông cạnh 3 phải là 9"); // kiểm tra diện tích: 3*3=9

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng (không có check nào ném lỗi)
    }
}
