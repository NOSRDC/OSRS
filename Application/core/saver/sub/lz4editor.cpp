//
// Created by Neemaxon on 03.03.2026.
//

#include <lz4.h>
#include <QByteArray>

QByteArray CompressLZ4(const QByteArray& input) {
    int maxSize = LZ4_compressBound(input.size());
    QByteArray compressed(maxSize, 0);

    int compressedSize = LZ4_compress_default(
        input.constData(),
        compressed.data(),
        input.size(),
        maxSize
    );

    if (compressedSize <= 0)
        throw std::runtime_error("rbxmk file compression failed");

    compressed.resize(compressedSize);
    return compressed;
}