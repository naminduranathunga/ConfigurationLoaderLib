#include "ConfigurationLoaderLib.h"

using namespace std;

ConfigurationList::ConfigurationList() {
	this->filename = "";
	this->isLoaded = false;
}

ConfigurationList::ConfigurationList(string filename) {
	this->filename = filename;
	this->isLoaded = false;
}

ConfigurationList::~ConfigurationList() {
	vector<PropertyBlock*>::iterator it = this->blocks.begin();
	while (it != this->blocks.end()) {
		delete *it;
		it++;
	}
	this->blocks.erase(this->blocks.begin(), this->blocks.end());
}

//loading from file
void ConfigurationList::LoadFromFile() {
	ifstream file(this->filename);

	if (!file.is_open()) {
		this->isLoaded = false;
		return;
		//throw exception("File not found");
	}

	string line;
	PropertyBlock* block = new PropertyBlock("unnamed"); //unnamed block - this is the default block


	while (getline(file, line)) {
		//ignore comments and empty lines
		if (line.length() == 0 || line[0] == '#') {
			continue;
		}

		//Start of a new block [blockname]
		if (line[0] == '[') {
			this->blocks.push_back(block);
			int endofblock = line.find(']');
			block = new PropertyBlock(line.substr(1, endofblock - 1));
		}
		else {
			//name=value
			int pos = line.find('=');
			block->AddProperty(line.substr(0, pos), line.substr(pos + 1, line.length() - 1));
		}
	}

	this->blocks.push_back(block);

	file.close();
	this->isLoaded = true;
}


void ConfigurationList::SaveToFile() {
	/*ofstream fclear;
	fclear.open(this->filename, std::ofstream::out | std::ofstream::trunc);

	fclear.write("#Configuration file\n", 20);
	fclear.close();*/
	//return;
	ofstream file(this->filename, std::ofstream::out | std::ofstream::trunc);

	if (!file.is_open()) {
		throw exception("Error saving to file");
	}


	bool isNotFirst = true;
	for (int i = 0; i < this->blocks.size(); i++) {
		if (this->blocks[i]->GetName() != "unnamed") {
			if (!isNotFirst) {
				file << endl;
			}
			file << "[" << this->blocks[i]->GetName() << "]" << endl;
			isNotFirst = false;
		}

		vector<string> names = this->blocks[i]->GetPropertyNames();
		for (int j = 0; j < names.size(); j++) {
			file << names[j] << "=" << this->blocks[i]->GetPropertyValue(names[j]) << endl;
		}
	}

	file.close();
}


PropertyBlock* ConfigurationList::GetBlock(string name) {
	for (int i = 0; i < this->blocks.size(); i++) {
		if (this->blocks[i]->GetName() == name) {
			return this->blocks[i];
		}
	}
	return nullptr;
}

vector<PropertyBlock*> ConfigurationList::GetBlocks(string name) {
	vector<PropertyBlock*> blocks;

	for (int i = 0; i < this->blocks.size(); i++) {
		if (this->blocks[i]->GetName() == name) {
			blocks.push_back(this->blocks[i]);
		}
	}

	return blocks;
}

vector<PropertyBlock*> ConfigurationList::GetBlocks() const {
	return this->blocks;
}


PropertyBlock* ConfigurationList::AddBlock(string block) {
	if (block == "") {
		throw exception("Block name cannot be empty");
	}
	PropertyBlock* newBlock = new PropertyBlock(block);
	this->blocks.push_back(newBlock);
	return newBlock;
}

void ConfigurationList::AddBlock(PropertyBlock* block) {
	this->blocks.push_back(block);
}


void ConfigurationList::SetFilename(string filename) {
	this->filename = filename;
	this->isLoaded = false;
}

string ConfigurationList::GetFilename() const {
	return this->filename;
}

bool ConfigurationList::IsLoaded() const {
	return this->isLoaded;
}