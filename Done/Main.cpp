#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <string>   
#include <vector>
#include <algorithm>
#include <fstream>
#include <functional>

using namespace std;

class Adder;
class Edge;
class Vertex;
class Graph;
class Files;
class ShowData;
class MainMenu;

class DATA
{
protected:
	vector<Edge*> edges;
	vector<Vertex*> vertexs;
	vector<vector<int>> listWays;
	friend class ShowData;
public:
	void ClearWays() 
	{
		listWays.clear();
	}
	virtual ~DATA()
	{
		vector<Edge*>().swap(edges);
		edges.shrink_to_fit();
		vector<Vertex*>().swap(vertexs);
		vertexs.shrink_to_fit();
		vector<vector<int>>().swap(listWays);
		listWays.shrink_to_fit();
	}
};

class Adder
{
private:
	int a, b, w, index;
	string label;
public:
	void ADEdge(vector<Vertex*>&, vector<Edge*>&, int);

	void ADVertex(vector<Vertex*>&, vector<Edge*>&, int);

	void ChangeEdge(vector<Edge*>&, vector<Vertex*>&, int);

	void ChangeEdge(vector<Edge*>&, vector<Vertex*>&);

	void ChangeVertex(vector<Vertex*>&);

	void ChangeVertex(vector<Vertex*>&, vector<Edge*>&);
};

class Edge
{
private:
	int u, v, weight;
	friend void Adder::ADEdge(vector<Vertex*>&, vector<Edge*>&, int);
	friend void Adder::ADVertex(vector<Vertex*>&, vector<Edge*>&, int);
	friend void Adder::ChangeEdge(vector<Edge*>&, vector<Vertex*>&, int);
	friend void Adder::ChangeEdge(vector<Edge*>&, vector<Vertex*>&);
	friend void Adder::ChangeVertex(vector<Vertex*>&, vector<Edge*>&);
	friend class Functions;
public:
	Edge(int u, int v, int weight)
	{
		this->u = u;
		this->v = v;
		this->weight = weight;
	}

	int U() {
		return u;
	}
	int V() {
		return v;
	}
	int WEIGHT() {
		return weight;
	}

	bool operator == (Edge &other) {
		return this->u == other.u && this->v == other.v;
	}
};

class Vertex
{
private:
	int index;
	string label;
	friend void Adder::ADVertex(vector<Vertex*>&, vector<Edge*>&, int);
	friend void Adder::ChangeVertex(vector<Vertex*>&);
	friend void Adder::ChangeVertex(vector<Vertex*>&, vector<Edge*>&);
	friend void Adder::ChangeEdge(vector<Edge*>&, vector<Vertex*>&, int);
	friend void Adder::ChangeEdge(vector<Edge*>&, vector<Vertex*>&);
	friend class Functions;
public:
	Vertex(int index, string label)
	{
		this->index = index;
		this->label = label;
	}

	int INDEX()
	{
		return index;
	}
	string LABEL()
	{
		return label;
	}

	bool operator == (const Vertex &other)
	{
		return this->index == other.index || this->label == other.label;
	}
};

class Functions : public DATA
{
public:
	Functions(vector<Edge*> edges1, vector<Vertex*> vertexs1)
	{
		edges = edges1;
		vertexs = vertexs1;
	}
	Functions(vector<Vertex*> vertexs1)
	{
		vertexs = vertexs1;
	}
	int FIRST(string label)
	{
		int index = -2;
		Vertex* tempVar = new Vertex(-1, label);

		for (int i = 0; i < vertexs.size(); i++)
		{
			if (vertexs[i]->label == tempVar->label)
				tempVar->index = vertexs[i]->index;
		}
		if (tempVar->index == -1)
			return -1;

		for (int j = 0; j < edges.size(); j++)
		{
			if (edges[j]->u == tempVar->index)
			{
				index = edges[j]->v;
				break;
			}

			if (edges[j]->v == tempVar->index)
			{
				index = edges[j]->u;
				break;
			}
		}

		return index;
	}
	int NEXT(string label, int index)
	{
		Vertex* tempVar = new Vertex(1, label);

		for (int i = 0; i < vertexs.size(); i++)
		{
			if (vertexs[i]->label == tempVar->label)
				tempVar->index = vertexs[i]->index;
		}
		if (tempVar->index == -1)
			return -1;

		int min = INT_MAX;
		for (int j = 0; j < edges.size(); j++)
		{
			if (edges[j]->u == tempVar->index)
			{
				if ((edges[j]->v > index) && (edges[j]->v < min))
					min = edges[j]->v;
			}

			if (edges[j]->v == tempVar->index)
			{
				if ((edges[j]->u > index) && (edges[j]->u < min))
					min = edges[j]->u;
			}
		}

		return min;
	}
	string VERTEX(string label, int index)
	{
		int sindex = -1;
		string slabel;

		Vertex* tempVar = new Vertex(-1, label);

		for (int i = 0; i < vertexs.size(); i++)
		{
			if (vertexs[i]->label == tempVar->label)
				tempVar->index = vertexs[i]->index;
		}
		if (tempVar->index == -1)
			return "-1";

		for (int j = 0; j < edges.size(); j++)
		{
			if (edges[j]->u == tempVar->index)
			{
				if (edges[j]->v == index)
					sindex = edges[j]->v;
			}

			if (edges[j]->v == tempVar->index)
			{
				if (edges[j]->u == index)
					sindex = edges[j]->u;
			}
		}

		if (sindex == -1)
			return "-2";

		Vertex* tempVar1 = new Vertex(sindex, "1");
		for (int i = 0; i < vertexs.size(); i++)
		{
			if (vertexs[i]->index == tempVar1->index)
				slabel = vertexs[i]->label;
		}

		return slabel;
	}

	int FindVertex(string label)
	{
		int index;
		for (vector<Vertex*>::iterator i = vertexs.begin(); i != vertexs.end(); i++)
		{
			if ((*i)->LABEL() == label)
				return (*i)->INDEX();
		}
		return -1;
	}

	string FindVertex(int index)
	{
		string label, no = "NOT";
		for (vector<Vertex*>::iterator i = vertexs.begin(); i != vertexs.end(); i++)
		{
			if ((*i)->INDEX() == index)
				return (*i)->LABEL();
		}
		return no;
	}

	bool VertexExists(string label)
	{
		for (vector<Vertex*>::iterator i = vertexs.begin(); i != vertexs.end(); i++)
		{
			if (label == (*i)->LABEL())
				return true;
		}
		return false;
	}

	bool VertexExists(int index)
	{
		for (vector<Vertex*>::iterator i = vertexs.begin(); i != vertexs.end(); i++)
		{
			if (index == (*i)->INDEX())
				return true;
		}
		return false;
	}
};

class Graph 
{
private:
	bool Find(vector<int> &list, int x)
	{
		if (list.empty())
			return false;
		else
		{
			for (int i = 0; i < list.size(); i++)
			{
				if (list[i] == x)
					return true;
			}
		}
		return false;
	}

	bool Compare(vector<int> &L1, vector<int> &L2)
	{
		if (L1.size() == L2.size())
		{
			for (int i = 0; i < L1.size(); i++)
			{
				if (L1[i] != L2[i])
					return false;
			}
		}
		else
			return false;
		return true;
	}

	void AddWay(vector<int> &list, vector<vector<int>> &listWays)
	{
		int i = 0;
		bool temp = true;
		while (i < listWays.size() && temp)
		{
			if (Compare(list, listWays[i]))
				temp = false;
			else
				i++;
		}
		if (temp || i == listWays.size())
		{
			listWays.push_back(vector<int>());
			for (int j = 0; j < list.size(); j++)
			{
				listWays[listWays.size() - 1].push_back(list[j]);
			}
		}
	}

public:
	void Ways(vector<Edge*> &edges, int numberEdge, vector<int> &list, vector<vector<int>> &listWays, int b)
	{
		for (int i = 0; i < edges.size(); i++)
		{
			Edge* edge = edges[i];
			if (!Find(list, numberEdge))
			{
				if (edge->U() == numberEdge)
				{
					list.push_back(numberEdge);

					if (!Find(list, edge->V()))
						Ways(edges, edge->V(), list, listWays, b);
					else
					{
						if (edge->U() == b)
							AddWay(list, listWays);
					}
					list.erase(remove(list.begin(), list.end(), numberEdge), list.end());
				}
			}
		}
	}
};

class Files
{
private:
	vector<string> split(const string& str, const char * delim)
	{
		vector<string> dest;
		char* pTempStr = _strdup(str.c_str());
		char* pWord = strtok(pTempStr, delim);
		while (pWord != NULL) 
		{
			dest.push_back(pWord);
			pWord = strtok(NULL, delim);
		}

		free(pTempStr);

		return dest;
	}

public:
	int ReadFromFile(string FILENAME, vector<Vertex*>& vertexs, vector<Edge*>& edges) 
	{
		char buff[255];
		vector<string> buffer;
		bool flag = 0;
		fstream fin;
		fin.open(FILENAME, ios::in);
		if (!fin.good())
		{
			return -1;
		}
		while (!fin.eof()) 
		{
			fin.getline(buff, 20);
			if (buff[0] == '#') 
			{
				flag = 1;
				continue;
			}
			if (flag == 0) 
			{
				buffer = split(buff, " ");
				Vertex* tempVar = new Vertex(atoi(buffer[0].c_str()), buffer[1].c_str());
				vertexs.push_back(tempVar);
			}
			if (flag == 1) 
			{
				buffer = split(buff, " ");
				Edge* tempVar1 = new Edge(atoi(buffer[0].c_str()), atoi(buffer[1].c_str()), atoi(buffer[2].c_str()));
				edges.push_back(tempVar1);
			}
		}

		fin.close();
		return 0;
	}

	void WriteFromFile(string FILENAME, vector<Vertex*> &vertexs, vector<Edge*> edges) 
	{
		ofstream out(FILENAME);

		for (vector<Vertex*>::iterator ITER = vertexs.begin(); ITER != vertexs.end(); ITER++) 
			out << (*ITER)->INDEX() << " " << (*ITER)->LABEL() << endl;
		out << "#" << endl;
		for (vector<Edge*>::iterator ITER = edges.begin(); ITER != edges.end(); ITER++)
			out << (*ITER)->U() << " " << (*ITER)->V() << " " << (*ITER)->WEIGHT() << endl;
		out.close();
	}
};

class ShowData
{
public:
	void Print(vector<vector<int>> list, vector<Vertex*> vertexs, Functions fun)
	{
		int j = 1;
		for (vector<vector<int>>::iterator ITER = list.begin(); ITER != list.end(); ITER++) {
			cout << "[" << j << "] ";
			for (const auto &i : *ITER)
				cout << fun.FindVertex(i) << " -> ";
			cout << endl;
			j++;
		}
	}
	void Print(vector<Edge*> edges, int flag, Functions fun)
	{
		for (vector<Edge*>::iterator ITER = edges.begin(); ITER != edges.end(); ITER++)
		{
			if (flag == 1)
				cout << fun.FindVertex((*ITER)->U()) << " -> " << fun.FindVertex((*ITER)->V()) << endl;
			else
				cout << fun.FindVertex((*ITER)->U()) << " -> " << fun.FindVertex((*ITER)->V()) << "   ���: " << (*ITER)->WEIGHT() << endl;
		}
	}
	void Print(vector<Vertex*> vertexs)
	{
		for (vector<Vertex*>::iterator i = vertexs.begin(); i != vertexs.end(); i++)
			cout << (*i)->LABEL() << " [" << (*i)->INDEX() << "]" << endl;
	}
};

void Adder::ADEdge(vector<Vertex*>& vertexs, vector<Edge*>& edges, int flag) 
{
	Functions fun(edges, vertexs);
	if (flag == 6)
	{
		int flag2 = -1;
		cout << "������ ���� �� 1 - �������� ��� 2 - �������� ������: ";
		cin >> flag2;
		cout << endl;
		if (flag2 = 1) 
		{
			cout << "������� ���� - ������� ������ � ��� (1 2 24): ";
			cin >> a >> b >> w;
			cout << endl;
			for (int j = 0; j < edges.size(); j++)
			{
				if (edges[j]->u == a && edges[j]->v == b)
				{
					cout << "���� " << a << " -> " << b << " � ����� " << edges[j]->weight << " ��� ����������!" << endl;
					cout << "����� �������� ��� ����, �������� '�������� ����'" << endl;
					return;
				}
			}
			Edge* tempVar = new Edge(a, b, w);
			edges.push_back(tempVar);
		}
		else
		{
			string label1, label2;
			cout << "������� ���� - �������� 1-�� �������: "; cin >> label1; cout << endl;
			cout << "������� ���� - �������� 2-�� �������: "; cin >> label2; cout << endl;
			cout << "������� ���� - ���: "; cin >> w; cout << endl;
			for (int j = 0; j < edges.size(); j++)
			{
				if (edges[j]->u == fun.FindVertex(label1) && edges[j]->v == fun.FindVertex(label2))
				{
					cout << "���� " << label1 << " -> " << label2 << " � ����� " << edges[j]->weight << " ��� ����������!" << endl;
					cout << "����� �������� ��� ����, �������� '�������� ����'" << endl;
					return;
				}
			}
			Edge* tempVar = new Edge(fun.FindVertex(label1), fun.FindVertex(label2), w);
			edges.push_back(tempVar);
		}
	}
	else
	{
		int flag2 = -1;
		cout << "������ ���� �� 1 - �������� ��� 2 - �������� ������: ";
		cin >> flag2;
		cout << endl;
		if (flag2 = 1)
		{
			cout << "������� ���� - ������� ������ (1 2): ";
			cin >> a >> b;
			cout << endl;
			if (!fun.VertexExists(a))
			{
				cout << "������� � �������� " << a << " �� ����������!" << endl;
				return;
			}
			if (!fun.VertexExists(b))
			{
				cout << "������� � �������� " << b << " �� ����������!" << endl;
				return;
			}
			int flagEx = -1;
			for (int j = 0; j < edges.size(); j++)
			{
				if (edges[j]->u == a && edges[j]->v == b)
				{
					flagEx = 1;
					break;
				}
			}
			if (flagEx == -1)
			{
				cout << "���� " << a << " -> " << b << " �� ����������!" << endl;
				return;
			}

			w = 0;
			Edge* tempVar = new Edge(a, b, w);
			for (int i = 0; i < edges.size(); i++)
			{
				if (edges[i]->u == tempVar->u && edges[i]->v == tempVar->v)
				{
					w = edges[i]->weight;
					edges.erase(edges.begin() + i);
				}
			}
			cout << "���� " << a << " -> " << b << " ����� " << w << " - �������!" << endl;
		}
		else
		{
			string label1, label2;
			cout << "������� ���� - �������� 1-�� �������: "; cin >> label1; cout << endl;
			cout << "������� ���� - �������� 2-�� �������: "; cin >> label2; cout << endl;
			if (!fun.VertexExists(label1))
			{
				cout << "������� � ��������� " << label1 << " �� ����������!" << endl;
				return;
			}
			if (!fun.VertexExists(label2))
			{
				cout << "������� � ��������� " << label2 << " �� ����������!" << endl;
				return;
			}
			a = fun.FindVertex(label1);
			b = fun.FindVertex(label2);
			int flagEx = -1;
			for (int j = 0; j < edges.size(); j++)
			{
				if (edges[j]->u == a && edges[j]->v == b)
				{
					flagEx = 1;
					break;
				}
			}
			if (flagEx == -1)
			{
				cout << "���� " << label1 << " -> " << label2 << " �� ����������!" << endl;
				return;
			}

			w = 0;
			Edge* tempVar = new Edge(a, b, w);
			for (int i = 0; i < edges.size(); i++)
			{
				if (edges[i]->u == tempVar->u && edges[i]->v == tempVar->v)
				{
					w = edges[i]->weight;
					edges.erase(edges.begin() + i);
				}
			}
			cout << "���� " << label1 << " -> " << label2 << " ����� " << w << " - �������!" << endl;
		}
	}

}
void Adder::ADVertex(vector<Vertex*>& vertexs, vector<Edge*>& edges, int flag) 
{
	Functions fun(edges, vertexs);
	if (flag == 3) 
	{
		cout << "������� ������ �������: ";
		cin >> index;
		cout << endl;
		if (fun.VertexExists(index) == true)
		{
			cout << "������� � ����� �������� ��� ����������!" << endl;
			return;
		}
		cout << "������� �������� �������: ";
		cin >> label;
		if (fun.VertexExists(label) == true)
		{
			cout << "������� � ����� ��������� ��� ����������!" << endl;
			return;
		}
		Vertex* tempVar = new Vertex(index, label);
		vertexs.push_back(tempVar);
		cout << "��������� ������� " << label << " � �������� " << index << endl;
	}
	else 
	{
		vector<Edge> DELedges;
		Edge* stemp = new Edge(0, 0, 0);
		int Tflag = 0;
		cout << "������� �� 1 - �������, 2 - ��������: " ;
		cin >> Tflag;
		cout << endl;
		if (Tflag == 1)
		{
			cout << "������� ������ �������: ";
			cin >> index;
			if (fun.VertexExists(index) == false)
			{
				cout << "������� � ����� �������� �� ����������!" << endl;
				return;
			}
			label = fun.FindVertex(index);
			for (int i = 0; i < vertexs.size(); i++)
			{
				if (vertexs[i]->index == index)
				{
					for (int j = 0; j < edges.size(); j++)
					{
						if (edges[j]->u == index)
						{
							stemp = edges[j];
							DELedges.push_back(*stemp);
							edges.erase(edges.begin() + j);
						}
						if (edges[j]->v == index)
						{
							stemp = edges[j];
							DELedges.push_back(*stemp);
							edges.erase(edges.begin() + j);
						}
					}
					vertexs.erase(vertexs.begin() + i);
				}
			}
			cout << "������� " << label << " ��� �������� " << index << " - ������A!" << endl;
		}
		else 
		{
			cout << "������� �������� �������: ";
			cin >> label;
			if (fun.VertexExists(label) == false)
			{
				cout << "������� � ����� ��������� �� ����������!" << endl;
				return;
			}
			index = fun.FindVertex(label);
			for (int i = 0; i < vertexs.size(); i++)
			{
				if (vertexs[i]->label == label)
				{
					for (int j = 0; j < edges.size(); j++)
					{
						if (edges[j]->u == fun.FindVertex(label))
						{
							stemp = edges[j];
							DELedges.push_back(*stemp);
							edges.erase(edges.begin() + j);
						}
						if (edges[j]->v == fun.FindVertex(label))
						{
							stemp = edges[j];
							DELedges.push_back(*stemp);
							edges.erase(edges.begin() + j);
						}
					}
					vertexs.erase(vertexs.begin() + i);
				}
			}
			cout << "������� " << label << " ��� �������� " << index << " - ������A!" << endl;
		}
		
		if (DELedges.size() != 0) {
			cout << "����� ������� " << DELedges.size() << " ���: " << endl;
			for (vector<Edge>::iterator ITER = DELedges.begin(); ITER != DELedges.end(); ITER++)
				cout << "                     " << ITER->U() << " - " << ITER->V() << endl;
		}
	}
}
void Adder::ChangeEdge(vector<Edge*>& edges, vector<Vertex*>& vertexs, int flag)
{
	Functions fun(edges, vertexs);
	int flag2 = -1;
	cout << "������ ���� �� 1 - �������� ��� 2 - �������� ������: ";
	cin >> flag2;
	cout << endl;
	if (flag2 = 1)
	{
		cout << "������� ������� ������ ���, � ������� ������ �������� ��� (1 2): ";
		cin >> a >> b;
		cout << endl;
		cout << "������� ����� ���: ";
		cin >> w;
		if (!fun.VertexExists(a))
		{
			cout << "������� � �������� " << a << " �� ����������!" << endl;
			return;
		}
		if (!fun.VertexExists(b))
		{
			cout << "������� � �������� " << b << " �� ����������!" << endl;
			return;
		}
		int flagEx = -1;
		for (int j = 0; j < edges.size(); j++)
		{
			if (edges[j]->u == a && edges[j]->v == b)
			{
				flagEx = 1;
				break;
			}
		}
		if (flagEx == -1)
		{
			cout << "���� " << a << " -> " << b << " �� ����������!" << endl;
			return;
		}

		int tempW;
		Edge* tempVar = new Edge(a, b, w);
		for (int i = 0; i < edges.size(); i++)
		{
			if (edges[i]->u == tempVar->u && edges[i]->v == tempVar->v)
			{
				tempW = edges[i]->weight;
				edges[i]->weight = w;
			}
		}
		cout << "���� " << a << " -> " << b << " ���� � ����� " << tempW << " ����� � ����� " << w << endl;
	}
	else
	{
		string label1, label2;
		cout << "������� ���� - �������� 1-�� �������: "; cin >> label1; cout << endl;
		cout << "������� ���� - �������� 2-�� �������: "; cin >> label2; cout << endl;
		if (!fun.VertexExists(label1))
		{
			cout << "������� � ��������� " << label1 << " �� ����������!" << endl;
			return;
		}
		if (!fun.VertexExists(label2))
		{
			cout << "������� � ��������� " << label2 << " �� ����������!" << endl;
			return;
		}
		a = fun.FindVertex(label1);
		b = fun.FindVertex(label2);
		int flagEx = -1;
		for (int j = 0; j < edges.size(); j++)
		{
			if (edges[j]->u == a && edges[j]->v == b)
			{
				flagEx = 1;
				break;
			}
		}
		if (flagEx == -1)
		{
			cout << "���� " << label1 << " -> " << label2 << " �� ����������!" << endl;
			return;
		}

		int tempW;
		Edge* tempVar = new Edge(a, b, w);
		for (int i = 0; i < edges.size(); i++)
		{
			if (edges[i]->u == tempVar->u && edges[i]->v == tempVar->v)
			{
				tempW = edges[i]->weight;
				edges[i]->weight = w;
			}
		}
		cout << "���� " << label1 << " -> " << label2 << " ���� � ����� " << tempW << " ����� � ����� " << w << endl;
	}
}
void Adder::ChangeEdge(vector<Edge*>& edges, vector<Vertex*>& vertexs)
{
	Functions fun(edges, vertexs);
	int flag2 = -1;
	cout << "������ ���� �� 1 - �������� ��� 2 - �������� ������: ";
	cin >> flag2;
	cout << endl;
	if (flag2 = 1)
	{
		cout << "������� ������� ������ ����, � ������� ������ �������� ����������� (1 2): ";
		cin >> a >> b;
		cout << endl;
		if (!fun.VertexExists(a))
		{
			cout << "������� � �������� " << a << " �� ����������!" << endl;
			return;
		}
		if (!fun.VertexExists(b))
		{
			cout << "������� � �������� " << b << " �� ����������!" << endl;
			return;
		}
		int flagEx = -1;
		for (int j = 0; j < edges.size(); j++)
		{
			if (edges[j]->u == a && edges[j]->v == b)
			{
				flagEx = 1;
				break;
			}
		}
		if (flagEx == -1)
		{
			cout << "���� " << a << " -> " << b << " �� ����������!" << endl;
			return;
		}

		w = 0;
		int temp;
		Edge* tempVar = new Edge(a, b, w);
		for (int i = 0; i < edges.size(); i++)
		{
			if (edges[i]->u == tempVar->u && edges[i]->v == tempVar->v)
			{
				w = i;
				temp = edges[i]->u;
				edges[i]->u = edges[i]->v;
				edges[i]->v = temp;
			}
		}
		cout << "���� " << a << " -> " << b << " ����� " << edges[w]->u << " -> " << edges[w]->v << endl;
	}
	else
	{
		string label1, label2;
		cout << "������� ���� - �������� 1-�� �������: "; cin >> label1; cout << endl;
		cout << "������� ���� - �������� 2-�� �������: "; cin >> label2; cout << endl;
		if (!fun.VertexExists(label1))
		{
			cout << "������� � ��������� " << label1 << " �� ����������!" << endl;
			return;
		}
		if (!fun.VertexExists(label2))
		{
			cout << "������� � ��������� " << label2 << " �� ����������!" << endl;
			return;
		}
		a = fun.FindVertex(label1);
		b = fun.FindVertex(label2);
		int flagEx = -1;
		for (int j = 0; j < edges.size(); j++)
		{
			if (edges[j]->u == a && edges[j]->v == b)
			{
				flagEx = 1;
				break;
			}
		}
		if (flagEx == -1)
		{
			cout << "���� " << label1 << " -> " << label2 << " �� ����������!" << endl;
			return;
		}

		w = 0;
		int temp;
		Edge* tempVar = new Edge(a, b, w);
		for (int i = 0; i < edges.size(); i++)
		{
			if (edges[i]->u == tempVar->u && edges[i]->v == tempVar->v)
			{
				w = i;
				temp = edges[i]->u;
				edges[i]->u = edges[i]->v;
				edges[i]->v = temp;
			}
		}
		cout << "���� " << label1 << " -> " << label2 << " ����� " << fun.FindVertex(edges[w]->u) << " -> " << fun.FindVertex(edges[w]->v) << endl;
	}
}
void Adder::ChangeVertex(vector<Vertex*>& vertexs)
{
	Functions fun(vertexs);
	cout << "�������  �������� �������, ������� ������ �������������: ";
	cin >> label;
	if (fun.VertexExists(label) == false)
	{
		cout << "������� � ����� ��������� �� ����������!" << endl;
		return;
	}
	cout << endl;
	cout << "������� ����� ��������: ";
	string newlabel;
	cin >> newlabel;
	if (fun.VertexExists(newlabel) == true)
	{
		cout << "������� � ����� ��������� ��� ����������!" << endl;
		return;
	}

	for (int i = 0; i < vertexs.size(); i++)
	{
		if (vertexs[i]->label == label)
			vertexs[i]->label = newlabel;
	}
	cout << "������� � ��������� " << label << " � �������� " << fun.FindVertex(newlabel) << " ���� ������������� � " << newlabel << endl;
}
void Adder::ChangeVertex(vector<Vertex*>& vertexs, vector<Edge*>& edges)
{
	Functions fun(edges, vertexs);
	cout << "������� �������� �������, � ������� ������ �������� ������: ";
	cin >> label;
	cout << endl;
	if (fun.VertexExists(label) == false)
	{
		cout << "������� � ����� ��������� �� ����������!" << endl;
		return;
	}
	cout << "������� ����� ������: ";
	int newindex;
	cin >> newindex;
	cout << endl;

	if (fun.VertexExists(newindex) == true)
	{
		bool q;
		cout << "������� ������� � ����� " << fun.FindVertex(newindex) << " � ����� �� ��������!" << endl;
		cout << "������� ����� ���������! (��� ���� ����� ���������� � " << label << " � ����� �������� " << newindex << " ), � " << fun.FindVertex(newindex) << " ����� �������!" << endl;
		cout << "����������? 1 - ��, 0 - ���: ";
		cin >> q;
		cout << endl;
		if (q)
		{
			vector<Edge> BReplaceedges;
			vector<Edge*> AReplaceedges;
			Edge* stemp = new Edge(0, 0, 0);
			for (int j = 0; j < edges.size(); j++)
			{
				if (edges[j]->u == fun.FindVertex(label))
				{
					stemp = edges[j];
					BReplaceedges.push_back(*stemp);
					edges[j]->u = newindex;
					AReplaceedges.push_back(edges[j]);
				}
				if (edges[j]->v == fun.FindVertex(label))
				{
					stemp = edges[j];
					BReplaceedges.push_back(*stemp);
					edges[j]->v = newindex;
					AReplaceedges.push_back(edges[j]);
				}
			}
			
			cout << "�������" << label << " ���� � �������� " << fun.FindVertex(label) << " ����� � " << newindex << endl;
			cout << "�������" << fun.FindVertex(newindex) << " � �������� " << newindex << " �������! " << endl;

			for (int i = 0; i < vertexs.size(); i++)
			{
				if (vertexs[i]->label == label)
					vertexs.erase(vertexs.begin() + i);
			}
			for (int i = 0; i < vertexs.size(); i++)
			{
				if (vertexs[i]->index == newindex)
					vertexs[i]->label = label;
			}
			if (BReplaceedges.size() != 0) 
			{
				cout << "���� �������� " << BReplaceedges.size() << " ���" << endl;
				vector<Edge>::iterator ITER2 = BReplaceedges.begin();
				for (vector<Edge*>::iterator ITER = AReplaceedges.begin(); ITER != AReplaceedges.end(); ITER++, ITER2++)
					cout << ITER2->U() << " - " << ITER2->V() << "==>" << (*ITER)->U() << " - " << (*ITER)->V() << endl;
			}
		}
	}
	else
	{
		cout << "� ������� � ��������� " << label << " � �������� " << fun.FindVertex(label) << " ��� ������� ������ �� " << newindex << endl;
		for (int j = 0; j < vertexs.size(); j++)
		{
			if (vertexs[j]->label == label)
				vertexs[j]->index = newindex;
		}
	}
}

class MainMenu : public DATA
{
private:
	int flag, check;
	vector<int> Paph;
public:
	Graph graph;
	ShowData show;
	Adder add;
	void menu()
	{
		cout << "      ________________________________________________________________________________________________________" << endl;
		cout << "     |                                                                                                        |" << endl;
		cout << "     |                                                  ����                                                  |" << endl;
		cout << "     |________________________________________________________________________________________________________|" << endl;
		cout << "     |                                                                                                        |" << endl;
		cout << "     |       (1) ��������� ���� �� �����              (7) ������� ����                                        |" << endl;
		cout << "     |       (2) ������� ����                         (8) �������� ����                                       |" << endl;
		cout << "     |       (3) �������� �������                     (9) ����� ��� ������� ���� �� A �� B                    |" << endl;
		cout << "     |       (4) ������� �������                      (10) ������� FIRST(v), NEXT(v, i), VERTEX(v, i)         |" << endl;
		cout << "     |       (5) �������� �������                     (11) ��������� ������� ����                             |" << endl;
		cout << "     |       (6) �������� ����                        (12) ������� ������� ����                               |" << endl;
		cout << "     |                                                                                                        |" << endl;
		cout << "     |                                        (13) ����� �� ���������                                         |" << endl;
		cout << "     |________________________________________________________________________________________________________|" << endl;
	}
	void input_item()
	{
		menu();
		Functions fun(edges, vertexs);
		cout << endl;
		cout << "�������� ��������: ";
		cin >> flag;

		if (flag <= 0 or flag > 14) {
			cout << "������� �������� ��������. ��������� ����!" << endl;
			system("pause"); system("cls");
			input_item();
		}
		if (flag == 1)
		{
			Files file;
			string FILENAME;
			cout << "������� ��� �����: ";
			cin >> FILENAME;
			check = file.ReadFromFile(FILENAME, vertexs, edges);
			if (check == -1)
				cout << "������ ������ �����!" << endl;
			else
				cout << "���� ��������!" << endl;
			system("pause"); system("cls");
			input_item();
		}
		if (flag == 2)
		{
			if (!vertexs.empty())
			{
				Functions fun(edges, vertexs);
				cout << "������� 1 - ������ ���" << endl;
				cout << "        2 - ������ ����� ���" << endl;
				cout << "        3 - ������ ������ � ��������: ";
				cin >> flag;
				cout << endl;
				if (flag == 1 or flag == 2)
				{
					if (!edges.empty())
						show.Print(edges, flag, fun);
					else
						cout << "� ����� ��� ���!" << endl;
				}
				else if (flag == 3)
				{
					show.Print(vertexs);
				}
				else
				{
					cout << "������� �������� ��������. ��������� ����!" << endl;
					system("pause"); system("cls");
					input_item();
				}
			}
			else cout << "���� ����! (��� �� ����� �������)" << endl; system("pause"); system("cls");
			input_item();
		}
		if (flag == 3)
		{
			add.ADVertex(vertexs, edges, flag);
			system("pause"); system("cls");
			input_item();
		}
		if (flag == 4)
		{
			if (!vertexs.empty()) {
				add.ADVertex(vertexs, edges, flag);
			}
			else cout << "� ����� ��� ������!" << endl; system("pause"); system("cls");
			input_item();
		}
		if (flag == 5)
		{
			if (!vertexs.empty()) {
				cout << "�������� 1 - ��������" << endl;
				cout << "         2 - ������: ";
				cin >> flag;
				if (flag == 1)
					add.ChangeVertex(vertexs);
				else if (flag == 2)
					add.ChangeVertex(vertexs, edges);
				else
				{
					cout << "������� �������� ��������. ��������� ����!" << endl;
					system("pause"); system("cls");
					input_item();
				}
			}
			else cout << "���� ������! � ����� ��� ������." << endl; system("pause"); system("cls");
			input_item();
		}
		if (flag == 6)
		{
			add.ADEdge(vertexs, edges, flag);
			system("pause"); system("cls");
			input_item();
		}
		if (flag == 7)
		{
			if (!edges.empty()) {
				add.ADEdge(vertexs, edges, flag);
			}
			else cout << "� ����� ��� ���!" << endl; system("pause"); system("cls");
			input_item();
		}
		if (flag == 8)
		{
			if (!edges.empty()) {
				cout << "�������� 1 - ����������� ����" << endl;
				cout << "         2 - ��� ����: ";
				cin >> flag;
				if (flag == 1)
					add.ChangeEdge(edges, vertexs);
				else if (flag == 2)
					add.ChangeEdge(edges, vertexs, 2);
				else
				{
					cout << "������� �������� ��������. ��������� ����!" << endl;
					system("pause"); system("cls");
					input_item();
				}
			}
			else cout << "� ����� ��� ���!" << endl; system("pause"); system("cls");
			input_item();
		}
		if (flag == 9)
		{
			if (!edges.empty()) {
				int a, b, flag2 = -1;
				cout << "������ ���� 1 - �� �������� 2 - ��������� ������: ";
				cin >> flag2;
				if (flag2 == 1)
				{
					do
					{
						cout << "������� ���� �� A �� B - ������� ������ (1 2): ";
						cin >> a >> b;
						if (!fun.VertexExists(a))
							cout << "������� � �������� " << a << " �� ����������!" << endl;
						if (!fun.VertexExists(b))
							cout << "������� � �������� " << b << " �� ����������!" << endl;
					} while (!fun.VertexExists(a) && !fun.VertexExists(b));
				
				}
				else
				{
					string label1, label2;
					do
					{
						cout << "������� �������� 1-�� �������: "; cin >> label1; cout << endl;
						cout << "������� �������� 2-�� �������: "; cin >> label2; cout << endl;
						if (!fun.VertexExists(label1))
							cout << "������� � ��������� " << label1 << " �� ����������!" << endl;
						
						if(!fun.VertexExists(label2))
							cout << "������� � ��������� " << label2 << " �� ����������!" << endl;
					} while (!fun.VertexExists(label1) && !fun.VertexExists(label2));
					a = fun.FindVertex(label1);
					b = fun.FindVertex(label2);
				}
				
				graph.Ways(edges, a, Paph, listWays, b);
				if (!listWays.empty()) {
					show.Print(listWays, vertexs, fun);
					ClearWays();
				}
				else cout << "����� �� " << fun.FindVertex(a) << " � " << fun.FindVertex(b) << " �� ����������!" << endl;
			}
			else cout << "� ����� ��� ���!" << endl; system("pause"); system("cls");
			input_item();
		}
		if (flag == 10)
		{
			if (!vertexs.empty()) {
				cout << "                  1 - FIRST(v), ������� ���������� ������ ������ ������� ������� � �����" << endl;
				cout << "                  2 - NEXT(v, i), ������� �	" << endl;
				cout << "                  3 - VERTEX(v, i), ������� ���������� ������� � �������� i �� ��������� ������, ������� � v" << endl;
				cout << "�������� �������: "; cin >> flag;
				cout << endl;
				if (flag == 1) 
				{
					string label;
					cout << "������� �������� �������: "; cin >> label;
					if (fun.FIRST(label) == -1)
						cout << "����� ������� ��� � �����!" << endl;
					else if (fun.FIRST(label) == -2)
						cout << "� ������ ��� ������� ������!" << endl;
					else
						cout << "�������, ������� � " << label << " ����� ������ " << fun.FIRST(label) << endl;
				}
				else if (flag == 2) 
				{
					string label;
					cout << "������� �������� �������: "; cin >> label;
					cout << endl;
					int index;
					cout << "������� ������: "; cin >> index;
					if (fun.NEXT(label, index) == -1)
						cout << "����� ������� ��� � �����!" << endl;
					else if (fun.NEXT(label, index) == INT_MAX)
						cout << "� ������� ��� ����� ������� �������!" << endl;
					else
						cout << "������ �������, ������� � �������� " << label << ", ��������� �� �������� " << index << " ����� " << fun.NEXT(label, index) << endl;
				}
				else if (flag == 3) 
				{
					string label;
					cout << "������� �������� �������: "; cin >> label;
					cout << endl;
					int index;
					cout << "������� ������: "; cin >> index;
					if (fun.VERTEX(label, index) == "-1")
						cout << "����� ������� ��� � �����!" << endl;
					else if (fun.VERTEX(label, index) == "-2")
						cout << "� ������� ��� ������� ������!" << endl;
					cout << "������� " << fun.VERTEX(label, index) << " � �������� " << index << " �� ��������� ������, ������� � " << label << endl;
				}
				else
				{
					cout << "������� �������� ��������. ��������� ����!" << endl;
					system("pause"); system("cls");
					input_item();
				}
			}
			else cout << "� ����� ��� ������!" << endl; system("pause"); system("cls");
			input_item();
		}
		if (flag == 11)
		{
			if (!vertexs.empty()) {
				Files file;
				string FILENAME;
				cout << "������� ��� ������ �����: ";
				cin >> FILENAME;
				file.WriteFromFile(FILENAME, vertexs, edges);
			}
			else cout << "� ����� ��� ������!" << endl; system("pause"); system("cls");
			input_item();
		}
		if (flag == 12)
		{
			edges.clear();
			vertexs.clear();
			if (vertexs.empty() && edges.empty())
				cout << "������� ���� ������!" << endl;
			else
				cout << "ERROR: ��������� ������ ��������!" << endl;

			system("pause"); system("cls");
			input_item();
		}
		if (flag == 13)
			exit(0);
	}
	~MainMenu() override
	{
		vector<int>().swap(Paph);
		Paph.shrink_to_fit();
		graph.~Graph();
		show.~ShowData();
		add.~Adder();
	}
};

void main()
{
	setlocale(LC_ALL, "RUS");
	MainMenu start;
	start.input_item();
	system("pause");
}