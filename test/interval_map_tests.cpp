#include "ut.hpp"

#include "interval_map.h"

#include <sstream>

using namespace boost::ut;

int main() {
    "create(int)"_test = [] {
        try {
            fadeev::IntervalMap<int, int> mp;
            expect(true);
        } catch (std::exception& ex) {
            expect(false) << "Exception happened while construction: " << ex.what() << "\n";
        }
    };

    "create(char)"_test = [] {
        try {
            fadeev::IntervalMap<int, char> mp;
            expect(true);
        } catch (std::exception& ex) {
            expect(false) << "Exception happened while construction: " << ex.what() << "\n";
        }
    };

    "insert(int)"_test = [] {
        try {
            fadeev::IntervalMap<int, int> mp;
            mp[1].insert(1, 2);
            expect(true);
        } catch (std::exception& ex) {
            expect(false) << "Exception happened: " << ex.what() << "\n";
        }
    };

    "insert(char)"_test = [] {
        try {
            fadeev::IntervalMap<int, char> mp;
            mp[1].insert('1', '2');
            expect(true);
        } catch (std::exception& ex) {
            expect(false) << "Exception happened: " << ex.what() << "\n";
        }
    };

    "insert_faulty_interval(int)"_test = [] {
        try {
            fadeev::IntervalMap<int, int> mp;
            mp[1].insert(2, 1);
            expect(false) << "Exception is expected\n";
        } catch (std::exception& ex) {
            expect(true) << "Exception happened: " << ex.what() << "\n";
        }
    };

    "insert_faulty_interval(char)"_test = [] {
        try {
            fadeev::IntervalMap<int, int> mp;
            mp[1].insert('2', '1');
            expect(false) << "Exception is expected\n";
        } catch (std::exception& ex) {
            expect(true) << "Exception happened: " << ex.what() << "\n";
        }
    };


    "insert_val_check(int)"_test = [] {
        try {
            fadeev::IntervalMap<int, int> mp;
            mp[1].insert(1, 2);

            std::list<std::pair<int, int>> expectVal{{1, 2}};
            expect(mp[1].data() == expectVal);
        } catch (std::exception& ex) {
            expect(false) << "Exception happened: " << ex.what() << "\n";
        }
    };

    "insert_val_check(char)"_test = [] {
        try {
            fadeev::IntervalMap<int, char> mp;
            mp[1].insert('1', '2');

            std::list<std::pair<char, char>> expectVal{{'1', '2'}};
            expect(mp[1].data() == expectVal);
        } catch (std::exception& ex) {
            expect(false) << "Exception happened: " << ex.what() << "\n";
        }
    };

    // ---------

    "multi_insert_val_check1(int)"_test = [] {
        try {
            fadeev::IntervalMap<int, int> mp;
            mp[1].insert(1, 2);
            mp[1].insert(-1 , 0);

            std::list<std::pair<int, int>> expectVal{{-1, 0}, {1, 2}};
            expect(mp[1].data() == expectVal);
        } catch (std::exception& ex) {
            expect(false) << "Exception happened: " << ex.what() << "\n";
        }
    };

    "multi_insert_val_check2(int)"_test = [] {
        try {
            fadeev::IntervalMap<int, int> mp;
            mp[1].insert(1, 2);
            mp[1].insert(3 , 5);

            std::list<std::pair<int, int>> expectVal{{1, 2}, {3, 5}};
            expect(mp[1].data() == expectVal);
        } catch (std::exception& ex) {
            expect(false) << "Exception happened: " << ex.what() << "\n";
        }
    };

    "multi_insert_overlap1(int)"_test = [] {
        try {
            fadeev::IntervalMap<int, int> mp;
            mp[1].insert(1, 2);
            mp[1].insert(-1 , 1);

            std::list<std::pair<int, int>> expectVal{{-1, 2}};
            expect(mp[1].data() == expectVal);
        } catch (std::exception& ex) {
            expect(false) << "Exception happened: " << ex.what() << "\n";
        }
    };

    "multi_insert_overlap2(int)"_test = [] {
        try {
            fadeev::IntervalMap<int, int> mp;
            mp[1].insert(1, 3);
            mp[1].insert( 2, 4);

            std::list<std::pair<int, int>> expectVal{{1, 4}};
            expect(mp[1].data() == expectVal);
        } catch (std::exception& ex) {
            expect(false) << "Exception happened: " << ex.what() << "\n";
        }
    };

    "multi_insert_overlap3(int)"_test = [] {
        try {
            fadeev::IntervalMap<int, int> mp;
            mp[1].insert(1, 5);
            mp[1].insert( 2, 4);

            std::list<std::pair<int, int>> expectVal{{1, 5}};
            expect(mp[1].data() == expectVal);
        } catch (std::exception& ex) {
            expect(false) << "Exception happened: " << ex.what() << "\n";
        }
    };

    "multi_insert_overlap4(int)"_test = [] {
        try {
            fadeev::IntervalMap<int, int> mp;
            mp[1].insert(3, 5);
            mp[1].insert( 6, 8);
            mp[1].insert(4, 7);

            std::list<std::pair<int, int>> expectVal{{3, 8}};
            expect(mp[1].data() == expectVal);
        } catch (std::exception& ex) {
            expect(false) << "Exception happened: " << ex.what() << "\n";
        }
    };

    "multi_insert_overlap5(int)"_test = [] {
        try {
            fadeev::IntervalMap<int, int> mp;
            mp[1].insert(3, 5);
            mp[1].insert( 6, 8);
            mp[1].insert(1, 10);

            std::list<std::pair<int, int>> expectVal{{1, 10}};
            expect(mp[1].data() == expectVal);
        } catch (std::exception& ex) {
            expect(false) << "Exception happened: " << ex.what() << "\n";
        }
    };

    "multi_insert(int)"_test = [] {
        try {
            fadeev::IntervalMap<int, int> mp;
            mp[1].insert(1, 2);
            mp[1].insert( 5, 6);
            mp[2].insert(1, 10);
            mp[3].insert(1, 5);
            mp[3].insert(4, 11);

            std::list<std::pair<int, int>> expectVal1{{1, 2}, {5, 6}};
            std::list<std::pair<int, int>> expectVal2{{1, 10}};
            std::list<std::pair<int, int>> expectVal3{{1, 11}};
            expect(mp[1].data() == expectVal1);
            expect(mp[2].data() == expectVal2);
            expect(mp[3].data() == expectVal3);
        } catch (std::exception& ex) {
            expect(false) << "Exception happened: " << ex.what() << "\n";
        }
    };

    "multi_insert(char)"_test = [] {
        try {
            fadeev::IntervalMap<int, int> mp;
            mp[1].insert('1', '2');
            mp[1].insert( '5', '6');
            mp[2].insert('1', '9');
            mp[3].insert('1', '5');
            mp[3].insert('4', '9');

            std::list<std::pair<int, int>> expectVal1{{'1', '2'}, {'5', '6'}};
            std::list<std::pair<int, int>> expectVal2{{'1', '9'}};
            std::list<std::pair<int, int>> expectVal3{{'1', '9'}};
            expect(mp[1].data() == expectVal1);
            expect(mp[2].data() == expectVal2);
            expect(mp[3].data() == expectVal3);
        } catch (std::exception& ex) {
            expect(false) << "Exception happened: " << ex.what() << "\n";
        }
    };

    "multi_insert_print(int)"_test = [] {
        try {
            fadeev::IntervalMap<int, int> mp;
            mp[1].insert(1, 2);
            mp[1].insert( 5, 6);
            mp[2].insert(1, 9);
            mp[3].insert(1, 5);
            mp[3].insert(4, 9);

            std::stringstream output;
            output << mp;
            std::string str = output.str();


            expect(output.str() == "[{1 : (1, 2), (5, 6)}, {2 : (1, 9)}, {3 : (1, 9)}]") << "Invalid printing of map: " << output.str();

        } catch (std::exception& ex) {
            expect(false) << "Exception happened: " << ex.what() << "\n";
        }
    };

    "multi_insert_print(char)"_test = [] {
        try {
            fadeev::IntervalMap<int, char> mp;
            mp[1].insert('1', '2');
            mp[1].insert( '5', '6');
            mp[2].insert('1', '9');
            mp[3].insert('1', '5');
            mp[3].insert('4', '9');

            std::stringstream output;
            output << mp;
            std::string str = output.str();


            expect(output.str() == "[{1 : (1, 2), (5, 6)}, {2 : (1, 9)}, {3 : (1, 9)}]") << "Invalid printing of map: " << output.str();

        } catch (std::exception& ex) {
            expect(false) << "Exception happened: " << ex.what() << "\n";
        }
    };

    "multi_insert_print_random_order(int)"_test = [] {
        try {
            fadeev::IntervalMap<int, int> mp;
            mp[3].insert(1, 5);
            mp[1].insert( 5, 6);
            mp[3].insert(4, 9);
            mp[2].insert(1, 9);
            mp[1].insert(1, 2);

            std::stringstream output;
            output << mp;
            std::string str = output.str();


            expect(output.str() == "[{1 : (1, 2), (5, 6)}, {2 : (1, 9)}, {3 : (1, 9)}]") << "Invalid printing of map: " << output.str();

        } catch (std::exception& ex) {
            expect(false) << "Exception happened: " << ex.what() << "\n";
        }
    };

    return 0;
}