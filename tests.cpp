#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE hash44

#include <boost/test/unit_test.hpp>
#include "HD_Wallet.cpp"

using namespace bc;

BOOST_AUTO_TEST_SUITE(hd_wallet_tests)

#define MNEMONIC_SEED "label stick flat innocent brother frost rebel aim creek six baby copper need side cannon student announce alpha"
#define UNINITIALIZED_ADDRESS "1111111111111111111114oLvT2"
#define CHILD_ADDRESS_0 "1KD186Ko4ejaBeYk8EpMikYqfxnpnVTYKk"
#define COIN256_CHILD_ADDRESS_0 "16HAUSw9YhTXu1YPc1RNBeWo64SDc77WHu"
#define ACCOUNT256_CHILD_ADDRESS_0 "1q6Z5ZpsFaqV8VE6LbwKP9uqfPoKQGUQv"
const Prefixes coin = {256, 0x0488ADE4, 0x0488B21E, 0x00, 0x05};
const data_chunk seed = to_chunk(wallet::decode_mnemonic(split(MNEMONIC_SEED)));


BOOST_AUTO_TEST_CASE(hd_wallet_construct_default_valid)
{
	HD_Wallet wallet = HD_Wallet();
	wallet.setCoinPrefixes(wallet.BTC);
	bool address_match = 0;
	if(wallet.childAddress(0).encoded() == UNINITIALIZED_ADDRESS)
	{
		address_match = 1;
	}
	BOOST_REQUIRE(!address_match);
}

BOOST_AUTO_TEST_CASE(hd_wallet_construct_coin_code)
{
	HD_Wallet wallet(coin);
	BOOST_REQUIRE_EQUAL(wallet.getCoinPrefixes().bip44_code, coin.bip44_code);
}
BOOST_AUTO_TEST_CASE(hd_wallet_construct_entropy)
{
	HD_Wallet wallet(seed);
	BOOST_REQUIRE_EQUAL(wallet.childAddress(0).encoded(), CHILD_ADDRESS_0);
}
BOOST_AUTO_TEST_CASE(hd_wallet_construct_entropy_coin)
{
	HD_Wallet wallet(seed, coin);
	BOOST_REQUIRE_EQUAL(wallet.childAddress(0).encoded(), COIN256_CHILD_ADDRESS_0);
	BOOST_REQUIRE_EQUAL(wallet.getCoinPrefixes().bip44_code, coin.bip44_code);

}
BOOST_AUTO_TEST_CASE(hd_wallet_construct_mnemonic_default)
{
	HD_Wallet wallet(MNEMONIC_SEED);
	BOOST_REQUIRE_EQUAL(wallet.childAddress(0).encoded(), CHILD_ADDRESS_0);
}
BOOST_AUTO_TEST_CASE(hd_wallet_construct_mnemonic_coin)
{
	HD_Wallet wallet(MNEMONIC_SEED, coin);
	BOOST_REQUIRE_EQUAL(wallet.childAddress(0).encoded(), COIN256_CHILD_ADDRESS_0);
	BOOST_REQUIRE_EQUAL(wallet.getCoinPrefixes().bip44_code, coin.bip44_code);
}
BOOST_AUTO_TEST_CASE(hd_wallet_set_coin)
{
	HD_Wallet wallet(MNEMONIC_SEED);
	wallet.setCoin(256);
	BOOST_REQUIRE_EQUAL(wallet.getCoinPrefixes().bip44_code, 256);
}
BOOST_AUTO_TEST_CASE(hd_wallet_set_coin_prefixes)
{
	HD_Wallet wallet(MNEMONIC_SEED);
	wallet.setCoinPrefixes(coin);
	BOOST_REQUIRE_EQUAL(wallet.childAddress(0).encoded(), COIN256_CHILD_ADDRESS_0);
	BOOST_REQUIRE_EQUAL(wallet.getCoinPrefixes().bip44_code, coin.bip44_code);

}
BOOST_AUTO_TEST_CASE(hd_wallet_set_account)
{
	HD_Wallet wallet(MNEMONIC_SEED);
	wallet.set_account(256);
	BOOST_REQUIRE_EQUAL(wallet.getCurrentAccount(), 256);
	BOOST_REQUIRE_EQUAL(wallet.childAddress(0).encoded(), ACCOUNT256_CHILD_ADDRESS_0);
}





























BOOST_AUTO_TEST_SUITE_END()