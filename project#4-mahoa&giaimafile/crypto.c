#include "crypto.h"
#include <stdio.h>
#include <string.h>

// Đối với mã hóa XOR, phải luôn dùng file nhị phân để bảo toàn độ chính xác dữ liệu.

int mahoavagiaima(const char *ten_file_nguon, const char *ten_file_dich, const char *khoa) {
    char thung_chua[1024]; // Để hứng data từ file A.
    char dataXOR[1024]; // Để hứng data sau khi XOR, từ đó ghi vào file B.
    int j=0; // Phải để bên ngoài while, để sau mỗi lần lặp while, giá trị j không bị reset đứt đoạn.
    FILE *f = fopen (ten_file_nguon, "rb"); // Nhớ là ko bỏ trong ngoặc ten_file_nguon vì ta muốn link nó, không phải chuỗi.
    if (f==NULL) {
        printf ("File không tồn tại.\n");
        return 1;
    }
    FILE *f2 = fopen (ten_file_dich, "ab"); // Dùng "ab" để ghi nối, nếu chưa có thì tạo mới.
                                            
    int lenght; // Không được khai báo int ở bên trong vòng lặp while.
    while ((lenght = fread(thung_chua, 1, sizeof(thung_chua), f)) > 0) { // Lấy data từ file *f, ghi vào thung_chua, mỗi lần lấy 1 byte, lấy 1024 lần. 
        // Làm như này (1,1024) thay vì (1024,1) giúp fread đọc 1 byte 1024 lần, nếu k đủ thì nó vẫn trả kết quả về. còn nếu đọc 1 lần 1024 byte mà k đủ, thì nó trả kq về 0 => Gây ra việc thiếu dữ liệu.
        // Nếu có cả so sánh > và dấu bằng = thì nhớ để trong ngoặc.
        for (int i=0; i < lenght; i++) {
            dataXOR[i] = thung_chua[i] ^ khoa[j];
            j++;
            if (j==strlen(khoa)) { // strlen để đo khóa là đúng, nó chỉ sợ gặp kí tự 00000000.
                                   // fread nó đọc full và k tự động thêm "\0" vào cuối, nên strlen đo mãi k gặp dc "\0" => nó sẽ đọc lấn sang vùng nhớ rác của ctrinh khác.
                j=0;
            }
        }
        // Sau 1 lần lặp for, ta ghi vào file B.
        fwrite (dataXOR, 1, lenght, f2); // Ghi vào file B, mỗi lần ghi 1 byte, ghi lenght lần (vì khi fread đọc lần cuối, nếu bé hơn 1024 byte, mà vẫn ghi 1024 byte thì fwite sẽ bốc dữ liệu rác trong RAM để ghi vào (nó không phân biệt được rác)).
    }
    fclose (f2);
    fclose (f);
    return 0; // Nếu đọc file thành công, trả về 0.
}



// Nhược điểm của fgets :
    // Thứ 1, nó đọc đến khi gặp "\n" là dừng, cho nên khi đọc file nhị phân, có kí tự giống "\n" thì nó sẽ dừng, dẫn đến việc đọc file nhị phân bị lỗi.
    // Thứ 2, khi đọc hết, nó sẽ tự động thêm "\0" ở cuối, lúc này nếu ghép nối với chuỗi khác sẽ làm chuỗi nhị phân bị sai lệch.
// Nhược điểm của %s :
    // Khi nó nhảy vào đọc cái thằng dataXOR, nếu XOR xong mà gặp 0... thì nó dừng ngày lập tức, nó không ghi được gì cả.
// Nhược điểm của strlen :
    // Khi nó đo độ dài của file nhị phân, vì nếu gặp kí tự nhị phân trùng với "\0" thì nó dừng, đo ra độ dài không chính xác

// fread(cái_ca, kích_thước_1_giọt, số_giọt_tối_đa_múc_được, file_nguồn); // Thu được thùng chứa, trả về số byte đã đọc.
// fwrite(cái_ca, kích_thước_1_giọt, số_giọt_thực_tế_muốn_đổ, file_đích); // Lấy từ thùng chứa ghi vào file, trả về số byte đã đọc.

// Code lỗi : 

// int mahoavagiaima(const char *ten_file_nguon, const char *ten_file_dich, const char *khoa) {
    // char thung_chua[1024]; // Để hứng data từ file A.
    // char dataXOR[1024]; // Để hứng data sau khi XOR, từ đó ghi vào file B.
    // int j=0; // Phải để bên ngoài while, để sau mỗi lần lặp while, giá trị j không bị reset đứt đoạn.
    // FILE *f = fopen (ten_file_nguon, "rb"); // Nhớ là ko bỏ trong ngoặc ten_file_nguon vì ta muốn link nó, không phải chuỗi.
    // if (f==NULL) {
        // printf ("File không tồn tại.\n");
        // return 1;
    // }
    // FILE *f2 = fopen (ten_file_dich, "ab"); // Dùng "ab" để ghi nối, nếu chưa có thì tạo mới.
    // while (fgets(thung_chua, sizeof(thung_chua), f) != NULL) {
        // Mở file đích ra, ghi vào file
        // Nhưng trước tiên, cần lấy data từ thung_chua để XOR đã.
        // Nhưng muốn XOR, phải nghĩ ra cách nhân bản khóa, làm tăng độ dài.
        // for (int i=0; i < strlen (thung_chua); i++) {
            // dataXOR[i] = thung_chua[i] ^ khoa[j];
            // j++;
            // if (j==strlen(khoa)) {
                // j=0;
            // }
        // }
        // Sau khi đã XOR 1024 bytes (vì char chiếm 1 byte), ta cần ghi chuỗi dataXOR vào file B.
        // fprintf (f2, "%s", dataXOR);
        // Lưu ý, chỉ được XOR sau khi đã lặp xong for.
    // }
    // fclose (f2);
    // fclose (f);
    // return 0; // Nếu đọc file thành công, trả về 0.
// }