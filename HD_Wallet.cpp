
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/client.hpp>
#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>


using namespace bc;
// Coin  | coin_type’ |    version_WIF   |  version_p2pkh  |  version_p2sh   | version_hd_secret
// POT   |     81     |        183       |  55/('P')       |   5/('3')  
struct Prefixes
{
	uint32_t bip44_code;
	uint32_t HDprivate;
	uint32_t HDpublic;
	uint32_t P2KH;
	uint32_t P2SH;

};

class HD_Wallet
{
public:
	
	Prefixes BTC =  {0x80000000, 0x0488ADE4, 0x0488B21E, 0x00, 0x05};
	Prefixes tBTC = {0x80000001, 0x04358394, 0x043587CF, 0x6f, 0xC4};
	Prefixes LTC =  {0x80000002, 0x0488ADE4, 0x0488B21E, 0x30, 0x32};
	Prefixes tLTC = {0x80000001, 0x04358394, 0x04358394, 0x6f, 0xC0};
	Prefixes POT =  {0x80000081, 0x0488ADE4, 0x0488B21E, 55, 0x05};

	//constructor
	HD_Wallet()
	{
		data_chunk entropy = data_chunk(16);
		pseudo_random_fill(entropy);
		mnemonic = wallet::create_mnemonic(entropy);
		seed = to_chunk(wallet::decode_mnemonic(mnemonic));
		purpose44Key = wallet::hd_private(seed).derive_private(0x8000002C);

	}
	HD_Wallet(Prefixes coin_code)
	{
		data_chunk entropy = data_chunk(16);
		pseudo_random_fill(entropy);
		mnemonic = wallet::create_mnemonic(entropy);
		seed = to_chunk(wallet::decode_mnemonic(mnemonic));
		purpose44Key = wallet::hd_private(seed).derive_private(0x8000002C);
		setCoinPrefixes(coin_code);

	}

	HD_Wallet(const data_chunk userSeed)
	{
		//defaults to BTC
		seed = userSeed;
		//mnemonic = wallet::create_mnemonic(entropy);
		//seed = entropy; //to_chunk(wallet::decode_mnemonic(mnemonic));
		purpose44Key = wallet::hd_private(seed).derive_private(0x8000002C);
		setCoinPrefixes(BTC);
	}

	HD_Wallet(const data_chunk userSeed, Prefixes coin_code)
	{
		seed = userSeed;
		//mnemonic = wallet::create_mnemonic(entropy);
		//seed = entropy; //to_chunk(wallet::decode_mnemonic(mnemonic));
		purpose44Key = wallet::hd_private(seed).derive_private(0x8000002C);
		setCoinPrefixes(coin_code);
	}

	HD_Wallet(const std::string mnemonicSeed)
	{
		//defaults to BTC
		mnemonic = split(mnemonicSeed);
		seed = to_chunk(wallet::decode_mnemonic(mnemonic));
		//seed = to_chunk(hashSeed);
		purpose44Key = wallet::hd_private(seed).derive_private(0x8000002C);
		setCoinPrefixes(BTC);
	}
	HD_Wallet(const std::string mnemonicSeed, Prefixes coin_code)
	{
		mnemonic = split(mnemonicSeed);
		seed = to_chunk(wallet::decode_mnemonic(mnemonic));
		//seed = to_chunk(hashSeed);
		purpose44Key = wallet::hd_private(seed).derive_private(0x8000002C);
		setCoinPrefixes(coin_code);
	}
	void setCoin(int bip44coin_code)
	{
		coin_type.bip44_code = bip44coin_code;
		coin = purpose44Key.derive_private(bip44coin_code);
	}
	void setCoinPrefixes(Prefixes coin_code)
	{
		coin_type = coin_code;
		coin = purpose44Key.derive_private(coin_type.bip44_code);
		//to-do scan accounts
		set_account(0x80000000);

	}
	void set_account(int account_num)
	{
		currentAccount = account_num;
		account = coin.derive_private(account_num);
	}
	//display output
	void dumpKeys()
	{
		displayMnemonic();
		displayMasterKey();
		displayChildSecretKey(0);
		displayChildAddress(0);

	}
	void displayMasterKey()
	{
		std::cout << "\nMaster Private Key: " << wallet::hd_private(seed).encoded() << std::endl;
	}

	void displayMnemonic()
	{
		if(wallet::validate_mnemonic(mnemonic))
		{
			std::cout << "\n" << join(mnemonic) << std::endl;

		}else{
			std::cout << "\n" << "Mnemonic Invalid! " << std::endl;
		}
	}

	void displayChildSecretKey(int index)
	{
		std::cout << "\nSecret Key: " << encode_base16(childSecretKey(index)) << std::endl;
	}
	// void displayChildWif(int index)
	// {
	// 	std:cout <<"\n WIF: " << childWif(index).encoded() << std::endl;
	// }

	void displayChildPublicKey(int index)
	{
		std::cout << "\nPublic Key: " << childPublicKey(index).encoded() << std::endl;
	}

	void displayChildAddress(int index)
	{
		std::cout << "\nAddress: " << childAddress(index).encoded() << std::endl;
	}
	std::string getChildKeyPath()
	{

		return "Master / 0x8000002C / " + std::to_string(getCoinPrefixes().bip44_code) + " / " + std::to_string(getCurrentAccount()) + " / 0 / Child Index";
	}
	void addressRange(int start, int end)
	{
		while(start != end)
		{
			displayChildAddress(start);
			start++;
		}
	}

	void getBalance(int index)
	{
		
		client::connection_type connection = {};
		connection.retries = 3;
		connection.timeout_seconds = 8;
		connection.server = config::endpoint("tcp://testnet.libbitcoin.net:19091");

		client::obelisk_client client(connection);


		static const auto on_done = [](const chain::history::list& rows)
		{
			uint64_t unspent_balance = 0;

			for(const auto& row: rows)
			{

			    // spend unconfirmed (or no spend attempted)
			    if (row.spend.hash() == null_hash)
			        unspent_balance += row.value;
			}
			std::cout<< encode_base10(unspent_balance, 8) << std::endl;

		};
		static const auto on_error2 = [](const code ec) {

			std::cout << "Error Code: " << ec.message() << std::endl;

		};


		if(!client.connect(connection))
		{
			std::cout << "Fail" << std::endl;
		} else {
			std::cout << "Connection Succeeded" << std::endl;
		}

		client.blockchain_fetch_history3(on_error2, on_done, childAddress(index));
		client.wait();


	}

	//accesor
	wallet::hd_private getMasterKey()
	{
		return wallet::hd_private(seed);
	}
	
	ec_secret childSecretKey(int index)
	{
		return account.derive_private(0).derive_private(index);
	}
	// wallet::hd_private childWif(int index)
	// {
	// 	return account.derive_private(0).derive_private(index);
	// }

	wallet::ec_public childPublicKey(int index)
	{
	
		return account.derive_public(0).derive_public(index).point();
	}

	wallet::payment_address childAddress(int index)
	{
		return wallet::payment_address((childPublicKey(index).point()), coin_type.P2KH);
	}

	Prefixes getCoinPrefixes(){
		return coin_type;
	}

	int getCurrentAccount()
	{
		return currentAccount;
	}
private:
	//members
	//data_chunk entropy;
	data_chunk seed;
	Prefixes coin_type;
	int currentAccount;
	wallet::word_list mnemonic;
	wallet::hd_private purpose44Key;
	wallet::hd_private coin;
	wallet::hd_private account;





};