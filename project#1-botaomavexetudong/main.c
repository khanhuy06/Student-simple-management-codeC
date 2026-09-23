#include <stdio.h> 
#include <stdlib.h>      // Cần thư viện này để dùng hàm atoi() "ASCII to Integer" đổi chữ thành số
#include <string.h>      // Cần thư viện này để dùng hàm strcmp() để so sánh vé có đúng là VIP hoặc THUONG không
#include "generator.h"
// Người dùng sẽ nhập loại vé : VIP hoặc THUONG (ta tự biến thành chữ HOA), mặc định là vé thường, số lượng là 1 nếu k nhập data
// Nếu nhập sai kiểu dữ liệu (không có dấu cách, không đúng loại vé, không đúng kiểu dữ liệu) thì hệ thống sẽ báo lỗi
// ***Người dùng nhập lệnh trên terminal đã thì chương trình mới bắt đầu chạy***
int main (int soluongtu, char *tuso[]) { // Cứ khi nào chạy hàm main, Hệ điều hành BẮT BUỘC phải truyền "số lượng TỪ" vào tham số thứ nhất, và truyền "danh sách các TỪ" vào tham số thứ hai
    
    const char *raw_loai = (soluongtu > 1) ? tuso[1] : "THUONG"; // Nếu nhập 2 từ trở lên thì trả về từ số 2, không thì trả THUONG
    chuyen_thanh_chu_hoa(loai_ve, raw_loai);

    int so_luong = (soluongtu > 2) ? atoi(tuso[2]) : 1;

     // Bắt lỗi loại vé nhập bậy
     if (strcmp(loai_ve, "VIP") != 0 && strcmp(loai_ve, "THUONG") != 0) { // Hàm strcmp nếu 2 chuỗi giống nhau, nó trả về 0
        printf("\n[!] LOI: Loai ve '%s' khong hop le!\n", tuso[1]);
        printf("--> Goi y: He thong chi chap nhan ve 'VIP' hoac 'THUONG'.\n\n");
        return 1;
    }
    // Bắt lỗi số lượng vé
    if (soluongtu > 2) {
        if (!la_so_nguyen_duong(tuso[2]) || atoi(tuso[2]) == 0) { // Nếu k phải là số nguyên dương và nếu == 0 thì loại (vì hàm đầu tiên không loại số 0)
            printf("\n[!] LOI: So luong ve '%s' khong hop le!\n", tuso[2]);
            printf("--> Goi y: So luong phai la mot so nguyen > 0 (vi du: 1, 2, 3...).\n\n");
            return 1;
        }
        so_luong = atoi(tuso[2]);
    }

    printf("=== In %d ve%s (Loai: %s) ===\n", 
           so_luong, 
           (so_luong > 1) ? "s" : "", 
           loai_ve);
    
    while (so_luong-- > 0) { // soluong-- tức là lấy giá trị số lượng trước đã, sau khi lấy rồi mới trừ đi 1 đơn vị (nếu so_luong ==3 thì vòng lặp sẽ lặp 3 lần)
        in_ve(loai_ve);
    }

    return 0;
}



