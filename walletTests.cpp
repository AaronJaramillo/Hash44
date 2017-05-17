#include <bitcoin/bitcoin.hpp>
#include <bitcoin/client.hpp>
#include "HD_Wallet.cpp"
using namespace bc;

void genericConstructor()
{
	HD_Wallet wallet = HD_Wallet();
	wallet.setCoin(1);
	wallet.dumpKeys();
}
void testMnemonic_MasterKey()
{	
	wallet::hd_private master(to_chunk(wallet::decode_mnemonic(split("label stick flat innocent brother frost rebel aim creek six baby copper need side cannon student announce alpha"))));
	HD_Wallet wallet("label stick flat innocent brother frost rebel aim creek six baby copper need side cannon student announce alpha");
	if(master == wallet.getMasterKey()){
		std::cout << "Success!" << std::endl;
		std::cout << master.encoded() << std::endl;
		wallet.displayMasterKey();
	}
}
int main()
{
	//genericConstructor();
	testMnemonic_MasterKey();
}