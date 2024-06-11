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


//kue
template <typename T>
class Cake{
    private:
        T name;
        T desc;
        double price;
        
    public:
        Cake(const T &name, const T &desc, double price) : name(name), desc(desc), price(price){
            
        }
        
        T getName()const {
            return name;
        }
        
        T getDesc()const{
            return desc;
        }
        
        double getPrice()const {
            return price;
        }
        
};

template <typename T>
class CakeManager{
    private:
        vector<Cake<T>> cakes;
        
    public:
        void addCake(const T &name, const T &desc, double price){
            cakes.push_back(Cake<T>(name, desc, price));
        }
        void displayCakes() const{
            for(size_t i = 0; i < cakes.size(); i++){
                cout << i+1 << ". Name: " << cakes[i].getName() << endl <<
                "Description: " << cakes[i].getDesc() << endl << 
                "Price: Rp" << cakes[i].getPrice() <<endl << endl;
            }
        }
        vector<Cake<T>> getCakes()const {
            return cakes;
        }        
};


//order
template <typename T>
class Order {
    private:
        Cake<T> cake;
        T custom;
        
    public:
        Order(const Cake<T> &cake, const T &custom) : cake(cake), custom(custom){    
        
        }
        
        void displayOrder()const {
            cout << "Cake: " << cake.getName() << endl <<
            "Customization: " << custom << endl << 
            "Price: " << cake.getPrice() << endl << endl;
        }
};

template <typename T>
class OrderManager{
    private:
        vector<Order<T>> orders;
        
    public:
        void placeOrder(const Cake<T> &cake, const T custom){
            orders.push_back(Order<T>(cake, custom));
        }
        
        vector<Order<T>> getOrders()const {
            return orders;
        }
        
        void displayOrders()const {
            for (const auto &itr : orders) {
                itr.displayOrder();
            }
        }
};


//receipt
template <typename T>
class Receipt{
    private:
        queue<Order<T>> orderq;

    public:
        void addOrder(const Order<T> &order) {
            orderq.push(order);
        }

        void displayReceipt() {
            while (!orderq.empty()) {
                Order<T> order = orderq.front();
                order.displayOrder();
                orderq.pop();
            }
        }
};


int main() {
    

    return 0;
}

