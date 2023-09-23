#include <stdio.h>
#include <string.h>

#define MAX_QUEUE_SIZE 100

struct BenhNhan {
    int soThuTu;
    char hoTen[50];
    int tuoi;
};

struct HangDoi {
    struct BenhNhan danhSach[MAX_QUEUE_SIZE];
    int front, rear;
    int soLuongDaKham;
};

void initQueue(struct HangDoi *queue) {
    queue->front = -1;
    queue->rear = -1;
    queue->soLuongDaKham = 0;
}

int isQueueEmpty(struct HangDoi *queue) {
    return (queue->front == -1 && queue->rear == -1);
}

int isQueueFull(struct HangDoi *queue) {
    return ((queue->rear + 1) % MAX_QUEUE_SIZE == queue->front);
}

void themBenhNhan(struct HangDoi *queue, char *hoTen, int tuoi) {
    if (isQueueFull(queue)) {
        printf("Hang doi da day, khong the them benh nhan moi.\n");
        return;
    }

    struct BenhNhan bn;
    bn.soThuTu = (queue->rear == -1) ? 1 : queue->danhSach[queue->rear].soThuTu + 1;
    strncpy(bn.hoTen, hoTen, sizeof(bn.hoTen));
    bn.tuoi = tuoi;

    if (isQueueEmpty(queue)) {
        queue->front = 0;
        queue->rear = 0;
    } else {
        queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
    }

    queue->danhSach[queue->rear] = bn;
    printf("%s da duoc them vao hang doi.\n", bn.hoTen);
}

void layBenhNhanTiepTheo(struct HangDoi *queue) {
    if (isQueueEmpty(queue)) {
        printf("Hang doi rong, khong co benh nhan nao.\n");
        return;
    }

    struct BenhNhan bn = queue->danhSach[queue->front];
    printf("Benh nhan tiep theo la: STT %d, Ten: %s, Tuoi: %d tuoi.\n", bn.soThuTu, bn.hoTen, bn.tuoi);

    queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
    if (queue->front == (queue->rear + 1) % MAX_QUEUE_SIZE) {
        queue->front = -1;
        queue->rear = -1;
    }
    queue->soLuongDaKham++;
}

void soLuongDaKham(struct HangDoi *queue) {
    printf("So luong benh nhan da kham: %d\n", queue->soLuongDaKham);
    if (queue->soLuongDaKham > 0) {
        for (int i = 0; i < queue->soLuongDaKham; i++) {
            struct BenhNhan bn = queue->danhSach[i];
            printf("STT %d, Ten: %s, Tuoi: %d tuoi.\n", bn.soThuTu, bn.hoTen, bn.tuoi);
        }
    }
}

void soLuongChuaKham(struct HangDoi *queue) {
    if (isQueueEmpty(queue)) {
        printf("So luong benh nhan chua kham: 0\n");
    } else {
        int soLuongChuaKham = ((queue->rear - queue->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE) + 1;
        printf("So luong benh nhan chua kham: %d\n", soLuongChuaKham);
        for (int i = queue->front; i <= queue->rear; i++) {
            struct BenhNhan bn = queue->danhSach[i];
            printf("STT %d, Ten: %s, Tuoi: %d tuoi.\n", bn.soThuTu, bn.hoTen, bn.tuoi);
        }
    }
}

void xuatDanhSachChoKham(struct HangDoi *queue) {
    if (isQueueEmpty(queue)) {
        printf("Hang doi rong, khong co benh nhan nao cho kham.\n");
        return;
    }

    printf("Danh sach benh nhan con cho kham:\n");
    int i = queue->front;
    while (i != queue->rear) {
        struct BenhNhan bn = queue->danhSach[i];
        printf("STT %d, Ten: %s, Tuoi: %d tuoi.\n", bn.soThuTu, bn.hoTen, bn.tuoi);
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
    struct BenhNhan bn = queue->danhSach[i];
    printf("STT %d, Ten: %s, Tuoi: %d tuoi.\n", bn.soThuTu, bn.hoTen, bn.tuoi);
}

int main() {
    struct HangDoi queue;
    int choice;

    initQueue(&queue);

    do {
        printf("\nMENU:\n");
        printf("1. Them benh nhan\n");
        printf("2. Lay benh nhan tiep theo\n");
        printf("3. So luong benh nhan da kham\n");
        printf("4. So luong benh nhan chua kham\n");
        printf("5. Xuat danh sach benh nhan con cho kham\n");
        printf("0. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                fflush(stdin);
                char hoTen[50];
                int tuoi;
                printf("Nhap ho ten benh nhan: ");
                fgets(hoTen, sizeof(hoTen), stdin);
                hoTen[strlen(hoTen) - 1] = '\0'; // Loai bo ky tu newline
                printf("Nhap tuoi benh nhan: ");
                scanf("%d", &tuoi);
                themBenhNhan(&queue, hoTen, tuoi);
                break;
            }
            case 2:
                layBenhNhanTiepTheo(&queue);
                break;
            case 3:
                soLuongDaKham(&queue);
                break;
            case 4:
                soLuongChuaKham(&queue);
                break;
            case 5:
                xuatDanhSachChoKham(&queue);
                break;
            case 0:
                printf("Ket thuc chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long nhap lai.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}
