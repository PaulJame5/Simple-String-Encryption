/// EZ Encryption v0.2 Program for encypting string messages
/// By Paul O'Callaghan
/// Began 19/8/19
/// Updated 20/8/19
/// Known Issues: Fixed last issue of repeated patterns. Could still be brute forced if the pattern is known but less likely now.
/// Another issue is if we were to overflow the string the message would not produce the characters to get all of the message
/// Known Bugs: NA as i can tell yet

#include <iostream>
#include <string>
#include <stdlib.h> 

const int ENCRYPTION_STRENGTH = 15;
int keySeed = 45;

std::string charactersScrambled[128];

// 0 = encrypt, 1 = decrypt
const int OPTION = 1;

// SET UP 
std::string encryptMessage(std::string t_message, int t_unlockKey);
std::string decryptMessage(std::string t_message, int t_unlockKey);
void setUpCharacters(int t_seed);

int main()
{
    
    
  std::string message = "Hello, world!";
  // Hello, world! encryptted is equal to this with encryption strength set to 15 and keySeed at 45
  std::string messageToDecrypt = "mkmatkv`mtlhhaqwwrqdrmv`x^kbal}ge{g}t^ydylis`rzvo`^lzaqnzmlyom^|sxwz|{yy~b{jhxsayc^zgaedbzjm|`azims`lxjpiwqkhcrwucg}}`gzcbnuadvyfof^gietctaklot}~p|rt{h^ijuipnnunmyn|cbedvrxul~cwjg^rskdwebkwjgp_n^";
  
  
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
