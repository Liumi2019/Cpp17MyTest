#include <iostream>

#include "UsingClass.h"

void Data::Set(HolderBase *ptr) {
	_holderBase = ptr;
}

int Data::Get() {
	if (_holderBase == nullptr) {
		std::cout << "error _holderBase = nullptr" << std::endl;
		return 0;
	}

	_holderBase->printInfo();

	Holder* holder = static_cast<Holder*>(_holderBase);
	return holder->getData();
}

void test_usingClass() {

	Data data;

	Holder h(50);

	data.Set(&h);

	std::cout << data.Get() << std::endl;

}
