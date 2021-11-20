// Compare different types of sorting using 'Sequences' from last semester.

#include<iostream>
#include<chrono>
#include<random>

#include"dyarray.h"
#include"linklist.h"
#include"elem_types.h"
#include"sequence.h"
#include"sorters.h"

template<class T>
void All_sort(Sequence<T> *my_seq){
    std::cout << "Unsorted Sequence:" << std::endl;
    //my_seq->Print();

    std::cout << "\nSorted using bubble sort:" << std::endl;
    Sequence<T> *bubble_Sort_seq = bubble_Sort(my_seq, compare);
    //bubble_Sort_seq->Print();
    delete bubble_Sort_seq;

    std::cout << "\nSorted using shaker sort:" << std::endl;
    Sequence<T> *shaker_Sort_seq = shaker_Sort(my_seq, compare);
    //shaker_Sort_seq->Print();
    delete shaker_Sort_seq;

    std::cout << "\nSorted using quick sort:" << std::endl;
    Sequence<T> *quick_Sort_seq = quick_Sort(my_seq, compare);
    //quick_Sort_seq->Print();
    delete quick_Sort_seq;

    return;
}

int main(){

    std::random_device rd;

    int choice, n=1000;
    std::cout << "Choose a type:\n1. Integers\n2. Doubles\n3. Complex numbers\nZYour choice:";
    choice = choose(1,5);
    switch(choice){
    case 1:{
        int my_Arr[n];
        for(int i = 0; i<n; i++){
            my_Arr[i] = rd()%(n-1) + 1;
        }

        Sequence<int> *my_seq = new ArraySequence<int>(my_Arr, n);
        All_sort(my_seq);
        break;
    }
    case 2:{
        double my_Arr[n];
        for(int i = 0; i<n; i++){
            my_Arr[i] = rd()%(n-1) + 1;
        }
        Sequence<double> *my_seq = new ArraySequence<double>(my_Arr, n);
        All_sort(my_seq);
        break;

    }
    case 3:{
        Complex my_Arr[n];
        for(int i = 0; i<n; i++){
            Complex *A = new Complex();
            A->SetReal(rd()%(n-1) + 1);
            A->SetImag(rd()%(n-1) + 1);
            my_Arr[i] = *A;
            delete A;
        }
        Sequence<Complex> *my_seq = new ArraySequence<Complex>(my_Arr, n);
        All_sort(my_seq);

        break;
    }

    default:
        std::cout << "An error occurred while choosing" << std::endl;
    }

    return 0;
}
