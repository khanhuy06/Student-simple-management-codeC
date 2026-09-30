#ifndef PACKETFILTER_H
#define PACKETFILTER_H

typedef struct {
    char IP[16]; 
    int Port;
    char Payload[256];
}Packet;

typedef int (*Packetfilter) (const Packet *goitin);

// Phải khai báo kiểu dữ liệu trước khi đưa vào hàm.

int sql_injection_filter (const Packet *goitin);
int port_filter (const Packet *goitin);

int fire_wall (Packet goitin[], int tongsogoitin, Packetfilter ham_loc);

#endif