
#ifndef _FILE_ENCRYPTER_HPP_
#define _FILE_ENCRYPTER_HPP_

#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include "duthomhas/csprng.hpp"
#include <openssl/sha.h>
#include "alg.hpp"

#define DEBUG 1

#define SIMMETRY_KEY_LEN 64

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::experimental::filesystem::path;
using duthomhas::csprng;

enum Algorithm {
    Cesar = 1, 
    SimmetryLast = 10, ///< Unused
    Unknown
};

class FileEncrypter {

public:
    /**
     *  Функция вызыввется из фронта для шифрования выбранного файла. 
     *  Должна создавать выходной файл и записывать в него хедер.
     *  
     *  @param file_path - путь до входного файла
     *  @param algorithm - число из enum Algorithm, 
     *  @param quantity_keys - на стартовой версии  равно 1.
     *  @param encypt_key - пароли в виде массивов длиной 512 байт
     */
    int Encrypt (string& file_path, 
                  uint64_t algorithm, 
                  uint64_t quantity_keys, 
                  vector<vector<uint8_t>>  &encrypt_key);
    uint64_t GetAlgorithm (string& encrypt_file_path);

    /**
     * Функция должна расщифровывать файл по заданному пути. 
     * Она должна парсить хедер зашифрованного файла, 
     * получать реальный ключ, 
     * проверять, что введенные пользователем данные верны. 
     * После чего, создавать файл и 
     * вызывать нужный алгоритм для расшифрования
     *
     * @param decrypt_key - 512 байт, описывающие пользовательский ввод
     */
    int  Decrypt (string& encrypt_file_path, 
                  vector<uint8_t> &decrypt_key); 
};

#endif // _FILE_ENCRYPTER_HPP_
