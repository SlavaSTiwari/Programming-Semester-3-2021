#include"Cache.h"
#include "CMisc.h"

int main()
{
	LRUCache< std::string, Student>* cache = new LRUCache<std::string, Student>(5);

	Student Slava("Slava", "Random");
	Student Achmad("Achmad", "Random");
	Student Anshuman("Anshuman", "Random");
	Student Mwansa("Mwansa", "Random");
	Student Raunak("Raunak", "Random");
	Student Abhay("Abhay", "Random");

	cache->set("Slava", Slava);
	cache->set("Achmad", Achmad);
	cache->set("Anshuman", Anshuman);
	cache->set("Mwansa", Mwansa);
	cache->set("Raunak", Raunak);

	std::cout << "The Cache:" << std::endl;
	cache->display();

	std::cout << cache->get("Slava") << std::endl;	 // Recently accessed,
													// will go to 1st from 5th
	std::cout << "\nThe Cache:" << std::endl;
	cache->display();

	cache->set("Abhay", Abhay);		// Now since there is no more space left,
								   // the least recently used element will be removed
	std::cout << "\nThe Cache:" << std::endl;
	cache->display();

	return 0;
}