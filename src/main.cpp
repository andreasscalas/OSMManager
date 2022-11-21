#include <iostream>
#include <utils.h>
#include <root.h>
int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cerr << "No input file specified, thus nothing can be read." << std::endl;
        return 1;
    }


    std::string inputFileName = argv[1];
    std::string outputFileName = "output.osm";

    if(argc > 2)
        outputFileName = argv[2];
    OpenStreetMap::Root map;
    int retValue = map.load(inputFileName);
    if(retValue != 0)
    {
        std::cerr << "Error loading requested file" << std::endl;
        return 1;
    }

    int retValue1 = map.save(outputFileName);
    if(retValue1 != 0)
    {
        std::cerr << "Error saving the output file" << std::endl;
        return 2;
    }
	return 0;
}
