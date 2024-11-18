#include "KVPair.h"
#include "TreeMap.h"
#include <string>

int main(int argc, char const *argv[])
{
    TreeMap<std::string, int> mapInstance;
    KVPair<std::string, int> node01 = KVPair<std::string, int>("first", 1);
    KVPair<std::string, int> node02 = KVPair<std::string, int>("second", 2);
    mapInstance.add(node01);
    mapInstance.add(node02);

    mapInstance.printInOrder();

    std::cout << "before: " << mapInstance.count() << '\n';

    mapInstance.removeKey("second");
    
    std::cout << "after: " << mapInstance.count() << '\n';

    KVPair<std::string, int> *mI = mapInstance.toArray();

    for (int i = 0; i < mapInstance.count(); i++) {
        std::cout << '{' << mI[i].getKey() << ", " << mI[i].getValue() << "}\n";
    }

    return 0;
}
