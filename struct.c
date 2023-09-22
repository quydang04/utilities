#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SinhVien {
    char ma[10];
    char ten[40];
    float dtb;
};

struct node {
    struct SinhVien data;
    struct node* next;
};

void nhapSV(struct node** head, struct SinhVien sv) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = sv;
    newNode->next = *head;
    *head = newNode;
}

void timSVDTB5(struct node* head) {
    struct node* current = head;
    int found = 0;

    while (current != NULL) {
        if (current->data.dtb > 5.0) {
            found = 1;
            printf("MSSV: %s, Ten: %s, DTB: %.2f\n", current->data.ma, current->data.ten, current->data.dtb);
        }

        current = current->next;
    }

    if (!found) {
        printf("Khong tim thay sinh vien nao co diem trung binh lon hon 5.\n");
    }
}

void XoaSVMa(struct node** head, char maX[]) {
    struct node* current = *head;
    struct node* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->data.ma, maX) == 0) {
            if (prev != NULL) {
                prev->next = current->next;
                free(current);
                current = prev->next;
            } else {
                *head = current->next;
                free(current);
                current = *head;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void XoaSVTen(struct node** head, char tenX[]) {
    struct node* current = *head;
    struct node* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->data.ten, tenX) == 0) {
            if (prev != NULL) {
                prev->next = current->next;
                free(current);
                current = prev->next;
            } else {
                *head = current->next;
                free(current);
                current = *head;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void SapXepTheoMa(struct node** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    struct node* current = *head;
    struct node* nextNode = NULL;
    struct SinhVien temp;

    while (current != NULL) {
        nextNode = current->next;

        while (nextNode != NULL) {
            if (strcmp(current->data.ma, nextNode->data.ma) > 0) {
                temp = current->data;
                current->data = nextNode->data;
                nextNode->data = temp;
            }

            nextNode = nextNode->next;
        }

        current = current->next;
    }
}

void InDanhSachKha(struct node* head) {
    struct node* current = head;

    while (current != NULL) {
        if (current->data.dtb >= 6.5 && current->data.dtb <= 7.9) {
            printf("MSSV: %s, Ten: %s, DTB: %.2f\n", current->data.ma, current->data.ten, current->data.dtb);
        }

        current = current->next;
    }
}

struct SinhVien TimSVMax(struct node* head) {
    struct node* current = head;
    struct SinhVien svMax;
    svMax.dtb = -1;

    while (current != NULL) {
        if (current->data.dtb > svMax.dtb) {
            svMax = current->data;
        }

        current = current->next;
    }

    return svMax;
}

struct SinhVien TimSVMinGioi(struct node* head) {
    struct node* current = head;
    struct SinhVien svMin;
    svMin.dtb = 10;

    while (current != NULL) {
        if (current->data.dtb >= 8.0 && current->data.dtb < svMin.dtb) {
            svMin = current->data;
        }

        current = current->next;
    }

    return svMin;
}

struct SinhVien NhapSV() {
    struct SinhVien sv;
    printf("Nhap ma SV: ");
    scanf("%s", sv.ma);
    printf("Nhap ten SV: ");
    scanf("%s", sv.ten);
    printf("Nhap DTB: ");
    scanf("%f", &sv.dtb);
    return sv;
}

void XuatSV(struct SinhVien sv) {
    printf("MSSV: %s, Ten: %s, DTB: %.2f\n", sv.ma, sv.ten, sv.dtb);
}

int main() {
    struct node* head = NULL;
    int chon;

    do {
        printf("\n------ MENU ------\n");
        printf("1. Them sinh vien\n");
        printf("2. Xoa sinh vien theo ma\n");
        printf("3. Xoa tat ca sinh vien theo ten\n");
        printf("4. Sap xep danh sach theo ma SV\n");
        printf("5. In danh sach sinh vien dat loai kha\n");
        printf("6. Tim SV co DTB cao nhat\n");
        printf("7. Tim SV co DTB thap nhat trong cac SV xep loai gioi\n");
        printf("8. Xuat sinh vien co diem trung binh lon hon 5\n");
        printf("9. Xuat danh sach sinh vien\n");
        printf("0. Thoat\n");
        printf("Chon: ");
        scanf("%d", &chon);

        switch (chon) {
            case 1: {
                int n;
                printf("Nhap so luong sinh vien can them: ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    struct SinhVien sv = NhapSV();
                    nhapSV(&head, sv);
                }
                break;
            }
            case 2: {
                char maX[10];
                printf("Nhap ma SV can xoa: ");
                scanf("%s", maX);
                XoaSVMa(&head, maX);
                break;
            }
            case 3: {
                char tenX[40];
                printf("Nhap ten SV can xoa: ");
                scanf("%s", tenX);
                XoaSVTen(&head, tenX);
                break;
            }
            case 4: {
                SapXepTheoMa(&head);
                printf("Danh sach da sap xep theo ma SV.\n");
                break;
            }
            case 5: {
                printf("Danh sach sinh vien dat loai kha:\n");
                InDanhSachKha(head);
                break;
            }
            case 6: {
                struct SinhVien svMax = TimSVMax(head);
                printf("Sinh vien co DTB cao nhat:\n");
                XuatSV(svMax);
                break;
            }
            case 7: {
                struct SinhVien svMinGioi = TimSVMinGioi(head);
                printf("Sinh vien co DTB thap nhat trong cac SV xep loai gioi:\n");
                XuatSV(svMinGioi);
                break;
            }
            case 8: {
                printf("Sinh vien co diem trung binh lon hon 5 la: \n");
                timSVDTB5(head);
                break;
            }
            case 9: {
                printf("Danh sach sinh vien:\n");
                struct node* current = head;
                while (current != NULL) {
                    XuatSV(current->data);
                    current = current->next;
                }
                break;
            }
            case 0: {
                printf("Da thoat chuong trinh!");
                while (head != NULL) {
                    struct node* temp = head;
                    head = temp->next;
                    free(temp);
                }
                break;
            }
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (chon != 0);

    return 0;
}
