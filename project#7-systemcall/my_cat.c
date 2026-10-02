#include <stdio.h>
#include <fcntl.h> // Thư viện này dùng cho hàm open.
#include <unistd.h> // Thư viện này dùng cho hàm read, write.

int main (int argc, char *argv[]) {
    if (argc < 2) {
        write(1, "Vui long dien ten file\n", 23);
        write(1, "./my_cat \"ten_file\"\n", 23);
        return 1;
    }
    // Người dùng nhập tên file, đầu tiên, ta phải đọc, sau đó, ta in ra màn hình.
    int fd = open (argv[1], O_RDONLY);
    if (fd == -1) { // Nhớ check lỗi k mở được file và in ra loại lỗi.
        perror ("Loi");
        return 1;
    }
    char thung_chua[1024];
    ssize_t byte;
    // Lấy data từ file, rót vào thung_chua ở trên RAM. 
    // Đầy thì ta đổ ra màn hình.
    while ((byte = read (fd, thung_chua, sizeof(thung_chua))) > 0) {
        write (1, thung_chua, byte);
    }
    close(fd); // Nhớ phải đóng file trước khi out chương trình.
    return 0;
}

