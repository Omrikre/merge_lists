#include <iostream>

struct Node {
    int val;
    Node* next = nullptr;
};

Node* mergeLists(Node* list1, Node* list2) {
    if (list1 == nullptr) return list2;
    if (list2 == nullptr) return nullptr;

    // list head
    Node* dummyHead = new Node;
    Node* mergedList = nullptr;
    mergedList = dummyHead;
    Node* ptrMrg = dummyHead, * ptr1 = list1, * ptr2 = list2;


    while ((ptr1 != nullptr) && (ptr2 != nullptr)) {
        Node* currNode = new Node;
        ptrMrg->next = currNode;
        ptrMrg = currNode;
        if (ptr1->val < ptr2->val) {
            ptrMrg->val = ptr1->val;
            ptr1 = ptr1->next;
        }
        else {
            ptrMrg->val = ptr2->val;
            ptr2 = ptr2->next;
        }
    }

    // add the rest of the list
    while (ptr1 != nullptr) {
        Node* currNode = new Node;
        ptrMrg->next = currNode;
        ptrMrg = currNode;
        ptrMrg->val = ptr1->val;
        ptr1 = ptr1->next;
    }
    while (ptr2 != nullptr) {
        Node* currNode = new Node;
        ptrMrg->next = currNode;
        ptrMrg = currNode;
        ptrMrg->val = ptr2->val;
        ptr2 = ptr2->next;
    }

    // free dummy head
    mergedList = mergedList->next;
    free(dummyHead);

    return mergedList;
}

bool checkDescending(Node* head) {
    if (head == nullptr)
        return false;

    int headVal = head->val;
    Node* comp = head->next;

    while ((comp != nullptr) && (comp->val == headVal))
        comp = comp->next;

    // all vals are the same (or only 1 node)
    if (comp == nullptr)
        return false;

    return (headVal > comp->val); // the list is descending
}

Node* removeDup(Node* head) {
    Node* curr = head;
    while (curr != nullptr && curr->next != nullptr) {
        if (curr->val == curr->next->val) {
            Node* temp = curr->next;
            curr->next = curr->next->next;
            free(temp);
        }
        else {
            curr = curr->next;
        }
    }
    return head;
}

void freeList(Node* head) {
    Node* currNode = head, * tmpPtr;
    while (currNode != nullptr){
        tmpPtr = currNode;
        currNode = currNode->next;
        delete tmpPtr;
    }
}

void printList(Node* head) {
    Node* curr = head;
    while (curr != nullptr) {
        std::cout << curr->val << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

Node* reverseList(Node* head) {
    Node* prev = nullptr;
    Node* curr = head;
    while (curr != nullptr) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

bool isListAscending(Node* head) {
    Node* curr = head;
    while (curr != nullptr && curr->next != nullptr) {
        if (curr->val > curr->next->val) {
            return false;
        }
        curr = curr->next;
    }
    return true;
}

bool isListDecending(Node* head) {
    Node* curr = head;
    while (curr != nullptr && curr->next != nullptr) {
        if (curr->val < curr->next->val) {
            return false;
        }
        curr = curr->next;
    }
    return true;
}

Node* readSortedList() {
    Node* head = new Node, *currPtr = head;
    int num;
    std::cout << "Enter a sorted list of integers, one at a time. Enter to stop." <<std::endl;
    while (std::cin >> num) {
        Node* new_node = new Node{ num, nullptr };
        currPtr->next = new_node;
        currPtr = currPtr->next;
        if (std::cin.peek() == '\n') {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    Node* list = head->next;
    delete head;
    if ((!isListAscending(list)) && (!isListDecending(list))) {
        std::cout << "Not Sorted!" << std::endl;
        freeList(list);
        exit(1);
    }
    return list;
}




int main() {
    // list 1
    std::cout << "List 1:" << std::endl;
    Node* list1 = readSortedList();
    // list 2 
    std::cout << "List 2:" << std::endl;
    Node* list2 = readSortedList();

    // check if descending. reveres if needed
    if (checkDescending(list1))
        list1 = reverseList(list1);
    if (checkDescending(list2))
        list2 = reverseList(list2);

    // merge 2 ascending lists
    Node* mergedList = mergeLists(list1, list2);
    
    // remove duplicates
    mergedList = removeDup(mergedList);

    // print the merged list
    printList(mergedList);

    // free memory
    freeList(list1);
    freeList(list2);
    freeList(mergedList);

    return 0;
}