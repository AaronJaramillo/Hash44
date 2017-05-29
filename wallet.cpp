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
	std::cout << "3." << " Custom Coin Path" << std::endl;
	std::cout << "4." << " Change Coin" << std::endl;
	std::cout << "5." << " Display" << std::endl;
	std::cout << "6." << " Quit" << std::endl;
	std::cout << "==========================" << std::endl;
}

void displayMenu()
{
	std::cout << "\n==========================" << std::endl;
	std::cout << "1. Master Key" << std::endl;
	// std::cout << "2. Mnemonic" << std::endl;
	std::cout << "3. Dump Child Secret Key" << std::endl;
	std::cout << "4. Payment Address" << std::endl;
	std::cout << "5. Show Child Keys Path" << std::endl; 
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
	} else if(coin=="POT"){
		return HD_Wallet().POT;
	}
	else {
		
		return HD_Wallet().BTC;

	}
}

int main(int argc, char *argv[]){
	HD_Wallet wallet = HD_Wallet();
	if(argc == 3)
	{
		for(int i = 0; i < argc; i++)
		{
			if(std::string(argv[i]) == "-c")
			{
				wallet.setCoinPrefixes(matchPrefixTicker(std::string(argv[i+1])));
				wallet.dumpKeys();
				std::cout << std::string(argv[1]) << std::endl;
			}else if(std::string(argv[i]) == "-m"){
				wallet = HD_Wallet(std::string(argv[i+1]));
				wallet.dumpKeys();
				std::cout << std::string(argv[1]) << std::endl;
			}
		}
	}else if(argc == 5){
			std::string coinArg;
			std::string seedArg;
			if(std::string(argv[1]) == "-c")
			{
				coinArg = std::string(argv[2]);
				seedArg = std::string(argv[4]);
			}else if(std::string(argv[1]) == "-m"){
				coinArg = std::string(argv[4]);
				seedArg = std::string(argv[2]);

			}
			wallet = HD_Wallet(seedArg, matchPrefixTicker(coinArg));
			wallet.dumpKeys();
	}
	int choice = 0;
	while(choice != 6)
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
			int pathIndex = getInput();
			wallet.setCoin(pathIndex);
			//printpath
		} else if (choice == 5)
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

				} else if (choice == 3)
				{
					index = getInput();
					wallet.displayChildSecretKey(index);

				} else if (choice == 4)
				{
					index = getInput();
					wallet.displayChildAddress(index);
				} else if (choice == 5)
				{
					std::cout << "Master Key / Purpose Code / Coin Code / Account / Change(T/F) / Child Index" << std::endl;
					std::cout << "Master / 44 / " << wallet.getCoinPrefixes().bip44_code << " / " << wallet.getCurrentAccount() << " / 0 / Child Index" << std::endl;
				
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
			wallet.setCoinPrefixes(matchPrefixTicker(getCoinTicker()));

		} else if (choice == 6)
		{
			std::cout << "Good Bye!" << std::endl;
		} else {
			std::cout << "Selection Invalid!" << std::endl;
		}
	}
}
