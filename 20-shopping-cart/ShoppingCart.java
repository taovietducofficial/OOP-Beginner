/*
 * Ngôn ngữ: Java
 * Công dụng: ShoppingCart là bài ÔN TẬP tổng hợp mọi kỹ thuật đã học ở tầng
 * beginner trong một bài toán duy nhất: đóng gói + validate ở biên (bài 06),
 * overload phương thức (bài 14), một class quản lý tập hợp nhiều object con
 * và tổng hợp dữ liệu (bài 12), defensive copy khi để lộ danh sách ra ngoài
 * (bài 17), và object tự mô tả chính nó qua toString (bài 08).
 * Tại sao cần học: đây là hình dạng gần với code thực tế nhất trong cả tầng
 * — một class không dạy một khái niệm mới, mà PHỐI HỢP nhiều khái niệm cũ
 * để giải quyết một bài toán hoàn chỉnh. Từ bài sau (tầng 02-student), 4 trụ
 * cột OOP (đóng gói, kế thừa, đa hình, trừu tượng) sẽ mở rộng đúng nền này —
 * ví dụ ShoppingCart tính giảm giá khác nhau theo loại khách hàng.
 */
import java.util.ArrayList; // thư viện chuẩn: danh sách động
import java.util.List;      // thư viện chuẩn: kiểu interface cho danh sách

class CartItem { // class phụ trợ — một dòng hàng trong giỏ: tên, đơn giá, số lượng
    private final String name;  // tên món hàng — riêng cho từng object, không đổi sau khi tạo
    private final int price;    // đơn giá (đồng) — số nguyên, không dùng float cho tiền (như bài 09 Money)
    private final int quantity; // số lượng — riêng cho từng object, không đổi sau khi tạo

    CartItem(String name, int price, int quantity) { // constructor — chạy khi thêm một dòng hàng
        if (name == null || name.isEmpty()) throw new IllegalArgumentException("Tên món hàng không được rỗng"); // validate ở biên
        if (price <= 0) throw new IllegalArgumentException("Đơn giá phải > 0");   // validate ở biên
        if (quantity <= 0) throw new IllegalArgumentException("Số lượng phải > 0"); // validate ở biên
        this.name = name;
        this.price = price;
        this.quantity = quantity;
    }

    String getName() { return name; }         // getter — xem tên món hàng
    int getSubtotal() { return price * quantity; } // thành tiền của riêng dòng hàng này

    @Override
    public String toString() { // dòng hàng tự mô tả chính nó, vd. "Áo thun x1 = 100000đ"
        return name + " x" + quantity + " = " + getSubtotal() + "đ";
    }
}

public class ShoppingCart { // khai báo class — khuôn mẫu để tạo ra các object ShoppingCart

    private final String customerName;               // tên khách hàng — riêng cho từng object, không đổi sau khi tạo
    private final List<CartItem> items = new ArrayList<>(); // TẬP HỢP: giỏ hàng chứa nhiều CartItem (giống Classroom chứa nhiều Student ở bài 12)

    public ShoppingCart(String customerName) { // constructor — chạy khi tạo giỏ hàng mới, ban đầu chưa có món nào
        if (customerName == null || customerName.isEmpty()) throw new IllegalArgumentException("Tên khách hàng không được rỗng"); // validate ở biên
        this.customerName = customerName;
    }

    public void addItem(String name, int price) { // OVERLOAD 1: thêm hàng với số lượng mặc định là 1 (giống bài 14 Invoice)
        addItem(name, price, 1); // ủy quyền cho bản đầy đủ — logic tạo CartItem (và validate của nó) chỉ nằm ở một chỗ duy nhất
    }

    public void addItem(String name, int price, int quantity) { // OVERLOAD 2: thêm hàng với số lượng chỉ định rõ
        items.add(new CartItem(name, price, quantity)); // CartItem tự validate trong constructor của nó
    }

    public List<CartItem> getItems() { // getter — trả về danh sách dòng hàng
        return new ArrayList<>(items); // DEFENSIVE COPY (bài 17) — không để lộ tham chiếu tới danh sách nội bộ
    }

    public int getTotal() { // tổng tiền giỏ hàng — TỔNG HỢP dữ liệu từ nhiều CartItem (giống averageScore ở bài 12)
        int sum = 0;
        for (CartItem item : items) sum += item.getSubtotal(); // cộng dồn thành tiền từng dòng hàng
        return sum;
    }

    @Override
    public String toString() { // giỏ hàng tự mô tả chính nó (bài 08)
        return "Giỏ hàng của " + customerName + ": " + items.size() + " món, tổng " + getTotal() + "đ";
    }

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình khi gõ "java ShoppingCart"
        ShoppingCart cart = new ShoppingCart("An"); // tạo giỏ hàng của An, ban đầu rỗng
        cart.addItem("Áo thun", 100_000);        // OVERLOAD 1 — số lượng ngầm định là 1
        cart.addItem("Quần jean", 200_000, 2);   // OVERLOAD 2 — số lượng chỉ định rõ là 2

        check(cart.getItems().size() == 2, "giỏ hàng phải có 2 dòng hàng"); // đếm đúng số phần tử đã thêm
        check(cart.getTotal() == 100_000 + 200_000 * 2, "tổng tiền giỏ hàng tính sai"); // 100.000 + 400.000 = 500.000
        check(cart.toString().equals("Giỏ hàng của An: 2 món, tổng 500000đ"), "toString sai định dạng");

        List<CartItem> copy = cart.getItems(); // lấy bản sao ra ngoài
        copy.clear(); // sửa bản sao — mô phỏng code ngoài tự ý xóa hết
        check(cart.getItems().size() == 2, "sửa danh sách lấy từ getItems() không được ảnh hưởng tới giỏ hàng gốc"); // defensive copy vẫn giữ vững

        boolean blocked = false; // cờ đánh dấu: đơn giá không hợp lệ có bị chặn không
        try { cart.addItem("Lỗi", -1000); } catch (IllegalArgumentException e) { blocked = true; }
        check(blocked, "đơn giá âm phải bị chặn");

        boolean noCustomer = false; // cờ đánh dấu: tên khách hàng rỗng có bị chặn không
        try { new ShoppingCart(""); } catch (IllegalArgumentException e) { noCustomer = true; }
        check(noCustomer, "tên khách hàng rỗng phải bị chặn");

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng
    }
}
