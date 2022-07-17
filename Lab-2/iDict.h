#pragma once

#include<iostream>
#include<vector>
#include<unordered_map>


template<class TKey,class TValue>
class IDictionary		// HashTable implementation
{
private:
	struct element
	{
		TKey key;
		TValue value;
		bool isUsed = false;
		bool isDeleted = false;
	};

	std::vector<element> Dict;
	int Capacity = 0;
	int Count = 0;
	bool checkPrime(int n) 
	{
		if (n == 2 || n == 3)
			return true;

		if (n <= 1 || n % 2 == 0 || n % 3 == 0)
		{
			return false;
		}

		for (int i = 5; i * i <= n; i += 6)
		{
			if (n % i == 0 || n % (i + 2) == 0)
				return false;
		}
		return true;
	}

public:
	IDictionary()
	{
		Capacity = 7;
		Dict.resize(Capacity);
	}

	IDictionary(int Size)
	{
		Capacity = Size;
		Dict.resize(Capacity);
	}

	int hash_Function(const TKey& key)
	{
		return std::hash<TKey>{}(key) % Capacity;
	}


	double get_Count() const	// No. of actually existing elements
	{
		return this->Count;
	}

	double get_Capacity() const	 // Total capacity in the Dictionary 
	{
		return this->Capacity;
	}

	bool is_Empty(const int& index) const
	{
		return !Dict[index].isUsed || Dict[index].isDeleted;
	}

	bool is_Deleted(const int& index) const
	{
		return Dict[index].isDeleted;
	}

	TValue& Get(const TKey& key)
	{
		if (!this->is_Empty( hash_Function(key) ) )
		{
			return Dict[hash_Function(key)].value;
		}
		
	}

	bool contains_Key(const TKey& key)
	{
		return (Dict[hash_Function(key)].key == key);
	}

	void Resize() 
	{
		int old_cap = this->Capacity;
		int new_cap = this->Capacity * 2;
		bool isPrime = false;
		while (isPrime == false)		// Find the closest Prime number
		{
			new_cap++;
			isPrime = checkPrime(new_cap);
		}
		std::vector<element> newDict(new_cap);
		//std::cout << "Hash-table resized to: " << new_cap << std::endl;

		Dict.resize(new_cap);
		this->Capacity = new_cap;

		for (int i = 0; i < old_cap; i++)
		{
			if (Dict[i].isUsed && !Dict[i].isDeleted)			// Move element from old index
			{													// to new hash index
				size_t new_hash = hash_Function(Dict[i].key);
				newDict[new_hash] = Dict[i];
			}
		}
		Dict.clear();
		Dict = newDict;
	}

	void Add(const TKey& key, const TValue& data)
	{
		double loadFactor = get_Count() / get_Capacity();
		//std::cout << "Load Factor: " << loadFactor << std::endl;
		if (loadFactor > 0.7)		// Never need to fill a HashTable to 100%, <70% is ideal.
		{
			this->Resize();
		}
		size_t hash = hash_Function(key);

		while (Dict[hash].isUsed && !Dict[hash].isDeleted)
		{
			hash = (hash * 3) % static_cast<int>(Capacity);
		}
		//std::cout << "Adding: " << key << " -> " << data << " at Hash index: " << hash << std::endl;

		Dict[hash].key = key;
		Dict[hash].value = data;
		Dict[hash].isUsed = true;
		Dict[hash].isDeleted = false;
		this->Count++;

		return;
	}

	void Delete(const TKey& key)
	{
		int hash = hash_Function(key);
		Dict[hash].isDeleted = true;
		this->Count--;
		return;
	}

	void Print() 
	{
		for (int i = 0; i < Capacity; i++)
		{
			if (Dict[i].isUsed && !Dict[i].isDeleted)
			{
				std::cout << Dict[i].key << " -> " << Dict[i].value << std::endl;
			}
		}
	}

};
