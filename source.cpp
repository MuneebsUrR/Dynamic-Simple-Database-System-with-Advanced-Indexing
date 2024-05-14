#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;


struct node {
	int ID;
	int year;
	string cause;
	string state;
	int deaths;
	float adr;
	node* left;
	node* right;
	node* next;
	int height;

	node() {
		ID = 0;
		year = 0; cause = state = '\0'; adr = 0.0;
		next = left = right = NULL;
		height = 0;
	}
	node(int val) {
		ID = val;
		year = 0; cause = state = '\0'; adr = 0.0;
		next = left = right = NULL;
		height = 0;
	}
	void setfunction(int id, string cause, string state, int death, float adr) {
		this->ID = id;
		this->cause = cause;
		this->state = state;
		this->deaths = death;
		this->adr = adr;
	}
	node(int id, int year, string cause, string state, int death, float adr) {
		this->ID = id;
		this->year = year;
		this->cause = cause;
		this->state = state;
		this->deaths = death;
		this->adr = adr;
		next = left = right = NULL;
		height = 0;
	}
	~node() {

	}
};



class AVL {
	void inorder(node* root);
	void preorder(node* root);
public:
	node* root;
	AVL() {
		root = NULL;
	}
	void printPreorder();
	int getHeight(node* curr);
	int getBalance(node* curr);
	bool find(node*& cur, int key);
	void AVLinsertion(node*& cur, int val, int year, string cause, string state, int deaths, float adr, char);
	node* minValueNode(node* node);
	node* deleteID(node* root, int ID);
	node* deleteyear(node* root, int year);
	node* deletestate(node* root, string state);
	node* deletedeaths(node* root, int deaths);
	node* deletecause(node* root, string cause);
	node* deleteadr(node* root, float adr);
	node* rightrotate(node* cur);
	node* leftrotate(node* cur);
	int max(int a, int b);
	node* RLrotation(node* cur);
	node* LRrotaion(node* cur);
	void PrintInOrder();
	~AVL() {
		delete root;
	}
};

void filedeleting(node* root, int id = 0, int y = 0, string c = "", string s = "", int d = 0, float a = 0.0) {


	int ID;
	int year;
	string cause113;
	string dimmycause113;
	string dimmy, dimmy2;
	string cause;
	string state;
	int deaths;
	float adr;
	ifstream fin;
	string fileName[2]{ "NCHS_-_Leading_Causes_of_Death__United_States_1.csv" ,"NCHS_-_Leading_Causes_of_Death__United_States_8.csv" };

	bool close = false;
	string line = "";
	ofstream fout;
	for (int i = 0; i < 2; i++) {
		fin.open(fileName[i]);
		fout.open("dt.csv");

		line = "";

		while (getline(fin, line)) {
			string tempstring;
			stringstream inputstring(line);

			//getting ID
			getline(inputstring, tempstring, ',');
			ID = atoi(tempstring.c_str());

			//getting year
			tempstring = "";
			getline(inputstring, tempstring, ',');
			year = atoi(tempstring.c_str());

			//getting cause113,cause,state
			getline(inputstring, cause113, ',');
			for (int i = 0; i < cause113.size(); i++) {
				if (cause113[i] == '-') {
					getline(inputstring, dimmycause113, ',');
				}
			}
			getline(inputstring, cause, ',');
			getline(inputstring, state, ',');

			//getting death
			tempstring = "";
			getline(inputstring, tempstring, ',');
			deaths = atoi(tempstring.c_str());

			//getting adr
			tempstring = "";
			getline(inputstring, tempstring);
			adr = atof(tempstring.c_str());


			if (id != ID && y != year && c != cause && s != state && d != deaths && a != adr) {
				fout << ID << "," << year << "," << cause113 << "," << cause << "," << state << "," << deaths << "," << adr << endl;
			}
			else
				close = true;

			line = "";

		}
		fout.close();
		fin.close();

		remove(fileName[i].c_str());
		if (rename("dt.csv", fileName[i].c_str()) != 0) {
				cout << "Data is edited in file successfully" << endl;
		}

		if (close == true)
			return;
	}

}

node* AVL::LRrotaion(node* cur) {
	cur->right = rightrotate(cur->right);
	return leftrotate(cur);
}

node* AVL::leftrotate(node* cur) {
	node* temp;
	temp = cur->right;
	cur->right = temp->left;
	temp->left = cur;
	cur->height = max(getHeight(cur->left), getHeight(cur->right)) + 1;
	temp->height = max(getHeight(temp->right), cur->height) + 1;
		temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
	return temp;
}

node* AVL::RLrotation(node* cur) {
	cur->left = leftrotate(cur->left);

	return rightrotate(cur);
}


int AVL::max(int a, int b)
{
	return (a > b) ? a : b;
}
node* AVL::rightrotate(node* cur) {
	node* temp;
	temp = cur->left;
	cur->left = temp->right;
	temp->right = cur;
	cur->height = max(getHeight(cur->left), getHeight(cur->right)) + 1;
	temp->height = max(getHeight(temp->left), cur->height) + 1;
	return temp;
}

void AVL::AVLinsertion(node*& cur, int val, int year, string cause, string state, int deaths, float adr, char choice) {

	if (choice == '1') {

		if (cur == NULL) {
			cur = new node(val, year, cause, state, deaths, adr);

			return;
		}

		if (val < cur->ID) {
			AVLinsertion(cur->left, val, year, cause, state, deaths, adr, choice);
			if (getHeight(cur->left) - getHeight(cur->right) >= 2)
				if (val < cur->left->ID) {
					cur = rightrotate(cur);
				}
				else
					cur = RLrotation(cur);
		}
		if (val > cur->ID) {
			AVLinsertion(cur->right, val, year, cause, state, deaths, adr, choice);
			if (getHeight(cur->right) - getHeight(cur->left) >= 2) {
				if (val > cur->right->ID)
					cur = leftrotate(cur);
				else
					cur = LRrotaion(cur);
			}
		}

		if (val == cur->ID) {
			node* temp = new node(val, year, cause, state, deaths, adr);
			node* temp2 = cur;

			while (temp2->next != NULL) {
				temp2 = temp2->next;
			}
			temp2->next = temp;
		}

		cur->height = max(getHeight(cur->left), getHeight(cur->right)) + 1;
	}
	else if (choice == '2') {
		if (cur == NULL) {
			cur = new node(val, year, cause, state, deaths, adr);
			return;
		}

		if (year < cur->year) {
			AVLinsertion(cur->left, val, year, cause, state, deaths, adr, choice);
			if (getHeight(cur->left) - getHeight(cur->right) >= 2)
				if (year < cur->left->year) {
					cur = rightrotate(cur);
				}
				else
					cur = RLrotation(cur);
		}
		if (year > cur->year) {
			AVLinsertion(cur->right, val, year, cause, state, deaths, adr, choice);
			if (getHeight(cur->right) - getHeight(cur->left) >= 2) {
				if (year > cur->right->year)
					cur = leftrotate(cur);
				else
					cur = LRrotaion(cur);
			}
		}

		if (year == cur->year) {
			node* temp = new node(val, year, cause, state, deaths, adr);
			node* temp2 = cur;

			while (temp2->next != NULL) {
				temp2 = temp2->next;
			}
			temp2->next = temp;
		}

		cur->height = max(getHeight(cur->left), getHeight(cur->right)) + 1;
	}

	else if (choice == '3') {
		if (cur == NULL) {
			cur = new node(val, year, cause, state, deaths, adr);
			return;
		}

		if (state < cur->state) {
			AVLinsertion(cur->left, val, year, cause, state, deaths, adr, choice);
			if (getHeight(cur->left) - getHeight(cur->right) >= 2)
				if (state < cur->left->state) {
					cur = rightrotate(cur);
				}
				else
					cur = RLrotation(cur);
		}
		if (state > cur->state) {
			AVLinsertion(cur->right, val, year, cause, state, deaths, adr, choice);
			if (getHeight(cur->right) - getHeight(cur->left) >= 2) {
				if (state > cur->right->state)
					cur = leftrotate(cur);
				else
					cur = LRrotaion(cur);
			}
		}

		if (state == cur->state) {
			node* temp = new node(val, year, cause, state, deaths, adr);
			node* temp2 = cur;

			while (temp2->next != NULL) {
				temp2 = temp2->next;
			}
			temp2->next = temp;
		}

		cur->height = max(getHeight(cur->left), getHeight(cur->right)) + 1;
	}

	else if (choice == '4') {
		if (cur == NULL) {
			cur = new node(val, year, cause, state, deaths, adr);
			return;
		}

		if (deaths < cur->deaths) {
			AVLinsertion(cur->left, val, year, cause, state, deaths, adr, choice);
			if (getHeight(cur->left) - getHeight(cur->right) >= 2)
				if (deaths < cur->left->deaths) {
					cur = rightrotate(cur);
				}
				else
					cur = RLrotation(cur);
		}
		if (deaths > cur->deaths) {
			AVLinsertion(cur->right, val, year, cause, state, deaths, adr, choice);
			if (getHeight(cur->right) - getHeight(cur->left) >= 2) {
				if (deaths > cur->right->deaths)
					cur = leftrotate(cur);
				else
					cur = LRrotaion(cur);
			}
		}

		if (deaths == cur->deaths) {
			node* temp = new node(val, year, cause, state, deaths, adr);
			node* temp2 = cur;

			while (temp2->next != NULL) {
				temp2 = temp2->next;
			}
			temp2->next = temp;
		}

		cur->height = max(getHeight(cur->left), getHeight(cur->right)) + 1;
	}

	else if (choice == '5') {
		if (cur == NULL) {
			cur = new node(val, year, cause, state, deaths, adr);
			return;
		}

		if (adr < cur->adr) {
			AVLinsertion(cur->left, val, year, cause, state, deaths, adr, choice);
			if (getHeight(cur->left) - getHeight(cur->right) >= 2)
				if (adr < cur->left->adr) {
					cur = rightrotate(cur);
				}
				else
					cur = RLrotation(cur);
		}
		if (adr > cur->adr) {
			AVLinsertion(cur->right, val, year, cause, state, deaths, adr, choice);
			if (getHeight(cur->right) - getHeight(cur->left) >= 2) {
				if (adr > cur->right->adr)
					cur = leftrotate(cur);
				else
					cur = LRrotaion(cur);
			}
		}

		if (adr == cur->adr) {
			node* temp = new node(val, year, cause, state, deaths, adr);
			node* temp2 = cur;

			while (temp2->next != NULL) {
				temp2 = temp2->next;
			}
			temp2->next = temp;
		}

		cur->height = max(getHeight(cur->left), getHeight(cur->right)) + 1;
	}

	else if (choice == '6') {
		if (cur == NULL) {
			cur = new node(val, year, cause, state, deaths, adr);
			return;
		}

		if (cause < cur->cause) {
			AVLinsertion(cur->left, val, year, cause, state, deaths, adr, choice);
			if (getHeight(cur->left) - getHeight(cur->right) >= 2)
				if (cause < cur->left->cause) {
					cur = rightrotate(cur);
				}
				else
					cur = RLrotation(cur);
		}
		if (cause > cur->cause) {
			AVLinsertion(cur->right, val, year, cause, state, deaths, adr, choice);
			if (getHeight(cur->right) - getHeight(cur->left) >= 2) {
				if (cause > cur->right->cause)
					cur = leftrotate(cur);
				else
					cur = LRrotaion(cur);
			}
		}

		if (cause == cur->cause) {
			node* temp = new node(val, year, cause, state, deaths, adr);
			node* temp2 = cur;

			while (temp2->next != NULL) {
				temp2 = temp2->next;
			}
			temp2->next = temp;
		}

		cur->height = max(getHeight(cur->left), getHeight(cur->right)) + 1;
	}


}


int AVL::getHeight(node* curr) {
	if (curr == NULL)
		return -1;

	return curr->height;
}
int AVL::getBalance(node* curr) {
	if (curr == NULL)
		return 0;
	return getHeight(curr->left) - getHeight(curr->right);
}


void AVL::inorder(node* root) {
	if (root == NULL)
		return;

	inorder(root->left);
	cout << root->ID << " ";
	inorder(root->right);
}
void AVL::preorder(node* root) {
	if (root == NULL)
		return;

	cout << root->ID << "," << root->state << "," << root->deaths << "," << root->adr << endl;
	preorder(root->left);
	preorder(root->right);
}
void AVL::printPreorder() {
	preorder(root);
}
void AVL::PrintInOrder() {
	inorder(root);
}


node* AVL::minValueNode(node* nod)
{
	node* current = nod;

	while (current->left != NULL)
		current = current->left;

	return current;
}

node* AVL::deleteadr(node* root, float adr) {
	if (root == NULL) {
		cout << "Value not found" << endl;
		return root;
	}

	if (adr < root->adr)
		root->left = deleteadr(root->left, adr);

	else if (adr > root->adr)
		root->right = deleteadr(root->right, adr);

	else
	{

		if ((root->left == NULL) ||
			(root->right == NULL))
		{
			node* temp = root->left ?
				root->left :
				root->right;

			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;
			free(temp);
		}
		else
		{
			node* temp = minValueNode(root->right);

			root->adr = temp->adr;
			root->right = deleteadr(root->right,
				temp->adr);
		}
	}

	if (root == NULL)
		return root;

	root->height = 1 + max(getHeight(root->left),
		getHeight(root->right));

	int balance = getBalance(root);

	if (balance > 1 &&
		getBalance(root->left) >= 0)
		return rightrotate(root);

	if (balance > 1 &&
		getBalance(root->left) < 0)
	{
		root->left = leftrotate(root->left);
		return rightrotate(root);
	}

	if (balance < -1 &&
		getBalance(root->right) <= 0)
		return leftrotate(root);

	if (balance < -1 &&
		getBalance(root->right) > 0)
	{
		root->right = rightrotate(root->right);
		return leftrotate(root);
	}
	filedeleting(root, 0, 0, "", "", 0, adr);
	return root;
}

node* AVL::deletecause(node* root, string cause) {
	if (root == NULL) {
		cout << "Value not found" << endl;
		return root;
	}

	if (cause < root->cause)
		root->left = deletecause(root->left, cause);

	else if (cause > root->cause)
		root->right = deletecause(root->right, cause);

	else
	{

		if ((root->left == NULL) ||
			(root->right == NULL))
		{
			node* temp = root->left ?
				root->left :
				root->right;

			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;
			free(temp);
		}
		else
		{
			node* temp = minValueNode(root->right);

			root->cause = temp->cause;
			root->right = deletecause(root->right,
				temp->cause);
		}
	}

	if (root == NULL)
		return root;

	root->height = 1 + max(getHeight(root->left),
		getHeight(root->right));

	int balance = getBalance(root);

	if (balance > 1 &&
		getBalance(root->left) >= 0)
		return rightrotate(root);

	if (balance > 1 &&
		getBalance(root->left) < 0)
	{
		root->left = leftrotate(root->left);
		return rightrotate(root);
	}

	if (balance < -1 &&
		getBalance(root->right) <= 0)
		return leftrotate(root);

	if (balance < -1 &&
		getBalance(root->right) > 0)
	{
		root->right = rightrotate(root->right);
		return leftrotate(root);
	}
	filedeleting(root, 0, 0, cause, "", 0, 0.0);
	return root;
}

node* AVL::deletedeaths(node* root, int deaths) {
	if (root == NULL) {
		cout << "Value not found" << endl;
		return root;
	}

	if (deaths < root->deaths)
		root->left = deletedeaths(root->left, deaths);

	else if (deaths > root->deaths)
		root->right = deletedeaths(root->right, deaths);

	else
	{

		if ((root->left == NULL) ||
			(root->right == NULL))
		{
			node* temp = root->left ?
				root->left :
				root->right;

			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;
			free(temp);
		}
		else
		{
			node* temp = minValueNode(root->right);

			root->deaths = temp->deaths;
			root->right = deletedeaths(root->right,
				temp->deaths);
		}
	}

	if (root == NULL)
		return root;

	root->height = 1 + max(getHeight(root->left),
		getHeight(root->right));

	int balance = getBalance(root);

	if (balance > 1 &&
		getBalance(root->left) >= 0)
		return rightrotate(root);

	if (balance > 1 &&
		getBalance(root->left) < 0)
	{
		root->left = leftrotate(root->left);
		return rightrotate(root);
	}

	if (balance < -1 &&
		getBalance(root->right) <= 0)
		return leftrotate(root);

	if (balance < -1 &&
		getBalance(root->right) > 0)
	{
		root->right = rightrotate(root->right);
		return leftrotate(root);
	}
	filedeleting(root, 0, 0, "", "", deaths, 0.0);
	return root;
}

node* AVL::deletestate(node* root, string state) {
	if (root == NULL) {
		cout << "Value not found" << endl;
		return root;
	}

	if (state < root->state)
		root->left = deletestate(root->left, state);

	else if (state > root->state)
		root->right = deletestate(root->right, state);

	else
	{

		if ((root->left == NULL) ||
			(root->right == NULL))
		{
			node* temp = root->left ?
				root->left :
				root->right;

			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;
			free(temp);
		}
		else
		{
			node* temp = minValueNode(root->right);

			root->state = temp->state;
			root->right = deletestate(root->right,
				temp->state);
		}
	}

	if (root == NULL)
		return root;

	root->height = 1 + max(getHeight(root->left),
		getHeight(root->right));

	int balance = getBalance(root);

	if (balance > 1 &&
		getBalance(root->left) >= 0)
		return rightrotate(root);

	if (balance > 1 &&
		getBalance(root->left) < 0)
	{
		root->left = leftrotate(root->left);
		return rightrotate(root);
	}

	if (balance < -1 &&
		getBalance(root->right) <= 0)
		return leftrotate(root);

	if (balance < -1 &&
		getBalance(root->right) > 0)
	{
		root->right = rightrotate(root->right);
		return leftrotate(root);
	}
	filedeleting(root, 0, 0, "", state, 0, 0.0);
	return root;
}

node* AVL::deleteyear(node* root, int year) {
	if (root == NULL) {
		cout << "Value not found" << endl;
		return root;
	}

	if (year < root->year)
		root->left = deleteyear(root->left, year);

	else if (year > root->year)
		root->right = deleteyear(root->right, year);

	else
	{

		if ((root->left == NULL) ||
			(root->right == NULL))
		{
			node* temp = root->left ?
				root->left :
				root->right;

			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;
			free(temp);
		}
		else
		{
			node* temp = minValueNode(root->right);

			root->year = temp->year;
			root->right = deleteyear(root->right,
				temp->year);
		}
	}

	if (root == NULL)
		return root;

	root->height = 1 + max(getHeight(root->left),
		getHeight(root->right));

	int balance = getBalance(root);

	if (balance > 1 &&
		getBalance(root->left) >= 0)
		return rightrotate(root);

	if (balance > 1 &&
		getBalance(root->left) < 0)
	{
		root->left = leftrotate(root->left);
		return rightrotate(root);
	}

	if (balance < -1 &&
		getBalance(root->right) <= 0)
		return leftrotate(root);

	if (balance < -1 &&
		getBalance(root->right) > 0)
	{
		root->right = rightrotate(root->right);
		return leftrotate(root);
	}
	filedeleting(root, 0, year, "", "", 0, 0.0);
	return root;
}

node* AVL::deleteID(node* root, int ID)
{
	if (root == NULL) {
		cout << "Value not found" << endl;
		return root;
	}

	if (ID < root->ID)
		root->left = deleteID(root->left, ID);

	else if (ID > root->ID)
		root->right = deleteID(root->right, ID);

	else
	{

		if ((root->left == NULL) ||
			(root->right == NULL))
		{
			node* temp = root->left ?
				root->left :
				root->right;

			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;
			free(temp);
		}
		else
		{
			node* temp = minValueNode(root->right);

			root->ID = temp->ID;
			root->right = deleteID(root->right,
				temp->ID);
		}
	}

	if (root == NULL)
		return root;

	root->height = 1 + max(getHeight(root->left),
		getHeight(root->right));

	int balance = getBalance(root);

	if (balance > 1 &&
		getBalance(root->left) >= 0)
		return rightrotate(root);

	if (balance > 1 &&
		getBalance(root->left) < 0)
	{
		root->left = leftrotate(root->left);
		return rightrotate(root);
	}

	if (balance < -1 &&
		getBalance(root->right) <= 0)
		return leftrotate(root);

	if (balance < -1 &&
		getBalance(root->right) > 0)
	{
		root->right = rightrotate(root->right);
		return leftrotate(root);
	}

	filedeleting(root, ID, 0, "", "", 0, 0.0);
	return root;
}


string convert_to_string(string file_name) {

	ifstream FileName(file_name);
	string line;

	if (FileName) {

		ostringstream ss;
		ss << FileName.rdbuf();           // reading data
		line = ss.str();

	}
	return line;
}

void AVLindexing(AVL& rootID, AVL& rootyear, AVL& rootstate, AVL& rootdeath, AVL& rootadr,AVL&causeN,char choice) {
	static bool firsttime;
	static int firstline = 0;

	int ID;
	int year;
	string cause113;
	string dimmycause113;
	string dimmy,dimmy2;
	string cause;
	string state;
	int deaths;
	float adr;
	ifstream fin;
	string fileName[2]{ "NCHS_-_Leading_Causes_of_Death__United_States_1.csv" ,"NCHS_-_Leading_Causes_of_Death__United_States_8.csv" };
		string line = "";
		
	
		for (int i = 0; i < 2; i++) {
			fin.open(fileName[i]);
			firstline = 0;
			line = "";
			
			while (getline(fin, line)) {
				string tempstring;
				stringstream inputstring(line);

				//getting ID
				getline(inputstring, tempstring, ',');
				ID = atoi(tempstring.c_str());

				//getting year
				tempstring = "";
				getline(inputstring, tempstring, ',');
				year = atoi(tempstring.c_str());

				//getting cause113,cause,state
				getline(inputstring, cause113, ',');
				for (int i = 0; i < cause113.size(); i++) {
					if (cause113[i] == '-') {
						getline(inputstring, dimmycause113, ',');
					}
				}
				getline(inputstring, cause, ',');
				getline(inputstring, state, ',');

				//getting death
				tempstring = "";
				getline(inputstring, tempstring, ',');
				deaths = atoi(tempstring.c_str());

				//getting adr
				tempstring = "";
				getline(inputstring, tempstring);
				adr = atof(tempstring.c_str());

				if (firstline != 0) {
						cout << ID << "  " << year << "  " << cause113 << " " << cause << " " << state << " " << deaths << " " << adr << endl;
					if (choice == '1') {
						rootID.AVLinsertion(rootID.root, ID, year, cause, state, deaths, adr, choice);//ID indexing

					}
					else if (choice == '2') {
						rootyear.AVLinsertion(rootyear.root, ID, year, cause, state, deaths, adr, choice);
					}
					else if (choice == '3') {
						rootstate.AVLinsertion(rootstate.root, ID, year, cause, state, deaths, adr, choice);
					}
					else if (choice == '4') {
						rootdeath.AVLinsertion(rootdeath.root, ID, year, cause, state, deaths, adr, choice);
					}
					else if (choice == '5') {
						rootadr.AVLinsertion(rootadr.root, ID, year, cause, state, deaths, adr, choice);
					}
					else if (choice == '6') {
						causeN.AVLinsertion(causeN.root, ID, year, cause, state, deaths, adr, choice);
					}
					else if (choice == '7') {
						rootyear.AVLinsertion(rootyear.root, ID, year, cause, state, deaths, adr, choice);
					}

				}
				else firstline++;
				line = "";

			}
				fin.close();
		}
		
		
	
}

void printdata(node* root) {
	/*system("cls");
	cout << "*************************************************************************" << endl;
	cout << "*                                       DBMS                            *" << endl;
	cout << "*************************************************************************\n" << endl;*/
	cout << "ID   year     cause     state     deaths     adr" << endl;

	        cout << root->ID << "   " << root->year << "   " << root->cause << "   " << root->state << "   " << root->deaths << "   " << root->adr << endl;
	if (root->next != NULL) {
		node* temp = root;
		while (temp->next != NULL) {

			temp = temp->next;
			cout << temp->ID << "   " << temp->year << "   " << temp->cause << "   " << temp->state << "   " << temp->deaths << "   " << temp->adr << endl;
		}
	}
}
bool searchID(node*& rootID, int ID) {
	if (rootID == NULL) {
		cout << "Not found ID " <<ID<< endl;
		return false;
	}

	if (ID == rootID->ID)
	{
		cout << "Key"<<ID<<" is found" << endl;
		printdata(rootID);
		return true;
	}

	else if (ID < rootID->ID) {
		searchID(rootID->left, ID);
	}
	else if (ID > rootID->ID) {
		searchID(rootID->right, ID);
	}
}

bool searchadr(node*& rootadr, float adr) {
	if (rootadr == NULL) {
		cout << "Not found adr " <<adr<< endl;
		return false;
	}

	if (adr == rootadr->adr)
	{
		cout << "adr "<<adr<<" is found" << endl;
		printdata(rootadr);
		return true;
	}

	else if (adr < rootadr->adr) {
		searchadr(rootadr->left, adr);
	}
	else if (adr > rootadr->adr) {
		searchadr(rootadr->right, adr);
	}
}


bool searchdeaths(node*& rootdeaths, int deaths) {

	if (rootdeaths == NULL) {
		cout << "Not found deaths "<<deaths << endl;
		return false;
	}

	if (deaths == rootdeaths->deaths)
	{
		cout << "Deaths "<<deaths<<"  is found" << endl;
		printdata(rootdeaths);
		return true;
	}

	else if (deaths < rootdeaths->deaths) {
		searchdeaths(rootdeaths->left, deaths);
	}
	else if (deaths > rootdeaths->deaths) {
		searchdeaths(rootdeaths->right, deaths);
	}
}

bool searchcause(node*& rootcause, string cause) {

	if (rootcause == NULL) {
		cout << "Not found cause " << cause << endl;
		return false;
	}

	if (cause == rootcause->cause)
	{
		cout << "cause " << cause << "  is found" << endl;
		printdata(rootcause);
		return true;
	}

	else if (cause < rootcause->cause) {
		searchcause(rootcause->left, cause);
	}
	else if (cause > rootcause->cause) {
		searchcause(rootcause->right, cause);
	}
}

bool searchyear(node*& rootyear, int year) {
	if (rootyear == NULL) {
		cout << "Not found the year  " << year<<endl;
		return false;
	}

	if (year == rootyear->year)
	{
		cout << "year "<< year<<" is found" << endl;
		printdata(rootyear);
		return true;
	}

	else if (year < rootyear->year) {
		searchyear(rootyear->left, year);
	}
	else if (year > rootyear->year) {
		searchyear(rootyear->right, year);
	}
}

bool searchstate(node*& rootstate, string state) {
	if (rootstate == NULL) {
		cout << "Not found the state " << state<<endl;
		return false;
	}

	if (state == rootstate->state)
	{
		cout << "state "<<state<<" is found" << endl;
		printdata(rootstate);
		return true;
	}

	else if (state < rootstate->state) {
		searchstate(rootstate->left, state);
	}
	else if (state > rootstate->state) {
		searchstate(rootstate->right, state);
	}
}
void IDRange(AVL rootID, int start, int end) {
	system("cls");
	cout << "*******************************************************" << endl;
	cout << "*                           DBMS                      *" << endl;
	cout << "*******************************************************\n" << endl;
	for (int i = start; i <= end; i++) {
		searchID(rootID.root, i);
	}
}

void yearRange(AVL rootyear, int start, int end) {
	system("cls");
	cout << "*******************************************************" << endl;
	cout << "*                           DBMS                      *" << endl;
	cout << "*******************************************************\n" << endl;


		for (int i = start; i <= end; i++) {
			searchyear(rootyear.root, i);
		}

}


void deathRange(AVL rootdeath, int start, int end) {
	system("cls");
	cout << "*******************************************************" << endl;
	cout << "*                           DBMS                      *" << endl;
	cout << "*******************************************************\n" << endl;


	for (int i = start; i <= end; i++) {
		searchdeaths(rootdeath.root, i);
	}

}

void adrrange(AVL rootadr, float start, float end) {
	system("cls");
	cout << "*******************************************************" << endl;
	cout << "*                           DBMS                      *" << endl;
	cout << "*******************************************************\n" << endl;

	for (float i = start; i <= end; i++) {
		searchadr(rootadr.root, i);
	}
}

bool searchwhere(node*& rootyear, int year,string state) {
	if (rootyear == NULL) {
		cout << "Not found the year  " << year << endl;
		return false;
	}

	if (year==rootyear->year || state==rootyear->state )
	{
		printdata(rootyear);
		return true;
	}

	else if (year < rootyear->year) {
		searchwhere(rootyear->left, year,state);
	}
	else if (year > rootyear->year) {
		searchwhere(rootyear->right, year,state);
	}
}

void Whereclause( AVL& rootyear) {
	int kyear;
	cout << "Kindly Enter the key (year)"<<endl;
		cin >> kyear;
		string kstate;
		cout << "Kindly enter the entry(state)"<<endl;
		cin >> kstate;
		AVL objID, objstate, objdeaths, objadr, objcause;
		AVLindexing(objID, rootyear, objstate, objdeaths,objadr, objcause, '2');
		searchwhere(rootyear.root, kyear,kstate);

		rootyear.~AVL();
}


void UpdateID(node*& rootID, int ID) 
{
	system("cls");
	cout << "*******************************************************" << endl;
	cout << "*                           DBMS                      *" << endl;
	cout << "*******************************************************\n" << endl;
	string fileName[2]{ "NCHS_-_Leading_Causes_of_Death__United_States_1.csv" ,"NCHS_-_Leading_Causes_of_Death__United_States_8.csv" };
	int nyear; string nstate,ncause; int ndeaths; float nadr;
	if (rootID == NULL) {
		cout << "Not found ID " << ID << endl;
		return ;
	}

	if (ID == rootID->ID)
	{
		cout << "ID " << ID << " is found" << endl;
		printdata(rootID);
		cout << "\nEnter the new year : "; cin >> nyear; rootID->year = nyear;
		cin.ignore();
		cout << "\nEnter the new cause : "; getline(cin,ncause); rootID->cause = ncause;
		cout << "\nEnter the new state : "; getline(cin, nstate); rootID->state = nstate;
		cout << "\nEnter the new deaths : "; cin >> ndeaths; rootID->deaths = ndeaths;
		cout << "\nEnter the new ADR : "; cin >> nadr; rootID->adr = nadr;

		cout << "Data is updated successfully" << endl;
		
		int fileID;
		int year;
		string cause113;
		string dimmycause113;
		string cause;
		string state;
		int deaths;
		float adr;
		ifstream fin;
		bool close = false;
		fstream fout;
		fout.open("temp.csv");
		string line = "";
		
		for (int i = 0; i < 2; i++) {


			fin.open(fileName[i]);
			while (getline(fin, line)) {
				string tempstring;
				stringstream inputstring(line);

				//getting ID
				getline(inputstring, tempstring, ',');
				fileID = atoi(tempstring.c_str());
				//getting year
				tempstring = "";
				getline(inputstring, tempstring, ',');
				year = atoi(tempstring.c_str());

				//getting cause113,cause,state
				string finalcause113;
				finalcause113 = "";
				getline(inputstring, cause113, ',');
				finalcause113 = cause113;
				for (int i = 0; i < cause113.size(); i++) {
					if (cause113[i] == '-') {
						getline(inputstring, dimmycause113, ',');
						finalcause113 = finalcause113 + ',' + dimmycause113;
					}

				}

				getline(inputstring, cause, ',');
				getline(inputstring, state, ',');

				//getting death
				tempstring = "";
				getline(inputstring, tempstring, ',');
				deaths = atoi(tempstring.c_str());

				//getting adr
				tempstring = "";
				getline(inputstring, tempstring);
				adr = atof(tempstring.c_str());

				if (fileID != ID) {
					fout << fileID << "," << year << "," << finalcause113 << "," << cause << "," << state << "," << deaths << "," << adr << endl;
				}
				else if (fileID == ID) {
					fout << fileID << "," << nyear << "," << finalcause113 << "," << ncause << "," << nstate << "," << ndeaths << "," << nadr << endl;
					close = true;
				
				}
			}
			fout.close();
			fin.close();

			remove(fileName[i].c_str());
			if (rename("temp.csv", fileName[i].c_str()) != 0) {
				cout << "Data is updated successfully" << endl;
			}
			if (close == true)
				return;
		}
		return ;
	}

	else if (ID < rootID->ID) {
		UpdateID(rootID->left, ID);
	}
	else if (ID > rootID->ID) {
	    UpdateID(rootID->right, ID);
	}

}


void AVLindexing_ID(AVL& rootID) {
	system("cls");
	cout << "*******************************************************" << endl;
	cout << "*                           DBMS                      *" << endl;
	cout << "*******************************************************\n" << endl;

	char choice; int val;
	back:
	cout << "1)Search ID.\n2)Delete ID.\n3)Update ID.\n4)ID Range query.\n";
	cin >> choice;
	switch (choice) {
	case'1':
		int id;
		cout << "Enter ID = "; cin >> id;
		system("cls");
		searchID(rootID.root, id);
		break;
	case '2':
		
		cout << "Enter the ID you want to delete : "; cin >> val;
		system("cls");
		searchID(rootID.root, val);
		rootID.root = rootID.deleteID(rootID.root, val);
		 cout << val << " deleted successfully" << endl;
		break;
	case '3':
		cout << "Enter the ID you want to update : "; cin >> val;
		UpdateID(rootID.root, val);
		break;

	case '4':
		int start, end;

		cout << "Enter the range (start - end) \n"; cin >> start; cin >> end;
		while (start > end) {
			cout << "Enter the range (start - end) \n"; cin >> start; cin >> end;
		}
		IDRange(rootID, start, end);
		break;
	default: {
		cout << "Select the valid option" << endl;
		goto back;
	}
	}
}

void AVLindexing_adr(AVL& rootadr) {
	system("cls");
	cout << "*******************************************************" << endl;
	cout << "*                           DBMS                      *" << endl;
	cout << "*******************************************************\n" << endl;
	char choice;
back:
	cout << "1)Search adr.\n2)Delete adr.\n3)Update adr.\n4)ADR range query.\n";
	cin >> choice;
	switch (choice) {
	case'1':
		float id;
		cout << "Enter adr = "; cin >> id;
		system("cls");
		searchadr(rootadr.root, id);
		break;
	case '2':
		float val;
		cout << "Enter the adr you want to delete : "; cin >> val;
		system("cls");
		searchadr(rootadr.root, val);
		rootadr.root = rootadr.deleteadr(rootadr.root, val);
		cout << val << " deleted successfully" << endl;
		break;
	case '4':
		float start, end;

		cout << "Enter the range (start - end) \n"; cin >> start; cin >> end;
		while (start > end) {
			cout << "Enter the range (start - end) \n"; cin >> start; cin >> end;
		}
		adrrange(rootadr, start, end);
		break;
	default: {
		cout << "Select the valid option" << endl;
		goto back;
	}
	}
}

void AVLindexing_deaths(AVL& rootdeaths) {
	system("cls");
	cout << "*******************************************************" << endl;
	cout << "*                           DBMS                      *" << endl;
	cout << "*******************************************************\n" << endl;

	char choice;
back:
	cout << "1)Search deaths.\n2)Delete deaths.\n3)Update deaths.\n4)Deaths range query.\n";
	cin >> choice;
	switch (choice) {
	case'1':
		int id;
		cout << "Enter deaths = "; cin >> id;
		system("cls");
		searchdeaths(rootdeaths.root, id);
		break;
	case '2':
		int val;
		cout << "Enter the deaths you want to delete : "; cin >> val;
		system("cls");
		searchID(rootdeaths.root, val);
		rootdeaths.root = rootdeaths.deletedeaths(rootdeaths.root, val);
		cout << val << " deleted successfully" << endl;
		break;
	case '4':
		int start, end;
		cout << "Enter the range (start - end) \n"; cin >> start; cout << " - "; cin >> end;
		while (start > end) {
			cout << "Enter the range (start - end) \n"; cin >> start; cin >> end;
		}
		deathRange(rootdeaths, start, end);
		break;
	default: {
		cout << "Select the valid option" << endl;
		goto back;
	}
	}
}

void AVLindexing_cause(AVL& rootcause) {
	system("cls");
	cout << "*******************************************************" << endl;
	cout << "*                           DBMS                      *" << endl;
	cout << "*******************************************************\n" << endl;
	string id;
	char choice;
back:
	cout << "1)Search cause.\n2)Delete cause.\n3)Update cause.\n4)Deaths range query.\n";
	cin >> choice;
	string val;
	switch (choice) {
	case'1':
		cout <<"Hello"<< rootcause.root->cause;
		cin.ignore();
		cout << "Enter cause = "; getline(cin, id);
		system("cls");
		searchcause(rootcause.root, id);
		break;
	case '2':
		cin.ignore();
		cout << "Enter the cause you want to delete : "; getline(cin,val);
		system("cls");
		searchcause(rootcause.root, val);
		rootcause.root = rootcause.deletecause(rootcause.root, val);
		cout << val << " deleted successfully" << endl;
		break;
	case '4':
		int start, end;
		cout << "Enter the range (start - end) \n"; cin >> start; cout << " - "; cin >> end;
		while (start > end) {
			cout << "Enter the range (start - end) \n"; cin >> start; cin >> end;
		}
		deathRange(rootcause, start, end);
		break;
	default: {
		cout << "Select the valid option" << endl;
		goto back;
	}
	}
}


void AVLindexing_year(AVL& rootyear) {
	system("cls");
	cout << "*******************************************************" << endl;
	cout << "*                           DBMS                      *" << endl;
	cout << "*******************************************************\n" << endl;

	char choice;
back:
	cout << "1)Search year.\n2)Delete year.\n3)Update year.\n4)Year range query.\n";
	cin >> choice;
	int year;
	switch (choice) {
	case'1':
		
		cout << "Enter year = "; cin >> year;
		system("cls");
		searchyear(rootyear.root, year);
		break;
	case '2':
		
		cout << "Enter the year you want to delete : "; cin >> year;
		system("cls");
		searchyear(rootyear.root, year);

		rootyear.root = rootyear.deleteyear(rootyear.root, year);
		cout << year << " deleted successfully" << endl;
		break;
	case '4':
		int start, end;
		cout << "Enter the range (start - end) \n"; cin >> start; cout << " - "; cin >> end;
		while (start > end) {
			cout << "Enter the range (start - end) \n"; cin >> start; cin >> end;
		}
		yearRange(rootyear, start, end);
		break;
	default: {
		cout << "Select the valid option" << endl;
		goto back;
	}
	}
}

void AVLindexing_state(AVL& rootstate) {
	system("cls");
	cout << "*******************************************************" << endl;
	cout << "*                           DBMS                      *" << endl;
	cout << "*******************************************************\n" << endl;

	char choice;
back:
	cout << "1)Search state.\n2)Delete state.\n3)Update state.\n4)State range query.\n";
	cin >> choice;
	string state;
	switch (choice) {
	case'1':
		cin.ignore();
		cout << "Enter state = "; getline(cin,state);
		system("cls");
		searchstate(rootstate.root, state);
		break;
	case '2':
		
		cout << "Enter the state you want to delete : "; cin >> state;
		system("cls");
		searchstate(rootstate.root, state);
		rootstate.root = rootstate.deletestate(rootstate.root, state);
		cout << state << " deleted successfully" << endl;
		break;
	default: {
		cout << "Select the valid option" << endl;
		goto back;
	}
	}
}

void writepreorder(node* root, fstream& fname) {
	
	if (root == NULL)
		return;

	fname << root->ID << "," <<root->year<<"," << root->state << "," << root->deaths << "," << root->adr << endl;
	writepreorder(root->left,fname);
	writepreorder(root->right, fname);

}
void writingfile(AVL rootID, AVL rootyear, AVL rootstate, AVL rootdeath, AVL rootadr, AVL rootcause) {
	string fileName[6] = { "id.txt" , "year.txt" , "state.txt" , "death.txt" , "adr.txt", "cause.txt" };
	fstream fout;
	for (int i = 0; i < 6; i++) {
		if (i == 0) {
			fout.open(fileName[0]);
			writepreorder(rootID.root, fout);
			fout.close();
		}
		if (i == 1) {
			fout.open(fileName[1]);
			writepreorder(rootyear.root, fout);
			fout.close();
		}
		if (i == 2) {
			fout.open(fileName[2]);
			writepreorder(rootstate.root, fout);
			fout.close();
		}
		if (i == 3) {
			fout.open(fileName[3]);
			writepreorder(rootdeath.root, fout);
			fout.close();
		}
		if (i == 4) {
			fout.open(fileName[4]);
			writepreorder(rootadr.root, fout);
			fout.close();
		}
		if (i == 5) {
			fout.open(fileName[5]);
			writepreorder(rootcause.root, fout);
			fout.close();
		}
		
	}
	
}
void AVLModule(AVL& rootID, AVL& rootyear, AVL& rootstate, AVL& rootdeath, AVL& rootadr,AVL& rootcause) {
	char choice;
	main:
	system("cls");
	cout << "*******************************************************" << endl;
	cout << "*                           DBMS                      *" << endl;
	cout << "*******************************************************\n" << endl;
	cout << "1)Indexing on ID.\n2)Indexing on year.\n3)Indexing on state. \n4)Indexing on deaths.\n5)Indexing on Age-Death-Rate.\n6)Indexing on cause name.\n7)Where Clause.\n8)Exit.\n";
back2:
	cout << "Select the desired option : "; cin >> choice;
	switch (choice) {
	case '1':
		AVLindexing(rootID, rootyear, rootstate, rootdeath, rootadr,rootcause, choice);
	Back3:
		AVLindexing_ID(rootID);
	correct:
		cout << "1)Wants to do any query again.\n2)Back to menu. " << endl;

		cout << "Select the desired option : "; cin >> choice;
		switch (choice) {
		case'1':
			goto Back3;
			break;
		case '2':
			goto main;
			break;
		default: {
			cout << "Choose the valid option" << endl;
			goto correct;
		}
		}
		break;

	case '2':
		AVLindexing(rootID, rootyear, rootstate, rootdeath, rootadr, rootcause,choice);
	Back4:
		AVLindexing_year(rootyear);
	correct2:
		cout << "1)Wants to do any query again\n2)Back to menu " << endl;

		cout << "Select the desired option : "; cin >> choice;
		switch (choice) {
		case'1':
			goto Back4;
			break;
		case '2':
			goto main;
			break;
		default: {
			cout << "Choose the valid option" << endl;
			goto correct2;
		}
		}
		break;

	case '3':
		AVLindexing(rootID, rootyear, rootstate, rootdeath, rootadr,rootcause, choice);
	Back5:
		AVLindexing_state(rootstate);
	correct3:
		cout << "1)Wants to do any query again\n2)Back to menu " << endl;

		cout << "Select the desired option : "; cin >> choice;
		switch (choice) {
		case'1':
			goto Back5;
			break;
		case '2':
			goto main;
			break;
		default: {
			cout << "Choose the valid option" << endl;
			goto correct3;
		}
		}
		break;

	case '4':
		AVLindexing(rootID, rootyear, rootstate, rootdeath, rootadr,rootcause, choice);
	Back6:
		AVLindexing_deaths(rootdeath);
	correct4:
		cout << "1)Wants to do any query again\n2)Back to menu " << endl;

		cout << "Select the desired option : "; cin >> choice;
		switch (choice) {
		case'1':
			goto Back6;
			break;
		case '2':
			goto main;
			break;
		default: {
			cout << "Choose the valid option" << endl;
			goto correct4;
		}
		}
		break;
	case '5':
		AVLindexing(rootID, rootyear, rootstate, rootdeath, rootadr,rootcause, choice);
	Back7:
		AVLindexing_adr(rootadr);
	correct5:
		cout << "1)Wants to do any query again\n2)Back to menu " << endl;

		cout << "Select the desired option : "; cin >> choice;
		switch (choice) {
		case'1':
			goto Back7;
			break;
		case '2':
			goto main;
			break;
		default: {
			cout << "Choose the valid option" << endl;
			goto correct5;
		}
		}
		break;
	case '6':
		AVLindexing(rootID, rootyear, rootstate, rootdeath, rootadr, rootcause, choice);
	Back8:
		AVLindexing_cause(rootcause);
	correct6:
		cout << "1)Wants to do any query again\n2)Back to menu " << endl;

		cout << "Select the desired option : "; cin >> choice;
		switch (choice) {
		case'1':
			goto Back8;
			break;
		case '2':
			goto main;
			break;
		default: {
			cout << "Choose the valid option" << endl;
			goto correct6;
		}
		}
		break;
	case '7':
		Whereclause(rootyear);
		break;
	case '8':
		writingfile(rootID, rootyear, rootstate, rootdeath, rootadr, rootcause);
		exit(0);
	default: {
		cout << "select the valid option" << endl;
		goto back2;
	}
	}

}
void mainscreen(AVL& rootID, AVL& rootyear, AVL& rootstate, AVL& rootdeath, AVL& rootadr,AVL& rootcause) {
     	cout << "************************************************************************"<<endl;
		cout << "*                         WELCOME TO DBMS                              *"<<endl;
		cout << "************************************************************************\n"<<endl;

		char choice;
	    main:
		cout << " 1)Indexing on base of AVL Tree.\n 2)Indexing on the base of B-Tree.(not implemented)\n 3)Indexing on the base of Red-Black Tree.(not implemented)\n 4)Exit\n";
		cout << "Select the desired option : "; cin >> choice;
		back:
		switch (choice) {
		case '1':
			AVLModule(rootID, rootyear, rootstate, rootdeath, rootadr,rootcause);
			break;
		case '2':
			break;
		case '3':
			break;
		case '4':
			exit(0);
		default:{
			cout << "Choose the valid option" << endl;
			goto back;
		}
	}
	
}

int main() {
	AVL objID, objyear, objstate,objdeaths,objadr,objcause;
	mainscreen(objID,objyear,objstate,objdeaths,objadr,objcause);

}