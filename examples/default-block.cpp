/**
 * Added feature in version 2.0.0
 * 
 * in a configuration file, there is a default block which does not have a name.
 * This block can be accessed directly by the ConfigurationList object.
 * 
 * 
*/
#include <ConfigurationLoaderLib.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    // first create a simple configuration file
    cout << "Creating a new configuration file" << endl;
    ConfigurationList* list = new ConfigurationList("default-block.txt");
    list->SetPropertyValue("name", "Default Block");
    list->SetPropertyValue("text", "Hello! This is the default block");
    list->save(); // new save() function in version 2.0.0
    cout << endl;

    delete list;

    // now load the configuration file
    cout << "Loading the configuration file" << endl;
    list = new ConfigurationList("default-block.txt");
    list->LoadFromFile();

    // error handling
    if (!list->IsLoaded())
    {
        cout << "File not found" << endl;
        return 0;
    }

    // print the default block
    cout << "Default Block" << endl;
    cout << "name=" << list->GetPropertyValue("name") << endl;
    cout << "text=" << list->GetPropertyValue("text") << endl;
    cout << endl;
    system("pause");
        
    return 0;
}