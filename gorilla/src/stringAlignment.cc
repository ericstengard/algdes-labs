#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <set>
#include <unordered_set>
#include <cstddef>
#include <map>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <limits>
#include <iomanip>

enum AminoAcid
{
	A, R, N, D, C, Q, E, G, H, I, L, K, M, F, P, S, T, W, Y, V, B, Z, X, MINSCORE
};

class NeedlemanWunsch
{
private:

	std::string _alignment_a;
	std::string _alignment_b;
	std::string _signs;

	std::string _dna_a, _dna_b;
	size_t _length_of_a, _length_of_b;

	int **_similarity_matrix;
	int _subsitition_matrix[24][24];
	int _similarity, _gaps, _identity;
	std::map<char, int> _dna_int_map;

public:
	// Constructor and destructor.
	NeedlemanWunsch(std::string dna_a, std::string dna_b);
	~NeedlemanWunsch();

	// Necessary methods.
	void calculate_similarity();
	void populate_subs_matrix(std::string subs_matrix_file);
	void dna_align();
	void print_results();
};

NeedlemanWunsch::NeedlemanWunsch(std::string dna_a, std::string dna_b)
{
	this->_dna_a = dna_a;
	this->_dna_b = dna_b;

	this->_length_of_a = dna_a.length();
	this->_length_of_b = dna_b.length();

	this->_similarity = 0;

	this->_similarity_matrix = new int*[this->_length_of_a + 2];
	for (int i = 0; i < (this->_length_of_a + 1); i++)
	{
		this->_similarity_matrix[i] = new int[this->_length_of_b + 2];
	}

	for (int i = 0; i < _length_of_a; i++)
	{
		for (int j = 0; j < _length_of_a; j++)
		{
			_similarity_matrix[i][j] = 0;
		}
	}
}

NeedlemanWunsch::~NeedlemanWunsch()
{
	for (int i = 0; i < (_length_of_a + 2); i++)
	{
		delete[] this->_similarity_matrix[i];
	}
	delete[] this->_similarity_matrix;
}

// Calculating similarity matrix
void NeedlemanWunsch::calculate_similarity()
{
	enum AminoAcid amino = MINSCORE;
	int gap_penalty = _subsitition_matrix[0][amino];
	for (int i = 0; i < (_length_of_a + 1); i++)
	{
		_similarity_matrix[i][0] = i * gap_penalty;
	}

	for (int j = 0; j < (_length_of_a + 1); j++)
	{
		_similarity_matrix[0][j] = j * gap_penalty;
	}

	int match = 0, insert = 0, del = 0 , max = 0, selected = 0;
	for (int i = 1; i < _length_of_a + 1; i++)
	{
		for (int j = 1; j < _length_of_b + 1; j++)
		{
			match = _similarity_matrix[i - 1][j - 1] +
				_subsitition_matrix[_dna_int_map[_dna_a[i - 1] ] ][_dna_int_map[_dna_b[j - 1] ] ];
			del = _similarity_matrix[i - 1][j] + gap_penalty;
			insert = _similarity_matrix[i][j - 1] + gap_penalty;

			max = (match < del) ? del : match;
			selected = ((max < insert) ? insert : max);

			_similarity_matrix[i][j] = selected;
		}
	}
}

void NeedlemanWunsch::populate_subs_matrix(std::string subs_matrix_file)
{
	std::fstream subs_matrix;
	subs_matrix.open(subs_matrix_file.c_str());
	if (!subs_matrix)
	{
		std::cerr << "Error (3): Substition matrix file not found! \n";
		exit(3);
	}
	std::string line, parsed;
	int i = 0, j = 0;
	while (std::getline(subs_matrix, line) )
	{
		if (line[0] != '#')
		{
			std::istringstream iss(line);

			j = 0;
			while (std::getline(iss, parsed, ' '))
			{
				if (parsed != "")
				{
					if (i == 0)
					{
						_dna_int_map.insert(std::pair<char, int>(parsed[0], j));
					}
					if (j > 0 && i > 0)
					{
						_subsitition_matrix[i - 1][j - 1] = atoi(parsed.c_str());
					}
					j++;
				}
			}
			i++;
		}
	}
}

// Trace back step.
void NeedlemanWunsch::dna_align()
{
	enum AminoAcid amino = MINSCORE;
	int gap_penalty = _subsitition_matrix[0][amino];
  for(int i = 0 ; i < 24; i++){
    for(int j = 0; j < 24; j++){
      if (_subsitition_matrix[i][j] < 0){
        std::cout << _subsitition_matrix[i][j] << ", ";
      } else {std::cout << _subsitition_matrix[i][j] << ",  ";}
    }
    std::cout << '\n';
  }
	_alignment_a = "";
	_alignment_b = "";
	_signs = "";

	size_t i = _length_of_a;
	size_t j = _length_of_b;
	while (i > 0 || j > 0)
	{
		// Going to S(i-1, j-1)
		if (i > 0 && j > 0
			&& (_similarity_matrix[i][j] ==
				_similarity_matrix[i - 1][j - 1]
				+ _subsitition_matrix[_dna_int_map[_dna_a[i - 1]]][_dna_int_map[_dna_b[j - 1]]]))
		{
			_alignment_a = _dna_a[i - 1] + _alignment_a;
			_alignment_b = _dna_b[j - 1] + _alignment_b;

			if (_subsitition_matrix[_dna_int_map[_dna_a[i - 1]]][_dna_int_map[_dna_b[j - 1]]] > 0)
			{
				if (_dna_a[i - 1] != _dna_b[j - 1])
				{
					_signs = ":" + _signs;
				}
				else
				{
					_signs = "|" + _signs;
					_identity += 1;
				}
				_similarity += 1;
			}
			else
			{
				_signs = "." + _signs;
			}

			i -= 1;
			j -= 1;
		}
		// Going to S(i-1, j)
		else if (i > 0
			&& _similarity_matrix[i][j] == (_similarity_matrix[i - 1][j] + gap_penalty))
		{
			_alignment_a = _dna_a[i - 1] + _alignment_a;
			_alignment_b = '-' + _alignment_b;
			_signs = " " + _signs;
			_gaps += 1;

			i -= 1;
		}
		// Going to S(i, j-1)
		else
		{
			_alignment_a = '-' + _alignment_a;
			_alignment_b = _dna_b[j - 1] + _alignment_b;
			_signs = " " + _signs;
			_gaps += 1;

			j -= 1;
		}
	}
}

void NeedlemanWunsch::print_results()
{
	// std::cout << _similarity_matrix[102][138];
	std::cout << "\nAlignment: \n\n";
	for (size_t i = 0; i < _alignment_a.length(); i++)
	{
		std::cout << _alignment_a[i];
	}
	std::cout << "\n";

	int gaps = 0, identity = 0;
	for (size_t i = 0; i < _alignment_a.length(); i++)
	{
		std::cout << _signs[i];
	}
	std::cout << "\n";

	for (size_t i = 0; i < _alignment_b.length(); i++)
	{
		std::cout << _alignment_b[i];
	}
	std::cout << "\n";
	std::cout << std::setfill(' ') << std::setw(50) << "\n";

	double percentage;
	std::cout << "Score: " << _similarity_matrix[_length_of_a][_length_of_b] << "\n";

	std::cout << "Length: " << _alignment_a.length() << " (with gaps)\n";

	percentage = ((double)_identity / (double)_alignment_a.length()) * 100;
	std::cout << "Identity: " << _identity << "/" <<_alignment_a.length() << " ( %" << percentage << " ) " << "\n";

	percentage = ((double)_similarity / (double)_alignment_a.length()) * 100;
	std::cout << "Similarity: " << _similarity << "/" << _alignment_a.length() <<" ( %" << percentage << " ) " << "\n";

	percentage = ((double)_gaps / (double)_alignment_a.length()) * 100;
	std::cout << "Gaps: " << _gaps << "/" << _alignment_a.length() << " ( %" << percentage << " ) " << "\n";
}

int main(int argc, char **argv)
{
	// File Parsing.
	// std::fstream compare_one, compare_two;
	// if (argc != 3)
	// {
	// 	std::cout << "Warning: Using default values! \n";
	// 	compare_one.open("mouse-hemoglobin-sequence.fasta");
	// 	compare_two.open("human-hemoglobin-sequence.fasta");
	// }
	// else
	// {
	// 	compare_one.open(argv[1]);
	// 	compare_one.open(argv[2]);
	// }
  //
  //
	// if (!compare_one || !compare_two)
	// {
	// 	std::cerr << "Error (2): Necessary files not found! \n";
	// 	exit(2);
	// }

	std::string dna_a = "KQRK", dna_b = "KQRIKAAKABK", line;
	// for (int i = 0; std::getline(compare_one, line); i++)
	// {
	// 	if (i != 0)
	// 	{
	// 		dna_a += line;
	// 	}
	// }
  //
	// for (int i = 0; std::getline(compare_two, line); i++)
	// {
	// 	if (i != 0)
	// 	{
	// 		dna_b += line;
	// 	}
	// }

	// Application of algorithm.
	NeedlemanWunsch *nw = new NeedlemanWunsch(dna_a, dna_b);
  std::cout << "hej" << '\n';
	nw->populate_subs_matrix("../data/BLOSUM62.txt");
	nw->calculate_similarity();
	nw->dna_align();
	nw->print_results();
}
