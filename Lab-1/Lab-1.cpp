// Compare different types of sorting using 'Sequences' from last semester.

#include<iostream>
#include<chrono>
#include<random>

#include"elem_types.h"
#include"sequence.h"
#include"sorters.h"

template <class T>
void choose_sort(Sequence<T>* my_seq)
{
    int s_choice;
    std::cout << "Enter the sorting method:\n1. Bubble sort\n2. Shaker sort\n3. Merge sort\n4. Quick sort\nYour choice: ";
    s_choice = choose(1,4);

    std::cout << "Unsorted Sequence:" << std::endl;
    //my_seq->Print();

    switch(s_choice)
    {
    case 1:
    {
        std::cout << "\nSorted using bubble sort:" << std::endl;
        Sequence<T> *bubble_Sort_seq = bubble_Sort(my_seq, compare);
        //bubble_Sort_seq->Print();
        delete bubble_Sort_seq;
        break;
    }
    case 2:
    {
        std::cout << "\nSorted using shaker sort:" << std::endl;
        Sequence<T> *shaker_Sort_seq = shaker_Sort(my_seq, compare);
        //shaker_Sort_seq->Print();
        delete shaker_Sort_seq;
        break;
    }
    case 3:
    {
        std::cout << "\nSorted using merge sort:" << std::endl;
        Sequence<T> *merge_Sort_seq = merge_Sort(my_seq, compare);
        //merge_Sort_seq->Print();
        delete merge_Sort_seq;
        break;
    }
    case 4:
    {
        std::cout << "\nSorted using quick sort:" << std::endl;
        Sequence<T> *quick_Sort_seq = quick_Sort(my_seq, compare);
        //quick_Sort_seq->Print();
        delete quick_Sort_seq;
        break;
    }
    default:
    {
        std::cout << "Defaulted to using quick sort:" << std::endl;
        Sequence<T> *quick_Sort_seq = quick_Sort(my_seq, compare);
        quick_Sort_seq->Print();
        delete quick_Sort_seq;
    }
    }
    return;
}

void choose_type()
{
    std::random_device rd;

    int type_choice, seq_choice, n=10000;

    std::cout << "Choose a type:\n1. Dynamic Array\n2. Linked List\nYour choice: ";
    seq_choice = choose(1,2);

    std::cout << "Choose a type:\n1. Integers\n2. Doubles\n3. Complex numbers\n4. Student\n5. Teacher\nYour choice: ";
    type_choice = choose(1,5);

    switch(seq_choice)
    {
    case 1: // Dynamic Array
        switch(type_choice)
        {
        case 1:
        {
            Sequence<int> *my_seq = new ArraySequence<int>(n);
            for(int i = 0; i<n; i++)
            {
                my_seq->Append(rd()%(n-1) + 1);
            }
            choose_sort(my_seq);
            return;
        }
        case 2:
        {
            Sequence<double> *my_seq = new ArraySequence<double>(n);
            for(int i = 0; i<n; i++)
            {
                my_seq->Append(rd()%(n-1) + 1);
            }
            choose_sort(my_seq);
            return;
        }

        case 3:
        {
            Sequence<Complex> *my_seq = new ArraySequence<Complex>(n);
            for(int i = 0; i<n; i++)
            {
                Complex A;
                A.SetReal(rd()%(n-1) + 1);
                A.SetImag(rd()%(n-1) + 1);
                my_seq->Append(A);
            }
            choose_sort(my_seq);
            return;
        }
        case 4:
        {
            Sequence<Student> *my_seq = new ArraySequence<Student>(n);
            for(int i = 0; i<n; i++)
            {
                Student A;
                A.Randomize();
                my_seq->Append(A);
            }
            choose_sort(my_seq);
            return;
        }
        case 5:
        {
            Sequence<Teacher> *my_seq = new ArraySequence<Teacher>(n);
            for(int i = 0; i<n; i++)
            {
                Teacher A;
                A.Randomize();
                my_seq->Append(A);
            }
            choose_sort(my_seq);
            return;
        }
        default:
            std::cout << "An error occurred while choosing" << std::endl;
        return;
    }

    case 2: // Linked List
    {
        switch(type_choice){
        case 1:
        {
        Sequence<int> *my_seq = new ListSequence<int>(n);
            for(int i = 0; i<n; i++)
            {
                my_seq->Append(rd()%(n-1) + 1);
            }
            choose_sort(my_seq);
            return;
        }
        case 2:
        {
            Sequence<double> *my_seq = new ListSequence<double>(n);
            for(int i = 0; i<n; i++)
            {
                my_seq->Append(rd()%(n-1) + 1);
            }
            choose_sort(my_seq);
            return;
        }

        case 3:
        {
            Sequence<Complex> *my_seq = new ListSequence<Complex>(n);
            for(int i = 0; i<n; i++)
            {
                Complex A;
                A.SetReal(rd()%(n-1) + 1);
                A.SetImag(rd()%(n-1) + 1);
                my_seq->Append(A);
            }
            choose_sort(my_seq);
            return;
        }
        case 4:
        {
            Student my_Arr[n];
            for(int i = 0; i<n; i++)
            {
                Student A;
                A.Randomize();
                my_Arr[i] = A;
            }
            Sequence<Student> *my_seq = new ListSequence<Student>(my_Arr, n);
            choose_sort(my_seq);
            return;
        }
        case 5:
        {
            Teacher my_Arr[n];
            for(int i = 0; i<n; i++)
            {
                Teacher A;
                A.Randomize();
                my_Arr[i] = A;
            }
            Sequence<Teacher> *my_seq = new ListSequence<Teacher>(my_Arr, n);
            choose_sort(my_seq);
            return;
        }
        default:
            std::cout << "An error occurred while choosing" << std::endl;
            return;
        }
    break;
    }
    }
    return;
}

int main()
{
    choose_type();

    return 0;
}
