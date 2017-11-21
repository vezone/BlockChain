#include <iostream>
#include <cstring>

#include "src\BlockChain.h"
#include "src\sha256.h"

#define log(x) std::cout << x << std::endl;
#define l(x) std::cout << #x << std::endl;


int main() {

	using namespace vez;
	
	BlockChain blockchain(10);
	Block currentblock = blockchain.createGenesis();
	while (blockchain.moveNext()) {
		blockchain.push(currentblock);
		currentblock = blockchain.nextBlock(currentblock);
	}

	blockchain.print();
	
	std::cin.get();
}


/*
TODO: Прога совсем не ловит ошибки
*/
