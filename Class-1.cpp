#include<iostream>
#include<string>
#include<vector>

  // QUESTION 1

std::string Find_longest(std::string input){

    char out, curr;
    int len_out=1, len_curr=1;

    for(int i=0; i<input.length()-1; i++){
      if(input[i]==input[i+1]){
        curr = input[i];
        len_curr++;
      }
      if(len_curr > len_out){
        out = curr;
        len_out = len_curr;
      }
      if(input[i]!=input[i+1]){
        curr = input[i+1];
        len_curr = 1;
      }
    }
    return std::string(len_out, out);
}

  // QUESTION 2

void CocktailSort(int a[], int n){

    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        swapped = false;
        for (int i = start; i < end; ++i) {
          if (a[i] > a[i + 1]) {
            std::swap(a[i], a[i + 1]);
            swapped = true;
          }
        }
        if (!swapped)
          break;

        swapped = false;
        --end;

        for (int i = end - 1; i >= start; --i) {
          if (a[i] > a[i + 1]) {
            std::swap(a[i], a[i + 1]);
            swapped = true;
          }
        }

        ++start;
    }
}

void printArray(int a[], int n){
    for (int i = 0; i < n; i++){
        std::cout << a[i] << ", ";
    }
    std::cout << std::endl;
}

  // QUESTION 3
struct List{
    int data;
    List *next;
};

struct List *new_node(int data){
    struct List *New = new List;
    New->data=data;
    New->next = nullptr;
    return New;
}

int List_size(struct List *org){

    if(org==nullptr){
        return 0;
    }
    int size = 1;
    while(org->next!=nullptr){
        org = org->next;
        size++;
    }
    return size;
}

void insert_at(struct List *org, int data, int index){

    int i=0;

    if(index > List_size(org)){
        std::cout << "INDEX OUT OF RANGE" << std::endl;
        return;
    }
    struct List *New = new_node(data);

    if(org == nullptr){
        org = New;
        return;
    }
    if(index == 0){
        New->next = org;
        org = New;
        return;
    }

    while(i<index-1){
        org = org->next;
        i++;
    }

    struct List *temp = org->next;

    org->next = New;
    New->next = temp;
    return;
}

void Append_node(struct List *curr, int data){

    if(curr==nullptr){
        curr=new_node(data);
        return;
    }
    while(curr->next!=nullptr){
        curr = curr->next;
    }

    curr->next = new_node(data);
    return;
}

void Prepend_node(struct List *head, int data){
    if(head==nullptr){
        head=new_node(data);
        return;
    }
    struct List *New = new List;
    New->data = data;
    New->next = head;
    head = New;
    return;
}

struct List* List_reverse(struct List *org){
    struct List *curr, *next, *prev;

    curr = org;
    next = org;
    prev = nullptr;

    while(curr != nullptr){
        next = next->next;

        curr->next =prev;

        prev = curr;
        curr = next;
    }
    return prev;
}

void List_print(struct List *curr){
    if(curr==nullptr){
        std::cout <<"LIST IS EMPTY OR NOT FOUND" << std::endl;
        return;
    }

    while(curr!=nullptr){
        std::cout << curr->data << ", ";
        curr = curr->next;
    }
}

  // QUESTION 4

class Node{
public:
    Node(int val)
    {
        data = val;
        left = 0;
        right = 0;
    }

    int data;
    Node* left;
    Node* right;
};

void Add(Node** root, Node* n){

    if(!*root){
        *root = n;
        return;
    }
    if((*root)->data < n->data){
        Add(&(*root)->right, n);
    }
    else{
        Add(&(*root)->left, n);
    }
}

void Print(Node* node){
    if (!node)  return;
    Print(node->left);
    std::cout << node->data << ", ";
    Print(node->right);
}

void Leaf_sum(Node *root, int& sum){
    if (!root){
        return;
    }

    if (!root->left && !root->right){
        sum += root->data;
    }

    Leaf_sum(root->left, sum);
    Leaf_sum(root->right, sum);
}

int main(){

  // QUESTION 1
  std::cout << "QUESTION 1\n" << std::endl;

  std::string my_string = "aabbbbccc";
  std::cout << "Longest repeating combination: " << Find_longest(my_string) << std::endl;

  // QUESTION 2
  std::cout << "\nQUESTION 2\n" << std::endl;

  int arr[] = {3, 5, 1, 4, 2, 8, 0, 2, 6, 9, 12, -1};
  int len_arr = sizeof(arr) / sizeof(arr[0]);

  CocktailSort(arr, len_arr);
  std::cout << "Sorted array:" << std::endl;
  printArray(arr, len_arr);

  // QUESTION 3
  std::cout << "\nQUESTION 3\n" << std::endl;

  struct List *my_list = new_node(5);
  struct List *rev_list = new List;

  Append_node(my_list, 2);
  Append_node(my_list, 8);
  Append_node(my_list, 3);
  Append_node(my_list, 1);
  Prepend_node(my_list, -1000);

  insert_at(my_list, 100, 1);

  std::cout << "List: ";
  List_print(my_list);

  std::cout << "\nREVERSE of list: ";
  rev_list = List_reverse(my_list);
  List_print(rev_list);

  // QUESTION 4
  std::cout << "\n\nQUESTION 4\n" << std::endl;

  int sum=0;
  Node* root = 0;

  Add(&root, new Node(5));
  Add(&root, new Node(-6));
  Add(&root, new Node(-3));
  Add(&root, new Node(12));
  Add(&root, new Node(20));
  Add(&root, new Node(-4));

  Print(root);

   Leaf_sum(root, sum);
   std::cout << "\nThe sum of all leaf nodes: " << sum << std::endl;
  return 0;
}
