#include <bits/stdc++.h> 
using namespace std;

class Runner
{
    int t;
    vector<int> tn;
    vector<vector<string>> twords;  


public:
    void takeInput()
    {
        cin >> t;       
        for (int c = 0; c < t; c++)
        {
           int n;
           cin>>n;
            vector<string> tmp(n);
            for(int i=0;i<n;i++){
                cin>>tmp[i];
            }        

            
            tn.push_back(n);
            twords.push_back(tmp);
            
        }
    }

    void execute()
    {
        

        for (int i = 0; i < t; i++)
        {   
            vector<vector<string>> copytwords = twords;
            vector<vector<int>> ans = countPalindromicPairs(copytwords[i]);           

        }

        
    }

    void executeAndPrintOutput()
    {
        for (int i = 0; i < t; i++)
        {   
            vector<vector<int>> ans = countPalindromicPairs(twords[i] );           
            for(int i=0;i<ans.size();i++){
                for(int j=0;j<ans[0].size();j++){
                    cout<<ans[i][j]<<" ";
                }
                cout<<endl;
            }
        }
        
    }
};

int main()
{
    Runner runner;
    runner.takeInput();
    runner.executeAndPrintOutput();

    return 0;
}

class Node{
public:
    char data;
    int id;
    vector<int> isPalindrome;
    Node* child[26];

    Node(char data){
        this->data = data;
        id = -1;
        for(int i = 0 ; i < 26 ; i++){
            child[i] = NULL;
        }
    }

};

bool isPalindrome(string word , int i , int j){
    while(i < j)
        if(word[i++] != word[j--]) return false;
    
    return true;
}

void insert(Node *root , string word , int word_idx){
    Node *p = root;

    for(int  i = word.size() - 1 ; i >= 0 ; i--){
        //check palindrome
        if(isPalindrome(word, 0, i)){
            p->isPalindrome.push_back(word_idx);
        }
        //trie
        int index = word[i] - 'a';
        if(p->child[index] == NULL){
            Node* new_node = new Node(word[i]);
            p->child[index] = new_node;
        }
        p = p ->child[index];
    }
    p->id = word_idx;
    p->isPalindrome.push_back(word_idx);
}

void find(Node *root , string word , int  word_idx , vector<vector<int>> &ans){
    Node *p = root;

    //2nd case
    for(int  i = 0 ; i < word.size() ; i++){
        if(p->id >= 0 && isPalindrome(word, i, word.size()-1)){
            ans.push_back({word_idx , p->id});
        }
        int index = word[i] - 'a';
        p = p -> child[index];
        if(p == NULL) return;
    }
    //case 2
    for(int idx : p->isPalindrome){
        if(word_idx != idx){
            ans.push_back({word_idx , idx});
        }
    }
}

vector<vector<int>> countPalindromicPairs(vector<string> &words)
{
    vector<vector<int>> ans;
    Node *root = new Node('$');

    for(int i = 0 ; i < words.size() ; i++){
        insert(root , words[i] , i);
    }


    for(int i = 0 ; i < words.size() ; i++){
        find(root , words[i] , i , ans);
    }



    return ans;
}