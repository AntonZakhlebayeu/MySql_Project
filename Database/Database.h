#pragma once
#define ProjectDirectory RESOURCES_DIR

#include <iostream>
#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <fstream>
#include <json.h>
#include "../Model/CreateModel.h"

using namespace sql;
using std::cout;
using std::endl;
using std::unique_ptr;

class Database {
private:
    Driver *driver = nullptr;
    Connection *connection = nullptr;
    Statement *statement = nullptr;
    PreparedStatement *preparedStatement = nullptr;
    Json::Value connectionStrings;

    void static PrintTheError(const SQLException& exception) {
        cout << "Error: " << exception.what() << endl;
    }

public:
    Database() {
        driver = get_driver_instance();

        try {
            std::ifstream database_settings_file(ProjectDirectory"/database_settings.json", std::ifstream::binary);
            database_settings_file >> connectionStrings;

            database_settings_file.close();
        }
        catch(const Json::Exception exception) {
            cout << "Error with reading file" << exception.what() << endl;
        }
    }

    ~Database() {
        connection->close();
        delete connection;
    }

    Connection* OpenDatabaseConnection() {
        try {
            connection = driver->connect(this->connectionStrings["servername"].asString(), this->connectionStrings["username"].asString(), this->connectionStrings["password"].asString());
            connection->setSchema(connectionStrings["schema"].asString());
        }
        catch (sql::SQLException e) {
            cout << "Could not connect to server. Error message: " << e.what() << endl;
            system("pause");
            exit(1);
        }
        return nullptr;
    }

    void CreateTableUser() {
        try {
            statement = connection->createStatement();
            statement->execute("CREATE TABLE User ("
                                                        "id INT PRIMARY KEY AUTO_INCREMENT, "
                                                        "Email VARCHAR(255) NOT NULL,"
                                                        "FirstName VARCHAR(255) NOT NULL,"
                                                        "LastName VARCHAR(255) NOT NULL,"
                                                        "Password VARCHAR(255) NOT NULL,"
                                                        "Gender VARCHAR(255) NOT NULL,"
                                                        "Age INT NOT NULL)");

            delete statement;

            cout << "Table created" << endl;
        }
        catch(const SQLException exception) {
            PrintTheError(exception);
        }
    }

    void FillTheTable(const User user) {
        try {
            cout << CheckUser(user) << endl;
            if(CheckUser(user)) {
                cout << "Account exists!" << endl;
                return;
            }

            preparedStatement = connection->prepareStatement("INSERT INTO User (Email, FirstName, LastName, Password, Gender, Age) VALUES(?, ?, ?, ?, ?, ?);");
            preparedStatement->setString(1, user.Email);
            preparedStatement->setString(2, user.FirstName);
            preparedStatement->setString(3, user.LastName);
            preparedStatement->setString(4, user.Password);
            preparedStatement->setString(5, user.Gender);
            preparedStatement->setInt(6, user.Age);

            preparedStatement->executeUpdate();

            delete preparedStatement;

            cout << "Table filled" << endl;
        }
        catch(SQLException exception) {
            PrintTheError(exception);
        }

    }

    void DeleteTable(const std::string tableName) {
        try {
            statement = connection->createStatement();
            statement->execute("DROP TABLE " + tableName);

            delete statement;

            cout << "Table deleted" << endl;
        }
        catch (const SQLException exception) {
            PrintTheError(exception);
        }
    }

    bool CheckUser(const User user) {
        std::string sqlQuery = "SELECT Email FROM User WHERE Email = \'";
        sqlQuery.append(user.Email);

        preparedStatement = connection->prepareStatement(sqlQuery + "\';");
        auto res = preparedStatement->executeQuery();

        bool result = res->next();

        delete preparedStatement;
        delete res;

        return result;
    }

    void AddNewUser(const User user) {
        try {
            preparedStatement = connection->prepareStatement("INSERT INTO User (Email, FirstName, LastName, Password, Gender, Age) VALUES(?, ?, ?, ?, ?, ?);");
            preparedStatement->setString(1, user.Email);
            preparedStatement->setString(2, user.FirstName);
            preparedStatement->setString(3, user.LastName);
            preparedStatement->setString(4, user.Password);
            preparedStatement->setString(5, user.Gender);
            preparedStatement->setInt(6, user.Age);

            preparedStatement->executeUpdate();

            delete preparedStatement;

            cout << "Table filled" << endl;
        }
        catch(SQLException exception) {
            PrintTheError(exception);
        }
    }

    bool CheckLoginUser(const std::string Email, char *const Password) {
        try {
            SHA256 sha;
            sha.update(Password);
            uint8_t *digest = sha.digest();
            strcpy(Password, SHA256::toString(digest).c_str());

            preparedStatement = connection->prepareStatement("SELECT Email, Password FROM User WHERE Email = \'" + Email + "\' AND Password = \'" + Password + "\';");
            auto res = preparedStatement->executeQuery();
            auto result = res->next();

            delete preparedStatement;
            delete res;

            return result;

        } catch(SQLException exception) {
            PrintTheError(exception);
        }
    }

    void RegisterNewUser();
    void LoginUser();
    void WelcomePage();
    void Menu();
};


