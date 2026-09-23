#ifndef CRYPTO_H
#define CRYPTO_H

    int mahoavagiaima(const char *ten_file_nguon, const char *ten_file_dich, const char *khoa); // Chưa biết kiểu dữ liệu đầu vào của file. => bản chất tên file là chuỗi ký tự
                                           // Chưa biết làm sao để hút theo từng chuỗi byte của file. => tạo 1 thùng chứa để hứng bằng fgets.
                                           // Chưa biết làm sao để tự sinh khóa. => dùng 1 chuỗi kí tự đầu vào làm khóa, và tự nhân bản trong vòng lặp for (ở file crypto.c).
                                           // Trả về 0 hoặc 1 để biết là có đọc dc file hay ko.
    // Bây giờ, ta cần tạo 1 thùng chứa, sau đó hút byte đổ vào đó,  sau đó XOR, rồi ghi vào file đích.

#endif