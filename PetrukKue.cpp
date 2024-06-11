#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <list>
#include <algorithm>
#include <conio.h>
#include <windows.h>

using namespace std;

//User
template <typename T>
class User{
    private:
        T username;
        T password;
    
    public:
        User(const T &username, const T &password) : username(username), password(password){
            
        }
        
        T getUsername() const{
            return username;
        }
        
        T getPassword() const{
            return password;
        }
};

template <typename T>
class UserManager{
    private:
        vector<User<T>> users;
        
    public:
        void loadUsers(){
            ifstream file("users.txt");
            T username, password;
            while(file >> username >> password){
                users.push_back(User<T>(username, password));
            }
            file.close();
        }
        
        void saveUsers(){
            ofstream file("users.txt");
            for(const auto &itr : users){
                file << itr.getUsername() << " " << itr.getPassword() << endl;
            }
            file.close();
        }
        
        void registerUser(const T &username, const T &password){
            users.push_back(User<T>(username, password));
            saveUsers();
        }
        
        bool loginUser(const T &username, const T &password){
            for(const auto &itr : users){
                if(itr.getUsername() == username && itr.getPassword() == password){
                    return true;
                }
            }
            return false;
        }
};



int main() {
	
	
	
    return 0;
}

