void Database::WelcomePage() {

    while (true) {
        cout << "Choose options: \n"
             << "1 - Register\n"
             << "2 - Login\n"
             << "3 - Exit\n";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                RegisterNewUser();
                break;
            case 2:
                LoginUser();
                break;
            case 3:
                return;
        }
    }
}

void Database::Menu() {

    while (true) {
        cout << "Choose options: \n"
             << "1 - Create table\n"
             << "2 - Fill the table\n"
             << "3 - Delete the table\n"
             << "4 - Exit\n";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                CreateTableUser();

                break;
            case 2:
                FillTheTable(CreateUser());

                break;
            case 3:
                char tableName[255];
                cout << "Enter the table name: \n";
                cin >> tableName;
                DeleteTable(tableName);

                break;
            case 4:
                return;
        }
    }
}