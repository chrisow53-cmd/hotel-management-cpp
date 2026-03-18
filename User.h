#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <string>
using namespace std;

class User
{
private:
    string username;
    string password;
    string name;
    string email;
    string couponCode;

public:
    User(const string& username, const string& password, const string& name, const string& email, const string& couponCode)
        : username(username), password(password), name(name), email(email), couponCode(couponCode) {}

    string getUsername() const
    {
        return username;
    }
    string getPassword() const
    {
        return password;
    }
    string getName() const
    {
        return name;
    }
    string getEmail() const
    {
        return email;
    }
    string getCouponCode() const
    {
        return couponCode;
    }
};


#endif // USER_H_INCLUDED
