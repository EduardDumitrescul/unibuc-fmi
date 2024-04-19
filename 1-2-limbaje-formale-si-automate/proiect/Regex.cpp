//
// Created by eduarddumitrescul on 4/5/23.
//

#include <stack>
#include <iostream>
#include "Regex.h"

Regex::Regex(std::string exp) {
    this->exp = exp;
}

LambdaNFA Regex::asLambdaNFA() {
    std::string temp = this->toPostfix(exp);
//    std::cout << temp;

    std::vector <LambdaNFA> v;

    for(int i = 0; i < temp.size(); i ++) {
        if(std::isalpha(temp[i])) {
            LambdaNFA lnfa(0, 2);
            lnfa.setFinal(1, true);
            lnfa.addTransition(0, temp[i], 1);
            v.push_back(lnfa);
            continue;
        }
        if(temp[i] == LambdaNFA::LAMBDA) {
            LambdaNFA lnfa(0, 1);
            lnfa.setFinal(0, true);
            v.push_back(lnfa);
            continue;
        }
        if(temp[i] == '*') {
            v[v.size()-1] = v[v.size()-1].multiply();
            continue;
        }
        if(temp[i] == '-') {
            LambdaNFA lnfa = v[v.size()-2].concatenate(v[v.size()-1]);
            v.pop_back();
            v.pop_back();
            v.push_back(lnfa);
            continue;
        }
        if(temp[i] == '+') {
            LambdaNFA lnfa = v[v.size()-2].merge(v[v.size()-1]);
            v.pop_back();
            v.pop_back();
            v.push_back(lnfa);
            continue;
        }
    }
    if(v.size() != 1) {
        std::cout << "Regex::asLambdaNFA error\n";
        return LambdaNFA();
    }
    return v[0];
}

std::string Regex::toPostfix(std::string s) {
    std::string temp = "";
    for(int i = 0; i < s.size(); i ++) {
        if (std::isalpha(s[i]) or s[i] == LambdaNFA::LAMBDA or s[i] == '(') {
            if (!temp.empty() and (temp.back() != '-' and temp.back() != '+' and temp.back() != '(')) {
                temp.push_back('-');
            }
        }
        temp.push_back(s[i]);
    }
    std::stack <char> stack;

    std::string postfix = "";
    for(auto chr: temp) {
        if(std::isalpha(chr) or chr == LambdaNFA::LAMBDA) {
            postfix.push_back(chr);
        }
        else if(chr == '(') {
            stack.push(chr);
        }
        else if(chr == ')') {
            while(stack.top() != '(') {
                postfix.push_back(stack.top());
                stack.pop();
            }
            stack.pop();
        }
        else {
            while(!stack.empty()) {
                if(chr == '-' and (stack.top() == '*' or stack.top() == '-')) {
                    postfix.push_back(stack.top());
                    stack.pop();
                }
                else if(chr == '+' and (stack.top() == '*' or stack.top() == '-' or stack.top() == '+')){
                    postfix.push_back(stack.top());
                    stack.pop();
                }
                break;
            }
            stack.push(chr);
        }
    }
    while(!stack.empty()) {
        postfix.push_back(stack.top());
        stack.pop();
    }
    return postfix;
}
