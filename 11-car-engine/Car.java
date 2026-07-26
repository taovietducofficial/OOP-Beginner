/*
 * Ngôn ngữ: Java
 * Công dụng: Car minh họa KẾT HỢP (composition) — Car tự tạo ra Engine của
 * riêng mình ngay trong constructor, Engine sống chết theo Car (không object
 * nào khác nắm giữ Engine này). Car "ủy quyền" (delegate) các phương thức
 * start()/isRunning() cho engine bên trong thay vì tự làm hết.
 * Tại sao cần học: bài 05 cho object khác làm THAM SỐ (aggregation — Person
 * không sở hữu Person kia, hai object độc lập). Bài này khác: Car SỞ HỮU
 * Engine — quan hệ "toàn thể - bộ phận" (whole-part). Đây là cách OOP mô
 * hình hóa vật thật gồm nhiều bộ phận: Car có Engine, Order có Address,
 * Computer có CPU — object lớn được ghép từ object nhỏ hơn.
 */
class Engine { // package-private: chỉ Car trong cùng file này cần biết tới Engine — thế giới bên ngoài chỉ làm việc với Car
    private final int horsepower; // mã lực — riêng cho từng động cơ, không đổi sau khi tạo
    private boolean running = false; // trạng thái chạy/tắt — riêng cho từng động cơ, thay đổi được qua start()

    Engine(int horsepower) { // constructor — không public vì chỉ Car (cùng file) được tạo Engine
        if (horsepower <= 0) throw new IllegalArgumentException("Mã lực phải > 0"); // validate ở biên: động cơ không thể có mã lực âm hoặc 0
        this.horsepower = horsepower; // gán mã lực cho object Engine
    }

    void start() { // khởi động động cơ
        running = true; // chuyển trạng thái sang đang chạy
    }

    boolean isRunning() { // kiểm tra động cơ có đang chạy không
        return running; // trả về trạng thái hiện tại
    }

    int getHorsepower() { // getter — xem mã lực động cơ
        return horsepower; // trả về mã lực
    }
}

public class Car { // khai báo class — khuôn mẫu để tạo ra các object Car

    private final String model; // tên dòng xe — riêng cho từng object, không đổi sau khi tạo
    private final Engine engine; // KẾT HỢP: Car giữ một Engine của riêng mình, tạo ra ngay trong constructor bên dưới

    public Car(String model, int horsepower) { // constructor — nhận thông tin xe VÀ thông tin động cơ để tự tạo Engine bên trong
        if (model == null || model.isEmpty()) throw new IllegalArgumentException("Tên xe không được rỗng"); // validate ở biên: tên xe bắt buộc phải có
        this.model = model; // gán tên dòng xe
        this.engine = new Engine(horsepower); // Car TỰ TẠO Engine của mình — đây chính là composition, không ai truyền Engine từ bên ngoài vào
    }

    public void start() { // khởi động xe — Car không tự biết cách nổ máy, nó NHỜ Engine của mình làm việc đó
        engine.start(); // ủy quyền (delegate) hành vi cho object bên trong
    }

    public boolean isRunning() { // kiểm tra xe có đang chạy không
        return engine.isRunning(); // ủy quyền: hỏi thẳng Engine bên trong, Car không tự giữ trạng thái này
    }

    public String describe() { // mô tả xe — kết hợp dữ liệu của Car và dữ liệu của Engine bên trong nó
        return model + " (" + engine.getHorsepower() + "hp)"; // ví dụ: "Toyota Vios (120hp)"
    }

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình khi gõ "java Car"
        Car car = new Car("Toyota Vios", 120); // tạo xe — Engine(120) được tạo tự động bên trong constructor của Car
        check(!car.isRunning(), "xe chưa start thì chưa được chạy"); // trạng thái ban đầu: chưa nổ máy
        check(car.describe().equals("Toyota Vios (120hp)"), "describe phải ghép đúng tên xe và mã lực"); // dữ liệu Car + Engine ghép lại đúng

        car.start(); // khởi động xe — thực chất là gọi engine.start() bên trong
        check(car.isRunning(), "sau start xe phải đang chạy"); // trạng thái đã đổi, dù Car không tự giữ biến "running"

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng
    }
}
