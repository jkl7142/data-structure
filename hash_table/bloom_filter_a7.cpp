/*
*   Exercise 16 : 이메일 주소 중복 검사
*/

#include <iostream>
#include <vector>
#include <openssl/md5.h>

class BloomFilter {
    int nHashes;
    // 블룸 필터
    std::vector<bool> bits;

    static constexpr int hashSize = 128 / 8;     // 128bits (16bytes)

    // 해시 값 버퍼
    unsigned char hashValue[hashSize];

public:
    BloomFilter(int size, int hashes) : bits(size), nHashes(hashes) {
        if (nHashes > hashSize) {   // 16bytes 이상의 해시 함수 사용은 불가능
            throw("해시 함수 개수가 너무 많습니다.");
        }

        if (size > 255) {   // 각 해시 값이 1byte이므로 255를 초과할 수 없음
            throw("블룸 필터 크기가 255보다 클 수 없습니다.");
        }
    }

    // MD5를 이용한 해시 함수
    void hash(const std::string& key) {
        MD5(reinterpret_cast<const unsigned char*>(key.data()), key.length(), hashValue);
    }

    // 이메일 주소 추가
    void add(const std::string& key) {
        hash(key);
        for (auto it = &hashValue[0]; it < &hashValue[nHashes]; it++) {
            bits[*it & bits.size()] = true;
        }

        std::cout << "블룸 필터에 추가: " << key << std::endl;
    }

    // 이메일 주소 검색
    bool mayContatin(const std::string& key) {
        hash(key);
        for (auto it = &hashValue[0]; it < &hashValue[nHashes]; it++) {
            if (!bits[*it % bits.size()]) {
                std::cout << key << " : 사용할 수 있는 이메일입니다." << std::endl;
                return false;
            }
        }

        // 블룸 필터 값이 전부 true면
        std::cout << key << " : 이미 사용 중입니다." << std::endl;
        return true;
    }
};

int main() {

    BloomFilter bloom(128, 5);
    bloom.add("abc@gilbut.com");
    bloom.add("xyz@gilbut.com");

    bloom.mayContatin("abc");
    bloom.mayContatin("xyz@gilbut.com");
    bloom.mayContatin("xyz");

    bloom.add("abcd@gilbut.com");
    bloom.add("ab@gilbut.com");

    bloom.mayContatin("abcd");
    bloom.mayContatin("ab@gilbut.com");

    return 0;
}