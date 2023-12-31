#include <ConfigurationLoaderLib.h>
#include <stdexcept>

using namespace std;

ConfigurationList::ConfigurationList() {
	this->filename = "";
	this->isLoaded = false;
	blocks = vector<PropertyBlock*>();  // Namindu - issue #1
}

ConfigurationList::ConfigurationList(string filename) {
	this->filename = filename;
	this->isLoaded = false;
	blocks = vector<PropertyBlock*>();  // Namindu - issue #1
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
		//throw "Error saving to file";
		throw runtime_error("Error saving to file");  // Namindu - issue #2
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
	if (name == ""){
		name = "unnamed";
	}

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
		//throw "Block name cannot be empty";
		throw runtime_error("Block name cannot be empty");  // Namindu - issue #2
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

// Namindu - adding new save function
void ConfigurationList::save(string filename) {
	if (filename == "") {
		filename = this->filename;
	}

	ofstream file(filename, std::ofstream::out | std::ofstream::trunc);

	if (!file.is_open()) {
		//throw "Error saving to file";
		throw runtime_error("Error saving to file : " + filename);  // Namindu - issue #2
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

string ConfigurationList::GetPropertyValue(string name){
	//get the default block
	PropertyBlock* block = this->GetBlock();
	if (block == nullptr) {
		return "";
	}
	return block->GetPropertyValue(name);
}

//SetPropertyValue(string name, string value)
void ConfigurationList::SetPropertyValue(string name, string value){
	//get the default block
	PropertyBlock* block = this->GetBlock();
	if (block == nullptr) {
		block = new PropertyBlock("unnamed");
		this->AddBlock(block);
	}
	block->AddProperty(name, value);
}