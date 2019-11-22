//! Unit Tests for MPAGSCipher PLayfairCipher class
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "PlayfairCipher.hpp"

TEST_CASE("Playfair Cipher encryption", "[playfair]"){
    PlayfairCipher pc{"SpicyPlayfair"};
    REQUIRE(pc.applyCipher("HELLOWORLD", CipherMode::Encrypt) == "KGRUFMIWBAKU");
}

TEST_CASE("Playfair Cipher decryption", "[playfair]"){
    PlayfairCipher pc{"SpicyPlayfair"};
    REQUIRE(pc.applyCipher("KGRUFMIWBAKU", CipherMode::Decrypt) == "HELXLOWORLDZ");
}
//The numbers are entered as ONETWOTHREEFOURFIVE due to how they are formatted before the 'apply cipher'
TEST_CASE("Playfair Cipher encryption with num", "[playfair]"){
    PlayfairCipher pc ("SpicyPlayfair");
	REQUIRE(pc.applyCipher("ONETWOTHREEFOURFIVE", CipherMode::Encrypt) == "QOKNIWQKAHGAMWBRPWKV");
}

TEST_CASE("Playfair Cipher decryption with num", "[playfair]"){
    PlayfairCipher pc ("SpicyPlayfair");
	REQUIRE(pc.applyCipher("QOKNIWQKAHGAMWBRPWKV", CipherMode::Decrypt) == "ONETWOTHREEFOURFIVEZ");
}