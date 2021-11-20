#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED

template <class T>
class LinkedList{
    private:
        struct node{
            node *next = nullptr;
            T data;
            node *prev = nullptr;
        };
        int length=0;
        struct node *head;

    public:
        //Constructors:
        LinkedList(T *aitems, int acount){
            head = new node;
            head->prev = nullptr;
            head->next = nullptr;
            head->data = aitems[0];
            this->length = acount;

            struct node *last = head;

            for(int i=1; i<acount; i++){
                struct node* last = head;
                struct node* new_node = new node;
                new_node->data = aitems[i];
                std::cout << "Entered data: " << new_node->data << std::endl;  // DEBUG

                new_node->next = nullptr;

                while(last->next != nullptr){
                    last = last->next;
                }

                last->next = new_node;
                new_node->prev = last;
            }
        }

        LinkedList(LinkedList<T> *List){

            node *temp = List->head;

            head = new node;
            head->data = temp->data;
            head->next = nullptr;
            int i = 0;

            struct node *current = new node;
            current = head;

            temp = temp->next;
            while(temp !=nullptr) {
                current->next = new node;
                current = current->next;
                current->data = temp->data;
                std::cout << current->data << std::endl;
                current->next = nullptr;
                temp = temp->next;
                i++;
            }
            this->length = i;
        }

        LinkedList(){
            head = new node;
            //head->data = NULL;
            head->next = nullptr;
            head->prev = nullptr;
            this->length = -1;
            //std::cout << "Length is: " << -1 << std::endl;
        }
        // GETTERS:

        T GetFirst() {
            if(!head->data){
                std::cout << "\nERROR: <in class: LinkedList>: INDEX OUT OF RANGE: empty list" << std::endl;
                exit(EXIT_FAILURE);
            }
            else{
                return head->data;
            }
        }

        T GetLast() {
            node *temp = head;

            if(!(temp->data)){
                std::cout << "\nERROR: <in class: LinkedList>: INDEX OUT OF RANGE: empty list" << std::endl;
                exit(EXIT_FAILURE);
            }
            else{
                while(temp->next != nullptr){
                    temp = temp->next;
                }
                //std::cout << "The length is: " << this->GetLength() << std::endl;
                //std::cout << "Temp data is: " << temp->data << std::endl;
                return temp->data;
            }
        }

        T GetIndex(int index){
            node *temp = head;
            int i = 0;
            while(temp != nullptr){
                if(index == i){
                    return temp->data;
                }
                i++;
                temp = temp->next;
            }
            std::cout << "\nERROR: <in class: LinkedList>: in 'GetIndex': INDEX OUT OF RANGE" << std::endl;
            exit(EXIT_FAILURE);
        }

        LinkedList<T>* GetSublist(int start_index, int end_index){
            int org_len = this->GetLength();
            if(start_index>end_index || start_index<0 || start_index>org_len || end_index<0 || end_index>org_len){
                 std::cout << "\nERROR: <in class: LinkedList>: in 'GetSublist': INDEX ERROR" << std::endl;
                 exit(EXIT_FAILURE);
            }
            LinkedList<T> *Sublist = new LinkedList<T>();
            Sublist->length = 0;

            for(start_index; start_index<=end_index; start_index++){
                Sublist->Append(this->GetIndex(start_index));
            }
            return Sublist;
        }

        int GetLength(){
            if(this->length == -1){return 0;}
            return this->length;
        }

        //SETTERS
        void Append(const T& item){
            if (this->GetLength()==0){
                this->head->data = item;
                this->length = 1;
            }
            else{
                struct node *new_node = new node;
                new_node->data = item;
                new_node->next = nullptr;
                new_node->prev = nullptr;

                struct node *last = head;

                while(last->next != nullptr){
                    last = last->next;
                }
                last->next = new_node;
                new_node->prev = last;
                this->length++;
            }
        }

        void Delete_last(){
            if(this->length==1){
                delete(this->head);
                this->head = new node;
                this->head->next = nullptr;
                this->head->prev = nullptr;
                this->length = -1;
            }
            else{
                node *temp = head;
                while(temp->next->next != nullptr){
                    temp = temp->next;
                }
                delete(temp->next);

                temp->next = nullptr;
                this->length--;
            }
        }

        void Prepend(const T& item){
            if (this->GetLength()==0){
                this->head->data = item;
                this->length = 1;
            }
            else{
                struct node *new_node = new node;
                new_node->data = item;
                new_node->prev = nullptr;
                new_node->next = nullptr;

                head->prev = new_node;
                new_node->next = head;
                head = new_node;
                this->length++;
            }
        }

        void Delete_first(){
            node *temp = head;
            head = head->next;
            delete(temp);
            this->length--;
        }

        void InsertAt(const T& item, int index){
            node *temp = head;
            int i = 0;
            while(temp != nullptr){
                if(index == i){
                    temp->data = item;
                    return;
                }
                i++;
                temp = temp->next;
            }
            this->length++;
        }

        LinkedList <T> *Concat(LinkedList<T> &seclist){
            LinkedList<T> *concat_list = new LinkedList <T>();
            concat_list->head = new node;
            concat_list->head = head;
            node *temp = head;

            while(temp->next != nullptr) {
                //std::cout << "Concat works" << std::endl;

                temp = temp->next;
            }
            temp->next = seclist.head;
            seclist.head->prev = temp;

            this->length = this->GetLength() + seclist->GetLength();

            return concat_list;
        }

        // MISC~
        void Print(){
            node *temp = head;
            while(temp != nullptr){
                std::cout << temp->data << std::endl;
                temp = temp->next;
            }
        }

};

#endif // LINKLIST_H_INCLUDED
