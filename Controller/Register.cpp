void Database::RegisterNewUser()  {
    cout << "Register new User: " << endl;
    auto user = CreateUser();
    if(CheckUser(user)) {
        cout << "Account exists! Login" << endl;
    }
    else {
        AddNewUser(user);
    }
}