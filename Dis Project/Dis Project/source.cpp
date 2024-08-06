#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class Set
{
public:
     set<int> intSet;
     set<char> charSet;

    void createSet( string type)
    {
        if (type == "int") 
        {
            int num;
             cout << "Enter elements of the set (enter -1 to stop): " <<  endl;
            while ( cin >> num && num != -1)
            {
                intSet.insert(num);
            }
        }
        else if (type == "char")
        {
            char ch;
             cout << "Enter elements of the set (enter '#' to stop): " <<  endl;
            while ( cin >> ch && ch != '#') 
            {
                charSet.insert(ch);
            }
        }
        else
        {
             cout << "Invalid set type." <<  endl;
        }
    }

    void displaySet( string type) 
    {
        if (type == "int") 
        {
            if (intSet.empty())
            {
                 cout << "The set is empty." <<  endl;
            }
            else 
            {
                 cout << "The set is: { ";
                for (auto it = intSet.begin(); it != intSet.end(); it++) 
                {
                     cout << *it << " ";
                }
                 cout << "}" <<  endl;
            }
        }
        else if (type == "char") 
        {
            if (charSet.empty()) 
            {
                 cout << "The set is empty." <<  endl;
            }
            else
            {
                 cout << "The set is: { ";
                for (auto it = charSet.begin(); it != charSet.end(); it++)
                {
                     cout << *it << " ";
                }
                 cout << "}" <<  endl;
            }
        }
        else 
        {
             cout << "Invalid set type." <<  endl;
        }
    }

    Set unionSet(Set other) 
    {
        Set result;
        for (auto it = intSet.begin(); it != intSet.end(); it++) 
        {
            result.intSet.insert(*it);
        }
        for (auto it = other.intSet.begin(); it != other.intSet.end(); it++)
        {
            result.intSet.insert(*it);
        }
        for (auto it = charSet.begin(); it != charSet.end(); it++)
        {
            result.charSet.insert(*it);
        }
        for (auto it = other.charSet.begin(); it != other.charSet.end(); it++) 
        {
            result.charSet.insert(*it);
        }
        return result;
    }

    Set intersectionSet(Set other)
    {
        Set result;
         set_intersection(intSet.begin(), intSet.end(), other.intSet.begin(), other.intSet.end(),  inserter(result.intSet, result.intSet.begin()));
         set_intersection(charSet.begin(), charSet.end(), other.charSet.begin(), other.charSet.end(),  inserter(result.charSet, result.charSet.begin()));
        return result;
    }

    bool subsetCheck(Set other) 
    {
        if (intSet.size() > other.intSet.size() || charSet.size() > other.charSet.size()) 
        {
            return false;
        }
        if (intSet.size() == other.intSet.size() && charSet.size() == other.charSet.size()) 
        {
            return (intSet == other.intSet && charSet == other.charSet);
        }
        if (intSet.size() == other.intSet.size())
        {
            return (intSet == other.intSet);
        }
        if (charSet.size() == other.charSet.size())
        {
            return (charSet == other.charSet);
        }
        return false;
    }

    Set differenceSet(Set other) 
    {
        Set result;
         set_difference(intSet.begin(), intSet.end(), other.intSet.begin(), other.intSet.end(),  inserter(result.intSet, result.intSet.begin()));
         set_difference(charSet.begin(), charSet.end(), other.charSet.begin(), other.charSet.end(),  inserter(result.charSet, result.charSet.begin()));
        return result;
    }

     set< set<int>> powerSet() 
     {
         set< set<int>> result;
         set<int> empty;
        result.insert(empty);
        for (auto it = intSet.begin(); it != intSet.end(); it++)
        {
             set< set<int>> temp;
            for (auto it2 = result.begin(); it2 != result.end(); it2++) 
            {
                 set<int> newSet(*it2);
                newSet.insert(*it);
                temp.insert(newSet);
            }
            result.insert(temp.begin(), temp.end());
        }
        return result;
    }

    int cardinality() 
    {
        return intSet.size() + charSet.size();
    }

    bool setEqual(Set other)
    {
        return (intSet == other.intSet && charSet == other.charSet);
    }

    void complementSet(Set universalSet)
    {
        Set result;
        for (auto it = universalSet.intSet.begin(); it != universalSet.intSet.end(); it++)
        {
            if (intSet.find(*it) == intSet.end())
            {
                result.intSet.insert(*it);
            }
        }
        for (auto it = universalSet.charSet.begin(); it != universalSet.charSet.end(); it++)
        {
            if (charSet.find(*it) == charSet.end())
            {
                result.charSet.insert(*it);
            }
        }
         cout << "Complement: ";
        result.displaySet("int");
        result.displaySet("char");
    }

    void saveToFile( string filename)
    {
         ofstream outfile(filename);
        if (outfile.is_open()) 
        {
            outfile << "intSet: ";
            for (auto it = intSet.begin(); it != intSet.end(); it++)
            {
                outfile << *it << " ";
            }
            outfile <<  endl;
            outfile << "charSet: ";
            for (auto it = charSet.begin(); it != charSet.end(); it++)
            {
                outfile << *it << " ";
            }
            outfile <<  endl;
            outfile.close();
        }
        else
        {
             cout << "Unable to open file." <<  endl;
        }
    }

    void loadFromFile( string filename) 
    {
         ifstream infile(filename);
        if (infile.is_open())
        {
             string line;
             getline(infile, line);
             istringstream iss(line);
            int num;
            char ch;
            while (iss >> num) 
            {
                intSet.insert(num);
            }
             getline(infile, line);
             istringstream chars(line);
            while (chars >> ch) 
            {
                charSet.insert(ch);
            }
            infile.close();
        }
        else
        {
             cout << "Unable to open file." <<  endl;
        }
    }
};

int main()
{
    Set set1, set2, set3, universalSet;
     string filename;
    int choice;

    while (true) 
    {
         cout << "1. Create set\n2. Display set\n3. Union\n4. Intersection\n5. Subset check\n6. Difference\n7. Power set\n8. Cardinality\n9. Set equality\n10. Set complement\n11. Save to file\n12. Load from file\n13. Quit" <<  endl;
         cin >> choice;

        switch (choice)
        {
        case 1:
        {
             string type;
             cout << "Enter set type (int or char): ";
             cin >> type;
            set1.createSet(type);
            break;
        }
        case 2: 
        {
             string type;
             cout << "Enter set type (int or char): ";
             cin >> type;
            set1.displaySet(type);
            break;
        }
        case 3: 
        {
            set3 = set1.unionSet(set2);
             cout << "Union: ";
            set3.displaySet("int");
            set3.displaySet("char");
            break;
        }
        case 4:
        {
            set3 = set1.intersectionSet(set2);
             cout << "Intersection: ";
            set3.displaySet("int");
            set3.displaySet("char");
            break;
        }
        case 5:
        {
            if (set1.subsetCheck(set2)) 
            {
                 cout << "Set 1 is a subset of Set 2." <<  endl;
            }
            else 
            {
                 cout << "Set 1 is not a subset of Set 2." <<  endl;
            }
            break;
        }
        case 6: 
        {
            set3 = set1.differenceSet(set2);
             cout << "Difference: ";
            set3.displaySet("int");
            set3.displaySet("char");
            break;
        }
        case 7: 
        {
             cout << "Power set: ";
            auto powerSet = set1.powerSet();
            for (const auto& subset : powerSet) 
            {
                 cout << "{ ";
                for (const auto& elem : subset)
                {
                     cout << elem << " ";
                }
                 cout << "} ";
            }
             cout <<  endl;
            break;
        }
        case 8:
        {
             cout << "Cardinality: " << set1.cardinality() <<  endl;
            break;
        }
        case 9: 
        {
            if (set1.setEqual(set2))
            {
                 cout << "Sets are equal." <<  endl;
            }
            else 
            {
                 cout << "Sets are not equal." <<  endl;
            }
            break;
        }
        case 10: 
        {
            universalSet = set1.unionSet(set2);
            set1.complementSet(universalSet);
            break;
        }
        case 11:
        {
             cout << "Enter filename: ";
             string filename;
             cin >> filename;
            set1.saveToFile(filename);
            break;
        }
        case 12: 
        {
             cout << "Enter filename: ";
             string filename;
             cin >> filename;
            set1.loadFromFile(filename);
            break;
        }
        case 13: 
        {
             cout << "Exiting program." <<  endl;
            return 0;  // Exit program
        }
        default:
        {
             cout << "Invalid choice." <<  endl;
            break;
        }
        }
    }

    return 0;
}
