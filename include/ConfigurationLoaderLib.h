/**
 * ConfigurationLoaderLib 
 * 
 * @brief A simple library to load and save text based key-value configuration information.
 * 
 * @version 2.0.0
 * @date 2024-04-05
 * @author Namindu S. Ranathunga (http://namindu.tk)
 * @website https://github.com/naminduranathunga/ConfigurationLoaderLib 
 * @license MIT
 * 
 * 
 * Changes from version 1.0.0
 *  - Default block can be access directly by ConfigurationList object
 *      - ConfigurationList::GetPropertyValue(string name)
 *      - ConfigurationList::SetPropertyValue(string name, string value)
 *  - Added a new save() function to save the configuration to the file to current filename or specified filename
 *  - Bug fixes #1
 *  - Improved error handling
*/

#ifndef CONF_LOADER_LIB_H
#define CONF_LOADER_LIB_H

#include "ConfigurationList.h"
#include "PropertyBlock.h"

#endif // !CONF_LOADER_LIB_H
