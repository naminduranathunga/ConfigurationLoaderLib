#include "ConfigurationLoaderLib.h"

using namespace std;

/**
* Constructors
*/
PropertyBlock::PropertyBlock() {
	this->name = "unnamed";
}

PropertyBlock::PropertyBlock(string name) {
	this->name = name;
}

PropertyBlock::PropertyBlock(PropertyBlock*& block) {
	vector<string> names = block->GetPropertyNames();

	for (int i = 0; i < names.size(); i++) {
		this->AddProperty(names[i], block->GetPropertyValue(names[i]));
	}
}




void PropertyBlock::SetName(string name) {
	this->name = name;
}

string PropertyBlock::GetName() {
	return this->name;
}

void PropertyBlock::AddProperty(string name, string value) {
	//search if name already exists
	for (int i = 0; i < this->names.size(); i++) {
		if (this->names[i] == name) {
			this->values[i] = value;
			return;
		}
	}

	//otherwise add new name and value
	this->names.push_back(name);
	this->values.push_back(value);
}


string PropertyBlock::GetPropertyValue(string name) {
	for (int i = 0; i < this->names.size(); i++) {
		if (this->names[i] == name) {
			return this->values[i];
		}
	}
	return "";
}

vector<string> PropertyBlock::GetPropertyNames() const {
	return this->names;
}

