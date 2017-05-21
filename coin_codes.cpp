#include <bitcoin/bitcoin.hpp>
#include <bitcoin/client.hpp>
#include <vector>
using namespace bc;

struct Prefixes
{
	uint32_t bip44_code;
	uint32_t HDprivate;
	uint32_t HDpublic;
	uint32_t P2KH;
	uint32_t P2SH;

};


enum coin_code : uint32_t::list
{
	BTC =  {0, 0x0488ADE4, 0x0488B21E, 0x00, 5},
	tBTC = {1, 0x04358394, 0x043587CF, 0x6f, 0xC4},
	// LTC = Prefixes {2, 0x0488ADE4, 0x0488B21E, 48, 50},
	// tLTC = Prefixes {1, 0x04358394, 0x04358394, 111, 196},
};