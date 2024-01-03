# ConfigurationLoaderLib

## Description

This library provides a simple way to load and save string key-value pairs from and to a file. The file format is a simple text file with key-value pairs grouped into blocks. The library is written in C++ and uses the standard library.

```text
[Block1]
key1=value1
key2=value2

[Block2]
key3=value3
```

## Usage

Project is precompiled as a static library. with visual studio. Simply include header files in include folder and use lib files in lib folder for linking.

## Example

```cpp
// open existing file
#include <iostream>
#include <ConfigurationLoaderLib.h>

int main()
{
    ConfigurationLoaderLib::ConfigurationLoader loader("config.txt");
    loader.LoadFromFile();
    if (!loader.IsLoaded()){
        throw "Handle file not found error";
    }

    std::cout << loader.GetBlock("Block1")->GetPropertyValue("key1") << std::endl;
    std::cout << loader.GetBlock("Block1")->GetPropertyValue("key2") << std::endl;
    std::cout << loader.GetBlock("Block2")->GetPropertyValue("key3") << std::endl;

    return 0;
}
```
if a block does not exists, it will return nullptr. If a property does not exists, it will return an empty string.


To create a new configuration file:

```cpp
ConfigurationList* config = new ConfigurationList("config.txt");
config->AddBlock("user");
config->GetBlock("user")->AddProperty("username", this->username);
config->GetBlock("user")->AddProperty("password", this->password);
config->GetBlock("user")->AddProperty("type", to_string(this->type));
config->SaveToFile();
```

