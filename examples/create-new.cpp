#include <ConfigurationLoaderLib.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    ConfigurationList* list = new ConfigurationList("test.conf");
    list->LoadFromFile();

    if (!list->IsLoaded())
    {
        cout << "File not found" << endl;
        list->AddBlock("block1");
    }

    list->GetBlock("block1")->AddProperty("name", "value");
    list->GetBlock("block1")->AddProperty("name2", "value2");
    list->GetBlock("block1")->AddProperty("name3", "value3");


    //print block1
    cout << "Block1" << endl;
    vector<string> names = list->GetBlock("block1")->GetPropertyNames();
    for (int i = 0; i < names.size(); i++)
    {
        cout << names[i] << "=" << list->GetBlock("block1")->GetPropertyValue(names[i]) << endl;
    }

    //save
    list->SaveToFile();
        
    return 0;
}