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

    auto relations = map.getRelation("4541865");
    std::cout.precision(15);
    for(auto w : relations->getWays())
    {
        std::cout << w.first->getId() << std::endl;
        for(auto n : w.first->getNodes())
        {
            std::cout << n->getCoordinates()->x << " " << n->getCoordinates()->y << std::endl;
        }
        std::cout << std::endl;

    }


	return 0;
}
