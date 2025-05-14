#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
class SkipList
{
private:
    struct Node
    {
        T value;
        Node* next;
        Node* prev;
        Node* up;
        Node* down;

        Node(T val)
        {
            value = val;
            next = prev = up = down = nullptr;
        }
    };

    vector<Node*> levelHeads;
    int maxLevel;
    float probability;
    int currentLevel;
    int nodeCount;

    int randomLevel()
    {
        int level = 0;
        
        while (((float)rand() / RAND_MAX) < probability && level < maxLevel - 1)
        {
            level++;
        }

        return level;
    }

public:
    SkipList(int maxLevel = 16, float probability = 0.5f)
    {
        this->maxLevel = maxLevel;
        this->probability = probability;
        this->currentLevel = 0;
        this->nodeCount = 0;

        srand((unsigned)time(nullptr));

        levelHeads.resize(maxLevel, nullptr);
        for (int i = 0; i < maxLevel; ++i)
        {
            levelHeads[i] = new Node(T());

            if (i > 0)
            {
                levelHeads[i]->down = levelHeads[i - 1];
                levelHeads[i - 1]->up = levelHeads[i];
            }
        }
    }

    ~SkipList()
    {
        for (int i = maxLevel - 1; i >= 0; --i)
        {
            Node* current = levelHeads[i];

            while (current)
            {
                Node* toDelete = current;
                current = current->next;

                delete toDelete;
            }
        }
    }

    void insert(T value)
    {
        vector<Node*> update(maxLevel, nullptr);

        Node* current = levelHeads[currentLevel];

        for (int i = currentLevel; i >= 0; --i)
        {
            while (current->next && current->next->value < value)
            {
                current = current->next;
            }

            update[i] = current;

            if (i > 0)
            {
                current = current->down;
            }
        }

        int newLevel = randomLevel();
        if (newLevel > currentLevel)
        {
            for (int i = currentLevel + 1; i <= newLevel; ++i)
            {
                update[i] = levelHeads[i];
            }

            currentLevel = newLevel;
        }

        Node* lowerNode = nullptr;

        for (int i = 0; i <= newLevel; ++i)
        {
            Node* newNode = new Node(value);

            newNode->next = update[i]->next;
            newNode->prev = update[i];

            if (update[i]->next)
            {
                update[i]->next->prev = newNode;
            }

            update[i]->next = newNode;

            if (lowerNode)
            {
                newNode->down = lowerNode;
                lowerNode->up = newNode;
            }

            lowerNode = newNode;
        }

        nodeCount++;
    }

    void remove(T value)
    {
        Node* current = levelHeads[currentLevel];

        bool found = false;

        for (int i = currentLevel; i >= 0; --i)
        {
            while (current->next && current->next->value < value)
            {
                current = current->next;
            }

            if (current->next && current->next->value == value)
            {
                Node* toDelete = current->next;
                current->next = toDelete->next;

                if (toDelete->next)
                {
                    toDelete->next->prev = current;
                }

                delete toDelete;

                found = true;
            }

            if (i > 0)
            {
                current = current->down;
            }
        }

        if (found)
        {
            nodeCount--;

            while (currentLevel > 0 && levelHeads[currentLevel]->next == nullptr)
            {
                currentLevel--;
            }
        }
    }

    bool find(T value)
    {
        Node* current = levelHeads[currentLevel];

        for (int i = currentLevel; i >= 0; --i)
        {
            while (current->next && current->next->value < value)
            {
                current = current->next;
            }

            if (current->next && current->next->value == value)
            {
                return true;
            }

            if (i > 0)
            {
                current = current->down;
            }
        }

        return false;
    }

    void print()
    {
        for (int i = currentLevel; i >= 0; --i)
        {
            cout << "Level " << i << ": ";

            Node* current = levelHeads[i]->next;

            while (current)
            {
                cout << current->value;

                if (current->up)
                {
                    cout << "(↑)";
                }
                if (current->down)
                {
                    cout << "(↓)";
                }

                cout << " ";

                current = current->next;
            }

            cout << endl;
        }
    }

    int size()
    {
        return nodeCount;
    }
};