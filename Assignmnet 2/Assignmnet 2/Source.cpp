#include<iostream>
#include<sqlite3.h>
#include<sqlcpp.h>
#include<iomanip>
#include<string>
#include<stdlib.h>
#include<vector>

constexpr const char* db_file = DB_PATH "\\Countries.db";

static int countryChoice{};
static int cityChoice{};
static int stateChoice{};
const char* SQL_in_C{};
std::string SQL_in_Str{};

void queryCountry(sqlite3* db, sqlite3_stmt* stmt) {

    sqlite3_prepare_v2(db, "SELECT * FROM countries", -1, &stmt, nullptr);
    int col_count = sqlite3_column_count(stmt);
    for (int i = 0; i < col_count; ++i) {
        std::cout << sqlite3_column_name(stmt, i);
        if (i < col_count - 1) 
            printf("  |  ");
    }

    std::cout << std::endl;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        for (int i = 0; i < col_count; ++i) {
            printf("\t%s", sqlite3_column_text(stmt, i));
            std::cout << std::setw(6);
            if (i < col_count - 1)
                std::cout << " -> ";
        }
        std::cout << std::endl;
    }
}

/*
*  queryStates is function which takes sqlite3 stmt and db as input.
*   and query data useing sqlite3_prepapre_v2(); and return
*/

void queryStates(sqlite3* db, sqlite3_stmt* stmt) {
    std::vector<int> indexOfStates{};

    if (stateChoice < 0 )
    {
        std::cout << "Enter Valid Index::";
    }
    else {
        SQL_in_Str = "Select * from states where country_id =" + std::to_string(countryChoice);
        SQL_in_C = SQL_in_Str.c_str();
        sqlite3_prepare_v2(db, SQL_in_C, -1, &stmt, nullptr);
        int col_count = sqlite3_column_count(stmt);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            //indexOfStates.push_back(sqlite3_column_int(stmt, 0));
            for (int i = 0; i < col_count; ++i) {
                printf("%s", sqlite3_column_text(stmt, i));
                if (i < col_count - 1)
                    std::cout << " -> ";
            }
            std::cout << std::endl;
        }
    }

    //for (auto& i : indexOfStates) {
      //  std::cout << i <<" ";
    //}
    std::cout<< std::endl;
}

/*
*  queryCities is function which takes sqlite3 stmt and db as input. 
*   and query data useing sqlite3_prepapre_v2();
*/

void queryCities(sqlite3* db, sqlite3_stmt* stmt) {
    if (cityChoice < 0)
    {
        std::cout << "Enter Valid Index::";
    }
    else {
        SQL_in_Str = "Select * from Cities where state_id = " + std::to_string(stateChoice);
        SQL_in_C = SQL_in_Str.c_str();
        sqlite3_prepare_v2(db, SQL_in_C, -1, &stmt, nullptr);
        int col_count = sqlite3_column_count(stmt);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            for (int i = 0; i < col_count; ++i) {
                printf("%s", sqlite3_column_text(stmt, i));
                if (i < col_count - 1)
                    std::cout << " -> ";
            }
            std::cout << std::endl;
        }
    }
}

int main() {
    int choice = 0;
    std::string country{};
	sqlite3* db = nullptr;
	sqlite3_stmt* stmt = nullptr;
	std::cout << sqlite3_libversion();

    int rc = sqlite3_open(db_file, &db);
    if (rc == SQLITE_OK) {
        puts("database open");
    }
    else {
        puts(sqlite3_errstr(rc));
        exit(1);
    }
    queryCountry(db, stmt);
    std::cout << "Select country_id :";
    std::cin >> countryChoice;
    system("CLS");
    queryStates(db, stmt);
    std::cout << "Enter State_id:";
    std::cin >> stateChoice;
    system("CLS");
    queryCities(db, stmt);
    std::cout << "Enter City_id:";
    std::cin >> cityChoice;
    system("CLS");
    std::cout << "\t::Your Selections are::";



}