#include<iostream>
#include<string.h>
#include<assert.h>
using namespace std;

class CStack{
public:
    CStack() : head(0) {}

    bool IsEmpty() const { return head == 0;};
    void Push(char a);
    void Pop();

    struct CNode;
    CNode* head;

};

struct CStack::CNode{
    char sk;

    CNode* next;
    CNode(char skob) : sk(skob), next(0) {}
};

void CStack::Push(char a) {
    CNode* newNode = new CNode(a);

    if(head == NULL) {
        head = newNode;
        return;
    }

    newNode->next = head;
    head = newNode;
}


void CStack::Pop() {

    if( head == 0 ){
        cout<<"EMPTY STACK";
        assert(!head);
    }
    CNode* temp = head;
    head = head->next;
    delete temp;

}

bool Is_Bad_Br(char br1, char br2) {
    return ( (br2 == ')' && ( br1 == '[' || br1 == '{' ))
             || (br2 == ']' && ( br1 == '(' || br1 == '{' ))
             || (br2 == '}' && ( br1 == '(' || br1 == '[' )) );
}

bool Is_Open_Br(char br) {
    return ( br == '{' || br == '[' || br == '(' );
}

bool Is_Full_Br(char br1, char br2) {
    return ( (br1 == '(' && br2 == ')') || (br1 == '[' && br2 == ']') || (br1 == '{' && br2 == '}') );
}

bool Is_Close_Br(char br) {
    return( br == ')' || br == ']' || br == '}');
}

char SkobReverse(char sk) {
    switch(sk) {
        case ')': return '(';
        case ']': return '[';
        case '}': return '{';
        case '(': return ')';
        case '[': return ']';
        case '{': return '}';

        default: return 0;
    }
}

int main() {

    char* line;
    cin >> line;
    int line_size=0;
    line_size=strlen(line);

    class CStack StackOpen;
    class CStack StackClose;
    int i = -1;
    for(i = 0; i < line_size; i++) {

        if( Is_Open_Br( line[i] ) ) {
            StackOpen.Push(line[i]);
        }

        if ( Is_Close_Br( line[i] ) ) {

            if(  !StackOpen.IsEmpty() && Is_Bad_Br(StackOpen.head->sk,line[i])) {
                cout << "IMPOSSIBLE";
                return 0;
            }

            if( !StackOpen.IsEmpty() && Is_Full_Br(StackOpen.head->sk, line[i]) ) {
                StackOpen.Pop();
            } else {
                StackClose.Push(line[i]);
            }
        }
    }

    while(StackClose.head != 0) {
        cout << SkobReverse( StackClose.head->sk );
        StackClose.Pop();
    }

    cout << line;

    while(StackOpen.head != 0) {
        cout << SkobReverse( StackOpen.head->sk );
            StackOpen.Pop();
    }
}