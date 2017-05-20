#include <bitcoin/bitcoin.hpp>
#include <bitcoin/client.hpp>
#include "HD_Wallet.cpp"

using namespace bc;

void genericConstructor()
{
	HD_Wallet wallet = HD_Wallet();
	wallet.setCoin(wallet.BTC);
	wallet.dumpKeys();
}
void testMnemonic_MasterKey()
{	
	wallet::hd_private master(to_chunk(wallet::decode_mnemonic(split("label stick flat innocent brother frost rebel aim creek six baby copper need side cannon student announce alpha"))));
	HD_Wallet wallet("label stick flat innocent brother frost rebel aim creek six baby copper need side cannon student announce alpha");
	if(master == wallet.getMasterKey()){
		std::cout << "testMnemonic_MasterKey: Success!" << std::endl;
		std::cout << master.encoded() << std::endl;
		wallet.displayMasterKey();
	}
}
void testCoin_address(Prefixes coin)
{
	uint32_t coinCode = coin.bip44_code;
	uint8_t addyPrefix = coin.P2KH; 
	HD_Wallet wallet("label stick flat innocent brother frost rebel aim creek six baby copper need side cannon student announce alpha", coin);
	wallet::payment_address address(wallet::hd_private(to_chunk(wallet::decode_mnemonic(split("label stick flat innocent brother frost rebel aim creek six baby copper need side cannon student announce alpha")))).derive_private(44).derive_private(coinCode).derive_private(0).derive_public(0).derive_public(0).point(), addyPrefix);
	if(address == wallet.childAddress(0))
	{
		std::cout << "testCoin_address: Success! \n" << std::endl;
	}
	wallet.displayChildAddress(0);
	std::cout << address.encoded() << std::endl;

}
void testCoinConstructor_childKeyDisplay()
{
	int BTC = HD_Wallet().BTC.bip44_code;
	HD_Wallet wallet1("label stick flat innocent brother frost rebel aim creek six baby copper need side cannon student announce alpha", HD_Wallet().BTC);
	wallet::ec_public publicPoint = wallet::hd_private(to_chunk(wallet::decode_mnemonic(split("label stick flat innocent brother frost rebel aim creek six baby copper need side cannon student announce alpha")))).derive_private(44).derive_private(BTC).derive_private(0).derive_public(0).derive_public(0).point();
	ec_secret secretKey = wallet::hd_private(to_chunk(wallet::decode_mnemonic(split("label stick flat innocent brother frost rebel aim creek six baby copper need side cannon student announce alpha")))).derive_private(44).derive_private(BTC).derive_private(0).derive_private(0).derive_private(0).secret();
	if(publicPoint.point() == wallet1.childPublicKey(0).point())
	{
		std::cout << "testCoinConstructor_childKeyDisplay: Success! \n" << std::endl;
	}
	wallet1.displayChildPublicKey(0);
	std::cout << publicPoint.encoded() << std::endl;
	if (secretKey == wallet1.childSecretKey(0))
	{
		std::cout << "testCoinConstructor_childKeyDisplay: Success! \n" << std::endl;
	}
	wallet1.displayChildSecretKey(0);
	std::cout << encode_base16(secretKey) << std::endl;

}

int main()
{
	genericConstructor();
	testMnemonic_MasterKey();
	testCoinConstructor_childKeyDisplay();
	testCoin_address(HD_Wallet().tBTC);
}