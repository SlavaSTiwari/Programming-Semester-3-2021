#ifndef SEQUENCE_H_INCLUDED
#define SEQUENCE_H_INCLUDED

/// SEQUENCE~
template <class T>
class Sequence
{
    public:
        virtual const T& GetFirst() = 0;
        virtual const T& GetLast()= 0;
        virtual const T& Get(int index) = 0;
        virtual int GetLength() const = 0;
        virtual Sequence<T> *GetSubsequence (int startIndex, int endIndex) = 0;
        virtual void Append(const T& item) = 0;
        virtual void Delete_first() = 0;
        virtual void Prepend(const T& item) = 0;
        virtual void Delete_last() = 0;
        virtual void InsertAt(const T& item, int index) = 0;
        virtual void Print() = 0;

        virtual bool operator ! () = 0;
        virtual bool operator ==(const Sequence<T> &Seq) const = 0;
        virtual const T& operator[](int index) const = 0;
        virtual T& operator[](int index) = 0;

};

template <class T>
class ArraySequence : public Sequence<T>
{
    private:
        T *items;
        int item_size;
        int item_capacity;

    public:
        // Constructors:
        ArraySequence(T *aitems, int acount) // from DynamicArray
        {
            item_size = acount;
            item_capacity = acount*sizeof(T);
            items = new T[acount];
            for(int i = 0; i<acount; i++)
            {
                items[i] = aitems[i];
            }
        }
        ArraySequence(int acount)
        {
            item_size = 0;
            item_capacity = acount;
            items = new T[acount];
        }

        ~ArraySequence()
        {
            delete []items;
        }

        void Resize(int new_size)
        {
            int cnt;
            if(new_size==0)
            {
                T *temp = new T[1];
                this->items = temp;
                this->item_size = 0;
            }
            else
            {
                if(new_size < item_size)
                {
                    cnt = new_size;
                }
                else
                {
                    cnt = item_size;
                }
                T *temp = new T[new_size];
                for(int i=0; i<cnt; i++)
                {
                    temp[i] = items[i];
                }
                item_size = cnt;
                item_capacity = new_size;
                delete [] items;
                items = temp;
            }
        }

        // GETTERS:
        const T& GetFirst() override
        {
            return items[0];
        }

        const T& GetLast() override
        {
            int last = item_size-1;
            if(last<0){last = 0;}
            return items[last];
        }

        const T& Get(int index) override
        {
            return items[index];
        }

        int GetLength() const override
        {
            return item_size;
        }

        int GetCapacity()
        {
            return item_capacity;
        }

        Sequence<T> *GetSubsequence(int start, int endi) override
        {
            auto *subSequence = new ArraySequence<T>(endi-start+1);
            for(int i = start; i <= endi; i++)
            {
                subSequence->Append(items[i]);
            }
            return subSequence;
        }

        // SETTERS:
        void Append(const T& item) override
        {
            if (item_capacity > item_size)
            {
                item_size++;
                items[item_size-1] = item;
            }
            else
            {
                this->Resize(item_size + 1);
                item_size++;
                items[item_size - 1] = item;
            }
        }

        void Delete_last() override
        {
            item_size--;
        }

        void Prepend(const T& item) override
        {
            if(item_size == 0)
            {
                this->Resize(1);
                items[0] = item;
            }
            else{
                this->Resize(item_size+1);
                int i = this->GetLength()-2;
                for(i; i>=0; i--)
                {
                    items[i+1] = items[i];
                }
                items[0] = item;
            }
        }

        void Delete_first() override
        {
            int i = 1;
            for(i; i<item_size; i++)
            {
                items[i-1] = items[i];
            }
            item_size--;
        }

        void InsertAt(const T& item, int index) override
        {
            items[index] = item;
        }

        // MISC~
        void Print() override
        {
            for(int i=0; i<item_size; i++)
            {
                std::cout << items[i] << ", \n";
            }
            std::cout << std::endl;
        }

        bool operator ! () override
        {
            if(this == nullptr)
            {
                return true;
            }
            return false;
        }

        bool operator == (const Sequence<T> &Seq) const override
        {
            return false;
        }

        const T& operator[](int index) const override
        {
            return items[index];
        }

        T& operator[](int index) override
        {
            return items[index];
        }
};

template <class T>
class ListSequence : public Sequence<T>
{
private:
	struct node
	{
		struct node* prev;
		T data;
		struct node* next;
	};
	struct node* head;
	int list_length;
	int list_capacity;

public:
	// Constructors
	ListSequence(int acount)
	{
		head = new struct node;
		head->prev = nullptr;
		head->next = nullptr;

		struct node* last = head;
		for (int i = 1; i < acount; i++)
		{
			struct node* new_node = new struct node;
			new_node->prev = last;
			new_node->next = nullptr;

			last->next = new_node;
			last = last->next;
		}
		list_length = 0;
		list_capacity = acount;
	}

	ListSequence(T* arr, int acount)
	{
		head = new struct node;
		head->prev = nullptr;
		head->next = nullptr;
		head->data = arr[0];

		struct node* last = head;
		for (int i = 1; i < acount; i++)
		{
			struct node* new_node = new struct node;
			new_node->prev = last;
			new_node->next = nullptr;
			new_node->data = arr[i];

			last->next = new_node;
			last = last->next;
		}
		list_length = 0;
		list_capacity = acount;
	}

	const T& GetFirst() override
	{
		return head->data;
	}

	const T& GetLast() override
	{
		struct node* temp = head;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		return temp->data;
	}

	const T& Get(int index) override
	{
		struct node* temp = head;
		for (int i = 0; i < index; i++)
		{
			temp = temp->next;
		}
		return temp->data;
	}

	int GetLength() const override
	{
		return list_length;
	}

	ListSequence<T>* GetSubsequence(int start, int end) override
	{
		int org_len = list_length;
		if (start > end || start<0 || start>org_len || end<0 || end>org_len)
        {
			std::cout << "\nERROR: <in class: LinkedList>: in 'GetSublist': INDEX ERROR" << std::endl;
			exit(EXIT_FAILURE);
		}

		ListSequence<T>* Sublist = new ListSequence<T>(end-start+1);

		for (int i = start; i <= end; i++)
        {
			Sublist->Append(this->Get(i));
		}
		return Sublist;
	}

	// Setters
	void Append(const T& item) override
	{
		if (list_capacity > list_length)
		{
			list_length++;
			struct node* temp = head;
			for (int i = 1; i < list_length; i++)
			{
				temp = temp->next;
			}
			temp->data = item;
		}
		else
		{
			struct node* temp = head;
			while (temp->next != nullptr) {
				temp = temp->next;
			}

			struct node* new_node = new node;
			new_node->data = item;
			new_node->next = nullptr;
			new_node->prev = temp;
			temp->next = new_node;

			list_length++;
			list_capacity++;
		}
	}

	void Prepend(const T& item) override
	{
		struct node* temp = new struct node;
		temp->prev = nullptr;
		temp->next = head;
		temp->data = item;

		head->prev = temp;
		head = temp;
		list_length++;
		list_capacity++;
	}

	void InsertAt(const T& item, int index) override
	{
		struct node* temp = head;
		for (int i = 0; i < index; i++)
		{
			temp = temp->next;
		}
		temp->data = item;
	}

	void Delete_last() override
	{
	    if (head->next == nullptr)
		{
			delete head;
			list_length = 0;
			list_capacity = 0;
			return;
		}
		struct node* temp = head;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		delete temp;
		list_length--;
		list_capacity--;
		return;
	}

	void Delete_first() override
	{
	    if (head->next == nullptr)
		{
			delete head;
			list_length = 0;
			list_capacity = 0;
			return;
		}
		struct node* temp = head;
		head = head->next;
		head->prev = nullptr;
		delete temp;
		list_length--;
		list_capacity--;
		return;
	}

	bool operator ! () override
	{
		if (this == nullptr)
		{
			return true;
		}
		return false;
	}

	bool operator == (const Sequence<T>& Seq) const override
	{
		return false;
	}

	const T& operator [] (int index) const override
	{
		struct node* temp = head;
		for (int i = 0; i < index; i++)
		{
			temp = temp->next;
		}
		return temp->data;
	}

	T& operator [] (int index) override
	{
		struct node* temp = head;
		for (int i = 0; i < index; i++)
		{
			temp = temp->next;
		}
		return temp->data;
	}

	void Print()
	{
		struct node* temp = head;
		while (temp != nullptr)
		{
			std::cout << temp->data << std::endl;
			temp = temp->next;
		}
	}

};

template<class T>
std::ostream& operator <<(std::ostream& os, const Sequence<T>& Obj)
{
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
