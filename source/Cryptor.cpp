#include "Cryptor.h"

#include "file_encrypter.hpp"


Cryptor::Cryptor(QObject* parent) {

}

void Cryptor::setAlgorithm(Algorithm algorithm) {
    m_algorithm = algorithm;
}

void Cryptor::setFile(QString fileName) {
    m_fileName = fileName;
}

void Cryptor::setKeyForCaesar(int key) {
    m_ceasarKey = key;
}

Cryptor::Result Cryptor::encryptionResult() {
    FileEncrypter fe;
    string fileName = m_fileName.toStdString();
    vector<vector<u_int8_t>> passwords(m_passwords.begin(), m_passwords.end());
    int res = fe.Encrypt(fileName, m_algorithm, m_passwords.size(), passwords);
    return res ? Result::Error : Result::Success;
}

void Cryptor::addNewPass(QString newPass) {
//    char* pass = newPass.toStdString().c_str();
//    pass = base64(pass);
//    m_passwords.append();
}

void Cryptor::setDecryptionPass(QString pass) {
    m_decryptionPassword = pass;
}

Cryptor::Result Cryptor::decryptionResult() {
    return Result::Error;
}
