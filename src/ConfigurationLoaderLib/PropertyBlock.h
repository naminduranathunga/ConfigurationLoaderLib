#pragma once

#ifndef PROPERTYBLOCK_H
#define PROPERTYBLOCK_H 1

#include <string>
#include <vector>

using namespace std;

class PropertyBlock {
private:
	string name;
	vector<string> names;
	vector<string> values;

public:
	/**
	* @brief Constructor
	* @param name The name of the property block as string (Optional)
	*/
	PropertyBlock();
	PropertyBlock(string name = "");
	PropertyBlock(PropertyBlock*& block);

	/**
	* @brief Sets the name of the property block
	* @param name The name of the property block as string
	*/
	void SetName(string name);

	/**
	* @brief Gets the name of the property block
	* @return The name of the property block as string
	*/
	string GetName();

	/**
	* @brief Adds a property to the property block
	*
	* This function will check if the property already exists and if so, it will update the value of the property.
	* Otherwise it will add a new property to the property block.
	*
	* @param name The name of the property as string
	*/
	void AddProperty(string name, string value);

	/**
	* @brief Gets the value of a property
	* @param name The name of the property as string
	* @return The value of the property or empty if not found as string
	*/
	string GetPropertyValue(string name);

	/**
	* @brief Get all property names
	* @return A vector of all property names as string read-only
	*/
	vector<string> GetPropertyNames() const;


};

#endif