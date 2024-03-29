#include <iostream>
using namespace std;

struct node {
    int data;
    node *next;
};

node *makeNode(int n) {
    node *newNode = new node;
    newNode->data = n;
    newNode->next = NULL;
    return newNode;
}

void duyet(node *head) {
    while (head != NULL) {
        cout << head->data << " ";
        head = head->next;
    }
}

int countNode(node *head) {
    int dem = 0;
    while (head != NULL) {
        dem++;
        head = head->next;
    }
    return dem;
}

void pushBack(node *&head, int n) {
    node *newNode = makeNode(n);
    node *temp = head;
    if (head == NULL) {
        head = newNode;
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

void insertList(node *&head) {
    int n;
    cout << "Nhap so luong phan tu: ";
    cin >> n;
    cout << "Nhap cac phan tu: ";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        pushBack(head, x);
    }
}

void chenptu(node *&head, int x, int y) {
    node *temp = head;
    if (head == NULL) {
        return;
    }
    
    while (temp) {
        if (temp->data == x) {
            node *newNode = makeNode(y);
            newNode->next = temp->next;
            temp->next = newNode;
            cout << "Da chen " << y << " sau " << x << endl;
            return;
        }
        temp = temp->next;
    }

    cout << "Khong tim thay phan tu co gia tri " << x << " trong danh sach." << endl;
}

int valueK(node *head, int k) {
    node *temp = head;
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

int findMin(node *head) {
    if (head == NULL) {
        cout << "Danh sach lien ket rong." << endl;
        return -1; 
    }

    int min = head->data;
    node *temp = head->next;

    while (temp != NULL) {
        if (temp->data < min) {
            min = temp->data;
        }
        temp = temp->next;
    }

    return min;
}

void deleteFirst(node *&head, int z) {
    if (head == NULL) {
        return;
    }

    if (head->data == z) {
        node *temp = head;
        head = head->next;
        delete temp;
        return;
    }

    node *prev = head;
    node *current = head->next;

    while (current != NULL) {
        if (current->data == z) {
            prev->next = current->next;
            delete current;
            return; 
        }
        prev = current;
        current = current->next;
    }
}

void sort(node *head) {
    node *temp = head;
    if(head == NULL) {
        return;
    }
    while (temp->next != NULL) {
        node *index = temp->next;
        while(index != NULL) {
            if(index->data < temp->data) {
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
    node *head = NULL;
    int choice, x, y, k, z;
    int res;
    do {
    	cout << "\n------ MENU ------\n"
        cout << "1. Them phan tu\n";
        cout << "2. Chen phan tu\n";
        cout << "3. In danh sach\n";
        cout << "4. Dem so phan tu\n";
        cout << "5. Tim gia tri tai vi tri k\n";
        cout << "6. Tim phan tu nho nhat\n";
        cout << "7. Xoa phan tu\n";
        cout << "8. Sap xep tang dan\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice) {
            case 1:
                insertList(head);
                break;
            case 2:
                cout << "Nhap gia tri can tim de chen: ";
                cin >> x;
                cout << "Nhap gia tri can chen: ";
                cin >> y;
                chenptu(head, x, y);
                break;
            case 3:
                cout << "Danh sach: ";
                duyet(head);
                break;
            case 4:
                cout << "So node co trong danh sach: " << countNode(head);
                break;
            case 5:
                cout << "Nhap vi tri k: ";
                cin >> k;
                res = valueK(head, k);
                if (res != -1) {
                    cout << "Gia tri node thu " << k << ": " << res << endl;
                } else {
                    cout << "Khong tim thay gia tri node thu " << k << endl;
                }
                break;
            case 6:
                cout << "Phan tu nho nhat trong danh sach la: " << findMin(head) << endl;
                break;
            case 7:
                cout << "Nhap phan tu can xoa: ";
                cin >> z;
                deleteFirst(head, z);
                cout << "Danh sach sau khi xoa la: ";
                duyet(head);
                break;
            case 8:
                sort(head);
                cout << "Danh sach duoc sap xep tang dan: ";
                duyet(head);
                break;
            case 0:
                cout << "Ket thuc chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le. Vui long chon lai.\n";
        }
    } while (choice != 0);

    // Giai phong bo nho
    while (head) {
        node *temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
