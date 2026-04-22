#include <stdio.h>
#include <ctype.h>
#include <string.h>

const char *keywords[] = {"int", "float", "if", "else","do","while", NULL};

int is_keyword(char *w){for(int i = 0;keywords[i];i++){if(!strcmp(w, keywords[i])){return 1;}return 0;}}
int is_op(char c){return strchr("+-*/+=<>?|!&", c); }
int is_punc(char c){return strchr("(){};.,[]", c); }

void tokenize(char *s) {
	char *p = s;
	char *start;

	while(*p) {
		// chunk = [start, p)
		start = p;

		// WHITESPACE
		if (isspace(*p)){
			while(isspace(*p)) p++;
			printf("WS\n");
		}

		// IDENTIFIERS/KEYWORDS
		else if (isalpha(*p) || *p=='_') {			
			while (isalnum(*p) || *p=='_') p++;
			
			char w[64];
			strncpy(w, start, p - start);
			w[p-start] = 0;

			printf("%s\t%s\n", is_keyword(w)? "KW" : "ID", w);
		}

		// NUMERICALS
		else if (isdigit(*p) || (*p=='-' && isdigit(*(p+1)))) {
			if (*p=='-') p++;
			while(isdigit(*p)) p++;
			if (*p=='.') {
				p++;
				while(isdigit(*p)) p++;
			}

			char w[64];
			strncpy(w, start, p - start);
			w[p-start] = 0;
			
			printf("NUM:%s\t\n", w);
		}

		// STRINGS
		else if (*p=='"') {
			p++;
			while(*p && *p!='"') p++;

			if (*p=='"') p++;
			char w[64];
			strncpy(w, start, p - start);
			w[p-start] = 0;
			
			printf("STR:%s\t\n", w);
		}

		// COMMENTS
		else if (*p=='/' && *(p+1)=='/') {
			while(*p && *p!='\n') p++;
			printf("COMMENT\n");
		}

		else if (*p=='/' && *(p+1)=='*') {
			p += 2;
			while (*p && !(*p=='*' && *(p+1) == '/')) p++;
			if (*p) p += 2;
			printf("COMMENT\n");
		}

		// OPERATORS
		else if(is_op(*p)) {
			if ((p[0]=='&' && p[1]=='&') ||
				(p[0]=='|' && p[1]=='|') || 
				(p[0]=='>' && p[1]=='=') ||
				(p[0]=='=' && p[1]=='=')) {
				printf("OP: %.*s\n", 2, p); p += 2;
			}
			else {
				printf("OP: %c\n", *p); p++;
			}
			
		}

		// PUNCTUATIONS
		else if (is_punc(*p)){printf("PUNC: %c\n", *p);p++;}

		// IDK
		else {printf("UNKNOWN: %c\n", *p);p++;}
	}
}

int main(int argc, char **argv) {
	FILE *f = fopen(argv[1], "r");
	char line[256];
	while(fgets(line, sizeof(line), f)) tokenize(line);
	fclose(f);
}