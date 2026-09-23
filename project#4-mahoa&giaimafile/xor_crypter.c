#include <stdio.h>
int main (int argc, char *argv[]) { // Số llượng từ - Danh sách các từ. 
    // Đọc nhị phân file A, sau đó ghi vào file B
    // Tự tạo 1 con số - kí tự chìa khóa để tự sinh số
    // XOR chìa khóa với dữ liệu của file A theo từng đợt.
    if (argc < 2) {
        printf ("Sai cú pháp! vui lòng nhập lệnh theo cú pháp sau để mã hóa hoặc giải mã:\n");
        printf ("./xor_crypter <ten_file_nguon> <ten_file_dich> <khoa>\n");
        return 1;
    }

    FILE *f = fopen (argv[1], "rb"); // Mở file A để đọc nhị phân
    if (f==NULL) {
        printf ("File không tồn tại.\n");
        return 1;
    }
    // Bây giờ, ta cần đọc file nhị phân, sau đó XOR với chìa khóa, sau đó ghi theo kiểu text vào file B. => ta sẽ dùng hàm mahoavagiaima() để gọi luôn.
    // Người dùng có thể vừa giải mã, vừa mã hóa, chỉ cần có 3 file khác nhau (A để đọc, B để mã hóa, C để hứng dữ liệu giải mã).
    mahoavagiaima(argv[1], argv[2], argv[3]); // Ta nhập 3 chuỗi làm dữ liệu đầu vào.
    // Bây giờ trong file argv[2] đã có dữ liệu sau mã hóa hoặc giải mã rồi.

    return 0;
}