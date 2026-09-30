// Bây giờ ở file chính, ta sẽ tạo 1 danh sách gồm các gói tin giả lập và test.

#include <stdio.h>
#include "packetfilter.h" // Nhớ include file .h của bạn vào!

int main() {
    // B1: Tạo danh sách gồm các gói tin
    Packet danh_sach[] = {
        // Gói 1: Sạch sẽ hoàn toàn
        { "192.168.1.10", 80, "GET /index.html HTTP/1.1" },

        // Gói 2: Tấn công SQL Injection vào Web (Port 80)
        { "10.0.0.99",    80, "SELECT * FROM users WHERE user='admin' OR 1=1 --" },

        // Gói 3: Cố tình truy cập cổng Telnet cấm (Port 23)
        { "172.16.0.4",   23, "USER root PASS toor" },

        // Gói 4: Quét cổng SMB nhạy cảm (Port 445 - WannaCry)
        { "192.168.1.77", 445, "SMB_NEGOTIATE_PROTOCOL_REQUEST" }
    };

    // B2: Tính số lượng gói tin
    int so_luong = sizeof(danh_sach) / sizeof(danh_sach[0]);

    printf("=====================================================\n");
    printf("   KHOI DONG HE THONG TUONG LUA (TONG: %d GOI TIN)\n", so_luong);
    printf("=====================================================\n\n"); // Xuống dòng 2 lần.

    // B3: Kiểm tra số gói tin bị chặn SQL
    printf(">>> DOT QUET 1: AP DUNG LUAT CHECK_SQL_INJECTION <<<\n");
    int bi_chan_sql = fire_wall (danh_sach, so_luong, sql_injection_filter);
    printf("=> Ket qua: Da chan %d goi tin SQL doc hai!\n\n", bi_chan_sql);

    // B4: Kiểm tra số gói tin bị chặn Port
    printf(">>> DOT QUET 2: AP DUNG LUAT CHECK_BLOCKED_PORTS <<<\n");
    int bi_chan_port = fire_wall (danh_sach, so_luong, port_filter);
    printf("=> Ket qua: Da chan %d goi tin co port nguy hiem!\n\n", bi_chan_port);

    return 0;
}