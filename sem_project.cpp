#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>

using namespace std;

void main_Menu();
void billing_Menu();
void inventory_Menu();
void billing();
void billing_History();
void add_Items();
void remove_Items();
void modify_Items();
float discounts(int);
void view_Items();
void low_Stock();
void load_Items();
void save_All_Items();
void search_Items();
void save_Billing_History(double total_price);
void about();
void about_Submenu();
void version_About();

struct items
{
    double price;
    int id;
    string name;
    string category;
    int quantity;
};

const int all_items=50;
items item[all_items];
int item_count=0;

int main()
{
    load_Items();
    cout<<"\n=======Welcome to Super Market Manager=======\n"<<endl;
    main_Menu();
    return 0;
}

void main_Menu()
{
    int choice;
    cout<<endl;
	cout<<"Enter 1 to login for Biling."<<endl;
    cout<<"Enter 2 to login as Inventory Manager (Password Required)."<<endl;
    cout<<"Enter 3 to View About."<<endl;
    cout<<"Enter 4 to Exit."<<endl;
    cout<<"Enter Your Choice : ";
    cin>>choice;
    cout<<endl;
    switch(choice)
    {
        case 1:
        {
            billing_Menu();
            break;
        }
        case 2:
        {
            int pass;
            const int pin=1122;
            const int pin2=1111;
            cout<<"Enter Your Password : ";
            cin>>pass;
            cout<<endl;
            if(pass==pin || pass==pin2)
            {
                inventory_Menu();
            }
            else
            {
                cout<<"Wrong Password"<<endl;
                main_Menu();
            }
            break;
        }
        case 3:
        {
            about();
            break;
        }
        case 4:
        {
        	cout<<"Successfully Exited."<<endl;
            break;	
		}
        default:
        {
            cout<<"Wrong Input"<<endl;
            main_Menu();
        }
    }
}

void billing_Menu()
{
    int choice;
    cout<<endl;
    cout<<"========== BILLING MENU =========="<<endl;
    cout<<"Enter 1 to Start Billing."<<endl;
    cout<<"Enter 2 to View Billing History."<<endl;
    cout<<"Enter 3 to Return to Main Menu."<<endl;
    cout<<"Enter Your Choice : ";
    cin>>choice;
    cout<<endl;
    switch(choice)
    {
        case 1:
        {
            billing();
            break;
        }
        case 2:
        {
            billing_History();
            break;
        }
        case 3:
        {
            main_Menu();
            break;
        }
        default:
        {
            cout<<"Wrong Input"<<endl;
            main_Menu();
        }
    }
}

void inventory_Menu()
{
    int choice;
    cout<<endl;
    cout<<"========= INVENTORY MENU ========="<<endl;
    cout<<"Enter 1 to Add Items."<<endl;
    cout<<"Enter 2 to Remove Items."<<endl;
    cout<<"Enter 3 to Modify Items."<<endl;
    cout<<"Enter 4 to View Items."<<endl;
    cout<<"Enter 5 to View Low Stock."<<endl;
    cout<<"Enter 6 to Search Between Items."<<endl;
    cout<<"Enter 7 to Return to Main Menu."<<endl;
    cout<<"Enter Your Choice : ";
    cin>>choice;
    cout<<endl;
    switch(choice)
    {
        case 1:
			{
				add_Items();
				break;
			}
        case 2:
        	{
				remove_Items();
				break;
			}
        case 3:
			{
				modify_Items();
				break;
			}
        case 4:
			{
				view_Items();
				break;
			}
        case 5:
			{
				low_Stock();
				break;
			}
        case 6:
			{
				search_Items();
				break;
			}
		case 7:
			{
				main_Menu();
				break;
			}
        default:
			{
				main_Menu();
				break;
			}
    }
}

void billing()
{
    int stop=0;
    int id;
    int qty;
    double total_price=0;
    cout<<"======= ENTERING BILLING MODE ======="<<endl;
    cout<<"Type -1 to finish billing"<<endl<<endl;
    while(stop!=-1)
    {
        cout<<"Enter Item ID : ";
        cin>>stop;
        cout<<endl;
        if(stop==-1)
        {
            break;
        }
		id=stop;
        bool found=false;
        for(int i=0;i<item_count;i++)
        {
            if(item[i].id==id)
            {
                found=true;
                cout<<left<<setw(20)<<"Name: "<<item[i].name<<endl;
                cout<<left<<setw(20)<<"Category: "<<item[i].category<<endl;
                cout<<left<<setw(20)<<"Price: "<<fixed<<setprecision(2)<<item[i].price<<endl;
                cout<<left<<setw(20)<<"Available Quantity: "<<item[i].quantity<<endl<<endl;
                cout<<"Enter Quantity to Buy: ";
                cin>>qty;
                cout<<endl;
                if(qty<=0)
                {
                    cout<<"Invalid Quantity"<<endl;
                }
                else if(qty>item[i].quantity)
                {
                    cout<<"Not Enough Stock"<<endl;
                }
                else if(qty>=5)
                {
                	float discount=discounts(qty);
                	total_price=(total_price+(item[i].price*qty))*discount;
                	cout<<"Discount of Excess Quantity Applied."<<endl;
				}
                else 
                {
                    total_price=total_price+(item[i].price*qty);
                    item[i].quantity=item[i].quantity-qty;
                    cout<<"Item Added to Bill"<<endl;
                }
                cout<<endl;
                break;
            }
        }
        if(found==false)
        {
            cout<<"Item Not Found"<<endl<<endl;
        }
    }
    fstream fout("items.txt", ios::out);
    for(int i=0;i<item_count;i++)
    {
        fout<<item[i].id<<" "<<item[i].name<<" "<<item[i].category<<" "<<item[i].price<<" "<<item[i].quantity<<endl;
    }
    fout.close();
    fstream bill("billing_history.txt", ios::app);
    bill<<"-----------------------------"<<endl;
    bill<<"New Bill Generated"<<endl;
    bill<<"Total Bill Amount: "<<fixed<<setprecision(2)<<total_price<<endl;
    bill<<"============================="<<endl;
    bill.close();
    cout<<"======= FINAL BILL ======="<<endl;
    cout<<"Total Amount: "<<fixed<<setprecision(2)<<total_price<<endl;
    cout<<endl;
	bool another_bill;
	cout<<"For Another Bill Press 1 ,,,,aand 0 to Exit Billing"<<endl;
	cout<<"Enter Your Choice : ";
	cin>>another_bill;
	cout<<endl;
	if(another_bill==1 || another_bill==0)
	{
		if(another_bill==1)
		{
			billing();
		}
		else
		{
			cout<<"Exiting Billing....."<<endl;
			main_Menu();
		}
	}
}

void load_Items()
{
    fstream fin("items.txt", ios::in);
	if(!fin)
    {
        return;
    }
	while(fin>>item[item_count].id>>item[item_count].name>>item[item_count].category>>item[item_count].price>>item[item_count].quantity)
    {
        item_count++;
        if(item_count>=all_items)
        {
            break;
        }
    }
    fin.close();
}

void save_All_Items()
{
    fstream fout("items.txt", ios::out);
    for(int i=0;i<item_count;i++)
    {
        fout<<item[i].id<<" "<<item[i].name<<" "<<item[i].category<<" "<<item[i].price<<" "<<item[i].quantity<<endl;
    }
    fout.close();
}

void add_Items()
{
    int n;
    cout<<"Enter total number of items to add: ";
    cin>>n;
    cout<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"Enter Item ID: ";
        cin>>item[item_count].id;
        cout<<"Enter Item Name: ";
        cin>>item[item_count].name;
        cout<<"Enter Item Category: ";
        cin>>item[item_count].category;
        cout<<"Enter Item Price: ";
        cin>>item[item_count].price;
        cout<<"Enter Item Quantity: ";
        cin>>item[item_count].quantity;
        cout<<endl;
        item_count++;
    }
    save_All_Items();
    inventory_Menu();
}

void remove_Items()
{
    int id;
    cout<<"Enter Item ID to Remove: ";
    cin>>id;
    cout<<endl;
    for(int i=0;i<item_count;i++)
    {
        if(item[i].id==id)
        {
            for(int j=i;j<item_count-1;j++)
            {
                item[j]=item[j+1];
            }
            item_count--;
            break;
        }
    }
    cout<<"Item Removed Successfully!!!"<<endl;
    save_All_Items();
    inventory_Menu();
}

void modify_Items()
{
    int id;
    cout<<"Enter Item ID to Modify: ";
    cin>>id;
    cout<<endl;
    for(int i=0;i<item_count;i++)
    {
        if(item[i].id==id)
        {
            cout<<"Enter New Price: ";
            cin>>item[i].price;
            cout<<"Enter New Quantity: ";
            cin>>item[i].quantity;
            cout<<endl;
            break;
        }
    }
    cout<<"Item Modified Successfully.!!!"<<endl;
    save_All_Items();
    inventory_Menu();
}

void view_Items()
{
    cout<<setw(5)<<"ID"<<setw(20)<<"Name"<<setw(20)<<"Category"<<setw(10)<<"Price"<<setw(10)<<"Qty"<<endl;
    cout<<setw(65)<<"-------------------------------------------------------------"<<endl;
    for(int i=0;i<item_count;i++)
    {
        cout<<setw(5)<<item[i].id<<setw(20)<<item[i].name<<setw(20)<<item[i].category
            <<setw(10)<<fixed<<setprecision(2)<<item[i].price<<setw(10)<<item[i].quantity<<endl;
    }
    cout<<endl;
    inventory_Menu();
}

void low_Stock()
{
    cout<<endl;
    cout<<setw(20)<<"Low Stock Items"<<endl;
    cout<<setw(30)<<"--------------------------"<<endl;
    for(int i=0;i<item_count;i++)
    {
        if(item[i].quantity<5)
        {
            cout<<setw(15)<<item[i].name<<setw(10)<<item[i].quantity<<endl;
        }
    }
    cout<<endl;
    inventory_Menu();
}

void billing_History()
{
    fstream fin("billing_history.txt", ios::in);
    if(!fin)
    {
        cout<<"No Billing History Found"<<endl;
        billing_Menu();
        return;
    }
    string line;
    cout<<"\n======= BILLING HISTORY =======\n"<<endl;
    while(getline(fin,line))
    {
        cout<<line<<endl;
    }
    fin.close();
    cout<<endl;
    billing_Menu();
}

void save_Billing_History(double total_price)
{
    fstream fout("billing_history.txt", ios::app);
    fout<<"-----------------------------"<<endl;
    fout<<"New Bill Generated"<<endl;
    fout<<"Total Bill Amount: "<<total_price<<endl;
    fout<<"============================="<<endl;
    fout.close();
}

float discounts(int q)
{
	float disc;
	disc=q*0.10;
	return disc;
}

void about()
{
	int choice;
	cout<<endl;
	cout<<"Press 1 for Program's Info."<<endl;
	cout<<"Press 2 for Developer's Info"<<endl;
	cout<<"Press 3 to Go Back."<<endl;
	cout<<endl;
	cout<<"Enter Your Choice : ";
	cin>>choice;
	cout<<endl;
	switch(choice)
	{
		case 1:
			{
				version_About();
				break;
			}
		case 2:
			{
				about_Submenu();
				break;
			}
		case 3:
			{
				main_Menu();
				break;
			}
		default:
			{
				cout<<endl;
				cout<<"Wrong Input \n";
				cout<<endl;
				about();
				break;
			}
	}
}

void about_Submenu()
{
	int choice;
	cout<<"Enter 1 to Show Developers Name."<<endl;
	cout<<"Enter 2 to Show their Roll Numbers."<<endl;
	cout<<"Enter 3 to Show their System Id's."<<endl;
	cout<<"Enter 4 to Contact Us."<<endl;
	cout<<"Enter 5 to Return Back."<<endl;
	cout<<endl;
	cout<<"Enter Your Choice : ";
	cin>>choice;
	cout<<endl;
	switch(choice)
	{
		case 1:
			{
				cout<<"This Program is Developed By : "<<endl;
				cout<<"1.  Abdul Wahab"<<endl;
				cout<<"2.  Adil Hussain"<<endl;
				cout<<"3.  Sajjad Hussain"<<endl;
				cout<<endl;
				about_Submenu();
				break;	
			}
		case 2:
			{
				cout<<"Roll Numbers are :"<<endl;
				cout<<"1. Abdul Wahab : I-CSA-9250017"<<endl;
				cout<<"2. Adil Hussain : I-CSA-9250018"<<endl;
				cout<<"3. Sajjad Hussain : I-CSA-9250005"<<endl;
				cout<<endl;
				about_Submenu();
				break;
			}
		case 3:
			{
				cout<<"System Id's are : "<<endl;
				cout<<"1. Abdul Wahab : NUML-ISB-F25-15632"<<endl;
				cout<<"2. Adil Hussain : NUML-ISB-F25-15635"<<endl;
				cout<<"3. Sajjad Hussain : NUML-ISB-F25-07771"<<endl;
				cout<<endl;
				about_Submenu();
				break;
			}
		case 4:
			{
				cout<<"Contact Us Through Emails :"<<endl;
				cout<<"1. wahabofficial209@gmail.com"<<endl;
				cout<<"2. adilnhussain512@gmail.com"<<endl;
				cout<<"3. sajjadhussainnn65@gmail.com"<<endl;
				cout<<endl;
				about_Submenu();
				break;
			}
		case 5:
			{
				about();
				break;
			}
		default:
			{
				cout<<"Wrong Input\n";
				cout<<endl;
				about_Submenu();
				break;
			}
	}
}

void version_About()
{
	cout<<"Version Number : 1"<<endl;
	cout<<"Functions Contain : 19"<<endl;
	cout<<"Lines Count : ~600"<<endl;
	cout<<endl;
	about();
}

void search_Items()
{
	int searchId;

	cout<<endl;
	cout<<"========= SEARCH ITEM ========="<<endl;
	cout<<"Enter Item ID to Search : ";
	cin>>searchId;
	cout<<endl;

	for(int i=0;i<item_count;i++)
	{
		if(item[i].id==searchId)
		{
			cout<<"Item Found Successfully"<<endl;
			cout<<"---------------------------------------------"<<endl;

			cout<<left<<setw(20)<<"Item ID:"<<item[i].id<<endl;
			cout<<left<<setw(20)<<"Name:"<<item[i].name<<endl;
			cout<<left<<setw(20)<<"Category:"<<item[i].category<<endl;
			cout<<left<<setw(20)<<"Price:"<<fixed<<setprecision(2)<<item[i].price<<endl;
			cout<<left<<setw(20)<<"Quantity:"<<item[i].quantity<<endl;

			cout<<"---------------------------------------------"<<endl;
			cout<<endl;

			inventory_Menu();
			return;
		}
	}

	cout<<"Item Not Found!"<<endl<<endl;
	inventory_Menu();
}


