#ifndef SORTERS_H_INCLUDED
#define SORTERS_H_INCLUDED

using namespace std::chrono;

/// Bubble Sort:
template <class T>
Sequence<T>* bubble_Sort(Sequence<T>* seq, int (*cmp)(const T&, const T&))
{
    auto start = high_resolution_clock::now();
    bSort_util(seq, cmp);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by bubble_sort: " << duration.count() << " microseconds" << std::endl;

    return seq;
}

template <class T>
void bSort_util(Sequence<T>*& seq, int (*cmp)(const T&,const T&))
{
    int n = seq->GetLength()-1;

    bool swapped = true;
    while(swapped){
        swapped = false;
        for (int i = 0; i < n; i++)
        {
            if( cmp((*seq)[i], (*seq)[i+1]) > 0 )
            {
                std::swap((*seq)[i], (*seq)[i+1]);
                swapped = true;
            }
        }
    }
}

/// Shaker Sort
template <class T>
Sequence<T>* shaker_Sort(Sequence<T>* seq, int (*cmp)(const T&,const T&))
{
    auto start = high_resolution_clock::now();
    sSort_Util(seq, cmp);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by shaker_sort: " << duration.count() << " microseconds" << std::endl;

    return seq;
}

template <class T>
void sSort_Util(Sequence<T>*& seq, int(*cmp)(const T&,const T&) )
{
    bool swapped = true;
    int start = 0;
    int end = seq->GetLength() - 1;

    while (swapped)
    {
        swapped = false;
        for (int i = start; i < end; ++i)
        {
            if(cmp((*seq)[i], (*seq)[i+1]) > 0)
            {
                std::swap((*seq)[i], (*seq)[i+1]);
                swapped = true;
            }
        }
        if(!swapped)
          break;

        swapped = false;
        --end;

        for (int i = end - 1; i >= start; --i)
        {
            if(cmp((*seq)[i], (*seq)[i+1]) > 0)
            {
                std::swap((*seq)[i], (*seq)[i+1]);
                swapped = true;
            }
        }
        ++start;
    }
}

/// Merge Sort:
template <class T>
Sequence<T>* merge_Sort(Sequence<T>* seq, int (*cmp)(const T&,const T&))
{
    auto start = high_resolution_clock::now();
    seq = mSort_Util(seq, cmp);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by merge_sort: " << duration.count() << " microseconds" << std::endl;

    return seq;
}

template <class T>
Sequence<T>* mSort_Util(Sequence<T>* seq, int (*cmp)(const T&,const T&) )
{
    int n = seq->GetLength();
    if(n==1)
    {
        return seq;
    }
    Sequence<T> *seq_A = seq->GetSubsequence( 0, (n/2)-1 );
    Sequence<T> *seq_B = seq->GetSubsequence( (n/2), n-1 );

    seq_A = mSort_Util(seq_A, cmp);
    seq_B = mSort_Util(seq_B, cmp);

    return Merge(seq_A, seq_B, cmp);
}

template <class T>
Sequence<T>* Merge(Sequence<T>* seq_A, Sequence<T>* seq_B, int (*cmp)(const T&,const T&) )
{
    int s = seq_A->GetLength() + seq_B->GetLength();
    Sequence<T> *seq_C = new ListSequence<T>(s);

    while(seq_A->GetLength() != 0 && seq_B->GetLength() != 0)    //SEQ A OR SEQ B HAVE MORE THAN 1 ELEMENTS
    {
        if(cmp((*seq_A)[0], (*seq_B)[0]) > 0)    // SEQ A[0] greater than SEQ B[0].
        {
            seq_C->Append((*seq_B)[0]);
            seq_B->Delete_first();
        }
        else
        {
            seq_C->Append((*seq_A)[0]);
            seq_A->Delete_first();
        }
    }

    // At this point either A or B is empty:
    while(seq_A->GetLength() > 0)    //SEQ A HAS >1 ELEMENTS
    {
        seq_C->Append((*seq_A)[0]);
        seq_A->Delete_first();
    }

    while(seq_B->GetLength() > 0)    //SEQ B HAS >1 ELEMENTS
    {
        seq_C->Append((*seq_B)[0]);
        seq_B->Delete_first();
    }

    return seq_C;
}

/// Quick Sort:
template <class T>
Sequence<T>* quick_Sort(Sequence<T>* seq, int (*cmp)(const T&,const T&) )
{
    auto start = high_resolution_clock::now();
    qSort_Util(seq, 0, seq->GetLength()-1, cmp);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by quick_sort: " << duration.count() << " microseconds" << std::endl;

    return seq;
}

template <class T>
void qSort_Util( Sequence<T>*& seq, int left, int right, int (*cmp)(const T&,const T&) )
{
    if(left>=right)
    {
        return;
    }
    int pivot_loc = Partition(seq, left, right, cmp);

    qSort_Util(seq, left, pivot_loc-1, cmp);
    qSort_Util(seq, pivot_loc+1, right, cmp);
}

template <class T>
int Partition(Sequence<T>*& seq, int left, int right, int (*cmp)(const T&,const T&) )
{
    T pivot = (*seq)[right];
    int i = left - 1;

    for(int j = left; j < right; ++j)
    {
        if(cmp( (*seq)[j], pivot) < 0)
        {
            i++;
            std::swap((*seq)[i], (*seq)[j]);
        }
    }
    std::swap((*seq)[i+1], (*seq)[right]);

    return i+1;
}

template <class T>
int compare(const T &a, const T &b)
{
    if (a < b)
    {
        return -1;
    }
    if (a == b)
    {
        return 0;
    }
    if (a > b)
    {
        return 1;
    }
}

#endif // SORTERS_H_INCLUDED
