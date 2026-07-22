/*
 * Ngôn ngữ: Java
 *
 * Công dụng: Temperature minh họa STATIC FACTORY METHOD — constructor để
 * private, object chỉ được tạo qua các phương thức static có TÊN RÕ NGHĨA
 * (fromCelsius, fromFahrenheit) thay vì qua "new Temperature(...)" mù mờ.
 *
 * Tại sao cần học: bài 07 overload nhiều constructor cùng tên khi THAM SỐ
 * khác kiểu/số lượng. Nhưng ở đây fromCelsius(double) và fromFahrenheit(double)
 * có CÙNG kiểu tham số (double) — không thể overload constructor vì trùng
 * chữ ký. Static factory method giải quyết đúng vấn đề này: tên phương thức
 * tự nói lên ý nghĩa, còn constructor bị khóa private để ép mọi người đi
 * qua factory.
 */
public class Temperature { // khai báo class — khuôn mẫu để tạo ra các object Temperature

    private static final double ABSOLUTE_ZERO_C = -273.15; // hằng số CLASS: 0 tuyệt đối theo độ C — dùng chung cho mọi object, không đổi

    private final double celsius; // nhiệt độ lưu trữ nội bộ luôn theo độ C — chọn 1 đơn vị chuẩn để tính toán, quy đổi khi cần hiển thị

    private Temperature(double celsius) { // constructor PRIVATE — bên ngoài không gọi "new Temperature(...)" được, phải đi qua factory method
        if (celsius < ABSOLUTE_ZERO_C) throw new IllegalArgumentException("Nhiệt độ không thể thấp hơn 0 tuyệt đối"); // validate ở biên: chặn giá trị vô lý về mặt vật lý
        this.celsius = celsius; // gán nhiệt độ (đã ở đơn vị chuẩn độ C)
    }

    public static Temperature fromCelsius(double celsius) { // FACTORY METHOD: tạo Temperature từ độ C — tên tự giải thích, khỏi cần đoán tham số là đơn vị gì
        return new Temperature(celsius); // độ C đã là đơn vị chuẩn nội bộ, không cần quy đổi
    }

    public static Temperature fromFahrenheit(double fahrenheit) { // FACTORY METHOD: tạo Temperature từ độ F — quy đổi sang độ C rồi mới gọi constructor
        return new Temperature((fahrenheit - 32) * 5 / 9); // công thức quy đổi F sang C
    }

    public double toCelsius() { // đọc nhiệt độ theo độ C
        return celsius; // đơn vị chuẩn nội bộ, trả thẳng ra
    }

    public double toFahrenheit() { // đọc nhiệt độ theo độ F
        return celsius * 9 / 5 + 32; // công thức quy đổi C sang F
    }

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình khi gõ "java Temperature"
        Temperature boiling = Temperature.fromCelsius(100); // tạo qua factory "fromCelsius" — rõ ràng đây là 100 độ C
        check(boiling.toFahrenheit() == 212, "100°C phải bằng 212°F"); // nước sôi: mốc quy đổi kinh điển

        Temperature freezing = Temperature.fromFahrenheit(32); // tạo qua factory "fromFahrenheit" — rõ ràng đây là 32 độ F
        check(freezing.toCelsius() == 0, "32°F phải bằng 0°C"); // nước đóng băng: mốc quy đổi kinh điển

        boolean blocked = false; // cờ đánh dấu: nhiệt độ dưới 0 tuyệt đối có bị chặn không
        try { Temperature.fromCelsius(-300); } catch (IllegalArgumentException e) { blocked = true; } // -300°C thấp hơn 0 tuyệt đối (-273.15°C) — phải bị chặn
        check(blocked, "nhiệt độ dưới 0 tuyệt đối phải bị chặn"); // xác nhận validate hoạt động dù tạo qua factory nào

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng
    }
}
