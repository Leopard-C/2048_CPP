
#include "game.h"
#include <getopt.h>
#include <cstring>
#include <iostream>
using namespace std;

const char* program_name;
char inputFile[256];
char outputFile[256];
int  prob;		// the probability generate number 2   range:[1, 10] 

void printUsageInfo(ostream& os, int exit_code);
void analyse(int argc, char* argv[]);


int main(int argc, char* argv[]) {
	prob = 6;		
	memset(inputFile, 0, sizeof(inputFile));
	memset(outputFile, 0, sizeof(outputFile));

	analyse(argc, argv);

	Game game(prob);
	game.play(inputFile, outputFile);

	return 0;
}

void analyse(int argc, char* argv[]) {
	const char* const short_opts = ":hi:o:p:";
	const struct option long_opts[] =
	{
		{ "help",        0, NULL, 'h' },
		{ "output",      1, NULL, 'o' },
		{ "probability", 1, NULL, 'p' },
		{ "input",       1, NULL, 'i' },
		{ NULL,          0, NULL,  0  }
	};

	program_name = argv[0];
	int opt = getopt_long(argc, argv, short_opts, long_opts, NULL);

	while(opt != -1) {
		switch(opt) {
			case 'h':
				printUsageInfo(cout, 0);
				break;
			case 'o':
				strcpy(outputFile, optarg);
				break;
			case 'p':
				sscanf(optarg, "%d", &prob);
				break;
			case 'i':
				strcpy(inputFile, optarg);
				break;
			case ':':					// parameter is missing
				cerr <<  program_name <<  ": option '-" << (char)optopt << "' require an argument" << endl;
				printUsageInfo(cerr, 1);
				break;
			case '?':					// unknown option
			default:
				cerr << program_name << ": option '-" << (char)optopt << "' is invalid: ignored" << endl;
				printUsageInfo(cerr, 1);
				break;
		}
		opt = getopt_long(argc, argv, short_opts, long_opts, NULL);
	}
}

void printUsageInfo(ostream& os, int exit_code) 
{
	os << "Usage:" << program_name << " options [filename]" << endl;
	os << " -h --help: Display this usage information " << endl;
	os << " -o --output filename: Save game scene to file" << endl;
	os << " -i --input filename: Load game from file" << endl;
	os << " -p --prob number: Set the probability of generate 2, range in (0, 10]" << endl;
	exit(exit_code);
}
