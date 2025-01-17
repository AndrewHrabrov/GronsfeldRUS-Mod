#include <modAlphaCipher.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>

modAlphaCipher::modAlphaCipher(const std::wstring& skey) {
    for (unsigned i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    key = convert(getValidKey(skey));
}

std::wstring modAlphaCipher::encrypt(const std::wstring& open_text) {
    std::vector<int> work = convert(getValidText(open_text));
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text) {
    std::vector<int> work = convert(getValidText(cipher_text));
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

std::wstring modAlphaCipher::checkValid(std::wstring& source, std::wstring& cipher) {
    if (source == decrypt(cipher)) {return decrypt(cipher);}
    else {
        throw modAlphaCipher_error("Invalid cipher text! ");
    }
}

inline std::vector<int> modAlphaCipher::convert(const std::wstring& s) {
    std::vector<int> result;
    for (auto c : s) {
        result.push_back(alphaNum[c]);
    }
    return result;
}

inline std::wstring modAlphaCipher::convert(const std::vector<int>& v) {
    std::wstring result;
    for (auto i : v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}


inline std::wstring modAlphaCipher::getValidKey(const std::wstring & s)
{
    if (s.empty()) {
        throw modAlphaCipher_error("Empty key!");
    }
    std::wstring temp(s);
    for (auto& v : temp) {
        if (iswlower(v)) {
            v = towupper(v);
        }
        
        if (!(v >= L'А' && v <= L'Я' || v == L'Ё')) {
            throw modAlphaCipher_error(std::string("Key has invalid symbols! "));
        }
    }
    return temp;
}

inline std::wstring modAlphaCipher::getValidText(const std::wstring & s)
{
    if (s.empty()) {
        throw modAlphaCipher_error("Empty text!");
    }
    std::wstring tmp(s);
    for (auto &c : tmp) {
        if (iswlower(c)) {
            c = towupper(c);
        }
        
        if (!(c >= L'А' && c <= L'Я' || c == L'Ё')) {
            throw modAlphaCipher_error(std::string("Text has invalid symbols! "));
        }
    }
    return tmp;
}