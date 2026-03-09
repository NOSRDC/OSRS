//
// Created by Neemaxon on 03.03.2026.
//

#include <QByteArray>

#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>

QByteArray EncryptAES(const QByteArray& input) {
    using namespace CryptoPP;

    AutoSeededRandomPool prng;

    SecByteBlock key(AES::DEFAULT_KEYLENGTH * 2); // 256 bit
    SecByteBlock iv(AES::BLOCKSIZE);

    prng.GenerateBlock(key, key.size());
    prng.GenerateBlock(iv, iv.size());

    CBC_Mode<AES>::Encryption enc;
    enc.SetKeyWithIV(key, key.size(), iv);

    std::string cipher;

    StringSource ss(
        reinterpret_cast<const byte*>(input.data()),
        input.size(),
        true,
        new StreamTransformationFilter(
            enc,
            new StringSink(cipher)
        )
    );

    return QByteArray(cipher.data(), cipher.size());
}