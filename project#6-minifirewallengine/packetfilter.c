#include <stdio.h>
#include <string.h>

typedef struct {
    char IP[16]; // Ví dụ 255.255.255.255, để 1 kí tự cuối cho "\0".
    int Port;
    char Payload[256]; // Vì kể cả có nhiều chữ, nhiều dòng, thì nó vẫn chỉ là 1 chuỗi duy nhất
}Packet;

typedef int (*Packetfilter) (const Packet *goitin); // Tạo con trỏ, trỏ tới hàm có dạng Packetfilter,
                                                    // nó sẽ nhận đầu vào là địa chỉ của các gói tin, trả về 1 hoặc 0.

// Tạo 1 hàm để lọc SQL Injection, 1 hàm chặn gửi tới cổng 23, 445

int sql_injection_filter (const Packet *goitin) { // goitin là con trỏ nên phải để dấu "->"
    // Hàm này sẽ nhận gói tin, kiểm tra Payload xem có các kí tự như : ('OR1=1--)(admin'--)
    // Dùng strstr(chuỗi cha, chuỗi muốn tìm) để lọc chuỗi.
    int False = 0;
    char *danh_sach_chan[] = {"'OR1=1--","admin'--"};
    for (int i = 0; i < (sizeof(danh_sach_chan) / sizeof(danh_sach_chan[0])); i++) {
        if (strstr(goitin->Payload, danh_sach_chan[i]) != NULL) // Đầu vào là con trỏ đại chỉ gói tin, phải dùng "->".
            // strstr chỉ trả về NULL hoặc ĐỊA CHỈ Ô NHỚ chứ k phải 0 với 1.
        {
            False = 1;
            goto thoat_vong_lap;
        }
    }
    thoat_vong_lap :
    if (False == 0) // Nhớ là phép so sánh phải có 2 dấu bằng "==".
    {
        printf ("0-PASS");
    }
    else {
        printf ("1-DROP");
    }
    return False;
}

int port_filter (const Packet *goitin) { // Truyền ĐỊA CHỈ gói tin vào.
    int False = 0;
    int danh_sach_cong_chan[] = {23, 445}; // Tạo mảng bình thường, k để dấu sao *.
    for (int i = 0; i < (sizeof(danh_sach_cong_chan) / sizeof(danh_sach_cong_chan[0])); i++) 
    
    // Số lượng ptu = sizeof(mảng) / sizeof(phần tử trong mảng).
    
    {
        if (goitin->Port == danh_sach_cong_chan[i]) 
            // strstr chỉ trả về NULL hoặc ĐỊA CHỈ Ô NHỚ chứ k phải 0 với 1.
        {
            False = 1;
            goto thoat_vong_lap;
        }
    }
    thoat_vong_lap :
    if (False == 0) {
        printf ("PASS");
    }
    else { 
        printf ("DROP");

    }
    return False;
}

// Bây giờ, đã tạo xong 2 hàm với chức năng : nhận gói tin, dò xem có lỗi muốn lọc không, in ra 0 hoặc 1 để cảnh báo cho tưởng lửa.

// Với hàm tiếp theo, khi nhận 1 đống gói tin, chúng sẽ đi qua hàm lọc, 
// nếu trả về 0, in ra danh sách pass, nếu trả về 1, in ra danh sách drop.

int fire_wall (Packet goitin[], int tongsogoitin, Packetfilter ham_loc) { // ham_loc đã là 1 con trỏ rồi. 
                                                                           // Việc đếm gói tin giao cho hàm khác.
                                                                           // Packet *goitin[] không cần *, vì nó hiểu là 1 mảng gồm nhiều biến kiểu dữ liệu Packet,
                                                                           // không cần * vì C ko copy mảng, ko sợ tốn RAM.
    char *danh_sach_ip_pass[tongsogoitin]; // Nếu k có dấu sao thì C sẽ tạo mảng gồm tongsogoitin kí tự, nếu có thì tạo mảng gồm tongsogoitin chuỗi.
    int a = 0;
    char *danh_sach_ip_drop[tongsogoitin];
    int b = 0; // Tạo biến đếm cho mảng để gán ip vào.
        for (int i = 0; i < tongsogoitin; i++) {
            int False = ham_loc (&goitin[i]); // Phải tạo 1 biến để hứng con số, nhớ gán địa chỉ cho mảng gói tin.
            if (False == 0) {
                danh_sach_ip_pass[a]=goitin[i].IP; // Dùng dấu chấm, vì ta truyền danh sách các gói tin thật vào từ Packet goitin[]. Xem lại dòng 21.
                a++;
            }
            else {
                danh_sach_ip_drop[b]=goitin[i].IP;
                b++;
            }
        }
        // Đã tạo được danh sách các gói tin pass và drop, bây giờ là bước trả về.
        // Mong muốn trả về kết quả danh sách IP và tổng số gói tin đã bị chặn.

    printf("=== DANH SACH CHO QUA (PASS) ===\n");
    for (int i = 0; i < a; i++) {
        printf(" [+] IP: %s\n", danh_sach_ip_pass[i]);
    }

    printf("\n=== DANH SACH BI CHAN (DROP) ===\n");
    for (int i = 0; i < b; i++) {
        printf(" [-] IP: %s\n", danh_sach_ip_drop[i]);
    }

    return b; // Là số lượng gói tin bị chặn, chứ k phải sizeof(mảng), sizeof đo số byte.
                // Nhớ là b chứ k phải b + 1, vì hứng 1 gói là b cộng thêm 1 rồi. 
}

// Lưu ý, đối với mảng, trong C không được tạo mảng rỗng, nếu chưa có thành phần, phải khai trước số lượng thành phần.