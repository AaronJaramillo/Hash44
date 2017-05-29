
CFLAGS=`pkg-config --cflags libbitcoin --libs libbitcoin libbitcoin-client`



wallet: wallet.cpp HD_Wallet.cpp
	g++ -std=c++11 -o wallet wallet.cpp HD_Wallet.cpp $(CFLAGS)
	./wallet
clean:
	rm wallet

