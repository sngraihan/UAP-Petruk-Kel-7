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


int main(){
    UserManager<string> um;
    um.loadUsers();
    CakeManager<string> cc;
    OrderManager<string> om;
    Receipt<string> r;
    
	cc.addCake("Risol Mayo", "Risol yang diisi dengan mayo dan potongan telur", 5000);
	cc.addCake("Kue Pancong", "Kue pancong yang manis dengan taburan gula", 2000);
	cc.addCake("Black Forest", "Kue ini terdiri dari kue spons, mousse dark chocolate, potongan buah ceri, dan krim chantilly. ", 380.000);
	cc.addCake("Tiramisu", ", harmoni sempurna antara mousse mascarpone, kopi espresso  dan bubuk kakao murni ", 365.000);
	cc.addCake("Kue Sus", "terdiri dari 10 pcs, berbagai macam rasa coklat, vanila, buah, strawberry", 10.000);
	cc.addCake("Lapis Legit", "memiliki rasa yang khas, dan mengingatkan pada hari raya.", 200.000);
	
    int choice;
    string username, password, custom;
    
    while (true) {
    	//login
        cout << "1. Register\n2. Login\n3. Exit\n";
        cin >> choice;
        
        if (choice == 1) {
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;
            um.registerUser(username, password);
            cout << "Registered successfully!" << endl << endl;
        } else if (choice == 2) {
            while (true) {
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;
                if (um.loginUser(username, password)) {
                    cout << "Login Successfully!" << endl << endl;
                    break;
                } else {
                    cout << "Wrong username or password!" << endl;
                }
            }
            
            // Katalog kue
            bool ordering = true;
            while (ordering) {
                cout << "Cake Catalog" << endl;
                cc.displayCakes();
                
                // Order kue
                int choice2;
                cout << "Select a cake (0 to finish): " << endl;
                cin >> choice2;
                
                if (choice2 == 0) {
                    break;
                }
                
                if (choice2 > 0 && choice2 <= cc.getCakes().size()) {
                    cout << "Customization: ";
                    cin.ignore();
                    getline(cin, custom);
                    cout<<endl;
                    
                    Cake<string> selectedCake = cc.getCakes()[choice2 - 1];
                    om.placeOrder(selectedCake, custom);
                } else {
                    cout << "Invalid choice!" << endl << endl;
                }
            }
                        // Konfirmasi pesanan
            cout << "Confirm your order? (y/n): ";
            char confirm;
            cin >> confirm;
            if (confirm == 'y') {
                vector<Order<string>> orders = om.getOrders();
                for (const auto &order : orders) {
                    r.addOrder(order);
                }
                r.displayReceipt();
            }
            cout<<endl;
            // Pesan kembali atau keluar
            cout << "Do you want to order again? (y/n): ";
            char orderAgain;
            cin >> orderAgain;
            if (orderAgain != 'y') {
                break;
            }
        } else if (choice == 3) {
            break;
        } else {
            cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}


