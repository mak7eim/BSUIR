#include <iostream>
#include "Map.h"
#include "Set.h"
#include "unordered_map.h"


int main() {

    unord_map<int, std::string, h<int>> table;
    std::pair<int, std::string> my_pair(11, "фывапр");
    table.insert(my_pair);
    std::cout << table.contain(11);
    table[12] = "йй";
    std::cout << table[12] << table.contain(12) << table[11] << "\nsize - "
              << table.size() << '\n';
    table.clear();

    Set<std::string> s;
    s.insert("цц");
    s.insert("уу");
    s.insert("кк");
    Set<std::string>::Iterator it = s.begin();
    for (it; it != s.end(); ++it) {
        std::cout << *it << "\n";
    }

    Map<std::string, int> m;
    m["гш"] = 5;
    m["м"] = 7;
    m["ддщ"] = 9;
    m.clear();
    m["тсттмь"] = 228;
    Map<std::string, int>::Iterator iter = m.begin();


    for (iter; iter != m.end(); ++iter) {
        std::cout << *iter << " ";
    }


    // std::cout << "\n sz - " << m.size() << '\n';
    //std::cout << m[0] << " " << m[13] <<" " << m.empty() << " "<< m.size() << std::endl;
    return 0;
}
