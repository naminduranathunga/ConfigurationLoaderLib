#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#ifndef CONFIGURATIONLIST_H 
#define CONFIGURATIONLIST_H 1

#include <string>
#include <fstream>
#include <vector>
#include "PropertyBlock.h"

class ConfigurationList {
private:
	vector<PropertyBlock*> blocks;
	string filename;
	bool isLoaded;

public:
	ConfigurationList();
	ConfigurationList(string filename = "");
	~ConfigurationList();

	/*
	* @brief get a single block by name
	* @param name the name of the block
	* @return the block PropertyBlock*
	*/
	PropertyBlock* GetBlock(string name);

	/*
	* @brief get all blocks by name
	* @param name the name of the block (optional
	* @return the blocks vector<PropertyBlock*>
	*/
	vector<PropertyBlock*> GetBlocks(string name);
	vector<PropertyBlock*> GetBlocks() const;

	/*
	* @brief adds a new block
	* @param name of the block
	* @return the blocks PropertyBlock*
	*/
	PropertyBlock* AddBlock(string block);

	/*
	* @brief adds a new block
	* @param pointer of the new block
	* @return void
	*/
	void AddBlock(PropertyBlock* block);

	/*
	* @brief sets the filename
	* This will change the property is loaded to false
	* @param filename the filename string
	*/
	void SetFilename(string filename);

	/*
	* @brief gets the filename
	* @return the filename string
	*/
	string GetFilename() const;

	/*
	* @brief checks if the configuration is loaded
	*/
	bool IsLoaded() const;

	/*
	* @brief Loads the configuration from the file
	*/
	void LoadFromFile();

	/*
	* @brief Saves the configuration to the file
	*/
	void SaveToFile();
};

#endif