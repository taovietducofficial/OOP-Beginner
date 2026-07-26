/*
 * Ngôn ngữ: Java
 * Công dụng: PizzaOrder minh họa FLUENT INTERFACE (method chaining) —
 * addTopping() trả về CHÍNH OBJECT ĐANG GỌI ("return this") thay vì void,
 * cho phép nối nhiều lời gọi liên tiếp trên cùng một dòng:
 * order.addTopping("cheese").addTopping("bacon").
 * Tại sao cần học: bài 16 (Fraction) trả về object MỚI ở mỗi phép toán vì nó
 * bất biến. Bài này ngược lại — object CÓ trạng thái thay đổi (giống Counter,
 * BankAccount) nhưng thay vì mỗi phương thức trả về void, nó trả về "this" để
 * người gọi CẤU HÌNH DẦN DẦN object qua một chuỗi lời gọi liền mạch, dễ đọc.
 * Đây là bước đệm tới Builder pattern chính thức ở tầng sau.
 */
import java.util.ArrayList; // thư viện chuẩn: danh sách động
import java.util.List;      // thư viện chuẩn: kiểu interface cho danh sách
import java.util.Map;       // thư viện chuẩn: bảng tra giá theo size

public class PizzaOrder { // khai báo class — khuôn mẫu để tạo ra các object PizzaOrder

    private static final Map<String, Integer> BASE_PRICE = Map.of("S", 30_000, "M", 45_000, "L", 60_000); // giá nền theo size — dùng chung cho mọi object
    private static final int TOPPING_PRICE = 10_000; // giá mỗi topping — dùng chung cho mọi object

    private final String size;                        // size bánh — riêng cho từng object, không đổi sau khi tạo
    private final List<String> toppings = new ArrayList<>(); // danh sách topping — dữ liệu MUTABLE nằm bên trong object

    public PizzaOrder(String size) { // constructor — chạy khi gọi "new PizzaOrder(...)"
        if (!BASE_PRICE.containsKey(size)) throw new IllegalArgumentException("Size phải là S, M hoặc L"); // validate ở biên
        this.size = size; // gán size hợp lệ
    }

    public PizzaOrder addTopping(String name) { // thêm topping — trả về CHÍNH OBJECT NÀY để gọi tiếp được (fluent)
        if (name == null || name.isEmpty()) throw new IllegalArgumentException("Tên topping không được rỗng"); // validate ở biên
        toppings.add(name); // đưa vào cuối danh sách nội bộ
        return this; // trả về chính object đang gọi — KHÔNG tạo object mới (khác hẳn Fraction.add() ở bài 16)
    }

    public List<String> getToppings() { // getter — trả về danh sách topping
        return new ArrayList<>(toppings); // DEFENSIVE COPY (kỹ thuật đã học ở bài 17) — không để lộ tham chiếu nội bộ
    }

    public int getTotal() { // tổng tiền = giá nền theo size + số topping * giá mỗi topping
        return BASE_PRICE.get(size) + toppings.size() * TOPPING_PRICE;
    }

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình khi gõ "java PizzaOrder"
        PizzaOrder order = new PizzaOrder("M"); // tạo đơn pizza size M, chưa có topping nào

        PizzaOrder chained = order.addTopping("cheese").addTopping("bacon"); // nối hai lời gọi liên tiếp trên cùng một object
        check(chained == order, "addTopping() phải trả về CHÍNH object đang gọi, không tạo object mới"); // reference equality: cùng một object trong bộ nhớ

        check(order.getToppings().equals(List.of("cheese", "bacon")), "danh sách topping phải đúng thứ tự đã thêm");
        check(order.getTotal() == 45_000 + 2 * 10_000, "tổng tiền phải bằng giá nền size M cộng 2 topping");

        List<String> copy = order.getToppings(); // lấy bản sao ra ngoài
        copy.add("Hacked Topping"); // sửa bản sao — mô phỏng code ngoài tự ý thêm
        check(order.getToppings().size() == 2, "sửa danh sách lấy từ getToppings() không được ảnh hưởng tới order gốc"); // defensive copy vẫn giữ vững

        boolean badSize = false; // cờ đánh dấu: size không hợp lệ có bị chặn không
        try { new PizzaOrder("XL"); } catch (IllegalArgumentException e) { badSize = true; }
        check(badSize, "size ngoài S/M/L phải bị chặn");

        boolean emptyTopping = false; // cờ đánh dấu: topping tên rỗng có bị chặn không
        try { order.addTopping(""); } catch (IllegalArgumentException e) { emptyTopping = true; }
        check(emptyTopping, "topping tên rỗng phải bị chặn");

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng
    }
}
