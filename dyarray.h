#ifndef DYARRAY_H_INCLUDED
#define DYARRAY_H_INCLUDED

template <class T>
class DynamicArray{
    private:
        T *items;
        int item_size;
    public:
    //Constructors
    DynamicArray(T *aitems, int acount){
        item_size = acount;
        //std::cout << "Sometings off" << std::endl;

        items = new T[acount];
        for(int i = 0; i<acount; i++){
            items[i] = aitems[i];
            //std::cout << "Constructor insert " << items[i] << std::endl; //DEBUG
        }
    }
    DynamicArray(int asize){
        item_size = 0;
        items = new T[asize];
    }

    //Getters
    const T Get(int index){
        if(index > item_size-1){
            std::cout << "\nINDEX OUT OF RANGE\n" << std::endl;
            exit(EXIT_FAILURE);
        }
        else{
            if(!items[index]){
                std::cout << "\nERROR: <in class: DynamicArray>: no value stored at index: " << index << std::endl;
                exit(EXIT_FAILURE);
            }
            else{
                return items[index];
            }
        }
    }

    T *Get_ptr(int index){
        if(index > item_size-1){
            std::cout << "\nINDEX OUT OF RANGE\n" << std::endl;
            exit(EXIT_FAILURE);
        }
        else{
            if(!items[index]){
                std::cout << "\nERROR: <in class: DynamicArray>: no value stored at index: " << index << std::endl;
                exit(EXIT_FAILURE);
            }
            else{
                return &items[index];
            }
        }
    }

    const int GetSize(){
        return item_size;
    }

    //Setters
    void Set(const T& value, int index){
        if(index > item_size-1 && item_size != 0){
            std::cout << "\nERROR: <in class: DynamicArray>:in 'void Set': INDEX OUT OF RANGE\n" << std::endl;
            exit(EXIT_FAILURE);
        }
        else{
            //std::cout << "The value: " << value << " is being set in dyarray.h at index: " << index << std::endl;
            //std::cout << "The size of array is: " << this->GetSize() << std::endl;
            //std::cout << sizeof(items[index]) << " == " << sizeof(value) << std::endl;
            items[index] = value;
        }
    }

    void Resize(int new_size){
        int cnt;
        if(new_size==0){
            T *temp = new T[1];
            this->items = temp;
            this->item_size = 0;
        }
        else{
            if(new_size < this->GetSize()){ cnt = new_size; }
            else{cnt = this->GetSize(); }
            T *temp = new T[new_size];
            for(int i=0; i<cnt; i++){
                temp[i] = items[i];
            }
            this->items = temp;
            item_size = new_size;
        }
        //std::cout << "The item_size in Dyarray is: " << item_size << std::endl; // DEBUG
    }

    // Misc:
    void Print() {
        for(int i=0; i<item_size; i++) {
            //std::cout << "This works?" << std::endl;
            std::cout << items[i] << std::endl;
        }
    }

};

#endif // DYARRAY_H_INCLUDED
