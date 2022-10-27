#include <iostream>
#include<string>
#include<vector>
#include<stack>
#include<sstream>
#include<queue>
#include<algorithm>
#include <fstream>
using namespace std;
bool is_dig(char a) {
	return (a <= '9' && a >= '0') || a=='.'|| a == '-';
}
bool is_numb(string a) {
	if (a[0] == '.')return false;
	for (auto i : a) {
		if (!is_dig(i))return false;
	}
	return true;
}
bool is_char(char a) {
	return a <= 'z' && a>='a';
}
//real code :)
double string_to_int(string off) {
	stringstream geek(off);
	double x = 0;
	geek >> x;
	return x;
}
int str_to_int(string off) {
	stringstream geek(off);
	int x = 0;
	geek >> x;
	return x;
}

struct reader {
private:
	string input;
	//1.)razdelqme inputa 
	//2.)xd pushvame vs token
	   // 2.1)push na xd koqto ako vidi zatv token popva dokato vidi otv
	   // 2.2)evaluate() -- s razl klasove ili funkcii
	  //  2.3) vs elementi gi pushvame v steka
	 // 3.)i output prosto
	  //4.) writer
public:
	reader(string constru) {
		input = constru;
	}
	vector<string> chop() {
		int i = 0;
		vector<string> output;
		while (input[i] != '\0') {
			string temp="";
			if (input[i] == '<') {
				i++;
				while (input[i] != '>') {
					temp.push_back(input[i]);
					i++;
				}
			}
			else if (is_dig(input[i])) {
				while (is_dig(input[i])) {
					temp.push_back(input[i]);
					i++;
				}
				i--;
			}
			output.push_back(temp);
			i++;
		}

		return clear_empty_cells(output);
	}
	vector<string> separate_arguments() {
		vector<string> to_separate = chop();
		vector<string> output;
		for (auto i : to_separate) {
			if (is_numb(i)) {
				output.push_back(i);
			}
			else if (no_arguments(i)) {
				output.push_back(i);
			}
			else {
				if (i.size() == 7) {
					cout << "ERROR: MISSING ARGUMENT FOR " << i;
					exit(1);
				}
				if (i[0] == 'M' && i[1] == 'A' && i[2] == 'P') {
					string arg = (get_arg(i));
					for (auto i : arg) {
						if (!is_dig(i)) {
							cout << "ERROR: INVALID MAP ARGUMENT";
							exit(1);
						}
					}
				}
				else if (i[0] == 'S' && i[1] == 'R' && i[2] == 'T' &&
					i[3] == '-' && i[4] == 'O' && i[5] == 'R' && i[6] == 'D') {
					string arg = (get_arg(i));
					if (arg != "ASC" && arg != "DSC") {
						cout << "ERROR: INVALID SRT ARGUMENT";
						exit(1);
					}
				}
				
				output.push_back(get_tag(i));
				output.push_back(get_arg(i));
			}
			
		}
		return output;

	}
	vector<string> tokenize() {
		vector<string> toki = separate_arguments();
		vector<string> output;
		for (auto i : toki) {
			output.push_back(token_if(i));
		}
		return output;
	}
	vector<string> clear_empty_cells(vector<string> jk) {
		for (unsigned int i = 0; i < jk.size(); i++) {
			if(jk[i] == "")jk.erase(jk.begin() + i);
		}
		return jk;
	}
	bool no_arguments(string to_bool) {
		to_bool.erase(to_bool.begin()+7, to_bool.end());
		return to_bool != "MAP-INC" && to_bool != "MAP-MLT" && to_bool != "SRT-SLC" && to_bool != "SRT-ORD";
	}
	string get_arg(string str) {
		str.erase(str.begin(), str.begin() + 7);
		str.erase(str.begin());
		str.erase(str.begin());
		str.erase(str.end()-1);
		return str;
	}
	string get_tag(string str) {
		str.erase(str.begin() + 7, str.end());
		return str;
	}
	string token_if(string to_if) {
		if (to_if == "SRT-DST") return "dst";
		else if (to_if == "/SRT-DST") return ".dst";

		else if (to_if == "AGG-SUM") return "sum";
		else if (to_if == "/AGG-SUM") return ".sum";

		else if (to_if == "AGG-PRO") return "pro";
		else if (to_if == "/AGG-PRO") return ".pro";

		else if (to_if == "AGG-AVG") return "avg";
		else if (to_if == "/AGG-AVG") return ".avg";

		else if (to_if == "AGG-FST") return "fst";
		else if (to_if == "/AGG-FST") return ".sst";

		else if (to_if == "AGG-LST") return "lst";
		else if (to_if == "/AGG-LST") return ".lst";

		else if (to_if == "SRT-REV") return "rev";
		else if (to_if == "/SRT-REV") return ".rev";

		else if (to_if == "MAP-INC") return "inc";
		else if (to_if == "/MAP-INC") return ".inc";

		else if (to_if == "MAP-MLT") return "mlt";
		else if (to_if == "/MAP-MLT") return ".mlt";

		else if (to_if == "SRT-ORD") return "ord";
		else if (to_if == "/SRT-ORD") return ".ord";

		else if (to_if == "SRT-SLC") return "slc";
		else if (to_if == "/SRT-SLC") return ".slc";

		else if (to_if == "ASC") return "asc";
		else if (to_if == "DSC") return "dsc";

		else if (is_numb(to_if) || to_if[0] == '-') return to_if;
		cout << "ERROR:\"" << to_if << "\" TAG DOES NOT EXISTS"; exit(1);
	}

};
struct stack_tag {
private:
	stack<string> s1;
public:
	bool is_opentag(string input) {
		if (input == "inc")return true;
		else if (input == "mlt")return true;
		else if (input == "sum")return true;
		else if (input == "pro")return true;
		else if (input == "avg")return true;
		else if (input == "fst")return true;
		else if (input == "lst")return true;
		else if (input == "rev")return true;
		else if (input == "ord")return true;
		else if (input == "asc")return true;
		else if (input == "dsc")return true;
		else if (input == "dst")return true;
		else if (input == "slc")return true;
		else return false;
	}
	bool is_negative(string input) {
		return input[0] == '-' ;
	}

	void push(string input) { //(edin token)
		if (is_numb(input) || is_opentag(input) || is_negative(input)) {
			//cout << input << endl;
			s1.push(input);
		}
		else if (input[0] == '.') {
			string remember_tag = input;
			remember_tag.erase(remember_tag.begin());
			stack<string> to_calculate;
			while (is_numb(s1.top()) || is_negative(s1.top())) {
				to_calculate.push(s1.top());
				s1.pop();
			}
			vector<string> calculated_push;
			//cout << s1.top() << " " << remember_tag<<endl;
			if (s1.top() == "inc" && remember_tag == s1.top()) {
				s1.pop();
				calculated_push = calculate_inc(to_calculate);
			}
			else if (s1.top() == "mlt" && remember_tag == s1.top()) {
				s1.pop();
				calculated_push = calculate_mlt(to_calculate);
				
			}
			else if (s1.top() == "sum" && remember_tag == s1.top()) {
				s1.pop();
				calculated_push = calculate_sum(to_calculate);

			}
			else if (s1.top() == "pro" && remember_tag == s1.top()) {
				s1.pop();
				calculated_push = calculate_pro(to_calculate);

			}
			else if (s1.top() == "avg" && remember_tag == s1.top()) {
				s1.pop();
				calculated_push = calculate_avg(to_calculate);

			}
			else if (s1.top() == "fst" && remember_tag == s1.top()) {
				s1.pop();
				calculated_push = calculate_fst(to_calculate);

			}
			else if (s1.top() == "lst" && remember_tag == s1.top()) {
				s1.pop();
				calculated_push = calculate_lst(to_calculate);

			}
			else if (s1.top() == "rev" && remember_tag == s1.top() ) {
				s1.pop();
				calculated_push = calculate_rev(to_calculate);

			}
			else if ((s1.top() == "asc" || s1.top() == "dsc") && remember_tag == "ord") {
				to_calculate.push(s1.top());
				s1.pop();
				s1.pop();
				calculated_push = calculate_ord(to_calculate);
			}
			else if (s1.top() == "dst" && remember_tag == s1.top()) {
				s1.pop();
				calculated_push = calculate_dst(to_calculate);

			}
			else if (s1.top() == "slc" && remember_tag == s1.top()) {
				s1.pop();
				calculated_push = calculate_slc(to_calculate);
			}
			else {
				cout << "ERROR: NOT BALANCED TAGS"<<endl;
				exit(1);
			}
			for (auto &i : calculated_push) {
				s1.push(i);
			}
		}
	}
	vector<string> calculate_inc(stack<string> numbers) {
		double argument = string_to_int(numbers.top());
		numbers.pop();
		vector<double> container;
		while (!numbers.empty()) {
			container.push_back(string_to_int(numbers.top()));
			numbers.pop();
		}
		vector<string> string_container;
		for (auto i : container) {
			i = i + argument;
			string_container.push_back(to_string(i));
		}
		return string_container;
	}
	vector<string> calculate_mlt(stack<string> numbers) {
		double argument = (string_to_int(numbers.top()));
		numbers.pop();
		vector<double> container;
		while (!numbers.empty()) {
			container.push_back(string_to_int(numbers.top()));
			numbers.pop();
		}
		vector<string> string_container;
		for (auto i : container) {
			i = i * argument;
			string_container.push_back(to_string(i));
		}
		return string_container;
	}
	vector<string> calculate_sum(stack<string> numbers) {
		double sum=0;
		while (!numbers.empty()) {
			sum=sum+(string_to_int(numbers.top()));
			numbers.pop();
		}
		vector<string> string_container;
		string_container.push_back(to_string(sum));
		return string_container;
	}
	vector<string> calculate_pro(stack<string> numbers) {
		double pro = 1;
		while (!numbers.empty()) {
			pro = pro * (string_to_int(numbers.top()));
			numbers.pop();
		}
		vector<string> string_container;
		string_container.push_back(to_string(pro));
		return string_container;
	}
	vector<string> calculate_avg(stack<string> numbers) {
		double sum = 0;
		int counter = 0;
		while (!numbers.empty()) {
			sum = sum + (string_to_int(numbers.top()));
			counter++;
			numbers.pop();
		}
		sum = sum / counter;
		vector<string> string_container;
		string_container.push_back(to_string(sum));
		return string_container;
	}
	vector<string> calculate_fst(stack<string> numbers) {
		vector<string> string_container;
		string_container.push_back(numbers.top());
		return string_container;
	}
	vector<string> calculate_lst(stack<string> numbers) {
		double temp;
		while (!numbers.empty()) {
			temp =(string_to_int(numbers.top()));
			numbers.pop();
		};
		vector<string> string_container;
		string_container.push_back(to_string(temp));
		return string_container;
	}
	vector<string> calculate_rev(stack<string> numbers) {
		stack<string> help_steck;
		while (!numbers.empty()) {
			help_steck.push(numbers.top());
			numbers.pop();
		};
		vector<string> string_container;
		while (!help_steck.empty()) {
			string_container.push_back(help_steck.top());
			help_steck.pop();
		}
		return string_container;
	}
	vector<string> calculate_ord(stack<string> numbers) {
		string argument = numbers.top();
		numbers.pop();
		vector<double> container;
		while (!numbers.empty()) {
			container.push_back(string_to_int(numbers.top()));
			numbers.pop();
		}
		if (argument == "asc") {
			sort(container.begin(), container.end());
		}
		else {
			sort(container.begin(), container.end());
			reverse(container.begin(), container.end());
		}
		vector<string> string_container;
		for (auto i : container) {
			string_container.push_back((to_string(i)));
		}
		return string_container;
	}
	vector<string> calculate_dst(stack<string> numbers) {
		vector<string> help_vector;
		while (!numbers.empty()) {
			help_vector.push_back(numbers.top());
			numbers.pop();
		};
		vector<string> new_vec;
		int sizee = help_vector.size();
		reverse(help_vector.begin(), help_vector.end()); // zashtoto zapazva poslednoto sreshtane
		for (int i = 0; i < sizee; i++) {
			bool check = false;
			for (int j = i + 1; j < sizee; j++) {
				if (help_vector[j] == help_vector[i])
					check = true;
			}
			if (!check) {
				new_vec.push_back(help_vector[i]);
			}
		}
		reverse(new_vec.begin(), new_vec.end());// zashtoto zapazva poslednoto sreshtane

		return new_vec;
	}
	vector<string> calculate_slc(stack<string> numbers) {
		int argument = (str_to_int(numbers.top()));
		numbers.pop();
		vector<double> container;
		int counter = 0;
		while (!numbers.empty()) {
			container.push_back(string_to_int(numbers.top()));
			counter++;
			numbers.pop();
		}
		if (argument > counter) {
			cout << "ERROR: ARGUMENT FOR SLC TOO BIG";
			exit(1);
		}
		vector<string> string_container;
		for (unsigned int j = argument; j < container.size(); j++) {
			string_container.push_back(to_string(container[j]));
		}
		return string_container;
	}

	void print(ostream& os) {
		vector <string> to_print;
		while (!s1.empty()) {
			to_print.push_back(s1.top());
			s1.pop();
		}
		reverse(to_print.begin(), to_print.end());
		for (auto& i : to_print) {
			os << string_to_int(i) << " ";
		}
	}

};
//TO DO


//failove


int main(){
	string input, output,text;
	cin >> input;
	cin >> output;
	ifstream ReadFile(input);
	ofstream WriteFile(output);
	while (getline(ReadFile, text)) {
		//cout << text;
	}
	ReadFile.close();
	reader reader(text);
	vector <string> L = reader.tokenize();
	stack_tag nqkaksi;
	for (auto& i : L) {
		nqkaksi.push(i);
	}
	nqkaksi.print(WriteFile);
	WriteFile.close();


	//reader reader("<SRT-ORD \"ASC\">81 3 <MAP-INC \"1\"> 4 12 55 <AGG-AVG> 4 8</AGG-AVG> </MAP-INC> 22 </SRT-ORD>");
	/*reader reader("<SRT-DST> <SRT-SLC \"3\">57 18 9 <MAP-INC \"-3.5\"> 4 2 2 </MAP-INC> 5 </SRT-SLC></SRT-DST>");
	vector <string> L = reader.tokenize();
	stack_tag nqkaksi;
	for (auto& i : L) {
		nqkaksi.push(i);
	}
	nqkaksi.print();
	*/
	//for (auto& i : L) {
	//	cout << i<<endl;
	//}

	/*
	L.push_back("sort");
	L.push_back("asc");
	L.push_back("81");
	L.push_back("3");
	L.push_back("inc");
	L.push_back("1");
	L.push_back("4");
	L.push_back("12");
	L.push_back("55");
	L.push_back("avg");
	L.push_back("4");
	L.push_back("8");
	L.push_back(".avg");
	L.push_back(".map");
	L.push_back("22");
	L.push_back(".sort");
	
	//<SRT - DST> < SRT - SLC "3">57 18 9 < MAP - INC "-3" > 4 2 2 < / MAP - INC > 5 < / SRT - SLC > < / SRT - DST>
	L.push_back("dst");
	L.push_back("slc");
	L.push_back("3");
	L.push_back("57");
	L.push_back("18");
	L.push_back("9");
	L.push_back("mlt");
	L.push_back("-3");
	L.push_back("4");
	L.push_back("2");
	L.push_back("2");
	L.push_back(".inc");
	L.push_back("5");
	L.push_back(".slc");
	L.push_back(".dst");
	
	xd nqkaksi;
	for (auto i : L) {
		nqkaksi.push(i);
	}
	nqkaksi.print();
	*/

	//cout << fix("<MAP-INC`111`>1 2 3</MAP-INC>");
	//< MAP - INC`-10`> 1 2 3
	//<SRT-ORD"ASC">81 3 <MAP-INC"1"> 4 12 55 <AGG-AVG> 4 8 </AGG-AVG> </MAP-INC> 22 </SRT-ORD> ->asdasd-> `( )
	//asc 81 3 inc1 4 12 55 6 

	//cout <<fix("<SRT-DST><SRT-SLC `3`>57 18 9<MAP-INC `-3`>4 2 2</MAP-INC>5</SRT-SLC></SRT-DST>");
	

	
	// 81 3 5 13 56 7 22
	// 3 5 7 13 22 56 81


	//<SRT-DST><SRT-SLC"3">57 18 9 <MAP-INC"-3"> 4 2 2 </MAP-INC> 5 </SRT-SLC> </SRT-DST>
	//1 -1 5

	return 0;
}




//

//<SRT-ORD"ASC">81 3<MAP-INC "1">4 12 55<AGG-AVG>4 8</AGG-AVG></MAP-INC>22 </SRT-ORD>