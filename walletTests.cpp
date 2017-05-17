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

int main()
{
	genericConstructor();
}