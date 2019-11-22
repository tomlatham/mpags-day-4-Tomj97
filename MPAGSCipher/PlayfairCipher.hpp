#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

// Standard library includes
#include <string>
#include <vector>
#include <map>

#include "CipherMode.hpp"

/**
* \file PLayfairCipher.hpp
*  \brief Contains the declaration of the PLayfairCipher class
*/



struct Coordinate
{

  unsigned long x,y;
  Coordinate(unsigned long a, unsigned long b){this->x=a; this->y=b;}


  bool operator< (const Coordinate& c) const {
    return std::make_pair(x,y) < std::make_pair(c.x, c.y);
  }

};







/**
* \class PlayfairCipher
* \brief Encrypt or decrypt text using the playfair cipher with the given key
*/
class PlayfairCipher {
	public:
	/**
	 * Create a new PlayfairCipher with the given key
	 *
	 * \param key the key to use in the cipher
	 */
	explicit PlayfairCipher( const std::string& key);
	
	
      /**
     * Apply the cipher to the provided text
     *
     * \param inputText the text to encrypt or decrypt
     * \param cipherMode whether to encrypt or decrypt the input text
     * \return the result of applying the cipher to the input text
     */
	
  std::string applyCipher( const std::string& inputText, const CipherMode cipherMode ) const;
  	
	
	
	
        private:
                /// The cipher key.
		std::string key_;
                
                /// Key_map, char: (column, row)
                std::map<char, Coordinate> letterCoordinateMap_;

               /// Keymap., (column, row): char
               std::map<Coordinate, char> coordinateLetterMap_;

              /**
              * \brief Set the key for the PlayfairCipher
              * \param key PlayfairCipher key
              */
              void setKey(const std::string &key);

             /**
              * \brief Set up the input text for encryption
              * \param inputText the text to encrypt
              * \return string formatted for input to the PlayFair cipher.
              */
              std::string setText(const std::string  &inputText) const;
};
#endif
