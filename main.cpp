/// EZ Encryption v0.2.1 Program for encypting string messages
/// By Paul O'Callaghan
/// Began 19/8/19
/// Updated 21/8/19
/// Known Issues: Fixed last issue of memory for string. Could still be brute forced by setting up a loop and printing out results to a text file but it would prevent data being
/// used easily by large companies providing messaging services or at least slow them down for a little while.
/// Known Bugs: The characters currently used aren't using capitals for some reason will fix in later update problem is probably @ line 138

#include <iostream>
#include <string>
#include <stdlib.h> 

const int ENCRYPTION_STRENGTH = 50000;
int keySeed = 4587483463;

std::string charactersScrambled[128];

// 0 = encrypt, 1 = decrypt
const int OPTION = 0;

// SET UP 
std::string encryptMessage(std::string t_message, int t_unlockKey);
std::string decryptMessage(std::string t_message, int t_unlockKey);
void setUpCharacters(int t_seed);

int main()
{
    
    
  std::string message = "Hello, Anita!";
  // Hello, world! encryptted is equal to this with encryption strength set to 15 and keySeed at 45
  std::string messageToDecrypt = "kfvyfs^wpho{aak^bvznztpkrpwfpod__rxtzs~zvfqkgbdo_vqopirv{biczw_le ";
  
  
  // Encryption
  if(OPTION == 0)
  {
      //std::cout << "Enter your message for encryption: ";
     // getline (std::cin, message);
      message = encryptMessage(message, keySeed);
      std::cout << "Your message after encryption: " << std::endl;
      std::cout << message;
  }
  // Decrypt
  else if(OPTION == 1)
  {
     // std::cout << "Enter your message for decryption: ";
    //  getline (std::cin, message);
      message = decryptMessage(messageToDecrypt, keySeed);
      std::cout << "Your message after decryption: " << message << "!\n";
  }
  else
  {
      std::cout << "Invalid option";
  }
}


std::string encryptMessage(std::string t_message, int t_unlockKey)
{
    // create a tempory empty string that we will populate with the translated data
    std::string encryptedMessage = "";
    
    // We allocate the memory for the encryption characters
    encryptedMessage.reserve(t_message.length() * ENCRYPTION_STRENGTH);
    
    for(unsigned int i = 0; i < t_message.size(); i++)
    {
        setUpCharacters(t_unlockKey + i);
        
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
    
    
   unsigned int i = 0;
   
    while(i < t_message.size())
    {
        setUpCharacters(t_unlockKey);
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
                t_unlockKey += 1;
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
    // Set all characters in string set to null string
    for(int index = 0; index < 128; index++)
    {
        charactersScrambled[index] = "";    
    }
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
