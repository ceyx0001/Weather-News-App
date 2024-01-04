#include "LoginInfo.h"

using std::cout;
using std::endl;
using std::rotate;
using std::string;

namespace
{
    const int ALPHABET_LEN = 26;
    const int SHIFT = 13;

    /**
     * @brief ROT13 encrypt.
     * @details Encrypts a string message using a ROT13 cipher.
     * @param p is the string to encrypt.
     * @return The encrypted password.
     */
    string encrypt(string p)
    {
        string encryption = "";
        for (int i = 0; i < p.length(); i++)
        {
            if (isupper(p[i]))
            {
                encryption += (p[i] - 'A' + SHIFT) % ALPHABET_LEN + 'A';
            }
            else if (islower(p[i]))
            {
                encryption += (p[i] - 'a' + SHIFT) % ALPHABET_LEN + 'a';
            }
            else
            {
                encryption += p[i];
            }
        }
        cout << "Encrypted:" << encryption << endl;
        return encryption;
    }

    /**
     * @brief ROT13 decrypt.
     * @details Decrypts a string message using a ROT13 cipher.
     * @param ep is the string to dencrypt.
     * @return The decrypted password.
     */
    string decrypt(string ep)
    {
        string decryption = "";
        for (int i = 0; i < ep.length(); i++)
        {
            if (isupper(ep[i]))
            {
                decryption += (ep[i] - 'A' - SHIFT + ALPHABET_LEN) % ALPHABET_LEN + 'A';
            }
            else if (islower(ep[i]))
            {
                decryption += (ep[i] - 'a' - SHIFT + ALPHABET_LEN) % ALPHABET_LEN + 'a';
            }
            else
            {
                decryption += ep[i];
            }
        }
        cout << "Decrypted:" << decryption << endl;
        return decryption;
    }
}

/**
 * @brief Constructor.
 * @details Constructor for a LoginInfo object that initializes members.
 * @param username is the session's username.
 * @param password is the session's password.
 * @return Nothing.
 */
LoginInfo::LoginInfo(string username, string password) : username(username), db("LoginInfo", "username", {"username", "encryptedPassword"})
{
    encryptedPassword = password;
}

/**
 * @brief Default destructor.
 * @details Default destructor for a LoginInfo object
 * but does not do anything.
 * @return Nothing.
 */
LoginInfo::~LoginInfo() {}

/**
 * @brief Authenticate user info.
 * @details Determines if the LoginInfo user info matches
 * an entry in the database.
 * @return Whether or not the user info is correct.
 */
bool LoginInfo::authenticate()
{
    string matchUser = "username=\"" + username + "\"";
    string matchPass = "encryptedPassword=\"" + encryptedPassword + "\"";
    // cerr << "\nLoginInfo: querying db.\n";
    bool correct = false;
    if (db.exists({matchUser, matchPass}))
    {
        correct = true;
    }
    return correct;
}

/**
 * @brief Existence of username.
 * @details Determines if the LoginInfo username exists in the database.
 * @return Whether or not the username exists.
 */
bool LoginInfo::exists()
{
    return db.exists({"username=\"" + username + "\""});
}

/**
 * @brief Save user info.
 * @details Saves the LoginInfo user information to the database.
 * @return Nothing.
 */
void LoginInfo::saveData()
{
    db.saveData({username, encryptedPassword});
}

/**
 * @brief Delete user info.
 * @details Delete the LoginInfo user information to the database.
 * @return Nothing.
 */
void LoginInfo::delData()
{
    db.delData(username);
}

/**
 * @brief Get username.
 * @details Returns the username that is saved internally.
 * @return The username.
 */
string LoginInfo::getUsername()
{
    return username;
}

/**
 * @brief Get password.
 * @details Returns the password that is saved internally.
 * @return The password.
 */
string LoginInfo::getPassword()
{
    return encryptedPassword;
}