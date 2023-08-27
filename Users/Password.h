#ifndef LIBRARY_SYSTEM_PASSWORDSECURITY_H
#define LIBRARY_SYSTEM_PASSWORDSECURITY_H

#include <string>

class Password {
private:
std::string word;
std::string hash;
bool hash_exists;
public:
    Password(std::string &new_word);
    std::string calculate_hash();
    void sha256(const char* message, uint32_t message_len, uint8_t* digest);
};


#endif //LIBRARY_SYSTEM_PASSWORDSECURITY_H
