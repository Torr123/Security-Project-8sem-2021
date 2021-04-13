#ifndef CRYPTOR_H
#define CRYPTOR_H

#include <vector>

#include <QObject>

#include "file_encrypter.hpp"

class Cryptor : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Algorithm algorithm WRITE setAlgorithm)
    Q_PROPERTY(QString file WRITE setFile)
    Q_PROPERTY(int keyForCaesar WRITE setKeyForCaesar)
    Q_PROPERTY(Result encryptionResult READ encryptionResult)
    Q_PROPERTY(QString newPass WRITE addNewPass)
    Q_PROPERTY(QString decryptionPass WRITE setDecryptionPass)
    Q_PROPERTY(Result decryptionResult READ decryptionResult)

public:
    enum Result {
        Success,
        Error
    };
    Q_ENUMS(Result)
    Q_ENUMS(Algorithm)
    explicit Cryptor(QObject *parent = nullptr);
    void setAlgorithm(Algorithm algorithm);
    void setFile(QString fileName);
    void setKeyForCaesar(int key);
    Result encryptionResult();
    void addNewPass(QString newPass);
    void setDecryptionPass(QString pass);
    Result decryptionResult();

private:
    Algorithm m_algorithm;
    QString m_fileName;
    QVector<vector<uint8_t>> m_passwords;
    int m_ceasarKey;
    QString m_decryptionPassword;
};
#endif // CRYPTOR_H
