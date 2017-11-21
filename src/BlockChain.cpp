#include <iostream>
#include <windows.h>
#include <cstdlib>

#include "BlockChain.h"
#include "sha256.h" //SHA256 sha; sha("string") <- hash;


namespace vez {

	Block::Block()
		: m_Index(0), m_Data("\0"), m_PData("\0")
	{
		GetLocalTime(&m_Time);
	}

	Block::Block(Block &block) {
		m_Index = block.getIndex();
		m_Time = block.m_Time;
		m_Data = block.m_Data;
		m_PData = block.m_PData;
	}

	Block::Block(int index, SYSTEMTIME time, const std::string &data, const std::string &pdata)
		: m_Index(index), m_Time(time), m_Data(data), m_PData(pdata)
	{
	}

	int Block::getIndex() {
		return m_Index;
	}

	void Block::setData(const std::string& string) {
		m_Data = string;
	}

	SYSTEMTIME Block::getTime() {
		return m_Time;
	}

	std::string Block::getData() {
		return m_Data;
	}

	std::string Block::getPData() {
		return m_PData;
	}

	std::ostream& operator<< (std::ostream& stream, const Block& block) {
		stream << "Block{ " << block.m_Index << ", "
			<< block.m_Time.wDay << "." << block.m_Time.wMonth << "." << block.m_Time.wYear
			<< " " << block.m_Time.wHour << ":" << block.m_Time.wMinute << ":"
			<< block.m_Time.wSecond << ":" << block.m_Time.wMilliseconds <<
			" " << block.m_Data << " " << block.m_PData << " }";
		return stream;
	}

	BlockChain::BlockChain()
	{
		m_Length = 10;
		m_Collection = new Block[m_Length];
	}

	BlockChain::BlockChain(int length)
		: m_Length(length)
	{
		m_Length = length;
		m_Collection = new Block[length];
	}

	int BlockChain::getLength() {
		return m_Length;
	}

	int BlockChain::getCurrentIndex() {
		return m_CurrentIndex;
	}

	bool BlockChain::moveNext() {
		return m_CurrentIndex < m_Length ? true : false;
	}

	void BlockChain::push(Block newBlock) {
		if (moveNext()) {
			m_Collection[m_CurrentIndex] = newBlock;
			m_CurrentIndex++;
		}

	}

	void BlockChain::print() {
		for (int i = 0; i < m_Length; i++) {
			std::cout << m_Collection[i] << std::endl;
		}
	}

	Block BlockChain::createGenesis() {
		SYSTEMTIME time;
		GetLocalTime(&time);
		SHA256 sha256;
		std::string data = sha256("genesis");
		return Block(0, time, data, "0");
	}

	Block BlockChain::nextBlock(Block prevBlock) {
		SHA256 sha256;
		int index = prevBlock.getIndex() + 1;
		SYSTEMTIME time;
		GetLocalTime(&time);
		std::string data = sha256(prevBlock.getData());
		std::string pdata = prevBlock.getData();
		return Block(index, time, data, pdata);
	}

	bool BlockChain::isValidBlock(Block newBlock, Block prevBlock) {
		if (newBlock.getIndex() != prevBlock.getIndex() + 1) {
			std::cout << "Wrong index int this block!" << std::endl;
			return false;
		}
		else if (newBlock.getPData() != prevBlock.getData()) {
			std::cout << "Wrong hash in prev block!" << std::endl;
			return false;
		}

		return true;
	}

	void BlockChain::replaceChain(BlockChain newChain) {
		int len = newChain.getLength();
		if (len > getLength()) {
			free(m_Collection);
			m_Collection = new Block[len];
			memcpy(m_Collection, newChain.m_Collection, sizeof(BlockChain) * 8);
		}
		else {
			std::cout << "Block chain is not valid!" << std::endl;
		}
	}

	bool BlockChain::isChainValid() {
		Block current, prev;
		for (int i = 1; i < m_Length; i++) {
			current = m_Collection[i],
			prev = m_Collection[i - 1];

			if (!isValidBlock(current, prev)) {
				std::cout << "Something goes wrong with that block: " << prev << std::endl;
				return false;
			}
			
		}

		return true;
	}

	void BlockChain::makeProblem() {
		int index = m_Length / 2;
		m_Collection[index].setData("labuda");
	}

}