#include<iostream>
#include<fstream>
#include<string>
using namespace std;
struct Contact {
    string name,no,email;
};
Contact contacts[1000];
int index=0;
void add_contact(string name, string no, string email);
void view_all_contacts();
void search_contact(string name);
void delete_contact(string name);
void edit_contact(string name);
void load_contacts();
void save_contacts();
bool valid_email(string email);
bool duplicate(string name,string no,string email);
int main() {
    load_contacts();
    int option;
    char again;
    do {
        cout<<"=======================================";
        cout<<"\nWELCOME TO CONTACT MANAGEMENT SYSTEM"<<endl;
        cout<<"======================================="<<endl;
        cout<<endl;
        cout<<"1: Add Contact"<<endl;
        cout<<"2: View All Contacts"<<endl;
        cout<<"3: Search Contact"<<endl;
        cout<<"4: Delete Contact"<<endl;
        cout<<"5: Edit Contact"<<endl;
        cout<<"6: Exit"<<endl;
        cout<<"Choose an option:";
        cin>>option;
        cin.ignore();
        switch(option){
            case 1: {
                string name,no,email;
                cout<<"Enter Name:";
                getline(cin,name);
                if(duplicate(name,no,email)){
        		cout<<"Error: A contact with the same name already exists."<<endl;
        		break;
    			}
                cout<<"Enter Number:";
                getline(cin,no);
                if(duplicate(name,no,email)){
        		cout<<"Error: A contact with the same number already exists."<<endl;
        		break;
    			}
                do {
                    cout<<"Enter Email:";
                    getline(cin,email);
                    if(!valid_email(email)) {
                        cout<<"Invalid email. Please enter a valid email.\n";
                    }
                } while(!valid_email(email));
                if(duplicate(name,no,email)){
        		cout<<"Error: A contact with the same email already exists."<<endl;
        		break;
    			}
                add_contact(name,no,email);
                break;
            }
            case 2:
                view_all_contacts();
                break;
            case 3: {
                string searchName;
                cout<<"Enter Name to Search:";
                getline(cin,searchName);
                search_contact(searchName);
                break;
            }
            case 4: {
                string deleteName;
                cout<<"Enter Name to Delete:";
                getline(cin,deleteName);
                delete_contact(deleteName);
                break;
            }
            case 5: {
                string editName;
                cout<<"Enter Name to Edit:";
                getline(cin,editName);
                edit_contact(editName);
                break;
            }
            case 6:
                cout<<"Thank you for using the system."<<endl;
                save_contacts();
                return 0;
            default:
                cout<<"Invalid option. Please try again."<<endl;
        }
        cout<<"\nDo you want to continue? (Y/N):";
        cin>>again;
        cin.ignore();
    } while (again=='Y'||again=='y');
    save_contacts();
    return 0;
}
void add_contact(string name,string no,string email){
    contacts[index].name=name;
    contacts[index].no=no;
    contacts[index].email=email;
    index++;
    ofstream file("record.txt", ios::app);
    if (file.is_open()) {
        file<<name<<endl;
        file<<no<<endl;
        file<<email<<endl;
        file<<"------------------"<<endl;
        file.close();
    }else{
        cout<<"Error creating or opening the file."<<endl;
    }
    cout<<"Contact added successfully!"<<endl;
}
void view_all_contacts(){
    if(index==0){
        cout<<"No contacts available."<<endl;
        return;
    }
    cout<<"\nContact List:"<<endl;
    cout<<"---------------------"<<endl;
    for(int i=0;i<index;i++){
        cout<<"Name: "<<contacts[i].name<<endl;
        cout<<"Number: "<<contacts[i].no<<endl;
        cout<<"Email: "<<contacts[i].email<<endl;
        cout<<"---------------------"<<endl;
    }
}
void search_contact(string name){
    for (int i=0;i<index;i++){
        if(contacts[i].name==name){
            cout<<"\nContact Found:"<<endl;
            cout<<"Name: "<<contacts[i].name<<endl;
            cout<<"Number: "<<contacts[i].no<<endl;
            cout<<"Email: "<<contacts[i].email<<endl;
            return;
        }
    }
    cout<<"\nContact not found."<<endl;
}
void delete_contact(string name){
    for (int i=0;i<index;i++){
        if (contacts[i].name==name){
            for (int j=i;j<index - 1;j++){
                contacts[j]=contacts[j+1];
            }
            index--;
            cout<<"Contact deleted successfully!"<<endl;
            save_contacts();
            return;
        }
    }
    cout<<"Contact not found."<<endl;
}
void edit_contact(string name){
    for (int i=0;i<index;i++){
        if (contacts[i].name==name){
            string newName, newNumber, newEmail;
            cout<<"Enter New Name:";
            getline(cin, newName);
            cout<<"Enter New Number:";
            getline(cin, newNumber);
            do {
                cout<<"Enter New Email:";
                getline(cin, newEmail);
                if(!valid_email(newEmail)){
                    cout<<"Invalid email. Please enter a valid email .\n";
                }
            } while (!valid_email(newEmail));
            contacts[i].name = newName;
            contacts[i].no = newNumber;
            contacts[i].email = newEmail;
            cout<<"Contact updated successfully!"<<endl;
            save_contacts();
            return;
        }
    }
    cout<<"Contact not found."<<endl;
}
void load_contacts(){
    ifstream file("record.txt");
    if(!file.is_open()) return;
    string name,no,email;
    while(getline(file,name)&&getline(file,no)&&getline(file, email)){
        contacts[index].name=name;
        contacts[index].no=no;
        contacts[index].email=email;
        index++;
        getline(file, email);
    }
    file.close();
}
void save_contacts(){
    ofstream file("record.txt",ios::trunc);
    if (!file.is_open()){
        cout<<"Error saving contacts."<<endl;
        return;
    }
    for (int i=0;i<index;i++){
        file<<contacts[i].name<<endl;
        file<<contacts[i].no<<endl;
        file<<contacts[i].email<<endl;
        file<<"------------------"<<endl;
    }
    file.close();
}
bool valid_email(string email){
    int at_count=0;
    for(int i=0;i<email.length();i++){
        if(email[i]=='@') {
            at_count++;
        }
    }
    if(at_count!=1){
        return false;
    }
    return true;
}
bool duplicate(string name,string no,string email){
    for (int i=0;i<index;i++){
        if(contacts[i].name==name||contacts[i].no==no||contacts[i].email==email){
            return true;
        }
    }
    return false;
}
