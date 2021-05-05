#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

void fifo();
void optimal();
void lru();
void pagingClock();
void printVector(vector<string> vect);

int noPages;

int main()
{
    cin >> noPages;
    string method;
    cin >> method;

    if (method == "FIFO")
        fifo();
    else if (method == "OPTIMAL")
        optimal();
    else if (method == "LRU")
        lru();
    else if (method == "CLOCK")
        pagingClock();

    return 0;
}

void fifo()
{
    int oldestPointer = 0;
    int faultCount = 0;
    vector<string> allocatedPages;
    vector<string> pages;
    int input = -999;

    do
    {
        cin >> input;
        string strInput = std::to_string(input);
        // Single digit number
        if (input / 10 == 0 && input != -1)
            pages.push_back("0" + strInput);
        else
            pages.push_back(strInput);
    } while (input != -1);

    pages.resize(pages.size() - 1); // Remove the last -1

    // Printing the output format
    cout << "Replacement Policy = FIFO" << endl;
    cout << "-------------------------------------" << endl;
    cout << "Page   Content of Frames" << endl;
    cout << "----   -----------------" << endl;
    // Push the pages into allocation vector in FIFO manner
    for (int i = 0; i < pages.size(); i++)
    {
        // An empty place exists and new page
        if (allocatedPages.size() < noPages &&
            find(allocatedPages.begin(), allocatedPages.end(), pages[i]) == allocatedPages.end())
        {
            allocatedPages.push_back(pages[i]); // Add a page
            cout << pages[i] << "     ";
            printVector(allocatedPages);
        }
        // The page exists in the allocated pages vector
        else if (find(allocatedPages.begin(), allocatedPages.end(), pages[i]) != allocatedPages.end())
        {
            cout << pages[i] << "     ";
            printVector(allocatedPages);
        }
        // New page and vector is full
        else
        {
            allocatedPages[oldestPointer] = pages[i];   // Replace the oldest page with new page
            oldestPointer++;                            // Increment pointer
            if (oldestPointer == allocatedPages.size()) // Exceeded the vector bounds
                oldestPointer = 0;                      // Reset pointer
            faultCount++;
            cout << pages[i] << " F   ";
            printVector(allocatedPages);
        }
    }
    // Printing output format
    cout << "-------------------------------------" << endl;
    cout << "Number of page faults = " << faultCount;
}

void optimal()
{
    int faultCount = 0;
    vector<string> allocatedPages;
    vector<string> pages;
    int input = -999;

    do
    {
        cin >> input;
        string strInput = std::to_string(input);
        // Single digit number
        if (input / 10 == 0 && input != -1)
            pages.push_back("0" + strInput);
        else
            pages.push_back(strInput);
    } while (input != -1);

    pages.resize(pages.size() - 1); // Remove the last -1

    // Printing the output format
    cout << "Replacement Policy = OPTIMAL" << endl;
    cout << "-------------------------------------" << endl;
    cout << "Page   Content of Frames" << endl;
    cout << "----   -----------------" << endl;
    for (int i = 0; i < pages.size(); i++)
    {
        // An empty place exists and new page
        if (allocatedPages.size() < noPages &&
            find(allocatedPages.begin(), allocatedPages.end(), pages[i]) == allocatedPages.end())
        {
            allocatedPages.push_back(pages[i]); // Add a page
            cout << pages[i] << "     ";
            printVector(allocatedPages);
        }
        // The page exists in the allocated pages vector
        else if (find(allocatedPages.begin(), allocatedPages.end(), pages[i]) != allocatedPages.end())
        {
            cout << pages[i] << "     ";
            printVector(allocatedPages);
        }

        // New page and vector is full (Fault case)
        else
        {
            vector<string>::iterator pgs = pages.begin(); // Iterator for pages vector
            vector<string>::iterator temp;
            int furthestIndex = 0;
            int currentMax = 0;
            int flag = 0;
            advance(pgs, i + 1);
            for (int k = 0; k < allocatedPages.size(); k++)
            {

                // If allocatedPages not found in remaining pages replace it
                if (find(pgs, pages.end(), allocatedPages[k]) == pages.end())
                {
                    allocatedPages[k] = pages[i];
                    faultCount++;
                    cout << pages[i] << " F   ";
                    printVector(allocatedPages);
                    flag = 1;
                    break;
                }
                //
                else
                {
                    temp = find(pgs, pages.end(), allocatedPages[k]);
                    // furthest position smaller than position found by this page
                    if (furthestIndex < temp - pages.begin())
                    {
                        furthestIndex = temp - pages.begin();
                        currentMax = k;
                    }
                }
            }
            if (flag == 0)
            {
                allocatedPages[currentMax] = pages[i];
                faultCount++;
                cout << pages[i] << " F   ";
                printVector(allocatedPages);
            }
        }
    }
    // Printing output format
    cout << "-------------------------------------" << endl;
    cout << "Number of page faults = " << faultCount;
}

void lru()
{
    int faultCount = 0;
    vector<string> allocatedPages;
    vector<string> pages;
    int input = -999;

    do
    {
        cin >> input;
        string strInput = std::to_string(input);
        // Single digit number
        if (input / 10 == 0 && input != -1)
            pages.push_back("0" + strInput);
        else
            pages.push_back(strInput);
    } while (input != -1);

    pages.resize(pages.size() - 1); // Remove the last -1

    // Printing the output format
    cout << "Replacement Policy = LRU" << endl;
    cout << "-------------------------------------" << endl;
    cout << "Page   Content of Frames" << endl;
    cout << "----   -----------------" << endl;
    for (int i = 0; i < pages.size(); i++)
    {
        if (allocatedPages.size() < noPages &&
            find(allocatedPages.begin(), allocatedPages.end(), pages[i]) == allocatedPages.end())
        {
            allocatedPages.push_back(pages[i]); // Add a page
            cout << pages[i] << "     ";
            printVector(allocatedPages);
        }
        // The page exists in the allocated pages vector
        else if (find(allocatedPages.begin(), allocatedPages.end(), pages[i]) != allocatedPages.end())
        {
            cout << pages[i] << "     ";
            printVector(allocatedPages);
        }

        else
        {
            int k;
            int furthestIndex = INT_MAX;
            int replacePage = 0;
            int flag = 0;
            for (int j = 0; j < allocatedPages.size(); j++)
            {
                flag = 0;
                for (k = i - 1; k >= 0; k--)
                {
                    if (pages[k] != allocatedPages[j])
                        continue;
                    else
                    {
                        flag = 1;
                        if (k < furthestIndex)
                        {
                            furthestIndex = k;
                            replacePage = j;
                        }

                        break;
                    }
                }

                if (flag == 0)
                {
                    allocatedPages[j] = pages[i];
                    faultCount++;
                    cout << pages[i] << " F   ";
                    printVector(allocatedPages);
                    break;
                }
            }
            if (flag == 1)
            {
                allocatedPages[replacePage] = pages[i];
                faultCount++;
                cout << pages[i] << " F   ";
                printVector(allocatedPages);
            }
        }
    }

    cout << "-------------------------------------" << endl;
    cout << "Number of page faults = " << faultCount;
}

void pagingClock()
{
    int faultCount = 0;
    int arm = 0;
    vector<string> allocatedPages;
    vector<string> pages;
    bool useBit[noPages];
    int input = -999;

    do
    {
        cin >> input;
        string strInput = std::to_string(input);
        // Single digit number
        if (input / 10 == 0 && input != -1)
            pages.push_back("0" + strInput);
        else
            pages.push_back(strInput);
    } while (input != -1);

    pages.resize(pages.size() - 1); // Remove the last -1

    // Printing the output format
    cout << "Replacement Policy = CLOCK" << endl;
    cout << "-------------------------------------" << endl;
    cout << "Page   Content of Frames" << endl;
    cout << "----   -----------------" << endl;
    for (int i = 0; i < pages.size(); i++)
    {
        auto it = find(allocatedPages.begin(), allocatedPages.end(), pages[i]);
        // An empty place exists and new page
        if (allocatedPages.size() < noPages &&
            find(allocatedPages.begin(), allocatedPages.end(), pages[i]) == allocatedPages.end())
        {
            allocatedPages.push_back(pages[i]); // Add a page
            useBit[i] = true;
            cout << pages[i] << "     ";
            printVector(allocatedPages);
        }
        // The page exists in the allocated pages vector

        else if (it != allocatedPages.end())
        {
            useBit[it - allocatedPages.begin()] = true;
            cout << pages[i] << "     ";
            printVector(allocatedPages);
        }

        // New page and vector is full (Fault case)
        else
        {
            int allPassed = 0; // A flag for the case all of pages were true
            while (allPassed == 0)
            {
                for (int j = 0; j < allocatedPages.size(); j++)
                {
                    if (useBit[arm] == true)
                    {
                        useBit[arm] = false;
                        arm++;
                        if (arm == allocatedPages.size()) // Reset clock arm
                            arm = 0;
                    }
                    else
                    {
                        allocatedPages[arm] = pages[i];
                        useBit[arm] = true;
                        arm++;
                        if (arm == allocatedPages.size()) // Reset clock arm
                            arm = 0;
                        allPassed = 1;
                        break;
                    }
                }
            }

            faultCount++;
            cout << pages[i] << " F   ";
            printVector(allocatedPages);
        }
    }

    cout << "-------------------------------------" << endl;
    cout << "Number of page faults = " << faultCount;
}

void printVector(vector<string> vect)
{
    for (int i = 0; i < vect.size(); i++)
    {
        if (i != vect.size() - 1)
            cout << vect[i] << " ";
        else
            cout << vect[i];
    }
    cout << endl;
}
