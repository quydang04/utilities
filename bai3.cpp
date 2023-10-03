#include <iostream>
#include <climits>
using namespace std;
// Khai bao mot cau truc danh sach lien ket don
struct node {
    int data;
    node* next;
};
// Tao mot node moi
node* makeNode(int data) {
    node* newNode = new node;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
// Ham tim so mu lon nhat
int findMax(node* head) {
    int max = INT_MIN;
    while (head != NULL) {
        if (head->data > max) {
            max = head->data;
        }
        head = head->next;
    }
    return max;
}
// Ham tim so mu nho nhat
int findMin(node* head) {
    int min = INT_MAX;
    while (head != NULL) {
        if (head->data < min) {
            min = head->data;
        }
        head = head->next;
    }
    return min;
}
// Ham nhap danh sach lien ket don
void nhap(node*& head, int n) {
    cout << "Nhap so luong so mu: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cout << "Nhap so mu thu " << i + 1 << ": ";
        cin >> x;
        node* newNode = makeNode(x);
        if (head == NULL) {
            head = newNode;
        } else {
            node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
}

int main() {
    node* head = NULL;
    int n;
    nhap(head, n);
    // In ra man hinh ket qua cua so mu lon nhat va so mu nho nhat
    if (head == NULL) {
        cout << "Danh sach rong" << endl;
    } else {
        int max = findMax(head);
        int min = findMin(head);
        cout << "So mu lon nhat trong danh sach la: " << max << endl;
        cout << "So mu nho nhat trong danh sach la: " << min << endl;
    }
    // Giai phong bo nho
    while (head != NULL) {
        node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
