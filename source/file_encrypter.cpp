#include "file_encrypter.hpp"


#if DEBUG > 0
/*void Cezar_Encrypt (ifstream& input_file, ofstream& output_file, vector<uint8_t> encrypt_key) {
    return;
}

void Cesar_Decrypt (ifstream& input_file, ofstream& output_file,
        vector<uint8_t> true_key) {
    return;
}*/
#endif

int FileEncrypter::Encrypt (string& file_path, 
                  uint64_t algorithm, 
                  uint64_t quantity_keys, 
                  vector<vector<uint8_t>>  &encrypt_key) {

    ifstream input_file;
    input_file.open (file_path, ifstream::in | ifstream::binary);
    string out_filename (string("enc_") + path (file_path).filename ().string());
    ofstream output_file;
    output_file.open (out_filename, ofstream::out | ofstream::binary);

    input_file.seekg (0);
    output_file.seekp (0);
    
    output_file.write ((char *)&algorithm, sizeof (uint64_t));
    output_file.write ((char *)&quantity_keys, sizeof (uint64_t));
    //output_file << quantity_keys;
    
    csprng rng;

    for (unsigned i = 0; i < quantity_keys; i++){
        vector<uint8_t> copy_key (encrypt_key[i].begin (), 
                encrypt_key[i].end());
        auto salt = rng (vector<uint8_t> (16));
        uint8_t * first_hash = NULL;
        uint8_t * second_hash = NULL;
        copy_key.insert (copy_key.end(), salt.begin (), salt.end());
        first_hash = SHA512 (
                &(copy_key[0]), 
                copy_key.size(), 
                NULL);
        second_hash = SHA512 (first_hash, SIMMETRY_KEY_LEN, NULL);
        
        for (unsigned j = 0; j < salt.size (); j++) {
            //std::cout << salt[j] << " ";
        }
        //std::cout << std::endl;
        output_file.write ((char *) (&salt[0]), salt.size ());

        output_file.write ((char *) second_hash, SIMMETRY_KEY_LEN);

        for (unsigned j = 0; j < SIMMETRY_KEY_LEN; j++) {
            first_hash[j] = first_hash[j] ^ encrypt_key[0][j];
        }
        output_file.write ((char *) first_hash, SIMMETRY_KEY_LEN);
    }
    
    int ret = 0;
    if (algorithm == 1) {
        ret = Cezar_Encrypt (input_file, output_file, encrypt_key[0]);
    }
    else {
        std::cerr << "Unknown algorithm\n";
        return -1;
    }

    input_file.close ();
    output_file.close ();

    return ret;
}

uint64_t FileEncrypter::GetAlgorithm (string& encrypt_file_path) {
    ifstream input_file;
    input_file.open (encrypt_file_path, ifstream::in | ifstream::binary);
    uint64_t result = 0;

    input_file.seekg (0);
    input_file.read ((char *) &result, sizeof (uint64_t));

    input_file.close ();

    return result;
}

int FileEncrypter::Decrypt (string& encrypt_file_path, 
                  vector<uint8_t> &decrypt_key) {
    ifstream input_file;
    input_file.open (encrypt_file_path, ifstream::in | ifstream::binary);
    string out_filename (
            "decr_" + path (encrypt_file_path).filename ().string());
    ofstream output_file;
    output_file.open (out_filename, ofstream::out | ofstream::binary);

    input_file.seekg (0);
    output_file.seekp (0);

    uint64_t algorithm = 0;
    uint64_t quantity_keys = 0;

    input_file.read ((char *) (&algorithm), sizeof (uint64_t));
    input_file.read ((char *) (&quantity_keys), sizeof (uint64_t));

    uint8_t crypt_key[SIMMETRY_KEY_LEN] = {0};
    bool find_key = false;
    for (unsigned i = 0; i < quantity_keys; i++) {
        uint8_t            salt[16] = {0};
        vector<uint8_t>  copy_key (decrypt_key.begin (), 
                decrypt_key.end());
        uint8_t          *second_hash = NULL;
        uint8_t          *first_hash = NULL;
        uint8_t          readed_second_hash[SIMMETRY_KEY_LEN] = {0};

        input_file.read ((char *) salt, 16);
        copy_key.insert (copy_key.end(), salt, salt + 16);
        input_file.read ((char *) readed_second_hash, SIMMETRY_KEY_LEN);

        first_hash = SHA512 (
                &(copy_key[0]), 
                copy_key.size(), 
                NULL);
        second_hash = SHA512 (first_hash, SIMMETRY_KEY_LEN, NULL);
        
        bool equal = true;
        for (unsigned j = 0; j < SIMMETRY_KEY_LEN; j++) {
            if (second_hash[j] != readed_second_hash[j]) {
                equal = false;
                break;
            }
        }

        if (equal) {
            uint8_t hash_xor_key[SIMMETRY_KEY_LEN] = {0};
            input_file.read ((char *) hash_xor_key, SIMMETRY_KEY_LEN);
            for (unsigned j = 0; j < SIMMETRY_KEY_LEN; j++)
                crypt_key[j] = hash_xor_key[j] ^ first_hash[j];
            //std::cout << unsigned (crypt_key[0]) << std::endl;
            find_key = true;
        }
    }

    if (!find_key) {
        std::cerr << "Unknown key\n";
        return -1;
    }

    vector<uint8_t> true_key(SIMMETRY_KEY_LEN);

    true_key.assign (crypt_key, crypt_key + SIMMETRY_KEY_LEN);
    //std::cout << unsigned (true_key[0]) << std::endl;

    int ret = Cezar_Decrypt (input_file, output_file, true_key);

    input_file.close ();
    output_file.close ();

    return ret;
}



