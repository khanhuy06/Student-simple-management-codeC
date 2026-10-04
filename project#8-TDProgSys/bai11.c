// CÁCH 1 :
// Gõ trên terminal 

// for u in $(cut -d: -f1 /etc/passwd); do     
   // ./bai10 $u
// done

// $(...) là chạy lệnh trong ngoặc trước.
// cut -d: -f1 /etc/passwd là : cắt và lấy (cut) cột (-d) 1 (-f1) của file /etc/passwd, cột 1 là tên người dùng.

// CÁCH 2 :
#include <stdio.h>      // Chứa hàm printf() và snprintf()
#include <pwd.h>        // Chứa hàm getpwent() và endpwent()
#include <stdlib.h>     // Chứa hàm system()
#include <sys/types.h> // Chứa mấy kiểu dữ liệu mà linux dùng, như uid_t; gid_t.

int main() // Không cần nhập tham số gì.
{
    struct passwd *p;
    int dem = 0;
    int hop_le = 0;
    char lenh[256]; // Vì ta cần 1 chuỗi liền, ví dụ : "./bai10 root"

    printf("DANH SACH TOAN BO TAI KHOAN TREN HE THONG\n\n");

    // Vòng lặp: mỗi lần lặp, p nhận 1 tài khoản mới. Khi hết tài khoản, p == NULL -> dừng
    while ((p = getpwent()) != NULL) {
        dem++;
        snprintf(lenh, sizeof(lenh), "./bai10 %s", p->pw_name); // Ghép chuỗi xong thì lưu vào mảng.
        int ket_qua = system (lenh); // Vì bài 10 trả về 0 hoặc 1.
        // Thực thi lệnh ./bai10 p->pwname, nếu chạy được thì PASS, nếu k được thì FALL, in ra lỗi chạy chương trình khi gặp biến đó.
        if (ket_qua == 0) {
            hop_le++;
            printf("===> [PASS] Tai khoan %s hop le!\n\n", p->pw_name);
        } else {
            printf("===> [FAIL] Loi khi kiem tra tai khoan %s!\n\n", p->pw_name);
        }
    }

    // Đóng cơ sở dữ liệu tài khoản lại sau khi duyệt xong
    endpwent();

    printf("\nTong cong he thong co %d tai khoan, %d tai khoan chay thanh cong !\n", dem, hop_le);
    return 0;
}