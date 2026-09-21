#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]) { // Đây là cách khai báo chuẩn 1 hàm main. Số lượng từ & Danh sách các từ.
    // Khi code công cụ dòng lệnh, ko cần gõ scanf, thay vào đó, khi người dùng gõ lệnh,
    // dữ liệu đã nằm sẵn ở trên argv.
    // Đầu tiên, ta cần kiểm tra xem người dùng có truyền dữ liệu không
    if (argc < 2) {
        printf("Huong dan: ./scanner \"GET /index.html HTTP/1.1\"\n");
        return 1;
    }
    // Hàm sscanf : đọc chữ từ 1 chuỗi có sẵn (scanf : đọc từ bàn phím. fscanf : đọc chữ từ file).
    // Ta cần chuẩn bị 3 cái hộp để đựng dữ liệu đầu vào 
    char method[10];     // Hộp đựng chữ "GET"
    char path[256];      // Hộp đựng đường dẫn "/index.html"
    char protocol[20];   // Hộp đựng giao thức "HTTP/1.1"
    sscanf(argv[1], "%s %s %s", method, path, protocol); // argv[1] là vì khách sẽ nhập : ./scanner "GET ... HTTP/1.1"

    // BÀI TEST 1: Soi lỗ hổng Path Traversal (Hacker dùng "..").
    if (strstr(path, "..") != NULL) {
        printf("\n[!] NGUY HIEM: Phat hien tan cong Path Traversal!\n");
        printf("--> Canh bao: Hacker dang dung ky tu '..' de thoat khoi thu muc web!\n");
        return 1; // Chặn ngay, không cho truy cập!
    }
    // BÀI TEST 2: Soi độ dài đường dẫn (Chống tràn bộ nhớ Buffer Overflow).
    if (strlen(path) > 100) {
        printf("\n[!] CANH BAO: Duong dan qua dai (> 100 ky tu)!\n");
        printf("--> Nghi van: Co y nhồi dữ liệu để làm tràn bộ nhớ máy chủ!\n");
        return 1; // Chặn ngay!
    }
    // Nếu vượt qua được cả 2 bài test an toàn ở trên.
    printf("\n--> Ket qua: [OK] Yeu cau sach, an toan!\n");

    return 0;
}