#include "GraphSolver.h"
#include <pthread.h>

#ifndef NULL
#define NULL 0
#endif

int const ChunkSize = 50;

// DONE
// Verified
GraphSolver::GraphSolver(FactorGraph newGraph)
{
	UseGraph(newGraph);
}


// DONE
// Verified
int GraphSolver::ReadGraphBin()
{
	graph.ReadGraphBin();
	return UseGraph(graph);
}

// DONE
// Verified
int GraphSolver::WriteGraphBin()
{
	return graph.WriteGraphBin();
}


// DONE
// Verified
int GraphSolver::ReadGraphBin(string const & FileName)
{
	graph.ReadGraphBin(FileName);
	return UseGraph(graph);
}

// DONE
// Verified
int GraphSolver::WriteGraphBin(string const & FileName)
{
	return graph.WriteGraphBin(FileName);
}


// DONE
// Verified
int GraphSolver::ReadGraph()
{
	graph.ReadGraph();
	return UseGraph(graph);
}

// DONE
// Verified
int GraphSolver::WriteGraph()
{
	return graph.WriteGraph();
}






////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

//  __    __                       ______                                 __          ___  ___   
// |  \  |  \                     /      \                               |  \        /   \|   \
// | $$  | $$  _______   ______  |  $$$$$$\  ______    ______    ______  | $$____   /  $$$ \$$$\
// | $$  | $$ /       \ /      \ | $$ __\$$ /      \  |      \  /      \ | $$    \ |  $$     \$$\
// | $$  | $$|  $$$$$$$|  $$$$$$\| $$|    \|  $$$$$$\  \$$$$$$\|  $$$$$$\| $$$$$$$\| $$      | $$
// | $$  | $$ \$$    \ | $$    $$| $$ \$$$$| $$   \$$ /      $$| $$  | $$| $$  | $$| $$      | $$
// | $$__/ $$ _\$$$$$$\| $$$$$$$$| $$__| $$| $$      |  $$$$$$$| $$__/ $$| $$  | $$ \$$\_  _/  $$
//  \$$    $$|       $$ \$$     \ \$$    $$| $$       \$$    $$| $$    $$| $$  | $$  \$$ \|   $$ 
//   \$$$$$$  \$$$$$$$   \$$$$$$$  \$$$$$$  \$$        \$$$$$$$| $$$$$$$  \$$   \$$   \$$$ \$$$  
//                                                             | $$                              
//                                                             | $$                              
//                                                              \$$                              



// DONE
// Verified by inspection only.
int GraphSolver::UseGraph(FactorGraph newGraph)
{
	graph = newGraph;

	Var_Fn_Edge.resize( graph.variables.size() );
	Fn_Var_Edge.resize( graph.functions.size() );
	for(int i=0;i<graph.variables.size();i++)
	{
		Var_Fn_Edge[i].resize(graph.variables[i].fns.size());
	}
	for(int i=0;i<graph.functions.size();i++)
	{
		Fn_Var_Edge[i].resize(graph.functions[i].vars.size());
	}

	int EdgeCount = 0;
	for(int i=0;i<graph.functions.size();i++)
	{
		EdgeCount += graph.functions[i].vars.size();
	}

	VarOfEdge.resize(EdgeCount);
	FnOfEdge.resize(EdgeCount);

	int WhichEdge = 0;
	// go through each function node
	for(int i=0;i<graph.functions.size();i++)
	{
		// for every variable connected to that function node
		// i.e. every edge from that function node
		for(int j=0;j<graph.functions[i].vars.size();j++)
		{
			VarOfEdge[WhichEdge] = graph.functions[i].vars[j];
			FnOfEdge[WhichEdge] = i;

			int FindIndex=0;
			while( i != graph.variables[ graph.functions[i].vars[j] ].fns[FindIndex] ) FindIndex++;
			Var_Fn_Edge[ graph.functions[i].vars[j] ][ FindIndex ] = WhichEdge;
			Fn_Var_Edge[i][j] = WhichEdge;

			WhichEdge++;
		}
	}
	return 0;
}






////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

//  __    __    __      __  __  __    __
// |  \  |  \  |  \    |  \|  \|  \  |  \
// | $$  | $$ _| $$_    \$$| $$ \$$ _| $$_    __    __
// | $$  | $$|   $$ \  |  \| $$|  \|   $$ \  |  \  |  \
// | $$  | $$ \$$$$$$  | $$| $$| $$ \$$$$$$  | $$  | $$                                
// | $$  | $$  | $$ __ | $$| $$| $$  | $$ __ | $$  | $$                                
// | $$__/ $$  | $$|  \| $$| $$| $$  | $$|  \| $$__/ $$                                
//  \$$    $$   \$$  $$| $$| $$| $$   \$$  $$ \$$    $$                                
//   \$$$$$$     \$$$$  \$$ \$$ \$$    \$$$$  _\$$$$$$$                                
//                                           |  \__| $$                                
//                                            \$$    $$                                
//                                             \$$$$$$                                 
//  ________                                  __      __
// |        \                                |  \    |  \
// | $$$$$$$$ __    __  _______    _______  _| $$_    \$$  ______   _______    _______
// | $$__    |  \  |  \|       \  /       \|   $$ \  |  \ /      \ |       \  /       \
// | $$  \   | $$  | $$| $$$$$$$\|  $$$$$$$ \$$$$$$  | $$|  $$$$$$\| $$$$$$$\|  $$$$$$$
// | $$$$$   | $$  | $$| $$  | $$| $$        | $$ __ | $$| $$  | $$| $$  | $$ \$$    \
// | $$      | $$__/ $$| $$  | $$| $$_____   | $$|  \| $$| $$__/ $$| $$  | $$ _\$$$$$$\
// | $$       \$$    $$| $$  | $$ \$$     \   \$$  $$| $$ \$$    $$| $$  | $$|       $$
//  \$$        \$$$$$$  \$$   \$$  \$$$$$$$    \$$$$  \$$  \$$$$$$  \$$   \$$ \$$$$$$$ 

// DONE
// Verified by inspection only.
int GraphSolver::FullToMarginalIndex(int Fn, int Leave, int FullIndex)
{
	vector< int > D;
	D.resize(graph.functions[Fn].vars.size());
	D[0] = 1;
	for(int i=1;i<D.size();i++)
	{
		D[i] = D[i-1] * graph.variables[ graph.functions[Fn].vars[ i-1 ] ].cardinality;
	}
	int RetVal = FullIndex % D[Leave];
	if(Leave+1 < D.size())
		RetVal += D[Leave] * (FullIndex / D[Leave+1]);
	return RetVal;
}





////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

// DONE
// Verified by inspection only.
int GraphSolver::CoordsToMarginalIndex(int Fn, int Leave, vector< int > const & theCoords)
{
	int RetVal=0;
	for(int i=theCoords.size()-1;i>=0;i--)
	{
		if(i != Leave)
		{
			RetVal *= graph.variables[ graph.functions[Fn].vars[i] ].cardinality;
			RetVal += theCoords[i];
		}
	}
	return RetVal;
}





////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

// DONE
// Verified by inspection only.
int GraphSolver::CoordsToFullIndex(int Fn, vector< int > const & theCoords)
{
	int RetVal=0;
	for(int i=theCoords.size()-1;i>=0;i--)
	{
		RetVal *= graph.variables[ graph.functions[Fn].vars[i] ].cardinality;
		RetVal += theCoords[i];
	}
	return RetVal;
}





////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void GraphSolver::IncSymbols(int Fn, vector< int > & theCoords)
{
	int Index=0;
	while( Index < theCoords.size() )
	{
		theCoords[Index]++;
		theCoords[Index] %= graph.variables[ graph.functions[Fn].vars[Index] ].cardinality;
		if( theCoords[Index] != 0 ) return;
		Index++;
	}
}





////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void GraphSolver::IncSymbolsExcept(int Fn, vector< int > & theCoords, int Except)
{
	int Index=0;
	while( Index < theCoords.size() )
	{
		if(Index==Except) Index++;
		if( Index >= theCoords.size() ) return;

		theCoords[Index]++;
		theCoords[Index] %= graph.variables[ graph.functions[Fn].vars[Index] ].cardinality;
		if( theCoords[Index] != 0 ) return;
		Index++;
	}
}





////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////












