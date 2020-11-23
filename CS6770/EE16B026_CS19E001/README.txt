Input Description:
=================
The information about Classes, Properties and Individuals, required for building the Hierarchy is 
supplied from the files named Input_1.txt, Input_2.txt, etc.
Each of the file contains statements like:
	Perry isA Platypus 		Which indicates that Perry is a Platypus
	Clyde isA NOT Grey		Which indicates that Clyde is not Grey.

To check if the conclusion 'is a an x' true or false, for a hierarchy build using an Input file, 
read the values of a and x from the corresponding files named a_x_1.txt, a_x_2.txt etc.
Each a_x file contains multiple pairs of values of a and x.

Output Description:
==================
The conclusions are drawn using Skeptical Reasoning and Ideally Skeptical Reasoning. The conclusions 
to these pairs of a and x are put in a file named solutions.txt. 
Additionally, the directory is populated with a number of .PNG files containing plots for the heirarchy
and the various extensions.
In case of any error found with the values of a and/or x, the errors are also dumped in solutions.txt

Packages required:
=================
1. 	python 3.5+

2. 	sys
	This module provides access to some variables used or maintained by the interpreter and to 
	functions that interact strongly with the interpreter.
	In the program, this package helps in reading the path to the input files.

3. 	networkx - https://networkx.github.io/documentation/networkx-1.10/install.html
	NetworkX is a Python package for the creation, manipulation, and study of the structure, dynamics, 
	and functions of complex networks.
	In the program, networkx is used to create graphs, obtain the list of paths given the source and
	the target node etc.
	This package can be installed by running the following command on the terminal:
		pip install networkx

4. 	matplotlib
	Matplotlib is a comprehensive library for creating static, animated, and interactive visualizations 
	in Python.
	This library is used to display the Original input heirarchy, and its various extensions.
	This package can be installed by running the following command on the terminal:
		pip install matplotlib

How to run the program:
======================
To the input the i_th example to the program, navigate to the appropriate directory and run the following
command by substituting i with suitable value without '<' and '>' :
	make run<i>

for instance, to input the first example, run the command :
	make run1