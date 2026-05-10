/** 
 * @file random_bool.h
 * 
 * @brief Quickly generate a pseudo-random boolean value
 */
#ifndef __RANDOM_BOOL_H__
#define __RANDOM_BOOL_H__

/*****************************************************************************
 * @brief Quickly generate a pseudo-random boolean value2
 * @param bit Bit to take as boolean value
 * 
 * Conditions that I've set myself:
 *     - Use a funny hexa value
 *     - Modulo/Xor a prime number
 *     - Use one bit of the result as the boolean
 *****************************************************************************/
char rand_bool(char bit);

#endif /* __RANDOM_BOOL_H__ */