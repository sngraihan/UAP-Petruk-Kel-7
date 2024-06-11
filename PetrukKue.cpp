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

#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define PURPLE 5
#define DARKYELLOW 6
#define WHITE 7
#define GREY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define PINK 13
#define YELLOW 14
#define LIGHTWHITE 15

using namespace std;

//visual
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int maxy= 29, maxx=119, midy=maxy/2, midx=maxx/2;

void gotoxy( short x, short y )
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE) ;
    COORD position = { x, y } ;

    SetConsoleCursorPosition( hStdout, position ) ;
}

void textcolor(int colorCode) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}

void setcursor(bool visible, DWORD size)
{
	if (size == 0)
		size = 20;
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}

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
		vector<Cake<T>*> cakes;
		
	public:
		CakeManager() {
			for (Cake<T>* cake : cakes) {
				delete cake;
			}
		}
		
		void addCake(const T &name, const T &desc, double price){
			cakes.push_back(new Cake<T>(name, desc, price));
		}
		void displayCakes() const{
			gotoxy(1, 3);
			for(size_t i = 0; i < cakes.size(); i++){
				cout << i+1 << ". Name: " << cakes[i]->getName() << endl;
				cout << "Description: " << cakes[i]->getDesc() << endl;
				cout << "Price: Rp" << cakes[i]->getPrice() << 'k' <<endl << endl;
			}
		}
		vector<Cake<T>*> getCakes()const {
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
		
		Cake<T> getCake() const {
			return cake;
		}
		
		double getPrice() const {
			return cake.getPrice();
		}
		
		void displayOrder() const {
			cout << "Cake: " << cake.getName() << endl <<
			"Customization: " << custom << endl << 
			"Price: Rp" << cake.getPrice() <<'k' <<endl << endl;
		}
};

template <typename T>
class OrderManager{
	private:
		vector<Order<T>> orders;
		
		int partition(int low, int high) {
			double pivot = orders[high].getPrice();
			int i = (low - 1);
			
			for (int j = low; j <= high - 1; j++) {
				if (orders[j].getPrice() <= pivot) {
					i++;
					swap(orders[i], orders[j]);
				}
			}
			swap(orders[i + 1], orders[high]);
			return (i + 1);
		}
		
		void quickSort(int low, int high) {
			if (low < high) {
				int pi = partition(low, high);
				
				quickSort(low, pi - 1);
				quickSort(pi + 1, high);
			}
		}
		
	public:
		void placeOrder(const Cake<T> &cake, const T custom){
			orders.push_back(Order<T>(cake, custom));
		}
		
		vector<Order<T>> getOrders() const {
			return orders;
		}
		
		void displayOrders() const {
			for (const auto &itr : orders) {
				itr.displayOrder();
			}
		}
		
		void sortOrdersByPrice() {
			quickSort(0, orders.size() - 1);
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

void window(){
	for(int i=1; i<maxx+1; i++){
	gotoxy(i, midy+1);
	cout << "\xcd";
	}
	
	for(int i=1; i<maxx+1; i++){
	gotoxy(i, midy+5);
	cout << "\xcd";
	}
	
	for(int i=midy+1 ;i< maxy;i++){
		gotoxy(1, i);
		cout << "\xba";
	}
	
	for(int i=midy+1 ;i< maxy;i++){
		gotoxy(maxx, i);
		cout << "\xba";
	}
	
	for(int i=1; i<maxx+1; i++){
	gotoxy(i, maxy);
	cout << "\xcd";
	}
}

void window2(){
	for(int i=1; i<maxx+1; i++){
	gotoxy(i, 2);
	cout << "\xcd";
	}
	
//	for(int i=2 ;i< maxy-2;i++){
//		gotoxy(maxx-15, i);
//		cout << "\xba";
//	}
	
	for(int i=2 ;i< maxy-2;i++){
		gotoxy(maxx, i);
		cout << "\xba";
	}
	
	for(int i=1; i<maxx+1; i++){
	gotoxy(i, maxy-3);
	cout << "\xcd";
	}
	
//	for(int i=1; i<maxx+1; i++){
//	gotoxy(i, maxy);
//	cout << "\xcd";
//	}
}

int main(){
	textcolor(PURPLE);
	setcursor(0,0);
	
	system("cls");	
	
	window();
	
	char welcome[] = " __          __ ______  _       _____  ____   __  __  ______       _______  ____                      \n \\ \\        / /|  ____|| |     / ____|/ __ \\ |  \\/  ||  ____|     |__   __|/ __ \\                     \n  \\ \\  /\\  / / | |__   | |    | |    | |  | || \\  / || |__           | |  | |  | |                    \n   \\ \\/  \\/ /  |  __|  | |    | |    | |  | || |\\/| ||  __|          | |  | |  | |                    \n    \\  /\\  /   | |____ | |____| |____| |__| || |  | || |____         | |  | |__| |                    \n     \\/  \\/    |______||______|\\_____|\\____/ |_|  |_||______|        |_|   \\____/                     \n  _    _         _____  ____   _____  _______  ______  _  __  _____  ______ _____  ______  _____   _____ \n | |  | |    /\\    |  \\/  ||  \\/  ||  ____||  __ \\      |  _ \\    /\\    | |/ /|  ____||  __ \\ \\   / /\n | |__| |   /  \\   | \\  / || \\  / || |__   | |__) |     | |_) |  /  \\   | ' / | |__   | |__) |\\ \\_/ / \n |  __  |  / /\\ \\  | |\\/| || |\\/| ||  __|  |  _  /      |  _ <  / /\\ \\  |  <  |  __|  |  _  /  \\   /  \n | |  | | / ____ \\ | |  | || |  | || |____ | | \\ \\      | |_) |/ ____ \\ | . \\ | |____ | | \\ \\   | |   \n |_|  |_|/_/    \\_\\|_|  |_||_|  |_||______||_|  \\_\\     |____//_/    \\_\\|_|\\_\\|______||_|  \\_\\  |_|   \n                                                                                                      \n                                                                                                      \n";
	
	textcolor(PINK);
	gotoxy(1,1);
	cout << welcome <<endl;
	textcolor(WHITE);	
	UserManager<string> um;
	um.loadUsers();
	CakeManager<string> cc;
	OrderManager<string> om;
	Receipt<string> r;
	
	cc.addCake("Risol Mayo", "Risol yang diisi dengan mayo dan potongan telur", 5);
	cc.addCake("Kue Pancong", "Kue pancong yang manis dengan taburan gula", 2);
	cc.addCake("Black Forest", "Kue ini terdiri dari kue spons, mousse dark chocolate, potongan buah ceri, dan krim chantilly. ", 380);
	cc.addCake("Tiramisu", ", harmoni sempurna antara mousse mascarpone, kopi espresso  dan bubuk kakao murni ", 365);
	cc.addCake("Kue Sus", "terdiri dari 10 pcs, berbagai macam rasa coklat, vanila, buah, strawberry", 10);
	cc.addCake("Lapis Legit", "memiliki rasa yang khas, dan mengingatkan pada hari raya.", 200);
	
	int choice;
	string username, password, custom;

	
	while (true) {
		
		gotoxy(midx-20, midy+3);
		cout << "Login first!";
		gotoxy(midx-5, midy+2);
	    cout << "1. Register" << endl;
	    gotoxy(midx-5, midy+3);
	    cout << "2. Login" << endl;
	    gotoxy(midx-5, midy+4);
	    cout << "3. Exit" << endl; 
	    
	    gotoxy(midx-13, midy+6);
	    cout << "select: ";
	    gotoxy(midx-5, midy+6);
	    cin >> choice;
	    textcolor(WHITE);
	    if (choice == 1) {
	    	gotoxy(midx-15, midy+8);
	        cout << "Username: ";
	        gotoxy(midx-5, midy+8);
	        cin >> username;
	        gotoxy(midx-15, midy+9);
	        cout << "Password: ";
	        gotoxy(midx-5, midy+9);
	        cin >> password;
	        um.registerUser(username, password);
	        gotoxy(midx-15, midy+10);
	        cout << "Registered successfully!" << endl << endl;
	    } else if (choice == 2) {
	        while (true) {
	            gotoxy(midx-15, midy+8);
		        cout << "Username: ";
		        gotoxy(midx-5, midy+8);
		        cin >> username;
		        gotoxy(midx-15, midy+9);
		        cout << "Password: ";
		        gotoxy(midx-5, midy+9);
		        cin >> password;
	            if (um.loginUser(username, password)) {
	            	gotoxy(midx-5, midy+10);
	                cout << "Login Successfully!" << endl << endl;
	                break;
	            } else {
	            	gotoxy(midx-5, midy+10);
	                cout << "Wrong username or password!" << endl;
	            }
	        }
	        
	        gotoxy(midx-7, 1);
	        // Katalog kue
	        bool ordering = true;
	        while (ordering) {
	        	system("cls");
	        	window2();
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
	                
	                Cake<string> selectedCake = *cc.getCakes()[choice2 - 1];
	                om.placeOrder(selectedCake, custom);
	            } else {
	                cout << "Invalid choice!" << endl << endl;
	            }
	        }
	        
	       
	        cout << "\nConfirm your order? (y/n): \n";
	        char confirm;
	        cin >> confirm;
	        if (confirm == 'y') {
	            om.sortOrdersByPrice();
	            vector<Order<string>> orders = om.getOrders();
	            for (const auto &order : orders) {
	                r.addOrder(order);
	            }
	            r.displayReceipt();
	        }
	        cout<<endl;
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
