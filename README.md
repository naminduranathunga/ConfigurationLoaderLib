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

## Change Log

#### 2.0.0
    
- Default block can be access directly by ConfigurationList object
    - ConfigurationList::GetPropertyValue(string name)
    - ConfigurationList::SetPropertyValue(string name, string value)
- Added a new save() function to save the configuration to the file to current filename or specified filename
- Bug fixes #1
- Improved error handling


## Installation

You can build the source code with CMake or download a release from the [releases]() page.

### Use with CMake

Copy the include and lib folders to your project directory. (Place them as you wish) 

```cmake
#...
project(my_project)
#...

add_executable(my_project main.cpp)
target_link_libraries(my_project "${CMAKE_SOURCE_DIR}/lib/libconfiguration-loader.a")

#...
```

### Compile with g++

```bash
g++ main.cpp lib/libconfiguration-loader.a
```


## Usage

Version 2 is compatible with version 1. You can simply include header files in include folder and use lib files in lib folder for linking. Also you can build the source code with CMake.

```cpp
#include "include/ConfigurationLoaderLib.h"

int main()
{
    ConfigurationList loader("test.xml");
    loader.SetPropertyValue("test", "test");
    loader.save();
    return 0;
}
```


### create a new configuration file:

```cpp
ConfigurationList* config = new ConfigurationList("config.txt");
config->AddBlock("user");
config->GetBlock("user")->AddProperty("username", this->username);
config->GetBlock("user")->AddProperty("password", this->password);
config->GetBlock("user")->AddProperty("type", to_string(this->type));
config->SaveToFile();
```


### Openinig a file

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



## ConfigurationList File Format

The file format is a simple text file with key-value pairs grouped into blocks. At the basic level the file can store key-value pairs without any grouping. The library treat it as the default block. The default block can be access directly by ConfigurationList object. (version 2.0.0)

```text
# person.txt
name=John
age=20
height=180
gender=male
```

You can define a block with a name by enclosing the name in square brackets. The block name is **case sensitive**. The block name can contain any character except the square brackets. The block name can be empty. The library treat it as the default block. 

```text
# options.txt
[main-page]
option1=value1
option2=value2

[search-page]
option1=value1
option2=value2

```
You can create multiple blocks with the same name. The library will treat them as different blocks. 

```text
# address-book.txt
[address]
name=John
address=123, Main Street.
phone=1234567890

[address]
name=Jane
address=456, Main Street.
phone=0987654321

[address]
name=Jack
address=789, Main Street.
phone=1357924680
```

You can put mixed data with default block and blocks. 

```text
# mixed.txt
name=John
age=20

[book]
title=The C++ Programming Language
author=Bjarne Stroustrup
year=1985

[book]
title=The C Programming Language
author=Dennis Ritchie
year=1978
```

You can use # character to comment out a line. The library will ignore the line. **Unfortunately, comments will be lost when you save the file.**

