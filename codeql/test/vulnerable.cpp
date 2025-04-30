#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <openssl/md5.h>
#include <openssl/des.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

// 1. Hardcoded secret key (Embedded Secret)
const string SECRET_KEY = "my$ecretK3y"; // Vulnerability: Hardcoded sensitive information

// 2. Hardcoded database credentials (Embedded Secret)
const string DB_USERNAME = "admin";      // Vulnerability: Hardcoded username
const string DB_PASSWORD = "password123"; // Vulnerability: Hardcoded password

// 3. Insecure password hashing
// 5. Command Injection vulnerability
void ping(const string& host) {
    string command = "ping -c 1 " + host; // Vulnerability: Unsanitized input in system command
    system(command.c_str());
}

// 6. Insecure deserialization
void load(const string& data) {
    FILE* file = fopen("temp.dat", "wb");
    fwrite(data.c_str(), 1, data.size(), file);
    fclose(file);
    file = fopen("temp.dat", "rb");
    char buffer[256];
    fread(buffer, 1, sizeof(buffer), file); // Vulnerability: Deserializing untrusted input
    fclose(file);
    cout << "Loaded data: " << buffer << endl;
}

// 7. Cross-Site Scripting (XSS) vulnerability
void greet(const string& name) {
    cout << "<h1>Hello, " << name << "!</h1>" << endl; // Vulnerability: Unsanitized input in HTML output
}

// 8. Insecure HMAC comparison
void calculate(const string& expression) {
    string command = "echo $(( " + expression + " ))"; // Vulnerability: Executing untrusted input
    system(command.c_str());
}

// 10. Insecure random number generation
string generate_token() {
    char token[9];
    for (int i = 0; i < 8; ++i)
        token[i] = 'A' + rand() % 26; // Vulnerability: rand() is not cryptographically secure
    token[8] = '\0';
    return string(token);
}

// 11. Weak encryption method
string weak_encrypt(const string& data, char key) {
    string encrypted = data;
    for (size_t i = 0; i < data.size(); ++i) {
        encrypted[i] ^= key; // Vulnerability: Weak encryption using XOR with a single-byte key
    }
    return encrypted;
}

// 12. Triple DES encryption method
string encrypt_health_info(const string& data, const string& key) {
    if (key.size() != 24) {
        throw invalid_argument("Key must be 24 bytes for Triple DES.");
    }

    DES_cblock key1, key2, key3;
    memcpy(key1, key.data(), 8);
    memcpy(key2, key.data() + 8, 8);
    memcpy(key3, key.data() + 16, 8);

    DES_key_schedule ks1, ks2, ks3;
    DES_set_key_unchecked(&key1, &ks1);
    DES_set_key_unchecked(&key2, &ks2);
    DES_set_key_unchecked(&key3, &ks3);

    string encrypted(data.size(), '\0');
    for (size_t i = 0; i < data.size(); i += 8) {
        DES_cblock input, output;
        memcpy(input, data.data() + i, min(size_t(8), data.size() - i));
        DES_ecb3_encrypt(&input, &output, &ks1, &ks2, &ks3, DES_ENCRYPT);
        memcpy(&encrypted[i], output, min(size_t(8), data.size() - i));
    }

    return encrypted;
}

int main() {
    // Example usage of the vulnerable functions
    string username = "user1";

    string host = "example.com";
    ping(host);

    string data = "example data";
    load(data);

    string name = "<script>alert('XSS');</script>";
    greet(name);

    string password = "password";

    string expression = "1 + 2";
    calculate(expression);

    cout << "Generated token: " << generate_token() << endl;

    string signature = "d41d8cd98f00b204e9800998ecf8427e";

    string sensitive_data = "SensitiveData";
    char encryption_key = 'K';
    string encrypted_data = weak_encrypt(sensitive_data, encryption_key);
    cout << "Encrypted data: " << encrypted_data << endl;

    string health_info = "BloodGlucose:120";
    string des_key = "123456789012345678901234"; // Vulnerability: Hardcoded key
    string encrypted_health_info = encrypt_health_info(health_info, des_key);
    cout << "Encrypted health info: " << encrypted_health_info << endl;

    return 0;
}
