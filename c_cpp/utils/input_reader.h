/** 
 * @file input_reader.h
 * 
 * @brief Quick utils to read some value.
 *
 * @note For now, only int and float.
 *       As a string is project dependent and needs further treatment,
 *       see an exemple in the OOP project "shoppingBasket".
 */

#ifndef __INPUT_READER_H__
#define __INPUT_READER_H__

/*****************************************************************************
 * @brief Clear remaining chars in stdin's buffer.
 *
 * @warning If used without a user-input fn beforehand (such as fgets or scanf),
 *          it will behave like them. And the input will simply be lost.
 * 
 * @example Here's a workflow example on how to use it alongside fgets
 *          if ( ! fgets(...) )
 *              RETURN EIO
 * 
 *          Look for '\n'
 *          p = strchr(buffer, '\n')
 *          if ( ! p )
 *              clear_remaining_stdin();
 *              RETURN ERROR_INPUT_TOO_LONG
 * 
 *          *p = '\0';  Replace '\n' with '\0'
 * 
 *          Further validation/treatment project dependent
 *          ...
 *****************************************************************************/
void clear_remaining_stdin(void);

/*****************************************************************************
 * @brief Read an int
 * @param  i Address where to store the read int
 * @return NEGATIVE value during input validation, without updating i
 *         POSITIVE value during input parsing   , without updating i
 *         0 if no error encountered and update i.
 *****************************************************************************/
int readInt(int *i);

/*****************************************************************************
 * @brief Read a float
 * @param  f Address where to store the read float
 * @return NEGATIVE value during input validation, without updating f
 *         POSITIVE value during input parsing   , without updating f
 *         0 if no error encountered and update f.
 *****************************************************************************/
int readFloat(float *f);

#endif /* __INPUT_READER_H__ */
