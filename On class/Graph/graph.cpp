#include <bits/stdc++.h>
using namespace std;
class GraphQ1
{
private:
    int **data;
    int numOfVertices;
    bool isWeightedGraph;
    bool isDirectedGraph;

public:
    GraphQ1(int numOfVertices, bool isWeighted = false, bool isDirected = false)
    {
        this->numOfVertices = numOfVertices;
        this->isWeightedGraph = isWeighted;
        this->isDirectedGraph = isDirected;

        this->data = new int *[numOfVertices];
        for (int i = 0; i < numOfVertices; i++)
        {
            this->data[i] = new int[numOfVertices];
            for (int j = 0; j < numOfVertices; j++)
            {
                this->data[i][j] = 0;
            }
        }
    }

    void addVertex()
    {
        int **data2 = new int *[numOfVertices + 1];
        for (int i = 0; i < numOfVertices; i++)
        {
            this->data[i] = new int[numOfVertices + 1];
            for (int j = 0; j < numOfVertices; j++)
                data2[i][j] = this->data[i][j];
        }
        for (int i = 0; i < numOfVertices + 1; i++)
        {
            data2[numOfVertices][i] = 0;
            data2[i][numOfVertices] = 0;
        }
        for (int i = 0; i < numOfVertices; i++)
            delete[] data[i];
        delete[] data;
        data = data2;
        this->numOfVertices++;
        
    }

    void addVertices(int numToAdd = 1)
    {
        int **data2 = new int *[numOfVertices + numToAdd];
        for (int i = 0; i < numOfVertices; i++)
        {
            this->data[i] = new int[numOfVertices + numToAdd];
            for (int j = 0; j < numOfVertices; j++)
                data2[i][j] = this->data[i][j];
        }
        for (int i = numOfVertices; i < numOfVertices + numToAdd; i++)
        {
            for (int j = 0; j < numOfVertices + numToAdd; j++)
            {
                data2[i][j] = 0;
                data2[j][i] = 0;
            }
        }
        for (int i = 0; i < numOfVertices; i++)
            delete[] data[i];
        delete[] data;
        data = data2;
        this->numOfVertices += numToAdd;
    }

    void addEgde(int source, int destination, int weight = 1)
    {
        this->data[source - 1][destination - 1] = weight;
        if (isDirectedGraph == 0)
            this->data[destination - 1][source - 1] = weight;
    }

    void removeEdge(int source, int destination)
    {
        this->data[source - 1][destination - 1] = 0;
        if (isDirectedGraph == 0)
            this->data[destination - 1][source - 1] = 0;
    }

    void dump()
    {
        for (int i = 0; i < this->numOfVertices; ++i)
        {
            cout << "Vertex " << i + 1 << ":" << endl;
            for (int j = 0; j < this->numOfVertices; ++j)
            {
                if (this->data[i][j] != 0)
                    cout << "   -> To " << j + 1 << (this->isWeightedGraph ? ": " + to_string(this->data[i][j]) : "") << endl;
            }
        }
    }

    ~GraphQ1()
    {
        for (int i = 0; i < numOfVertices; i++)
        {
            delete[] this->data[i];
        }
        delete[] this->data;
    }
};

class GraphQ2
{
private:
    map<string, int> dictionary;
    int **data;
    int numOfVertices;
    bool isWeightedGraph;
    bool isDirectedGraph;

protected:
    // Increase capacity of adjacency matrix and return current number of vertices
    int ensure(int newNumOfVertices)
    {
        if (this->numOfVertices >= newNumOfVertices)
            return this->numOfVertices;

        int **newData = new int *[newNumOfVertices];
        for (int i = 0; i < newNumOfVertices; i++)
        {
            newData[i] = new int[newNumOfVertices];
            for (int j = 0; j < newNumOfVertices; j++)
            {
                if (i < this->numOfVertices && j < this->numOfVertices)
                {
                    newData[i][j] = this->data[i][j];
                }
                else
                    newData[i][j] = 0;
            }
        }

        for (int i = 0; i < numOfVertices; i++)
        {
            delete[] this->data[i];
        }
        delete[] this->data;

        this->data = newData;

        int currentNumOfVertices = this->numOfVertices;
        this->numOfVertices = newNumOfVertices;

        return currentNumOfVertices;
    }

    string getName(int index)
    {
        map<string, int>::iterator it;
        for (it = this->dictionary.begin(); it != this->dictionary.end(); ++it)
        {
            if (it->second == index)
                return it->first;
        }
        return "";
    }

public:
    GraphQ2(bool isWeighted = false, bool isDirected = false)
    {
        this->isWeightedGraph = isWeighted;
        this->isDirectedGraph = isDirected;
        this->numOfVertices = 0;
        this->data = NULL;
    }

    void addVertex(string vName)
    {
        dictionary.insert(pair <string, int> (vName, this -> numOfVertices));
        this -> numOfVertices = ensure(this -> numOfVertices + 1) + 1;
    }

    void addVertices(string vNameList[], int numToAdd)
    {
        for (int i = 0; i < numToAdd; i++)
            dictionary[vNameList[i]] = this -> numOfVertices + i;
        this -> numOfVertices = ensure(this -> numOfVertices + numToAdd) + numToAdd;
    }

    void addEdge(string sourceName, string destinationName, int weight = 1)
    {
        this->data[dictionary[sourceName]][dictionary[destinationName]] = weight;
        if (isDirectedGraph == 0)
            this->data[dictionary[destinationName]][dictionary[sourceName]] = weight;
    }

    void removeEdge(string sourceName, string destinationName)
    {
        this->data[dictionary[sourceName]][dictionary[destinationName]] = 0;
        if (isDirectedGraph == 0)
            this->data[dictionary[destinationName]][dictionary[sourceName]] = 0;
    }

    void dump()
    {
        for (int i = 0; i < this->numOfVertices; ++i)
        {
            string sourceName = this->getName(i);
            cout << "Vertex " << sourceName << ":" << endl;
            for (int j = 0; j < this->numOfVertices; ++j)
            {
                string destinationName = this->getName(j);
                if (this->data[i][j] != 0)
                    cout << "   -> To " << destinationName << (this->isWeightedGraph ? ": " + to_string(this->data[i][j]) : "") << endl;
            }
        }
    }

    ~GraphQ2()
    {
        for (int i = 0; i < numOfVertices; i++)
            delete[] this->data[i];
        delete[] this->data;
    }
};

class GraphQ3
{
    class GEdge; // Forward declaration
public:
    int numOfVertices;
    bool isWeightedGraph;
    bool isDiretedGraph;
    map<string, list<GEdge> > adjVertices;
    GraphQ3(bool isWeighted = false, bool isDireted = false)
    {
        this->numOfVertices = 0;
        this->isWeightedGraph = isWeighted;
        this->isDiretedGraph = isDireted;
        this->adjVertices.clear();
    }
    bool isWeighted() const { return this->isWeightedGraph; }
    bool isDireted() const { return this->isDiretedGraph; }

    void addVertex(string vName)
    {
        adjVertices[vName] = {};
        numOfVertices++;
    }

    void addVertices(string *vNames, int numOfVerticesToAdd)
    {
        for (int i = 0; i < numOfVerticesToAdd; i++)
            adjVertices[vNames[i]] = {};
        numOfVertices += numOfVerticesToAdd;
    }

    void addEdge(string source, string destination, int weight = 0)
    {
        GEdge addSource = GEdge(destination, weight);
        GEdge addDestination = GEdge(source, weight);
        adjVertices[source].push_back(addSource);
        if (!isDireted())
            adjVertices[destination].push_back(addDestination);
    }

    void removeEdge(string source, string destination)
    {
        list<GEdge>::iterator it;
        for (it = adjVertices[source].begin(); it != adjVertices[source].end(); it++)
        {
            if ((it -> destination).compare(destination) == 0)
            {
                adjVertices[source].erase(it);
                break;
            }
        }
        if (!isDireted())
        {
            for (it = adjVertices[destination].begin(); it != adjVertices[destination].end(); it++)
            {
                if ((it -> destination).compare(source) == 0)
                {
                    adjVertices[destination].erase(it);
                    break;
                }
            }
        }
    }

    void dump()
    {
        map<string, list<GEdge> >::iterator it;
        for (it = adjVertices.begin(); it != adjVertices.end(); it++)
        {
            cout << "Vertex " << it->first << ": " << endl;
            list<GEdge>::iterator edge;
            for (edge = it->second.begin(); edge != it->second.end(); edge++)
                cout << "   -> To " << edge->destination << (this->isWeightedGraph ? ": " + to_string(edge->weight) : "") << endl;
        }
    }

private:
    class GEdge
    {
    public:
        string destination;
        int weight;
        GEdge(string destination, int weight) : destination(destination), weight(weight) {}
        bool operator==(const GEdge &other) const { return (this->destination == other.destination); }
    };
};

int main()
{
    GraphQ3 *g = new GraphQ3(true, true);
    
    g->addVertex("A");
    g->addVertex("B");
    g->addVertex("C");
    g->addVertex("D");
    
    g->addEdge("A", "B", 15);
    g->addEdge("C", "A", 17);
    g->addEdge("A", "D", 23);
    g->addEdge("A", "C", 16);
    g->addEdge("D", "B", 9);
    
    g->removeEdge("D", "B");
    g->removeEdge("B", "D");
    g->removeEdge("A", "F");
    
    g->dump();
}
