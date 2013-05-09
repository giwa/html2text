#include <iostream>
#include <string>
#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


using namespace std;

enum {HTML_FIRST, HTML_MID};


int SearchHtmlTag(const char *html, int offset, int *condition){
	int i = offset;
	size_t max = strlen(html);

	if(offset >= max) return -2;

	switch(*condition){
		case(HTML_FIRST):
			while(i <= max){
				if(strncmp(html + i, "<", 1) == 0){
					while(1){
						//cout << "< after looop" << endl;
						i++;
						if(strncmp(html + i, ">", 1) == 0){
						//	cout << "> hit" << endl;
							i++;
//							cout << i << endl;
							if(strncmp(html + i, "<", 1) == 0){
								SearchHtmlTag(html, i, condition);
							}else{
								return i;
							}
						}
						if(i == max){
							*condition = HTML_MID;
							return -1;
						}
					}
				}else{
					i++;
					if(i >= max) return -3;
				}
			}
			break;
		case(HTML_MID):
			while(1){
				if(strncmp(html + i, ">", 1) == 0){
					i++;
					if(strncmp(html + i, "<", 1) == 0){
						SearchHtmlTag(html, i, condition);
					}else{
						return i;
					}
				}
				i++;
			}
			break;
	}
}


int main(int argc, char **argv){
	const char * html;
	char *result;
	char tmp[100];
	list <string> res_list;
	int cnt = 0;
	int i = 0;
	int first_place = 0;
	int last_place = 0;
	int word_length = 0;
	int condition = 0;
	string word;

	html = "<html><body><p>This is a test.</p><blockquote>Here is text within a blockquote</blockquote></body></html>";
	cout << "size of html: " << strlen(html) << endl;

	condition = HTML_FIRST;
	while(i <= strlen(html)){
//		cout << "main func" << endl;
//		cout << "hit i th " <<  i << endl;
		if(strncmp(html + i, "<", 1) != 0){
			first_place = i;
			while(strncmp(html + i, " ", 1) != 0 && strncmp(html + i, "<", 1) != 0){
//				cout << html[i] << endl;
				i++;
				if(i >= strlen(html)) return 0;
			}
			//cout << "finish for" << endl;
//			cout << "first palce: "<< first_place << endl;
//			cout << "i: "<< i << endl;
			if(i - first_place < 100 && i != first_place){
				//last_place = i - 1;
				last_place = i ;
				//is alphabet or number
				if(isalnum(html[first_place]) == 0){
					first_place + 1;
				}
				if(isalnum(html[last_place - 1]) == 0){
					last_place = last_place - 1;
				}
				word_length = last_place - first_place;
				if(word_length >= 1){
					strncpy(tmp, html + first_place, word_length);
					//convert upper to lower if it is alphabet
					if(isupper(tmp[0]) != 0 && isalpha(tmp[0]) != 0) tmp[0] = tmp[0] + ('a' - 'A');
					tmp[word_length] = '\0';
					word = tmp;
				}
			}
			cout << "result: " << word << endl;
			cout << "------------------------------------" << endl;
			if(strncmp(html + i, "<", 1) != 0){
				i++;
			}
		}else{
			i = SearchHtmlTag(html, i, &condition);
			//cout << "search finish i:" << i << endl;
			if(i == -1){
				cout << "MID" << endl;
				return 0;
			}else if(i < -1){
				cout << i << endl;
				cout << "Error" << endl;
				return 0;
			}
		}
	}
	return 0;
}
