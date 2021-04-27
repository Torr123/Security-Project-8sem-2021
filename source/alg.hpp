#ifndef _ALG_HPP_
#define _ALG_HPP_

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>

#include <openssl/bio.h>
#include <openssl/evp.h>

char* base64(const unsigned char* input, int length);

unsigned char* decode64(const char* input, int length);

int Cezar_Encrypt(std::ifstream& file, std::ofstream& file_out, std::vector<uint8_t> vec);

int Cezar_Decrypt(std::ifstream& encrypted_file, std::ofstream& file_out, std::vector<uint8_t> vec);

#endif // _ALG_HPP_
