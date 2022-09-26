#include <iostream>
#include <string>
#include <list>
#include <map>
#include "token.cpp"

using namespace std;

class Scanner 
{
    private:

    
    string source;
    list<Token> tokens;
    int loopError = 0;
    int start = 0;
    int current = 0;
    int line = 1;
    map <string, TokenType> keywords = 
    {
        {"and", AND},
        {"class", CLASS},
        {"else", ELSE},
        {"false", FALSE},
        {"for", FOR},
        {"fun", FUN},
        {"if", IF},
        {"nil", NIL},
        {"or", OR},
        {"print", PRINT},
        {"return", RETURN},
        {"super", SUPER},
        {"this", THIS},
        {"true", TRUE},
        {"var", VAR},
        {"while", WHILE}

    };
    //look ahead - does not consume like advance()
    char peek() 
    {
        if(notEnd())
            return source[current];
        return '\0';
    }

    char peekNext()
    {
        //end of string
        if (source.length() < current + 1) 
            return '\0';

        // if not end -> return char
        return source[current+1];
    }

    bool isAlpha(char ch)
    {
        if (ch >= 'A' && ch <= 'Z') return true;
        if (ch >= 'a' && ch <= 'z') return true;
        if (ch == '_') return true;

        return false;
    }

    bool isDigit(char c){
        if (c >= '0')
        {
            if (c <= '9') return true;
        }

        return false;
    }

    bool notEnd()
    {
        return (current < source.length());
    }

    // consumes next char
    // for input
    char advance()
    {
        //advance current
        int tempCurrent = current;
        current = current + 1;

        return source[tempCurrent];
    }

    // creates token using text of lexeme
    // for output
    void addToken(TokenType ttype)
    {
        addToken(ttype, "");
    }

    // creates token using text of lexeme
    // for output
    void addToken(TokenType ttype, string literal)
    {
        string textInSource = source.substr(start, (current-start));


        //cout << "Text: " << textInSource << endl ;
        //cout << "TokenType: " << enum_str[ttype] << endl;
        //cout << "Start: " << start << endl;
        //cout << "Current: " << current << endl ;


        Token *newToken = new Token(ttype, textInSource, literal, line);
        tokens.push_back(*newToken);
        //cout << "New Token Added:  " << newToken->toString() << endl; 

        //cout << endl << endl;

    }

    void scanToken()
    {
        char ch = advance();

        /// @brief Solving Infinite Looping in function////////
        //if (loopError == 200) exit(1);
        //else loopError ++;
        //////////////////////

        ///@brief Error Checking for input variables ///////////
        //cout << "Source: " << source << endl << "///////////////" 
        //<< endl;
        //cout << "Current before switch:  " << current << endl;
        //////////////////////

        switch (ch) {
        case '(': 
            addToken(LEFT_PAREN); break;
        case ')': 
            addToken(RIGHT_PAREN); break;
        case '{': 
            addToken(LEFT_BRACE); break;
        case '}': 
            addToken(RIGHT_BRACE); break;
        case ',': 
            addToken(COMMA); break;
        case '.': 
            addToken(DOT); break;
        case '-': 
            addToken(MINUS); break;
        case '+': 
            addToken(PLUS); break;
        case ';': 
            addToken(SEMICOLON); break;
        case '*': 
            addToken(STAR); break;
        case '!':
            if (match('='))
                addToken(BANG_EQUAL);
            else 
                addToken(BANG);
            break;
        case '=':
            if (match('='))
                addToken(EQUAL_EQUAL);
            else 
                addToken(EQUAL);
            break;
        case '<':
            if (match('='))
                addToken(LESS_EQUAL);
            else 
                addToken(LESS);
            break;
        case '>':
            if (match('='))
                addToken(GREATER_EQUAL);
            else 
                addToken(GREATER);
            break;
        case '/':
            if (match('/')) {
                // a line of comment
                while(notEnd() && peek() != '\n')
                    advance();
            } 
            else {
                addToken(SLASH);
            }
            break;

        case ' ':
        case '\r':
        case '\t':
            //whitespace
            break;

        case '\n':
            line = line + 1;
            break;

        //STRING
        case '"':
            toString();
            break;

        default:
            if(isDigit(ch))
            {
                number();
            }  
            else if(isAlpha(ch))
            {
                identifier();
            }
            else
            {
                /// @brief Error message handling. Should redirect to lox.error //
                cout << line << ", " << "Unexpected character. " << endl;
            }

            break;
        }
        //cout << "Current after switch:  " << current << endl;
    }

    void identifier() 
    {
        //cout << "Entered Identifier Relm: " << endl;
        //cout << "  ch: " <<source[current] << endl;
        while(isAlpha(peek()) || isDigit(peek()))
        {
            advance();
            //cout << "  ch: " <<source[current] << endl;
        }
            
        
        //once found a non-alphanumeric char execute

        string idf = source.substr(start, (current-start));
        //cout << "identifier: " << "--" << idf << "--" << endl;
        if (keywords.find(idf) != keywords.end())
        {
            auto it = keywords.find(idf);
            TokenType t = it->second;
            addToken(t);
        }
        else
        {
            addToken(IDENTIFIER);
        }


        //auto it = keywords.find(idf);
        //TokenType t = it->second;
        //if(t) addToken(t);
        //else ;
        //addToken(EQUAL);
    }

    void number() 
    {
        while(isDigit(peek()))
        {
            advance();

            if(peek() == '.' && isDigit(peekNext()))
                advance();
        }

        addToken(NUMBER, source.substr(start, (current-start)));

    }

    void toString()
    {
        while(notEnd() && peek()!= '"')
        {
            if (peek() != '\n')
                advance();
            line++;
        }

        if(!notEnd())
        {
            /// @brief Error message handling. Should redirect to lox.error //
            cout << line << ", " << "Unterminated string. " << endl;
            return;
        }

        // consume "'
        advance();
        string val = source.substr(start+1, (current-1-(start+1)));
        addToken(STRING, val);
    }

    bool match(char expectedOperator)
    {
        if(!notEnd())
        {
            return false;
        }
        if(source[current] != expectedOperator)
        {
            return false;
        }

        current = current + 1;
        return true;
    }

    public:

    Scanner(string code)
    {
        source = code;
    }

    list<Token> scanTokens()
    {
        while(notEnd())
        {
            start = current;
            //cout << "///" << source[current] << "///" ;
            scanToken();
        }
        Token *newToken = new Token(TokenEOF, "", "", line);
        tokens.push_back(*newToken);
        
        return tokens;
    }

};