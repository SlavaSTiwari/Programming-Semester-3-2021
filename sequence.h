#ifndef SEQUENCE_H_INCLUDED
#define SEQUENCE_H_INCLUDED

/// SEQUENCE~
template <class T>
class Sequence{
    public:
        virtual T GetFirst() const = 0;
        virtual T GetLast() const = 0;
        virtual T Get(int index) const = 0;
        virtual int GetLength() const = 0;
        virtual Sequence<T> *GetSubsequence (int startIndex, int endIndex) = 0;
        virtual Sequence <T> *Concat(Sequence <T> *Seq_2) = 0;
        virtual void Append(const T& item) = 0;
        virtual void Delete_first() = 0;
        virtual void Prepend(const T& item) = 0;
        virtual void Delete_last() = 0;
        virtual void InsertAt(const T& item, int index) = 0;
        virtual void Print() = 0;
        virtual bool Search(Sequence<T> *Subseq) = 0;

        virtual Sequence<T> *Map(T (*Func)(T)) = 0;
        virtual Sequence<T> *Where(bool (*Cond)(T)) = 0;
        virtual T Reduce(T (*Func)(T, T)) = 0;

        virtual bool operator ! () = 0;
        virtual bool operator ==(const Sequence<T> &Seq) const = 0;

};

template <class T>
class ArraySequence : public Sequence<T> {
    private:
        DynamicArray<T> *items;

    public:
        // Constructors:
        ArraySequence(){
            items = new DynamicArray<T>(1);
        }
        ArraySequence(T *aitems, int acount){ // from DynamicArray
            items = new DynamicArray<T>(aitems, acount);
        }
        ArraySequence(LinkedList<T> &aitems){ // from LinkedList
            int acount = aitems.GetLength();
            T *list_arr = new T(acount);
            for(int i=0; i<acount; i++){
                list_arr[i] = aitems.GetIndex(i);
            }
            items = new DynamicArray<T>(list_arr, acount);
        }

        ~ArraySequence(){
            delete items;
        }
        // GETTERS:
        T GetFirst () const override{
            return items->Get(0);
        }

        T GetLast() const override{
            int last = this->GetLength()-1;
            //std::cout << last << std::endl;
            return items->Get(last);
        }

        T Get(int index) const override{
            return items->Get(index);
        }

        int GetLength() const override{
            return items->GetSize();
        }

        int GetCapacity(){
            return items->GetSize*sizeof(T);
        }

        Sequence<T> *GetSubsequence (int startIndex, int endIndex) override{

            Sequence<T> *subSequence = new ArraySequence<T>();
            for(int i = startIndex; i <= endIndex; i++){
                subSequence->Append(this->Get(i));
            }
            return subSequence;
        }

        Sequence <T> *Concat(Sequence<T> *Seq_2) override{
            int i = 0;
            int len = Seq_2->GetLength();
            for(i; i<len; i++){
                this->Append(Seq_2->Get(i));
            }
            return this;
        }

        // SETTERS:
        void Append(const T& item) override{
            if(this->items->GetSize() == 0){
                this->items->Resize(1);
                this->items->Set(item, 0);
            }
            else{
                this->items->Resize(this->items->GetSize()+1);
                this->items->Set(item, this->items->GetSize()-1);
            }
        }

        void Delete_last() override{
            items->Resize(items->GetSize()-1);
        }

        void Prepend(const T& item) override{ // org = 0
            if(this->items->GetSize() == 0){
                this->items->Resize(1); //size = 1
                this->items->Set(item, 0);
                //std::cout << "Size is: " << items->GetSize() << std::endl; //DEBUG
            }
            else{
                this->items->Resize(this->items->GetSize()+1); //size = 2
                //std::cout << "Size is now: " << items->GetSize() << std::endl; // DEBUG
                int i = this->items->GetSize()-2; // i = 0
                for(i; i>=0; i--) {
                    this->items->Set(this->items->Get(i), i+1);

                }
                this->items->Set(item, 0);
            }
        }

        void Delete_first() override{
            int i = 1;
            for(i; i<items->GetSize(); i++){
                items->Set(items->Get(i), i-1);
            }
            items->Resize(items->GetSize()-1);

        }

        void InsertAt(const T& item, int index) override{
            this->items->Set(item, index);
        }

        // MISC~
        void Print() override{
            this->items->Print();
        }

        bool Search(Sequence<T> *Subseq) override{
            int ind_start, ind_end;
            for(int i=0; i<this->GetLength(); i++){
                int sub_count = 0;
                if(this->Get(i) == Subseq->Get(sub_count)){
                    sub_count++;
                    int j=i+1;
                    ind_start = i;
                    while(sub_count<Subseq->GetLength()){
                        if(Subseq->Get(sub_count)==this->Get(j)){
                            sub_count++;
                            j++;
                        }
                        else{break;}
                    }
                    if(sub_count == Subseq->GetLength()){
                        ind_end = ind_start + Subseq->GetLength()-1;
                        std::cout << "Match found from " << ind_start << " to " << ind_end << std::endl;
                        return true;
                    }
                }
            }
            return false;
        }

        Sequence<T> *Map(T (*Func)(T)) override{

            Sequence<T> *Map_Seq = new ArraySequence<T>();
            for(int i=0; i<this->GetLength(); i++){
                T map_item = Func(this->Get(i));
                Map_Seq->Append(map_item);
            }
            std::cout << "Map Succesfull!" << std::endl;

            return Map_Seq;
        }

        Sequence<T> *Where(bool (*Cond)(T)){
            Sequence<T> *where_seq = new ArraySequence<T>();

            for(int i=0; i<this->GetLength(); i++){
                T item = this->Get(i);
                if(Cond(item)){
                    where_seq->Append(item);
                    std::cout << "Condition met at index: " << i <<std::endl;
                }
            }
            return where_seq;
        }

        T Reduce(T (*Func)(T, T)) override{
            T item = this->Get(0);
            for(int i = 1; i<this->GetLength(); i++){
                item = Func(item, this->Get(i));
            }
            return item;
        }

        bool operator ! () override{
            if(this == nullptr){
                return true;
            }
            return false;
        }

        bool operator == (const Sequence<T> &Seq) const override{
            return false;
        }
};

template <class T>
class ListSequence : public Sequence<T> {

    private:
        LinkedList<T> *items;
        // CONSTRUCTORS
    public:
        ListSequence(){
            items = new LinkedList<T>();
        }
        ListSequence(T* aitems, int acount){ // Using Array
            items = new LinkedList<T>();

            int i = 0;
            for(i; i<acount; i++){
                items->Append(aitems[i]);
            }
        }

        ListSequence(LinkedList<T> &aitems){
            items = new LinkedList<T>();

            int acount = aitems.GetLength();
            int i = 0;
            for(i; i<acount; i++){
                items->Append(aitems.GetIndex(i));
            }
        }

        // GETTERS
        T GetFirst() const override{
            return this->items->GetFirst();
        }

        T GetLast() const override{
            return this->items->GetLast();
        }

        T Get(int index) const override{
            return this->items->GetIndex(index);
        }

        int GetLength() const override{
            return this->items->GetLength();
        }

        int GetCapacity() {
            return this->items->GetLength()*sizeof(T);
        }

        Sequence<T> *GetSubsequence(int startIndex, int endIndex) override{
            Sequence<T> *Subseq = new ListSequence( *this->items->GetSublist(startIndex, endIndex) );
            return Subseq;
        }

        Sequence <T> *Concat(Sequence <T> *Seq_2) override{
            int i = 0;
            int len = Seq_2->GetLength();
            for(i; i<len; i++){
                this->Append(Seq_2->Get(i));
            }
            return this;
        }

        // SETTERS:
        void Append(const T& item) override{
            this->items->Append(item);
        }

        void Delete_last() override{
            this->items->Delete_last();
        }

        void Prepend(const T& item) override{
            this->items->Prepend(item);
        }

        void Delete_first() override{
            this->items->Delete_first();
        }

        void InsertAt(const T& item, int index) override{
            this->items->InsertAt(item, index);
        }

        // MISC~
        void Print() override{
            items->Print();
        }

        bool Search(Sequence<T> *Subseq) override{
            int ind_start, ind_end;
            for(int i=0; i<this->GetLength(); i++){
                int sub_count = 0;
                if(this->Get(i) == Subseq->Get(sub_count)){
                    sub_count++;
                    int j=i+1;
                    ind_start = i;
                    while(sub_count<Subseq->GetLength()){
                        if(Subseq->Get(sub_count)==this->Get(j)){
                            sub_count++;
                            j++;
                        }
                        else{break;}
                    }
                    if(sub_count == Subseq->GetLength()){
                        ind_end = ind_start + Subseq->GetLength()-1;
                        std::cout << "Match found from " << ind_start << " to " << ind_end << std::endl;
                        return true;
                    }
                }
            }
            return false;
        }

        Sequence<T> *Map(T (*Func)(T)) override{

            Sequence<T> *Map_Seq = new ListSequence<T>();
            for(int i=0; i<this->GetLength(); i++){
                T map_item = Func(this->Get(i));
                Map_Seq->Append(map_item);
            }
            std::cout << "Map Succesfull!" << std::endl;
            return Map_Seq;
        }

        Sequence<T> *Where(bool (*Cond)(T)) override{
            Sequence<T> *where_seq = new ListSequence<T>();

            for(int i=0; i<this->GetLength(); i++){
                T item = this->Get(i);
                if(Cond(item)){
                    where_seq->Append(item);
                    std::cout << "Condition met at index: " << i <<std::endl;
                }
            }
            return where_seq;
        }

        T Reduce(T (*Func)(T, T)) override{
            T item = this->Get(0);
            for(int i = 1; i<this->GetLength(); i++){
                item = Func(item, this->Get(i));
            }
            return item;
        }

        bool operator ! () override{
            if(this == nullptr){
                return true;
            }
            return false;
        }

        bool operator == (const Sequence<T> &Seq) const override{
            return false;
        }

};

template<class T>
std::ostream& operator <<(std::ostream& os, const Sequence<T>& Obj){
    int i = 0;
    os << "( " << Obj.Get(i);
    i++;
    for(i; i<Obj.GetLength(); i++){
        os << ", " << Obj.Get(i);
    }
    os << " )";
    return os;
}

#endif // SEQUENCE_H_INCLUDED
