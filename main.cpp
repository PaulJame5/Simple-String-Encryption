/// EZ Encryption v0.1 Program for encypting string messages
/// By Paul O'Callaghan
/// Began 19/8/19
/// Updated 20/8/19
/// Known Issues: Has a major security flaw where messages could be deciphered by process of eliminaton if someone was to look at the pattern at which the letters and words pront out 
/// or brute force it to print out
/// Known Bugs: NA as i can tell yet

#include <iostream>
#include <string>
#include <stdlib.h> 

const int ENCRYPTION_STRENGTH = 3;
int keySeed = 5;

std::string charactersScrambled[128];

std::string encryptMessage(std::string t_message, int t_unlockKey);
std::string decryptMessage(std::string t_message, int t_unlockKey);
void setUpCharacters(int t_seed);

int main()
{
    // Set all characters in string set to null string
    for(int index = 0; index < 128; index++)
    {
        charactersScrambled[index] = "";    
    }
    
  std::string message;
  
  // enter your message hello encrypted fyuuccjk_jk_vhq
  getline (std::cin, message);
  std::cout << "Your message before encryption: " << message << "!\n";
  
  // After Encryption
  //message = encryptMessage(message, keySeed);
  //std::cout << "Your message after encryption: " << message << " !\n";
  message = decryptMessage(message, keySeed);
  // After Decryption
  std::cout << "Your message after decryption: " << message << "!\n";
}


std::string encryptMessage(std::string t_message, int t_unlockKey)
{
    // create a tempory empty string that we will populate with the translated data
    std::string encryptedMessage = "";
    
    setUpCharacters(t_unlockKey);
    
    for(unsigned int i = 0; i < t_message.size(); i++)
    {
        for(int j = 0; j < 128; j++)
        {
            char currentChar = j;
            if(t_message[i] == currentChar)
            {
                encryptedMessage += charactersScrambled[j];
                break;
            }
        }
        
    }
    return encryptedMessage;
}


std::string decryptMessage(std::string t_message, int t_unlockKey)
{
    // create a tempory empty string that we will populate with the translated data
    std::string decryptedMessage = "";
    
    setUpCharacters(t_unlockKey);
    
   unsigned int i = 0;
   
    while(i < t_message.size())
    {
        std::string temp_msg = "";
        
        for(int j = 0; j < ENCRYPTION_STRENGTH; j++)
        {
            temp_msg += t_message[i+j];
        }
        
        for(int j = 0; j < 128; j++)
        {
            // if the scrambled msg is equal to the tempmsg string we add the decimal char to the decryptedMsg string
            if(charactersScrambled[j] == temp_msg)
            {
                char charDec = j;
                decryptedMessage += charDec;
                break; // we break out of the loop as it's been found
            }
        }
        // We add the amount of characters we are convertng to translate to i
        i += ENCRYPTION_STRENGTH;
    } // END While LOOp
    return decryptedMessage;   
}

void setUpCharacters(int t_seed)
{
    // initialise seed
    srand(t_seed);
    
    for(int i = 0; i < 128; i++)
    {
        
        // Assign characters to 3 random characters
        for(int j = 0; j < ENCRYPTION_STRENGTH; j++)
        {
            unsigned int x = rand() % (127 - 94) + 94;
            
            char randomChar = x;
            charactersScrambled[i] += randomChar;
        } // end for loop for assigning rand characters
        
        // check values are not the same as anything else
        for(int j = 0; j < i; j++)
        {
            if(charactersScrambled[j] == charactersScrambled[i])
            {
                
                // We clear the string
                charactersScrambled[i] = "";   
                // We set the index back one to try again
                --i;
                break;
            }
        } // end of for loop for checking characters are not the same
        
    } // end for loop
    
}
