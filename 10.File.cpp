#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include <iomanip>
#define MAX 10

using namespace std;

struct hash1
{
	int id, chain;
	char name[20];
}rec[MAX],tmp;

class hash1table
{
	public:
	void initialize();
	int hash1ing( int );
	void woreplace( struct hash1 );
	void wreplace( struct hash1 );
	void place_at_next_slot(int, int, struct hash1);
	void display();
	void search(int);
	void read_file();
	void send_to_file();
};

void hash1table::initialize() {
	int i;
	for(i = 0; i < MAX; i++ ){
		rec[i].id = -1;
		strcpy( rec[i].name, "-" );
		rec[i].chain = -1;
	}
}






int hash1table::hash1ing( int no ) {
	int key;
	key = no % MAX;
	return( key );
}

void hash1table::woreplace( struct hash1 h ) {
	int i,k,z,org_index;
	k = hash1ing( h.id );
	org_index = k;
	if( rec[k].id == -1 ) {
		rec[k].id = h.id;
		strcpy( rec[k].name, h.name );
	}
	else
		place_at_next_slot(k,org_index,h);
}

void hash1table::place_at_next_slot( int k, int org_index, struct hash1 h )
{
	int i, z;
	int flag=0;
	for(i = 1; i < MAX; i++ ){
		z = (k+i)%MAX;
		if( rec[z].id == -1 )
		{
			rec[z].id = h.id;
			strcpy( rec[z].name, h.name );
			if(hash1ing(rec[org_index].id) == k)
				rec[org_index].chain = z;
			flag = 1;
			break;
		}
		if( hash1ing( rec[z].id ) == k )
			   org_index = z;
	}
	if(flag==1)
	{
		rec[org_index].chain=z;
	}
}

void hash1table::wreplace( struct hash1 h )
{
	int k,p,org_index,change_pos;
	k = hash1ing( h.id );
	org_index = k;





	if( rec[k].id == -1 )
	{
		rec[k].id = h.id;
		strcpy( rec[k].name, h.name );
	}
	else if( hash1ing(rec[k].id) == hash1ing(h.id) )
		place_at_next_slot(k,org_index,h);
	else
	{
		tmp.id = rec[k].id;
		strcpy( tmp.name, rec[k].name );
		tmp.chain = rec[k].chain;
		rec[k].id = h.id;
		strcpy(rec[k].name, h.name);
		rec[k].chain = -1;
		place_at_next_slot(k,hash1ing(tmp.id),tmp);
	}
}

void hash1table::send_to_file()
{
	ofstream o;
	o.open("emp.txt",ios::binary |ios::out);
	o.seekp(0);
	for( int i = 0; i < MAX; i++ )
	{
		o.write((char *)&rec[i],sizeof(rec[i]) );
	}
	o.close();
	read_file();
}

void hash1table::read_file()
{	ifstream in_file;
	hash1 result[MAX];int i;
	in_file.open("emp.txt",ios::binary |ios::in);
	in_file.seekg(0);
	cout << endl << std::setw(10) << "Position" << std::setw(10) << "ID"  << std::setw(15) << "Name" << std::setw(10) << "Chain";
	for( i = 0; i < MAX; i++ )
	{
		in_file.read((char *)&result[i],sizeof(result[i]) );
		cout << endl << std::setw(10) << i << std::setw(10) << result[i].id  << std::setw(15) << result[i].name<< std::setw(10) << result[i].chain;
	}
	in_file.close();
}





void hash1table:: search(int n)
{
	int index,file_pos,record_present=0;
	fstream inFile;
	inFile.open("emp.txt", ios::binary|ios::in);
	index = hash1ing(n);
	file_pos = index * sizeof(tmp);
	inFile.seekp(file_pos,ios::beg);
	while(inFile.read((char*)&tmp, sizeof(tmp)))
	{
		if(tmp.id == n)
		{
			cout << endl << tmp.id << "\t" << tmp.name;
			record_present=1;
			break;
		}
		else if( hash1ing(tmp.id) == hash1ing(n) && tmp.chain != -1)
		{
			file_pos = tmp.chain * sizeof(tmp);
			inFile.seekp(file_pos,ios::beg);
		}
		else if( hash1ing(tmp.id) == hash1ing(n))
		{
			file_pos = 0;
			inFile.seekp(file_pos,ios::beg);
		}
	}
	inFile.close();
	if(record_present==0)
		cout <<"\n Record not found";
}

int main(){
	hash1table h;
	int ch,ch1,key;
	char ans;
	struct hash1 temph;
		do	{
		cout<<"\n Collision Handling ";
		cout<<"\n 1. Without Replacement \n 2. With Replacement ";
		cout<<"\n 3. Search Record \n 4. Exit \n Enter your choice : ";
		cin>>ch;
		switch(ch){
			case 1:
				h.initialize();
				do {
					cout<<"\n Enter ID : ";





					cin>>temph.id;
					cout<<"\n Enter Name : ";
					cin>>temph.name;
					h.woreplace(temph);
					cout<<"\n Do you want to add more elements(0/1)? ";
					cin>>ch1;
				}while( ch1 != 0 );
				h.send_to_file();
				break;

			case 2:
				h.initialize();
				do{
					cout<<"\n Enter ID : ";
					cin>>temph.id;
					cout<<"\n Enter Name : ";
					cin>>temph.name;
					h.wreplace(temph);
					cout<<"\n Do you want to add more elements(0/1)? ";
					cin>>ch1;
				}while( ch1 != 0 );
				h.send_to_file();
				break;
			case 3:
                               	cout << "\n Enter the id for searching: ";
				cin >> key;
                               	h.search(key);
				break;
			case 4:  exit(0);
		}
	}while( ch != 4 );
	return 0;
}
