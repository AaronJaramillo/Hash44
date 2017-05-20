#include <bitcoin/bitcoin.hpp>
#include <string.h>
#include <iostream>
#include "HD_Wallet.cpp"
#include <sstream>

using namespace bc;

void mainMenu()
{
	std::cout << "\n==========================" << std::endl;
	std::cout << "1. Generate New Wallet" << std::endl;
	std::cout << "2. Import Wallet" << std::endl;
	std::cout << "3. display" << std::endl;
	std::cout << "4. Exit" << std::endl;
	std::cout << "==========================" << std::endl;
}

void displayMenu()
{
	std::cout << "\n==========================" << std::endl;
	std::cout << "1. Master Key" << std::endl;
	// std::cout << "2. Mnemonic" << std::endl;
	// std::cout << "3. Child Private Key" << std::endl;
	// std::cout << "4. Payment Address" << std::endl;
	// std::cout << "5. Address Range" << std::endl; 
	std::cout << "6. Dump Keys" << std::endl;
	// std::cout << "7. Check Balance" << std::endl;
	std::cout << "8. Exit" << std::endl;
	std::cout << "==========================" << std::endl;
}
int getInput()
{
	std::string input;
	int choice = 0;

	while (true) {
		std::cout << "Enter a Number: "; 
		std::getline(cin, input);

		// This code converts from string to number safely.
		std::stringstream myStream(input);
		if (myStream >> choice)
		 break;
		std::cout << "Invalid number, please try again" << std::endl;
	}
	return choice;
		
}
std::string getMnemonic()
{
	
	std::string mnemonicSeed;
	std::cout << "Enter Seed String: ";
	std::getline(cin, mnemonicSeed);

	return mnemonicSeed;
}

std::string getCoinTicker()
{
	
	std::string ticker;
	std::cout << "Enter Coin Ticker: ";
	std::getline(cin, ticker);
	return ticker;
}
Prefixes matchPrefixTicker(std::string coin)
{

	if(coin == "BTC")
	{
		return HD_Wallet().BTC;
	} else if(coin == "tBTC"){

		return HD_Wallet().tBTC;
	}else if(coin == "LTC"){

		return HD_Wallet().LTC;

	} else if(coin == "tLTC"){

		return HD_Wallet().tLTC;
	} else {
		
		return HD_Wallet().BTC;

	}
}

int main(){
	HD_Wallet wallet;
	int choice = 0;
	while(choice != 4)
	{
		mainMenu();
		choice = getInput();

		if(choice == 1)
		{	
			std::string coinInput = getCoinTicker();
			Prefixes coin = matchPrefixTicker(coinInput);
			wallet = HD_Wallet(coin);
 
			wallet.dumpKeys();
		} else if(choice == 2)
		{	
			std::string mnemonicSeedList = getMnemonic();
			if(wallet::validate_mnemonic(split(mnemonicSeedList)))
			{

				std::string coinInput = getCoinTicker();
				wallet = HD_Wallet(mnemonicSeedList, matchPrefixTicker(coinInput));
				wallet.dumpKeys();
			} else {
				std::cout << "Mnemonic Invalid!" << std::endl;
			}

		} else if (choice == 3)
		{	
			while(choice != 8){
				displayMenu();
				choice = getInput();
				//std::cin.ignore();
				int index;
				
				if(choice == 1)
				{
					wallet.displayMasterKey();
				// } else if(choice == 2) 
				// {
				// 	wallet.displayMnemonic();

				// } else if (choice == 3)
				// {
				// 	index = getInput();
				// 	wallet.displayChildPrivateKey(index);

				// } else if (choice == 4)
				// {
				// 	index = getInput();
				// 	wallet.displayAddress(index);
				// } else if (choice == 5)
				// {
				// 	int start = getInput();
				// 	int end = getInput();
				// 	wallet.addressRange(start, end);
				// 
				} else if (choice == 6)
				{
					wallet.dumpKeys();
				//} else if (choice == 7)
				// {
				// 	index = getInput();
				// 	wallet.getBalance(index);
					
				} else if (choice == 8)
				{
					std::cout << "Bye" << std::endl;
					
				}else {
					std::cout << "Selection Invalid! " << std::endl;
				}
			}
		} else if (choice == 4)
		{
			std::cout << "Goodbye" << std::endl;
		}else {
			std::cout << "Selection Invalid!" << std::endl;
		}
	}
}






