#include <cstdio>
#include <stdlib.h>
#include <assert.h>
#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <set>
#include <cstring>

#define pb push_back
#define pop pop_back
#define clr(x, i) memset(x, (i), sizeof(x))
#define FOR(i, s, t) for(int i = (s); i <= (t); i++)
#define ROF(i, t, s) for(int i = (t); i >= (s); i--)
#define pii pair<int, int>
using namespace std;

inline int cmp(vector<char>& lhs, const vector<char>& rhs) {
	return strcmp(&(lhs[0]), &(rhs[0]));
}

inline void cpy(vector<char>& dest, const vector<char>& src) {
	dest.clear();
	int sz = src.size();
	FOR(i, 0, sz - 1) dest.pb(src[i]);
}

inline set<int> cmb(set<int> lhs, set<int> rhs) {
	set<int> dest = lhs;
	for (set<int>::iterator it = rhs.begin(); it != rhs.end(); it++) dest.insert(*it);
	return dest;
}

inline string numToString(int num) {
	if (!num) return string("0");
	vector<char> digits;
	bool neg = false;
	if (num < 0) neg = true, num = -num;
	while (num) {
		digits.pb(num % 10 + '0');
		num /= 10;
	}
	string ret = string("");
	if (neg) ret.append("-");
	int sz = digits.size() - 1;
	char str[2];
	str[1] = '\0';
	ROF(i, sz, 0) str[0] = digits[i], ret.append(str);
	return ret;
}

inline string charToString(char ch) {
	char x[2];
	x[0] = ch, x[1] = '\0';
	return string(x);
}

const static int codeBaseAddress = 0x00400000;
const static int dataBaseAddress = 0x10010000;

#define mp make_pair
const int maxSourceCodeLength = 1e5;
const int maxNumberLength = 7;
char sourceCode[maxSourceCodeLength + 10];
int sourceCodeLength;
const int maxArraySize = 7e5;

int lineNumber;
int cursorIndex;

#define PLUS 0							//'+'
#define MINUS 1							//'-'
#define STAR 2							//'*'
#define SLASH 3							//'/'
#define LESS 4							//'<'
#define LESS_EQUAL 5					//'<='
#define GREATER 6						//'>'
#define GREATER_EQUAL 7					//'>='
#define NOT_EQUAL 8						//'!='
#define EQUAL 9							//'=='
#define CHARACTER 10					//constant char content
#define UNSIGNED_NUMBER 11				//constant unsigned number
#define CONST 12						//'const'
#define INT 13							//'int'
#define CHAR 14							//'char'
#define VOID 15							//'void'
#define IF 16							//'if'
#define WHILE 17						//'while'
#define SWITCH 18						//'switch'
#define CASE 19							//'case'
#define DEFAULT 20						//'default'
#define RETURN 21						//'return'
#define STRING 22						//constant string content
#define IDENTIFIER 23					//identifier(not reserved)
#define LEFT_PARENTHESIS  24			//'('
#define RIGHT_PARENTHESIS 25			//')'
#define LEFT_SQUARE_BRACKET 26			//'['
#define RIGHT_SQUARE_BRACKET 27			//']'
#define LEFT_BRACKET 28					//'{'
#define RIGHT_BRACKET 29				//'}'
#define SEMI_COLON 30					//';'
#define COLON 31						//':'
#define COMMA 32						//','
#define SINGLE_QUOTE 33					//'\''
#define DOUBLE_QUOTE 34					//'\"'
#define ASSIGN 35						//'='
#define MAIN 36							//'main'
#define SCANF 37						//'scanf'
#define PRINTF 38						//'printf'
#define INVALID 39						//word is invalid
//if word to fecth is illegal, set typeCode to INVALID


//-------------ANXULARY SYMBOLS(NOT TO BE USED IN SYNTAX ANALYSIS)-----------------
#define CONSTANT 40						//mod :: constant
#define VARIABLE 41						//mod :: variable
#define FUNCTION 42						//mod :: function
#define VOID_TYPE 43					//void
#define INT_TYPE 44						//int
#define CHAR_TYPE 45					//char
//-------------ANXULARY SYMBOLS----------------------------------------------------


//------------ERROR CODE BEGIN-------------------
#define CHARACTER_ILLEGAL 100
#define PROGRAM_INCOMPLETE 101
#define LEADING_ZERO 102
#define INTEGER_OUT_OF_RANGE 103
#define IDENTIFIER_OUT_OF_LENGTH 104
#define ILLEGAL_CHARACTER_IN_STRING 105
#define MISS_RIGHT_DOUBLE_QUOTE 106
#define MISS_RIGHT_SINGLE_QUOTE 107
#define ILLEGAL_CHARACTER_IN_CONSTANT_CHAR 108
#define CONSTANT_CHAR_OUT_OF_LENGTH 109
#define INT_CHAR_EXPECTED 110
#define IDENTIFIER_EXPECTED 111
#define IDENTIFIER_DUPLICATE_DECLARE 112
#define EQUAL_EXPECTED 113
#define CHAR_EXPECTED 114
#define INT_EXPECTED 115
#define COMMA_OR_SEMI_COLON_EXPECTED 117
#define UNSIGNED_NUMBER_EXPECTED 118
#define ARRAY_SIZE_ZERO 119
#define ARRAY_SIZE_OUT_RANGE 120
#define RIGHT_SQUARE_BRACKET_EXPECTED 121
#define UNEXPECTED_SYMBOL 122
#define IDENTIFIER_UNDECLARED 123
#define LEFT_SQUARE_BRACKET_EXPECTED 124
#define ARRAY_NOT_DECLARED 125
#define VOID_FUNCTION_UNEXPECTED 126
#define RIGHT_PARENTHESIS_EXPECTED 127
#define TOO_MANY_FORMAL_PARA 128
#define TOO_FEW_FORMAL_PARA 129
#define LEFT_PARENTHESIS_EXPECTED 130
#define COMMA_EXPECTED 131
#define SEMI_COLON_EXPECTED 132
#define ASSIGN_EXPECTED 133
#define MAIN_EXPECTED 134
#define ARRAY_SIZE_TOO_SMALL 135
#define ARRAY_SIZE_TOO_LARGE 136
#define UNEXPECTED_MAIN_TYPE 137
#define UNEXPECTED_MAIN_PARA 138
#define RIGHT_BRACKET_EXPECTED 139
#define LEFT_BRACKET_EXPECTED 140
#define DEFAULT_EXPECTED 141
#define CASE_EXPECTED 142
#define CASE_DUPLICATE 143
#define COLON_EXPECTED 144
#define ASSIGN_TO_ARRAY 145
#define SELECT_NON_ARRAY 146
#define MAIN_CALLED 147
#define RETURN_IN_VOID 148
#define WRONG_SCANF_FORMAT 149
//------------ERROR CODE END---------------------

//-------------intermediate code begin------------------------
#define ADD 1001
#define SUB 1002
#define MUL 1003
#define DIV 1004
#define MUS 1005
#define ASTO 1006
#define ALOD 1007
#define ASG 1008
#define JMP 1009
#define JPC 1010
#define WRITE 1011
#define READ 1012
#define ARG 1013
#define RETA 1014
#define RETV 1015
#define EXF 1016
#define SLOD 1017
#define CLOD 1018
#define CAS 1019
#define EQL 1020
#define NEQ 1021
#define GRT 1022
#define GEQ 1023
#define LES 1024
#define LEQ 1025
#define READC 1026
#define WRITEC 1027
#define WRITES 1028
#define FRET 1029
#define JAL 1030
#define CAL 1031
//------------------------------------------------------------

void getWord();
void mExp(set<int> termiateToken);
void mCallStatement(set<int> terminateToken, int index);
void mFunctBlock(set<int> terminateToken, int type, int index, bool isMain);
void mParaList(set<int> terminateToken, int index, bool isMain);
void mStatementSeq(set<int> terminateToken, int index);
void mIfStatement(int functionIndex);
void mWhileStatement(int fidx);
void mSwitchStatement(set<int> terminateToken, int idx);
void mPrintfStatement(set<int> terminateToken);
void mScanfStatement(set<int> terminateToken);
void mReturnStatement(set<int> termianteToken, int fidx);
void mAssignStatement(set<int> terminateToken, int idx);
pii mConstant(set<int> termiateToken);
//------------------------------------------------------------
set<int> factorBeginSymbols = { IDENTIFIER, LEFT_PARENTHESIS, CHARACTER, PLUS, MINUS, UNSIGNED_NUMBER };
set<int> statementBeginSymbols = { IDENTIFIER, IF, WHILE, LEFT_BRACKET, PRINTF, SCANF, SEMI_COLON, SWITCH, RETURN };
//-----------------------------------------------------------
char wordDescriptionList[][30] = {
	"PLUS", "MINUS", "STAR", "SLASH", "LESS", "LESS_EQUAL", "GREATER", "GREATER_EQUAL", "NOT_EQUAL", "EQUAL",
	"CHARACTER", "UNSIGNED_NUMBER", "CONST", "INT", "CHAR", "VOID", "IF", "WHILE", "SWITCH", "CASE", "DEFAULT",
	"RETURN", "STRING", "IDENTIFIER", "LEFT_PARENTHESIS", "RIGHT_PARENTHESIS", "LEFT_SQUARE_BRACKET",
	"RIGHT_SQUARE_BRACKET", "LEFT_BRACKET", "RIGHT_BRACKET", "SEMI_COLON", "COLON", "COMMA", "SINGLE_QUOTE",
	"DOUBLE_QUOTE", "ASSIGN", "MAIN", "SCANF", "PRINTF"
};

struct Word {
	//remember :: call reset before you overwrite
	int type;
	vector<char> wordString;
	int wordValue;
	string oldname = string("");

	void reset() {
		if (wordString.size()) oldname = string(&(wordString[0]));
		type = INVALID;
		wordString.clear();
		//wordString.pb('\0');
		wordValue = 0;
	}
	//-----------------------------------------------
	void convertStringToValue() {
		//precondition :: wordString stores numeric value within range
		//no leading zeros
		//wordValue <-- wordString[]
		wordValue = 0;
		int p = 0, sz = wordString.size();
		while (p < sz - 1) {
			wordValue = wordValue * 10 + (wordString[p] - '0');
			p++;
		}
	}
}word;

struct Error {
	map<int, string> errorMap;
	int errorCounter;
	Error() {
		errorCounter = 0;
		errorMap.clear();
		errorMap[CHARACTER_ILLEGAL] = string("character is illegal in this context");
		errorMap[PROGRAM_INCOMPLETE] = string("program is incomplete");
		errorMap[LEADING_ZERO] = string("leading zeors is not allowed in this context");
		errorMap[INTEGER_OUT_OF_RANGE] = string("integer value is out of range");
		errorMap[IDENTIFIER_OUT_OF_LENGTH] = string("identifier length is too large");
		errorMap[ILLEGAL_CHARACTER_IN_STRING] = string("character is illegal in string context");
		errorMap[MISS_RIGHT_DOUBLE_QUOTE] = string("character '\"' expected");
		errorMap[MISS_RIGHT_SINGLE_QUOTE] = string("character '\'' expected");
		errorMap[ILLEGAL_CHARACTER_IN_CONSTANT_CHAR] = string("character is illegal in constant char");
		errorMap[CONSTANT_CHAR_OUT_OF_LENGTH] = string("constant char should contain only one character");
		errorMap[INT_CHAR_EXPECTED] = string("type 'int' or 'char' expected");
		errorMap[IDENTIFIER_EXPECTED] = string("");
		errorMap[IDENTIFIER_DUPLICATE_DECLARE] = string("indentifier already declared");
		errorMap[EQUAL_EXPECTED] = string("'==' expected");
		errorMap[CHAR_EXPECTED] = string("'char' expected");
		errorMap[INT_EXPECTED] = string("'int' expected");
		errorMap[COMMA_OR_SEMI_COLON_EXPECTED] = string("',' or ';' expected");
		errorMap[UNSIGNED_NUMBER_EXPECTED] = string("unsigned number expected");
		errorMap[ARRAY_SIZE_ZERO] = string("array size cannot be 0");
		errorMap[ARRAY_SIZE_OUT_RANGE] = string("array size is out of range");
		errorMap[RIGHT_SQUARE_BRACKET_EXPECTED] = string("']' expected");
		errorMap[UNEXPECTED_SYMBOL] = string("unexpected symbol");
		errorMap[IDENTIFIER_UNDECLARED] = string("indentifier was not declared");
		errorMap[LEFT_SQUARE_BRACKET_EXPECTED] = string("'[' expected");
		errorMap[ARRAY_NOT_DECLARED] = string("array is not declared");
		errorMap[VOID_FUNCTION_UNEXPECTED] = string("void function unexpected, should have a return value");
		errorMap[RIGHT_PARENTHESIS_EXPECTED] = string("')' expected");
		errorMap[TOO_MANY_FORMAL_PARA] = string("too many formal parameters");
		errorMap[TOO_FEW_FORMAL_PARA] = string("too few formal parameters");
		errorMap[LEFT_PARENTHESIS_EXPECTED] = string("'(' expected");
		errorMap[COMMA_EXPECTED] = string("',' expected");
		errorMap[SEMI_COLON_EXPECTED] = string("';' expected");
		errorMap[ASSIGN_EXPECTED] = string("'=' expected");
		errorMap[MAIN_EXPECTED] = string("'main' expected");
		errorMap[ARRAY_SIZE_TOO_SMALL] = string("array size is too small");
		errorMap[ARRAY_SIZE_TOO_LARGE] = string("array size is too large");
		errorMap[UNEXPECTED_MAIN_TYPE] = string("function 'main' should have type 'void'");
		errorMap[UNEXPECTED_MAIN_PARA] = string("function 'main' should have no parameters");
		errorMap[RIGHT_BRACKET_EXPECTED] = string("'}' expected");
		errorMap[LEFT_BRACKET_EXPECTED] = string("'{' expected");
		errorMap[DEFAULT_EXPECTED] = string("'default' expected");
		errorMap[CASE_EXPECTED] = string("'case' expected");
		errorMap[CASE_DUPLICATE] = string("case value duplicate");
		errorMap[COLON_EXPECTED] = string("':' expected");
		errorMap[ASSIGN_TO_ARRAY] = string("try to assign value to array type");
		errorMap[SELECT_NON_ARRAY] = string("non-array type variable cannot use subscript address");
		errorMap[MAIN_CALLED] = string("function 'main' should not be called");
		errorMap[RETURN_IN_VOID] = string("cannot return a value in function of type 'void'");
		errorMap[WRONG_SCANF_FORMAT] = string("scanf only accept parameter variable of type 'int' or 'char'");
	}
	void invoke(int lineno, int cursorindex, int errorcode) {
		errorCounter++;
		string errword = word.wordString.size() ? string(&(word.wordString[0])) : word.oldname;
		//string errKeyword = word.wordString.size() ? string(&(word.wordString[0])) : string("");
		cout << "error at LineNumber: " << lineno << ", Column: " << cursorindex << ", when try to resolve word \""
			<< errword << "\"" << endl;
		if (errorMap.find(errorcode) == errorMap.end()) {
			cout << "undefined error" << endl;
		} else {
			cout << errorMap[errorcode] << endl;
		}
	}
}error;

set<int> blockSpliter = set<int>{SEMI_COLON, RIGHT_BRACKET, INT, CHAR, CONST, VOID, WHILE, SWITCH, CASE, DEFAULT, LEFT_BRACKET};
void verify(const set<int> &src, Word &word, int errcode) {
	if (src.find(word.type) == src.end()) {
		error.invoke(lineNumber, cursorIndex, errcode);
		set<int> dest = cmb(blockSpliter, src);
		while (dest.find(word.type) == dest.end()) getWord();
	}
}

struct SingleSpliterDict {
	pair<int, int> spliters[20] = { mp('+', PLUS), mp('-', MINUS), mp('*', STAR), mp('/', SLASH), mp('<', LESS),
		mp('>', GREATER), mp('=', ASSIGN), mp(':', COLON), mp(';', SEMI_COLON), mp(',', COMMA), mp('(', LEFT_PARENTHESIS),
		mp(')', RIGHT_PARENTHESIS), mp('[', LEFT_SQUARE_BRACKET), mp(']', RIGHT_SQUARE_BRACKET), mp('{', LEFT_BRACKET),
		mp('}', RIGHT_BRACKET)
	};
	int spliterNum = 16;
	SingleSpliterDict() {
		sort(spliters, spliters + spliterNum);
	}
	int getSingleSpliterCode(char ch) {
		int l = 0, r = spliterNum;
		while (r - l > 1) {
			int mid = (l + r) >> 1;
			if (spliters[mid].first > ch) r = mid;
			else l = mid;
		}
		if (spliters[l].first != ch) return -1;
		return spliters[l].second;
	}
}spliterDict;

struct IntermediateCode {

	map<int, string> codeToString;
	struct codeItem {
		int opCode;
		string operand1 = "", operand2 = "", operand3 = "";
		int operandNum = 0;
		codeItem(int _opCode, int num) {
			opCode = _opCode;
			operandNum = num;
		}
		codeItem(int _opCode, string _operand1, int num) {
			opCode = _opCode, operand1 = _operand1;
			operandNum = num;
		}

		codeItem(int _opCode, string _operand1, string _operand2, int num) {
			opCode = _opCode, operand1 = _operand1, operand2 = _operand2;
			operandNum = num;
		}
		codeItem(int _opCode, string _operand1, string _operand2, string _operand3, int num) {
			opCode = _opCode, operand1 = _operand1, operand2 = _operand2, operand3 = _operand3;
			operandNum = num;
		}
	};
	vector<codeItem> code;

	int emit(int opCode) {
		//return IC index
		code.pb(codeItem(opCode, 0));
		//cout << codeToString[opCode] << endl;
		return code.size() - 1;
	}

	void flush() {
		int sz = code.size();
		FOR(i, 0, sz - 1) {
			int num = code[i].operandNum;
			cout << codeToString[code[i].opCode];
			if (num > 0) cout << " " << code[i].operand1;
			if (num > 1) cout << " " << code[i].operand2;
			if (num > 2) cout << " " << code[i].operand3;
			cout << endl;
		}
	}

	int emit(int opCode, string operand1) {
		code.pb(codeItem(opCode, operand1, 1));
		return code.size() - 1;
	}
	int emit(int opCode, string operand1, string operand2) {
		code.pb(codeItem(opCode, operand1, operand2, 2));
		return code.size() - 1;
	}

	int emit(int opCode, string operand1, string operand2, string operand3) {
		code.pb(codeItem(opCode, operand1, operand2, operand3, 3));
		return code.size() - 1;
	}

	vector<pii> tempOperandStack;
	int nextAllocatable = 0;
	int getNextAllocatable();

	string getTempStringByIdx(int idx) {
		return string("$T").append(numToString(idx));
	}


	IntermediateCode() {
		code.clear();
		codeToString.clear();
		tempOperandStack.clear();
		codeToString[ADD] = string("ADD"); codeToString[SUB] = string("SUB"); codeToString[MUL] = string("MUL");
		codeToString[DIV] = string("DIV"); codeToString[MUS] = string("MUS"); codeToString[ASTO] = string("ASTO");
		codeToString[ALOD] = string("ALOD"); codeToString[ASG] = string("ASG"); codeToString[JMP] = string("JMP");
		codeToString[JPC] = string("JPC"); codeToString[WRITE] = string("WRITE"); codeToString[READ] = string("READ");
		codeToString[ARG] = string("ARG"); codeToString[RETA] = string("RETA"); codeToString[RETV] = string("RETV");
		codeToString[EXF] = string("EXF"); codeToString[SLOD] = string("SLOD"); codeToString[CLOD] = string("CLOD");
		codeToString[CAS] = string("CAS"); codeToString[EQL] = string("EQL"); codeToString[NEQ] = string("NEQ");
		codeToString[GRT] = string("GRT"); codeToString[GEQ] = string("GEQ"); codeToString[LES] = string("LES");
		codeToString[LEQ] = string("LEQ"); codeToString[READC] = string("READC"); codeToString[WRITEC] = string("WRITEC");
		codeToString[WRITES] = string("WRITES"); codeToString[FRET] = string("FRET"); codeToString[JAL] = string("JAL");
		codeToString[CAL] = string("CAL");
	}

	int getNextCodeAddress() {
		return code.size();
		//invalibale, though
	}

	int mIdxFromTempRegString(string src) {
		//template "$T..."
		int len = src.length();
		int v = 0;
		FOR(i, 2, len - 1) v = 10 * v + (src.at(i) - '0');
		return v;
	}
	//note if you're to execute code whose idx > code.size(), you must stop
	//(for there is no more code to excute, you reach the end)
}mCode;

struct ReservedWordsDict {
	struct reservedKeyWord {
		char nameString[20];
		int code;
		reservedKeyWord(const char* src, int codeValue) {
			memcpy(nameString, src, strlen(src) + 1);
			code = codeValue;
		}
		reservedKeyWord() {}
		bool operator < (const struct reservedKeyWord &rhs) const {
			return strcmp(nameString, rhs.nameString) < 0;
		}
	};

	reservedKeyWord keyWords[20] = { reservedKeyWord("const", CONST), reservedKeyWord("int", INT),
		reservedKeyWord("char", CHAR), reservedKeyWord("void", VOID), reservedKeyWord("if", IF),
		reservedKeyWord("while", WHILE), reservedKeyWord("switch", SWITCH), reservedKeyWord("case", CASE),
		reservedKeyWord("default", DEFAULT), reservedKeyWord("return", RETURN), reservedKeyWord("main", MAIN),
		reservedKeyWord("printf", PRINTF), reservedKeyWord("scanf", SCANF)
	};

	int keyWordsNum = 13;

	ReservedWordsDict() {
		sort(keyWords, keyWords + keyWordsNum);
	}

	int getReservedWordCodeIndex(char *src) {
		//note: if src[] is a reserved word, return its codeIndex in macro, otherwise return -1
		int p = lower_bound(keyWords, keyWords + keyWordsNum, reservedKeyWord(src, 0)) - keyWords;
		if (strcmp(keyWords[p].nameString, src)) return -1;
		return keyWords[p].code;
	}

}reservedWordsDict;


struct SymbolTable {
	int spaceAllocatableTop = 0;
	int curFunctionIdexInTable = 0;
	int globalDataInTableTop = 0;//(0, glo...]
	const static int maxHashTableSize = 1e5;
	int hashTable[maxHashTableSize];

	set<string> globalDataNameSpace;
	struct TableItem {
		vector<char> name;
		int address = 0;
		//case variable(parameter included) :: address allocated in call stack
		//case function :: object code entrance address
		//case constant integer :: integer value
		//case constant character :: ascii code
		int ref = 0;
		//case array variable :: address of array in arrayTable
		//case function :: address of function in branchTable
		//default :: zero
		int type;//int/char/void
		int modifier;//constant/variable/function
		int link = 0;
		bool isArray = false;
		//head
		TableItem() {
			name.clear();
			name.pb('\0');
		}
		TableItem(int typeCode) {
			name.clear();
			name.pb('\0');
			type = typeCode;
		}
		TableItem(Word &word, int _link) {
			name.clear();
			name.pb('\0');
			link = _link;
			cpy(name, word.wordString);
			//note :: address and referece are not set
		}
	};
	vector<TableItem> table;

	TableItem& getTableItem(int __idx) {
		if (__idx >= 0 && __idx < table.size()) return table[__idx];
		return TableItem();
	}

	struct SymTableList {
		struct SymTableRecord {
			vector<TableItem> tableItems;
			SymTableRecord() {
				tableItems.clear();
			}
			string functName;
			int branchIndex = 0;
			int mCodeBegin = 0;
		}symTableRecord;
		vector<SymTableRecord> records;
		SymTableList() {
			records.clear();
		}
		int newSymTableRecord() {
			SymTableRecord __newSymTableRecord;
			int idx = records.size();
			records.pb(__newSymTableRecord);
			return idx;
		}
	}symTableList;

	void exitBlockPopTable(int functionIdxInTable) {
		//global items in (0, glbDataInTableTop]
		int curSize = table.size() - globalDataInTableTop - 1;
		int newRecordIdx = symTableList.newSymTableRecord();
		symTableList.records[newRecordIdx].tableItems.clear();
		symTableList.records[newRecordIdx].tableItems.resize(curSize);
		symTableList.records[newRecordIdx].branchIndex = table[functionIdxInTable].ref;
		symTableList.records[newRecordIdx].functName = string(&(table[functionIdxInTable].name[0]));
		symTableList.records[newRecordIdx].mCodeBegin = branchTable[table[functionIdxInTable].ref].mCodeBegin;

		while (table.size() - 1 > globalDataInTableTop) {
			int cur = table.size() - 1;
			symTableList.records[newRecordIdx].tableItems[cur - globalDataInTableTop - 1] = table[cur];
			//record[cur - globalDataInTableTop - 1] = table[cur];
			int &idx = hashTable[hash(&(table[cur].name[0]))];
			int nex = table[idx].link;
			idx = nex;
			table.pop();
		}
	}

	/*************************************************************************/
	struct ArrayTableItem {
		int type = INVALID;
		int length;
		ArrayTableItem() {
			type = INVALID;
			length = 0;
		}
	};

	vector<ArrayTableItem> arrayTable;

	int getLengthInArrayTable(int __idx) {
		if (__idx >= 0 && __idx < arrayTable.size()) return arrayTable[__idx].length;
		return 0;
	}

	ArrayTableItem& getArrayTableItem(int __idx) {
		if (__idx >= 0 && __idx < arrayTable.size()) return arrayTable[__idx];
		return ArrayTableItem();
	}

	int newArrayTableItem() {
		int sz = arrayTable.size();
		arrayTable.pb(ArrayTableItem());
		return sz;
	}

	/*************************************************************************/
	struct BranchTableItem {
		vector<int> paraTypeList;
		int size;
		int mCodeBegin;
		int maxCallParaNum = -1;
		int leftMostReg = 0x3f3f3f3f, rightMostReg = -0x3f3f3f3f;
		//consider local data
		//pair<string::name, int::size of data(bytes)
		//vector<pair<string, int> > localData;
		BranchTableItem() {
			size = 0;
			mCodeBegin = 0;
			paraTypeList.clear();
			//localData.clear();
		}
		//size of local variables parameters and privateSize occupoed in stack S
	};
	vector<BranchTableItem> branchTable;

	BranchTableItem& getBranchItem(int __idx) {
		if (__idx >= 0 && __idx < branchTable.size()) return branchTable[__idx];
		return BranchTableItem();
	}

	int newBranchTableItem() {
		int sz = branchTable.size();
		branchTable.pb(BranchTableItem());
		return sz;
	}
	/*************************************************************************/
	struct ConstantValueTableItem {
		int value;
		ConstantValueTableItem() {
			value = 0;
		}
	};

	vector<ConstantValueTableItem> constantValueTable;

	ConstantValueTableItem& getConstantValue(int __idx) {
		if (__idx >= 0 && __idx < constantValueTable.size()) return constantValueTable[__idx];
		return ConstantValueTableItem();
	}

	int newConstantValueTableItem() {
		int sz = constantValueTable.size();
		constantValueTable.pb(ConstantValueTableItem());
		return sz;
	}
	/*************************************************************************/
	struct CaseTableItem {
		int value;
		int address;
		int codeIndex;
		CaseTableItem(int _value, int _address) {
			value = _value;
			address = _address;
		}
	};
	struct CaseTable {
		vector<CaseTableItem> caseTable;
		CaseTable() {
			caseTable.clear();
		}
		bool checkDuplicate(int value) {
			int sz = caseTable.size();
			FOR(i, 0, sz - 1) if (caseTable[i].value == value) return true;
			return false;
		}
		int pushCaseItem(int value, int address) {
			caseTable.pb(CaseTableItem(value, address));
			return caseTable.size() - 1;
		}

		void emitCaseCode(int srcIdx) {
			int sz = caseTable.size();
			FOR(i, 0, sz - 1) {
				mCode.emit(CAS, numToString(caseTable[i].address), mCode.getTempStringByIdx(srcIdx), numToString(caseTable[i].value));
			}
		}

		void fillExitAddress(int exitAddress) {
			int sz = caseTable.size();
			FOR(i, 0, sz - 1) {
				int idx = caseTable[i].codeIndex;
				mCode.code[idx].operand1 = numToString(exitAddress);
			}
		}
	};

	vector<CaseTable> caseTableList;

	CaseTable& newCaseTable() {
		caseTableList.pb(CaseTable());
		return caseTableList[caseTableList.size() - 1];
	}

	/*************************************************************************/
	SymbolTable() {
		table.clear();
		arrayTable.clear();
		branchTable.clear();
		stringTable.clear();
		clr(hashTable, 0);
		table.pb(TableItem(INVALID));
		arrayTable.pb(ArrayTableItem());
		//item in position 0 is always invalid
	}

	unsigned int hash(char * src) {
		//DJBHash
		unsigned long hash = 5381;
		int c;
		while (c = *src++) hash = ((hash << 5) + hash) + c;
		return hash % maxHashTableSize;
	}

	int checkDuplicate() {
		int idx = hashTable[hash(&(word.wordString[0]))];
		while (idx && cmp(table[idx].name, word.wordString)) idx = table[idx].link;
		return idx;
	}

	int pushItem(Word& word, bool inGlobal) {
		int preIdx = checkDuplicate();
		if (preIdx && (preIdx > globalDataInTableTop || inGlobal)) {
			error.invoke(lineNumber, cursorIndex, IDENTIFIER_DUPLICATE_DECLARE);
			return 0;
		} else {
			if (inGlobal) globalDataNameSpace.insert(string(&(word.wordString[0])));
			int top = table.size();
			int idx = hash(&(word.wordString[0]));
			int nex = hashTable[idx];
			hashTable[idx] = top;
			table.pb(TableItem(word, nex));
			if (inGlobal) ++globalDataInTableTop;
			return top;
		}
	}

	int getIndexFromWord(Word &word) {
		int idx = hashTable[hash(&(word.wordString[0]))];
		while (idx && cmp(table[idx].name, word.wordString)) idx = table[idx].link;
		if (!idx) error.invoke(lineNumber, cursorIndex, IDENTIFIER_UNDECLARED);
		return idx;
	}

	vector<string> stringTable;
	int pushNewString(Word word) {
		int sz = stringTable.size();
		stringTable.pb(string(&(word.wordString[0])));
		return sz;
	}

	int getGlobalDataTypeByName(string name) {
		int sz = globalDataInTableTop;
		FOR(i, 1, sz) if (name == string(&(table[i].name[0]))) return table[i].type;
		return -1;//not found
	}

}symbolTable;


int IntermediateCode::getNextAllocatable() {
	SymbolTable::BranchTableItem &bitem = symbolTable.branchTable[
		symbolTable.table[symbolTable.curFunctionIdexInTable].ref];
	bitem.leftMostReg = min(nextAllocatable, bitem.leftMostReg);
	bitem.rightMostReg = max(nextAllocatable, bitem.rightMostReg);
	return nextAllocatable++;
}

struct ObjectCode {

	int labelTop = 0;

	void dataSegPrepare() {
		cout << ".data" << endl;
	}

	void textSegPrepare() {
		cout << ".text" << endl;
		cout << "j main" << endl;
	}

	map<int, string> stringMap;
	map<string, int> paraMap;

	string pushString(int index) {
		//a proper label for the string will be returned
		string label = string("$S").append(numToString(index));
		stringMap[index] = label;
		cout << label << ": " << ".asciiz " << "\"" << symbolTable.stringTable[index] << "\"" << endl;
		return label;
	}

	struct LocalDataItem {
		string name = "";
		int idxInTab = 0;
		int realativeAddress = 0;
		int sizeAllocated = 0;//bytes
		LocalDataItem() {}
	};

	int convertStringToInt(string numString) {
		//possibly negative
		bool neg = false;
		int len = numString.length();
		int bg = 0;
		if (numString.at(bg) == '-') neg = true, ++bg;
		int v = 0;
		while (bg < len) {
			v = v * 10 + (numString.at(bg) - '0');
			++bg;
		}
		if (neg) v = -v;
		return v;
	}

	int getLocalVarAddress(vector<LocalDataItem> &localData, string name) {
		int sz = localData.size();
		FOR(i, 0, sz - 1) if (localData[i].name == name) {
			return localData[i].realativeAddress;
		}
		return -1;
	}

	int getLocalOrGlobalorParaVarType(vector<LocalDataItem> &localData, string name,
		SymbolTable::SymTableList::SymTableRecord& record) {
		vector<SymbolTable::TableItem> &tb = record.tableItems;
		int paraNum = symbolTable.branchTable[record.branchIndex].paraTypeList.size();
		FOR(i, 0, paraNum - 1) if (string(&(tb[i].name[0])) == name) return tb[i].type;
		int sz = localData.size();
		FOR(i, 0, sz - 1) if (localData[i].name == name) {
			return  record.tableItems[localData[i].idxInTab].type;
		}
		//find global otherwise
		int gtp = symbolTable.getGlobalDataTypeByName(name);
		if (gtp != -1) return gtp;
		return INVALID;
	}

	void genObjCode() {
		//input :: intermediate code & symbolTable
		//output :: MIPS assembly code
		dataSegPrepare();
		vector<string> &sv = symbolTable.stringTable;
		int sz = sv.size();
		stringMap.clear();
		FOR(i, 0, sz - 1) pushString(i);
		sz = symbolTable.table.size();
		map<string, string> globalDataNameAffine;
		globalDataNameAffine.clear();
		FOR(i, 1, sz - 1) {
			int type = symbolTable.table[i].type;
			int modifier = symbolTable.table[i].modifier;
			if (type != CHAR && type != INT || modifier != VARIABLE) continue;
			if (type == INT) cout << ".align 2" << endl;//padding to a word length
			string label = string(type == INT ? "$I" : "$C").append(numToString(labelTop++));
			int len = 1;
			if (symbolTable.table[i].isArray) {
				len = symbolTable.getLengthInArrayTable(symbolTable.table[i].ref);
				if (type == INT) len *= 4;
				cout << label << ": " << ".space " << len << endl;
			} else {
				cout << label << ": " << (type == INT ? ".word " : ".byte ") << "0" << endl;
			}
			globalDataNameAffine[string(&(symbolTable.table[i].name[0]))] = label;
		}
		textSegPrepare();
		//global data are handled above
		sz = symbolTable.symTableList.records.size();
		FOR(i, 0, sz - 1) {
			//handle function block i
			SymbolTable::BranchTableItem &bitem = symbolTable.branchTable[symbolTable.symTableList.records[i].branchIndex];
			int mpc = bitem.mCodeBegin;
			int epc = i == sz - 1 ? mCode.code.size() :
				symbolTable.branchTable[symbolTable.symTableList.records[i + 1].branchIndex].mCodeBegin;
			//we are in function indexed by i
			vector<SymbolTable::TableItem> &tb = symbolTable.symTableList.records[i].tableItems;
			int paraNum = bitem.paraTypeList.size();
			int lhs = paraNum, rhs = tb.size();
			vector<LocalDataItem> localData;
			cout << symbolTable.symTableList.records[i].functName << ":" << endl;
			localData.clear();
			int totToAllocate = 0;
			if (bitem.maxCallParaNum != -1) {
				//>=0
				totToAllocate += max(4, bitem.maxCallParaNum) * 4;
				totToAllocate += 4; //ret address
			}
			//pair<string::name, pair<int::Index in tb,
			paraMap.clear();
			FOR(j, 0, paraNum - 1) paraMap[string(&tb[j].name[0])] = j;
			FOR(j, lhs, rhs - 1) {
				LocalDataItem item;
				item.name = string(&(tb[j].name[0]));
				item.idxInTab = j;
				int res = totToAllocate % 4;
				if (tb[j].type == INT && res) totToAllocate += 4 - res;
				item.realativeAddress = totToAllocate;
				int length = 1;
				if (tb[j].isArray) length = symbolTable.getLengthInArrayTable(tb[j].ref);
				totToAllocate += (tb[j].type == INT ? 4 : 1) * length;
				localData.pb(item);
			}
			int res = totToAllocate % 4;
			if (res) totToAllocate += 4 - res;
			//following are our memory registers(in memory, but for now take it easier)
			//
			int regsBaseRelativeAddress = totToAllocate;
			int regsToAllocate = 0;
			if (bitem.leftMostReg <= bitem.rightMostReg) regsToAllocate += (bitem.rightMostReg - bitem.leftMostReg + 1);
			totToAllocate += regsToAllocate * 4;
			//cout << symbolTable.symTableList.records[i].functName << ":" << endl;


			if (totToAllocate)	cout << "addiu $sp, $sp, -" << totToAllocate << endl;

			map<int, string> labelMap;
			labelMap.clear();
			FOR(j, mpc, epc - 1) if (mCode.code[j].opCode == JMP || mCode.code[j].opCode == JPC || mCode.code[j].opCode == CAS) {
				int npc = 0;
				if (mCode.code[j].opCode == JMP) npc = convertStringToInt(mCode.code[j].operand1);
				else if (mCode.code[j].opCode == JPC) npc = convertStringToInt(mCode.code[j].operand2);
				else if (mCode.code[j].opCode == CAS) npc = convertStringToInt(mCode.code[j].operand1);
				if (labelMap.find(npc) == labelMap.end()) labelMap[npc] = string("$L").append(numToString(labelTop++));
			}
			bool callSet = false;
			FOR(j, mpc, epc - 1) {
				if (labelMap.find(j) != labelMap.end()) cout << labelMap[j] << ":" << endl;
				//iterate through each intermediate code generated before
				IntermediateCode::codeItem &code = mCode.code[j];
				int offset, addr_offset, tar_addr;
				string tarName;
				if (code.opCode == ADD) {
					//template :: ADD res op1 op2 :: res <- op1 + op2
					//assert :: op1 and op2 in register and res should also be a specified register

					//load op1 to $t1
					offset = mCode.mIdxFromTempRegString(code.operand2);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t1, " << addr_offset << "($sp)" << endl;
					offset = mCode.mIdxFromTempRegString(code.operand3);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t2, " << addr_offset << "($sp)" << endl;
					cout << "addu $t0, $t1, $t2" << endl;
					offset = mCode.mIdxFromTempRegString(code.operand1);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "sw $t0, " << addr_offset << "($sp)" << endl;
				} else if (code.opCode == SUB) {
					offset = mCode.mIdxFromTempRegString(code.operand2);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t1, " << addr_offset << "($sp)" << endl;
					offset = mCode.mIdxFromTempRegString(code.operand3);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t2, " << addr_offset << "($sp)" << endl;
					cout << "subu $t0, $t1, $t2" << endl;
					offset = mCode.mIdxFromTempRegString(code.operand1);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "sw $t0, " << addr_offset << "($sp)" << endl;
				} else if (code.opCode == MUL) {
					//template :: MUL res op1 op2 :: rs <- op1 * op2
					offset = mCode.mIdxFromTempRegString(code.operand2);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t1, " << addr_offset << "($sp)" << endl;
					offset = mCode.mIdxFromTempRegString(code.operand3);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t2, " << addr_offset << "($sp)" << endl;
					cout << "mult $t1, $t2" << endl;
					cout << "mflo $t0" << endl;
					offset = mCode.mIdxFromTempRegString(code.operand1);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "sw $t0, " << addr_offset << "($sp)" << endl;
				} else if (code.opCode == DIV) {
					//template :: DIV res op1 op2 :: rs <- op1 / op2
					offset = mCode.mIdxFromTempRegString(code.operand2);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t1, " << addr_offset << "($sp)" << endl;
					offset = mCode.mIdxFromTempRegString(code.operand3);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t2, " << addr_offset << "($sp)" << endl;
					cout << "div $t1, $t2" << endl;
					cout << "mflo $t0" << endl;
					offset = mCode.mIdxFromTempRegString(code.operand1);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "sw $t0, " << addr_offset << "($sp)" << endl;
				} else if (code.opCode == MUS) {
					//template :: MUS op1 :: op1 <- -op1
					offset = mCode.mIdxFromTempRegString(code.operand1);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t0, " << addr_offset << "($sp)" << endl;
					cout << "subu $t0, $0, $t0" << endl;
					cout << "sw $t0, " << addr_offset << "($sp)" << endl;
				} else if (code.opCode == ASTO) {
					//template :: ASTO X index value :: X[index] <- value
					offset = mCode.mIdxFromTempRegString(code.operand2);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t1, " << addr_offset << "($sp)" << endl;
					//note X may be of type char or int
					offset = mCode.mIdxFromTempRegString(code.operand3);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t2, " << addr_offset << "($sp)" << endl;
					//whatever the target type is, we load the word
					//load the target address to $t0
					//para cannot be an array, so we don't handle case X is a para here
					tar_addr = getLocalVarAddress(localData, code.operand1);
					if (tar_addr == -1) {
						//in global
						string tarName = globalDataNameAffine[code.operand1];
						cout << "la $t0, " << tarName << endl;
					} else {
						//in local
						//int lhs = tar_addr >> 16, rhs = tar_addr & ((1 << 16) - 1);
						//cout << "lui $t0, " << lhs << endl;
						//cout << "ori $t0, $t0, " << rhs << endl;
						cout << "addiu $t0, $sp, " << numToString(tar_addr) << endl;
					}
					int type = getLocalOrGlobalorParaVarType(localData, code.operand1, symbolTable.symTableList.records[i]);
					if (type == INT) cout << "sll $t1, $t1, 2" << endl;
					cout << "addu $t0, $t0, $t1" << endl;
					cout << (type == INT ? "sw " : "sb ") << "$t2, 0($t0)" << endl;
				} else if (code.opCode == ALOD) {
					//template :: ALOD X index value :: value <- X[index]
					//cout << "lw $t2, " << addr_offset << "($sp)" << endl;
					offset = mCode.mIdxFromTempRegString(code.operand2);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t1, " << addr_offset << "($sp)" << endl;

					tar_addr = getLocalVarAddress(localData, code.operand1);
					if (tar_addr == -1) {
						//in global
						string tarName = globalDataNameAffine[code.operand1];
						cout << "la $t0, " << tarName << endl;
					} else {
						//int lhs = tar_addr >> 16, rhs = tar_addr &((1 << 16) - 1);
						//cout << "lui $t0, " << lhs << endl;
						//cout << "ori $t0, $t0, " << rhs << endl;
						cout << "addiu $t0, $sp, " << numToString(tar_addr) << endl;
					}
					int type = getLocalOrGlobalorParaVarType(localData, code.operand1, symbolTable.symTableList.records[i]);
					if (type == INT) cout << "sll $t1, $t1, 2" << endl;
					cout << "addu $t0, $t0, $t1" << endl;
					cout << (type == INT ? "lw " : "lb ") << "$t2, 0($t0)" << endl;
					offset = mCode.mIdxFromTempRegString(code.operand3);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "sw $t2, " << addr_offset << "($sp)" << endl;
				} else if (code.opCode == ASG) {
					//template :: ASG op1 op2 :: op1 <- op2
					//note :: case 1: op1 is var, op2 is reg | case 2: op1 is reg, op2 is var | case 3: op1 is reg, op2 is num/value
					if (code.operand1.at(0) == '$') {
						//op1 is reg
						if (code.operand2.at(0) >= '0' && code.operand2.at(0) <= '9' || code.operand2.at(0) == '-') {
							//op2 is num/value if case 3
							int v = convertStringToInt(code.operand2);
							int lhs = v >> 16, rhs = v &((1 << 16) - 1);
							cout << "lui $t1, " << lhs << endl;
							cout << "ori $t1, $t1, " << rhs << endl;
							offset = mCode.mIdxFromTempRegString(code.operand1);
							addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
							cout << "sw $t1, " << addr_offset << "($sp)" << endl;
						} else {
							//op2 is var, of case 2
							//ASG reg var
							offset = mCode.mIdxFromTempRegString(code.operand1);
							addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
							string tarReg = string("");
							if (paraMap.find(code.operand2) != paraMap.end()) {
								//is a para
								int paraIdx = paraMap[code.operand2];
								if (paraIdx < 4) tarReg = string("$a").append(numToString(paraIdx));
								else {
									cout << "lw $t0, " << numToString(totToAllocate + 4 * paraIdx) << "($sp)" << endl;
									tarReg = string("$t0");
								}
							} else {
								//is not a para
								tar_addr = getLocalVarAddress(localData, code.operand2);
								if (tar_addr == -1) {
									//in global
									string tarName = globalDataNameAffine[code.operand2];
									cout << "la $t1, " << tarName << endl;
								} else {
									//in local
									//int lhs = tar_addr >> 16, rhs = tar_addr & ((1 << 16) - 1);
									//cout << "lui $t1, " << lhs << endl;
									//cout << "ori $t1, $t1, " << rhs << endl;
									cout << "addiu $t1, $sp, " << numToString(tar_addr) << endl;
								}
								int type = getLocalOrGlobalorParaVarType(localData, code.operand2, symbolTable.symTableList.records[i]);
								cout << (type == INT ? "lw " : "lb ") << "$t0, " << "0($t1)" << endl;
								tarReg = string("$t0");
							}
							cout << "sw " << tarReg << ", " << addr_offset << "($sp)" << endl;
						}
					} else {
						//op1 is not reg, then of case 1
						//var <-- reg
						//ASG var reg
						offset = mCode.mIdxFromTempRegString(code.operand2);
						addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
						//cout << "lw $t0, " << addr_offset << "($sp)" << endl;

						int type = getLocalOrGlobalorParaVarType(localData, code.operand1, symbolTable.symTableList.records[i]);
						string strlead = string(type == INT ? "sw " : "sb ");

						if (paraMap.find(code.operand1) != paraMap.end()) {
							//is a para
							int paraIdx = paraMap[code.operand1];
							if (paraIdx < 4) cout << string(type == INT ? "lw " : "lb ") << "$a" << numToString(paraIdx)
								<< ", " << addr_offset << "($sp)" << endl;
							else {
								cout << "lw $t0, " << numToString(addr_offset) << "($sp)" << endl;
								cout << strlead << "$t0, " << numToString(totToAllocate + 4 * paraIdx)
									<< "($sp)" << endl;
							}
						} else {
							cout << "lw $t0, " << numToString(addr_offset) << "($sp)" << endl;
							//is not a para
							tar_addr = getLocalVarAddress(localData, code.operand1);
							if (tar_addr == -1) {
								//is a global var
								string tarName = globalDataNameAffine[code.operand1];
								//cout << "la $t0, " << tarName << endl;
								cout << "la $t1, " << tarName << endl;
								cout << strlead << "$t0, " << "0($t1)" << endl;
							} else {
								//int lhs = tar_addr >> 16, rhs = tar_addr & ((1 << 16) - 1);
								//cout << "lui $t1, " << lhs << endl;
								//cout << "ori $t1, $t1, " << rhs << endl;
								//ia a local var
								cout << strlead << "$t0, " << tar_addr << "($sp)" << endl;
								//cout << "addiu $t1, $sp, " << numToString(tar_addr) << endl;
							}

						}
					}
				} else if (code.opCode == CAL) {
					//first thing to do is to store $a0 ~ $a3(optional)
					//by using JAL we don't have to configure return address, but ret address has to be saved before changed
					//then we might do nothing else
					int paraSize = bitem.paraTypeList.size();
					//if (paraSize > 0) cout << "sw $a0, 0($sp)" << endl;
					//if (paraSize > 1) cout << "sw $a1, 4($sp)" << endl;
					//if (paraSize > 2) cout << "sw $a2, 8($sp)" << endl;
					//if (paraSize > 3) cout << "sw $a3, 12($sp)" << endl;
					int maxParaSize = bitem.maxCallParaNum;
					int offset = max(4, maxParaSize) * 4;
					if (callSet == false && bitem.maxCallParaNum != -1) {
						int psize = bitem.paraTypeList.size();
						FOR(i, 0, 3) if (psize > i) cout << "sw, $a" << numToString(i) << ", "
							<< numToString(totToAllocate + 4 * i) << "($sp)" << endl;
					}
					callSet = false;
					//note :: we assume that this num is realtively small
					cout << "sw $ra, " << offset << "($sp)" << endl;
					cout << "jal " << code.operand1 << endl;
					if (paraSize > 0) cout << "lw $a0, " << numToString(totToAllocate + 0) << "($sp)" << endl;
					if (paraSize > 1) cout << "lw $a1, " << numToString(totToAllocate + 4) << "($sp)" << endl;
					if (paraSize > 2) cout << "lw $a2, " << numToString(totToAllocate + 8) << "($sp)" << endl;
					if (paraSize > 3) cout << "lw $a3, " << numToString(totToAllocate + 12) << "($sp)" << endl;
					cout << "lw $ra, " << offset << "($sp)" << endl;
				} else if (code.opCode == EXF) {
					//return to $ra
					if (totToAllocate) {
						int lhs = totToAllocate >> 16, rhs = totToAllocate & ((1 << 16) - 1);
						//assume that totToAllocate is in 16-bit
						cout << "addiu $sp, $sp, " << numToString(totToAllocate) << endl;
						//cout << "lui $t0, " << lhs << endl;
						//cout << "ori $t0, $t0, " << rhs << endl;
						//cout << "subu $sp, $sp, $t0" << endl;
					}
					if (symbolTable.symTableList.records[i].functName == string("main")) {
						cout << "j $end" << endl;
					} else {
						cout << "jr $ra" << endl;
					}
				} else if (code.opCode == JMP) {//jump inside a function block
					int npc = convertStringToInt(code.operand1);
					cout << "j " << labelMap[npc] << endl;
				} else if (code.opCode == JPC) {
					int npc = convertStringToInt(code.operand2);
					int offset = mCode.mIdxFromTempRegString(code.operand1);
					int addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw " << "$t0, " << addr_offset << "($sp)" << endl;
					cout << "beq $t0, $0, " << labelMap[npc] << endl;
				} else if (code.opCode == WRITE) {
					int offset = mCode.mIdxFromTempRegString(code.operand1);
					int addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					if (bitem.paraTypeList.size()) cout << "sw " << "$a0, " << totToAllocate << "($sp)" << endl;
					cout << "lw " << "$a0, " << addr_offset << "($sp)" << endl;
					//write an integer, syscall (set $a0 to interger to print)
					cout << "li $v0, 1" << endl;
					cout << "syscall" << endl;
					if (bitem.paraTypeList.size()) cout << "lw " << "$a0, " << totToAllocate << "($sp)" << endl;
				} else if (code.opCode == WRITEC) {
					int offset = mCode.mIdxFromTempRegString(code.operand1);
					int addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					if (bitem.paraTypeList.size()) cout << "sw " << "$a0, " << totToAllocate << "($sp)" << endl;
					cout << "lb " << "$a0, " << addr_offset << "($sp)" << endl;
					//write a character, syscall(set $a0 to character to print)
					cout << "li $v0, 11" << endl;
					cout << "syscall" << endl;
					if (bitem.paraTypeList.size()) cout << "lw " << "$a0, " << totToAllocate << "($sp)" << endl;
				} else if (code.opCode == WRITES) {
					string tarName = stringMap[convertStringToInt(code.operand1)];
					if (bitem.paraTypeList.size()) cout << "sw " << "$a0, " << totToAllocate << "($sp)" << endl;
					cout << "la  $a0, " << tarName << endl;
					//write a string, sysall(set $a0 addresss of null-terminated string)
					cout << "li $v0, 4" << endl;
					cout << "syscall" << endl;
					if (bitem.paraTypeList.size()) cout << "lw " << "$a0, " << totToAllocate << "($sp)" << endl;
				} else if (code.opCode == READ) {
					cout << "li $v0, 5" << endl;
					cout << "syscall" << endl;
					if (paraMap.find(code.operand1) != paraMap.end()) {
						int paraIdx = paraMap[code.operand1];
						if (paraIdx < 4) cout << "addu $a" << numToString(paraIdx) << ", $v0, $0" << endl;
						else cout << "sw $v0, " << numToString(totToAllocate + paraIdx * 4) << "($sp)" << endl;
					} else {
						int tar_addr = getLocalVarAddress(localData, code.operand1);
						if (tar_addr == -1) {
							//is a global var
							string tarName = globalDataNameAffine[code.operand1];
							cout << "la $t0, " << tarName << endl;
							cout << "sw $v0, " << "0($t0)" << endl;
						} else {
							//ia a local var
							cout << "sw $v0, " << tar_addr << "($sp)" << endl;
						}
					}
				} else if (code.opCode == READC) {
					cout << "li $v0, 12" << endl;
					cout << "syscall" << endl;
					if (paraMap.find(code.operand1) != paraMap.end()) {
						int paraIdx = paraMap[code.operand1];
						if (paraIdx < 4) cout << "addu $a" << numToString(paraIdx) << ", $v0, $0" << endl;
						else cout << "sb $v0, " << numToString(totToAllocate + paraIdx * 4) << "($sp)" << endl;
					} else {
						int tar_addr = getLocalVarAddress(localData, code.operand1);
						if (tar_addr == -1) {
							//is a global var
							string tarName = globalDataNameAffine[code.operand1];
							cout << "sb $v0, " << "0(" << tarName << ")" << endl;
						} else {
							//ia a local var
							cout << "sb $v0, " << tar_addr << "($sp)" << endl;
						}
					}
				} else if (code.opCode == RETV) {
					//template RETV value
					int offset = mCode.mIdxFromTempRegString(code.operand1);
					int addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw " << "$v0, " << addr_offset << "($sp)" << endl;
				} else if (code.opCode == ARG) {
					//template ARG index value
					int idx = convertStringToInt(code.operand1);
					if (idx == 0) {
						if (bitem.maxCallParaNum != -1) {
							int psize = bitem.paraTypeList.size();
							FOR(i, 0, 3) if (psize > i) cout << "sw, $a" << numToString(i) << ", "
								<< numToString(totToAllocate + 4 * i) << "($sp)" << endl;
						}
						callSet = true;
					}
					int offset = mCode.mIdxFromTempRegString(code.operand2);
					int addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					if (idx < 4) {
						cout << "lw $a" << numToString(idx) << ", " << addr_offset << "($sp)" << endl;
					} else {
						cout << "lw $t0, " << numToString(addr_offset) << "($sp)" << endl;
						cout << "sw $t0, " << numToString(idx * 4) << "($sp)" << endl;
					}
				} else if (code.opCode == CAS) {
					//template CAS address op1 op2
					//case (Op1 == op2) jump to CAS
					int offset = mCode.mIdxFromTempRegString(code.operand2);
					int addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t1, " << addr_offset << "($sp)" << endl;

					int numOp = convertStringToInt(code.operand3);
					int lhs = numOp >> 16, rhs = numOp & ((1 << 16) - 1);
					cout << "lui $t2, " << numToString(lhs) << endl;
					cout << "ori $t2, $t2, " << numToString(rhs) << endl;

					string tarName = labelMap[convertStringToInt(code.operand1)];
					cout << "beq $t1, $t2, " << tarName << endl;
				} else if (code.opCode == EQL) {
					//template :: EQL res op1 op2 :: res = op1 == op2
					int offset = mCode.mIdxFromTempRegString(code.operand2);
					int addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t1, " << addr_offset << "($sp)" << endl;
					offset = mCode.mIdxFromTempRegString(code.operand3);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t2, " << addr_offset << "($sp)" << endl;
					cout << "slt $t0, $t1, $t2" << endl;
					cout << "slt $t1, $t2, $t1" << endl;
					cout << "or $t0, $t0, $t1" << endl;
					cout << "xori $t0, $t0, 1" << endl;
					offset = mCode.mIdxFromTempRegString(code.operand1);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "sw $t0, " << addr_offset << "($sp)" << endl;
				} else if (code.opCode == NEQ) {
					int offset = mCode.mIdxFromTempRegString(code.operand2);
					int addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t1, " << addr_offset << "($sp)" << endl;
					offset = mCode.mIdxFromTempRegString(code.operand3);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t2, " << addr_offset << "($sp)" << endl;
					cout << "slt $t0, $t1, $t2" << endl;
					cout << "slt $t1, $t2, $t1" << endl;
					cout << "or $t0, $t0, $t1" << endl;
					offset = mCode.mIdxFromTempRegString(code.operand1);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "sw $t0, " << addr_offset << "($sp)" << endl;
				} else if (code.opCode == GRT) {
					int offset = mCode.mIdxFromTempRegString(code.operand2);
					int addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t1, " << addr_offset << "($sp)" << endl;
					offset = mCode.mIdxFromTempRegString(code.operand3);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t2, " << addr_offset << "($sp)" << endl;
					cout << "slt $t0, $t2, $t1" << endl;
					offset = mCode.mIdxFromTempRegString(code.operand1);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "sw $t0, " << addr_offset << "($sp)" << endl;
				} else if (code.opCode == GEQ) {
					int offset = mCode.mIdxFromTempRegString(code.operand2);
					int addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t1, " << addr_offset << "($sp)" << endl;
					offset = mCode.mIdxFromTempRegString(code.operand3);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t2, " << addr_offset << "($sp)" << endl;
					cout << "slt $t0, $t1, $t2" << endl;
					cout << "xori $t0, $t0, 1" << endl;
					offset = mCode.mIdxFromTempRegString(code.operand1);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "sw $t0, " << addr_offset << "($sp)" << endl;
				} else if (code.opCode == LES) {
					int offset = mCode.mIdxFromTempRegString(code.operand2);
					int addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t1, " << addr_offset << "($sp)" << endl;
					offset = mCode.mIdxFromTempRegString(code.operand3);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t2, " << addr_offset << "($sp)" << endl;
					cout << "slt $t0, $t1, $t2" << endl;
					offset = mCode.mIdxFromTempRegString(code.operand1);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "sw $t0, " << addr_offset << "($sp)" << endl;
				} else if (code.opCode == LEQ) {
					int offset = mCode.mIdxFromTempRegString(code.operand2);
					int addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t1, " << addr_offset << "($sp)" << endl;
					offset = mCode.mIdxFromTempRegString(code.operand3);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "lw $t2, " << addr_offset << "($sp)" << endl;
					cout << "slt $t0, $t2, $t1" << endl;
					cout << "xori $t0, $t0, 1" << endl;
					offset = mCode.mIdxFromTempRegString(code.operand1);
					addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "sw $t0, " << addr_offset << "($sp)" << endl;
				} else if (code.opCode == FRET) {
					int offset = mCode.mIdxFromTempRegString(code.operand1);
					int addr_offset = (offset - bitem.leftMostReg) * 4 + regsBaseRelativeAddress;
					cout << "sw $v0, " << addr_offset << "($sp)" << endl;
				}

			}
		}
		cout << "$end:" << endl;
	}

}oCode;
void mGlobalConstantDecBlock();
void mFunctConstantDecBlock(int bidx);
void mFunctVarDecBlock(int bidx);
void mCaseItem(int functionIndex, SymbolTable::CaseTable &ctb);
pii mDefaultItem(set<int> terminateToken, int functionIdx, SymbolTable::CaseTable &ctb);
char *pointer;


void inputHandle() {
	char fileInName[100];
	//maximum fileName length :: 100
	printf("input file name:\n");
	scanf("%s", fileInName);
	FILE *fileIn;
	if ((fileIn = fopen(fileInName, "r")) == NULL) {
		printf("file not found. ABORT. \n");
		exit(0);
	}
	char ch;
	sourceCodeLength = 0;
	while ((ch = fgetc(fileIn)) != EOF) {
		sourceCode[sourceCodeLength++] = ch;
		if (sourceCodeLength >= maxSourceCodeLength) {
			fclose(fileIn);
			printf("source code length limit exceeded. ABORTED\n");
			exit(0);
		}
	}
	sourceCode[sourceCodeLength] = '\0';
	fclose(fileIn);
	lineNumber = 1, cursorIndex = 1;
	pointer = sourceCode;
}

bool isCharacterWhiteSpace(char ch) {
	return ch == '\n' || ch == '\t' || ch == ' ';
}

void getNextChar() {
	//precondtion :: *pointer != '\0'
	if (*pointer == '\n') cursorIndex = 1, lineNumber++;
	else cursorIndex++;
	pointer++;
}

void filterWhiteSpace() {
	while (*pointer == '\n' || *pointer == '\t' || *pointer == ' ') {
		getNextChar();
	}
}


bool isCharacterLetter(char ch) {
	return ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z' || ch == '_';
}

bool isCharacterNumer(char ch) {
	return ch >= '0' && ch <= '9';
}

bool isCharacterSpliterHeader(char ch) {
	return ch == '+' | ch == '-' | ch == '*' | ch == '/' | ch == '=' | ch == '!'
		| ch == '>' | ch == '<' | ch == '{' | ch == '}' | ch == '[' | ch == ']'
		| ch == '(' | ch == ')' | ch == '\'' | ch == '\"' | ch == ',' | ch == ';'
		| ch == ':';
}

bool isCharacterLegal(char ch) {
	if (ch == '\0') {
		error.invoke(lineNumber, cursorIndex, PROGRAM_INCOMPLETE);
		exit(0);
	}
	return isCharacterLetter(ch) | isCharacterNumer(ch) | isCharacterSpliterHeader(ch);
}


void filterIllegalCharacter() {
	// note: fileter a CONTINUOS CHARACTER SEGMENTS
	// note: error report at the begining
	// note: assert *pointer is illegal character
	error.invoke(lineNumber, cursorIndex, CHARACTER_ILLEGAL);
	while (*pointer && !isCharacterLegal(*pointer)) {
		getNextChar();
	}
}

bool isCharacterLegalInConstantChar(char ch) {
	return ch == '+' | ch == '-' | ch == '*' | ch == '/' | isCharacterLetter(ch) | isCharacterNumer(ch);
}

bool isCharacterLegalInString(char ch) {
	return ch >= 32 && ch <= 126 && ch != 34;
}

int getDoubleSpliterCode(char first, char second) {
	if (first == '=' && second == '=') return EQUAL;
	if (first == '<' && second == '=') return LESS_EQUAL;
	if (first == '>' && second == '=') return GREATER_EQUAL;
	if (first == '!' && second == '=') return NOT_EQUAL;
	return -1;
}

void getWord() {

	word.reset();
	//precondition :: *pointer != '\0'
	while (isCharacterWhiteSpace(*pointer) || !isCharacterLegal(*pointer)) {
		if (isCharacterWhiteSpace(*pointer)) filterWhiteSpace();
		else filterIllegalCharacter();
	}

	//assert :: *pointer != '\0' && *pointer is LEGAL && *pointer is NOT WHITESPACE
	if (isCharacterLetter(*pointer)) {
		//assert :: *pointer is a letter, in case no error occurs, we shall
		//have the word to fetch is an identifier(variable/constant/function/reserved)
		//indentifier pointer initialize to 0
		while (isCharacterLetter(*pointer) || isCharacterNumer(*pointer)) {
			word.wordString.pb(*pointer);
			getNextChar();
		}
		word.wordString.pb('\0');
		int typeCode = reservedWordsDict.getReservedWordCodeIndex(&(word.wordString[0]));
		if (typeCode == -1) typeCode = IDENTIFIER;
		word.type = typeCode;
		return;
	}

	if (isCharacterNumer(*pointer)) {
		//assert :: *pointer is a number, in case no error occurs, we shall return
		//a number(no leading zeros)
		int p = 0;
		int leadingZeroNum = 0;
		bool hasCastLeadingZeroError = false;
		while (*pointer == '0') {
			leadingZeroNum++;
			word.wordString.pb(*pointer);
			if (!hasCastLeadingZeroError && leadingZeroNum > 1) {
				error.invoke(lineNumber, cursorIndex, LEADING_ZERO);
				hasCastLeadingZeroError = true;
			}
			getNextChar();
		}
		while (isCharacterNumer(*pointer)) {
			if (!hasCastLeadingZeroError && leadingZeroNum && *pointer != '0') {
				error.invoke(lineNumber, cursorIndex, LEADING_ZERO);
				hasCastLeadingZeroError = true;
			}
			word.wordString.pb(*pointer);
			//CAUTION :: care about range
			getNextChar();
		}
		word.type = UNSIGNED_NUMBER;
		word.wordString.pb('\0');
		word.convertStringToValue();
		return;
	}

	//assert(isCharacterSpliterHeader(*pointer));

	if (*(pointer + 1)) {
		int typeCode = getDoubleSpliterCode(*pointer, *(pointer + 1));
		if (typeCode != -1) {
			word.wordString.pb(*pointer);
			word.wordString.pb(*(pointer + 1));
			word.wordString.pb('\0');
			getNextChar();
			getNextChar();
			word.type = typeCode;
			return;
		}
	}

	//assert :: pointer indicates a single spliter
	if (*pointer == '\"') {
		int p = 0;
		word.type = STRING;
		getNextChar();
		while (isCharacterLegalInString(*pointer)) {
			word.wordString.pb(*pointer);
			getNextChar();
		}
		//note: possibly '\0' reached
		//NOTE: error should be loacted locally
		if (*pointer == '\0') {
			error.invoke(lineNumber, cursorIndex, MISS_RIGHT_DOUBLE_QUOTE);
			exit(0);
		} else if (*pointer != '\"') {
			error.invoke(lineNumber, cursorIndex, ILLEGAL_CHARACTER_IN_STRING);
			getNextChar();
			return;
		}
		//assert :: *pointer == '\"'
		word.wordString.pb('\0');
		getNextChar();
		return;
	}

	if (*pointer == '\'') {
		word.type = CHARACTER;
		getNextChar();
		//note: possibly reach '\0'
		if (*pointer == '\0') {
			error.invoke(lineNumber, cursorIndex, MISS_RIGHT_SINGLE_QUOTE);
			exit(0);
		} else if (!isCharacterLegalInConstantChar(*pointer)) {
			error.invoke(lineNumber, cursorIndex, ILLEGAL_CHARACTER_IN_CONSTANT_CHAR);
			getNextChar();
			return;
		}
		//assert :: *pointer is okay
		word.wordString.pb(*pointer);
		getNextChar();
		if (*pointer == '\0') {
			error.invoke(lineNumber, cursorIndex, MISS_RIGHT_SINGLE_QUOTE);
			exit(0);
		} else if (*pointer != '\'') {
			error.invoke(lineNumber, cursorIndex, CONSTANT_CHAR_OUT_OF_LENGTH);
			getNextChar();
			return;
		}

		//assert :: *pointer == '\''
		word.wordString.pb('\0');
		getNextChar();
		return;
	}

	int typeCode = spliterDict.getSingleSpliterCode(*pointer);
	word.type = typeCode;
	word.wordString.pb(*pointer);
	word.wordString.pb('\0');
	getNextChar();
}

int mConstantDec(bool isGlobal, set<int> terminateToken, int branchIdex = -1) {
	//return number of constants
	//precondition :: word.type == CONSTANT
	/********************************************
	const int n = 15, m = 20;
	const char ch = 't', ox = 'y', px = 'l';
	*********************************************/
	//note: 'const' already consumed, proceed to go
	getWord();
	verify(set<int>{INT, CHAR}, word, UNEXPECTED_SYMBOL);
	int type = word.type;

	//cannot cross { or ;

	int num = 0;
	do {
		getWord();
		if (word.type != IDENTIFIER) {
			error.invoke(lineNumber, cursorIndex, IDENTIFIER_EXPECTED);
		} else {
			int idx = symbolTable.pushItem(word, isGlobal);
			SymbolTable::TableItem &tb = symbolTable.getTableItem(idx);
			if (idx > 0 && idx < symbolTable.table.size()) {
				tb.type = type;
				tb.modifier = CONSTANT;
			}
			getWord();
			if (word.type != ASSIGN) {
				error.invoke(lineNumber, cursorIndex, ASSIGN_EXPECTED);
			} else {
				getWord();
				int value = 0;
				verify(set<int>{PLUS, MINUS, UNSIGNED_NUMBER, CHARACTER}, word, UNEXPECTED_SYMBOL);
				if (word.type == PLUS || word.type == MINUS) {
					bool neg = word.type == MINUS;
					getWord();
					if (word.type == UNSIGNED_NUMBER) {
						value = word.wordValue;
						if (neg) value = -value;
					} else error.invoke(lineNumber, cursorIndex, UNSIGNED_NUMBER_EXPECTED);
				} else if (word.type == UNSIGNED_NUMBER) {
					value = word.wordValue;
				} else if (word.type == CHARACTER) {
					value = word.wordString[0];
				}
				getWord();
				int cidx = symbolTable.newConstantValueTableItem();
				SymbolTable::ConstantValueTableItem &ctb = symbolTable.getConstantValue(cidx);
				ctb.value = value;
				tb.ref = cidx;
				num++;
			}
		}
		if (word.type == SEMI_COLON) break;
		verify(set<int>{COMMA}, word, COMMA_EXPECTED);
	} while (word.type == COMMA);
	verify(terminateToken, word, SEMI_COLON_EXPECTED);
	return num;
}

int mArrayDec(set<int> terminateToken, int typeCode, int idx) {
	//return len of array
	int len = 1;
	//precondtion :: word.typeCode == '['
	SymbolTable::TableItem &tb = symbolTable.getTableItem(idx);
	getWord();
	if (word.type != UNSIGNED_NUMBER) {
		error.invoke(lineNumber, cursorIndex, UNSIGNED_NUMBER_EXPECTED);
	} else {
		int value = word.wordValue;
		if (value < 1) {
			error.invoke(lineNumber, cursorIndex, ARRAY_SIZE_TOO_SMALL);
		} else if (value > maxArraySize) {
			error.invoke(lineNumber, cursorIndex, ARRAY_SIZE_TOO_LARGE);
		}
		//set ATAB
		int aidx = symbolTable.newArrayTableItem();
		SymbolTable::ArrayTableItem &atb = symbolTable.getArrayTableItem(aidx);
		atb.type = typeCode;
		atb.length = value;
		tb.ref = aidx;
		tb.isArray = true;
		tb.type = typeCode;
		getWord();
		len = value;
	}
	verify(terminateToken, word, RIGHT_SQUARE_BRACKET_EXPECTED);
	return len;
}

void mGlobalVarDec(set<int> terminateToken, int tableIdx) {
	//ident and following symbol taken
	verify(set<int>{COMMA, SEMI_COLON, LEFT_SQUARE_BRACKET}, word, UNEXPECTED_SYMBOL);
	if (word.type == LEFT_SQUARE_BRACKET) {
		mArrayDec(set<int>{RIGHT_SQUARE_BRACKET}, symbolTable.getTableItem(tableIdx).type, tableIdx);
		if (word.type == RIGHT_SQUARE_BRACKET) getWord();
	}
	while (word.type == COMMA) {
		getWord();
		if (word.type == IDENTIFIER) {
			int idx = symbolTable.pushItem(word, true);
			if (idx > 0 && idx < symbolTable.table.size()) {
				symbolTable.table[idx].type = symbolTable.getTableItem(tableIdx).type;
				symbolTable.table[idx].modifier = VARIABLE;
			}
			getWord();
			if (word.type == LEFT_SQUARE_BRACKET) {
				mArrayDec(set<int>{RIGHT_SQUARE_BRACKET}, symbolTable.getTableItem(tableIdx).type, idx);
				if (word.type == RIGHT_SQUARE_BRACKET) getWord();
			}
		} else error.invoke(lineNumber, cursorIndex, IDENTIFIER_EXPECTED);
		if (word.type == SEMI_COLON) break;
		verify(set<int>{COMMA}, word, COMMA_EXPECTED);
	}
	verify(terminateToken, word, SEMI_COLON_EXPECTED);
}

pii mVarDec(bool isGlobal, int typeCode, set<int>terminateToken, int branchIdx = -1) {
	//return pair<number of var, length of these vars>
	//precondtion :: prepare to consume variable declare part
	//int x;
	//char sample[100], y;
	//int or char is alreay taken
	int num = 0, len = 0;
	getWord();
	verify(set<int>{IDENTIFIER}, word, IDENTIFIER_EXPECTED);
	if (word.type == IDENTIFIER) {
		int idx = symbolTable.pushItem(word, isGlobal);
		if (idx > 0 && idx < symbolTable.table.size()) {
			symbolTable.table[idx].type = typeCode, symbolTable.table[idx].modifier = VARIABLE;
		}
		num++, len++;
		getWord();
		if (word.type == LEFT_SQUARE_BRACKET) {
			int length = mArrayDec(set<int>{RIGHT_SQUARE_BRACKET}, typeCode, idx);
			if (word.type == RIGHT_SQUARE_BRACKET) getWord();
			len += length - 1;
		}
		while (word.type == COMMA) {
			getWord();
			verify(set<int>{IDENTIFIER}, word, IDENTIFIER_EXPECTED);
			if (word.type == IDENTIFIER) {
				idx = symbolTable.pushItem(word, isGlobal);
				if (idx > 0 && idx < symbolTable.table.size()) {
					symbolTable.table[idx].type = typeCode, symbolTable.table[idx].modifier = VARIABLE;
				}
				getWord();
				num++, len++;
				if (word.type == LEFT_SQUARE_BRACKET) {
					int length = mArrayDec(set<int>{RIGHT_SQUARE_BRACKET}, typeCode, idx);
					if (word.type == RIGHT_SQUARE_BRACKET) getWord();
					len += length - 1;
				}
			}
			if (word.type == SEMI_COLON) break;
			verify(set<int>{COMMA}, word, COMMA_EXPECTED);
		}
	}
	verify(terminateToken, word, SEMI_COLON_EXPECTED);
	return mp(num, len);
}

void selector(set<int> terminateToken, SymbolTable::TableItem &tb) {
	getWord();
	mExp(terminateToken);
	//vector<pii> &stk = mCode.tempOperandStack;
	//stk.pop();
	if (!tb.isArray) {
		error.invoke(lineNumber, cursorIndex, ARRAY_NOT_DECLARED);
	} else {
		int addr = tb.ref;
	}
}

void mFactor(set<int> terminateToken) {
	//<fac> ::= <ident> | <ident>[<exp>] | (<exp>) | <integer> | <character> | <rcall>

	verify(factorBeginSymbols, word, UNEXPECTED_SYMBOL);
	if (word.type == IDENTIFIER) {
		int idx = symbolTable.getIndexFromWord(word);
		SymbolTable::TableItem& tb = symbolTable.getTableItem(idx);
		getWord();
		if (tb.modifier == CONSTANT) {
			int nexId = mCode.getNextAllocatable();
			mCode.emit(ASG, mCode.getTempStringByIdx(nexId), numToString(symbolTable.getConstantValue(tb.ref).value));
			vector<pii> &stk = mCode.tempOperandStack;
			stk.pb(mp(nexId, tb.type));
			//mCode.emit(LDC, tb.address);
			verify(terminateToken, word, UNEXPECTED_SYMBOL);
		} else if (tb.modifier == VARIABLE) {
			if (word.type == LEFT_SQUARE_BRACKET) {
				//mCode.emit(LDA, tb.address);
				//load base address of array
				selector(set<int>{RIGHT_SQUARE_BRACKET}, tb);
				//mCode.emit(LDT);
				int nexId = mCode.getNextAllocatable();
				vector<pii> &stk = mCode.tempOperandStack;
				if (stk.size()) {
					mCode.emit(ALOD, string(&(tb.name[0])), mCode.getTempStringByIdx(stk[stk.size() - 1].first),
						mCode.getTempStringByIdx(nexId));
				}
				if(stk.size()) stk.pop();
				stk.pb(mp(nexId, tb.type));
				if (word.type == RIGHT_SQUARE_BRACKET) getWord();
				verify(terminateToken, word, UNEXPECTED_SYMBOL);
			} else {
				int nexId = mCode.getNextAllocatable();
				vector<pii> &stk = mCode.tempOperandStack;
				mCode.emit(ASG, mCode.getTempStringByIdx(nexId), string(&(tb.name[0])));
				stk.pb(mp(nexId, tb.type));
				//mCode.emit(LOD, tb.address);
				verify(terminateToken, word, UNEXPECTED_SYMBOL);
			}
		} else if (tb.modifier == FUNCTION) {
			if (tb.type == VOID_TYPE) error.invoke(lineNumber, cursorIndex, VOID_FUNCTION_UNEXPECTED);
			mCallStatement(terminateToken, idx);
			int nexId = mCode.getNextAllocatable();
			mCode.emit(FRET, mCode.getTempStringByIdx(nexId));
			vector<pii> &stk = mCode.tempOperandStack;
			stk.pb(mp(nexId, tb.type));
		}
	} else if (word.type == LEFT_PARENTHESIS) {
		getWord();
		mExp(set<int>{RIGHT_PARENTHESIS});
		if (word.type == RIGHT_PARENTHESIS) getWord();
		verify(terminateToken, word, UNEXPECTED_SYMBOL);
	} else if (word.type == CHARACTER) {
		int nexId = mCode.getNextAllocatable();
		mCode.emit(ASG, mCode.getTempStringByIdx(nexId), numToString(word.wordString[0]));
		vector<pii> &stk = mCode.tempOperandStack;
		stk.pb(mp(nexId, CHAR));
		//mCode.emit(LDC, word.wordString[0]);
		getWord();
		verify(terminateToken, word, UNEXPECTED_SYMBOL);
	} else if (word.type == PLUS || word.type == MINUS || word.type == UNSIGNED_NUMBER) {
		int syb = 1;
		if (word.type != UNSIGNED_NUMBER) {
			if (word.type == MINUS) syb *= -1;
			getWord();
			verify(set<int>{UNSIGNED_NUMBER}, word, UNSIGNED_NUMBER_EXPECTED);
		}
		vector<pii> &stk = mCode.tempOperandStack;
		int nexId = mCode.getNextAllocatable();
		if (word.type == UNSIGNED_NUMBER) {
			mCode.emit(ASG, mCode.getTempStringByIdx(nexId), numToString(word.wordValue));
			stk.pb(mp(nexId, INT));
			getWord();
		}
		if (syb == -1) {
			int idx = 0;
			if(stk.size()) idx = stk[stk.size() - 1].first;
			mCode.emit(MUS, mCode.getTempStringByIdx(idx));
		}
		//if (word.type == UNSIGNED_NUMBER) mCode.emit(LDC, word.wordValue), getWord();
		//if (syb == -1) mCode.emit(MUS);
		verify(terminateToken, word, UNEXPECTED_SYMBOL);
	}
}


void mCallStatement(set<int>terminateToken, int idx) {
	SymbolTable::TableItem &tb = symbolTable.getTableItem(idx);
	if (!cmp(tb.name, vector<char>{'m', 'a', 'i', 'n', '\0'})) {
		error.invoke(lineNumber, cursorIndex, MAIN_CALLED);
	}
	SymbolTable::TableItem &__tb = symbolTable.getTableItem(symbolTable.curFunctionIdexInTable);
	SymbolTable::BranchTableItem &__btb = symbolTable.getBranchItem(__tb.ref);
	int &tem = __btb.maxCallParaNum;
	int rhs = symbolTable.getBranchItem(tb.ref).paraTypeList.size();
	if (rhs > tem) tem = rhs;
	//tem = max(tem, symbolTable.branchTable[tb.ref].paraTypeList.size());
	//mCode.emit(MKS, idx);
	//mark the stack S
	//int lastPara = symbolTable.branchTable[tb.ref].lastParameter;
	//int curParaIndex = idx;
	verify(set<int> {LEFT_PARENTHESIS}, word, LEFT_PARENTHESIS_EXPECTED);
	//int paraNum = 0;
	vector<int> formalPara;
	formalPara.clear();
	do {
		getWord();
		if (word.type == RIGHT_PARENTHESIS) break;
		if (formalPara.size() >= symbolTable.getBranchItem(tb.ref).paraTypeList.size()) {
			error.invoke(lineNumber, cursorIndex, TOO_MANY_FORMAL_PARA);
		} else {
			mExp(set<int>{COMMA, RIGHT_PARENTHESIS});
			vector<pii> &stk = mCode.tempOperandStack;
			if(stk.size()) formalPara.pb(stk[stk.size() - 1].first);
			if(stk.size()) stk.pop();
			//mCode.emit(ARG, numToString(paraNum - 1), mCode.getTempStringByIdx(stk[stk.size() - 1].first));
			//value alreay loaded onto S top
		}
		verify(set<int>{COMMA, RIGHT_PARENTHESIS}, word, UNEXPECTED_SYMBOL);
	} while (word.type == COMMA);
	if (word.type == RIGHT_PARENTHESIS) getWord();
	else error.invoke(lineNumber, cursorIndex, RIGHT_PARENTHESIS_EXPECTED);
	if (formalPara.size() < symbolTable.getBranchItem(tb.ref).paraTypeList.size()) {
		error.invoke(lineNumber, cursorIndex, TOO_FEW_FORMAL_PARA);
	}
	verify(terminateToken, word, UNEXPECTED_SYMBOL);
	int sz = formalPara.size();
	FOR(i, 0, sz - 1) {
		mCode.emit(ARG, numToString(i), mCode.getTempStringByIdx(formalPara[i]));
	}
	mCode.emit(CAL, string(&(tb.name[0])));
	//mCode.emit(CAL, symbolTable.branchTable[tb.ref].privateSize - 1);
}

void mTerm(set<int> terminateToken) {
	set<int> firstFactorTerminateToken = cmb(terminateToken, set<int>{STAR, SLASH});
	mFactor(firstFactorTerminateToken);
	vector<pii> &stk = mCode.tempOperandStack;
	while (word.type == STAR || word.type == SLASH) {
		bool slash = word.type == SLASH;
		getWord();
		mFactor(firstFactorTerminateToken);
		stk = mCode.tempOperandStack;
		int idx1 = 0, idx2 = 0;
		if(stk.size() > 1) idx1 = stk[stk.size() - 2].first;
		if(stk.size()) idx2 = stk[stk.size() - 1].first;
		int nexId = mCode.getNextAllocatable();
		if (stk.size()) stk.pop();
		if (stk.size()) stk.pop();
		mCode.emit(slash ? DIV : MUL, mCode.getTempStringByIdx(nexId), mCode.getTempStringByIdx(idx1),
			mCode.getTempStringByIdx(idx2));
		stk.pb(mp(nexId, INT));
		//if (slash) mCode.emit(DIV);
		//else mCode.emit(MUL);
	}
}


/**************************************************************************
<exp> ::= [+|-]<term>{+|- <term>}
<term> ::= <fac>{*|/  <fac>}
<fac> ::= <ident> | <ident>[<exp>] | (<exp>) | <integer> | <character> | <rcall>

***************************************************************************/
void mExp(set<int> terminateToken) {
	//template <exp>) | <exp>;
	set<int> firstTermTerminateToken = cmb(terminateToken, set<int>{PLUS, MINUS});
	set<int> expressionBeginSymbols = cmb(factorBeginSymbols, set<int> {PLUS, MINUS});
	verify(expressionBeginSymbols, word, UNEXPECTED_SYMBOL);
	if (word.type == PLUS || word.type == MINUS) {
		bool neg = word.type == MINUS;
		getWord();
		mTerm(firstTermTerminateToken);
		if (neg) {
			vector<pii> &stk = mCode.tempOperandStack;
			int idx = 0;
			if(stk.size()) idx = stk[stk.size() - 1].first;
			mCode.emit(MUS, mCode.getTempStringByIdx(idx));
		}
		//if (neg) mCode.emit(MUS, mCode.getOperandStackTop());
		//if (neg) intermdediateCode.emit(MUS);
	} else mTerm(firstTermTerminateToken);
	vector<pii> &stk = mCode.tempOperandStack;
	//int o = 0, idx[2];
	//idx[o] = stk[stk.size() - 1].first;
	while (word.type == PLUS || word.type == MINUS) {
		bool minus = word.type == MINUS;
		getWord();
		mTerm(firstTermTerminateToken);
		stk = mCode.tempOperandStack;
		int idx1 = 0, idx2 = 0;
		if(stk.size() > 1) idx1 = stk[stk.size() - 2].first;
		if(stk.size()) idx2 = stk[stk.size() - 1].first;
		//idx[o ^ 1] = stk[stk.size() - 1].first;
		int nexId = mCode.getNextAllocatable();
		mCode.emit(minus ? SUB : ADD, mCode.getTempStringByIdx(nexId), mCode.getTempStringByIdx(idx1),
			mCode.getTempStringByIdx(idx2));
		if (stk.size()) stk.pop();
		if (stk.size()) stk.pop();
		stk.pb(mp(nexId, INT));
		//o ^= 1;
		//int nexOp = minus ? SUB : ADD;
		//mCode.emit(nexOp, numToString(stk[sz - 2]), numToString(stk[sz - 1]), nextVar);
		//stk[sz - 2] = ????
		/***********************************
		if (minus) intermdediateCode.emit(SUB);
		else intermdediateCode.emit(ADD);
		**************************************/
	}
}

void mFunctDec(set<int> terminateToken, int typeCode, bool isMain) {
	//function name alreay taken
	if (isMain && typeCode != VOID) error.invoke(lineNumber, cursorIndex, UNEXPECTED_MAIN_TYPE);
	int idx = symbolTable.pushItem(word, true);
	symbolTable.curFunctionIdexInTable = idx;
	/***************************************************
	NOTE: don't forget to set 'printf' and 'scanf' in case
	redefinition.
	****************************************************/

	SymbolTable::TableItem &tb = symbolTable.getTableItem(idx);
	//if we declare 'printf' or 'scanf' ?
	if (idx) {
		tb.type = typeCode;
		tb.modifier = FUNCTION;
	}
	getWord();
	verify(set<int>{LEFT_PARENTHESIS}, word, LEFT_PARENTHESIS_EXPECTED);
	mFunctBlock(terminateToken, typeCode, idx, isMain);
	mCode.emit(EXF);
	/*****************************************
	return to the place you marked in stack S.
	******************************************/
	symbolTable.exitBlockPopTable(idx);
}

void mFunctBlock(set<int> terminateToken, int typeCode, int index, bool isMain) {
	//word.typecode is expected to be '('
	//last read word to be '}'
	verify(set<int>{LEFT_PARENTHESIS}, word, LEFT_PARENTHESIS_EXPECTED);
	//symbolTable.table[index].ref = symbolTable.newBranchTableItem();
	if (word.type == LEFT_PARENTHESIS) getWord();
	mParaList(set<int>{RIGHT_PARENTHESIS}, index, isMain);
	if (index >= 0 && index < symbolTable.table.size()) {
		int __ref = symbolTable.table[index].ref;
		if (__ref >= 0 && __ref < symbolTable.branchTable.size()) {
			symbolTable.branchTable[__ref].mCodeBegin = mCode.code.size();
		}
		symbolTable.table[index].type = typeCode;
	}

	if (word.type == RIGHT_PARENTHESIS) getWord();
	verify(set<int>{LEFT_BRACKET}, word, LEFT_BRACKET_EXPECTED);
	if (word.type == LEFT_BRACKET) getWord();
	if (word.type == CONST) mFunctConstantDecBlock(symbolTable.table[index].ref);
	if (word.type == INT || word.type == CHAR) mFunctVarDecBlock(symbolTable.table[index].ref);
	symbolTable.getTableItem(index).address = mCode.getNextCodeAddress();
	//<state_seq> ::= {<state>}
	mStatementSeq(terminateToken, index);//you should take '}'
}

void mParaList(set<int>terminateToken, int index, bool isMain) {
	verify(set<int>{INT, CHAR, RIGHT_PARENTHESIS}, word, UNEXPECTED_SYMBOL);
	//note: int/char/')' already taken
	if (isMain && word.type != RIGHT_PARENTHESIS) {
		error.invoke(lineNumber, cursorIndex, RIGHT_PARENTHESIS_EXPECTED);
	}
	int bidx = symbolTable.newBranchTableItem();
	SymbolTable::BranchTableItem &btb = symbolTable.getBranchItem(bidx);
	SymbolTable::TableItem &tb = symbolTable.getTableItem(index);
	tb.ref = bidx;
	btb.paraTypeList.clear();
	//symbolTable.branchTable[bidx].privateSize = 5 * 4;//5 * 4bytes
	//symbolTable.branchTable[bidx].lastParameter = index;//indicates no parameter
	//symbolTable.branchTable[bidx].last = index;//indicates no content(no para of course)
	while (word.type == CHAR || word.type == INT) {
		int type = word.type;
		getWord();
		if (word.type != IDENTIFIER) {
			error.invoke(lineNumber, cursorIndex, IDENTIFIER_EXPECTED);
		} else {
			int idx = symbolTable.pushItem(word, false);
			//push paramter into symbol table
			if (idx) {
				if (idx >= 0 && idx < symbolTable.table.size()) {
					symbolTable.table[idx].type = type;
				}
			}
			if (idx >= 0 && idx < symbolTable.table.size()) {
				symbolTable.table[idx].modifier = VARIABLE;
			}
			//is a parameter
			if (bidx >= 0 && bidx < symbolTable.branchTable.size()) {
				symbolTable.branchTable[bidx].paraTypeList.pb(type);
			}
			//symbolTable.branchTable[bidx].lastParameter = idx;
			//symbolTable.branchTable[bidx].privateSize += type == CHAR ? 1 : 4;
			getWord();
		}
		verify(set<int>{COMMA, RIGHT_PARENTHESIS}, word, UNEXPECTED_SYMBOL);
		if (word.type == RIGHT_PARENTHESIS) break;
		if (word.type == COMMA) getWord();
	}
	//symbolTable.branchTable[bidx].last = symbolTable.branchTable[bidx].lastParameter;
	//symbolTable.branchTable[bidx].size = symbolTable.branchTable[bidx].privateSize;
	//symbolTable.branchTable[bidx].paraTypeList.pb(word.type);
	if (isMain && bidx >= 0 && bidx < symbolTable.branchTable.size() && symbolTable.branchTable[bidx].paraTypeList.size()){
		error.invoke(lineNumber, cursorIndex, UNEXPECTED_MAIN_PARA);
	}
	verify(terminateToken, word, RIGHT_PARENTHESIS_EXPECTED);
}

void mGlobalConstantDecBlock() {
	//precondition :: word.typeCode is CONST before called
	while (word.type == CONST) {
		mConstantDec(true, set<int>{SEMI_COLON});
		if (word.type == SEMI_COLON) getWord();
	}
	//postcondition :: read ahead for next
}

void mFunctConstantDecBlock(int bidx) {
	//precondition :: word.typeCode is CONST before called
	while (word.type == CONST) {
		int sz = mConstantDec(false, set<int>{SEMI_COLON}, bidx);
		if (word.type == SEMI_COLON) getWord();
	}
	//postcondition :: read ahead for next
}

void mFunctVarDecBlock(int bidx) {
	while (word.type == CHAR || word.type == INT) {
		int eleSize = word.type == CHAR ? 1 : 4;
		pii info = mVarDec(false, word.type, set<int>{SEMI_COLON}, bidx);
		SymbolTable::BranchTableItem &btb = symbolTable.getBranchItem(bidx);
		btb.size += eleSize * info.second;
		if (word.type == SEMI_COLON) getWord();
	}
}

void mStatement(int functionIndex) {
	//proceed till statement end, no more read
	if (word.type == IF) mIfStatement(functionIndex);
	//template if(<cond>) <state>
	//<state> either ends with ';' or '}'
	//you should take the last symbol
	else if (word.type == WHILE) mWhileStatement(functionIndex);
	//template while(<cond>) <state>
	else if (word.type == LEFT_BRACKET) {
		getWord();
		mStatementSeq(set<int>{RIGHT_BRACKET}, functionIndex);
		//template {}
	} else if (word.type == SWITCH) mSwitchStatement(set<int>{RIGHT_BRACKET}, functionIndex);
	//template switch{}
	else if (word.type == SCANF) mScanfStatement(set<int>{SEMI_COLON});
	//template scanf();
	else if (word.type == PRINTF) mPrintfStatement(set<int>{SEMI_COLON});
	//template printf();
	else if (word.type == RETURN) mReturnStatement(set<int>{SEMI_COLON}, functionIndex);
	//template return(1); | return;
	else if (word.type == SEMI_COLON);
	//template ;
	else if (word.type == IDENTIFIER) {
		//call/assign
		Word temword = word;
		getWord();
		int idx = symbolTable.getIndexFromWord(temword);//report error when necessary
		if (word.type == LEFT_PARENTHESIS) mCallStatement(set<int>{SEMI_COLON}, idx);
		else if (word.type == ASSIGN || word.type == LEFT_SQUARE_BRACKET) {
			mAssignStatement(set<int>{SEMI_COLON}, idx);
		} else error.invoke(lineNumber, cursorIndex, UNEXPECTED_SYMBOL);
	} else error.invoke(lineNumber, cursorIndex, UNEXPECTED_SYMBOL);
}

void mCondition(set<int> terminateToken) {
	//must start with '('
	if (word.type == LEFT_PARENTHESIS) getWord();
	set<int> compareOpreators = set<int>{ LESS, GREATER, LESS_EQUAL, GREATER_EQUAL, EQUAL, NOT_EQUAL };
	mExp(cmb(terminateToken, compareOpreators));
	vector<pii> &stk = mCode.tempOperandStack;
	pii lhs, rhs;
	if(stk.size()) lhs = stk[stk.size() - 1];
	if (word.type == LESS) {
		getWord();
		mExp(terminateToken);
		stk = mCode.tempOperandStack;
		if (stk.size()) rhs = stk[stk.size() - 1];
		int nexId = mCode.getNextAllocatable();
		mCode.emit(LES, mCode.getTempStringByIdx(nexId),
			mCode.getTempStringByIdx(lhs.first), mCode.getTempStringByIdx(rhs.first));
		if (stk.size()) stk.pop();
		if (stk.size()) stk.pop();
		stk.pb(mp(nexId, INT));
		//mCode.emit(LSS);
	} else if (word.type == GREATER) {
		getWord();
		mExp(terminateToken);
		stk = mCode.tempOperandStack;
		if (stk.size()) rhs = stk[stk.size() - 1];
		int nexId = mCode.getNextAllocatable();
		mCode.emit(GRT, mCode.getTempStringByIdx(nexId),
			mCode.getTempStringByIdx(lhs.first), mCode.getTempStringByIdx(rhs.first));
		if (stk.size()) stk.pop();
		if (stk.size()) stk.pop();
		stk.pb(mp(nexId, INT));
		//mCode.emit(GRT);
	} else if (word.type == LESS_EQUAL) {
		getWord();
		mExp(terminateToken);
		stk = mCode.tempOperandStack;
		if (stk.size()) rhs = stk[stk.size() - 1];
		int nexId = mCode.getNextAllocatable();
		mCode.emit(LEQ, mCode.getTempStringByIdx(nexId),
			mCode.getTempStringByIdx(lhs.first), mCode.getTempStringByIdx(rhs.first));
		if (stk.size()) stk.pop();
		if (stk.size()) stk.pop();
		stk.pb(mp(nexId, INT));
		//mCode.emit(LER);
	} else if (word.type == GREATER_EQUAL) {
		getWord();
		mExp(terminateToken);
		stk = mCode.tempOperandStack;
		if (stk.size()) rhs = stk[stk.size() - 1];
		int nexId = mCode.getNextAllocatable();
		mCode.emit(GEQ, mCode.getTempStringByIdx(nexId),
			mCode.getTempStringByIdx(lhs.first), mCode.getTempStringByIdx(rhs.first));
		if (stk.size()) stk.pop();
		if (stk.size()) stk.pop();
		stk.pb(mp(nexId, INT));
		//mCode.emit(GEQ);
	} else if (word.type == EQUAL) {
		getWord();
		mExp(terminateToken);
		stk = mCode.tempOperandStack;
		if (stk.size()) rhs = stk[stk.size() - 1];
		int nexId = mCode.getNextAllocatable();
		mCode.emit(EQL, mCode.getTempStringByIdx(nexId),
			mCode.getTempStringByIdx(lhs.first), mCode.getTempStringByIdx(rhs.first));
		if (stk.size()) stk.pop();
		if (stk.size()) stk.pop();
		stk.pb(mp(nexId, INT));
		//mCode.emit(EQL);
	} else if (word.type == NOT_EQUAL) {
		getWord();
		mExp(terminateToken);
		stk = mCode.tempOperandStack;
		if (stk.size()) rhs = stk[stk.size() - 1];
		int nexId = mCode.getNextAllocatable();
		mCode.emit(NEQ, mCode.getTempStringByIdx(nexId),
			mCode.getTempStringByIdx(lhs.first), mCode.getTempStringByIdx(rhs.first));
		if (stk.size()) stk.pop();
		if (stk.size()) stk.pop();
		stk.pb(mp(nexId, INT));
		//mCode.emit(NEQ);
	} else verify(terminateToken, word, UNEXPECTED_SYMBOL);
}

void mIfStatement(int functionIndex) {
	getWord();
	verify(set<int>{LEFT_PARENTHESIS}, word, LEFT_PARENTHESIS_EXPECTED);
	mCondition(set<int>{RIGHT_PARENTHESIS});
	if (word.type == RIGHT_PARENTHESIS) getWord();
	vector<pii> &stk = mCode.tempOperandStack;
	string topStr = string("");
	if (stk.size()) topStr = mCode.getTempStringByIdx(stk[stk.size() - 1].first);
	if(stk.size()) stk.pop();
	int branchCodeIndex = mCode.emit(JPC, topStr, numToString(0));
	mStatement(functionIndex);
	//you should take the last spliter
	if (branchCodeIndex >= 0 && branchCodeIndex < mCode.code.size()) {
		mCode.code[branchCodeIndex].operand2 = numToString(mCode.getNextCodeAddress());
	}
}

void mWhileStatement(int functionIndex) {
	int label1 = mCode.getNextCodeAddress();
	getWord();
	verify(set<int>{LEFT_PARENTHESIS}, word, LEFT_PARENTHESIS_EXPECTED);
	mCondition(set<int>{RIGHT_PARENTHESIS});
	if (word.type == RIGHT_PARENTHESIS) getWord();
	vector<pii> &stk = mCode.tempOperandStack;
	string topStr = string("");
	if (stk.size()) topStr = mCode.getTempStringByIdx(stk[stk.size() - 1].first);
	int branchCodeIndex = mCode.emit(JPC, topStr, numToString(0));
	if(stk.size()) stk.pop();
	mStatement(functionIndex);
	mCode.emit(JMP, numToString(label1));
	if (branchCodeIndex >= 0 && branchCodeIndex < mCode.code.size()) {
		mCode.code[branchCodeIndex].operand2 = numToString(mCode.getNextCodeAddress());
	}
}

void mSwitchStatement(set<int>terminateToken, int functionIndex) {
	/********************************************
	switch(<exp>) {<caseItemList> <default>}
	<caseItemList> ::= <caseItem>{<caseItem>}
	<caseItem> ::= case <constant> : <statement>
	<default> ::= default : <statemnt> | <null>
	*********************************************/
	//switch already taken
	getWord();
	verify(set<int>{LEFT_PARENTHESIS}, word, LEFT_PARENTHESIS_EXPECTED);
	if (word.type == LEFT_PARENTHESIS) getWord();
	mExp(set<int>{RIGHT_PARENTHESIS});
	vector<pii> &stk = mCode.tempOperandStack;
	int stkTopIdx = 0;
	if (stk.size()) stkTopIdx = stk[stk.size() - 1].first;
	if(stk.size()) stk.pop();

	int switchCodeIndex = mCode.emit(JMP, numToString(0));
	if (word.type == RIGHT_PARENTHESIS) getWord();
	verify(set<int>{LEFT_BRACKET}, word, LEFT_BRACKET_EXPECTED);
	if (word.type == LEFT_BRACKET) getWord();
	verify(set<int>{CASE}, word, CASE_EXPECTED);
	SymbolTable::CaseTable &ctb = symbolTable.newCaseTable();
	mCaseItem(functionIndex, ctb);
	getWord();
	while (word.type == CASE) mCaseItem(functionIndex, ctb), getWord();
	verify(set<int>{DEFAULT}, word, DEFAULT_EXPECTED);
	pii defaultAddress = mDefaultItem(terminateToken, functionIndex, ctb);

	int nexCode = mCode.getNextCodeAddress();
	if (switchCodeIndex >= 0 && switchCodeIndex < mCode.code.size()) {
		mCode.code[switchCodeIndex].operand1 = numToString(nexCode);
	}

	//set switch table
	//CAS is pesudocode which cannot be executed

	//omit it

	/******************************************
	��SWT y
	y:
	CAS value1
	CAS addr1
	CAS value2
	CAS addr2
	...
	JMP defaddr
	addr1/addr2/..defaddr:
	....
	JMP exitaddr(in case not default)
	********************************************/
	ctb.emitCaseCode(stkTopIdx);
	mCode.emit(JMP, numToString(defaultAddress.first));
	nexCode = mCode.getNextCodeAddress();
	if (defaultAddress.second >= 0 && defaultAddress.second < mCode.code.size()) {
		mCode.code[defaultAddress.second].operand1 = numToString(nexCode);
	}
	ctb.fillExitAddress(nexCode);
}

void mCaseItem(int functionIndex, SymbolTable::CaseTable& ctb) {
	//'case' taken
	//<caseItem> ::= case <constant> : <statement>
	getWord();
	pii temConst = mConstant(set<int>{COLON});
	if (ctb.checkDuplicate(temConst.first)) {
		error.invoke(lineNumber, cursorIndex, CASE_DUPLICATE);
	}
	if (word.type == COLON) getWord();
	int nexCode = mCode.getNextCodeAddress();
	int caseTableIndex = ctb.pushCaseItem(temConst.first, nexCode);
	mStatement(functionIndex);
	int jumpIndex = mCode.emit(JMP, numToString(0));
	if (caseTableIndex >= 0 && caseTableIndex < ctb.caseTable.size()) {
		ctb.caseTable[caseTableIndex].codeIndex = jumpIndex;
	}
}


pii mDefaultItem(set<int> terminateToken, int functionIdx, SymbolTable::CaseTable& ctb) {
	//'default' taken
	//return pair<entranceAddr, exitAddr>
	getWord();
	verify(set<int>{COLON}, word, COLON_EXPECTED);
	if (word.type == COLON) getWord();
	int nexCode = mCode.getNextCodeAddress();
	if (word.type != RIGHT_BRACKET) mStatement(functionIdx), getWord();
	int exitCode = mCode.emit(JMP, numToString(0));
	verify(terminateToken, word, RIGHT_BRACKET_EXPECTED);
	return mp(nexCode, exitCode);
}

pii mConstant(set<int> terminateToken) {
	//pair<value, type>
	//return constant value, perhaps not into symbolTable
	//only CHARACTER OR NUMBER EXPECTED
	verify(set<int>{CHARACTER, PLUS, MINUS, UNSIGNED_NUMBER}, word, UNEXPECTED_SYMBOL);
	int value = 0;
	int type = INT;
	if (word.type == CHARACTER) {
		value = word.wordString[0];
		type = CHAR;
		getWord();
	} else if (word.type == UNSIGNED_NUMBER) {
		value = word.wordValue;
		getWord();
	} else if (word.type == PLUS || word.type == MINUS) {
		bool neg = word.type == MINUS;
		getWord();
		verify(set<int>{UNSIGNED_NUMBER}, word, UNSIGNED_NUMBER_EXPECTED);
		if (word.type == UNSIGNED_NUMBER) value = word.wordValue;
		if (neg) value = -value;
		getWord();
	}
	verify(terminateToken, word, UNEXPECTED_SYMBOL);
	return mp(value, type);
}

void mScanfStatement(set<int> terminateToken) {
	/***************************************
	scanf(<ident> {, <ident>})
	****************************************/
	//scanf taken
	getWord();
	verify(set<int>{LEFT_PARENTHESIS}, word, LEFT_PARENTHESIS_EXPECTED);
	getWord();
	verify(set<int>{IDENTIFIER}, word, IDENTIFIER_EXPECTED);
	if (word.type == IDENTIFIER) {
		int idx = symbolTable.getIndexFromWord(word);
		if (!idx) error.invoke(lineNumber, cursorIndex, IDENTIFIER_UNDECLARED);
		else {
			SymbolTable::TableItem &item = symbolTable.getTableItem(idx);
			if (item.modifier != VARIABLE || item.type != INT && item.type != CHAR) {
				error.invoke(lineNumber, cursorIndex, WRONG_SCANF_FORMAT);
			} else {
				mCode.emit(item.type == INT ? READ : READC, string(&(item.name[0])));
			}
		}
		getWord();
	}
	while (word.type == COMMA) {
		getWord();
		verify(set<int>{IDENTIFIER}, word, IDENTIFIER_EXPECTED);
		if (word.type == IDENTIFIER) {
			int idx = symbolTable.getIndexFromWord(word);
			if (!idx) error.invoke(lineNumber, cursorIndex, IDENTIFIER_UNDECLARED);
			else {
				SymbolTable::TableItem &item = symbolTable.getTableItem(idx);
				if (item.modifier != VARIABLE || item.type != INT && item.type != CHAR) {
					error.invoke(lineNumber, cursorIndex, WRONG_SCANF_FORMAT);
				} else {
					mCode.emit(item.type == INT ? READ : READC, string(&(item.name[0])));
				}
			}
			getWord();
		}
	}
	verify(set<int>{RIGHT_PARENTHESIS}, word, RIGHT_PARENTHESIS_EXPECTED);
	if (word.type == RIGHT_PARENTHESIS) getWord();
	verify(terminateToken, word, SEMI_COLON_EXPECTED);
}

void mPrintfStatement(set<int> terminateToken) {
	/*******************************************
	printf(<string>, <exp>)
	printf(<string>)
	printf(<exp>)
	********************************************/
	getWord();
	verify(set<int>{LEFT_PARENTHESIS}, word, LEFT_PARENTHESIS_EXPECTED);
	if (word.type == LEFT_PARENTHESIS) getWord();
	if (word.type == STRING) {
		//TODO : handle string
		int idx = symbolTable.pushNewString(word);
		mCode.emit(WRITES, numToString(idx));
		getWord();
		if (word.type == COMMA) {
			getWord();
			mExp(set<int>{RIGHT_PARENTHESIS});
			vector<pii> &stk = mCode.tempOperandStack;
			pii value = mp(0, 0);
			if (stk.size()) value = stk[stk.size() - 1];
			mCode.emit(value.second == CHAR ? WRITEC : WRITE, mCode.getTempStringByIdx(value.first));
			if (word.type == RIGHT_PARENTHESIS) getWord();
		} else if (word.type == RIGHT_PARENTHESIS) getWord();
	} else {
		mExp(set<int>{RIGHT_PARENTHESIS});
		vector<pii> &stk = mCode.tempOperandStack;
		pii value = mp(0, 0);
		if (stk.size()) value = stk[stk.size() - 1];
		mCode.emit(value.second == CHAR ? WRITEC : WRITE, mCode.getTempStringByIdx(value.first));
		if (word.type == RIGHT_PARENTHESIS) getWord();
	}
	verify(terminateToken, word, SEMI_COLON_EXPECTED);
}

void mReturnStatement(set<int> terminateToken, int functionIndex) {
	//template :: return; | return (<exp>);
	SymbolTable::TableItem &tb = symbolTable.getTableItem(functionIndex);
	SymbolTable::BranchTableItem &btb = symbolTable.getBranchItem(tb.ref);
	//return taken
	getWord();
	if (tb.type == VOID) {
		verify(set<int>{SEMI_COLON}, word, SEMI_COLON_EXPECTED);
		mCode.emit(EXF);
	} else {
		verify(set<int>{LEFT_PARENTHESIS}, word, LEFT_PARENTHESIS_EXPECTED);
		getWord();
		mExp(set<int>{RIGHT_PARENTHESIS});
		if (word.type == RIGHT_PARENTHESIS) {
			getWord();
			verify(set<int>{SEMI_COLON}, word, SEMI_COLON_EXPECTED);
		}
		vector<pii> &stk = mCode.tempOperandStack;
		if (stk.size()) {
			mCode.emit(RETV, mCode.getTempStringByIdx(stk[stk.size() - 1].first));
		}
		if(stk.size()) stk.pop();
		mCode.emit(EXF);
		//???? ret the S[$top], to the called address
	}
}

void mAssignStatement(set<int>terminateToken, int identIdx) {
	//assert :: word == '=' or '['
	SymbolTable::TableItem &tb = symbolTable.getTableItem(identIdx);

	verify(set<int>{ASSIGN, LEFT_SQUARE_BRACKET}, word, UNEXPECTED_SYMBOL);
	if (word.type == ASSIGN) {
		if (tb.isArray) error.invoke(lineNumber, cursorIndex, ASSIGN_TO_ARRAY);
		//intermdediateCode.emit(LDA, 0);//what's the address of left opreand?
		getWord();
		mExp(set<int>{SEMI_COLON});
		//intermdediateCode.emit(STO);
		vector<pii> &stk = mCode.tempOperandStack;
		mCode.emit(ASG, string(&(tb.name[0])), mCode.getTempStringByIdx(stk[stk.size() - 1].first));
		if(stk.size()) stk.pop();
	} else if (word.type == LEFT_SQUARE_BRACKET) {
		if (!tb.isArray) {
			error.invoke(lineNumber, cursorIndex, SELECT_NON_ARRAY);
		}
		selector(set<int>{RIGHT_SQUARE_BRACKET}, tb);
		if (word.type == RIGHT_SQUARE_BRACKET) getWord();
		verify(set<int>{ASSIGN}, word, ASSIGN_EXPECTED);
		vector<pii> &stk = mCode.tempOperandStack;
		if (word.type == ASSIGN) getWord();
		int idx2 = 0;
		if (stk.size()) {
			idx2 = stk[stk.size() - 1].first;
			stk.pop();
		}
		//mCode.emit(LDA, 0);//what's the address of left opreand?
		mExp(set<int>{SEMI_COLON});
		stk = mCode.tempOperandStack;
		int idx3 = 0;
		if (stk.size()) {
			idx3 = stk[stk.size() - 1].first;
			stk.pop();
		}
		mCode.emit(ASTO, string(&(tb.name[0])), mCode.getTempStringByIdx(idx2), mCode.getTempStringByIdx(idx3));
		//mCode.emit(STO);
	}
}

void mStatementSeq(set<int> terminateToken, int functionIndex) {
	//template {<state>}, note you should read ahead, that's to read the outsider one(just one)
	//fisrt word already taken
	while (statementBeginSymbols.find(word.type) != statementBeginSymbols.end()) {
		mStatement(functionIndex);
		if (word.type == SEMI_COLON || word.type == RIGHT_BRACKET) getWord();
	}
	verify(terminateToken, word, RIGHT_BRACKET_EXPECTED);
}

void mProsdure() {
	//note: a word already fetched
	if (word.type == CONST) {
		mGlobalConstantDecBlock();
		if (word.type == SEMI_COLON) getWord();
	}
	verify(set<int>{VOID, CHAR, INT}, word, UNEXPECTED_SYMBOL);
	int type = word.type;
	bool hasMain = false;
	int idx;
	if (type == INT || type == CHAR) {
		getWord();
		verify(set<int>{IDENTIFIER}, word, IDENTIFIER_EXPECTED);
		idx = symbolTable.pushItem(word, true);
		if (word.type == IDENTIFIER) getWord();
		verify(set<int>{COMMA, SEMI_COLON, LEFT_SQUARE_BRACKET, LEFT_PARENTHESIS}, word, UNEXPECTED_SYMBOL);
		if (word.type != LEFT_PARENTHESIS) {
			//in global var decalre block
			while (word.type != LEFT_PARENTHESIS) {
				if (idx >= 0 && idx < symbolTable.table.size()) {
					symbolTable.table[idx].modifier = VARIABLE;
					symbolTable.table[idx].type = type;
				}
				mGlobalVarDec(set<int>{SEMI_COLON}, idx);
				if (word.type == SEMI_COLON) getWord();
				if (word.type != CHAR && word.type != INT) break;
				type = word.type;
				getWord();
				if (word.type != IDENTIFIER) {
					error.invoke(lineNumber, cursorIndex, IDENTIFIER_EXPECTED);
					break;
				}
				//cannot crash
				idx = symbolTable.pushItem(word, true);
				symbolTable.table[idx].type = type;
				symbolTable.curFunctionIdexInTable = idx;
				getWord();
				verify(set<int>{COMMA, SEMI_COLON, LEFT_SQUARE_BRACKET, LEFT_PARENTHESIS}, word, UNEXPECTED_SYMBOL);
			}
		}
	}

	//word be VOID or (
	if (word.type == LEFT_PARENTHESIS) {
		if (idx >= 0 && idx < symbolTable.table.size()) {
			symbolTable.table[idx].modifier = FUNCTION;
		}
		if (!cmp(symbolTable.table[idx].name, vector<char>{'m', 'a', 'i', 'n', '\0'})) hasMain = true;
		//from parameter, namely (,,,){}
		mFunctBlock(set<int>{RIGHT_BRACKET}, type, idx, hasMain);
		if (word.type == RIGHT_BRACKET && !hasMain) getWord();
		mCode.emit(EXF);
		/*****************************************
		return to the place you marked in stack S.
		******************************************/
		symbolTable.exitBlockPopTable(idx);
	}

	if (hasMain) return;

	//main cannot be called
	//main should be void
	//main contains no paras
	verify(set<int>{VOID, INT, CHAR}, word, UNEXPECTED_SYMBOL);
	while (word.type == VOID || word.type == CHAR || word.type == INT) {
		int type = word.type;
		getWord();
		bool hasMain = word.type == MAIN;
		if (word.type != MAIN && word.type != IDENTIFIER) {
			error.invoke(lineNumber, cursorIndex, IDENTIFIER_EXPECTED);
			cpy(word.wordString, vector<char>{'F', 'C', 'T', '\0'});
		}
		//ident(,,,){}
		mFunctDec(set<int>{RIGHT_BRACKET}, type, hasMain);
		if (hasMain) return;
		else getWord();
	}
	error.invoke(lineNumber, cursorIndex, MAIN_EXPECTED);
	//TODO...
}

int main() {
	int debug = 0;
	inputHandle();
	//freopen("out.txt", "w", stdout);
	if (!debug) freopen("out.txt", "w", stdout);
	getWord();
	mProsdure();
	if (error.errorCounter) exit(0);
	mCode.flush();
	if (!debug) freopen("obj.txt", "w", stdout);
	oCode.genObjCode();
	return 0;
}
