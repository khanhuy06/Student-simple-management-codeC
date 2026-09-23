#include <studio.h>
#include <ctype.h>  // Cần thư viện này để dùng hàm toupper() để đổi chữ thường thành chữ hoa, và hàm isdigit() để biết ký tự này có phải là một chữ số từ '0' đến '9' hay không?
#include "generator.h"

static int ma_so_ve = 1; // static khóa chặt biến này ở trong file, k cho dùng extern để gọi nó ra ngoài, muốn xem dc thì dùng hàm "in_ve"
                        // static cục bộ thì cho phép ta lưu giá trị của biến đó, kể cả khi thoát hàm, nhưng vẫn ko dc gọi nó ra ngoài
void in_ve(const char *loai_ve) { // Tức là ta sẽ nhập data vào là cả 1 chuỗi hằng, dùng con trỏ để định vị
    printf ("+------------------------------+\n");
    printf ("|        VÉ XE SỰ KIỆN         |\n");
    printf ("| Hạng: %-10s Số: #%03d   |\n", loai_ve, &ma_so_ve);
    printf ("+------------------------------+\n");
    ma_so_ve++;

void chuyen_thanh_chu_hoa(char *dich, const char *nguon) {
    int i = 0;
    while (nguon[i] != '\0') {
        dich[i] = toupper((unsigned char)nguon[i]); // toupper: biến chữ thường thành chữ HOA
// char sẽ nhận dc 256 kí tự, bth thì k sao, nhưng lỡ kí tự có dấu, vượt ngoài 127 (ASCII) sẽ bị hiểu là 1 số âm, khi hàm toupper tra bảng kí tự chữ HOA, nó thấy 1 số âm lạ, nó sẽ báo lỗi. Vì vậy, phải để "unsign char" để khi 1 kí tự > 127, ví dụ 200, toupper sẽ dò bảng, tìm số 200 và trả về kí tự HOA của số 200 đó 
        i++;
    }
    dich[i] = '\0'; // Ký tự kết thúc chuỗi
}
    
int la_so_nguyen_duong(const char *str) { // Để const để ko đổi giá trị, nó bị fix cứng
    if (str == NULL || *str == '\0') return 0;
    for (int i = 0; str[i] != '\0'; i++) { // Máy nhận nó là 1 TỪ, nên phải dùng dạng chuỗi
        if (!isdigit((unsigned char)str[i])) return 0; // Nếu str[i] không phải là 1 chữ số
    }
    return 1;
}
    




}