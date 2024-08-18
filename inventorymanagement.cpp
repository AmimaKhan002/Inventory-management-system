#include<iostream>
#include<fstream>
using namespace std;
struct InventoryAllocation
{
	char Allocated_to[56][30];
	char ItemName[56][20];
	int Count[56];
	int size=0;

};
struct InventoryItem
{
	char Name[100][20];
	int Item_Count[100];
	char Categgory[100][30];
	int Item_ID[100];
	InventoryAllocation Allocated_TO;
};
void LoadDataFromFile(InventoryItem &item, int& size)
{
	ifstream fin("inventory_items.txt");
	fin >> size;
	int i = 0;
	while (i < size)
	{
		fin >> item.Item_ID[i];
		fin >> item.Item_Count[i];
		fin.getline(item.Name[i],19, ' ');
		fin.getline(item.Name[i],19, ' ');
		fin.getline(item.Categgory[i],19, '\n');
		i++;
	}
	fin >> item.Allocated_TO.size;
	i = 0;
	while (i < item.Allocated_TO.size)
	{
		fin >> item.Allocated_TO.Count[i];
		fin.getline(item.Allocated_TO.Allocated_to[i], 19, ' ');
		fin.getline(item.Allocated_TO.Allocated_to[i], 19, ' ');
		fin.getline(item.Allocated_TO.ItemName[i], 19, '\n');
		i++;
	}
}
void StoreDataInFile(InventoryItem item, int size)
{
	ofstream fout("inventory_items.txt");
	int i = 0;
	fout << size << endl;
	while (i < size)
	{
		fout << item.Item_ID[i] << " ";
		fout << item.Item_Count[i] << " ";
		fout << item.Name[i] << " ";
		fout << item.Categgory[i] << endl;
	}
	fout << item.Allocated_TO.size << endl;
	i = 0;
	while (i < item.Allocated_TO.size)
	{
		fout << item.Allocated_TO.Count[i] << " ";
		fout << item.Allocated_TO.Allocated_to[i] << " ";
		fout << item.Allocated_TO.ItemName[i] << endl;
	}
}
void ListOfInventoryItems(InventoryItem item, int size)
{
	cout << "ID\t\tInventery name\t\tCount\t\tCatogry" << endl;
	for (int i = 0; i < size; i++)
	{
		cout<<item.Item_ID[i] << "\t\t" << item.Name[i] << "\t\t\t" << item.Item_Count[i] << "\t\t" << item.Categgory[i] << endl;
	}
}
void AddInventoryItems(InventoryItem &item, int& size)
{
	int ItemSize = 0;
isize:	cout << "Input number of items you wants to add  :  ";
	cin >> ItemSize;
	if (ItemSize == 0)
	{
		cout << "You Input 0 " << endl;
		cout << "Please Re-";
		goto isize;
	}
	for (int i = 0; i < ItemSize; i++)
	{
		cout << "Input Item name  :  ";
		cin >> item.Name[i + size];
		cout << "Input " << item.Name[i + size] << " count  :  ";
		cin >> item.Item_Count[i + size];
		item.Item_ID[i] = size + i;
		cout << "Input Item " << item.Name[i] << "'s Category  :  ";
		cin >> item.Categgory[i];
	}
	size += ItemSize;
	cout<<endl<<endl << ItemSize << " Items are added Successfully" << endl << endl;
}
bool SearchInventoryItem(char name[],int size,char ItemsName[][20],int &index)
{
	bool exist = false;
	for (int i = 0; i < size; i++)
	{
		if (name[0] == ItemsName[i][0])
		{
			exist = true;
			int j = 1;
			
			for (; name[j] != 0; j++)
			{
				if (name[j] != ItemsName[i][j])
					exist = false;
			}
			if (exist && ItemsName[i][j] == 0)
			{
				index = i;
				break;
			}
		}
	}
	return exist;
}
void EditInventoryItem(InventoryItem &item, int size)
{
	char Itemname[20];
	int index = 0;
	cout << "Input Inventory Item Name You Want To Edit  :  ";
	cin >> Itemname;
	if (SearchInventoryItem(Itemname, size, item.Name, index))
	{
		int choice;
	select:	cout << "1 - Change Item Name" << endl;
		cout << "2 - Dont Change Item Name" << endl;
		cin >> choice;
		if (choice == 1)
		{
			cout << "Input new name of " << Itemname << "   :  ";
			cin >> item.Name[index];
		}
		else if (choice != 2)
		{
			cout << "Select a valid number" << endl;
			goto select;
		}
	select1:cout << "1 - Change Item Count" << endl;
		cout << "2 - Dont Change Item Count" << endl;
		cin >> choice;
		if (choice == 1)
		{
			;
			cout << "Input new Count of " << Itemname << "   :  ";
			cin >> item.Item_Count[index];
		}
		else if (choice != 2)
		{
			cout << "Select a valid number" << endl;
			goto select1;
		}
select2:cout << "1 - Change Item Category" << endl;
		cout << "2 - Dont Change Item Category" << endl;
		cin >> choice;
		if (choice == 1)
		{
			;
			cout << "Input new Category name of " << Itemname << "   :  ";
			cin >> item.Categgory[index];
		}
		else if (choice != 2)
		{
			cout << "Select a valid number" << endl;
			goto select2;
		}
		cout << endl << endl << "Item is Updated Successfully" << endl << endl;
	}
	else
		cout << endl << endl << "Item " << Itemname << " Does not Exist in the System" << endl << endl;
}
void DeleteInventoryItem(InventoryItem& item, int& size)
{
	char Itemname[20];
	int index = 0;
	cout << "Input Inventory Item Name You Want To Delete  :  ";
	cin >> Itemname;
	if (SearchInventoryItem(Itemname, size, item.Name, index))
	{
		
		for (int i = index; i < size - 1; i++)
		{
			item.Item_Count[i] = item.Item_Count[i + 1];
			
			for (int j = 0; item.Name[i][j] != 0; j++)
				item.Name[i][j] = item.Name[i + 1][j];
		
			for (int j = 0; item.Categgory[i][j] != 0; j++)
				item.Categgory[i][j] = item.Categgory[i + 1][j];
		}
		size--;
		cout << endl << endl << Itemname << " is deleted Successfully" << endl << endl;
	}
	else
		cout << endl << endl << "Item " << Itemname << " Does not Exist in the System" << endl << endl;
}
void AssignInventory(InventoryItem& item, int size)
{
	char name[20];
	int index = 0;
	cout << "Input Inventory Item Name  :  ";
	cin >> name;
	if (SearchInventoryItem(name, size, item.Name, index))
	{
		cout << "Input Faculty Member Name  :  ";
		cin >> item.Allocated_TO.Allocated_to[item.Allocated_TO.size];
		cout << "Input item Count  :  ";
count:		cin >> item.Allocated_TO.Count[item.Allocated_TO.size];
		if (item.Allocated_TO.Count[item.Allocated_TO.size] > item.Item_Count[index+1])
		{
			cout << "There are only " << item.Item_Count[index+1] << item.Allocated_TO.ItemName[item.Allocated_TO.size] << " are Available" << endl;
			cout << "Please input a number in range (1 " << item.Item_Count[index+1] << " )" << endl;
			goto count;
		}
		else if (item.Allocated_TO.Count[item.Allocated_TO.size] == 0)
		{
			cout << "You input 0" << endl;
			cout << "Please input a number in range ( 1 " << item.Item_Count[index+1] << " )" << endl;
			goto count;
		}
		item.Item_Count[index+1] -= item.Allocated_TO.Count[item.Allocated_TO.size];
		cout << endl << endl<< item.Allocated_TO.Count[item.Allocated_TO.size]<<" " << item.Allocated_TO.ItemName[item.Allocated_TO.size] << "s are assigned to Mr(s)." << item.Allocated_TO.Allocated_to[item.Allocated_TO.size] << endl << endl;
		item.Allocated_TO.size++;
	}
	else
		cout << endl << endl << "Item " << item.Allocated_TO.ItemName[item.Allocated_TO.size] << " Does not Exist in the System" << endl << endl;
}
void ViewBorrowedList(InventoryItem item)
{
	if (item.Allocated_TO.size > 0)
	{
		cout << endl << endl << "Faculty Member Name\t\t\tItem Name\t\t\tItem Count" << endl;
		for (int i = 0; i < item.Allocated_TO.size; i++)
			cout << item.Allocated_TO.Allocated_to[i] << "\t\t\t\t\t" << item.Allocated_TO.ItemName[i] << "\t\t\t\t" << item.Allocated_TO.Count[i] << endl;
		cout << endl << endl;
	}
	else
		cout << endl << endl << "List is Empty" << endl << endl;
}
void RetriveInventory(InventoryItem& item, int size)
{
	if (item.Allocated_TO.size == 0)
	{
		cout << "No Item is Assign To Anyone Yet" << endl;
		return;
	}
	else
	{
		char name[30];
		cout << "Input Faculty Member Name  :  ";
		cin >> name;
		bool exist = true;
		int index = 0;
		for (int i = 0; i < item.Allocated_TO.size; i++)
		{
			if (name[0] == item.Allocated_TO.Allocated_to[i][0])
			{
				exist = true;
				int j = 1;
				for (; item.Allocated_TO.Allocated_to[i][j] != 0 && exist; j++)
					if (name[j] != item.Allocated_TO.Allocated_to[i][j])
						exist = false;
				if (exist && name[j] == 0)
				{
					SearchInventoryItem(item.Allocated_TO.ItemName[i], size, item.Name, index);
					item.Item_Count[index] += item.Allocated_TO.Count[i];

					for (; i < item.Allocated_TO.size - 1; i++)
					{
						item.Allocated_TO.Count[i] = item.Allocated_TO.Count[i + 1];

						for (j = 0; item.Allocated_TO.Allocated_to[i][j] != 0; j++)
							item.Allocated_TO.Allocated_to[i][j] = item.Allocated_TO.Allocated_to[i + 1][j];
				

						for (j = 0; item.Allocated_TO.ItemName[i][j] != 0; j++)
							item.Allocated_TO.ItemName[i][j] = item.Allocated_TO.ItemName[i + 1][j];
						
					}
					item.Allocated_TO.size--;
					cout  <<endl<<endl<< "Items are reterived Successfully"<<endl << endl;
					return;
				}
			}
		}
		cout << endl << endl <<"There is no Faculty Member with name "<<name<<" who take any Inventory Item" << endl << endl;
	}
}
						int main(){
							int choice;
	InventoryItem item;
	int size = 0;
	fstream fw("inventory_items.txt",ios::in|ios::out);
    	LoadDataFromFile(item, size);
	do{

		cout << "Select Option Number For Respective Function" << endl;
		cout << "1 - Add Inventory Items" << endl;
		cout << "2 - View All Inventory Items" << endl;
		cout << "3 - Search Inventory Item" << endl;
		cout << "4 - Edit Inventory Item" << endl;
		cout << "5 - Delete Inventory item" << endl;
		cout << "6 - Assign Inventory Item" << endl;
		cout << "7 - Retrieve Inventory Item" << endl;
		cout << "8 - Viem the List Of Faculty Members Who Borrowed a Specific Item" << endl;
		cin >> choice;

		if (choice == 1)
		{
			AddInventoryItems(item, size);
		}
		else if (choice == 2)	
		{
			ListOfInventoryItems(item, size);

		}
		else if (choice == 3)
		{
			char ItemName[20];
			int index = 0;
			cout << "Input Item Name  :  ";
			cin >> ItemName;
			if (SearchInventoryItem(ItemName,size,item.Name,index))
				cout << "Item " << ItemName << " Exist at index "<<index<<" in the System" << endl;
			else
				cout << "Item " << ItemName << " Does not Exist in the System" << endl;
		}
		else if (choice == 4)	
		{
			EditInventoryItem(item, size);
		}
		else if (choice == 5)	
		{
			DeleteInventoryItem(item, size);
			
		}
		else if (choice == 6)
		{
			AssignInventory(item,size);
			
		}
		else if (choice == 7)
		{
			RetriveInventory(item,size);
			
		}
		else if (choice == 8)	
		{
		
			ViewBorrowedList(item);
		}
		
    }while (choice!=8);
    StoreDataInFile(item, size);
	cout << endl;
	return 0;
}