#include <iostream>
#include <math.h>
#include "List.h"
using namespace std;

template <class T>
class Stack{
public:
    List<T> lst;
    int size;
    Stack();
    void push(T);
    T pop();
    T peek(int = 0);
    bool is_empty();
    T stack_top();
    void display();
};

template <class T>
Stack<T>::Stack(){
        size = 0;
}
template <class T>
void Stack<T>::push(T data){
    lst.create(data);
    size++;
}
template <class T>
T Stack<T>::pop(){
    T data =  lst.remove();
    size--;
    return data;
}
template <class T>
T Stack<T>::peek(int ind){
    T data = lst.get(ind);
    return data;
}
template <class T>
bool Stack<T>::is_empty(){
    return lst.head ? false: true;
}
template <class T>
T Stack<T>::stack_top(){
    if(!is_empty()){
        return lst.head->data;
    }
    else return -1;
}
template <class T>
void Stack<T>::display(){
    lst.display('\n');
}

class Operator{
public:
    char op;
    char ass;
    int in_precedence;
    int out_precedence;
    Operator(char o = '\0'){
        op = o;
        if(o == '+'||o== '-'){
            ass = 'L';
            in_precedence = 2;
            out_precedence = 1;
        }
        else if(o == '*' || o == '/'){
            ass = 'L';
            in_precedence = 4;
            out_precedence = 3;
        }
        else if(o == '^'){
            ass = 'R';
            in_precedence = 5;
            out_precedence = 6;
        }
        else if(o == '('){
            ass = 'L';
            in_precedence = 0;
            out_precedence = 7;
        }
        else if(o == ')'){
            ass= 'L';
            in_precedence = -2;
            out_precedence = 0;
        }
        else{
            ass = '\0';
            in_precedence = -1;
            out_precedence = -1;
        }
    }
    void assign(char o){
        op = o;
        if(o == '+'||o== '-'){
            ass = 'L';
            in_precedence = 2;
            out_precedence = 1;
        }
        else if(o == '*' || o == '/'){
            ass = 'L';
            in_precedence = 4;
            out_precedence = 3;
        }
        else if(o == '^'){
            ass = 'R';
            in_precedence = 5;
            out_precedence = 6;
        }
        else if(o == '('){
            ass = 'L';
            in_precedence = 0;
            out_precedence = 7;
        }
        else if(o == ')'){
            ass= 'L';
            in_precedence = -2;
            out_precedence = 0;
        }
    }
};
//Precedence and associativity table
class ptable{
public:
    Operator *op;
    int size;
    ptable(){
        char operators[] = {'+', '-','*','/','^' };
        size = sizeof(operators);
        op = new Operator[size];
        for(int i= 0; i < size; ++i){
            op[i].assign(operators[i]);
        }
    }
    Operator get(char c){
        int i= 0;
        for(i = 0; i < size; i++){
            if(op[i].op == c){
                break;
            }
        }
        if(i < size)        return op[i];
        else                return op[size-1];
    }
    float do_airthmatic(float x1, float x2, char o){
        float value=0;
        if(o == op[0].op)      value = x1 + x2;
        else if(o == op[1].op) value = x1 - x2;
        else if(o == op[2].op) value = x1 * x2;
        else if(o == op[3].op) value = x1 / x2;
        else if(o == op[4].op) value = pow(x1,x2);
        return value;
    }
};
class Expression{
    Stack<char> st;   //For the postfix conversion
    Stack<float>  evst;  //For the evaluation
    ptable pt;
public:
    string postfix;
    string exp;
    //Set the expression to semi computer code
    void set(string s){
        exp.clear();
        exp.push_back('(');
        for(int i= 0; s[i] != '\0'; ++i){
            if(s[i] >= '0' && s[i] <= '9'){
                exp.push_back('N');
                exp.push_back(s[i]);
                int j = i+1;
                for(j = i+1; s[j] != '\0'; ++j){
                    if(s[j] >= '0' && s[j] <= '9'){
                        exp.push_back(s[j]);
                    }
                    else if(s[j] == '.'){
                        exp.push_back(s[j]);
                    }
                    else break;
                }
                i = j-1;
                exp.push_back('n');
            }
            else if(s[i] != ' '){
                exp.push_back(s[i]);
            }
        }
        exp.push_back(')');
        convert();
    }
    //Convert to postfix;
    void convert(){
        postfix.clear();
        for(int i= 0; exp[i] != '\0';++i){
            if(exp[i] == 'N'){
                int j = i+1;
                postfix.push_back('N');
                while(exp[j] != 'n' && exp[j] != '\0'){
                    postfix.push_back(exp[j]);
                    j++;
                }
                postfix.push_back('n');
                i = j;
            }
            else if(exp[i] == '('){
                st.push('(');
            }
            else if(exp[i] == ')'){
                while(st.stack_top() != '('){
                    postfix.push_back( st.pop() );
                }
                st.pop();
            }
            else{
                char top = st.stack_top();
                Operator top_op;
                Operator curr = pt.get(exp[i]);
                if(top != '(')     top_op = pt.get(top);
                while(st.stack_top() != '(' && top_op.in_precedence >=  curr.out_precedence){
                    char ope = st.pop();
                    postfix.push_back(ope );
                    if(st.stack_top() == '(')  break;
                    else top_op = pt.get(st.stack_top());
                }
                st.push(exp[i]);
            }
        }
        while(!st.is_empty()){
            char ope = st.pop();
            postfix.push_back(ope);
        }
    }
    float to_num(string num){
        float value = 0;
        float pow = 1;
        int ind = 0;
        while(ind < num.size() && num[ind] != '.'){
            ind++;
        }
        for(int i = ind-1; i >= 0; --i){
            value += (num[i] - '0')*pow;
            pow *= 10;
        }
        pow = 0.1;
        for(int i = ind+1; i < num.size();++i){
            value += (num[i] - '0')*pow;
            pow /= 10;
        }
        return value;
    }
    float evaluate(){
        float value =0;
        for(int i = 0; postfix[i] != '\0'; ++i){
            if(postfix[i] == 'N'){
                int j = i+1;
                string num;
                while(postfix[j] != 'n' && postfix[j] != '\0'){
                    num.push_back(postfix[j]);
                    j++;
                }
                i = j;
                evst.push(to_num(num));
            }
            else{
                float x2 = evst.pop();
                float x1 = evst.pop();
                if(postfix[i] == '/' && x2 == 0){
                    cout<<"Can't divide by zero"<<endl;
                    return -1;
                }

                float result = pt.do_airthmatic(x1,x2,postfix[i]);
                cout<<x1<<" "<<postfix[i]<<" "<<x2<<" : "<<result<<endl;
                evst.push(result);
            }
        }
        value = evst.pop();
        return value;
    }
    string getpostfix(){ return postfix;   }
};
void clearbuffer(){
    while(cin.get() != '\n');
}
int main(){
    Expression e;
    string s;
    char ans = 'n';
    do{

        cout<<"Expression Calculator ( + - * / () ^ ) \n";
        cout<<"Enter the expression: ";
        getline(cin, s);
        e.set(s);
        cout<<"Expression: "<<s<<endl;
        float x = e.evaluate();
        cout<<"The result of the expression is: "<<x<<endl;
        cout<<"Want more ? (Y/N) : ";
        cin>>ans;
        clearbuffer();
    }while(ans == 'y' || ans == 'Y');

    return 0;
}
