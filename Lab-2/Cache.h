#pragma once

// LRU Cache
#include"iDict.h"

template <class K, class V>
class LRUCache
{
public:
	class Node
	{
	public:
		K Key;
		V Value;
		Node* next;
		Node* prev;

		Node()
		{
			next = nullptr;
			prev = nullptr;
		}

		Node(K key, V val)
		{
			next = nullptr;
			prev = nullptr;
			Key = key;
			Value = val;
		}
	};

	IDictionary<K, Node*> *item_map;
	Node *head = new Node();
	Node *tail = new Node();
	int Cache_cap;

public:
	LRUCache(int capacity)
	{
		Cache_cap = capacity;
		item_map = new IDictionary<K, Node*>(capacity*3);
		head->next = tail;
		tail->prev = head;
	}

	void set(const K& key, const V& value)
	{
		if ( !item_map->is_Empty(item_map->hash_Function(key)) && item_map->contains_Key(key))
		{
			//std::cout << "The position is full";
			Node *node = item_map->Get(key);
			remove(node);
			node->Value = value;
			add(node);
		}
		else
		{
			if (item_map->get_Count() == Cache_cap)
			{
				item_map->Delete(tail->prev->Key);
				remove(tail->prev);
			}
			Node* new_node = new Node(key, value);
			item_map->Add(key, new_node);
			add(new_node);
		}
	}

	V get(const K& key)
	{
		Node* node = item_map->Get(key);
		if (node != nullptr)
		{
			remove(node);
			add(node);
			return node->Value;
		}
	}

	void add(Node* node)
	{
		Node *head_next = head->next;
		head->next = node;
		node->prev = head;
		node->next = head_next;
		head_next->prev = node;
	}

	void remove(Node* node)
	{
		Node *next_node = node->next;
		Node *prev_node = node->prev;

		prev_node->next = next_node;
		next_node->prev = prev_node;
	}

	void display()
	{
		Node *temp = head->next;
		while (temp->next != nullptr)
		{
			std::cout << temp->Key << " -> " << temp->Value << std::endl;
			temp = temp->next;
		}
		return;
	}

};