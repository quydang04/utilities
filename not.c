#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* makeNode(int n) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = n;
    newNode->next = NULL;
    return newNode;
}

void duyet(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
}

int countNode(struct Node* head) {
    int dem = 0;
    while (head != NULL) {
        dem++;
        head = head->next;
    }
    return dem;
}

void pushBack(struct Node** head, int n) {
    struct Node* newNode = makeNode(n);
    struct Node* temp = *head;
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    if (temp->next == NULL) {
        temp->next = newNode;
        return;
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void insertList(struct Node** head) {
    int n;
    printf("Nhap so luong phan tu: ");
    scanf("%d", &n);
    printf("Nhap cac phan tu: ");
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        pushBack(head, x);
    }
}

void chenptu(struct Node** head, int x, int y) {
    struct Node* temp = *head;
    if (*head == NULL) {
        return;
    }

    while (temp != NULL) {
        if (temp->data == x) {
            struct Node* newNode = makeNode(y);
            newNode->next = temp->next;
            temp->next = newNode;
            printf("Da chen %d sau %d\n", y, x);
            return;
        }
        temp = temp->next;
    }

    printf("Khong tim thay phan tu co gia tri %d trong danh sach.\n", x);
}

int valueK(struct Node* head, int k) {
    struct Node* temp = head;
    int dem = 0;

    while (temp != NULL) {
        if (dem == k) {
            return temp->data;
        }
        temp = temp->next;
        dem++;
    }

    return -1;
}

int findMin(struct Node* head) {
    if (head == NULL) {
        printf("Danh sach lien ket rong.\n");
        return -1;
    }

    int minVal = head->data;
    struct Node* temp = head->next;

    while (temp != NULL) {
        if (temp->data < minVal) {
            minVal = temp->data;
        }
        temp = temp->next;
    }

    return minVal;
}

void deleteFirst(struct Node** head, int z) {
    if (*head == NULL) {
        return;
    }

    if ((*head)->data == z) {
        struct Node* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    struct Node* prev = *head;
    struct Node* current = (*head)->next;

    while (current != NULL) {
        if (current->data == z) {
            prev->next = current->next;
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void sort(struct Node* head) {
    struct Node* temp = head;
    if (head == NULL) {
        return;
    }
    while (temp->next != NULL) {
        struct Node* index = temp->next;
        while (index != NULL) {
            if (index->data < temp->data) {
                int tam = temp->data;
                temp->data = index->data;
                index->data = tam;
            }
            index = index->next;
        }
        temp = temp->next;
    }
}

int main() {
    struct Node* head = NULL;
    int choice, x, y, k, z;
    int res;
    do {
        printf("------ MENU ------\n");
        printf("1. Them phan tu\n");
        printf("2. Chen phan tu\n");
        printf("3. In danh sach\n");
        printf("4. Dem so phan tu\n");
        printf("5. Tim gia tri tai vi tri k\n");
        printf("6. Tim phan tu nho nhat\n");
        printf("7. Xoa phan tu\n");
        printf("8. Sap xep tang dan\n");
        printf("0. Thoat\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insertList(&head);
                break;
            case 2:
                printf("Nhap gia tri can tim de chen: ");
                scanf("%d", &x);
                printf("Nhap gia tri can chen: ");
                scanf("%d", &y);
                chenptu(&head, x, y);
                break;
            case 3:
                printf("Danh sach: ");
                duyet(head);
                printf("\n");
                break;
            case 4:
                printf("So node co trong danh sach: %d\n", countNode(head));
                break;
            case 5:
                printf("Nhap vi tri k: ");
                scanf("%d", &k);
                res = valueK(head, k);
                if (res != -1) {
                    printf("Gia tri node thu %d: %d\n", k, res);
                } else {
                    printf("Khong tim thay gia tri node thu %d\n", k);
                }
                break;
            case 6:
                printf("Phan tu nho nhat trong danh sach la: %d\n", findMin(head));
                break;
            case 7:
                printf("Nhap phan tu can xoa: ");
                scanf("%d", &z);
                deleteFirst(&head, z);
                printf("Danh sach sau khi xoa la: ");
                duyet(head);
                printf("\n");
                break;
            case 8:
                sort(head);
                printf("Danh sach duoc sap xep tang dan: ");
                duyet(head);
                printf("\n");
                break;
            case 0:
                printf("Ket thuc chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (choice != 0);

    // Giai phong bo nho
    while (head) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
