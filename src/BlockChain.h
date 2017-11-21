#pragma once

#include <iostream>
#include <windows.h>

namespace vez {

	class Block {

	private:
		int m_Index;
		SYSTEMTIME m_Time;
		std::string m_Data;
		std::string m_PData;

	public:
		Block();
		Block(Block &block);
		Block(int index, SYSTEMTIME time, const std::string &data, const std::string &spdata);
	
	public:
		int getIndex();
		SYSTEMTIME getTime();
		std::string getData();
		std::string getPData();

	public:
		friend std::ostream& operator<< (std::ostream& stream, const Block& block);

	};

	class BlockChain {

	private:
		int m_Length;
		int m_CurrentIndex;
		Block *m_Collection;
	
	public:

		BlockChain();
		BlockChain(int length);
	
	public:
		int getLength();
		int getCurrentIndex();

	public:
		bool moveNext();
		void push(Block newBlock);
		void print();

	public:
		Block createGenesis();
		Block nextBlock(Block prevBlock);
		bool isValidBlock(Block newBlock, Block prevBlock);
		void replaceChain(BlockChain newChain);
		bool isChainValid();

	};

}

/*

TODO: Нужно заменить char* на std::string и применить md5

*/