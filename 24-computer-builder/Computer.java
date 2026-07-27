/*
 * Ngôn ngữ: Java
 * Công dụng: Computer/ComputerBuilder minh họa BUILDER PATTERN — ComputerBuilder
 * là một object TẠM THỜI, riêng biệt, dùng để gom dữ liệu cấu hình qua nhiều
 * bước (setCpu, setRam, setSsd, theo thứ tự bất kỳ). Computer THẬT SỰ chưa
 * tồn tại cho tới khi gọi build() — lúc đó nó được tạo MỘT LẦN, đầy đủ, và
 * bất biến từ đầu.
 * Tại sao cần học: bài 18 (PizzaOrder) dùng fluent interface — object đã tồn
 * tại từ đầu, mỗi lần gọi addTopping() là SỬA NGAY chính nó. Bài này khác:
 * Computer KHÔNG có setter nào cả, không thể sửa sau khi build(); mọi việc
 * "sửa dần" chỉ xảy ra trên ComputerBuilder tạm thời, không phải trên chính
 * Computer.
 */
class ComputerBuilder { // object TẠM THỜI — gom dữ liệu qua nhiều bước, chưa phải Computer thật
    private String cpu;             // chưa set thì vẫn null — build() phải kiểm tra bắt buộc
    private int ram = 8;             // giá trị mặc định nếu người dùng không gọi setRam()
    private boolean hasSsd = false; // giá trị mặc định nếu người dùng không gọi setSsd()

    public ComputerBuilder setCpu(String cpu) { // mỗi bước trả về "this" để có thể gọi tiếp (giống fluent interface bài 18), nhưng KHÔNG sửa Computer nào cả — vì Computer chưa tồn tại
        if (cpu == null || cpu.isEmpty()) throw new IllegalArgumentException("CPU không được rỗng"); // validate ở biên
        this.cpu = cpu;
        return this;
    }

    public ComputerBuilder setRam(int ram) {
        if (ram <= 0) throw new IllegalArgumentException("RAM phải dương"); // validate ở biên
        this.ram = ram;
        return this;
    }

    public ComputerBuilder setSsd(boolean hasSsd) {
        this.hasSsd = hasSsd;
        return this;
    }

    public Computer build() { // chốt lại — tạo MỘT Computer bất biến, đây là lần DUY NHẤT dữ liệu được "đóng băng"
        if (cpu == null) throw new IllegalStateException("Phải setCpu(...) trước khi build()"); // validate: trường bắt buộc chưa có
        return new Computer(cpu, ram, hasSsd);
    }
}

public class Computer { // sản phẩm cuối — BẤT BIẾN, chỉ có getter, không setter (giống Fraction ở bài 16)
    private final String cpu;
    private final int ram;
    private final boolean hasSsd;

    Computer(String cpu, int ram, boolean hasSsd) { // package-private: chỉ ComputerBuilder (cùng file/package) gọi trực tiếp được — ép mọi người dùng khác đi qua Builder
        this.cpu = cpu;
        this.ram = ram;
        this.hasSsd = hasSsd;
    }

    public String getCpu() { return cpu; } // getter — xem cpu đã cấu hình

    public int getRam() { return ram; } // getter — xem dung lượng RAM (GB)

    public boolean hasSsd() { return hasSsd; } // getter — có ổ SSD hay không

    @Override
    public String toString() { // object tự mô tả chính nó (bài 08)
        return cpu + " / " + ram + "GB RAM / " + (hasSsd ? "SSD" : "HDD");
    }

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình khi gõ "java Computer"
        Computer full = new ComputerBuilder() // dựng qua nhiều bước, thứ tự bất kỳ
                .setCpu("Intel i7")
                .setRam(16)
                .setSsd(true)
                .build();
        check(full.getCpu().equals("Intel i7"), "cpu phải đúng giá trị đã set");
        check(full.getRam() == 16, "ram phải đúng giá trị đã set");
        check(full.hasSsd(), "hasSsd phải đúng giá trị đã set");

        Computer defaults = new ComputerBuilder().setCpu("AMD Ryzen").build(); // chỉ set cpu — ram và hasSsd dùng giá trị mặc định
        check(defaults.getRam() == 8, "không setRam() thì phải dùng mặc định 8");
        check(!defaults.hasSsd(), "không setSsd() thì phải dùng mặc định false");

        boolean blockedNoCpu = false; // cờ đánh dấu: build() thiếu cpu bắt buộc có bị chặn không
        try { new ComputerBuilder().setRam(32).build(); } catch (IllegalStateException e) { blockedNoCpu = true; }
        check(blockedNoCpu, "build() không có setCpu(...) trước đó phải bị chặn");

        boolean blockedBadRam = false; // cờ đánh dấu: RAM không dương có bị chặn không
        try { new ComputerBuilder().setRam(0); } catch (IllegalArgumentException e) { blockedBadRam = true; }
        check(blockedBadRam, "setRam(0) phải bị chặn");

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng
    }
}
