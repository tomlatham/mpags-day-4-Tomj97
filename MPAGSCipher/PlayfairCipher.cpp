// standard library includes 
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include<algorithm>

// Out project headers
#include "PlayfairCipher.hpp"
#include "CipherMode.hpp"

PlayfairCipher::PlayfairCipher( const std::string& key )
: key_{""}
{
	PlayfairCipher::setKey( key );
}

std::string PlayfairCipher::applyCipher ( const std::string& inputText, const CipherMode cipherMode ) const
{	
    //Changed the if statement to a switch.
   std::string outputText;
    switch (cipherMode) 
      {
        case CipherMode::Encrypt : 
	  {
            outputText = setText(inputText);
            break;
	  }
        case CipherMode::Decrypt : 
	  {
            outputText = inputText;
            break;
	  }
      }

    std::string charPair = "AA"; //digraph
    for (size_t i = 0; i<outputText.size(); i+=2) //i+=2 to loop over 2 letters 
      {
        std::copy(outputText.begin()+i, outputText.begin()+i+2, charPair.begin());

        Coordinate coordinateOne = (*letterCoordinateMap_.find(charPair[0])).second;
        Coordinate coordinateTwo = (*letterCoordinateMap_.find(charPair[1])).second;

        // Get new coordinates - map our way to the coordinates corresponding to the new letters we should have.
        if (coordinateOne.y == coordinateTwo.y)
	  {		//if we are encrypting map our way to coords. Else - go the opposite way along the map.
            if (cipherMode == CipherMode::Encrypt) {
                coordinateOne.x = (coordinateOne.x + 1) % 5;
                coordinateTwo.x = (coordinateTwo.x + 1) % 5;
            }
            else {
                coordinateOne.x = (coordinateOne.x - 1 + 5) % 5; 
                coordinateTwo.x = (coordinateTwo.x - 1 + 5) % 5;
            }
        }
        else if (coordinateOne.x == coordinateTwo.x) {
            if (cipherMode == CipherMode::Encrypt) 
	      {
                coordinateOne.y = (coordinateOne.y + 1) % 5;
                coordinateTwo.y = (coordinateTwo.y + 1) % 5;
	      }
            else 
	      {
                coordinateOne.y = (coordinateOne.y - 1 + 5) % 5;
                coordinateTwo.y = (coordinateTwo.y - 1 + 5) % 5;
	      }
        }
        else 
	  {
            //Coordinates make opposite corners of rectangle in the playfair grid.
           
            std::swap(coordinateOne.x, coordinateTwo.x);
	  }

        //Find the letter associated with the new coordinates on the square
        charPair[0] = (*coordinateLetterMap_.find(coordinateOne)).second;
        charPair[1] = (*coordinateLetterMap_.find(coordinateTwo)).second;
        outputText.replace(outputText.begin()+i, outputText.begin()+i+2, charPair);
    }
    // Return the text
    return outputText;
	
}

void PlayfairCipher::setKey( const std::string& key )
{
	
	
	const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	key_ = key;
	key_+=alphabet;
	
	//Change all characters in key to uppercase
	std::transform(key_.begin(), key_.end(), key_.begin(), 
	[] (unsigned char c) -> unsigned char 
	{
		return ::toupper(c);
		
	}
	);
	//Get rid of those pesky non-alpha characters.
	key_.erase(std::remove_if(key_.begin(), key_.end(),
	[] (unsigned char c) 
	{
		return !(std::isalpha(c));
		
	})
	,key_.end());
	//Change J to I in the key
	std::transform(key_.begin(), key_.end(), key_.begin(), 
	[] (unsigned char c)
	{
		if( c =='J')
		{
			c='I';
			
		}
		return c;
		
	}
	);
	
	std::string foundChars;
	//Remove all characters that are repeated in the key.
	key_.erase(std::remove_if(key_.begin(), key_.end(),
	[&foundChars] (unsigned char c) 
	{
		
		
		if(foundChars.find(c) == std::string::npos)
		{
			foundChars += c;
			return false;
			
		}
		return true;
		
		
		
	})
	,key_.end());
	
	
	
  //Store the coordinates of each letter into a map structure
  for (size_t i = 0; i<key_.size(); i++)
    {
      Coordinate coordinate = {i%5, i/5};
      letterCoordinateMap_.insert(std::pair<char, Coordinate> {key_[i],coordinate});
      coordinateLetterMap_[coordinate] = key_[i];

    }
	
	
	std::cout<< key_ << std::endl;
}





//Set up the input text for use in the encryption.
std::string PlayfairCipher::setText(const std::string &inputText) const
{
  



  std::string outputText = inputText;
  
  std::transform(outputText.begin(), outputText.end(), outputText.begin(), 
		 [] (char i)
		 {
		   
		   
		   return (i == 'J') ? 'I' : i;

		 }
		 );




  //if repeated characters occur add an X (Q if XX)
  for (size_t i{0}; i<outputText.size(); i+=2)
    {
        if (outputText[i] == outputText[i+1])
	  {
            if (outputText[i] == 'X')
	      {
                outputText.insert(i+1, "Q");
	      }
            else 
	      {
                outputText.insert(i+1, "X");
	      }
        }


    }

    //If the number of characters in the input string is an odd number, add a Z to the end.
    if (outputText.size() % 2 != 0){
        outputText += "Z";
    }

    return outputText;
    



}
