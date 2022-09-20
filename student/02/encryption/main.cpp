#include <iostream>
#include <string>
#include <cctype>

using namespace std;

const string KEY_LENGTH_ERROR = "Error! The encryption key must contain 26 characters.";
const string KEY_CASE_ERROR = "Error! The encryption key must contain only lower case characters.";
const string KEY_ALPHABET_ERROR = "Error! The encryption key must contain all alphabets a-z.";
const string TEXT_CASE_ERROR = "Error! The text to be encrypted must contain only lower case characters.";

const int KEY_LENGTH = 26;

bool check_key_length(string key)
{
  if(key.length() == KEY_LENGTH)
  return true;
  else return false;
}

bool check_key_lowercase(string key)
{
  for (char c : key)
    {
      if(!islower(c))
        {
          return false;
        }
    }
    return true;
}

bool check_key_alphabet(string key)
{
  for(int i = 97; i<=122; i++)
    {
      char c = i;
      if(key.find(c) == string::npos)
        {
          return false;
        }
    }

  return true;
}


bool check_key(string key)
{
  if(!check_key_length(key))
    {
      cout << KEY_LENGTH_ERROR << endl;
      return false;
    }

  if(!check_key_lowercase(key))
    {
      cout << KEY_CASE_ERROR << endl;
      return false;
    }

  if(!check_key_alphabet(key))
    {
      cout << KEY_ALPHABET_ERROR << endl;
      return false;
    }

  return true;
}


string encrypt_text(string plaintext, string key)
{
  string encrypt_text = "";

  for (uint i = 0; i < plaintext.length(); i++ )
    {
        char c = plaintext.at(i);
        uint key_index = (uint) c - (uint) 'a';
        char c_encrypt = key.at(key_index);
        encrypt_text += c_encrypt;
     }
   return encrypt_text;
}


int main()
{

  string key = "";
  string plaintext = "";

  cout << "Enter the encryption key: ";
  cin >> key;

  if(!check_key(key))
    {
      return EXIT_FAILURE;
    }
  cout << "Enter the text to be encrypted: ";
  cin >> plaintext;

  if(!check_key_lowercase(plaintext))
    {
      cout << TEXT_CASE_ERROR << endl;
      return EXIT_FAILURE;
    }
  cout << "Encrypted text: "<< encrypt_text(plaintext,key) << endl;

  return 0;
}
