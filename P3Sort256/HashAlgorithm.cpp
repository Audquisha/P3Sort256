#include "HashAlgorithm.h"
std::vector<int> HashAlgorithm::convertInputToHash(std::vector<std::pair<std::string, std::string>>& givenDataSet) {
    // hashes each password inplace
    for (auto& nameAndPass : givenDataSet) {
        hash(nameAndPass.second);
    }
    //generates random keys from 0-31 and places them in a vector
    std::vector<int> orderOfKeys;
	while(orderOfKeys.size() != 32) {
        int key = rand() % 32;
		if (std::find(orderOfKeys.begin(), orderOfKeys.end(), key) == orderOfKeys.end()) {
			orderOfKeys.push_back(key);
		}
	}
    return orderOfKeys;
}
void HashAlgorithm::hash(std::string& input) {

    // To begin the algorithm you need the first 32 bits of the sqare roots of the first 8 prime numbers (one of the reasons everyones afraid of quantum is that this won't work anymore)
    uint32_t h0 = 0x6a09e667;
    uint32_t h1 = 0xbb67ae85;
    uint32_t h2 = 0x3c6ef372;
    uint32_t h3 = 0xa54ff53a;
    uint32_t h4 = 0x510e527f;
    uint32_t h5 = 0x9b05688c;
    uint32_t h6 = 0x1f83d9ab;
    uint32_t h7 = 0x5be0cd19;

    // Then you add a '1' bit to the end, then pad 0's at the end
    std::vector<unsigned char> msg(input.begin(), input.end());
    msg.push_back(0x80);
    while ((msg.size() * 8) % 512 != 448) msg.push_back(0x00);

    // Then you have to convert the orignal message length into bits then add as a 64-bit big-endian integer (this is the end of the first stage of the algorithm(only 3 more lol))
    uint64_t lengthInBits = static_cast<uint64_t>(input.size()) * 8;
    for (int i = 7; i >= 0; i--) msg.push_back(static_cast<unsigned char>((lengthInBits >> (i * 8)) & 0xff));

    // This is the main processing stage, if you really wanna know how the functions I added in the h file work, read the url, way too much documentation to explain here
    const size_t chunkCount = msg.size() * 8 / 512;
    for (size_t chunk = 0; chunk < chunkCount; chunk++) {

        uint32_t messageSchedule[64] = { 0 };

        // This is where I strong suggest reading documentation to understand what Im doing if you wanna know (moving chunks over into a messaging schedule in big-endian)
        for (int i = 0; i < 16; i++) {
            size_t index = chunk * 64 + i * 4;
            messageSchedule[i] =
                (static_cast<uint32_t>(msg[index]) << 24) |
                (static_cast<uint32_t>(msg[index + 1]) << 16) |
                (static_cast<uint32_t>(msg[index + 2]) << 8) |
                (static_cast<uint32_t>(msg[index + 3]));
        }

        //This is a weird part of the hash where you extend the first 16 words in the remaining 48 words
        for (int i = 16; i < 64; i++) {
            messageSchedule[i] =
                sigma1(messageSchedule[i - 2]) +
                messageSchedule[i - 7] +
                sigma0(messageSchedule[i - 15]) +
                messageSchedule[i - 16];
        }

        // More constants to make brute force attacks worse, these are working variables and the first 32 bits of the fractional parts of the cube roots of the first 64 primes

        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
        uint32_t e = h4;
        uint32_t f = h5;
        uint32_t g = h6;
        uint32_t h = h7;

        const uint32_t k[64] =
        {
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

        // This is considered the compression stage where we mess with the words we have created and actually begin forming the string (most of these formulas are online)

        for (int i = 0; i < 64; i++) {
            uint32_t temp1 = h + SIGMA1(e) + CH(e, f, g) + k[i] + messageSchedule[i];
            uint32_t temp2 = SIGMA0(a) + MAJ(a, b, c);
            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
        h5 += f;
        h6 += g;
        h7 += h;
    }

    // formating and cleanup to make the string finalized
    std::stringstream ss;
    ss << std::hex << std::setfill('0') << std::nouppercase;
    ss << std::setw(8) << h0;
    ss << std::setw(8) << h1;
    ss << std::setw(8) << h2;
    ss << std::setw(8) << h3;
    ss << std::setw(8) << h4;
    ss << std::setw(8) << h5;
    ss << std::setw(8) << h6;
    ss << std::setw(8) << h7;
	input = ss.str();
}




