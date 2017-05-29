# Hash44
BIP44 multicoin CLI wallet

Hash44 is BIP 44 compliant command line keychain utility built with Libbitcoin. Hash44 allows navigating HD child chains to use multiple altcoins, accounts and protocols using different keys derived from the same master wallet.

BIP44 derivation is structured:
```
Master key / Purpose Code(44) / Coin Code / Account Index / Change Andress(Boolean) / Child Index
```

Depends on Libbitcoin
github.com/libbitcoin/libbitcoin
github.com/libbitcoin/libbitcoin-cient (Not really yet)

Make:

```
$ make wallet
```

Once the executable is made it can be run with:

```
./wallet
```

or compile on the command line:

```
g++ -std=c++11 -o wallet wallet.cpp HD_Wallet.cpp $(pkg-config --cflags libbitcoin --libs libbitcoin libbitcoin-client)
```

Allows:


- Generation of a new bip44 wallet master
- Import mnemonicm master key
- Use multiple altcoins
- Use custom coin paths
- Display child keys and addresses

To-Do:


- Add Balances
- Implement bip44 Accounts
- Implement account scanning to automatically recogonize balances. 
