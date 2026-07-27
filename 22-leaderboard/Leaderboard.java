/*
 * Ngôn ngữ: Java
 * Công dụng: Player/Leaderboard minh họa THỨ TỰ TỰ NHIÊN (natural ordering)
 * — Player tự khai báo cách so sánh với một Player khác bằng cách implement
 * Comparable<Player> và định nghĩa compareTo(). Nhờ vậy Collections.sort()
 * dùng được ngay trên danh sách Player mà không cần viết thêm hàm so sánh
 * rời rạc ở nơi gọi.
 * Tại sao cần học: bài 09 (Money) dạy so sánh BẰNG NHAU (equals/==). Bài này
 * dạy so sánh HƠN/KÉM để sắp xếp — một khái niệm khác, dùng cho một mục
 * đích khác (equals trả lời "có giống nhau không", compareTo trả lời "ai
 * đứng trước ai").
 */
import java.util.ArrayList; // thư viện chuẩn: List động
import java.util.Collections; // thư viện chuẩn: Collections.sort dùng thứ tự tự nhiên của phần tử
import java.util.List;

class Player implements Comparable<Player> { // implements Comparable<Player>: khai báo "Player biết tự so sánh với Player khác"
    private final String name;  // tên người chơi
    private final int score;    // điểm số — càng cao càng đứng trước trong bảng xếp hạng

    public Player(String name, int score) { // constructor — chạy khi tạo một người chơi
        if (name == null || name.isEmpty()) throw new IllegalArgumentException("Tên người chơi không được rỗng"); // validate ở biên
        if (score < 0) throw new IllegalArgumentException("Điểm số không được âm"); // validate ở biên
        this.name = name;
        this.score = score;
    }

    public String getName() { // getter — xem tên người chơi
        return name;
    }

    public int getScore() { // getter — xem điểm số hiện tại
        return score;
    }

    @Override
    public int compareTo(Player other) { // THỨ TỰ TỰ NHIÊN: điểm cao hơn thì "nhỏ hơn" (đứng trước) trong sắp xếp tăng dần
        return Integer.compare(other.score, this.score); // đảo other/this để sort tăng dần cho ra thứ tự ĐIỂM GIẢM DẦN
    }

    @Override
    public String toString() { // object tự mô tả chính nó (bài 08) — tiện khi in cả danh sách
        return name + ": " + score;
    }
}

public class Leaderboard { // khai báo class — quản lý tập hợp Player và tính bảng xếp hạng

    private final List<Player> players = new ArrayList<>(); // tập hợp các Player đã thêm — CHƯA sắp xếp theo thứ tự thêm vào

    public void addPlayer(String name, int score) { // thêm một người chơi mới vào bảng
        players.add(new Player(name, score));
    }

    public List<Player> getRanking() { // trả về danh sách đã SẮP XẾP theo score giảm dần — không đổi thứ tự nội bộ của "players"
        List<Player> ranking = new ArrayList<>(players); // bản sao (bài 17) — sort không được phép làm xáo trộn danh sách gốc ngoài ý muốn
        Collections.sort(ranking); // dùng ĐÚNG thứ tự tự nhiên đã khai báo trong Player.compareTo — không cần viết Comparator riêng
        return ranking;
    }

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình khi gõ "java Leaderboard"
        Leaderboard board = new Leaderboard();
        board.addPlayer("An", 50);   // thêm THEO THỨ TỰ: An, Binh, Chi — không phải thứ tự điểm số
        board.addPlayer("Binh", 90);
        board.addPlayer("Chi", 70);

        List<Player> ranking = board.getRanking();
        check(ranking.size() == 3, "bảng xếp hạng phải có đủ 3 người chơi");
        check(ranking.get(0).getName().equals("Binh"), "điểm cao nhất (90) phải đứng đầu bảng xếp hạng");
        check(ranking.get(1).getName().equals("Chi"), "điểm nhì (70) phải đứng thứ hai");
        check(ranking.get(2).getName().equals("An"), "điểm thấp nhất (50) phải đứng cuối");

        Player p1 = new Player("X", 100);
        Player p2 = new Player("Y", 80);
        check(p1.compareTo(p2) < 0, "người chơi điểm cao hơn phải 'nhỏ hơn' trong compareTo (để đứng trước khi sort tăng dần)");

        boolean blockedScore = false; // cờ đánh dấu: điểm âm có bị chặn không
        try { new Player("Z", -1); } catch (IllegalArgumentException e) { blockedScore = true; }
        check(blockedScore, "điểm số âm phải bị chặn");

        boolean blockedName = false; // cờ đánh dấu: tên rỗng có bị chặn không
        try { new Player("", 10); } catch (IllegalArgumentException e) { blockedName = true; }
        check(blockedName, "tên người chơi rỗng phải bị chặn");

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng
    }
}
