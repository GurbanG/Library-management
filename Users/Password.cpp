#include "Password.h"
#include <cstring>
#include <cstdint>

Password::Password(std::string &new_word){
    word = new_word;
}

std::string Password::calculate_hash() {
    if(hash_exists) {
        return hash;
    }
    uint8_t hash_int[32];
    sha256(word.c_str(), std::strlen(word.c_str()), hash_int);

    hash = "";
    for(auto i: hash_int){
        hash += std::to_string(i);
    }
    hash_exists = true;
    return hash;
}


void Password::sha256(const char* message, uint32_t message_len, uint8_t* digest)
{
    const uint32_t k[] = {
            0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
            0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
            0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
            0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
            0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
            0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
            0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
            0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
            0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
            0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
            0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
            0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
            0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
            0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
            0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
            0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    const uint32_t initial_hash[] = {
            0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
            0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

    uint32_t h[8];
    std::memcpy(h, initial_hash, sizeof(h));

    uint32_t w[64];
    uint32_t a, b, c, d, e, f, g, h_temp, i, j, t1, t2;

    for (i = 0; i < message_len / 64; i++) {
        for (j = 0; j < 16; j++) {
            w[j] = (static_cast<uint32_t>(message[i * 64 + j * 4 + 0]) << 24) |
                   (static_cast<uint32_t>(message[i * 64 + j * 4 + 1]) << 16) |
                   (static_cast<uint32_t>(message[i * 64 + j * 4 + 2]) << 8) |
                   (static_cast<uint32_t>(message[i * 64 + j * 4 + 3]) << 0);
        }

        for (j = 16; j < 64; j++) {
            const uint32_t s0 = (w[j - 15] >> 7) | (w[j - 15] << 25);
            const uint32_t s1 = (w[j - 15] >> 18) | (w[j - 15] << 14);
            const uint32_t s2 = (w[j - 15] >> 3);
            const uint32_t s3 = (w[j - 2] >> 17) | (w[j - 2] << 15);
            const uint32_t s4 = (w[j - 2] >> 19) | (w[j - 2] << 13);
            const uint32_t s5 = (w[j - 2] >> 10);

            w[j] = w[j - 16] + s0 + s1 + s2 + w[j - 7] + s3 + s4 + s5;
        }

        a = h[0];
        b = h[1];
        c = h[2];
        d = h[3];
        e = h[4];
        f = h[5];
        g = h[6];
        h_temp = h[7];

        for (j = 0; j < 64; j++) {
            const uint32_t s1 = (e >> 6) | (e << 26);
            const uint32_t s2 = (e >> 11) | (e << 21);
            const uint32_t s3 = (e >> 25) | (e << 7);
            const uint32_t ch = (e & f) ^ (~e & g);
            const uint32_t temp1 = h_temp + s3 + ch + k[j] + w[j];
            const uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            const uint32_t temp2 = s1 + maj;

            h_temp = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        h[0] += a;
        h[1] += b;
        h[2] += c;
        h[3] += d;
        h[4] += e;
        h[5] += f;
        h[6] += g;
        h[7] += h_temp;
    }

    std::memcpy(digest, h, sizeof(h));
}