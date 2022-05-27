void Database::LoginUser() {
cout << "Login User: " << endl;

cout << "Enter email: " << endl;
std::string Email;
cin >> Email;

cout << "Enter password: " << endl;
std::string Password;
cin >> Password;

if(CheckLoginUser(Email, const_cast<char *>(Password.c_str()))) {
    Menu();
}
else {
    cout << "Invalid password or email!" << endl;
    LoginUser();
}
}
