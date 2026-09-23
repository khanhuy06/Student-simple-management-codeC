#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]) {
    if (argc < 2) {
        printf ("Sai cú pháp, để quét mã độc, yêu cầu gõ :\n");
        printf ("./log_hunter <ten_file>\n"); // Không bỏ dấu ngoặc kép "ten_file" ở trong printf.
        return 1;
    }

    FILE *f = fopen (argv[1], "r"); // Không cần bỏ argv ở trong ngoặc kép vì nó k phải tên.
    if (f==NULL) {
        printf ("File không tồn tại.\n");
        return 1;
    }
    
    // Ý tưởng là ghi báo cáo vào 1 file khác để dùng fgets quét và ghi dữ liệu vào

    FILE *baocao =  fopen ("baocao.txt", "a"); // Thực ra ko cần làm cái if ở trên, vì nếu dùng "a", khi chưa có, máy sẽ tự tạo mới.
    char line[1000]; // Tạo 1 chỗ chứa cho fgets đọc từ f cho đến khi gặp \n, sau đó nó ghi vào đây
    int so_dong = 0;
    while (fgets (line, sizeof(line), f) != NULL) {
        so_dong++;
       
        // 1. Soi đòn Path Traversal (chứa "..")
        if (strstr(line, "..") != NULL) {
            printf("[!] Dong %d: Phat hien [PATH TRAVERSAL] -> %s", so_dong, line);
            fprintf(baocao, "[PATH TRAVERSAL] Dong %d: %s", so_dong, line);
        }
        // 2. Soi đòn SQL Injection (chứa "' OR " hoặc "--")
        else if (strstr(line, "' OR ") != NULL || strstr(line, "--") != NULL) {
            printf("[!] Dong %d: Phat hien [SQL INJECTION]  -> %s", so_dong, line);
            fprintf(baocao, "[SQL INJECTION] Dong %d: %s", so_dong, line);
        }
        // 3. Soi đòn XSS chèn mã độc (chứa "<script>")
        else if (strstr(line, "<script>") != NULL) {
            printf("[!] Dong %d: Phat hien [XSS INJECTION]  -> %s", so_dong, line);
            fprintf(baocao, "[XSS INJECTION] Dong %d: %s", so_dong, line);
        }
    }
    fclose(baocao);

    FILE *baocao2 = fopen("baocao.txt", "r");
    if (baocao2 == NULL) {
        return 1;
    }
    while (fgets (line, sizeof(line), baocao2) != NULL) { // ở trường hợp như kiểu nhập mật khẩu, xác thực tên file, lệnh fgets cần xoad \n ở đuôi (miniprojectw2).
        printf("%s", line); // fgets đã nuốt sẵn \n rồi nên k cần bỏ \n sau %s.
    }
    fclose(baocao2);

    fclose(f);
    return 0;
}

// Kỹ thuật khó nhất là so sánh để lọc, sau đó lưu vào file báo cáo để hiển thị đẹp mắt - đúng lỗi.