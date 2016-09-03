/*
pathfinder.cpp: test implementation of Dijkstra, BFS, DFS
author: Ulrike Hager
date: August 2016

compile: g++ -Wall -std=c++11 -o pathfinder pathfinder.cpp
*/


#include <vector>
#include <string>
#include <iostream>
#include <climits>
#include <queue>
#include <stack>


struct node
{
  int index;  // this node's index in tree
  char type;  // O = open, X = blocked, T = target
  node* next;

};


class Pathfinder
{
public:
  Pathfinder(const std::vector<std::string>& board);
  ~Pathfinder();
  void print_nodes();
  void plot_board();
  void dijkstra(int r0, int c0);
  void bfs(int r0, int c0);  // breadth-first search
  void dfs(int r0, int c0);  // depth-first search
  
private:
  void add_node(const std::vector<std::string>& board, int row, int col);
  void print_track(std::vector<int> track);
  void plot_track(std::vector<int> track);
  std::vector<int> construct_track(int start, int end, int* parents);
  std::vector<node> nodes;
  int rows;
  int cols;
};



Pathfinder::Pathfinder(const std::vector<std::string>& board)
{
  if (board.size() == 0 ) {
    std::cerr << "[Pathfinder::Pathfinder] Error: empty input string\n";
    exit(1);
  }
  
  rows = board.size();
  cols = board.at(0).size();

  for ( int i = 0; i < rows ; ++i ) {
    for ( int j = 0; j < cols ; ++j ) {
      add_node(board, i, j );
    }
  }
}


Pathfinder::~Pathfinder()
{
  for ( auto n : nodes ) {
    node *temp;
    while ( n.next != nullptr ) {
      temp = n.next;
      n.next = temp->next;
      delete temp;
    }
  }
}


void
Pathfinder::add_node(const std::vector<std::string>& board, int row, int col)
{
  node to_add;
  to_add.index = row * cols + col ;
  to_add.type = board.at(row).at(col);
  to_add.next = nullptr;

  std::cout << "[Pathfinder::add_node] " << to_add.index << " at (" << row << "," << col << ")" << std::endl;;  
  if ( to_add.type != 'X'){
    int rel[] = {0, -1, 0, 1, 0};
    for ( int i = 0; i < 4; ++i ) {
      int nr = row + rel[i];
      int nc= col + rel[i+1];
      if ( nr >= 0 && nr < rows && nc >= 0 && nc < cols && board.at(nr).at(nc) != 'X' ) {
	node* nn = new node;
	nn->index = cols * nr + nc;
	nn->type = board.at(nr).at(nc);
	nn->next = to_add.next;
	to_add.next = nn;
      }
    }
  }
  std::cout << "[Pathfinder::add_node] " << to_add.index << " connected" << std::endl;  
  nodes.push_back(std::move(to_add));
  std::cout << "[Pathfinder::add_node] " << nodes.back().index << " added" << std::endl;  
}


void
Pathfinder::bfs(int r0, int c0)
{
  if ( r0 >= rows || c0 >= cols ) {
    std::cerr << "[Pathfinder::bfs] Error: Start coordinates out of bounds\n";
    return;
  }

  bool found[nodes.size()];
  int parent[nodes.size()];
  for ( int i = 0; i < nodes.size() ; ++i ) {
    found[i] = false;
    parent[i] = -1;
  }
  std::queue<int> q;
  int start = r0 * cols + c0;

  q.push(start);
  found[start] = true;
  int i = start;
  bool stop = false;
  
  while ( !q.empty() && !stop ) {
    i = q.front();
    q.pop();
    node* nn = nodes.at(i).next;
    while (nn != nullptr ) {
      if ( !found[nn->index] ) {
	found[nn->index] = true;
	parent[nn->index] = i;
	if ( nn->type == 'T' ) {
	  i = nn->index;
	  stop = true;
	  break;
	}
	q.push(nn->index);
      }
      nn = nn->next;
    }
  }

  if ( !stop ) {
    std::cerr << "[Pathfinder::bfs] Error: Unable to reach target from (" << r0 << "," << c0 << ")\n";
    return;
  }
  
  std::vector<int> track = construct_track( start, i, parent );
  std::cout << "\nbfs: \n";
  print_track(track);
  plot_track(track);
}
  

void
Pathfinder::dfs(int r0, int c0)
{
  bool found[nodes.size()];
  int parent[nodes.size()];
  for (int i = 0; i < nodes.size() ; ++i ) {
    found[i] = false;
    parent[i] = -1;
  }

  std::stack<int> s;
  int start = r0 * cols + c0;
  found[start] = true;
  int i = start;
  bool stop = false;
  s.push(i);

  while( !s.empty() && !stop ) {
    i = s.top();
    s.pop();
    node * nn = nodes.at(i).next;
    while ( nn != nullptr ) {
      if ( !found[nn->index] ) {
	found[nn->index] = true;
	parent[nn->index] = i;
	if ( nn->type == 'T' ) {
	  i = nn->index;
	  stop = true;
	  break;
	}
	s.push(nn->index);
      }
      nn = nn->next;
    }
  }
  
  if ( !stop ) {
    std::cerr << "[Pathfinder::dfs] Error: unable to reach target from (" << r0 << "," << c0 << ")\n";
    return;
  }
  std::vector<int> track = construct_track(start, i, parent);
  std::cout << "\ndfs: \n";
  print_track(track);
  plot_track(track);
}



void
Pathfinder::dijkstra(int r0, int c0)
{
  if ( r0 >= rows || c0 >= cols ) {
    std::cerr << "[Pathfinder::dijkstra] Error: Start coordinates out of bounds\n";
    return;
  }
  bool found[nodes.size()];
  int parents[nodes.size()];
  int dist[nodes.size()];
  int t = -1;
  
  for ( int i = 0; i < nodes.size() ; ++i) {
    found[i] = false;
    parents[i] = -1;
    dist[i] = INT_MAX;
  }

  int start =  r0 * cols + c0;
  int i = start;
  dist[i] = 0;

  while ( !found[i] ){
    found[i] = true;
    if ( nodes.at(i).type == 'T' ) t = i;  // found target;
    node* n = nodes.at(i).next;
    while ( n != nullptr ) {
      if ( dist[n->index] > dist[i] + 1 ) {
	dist[n->index] = dist[i] + 1;
	parents[n->index] = i;
      }
      n = n->next;
    }
    int cd = INT_MAX;
    for ( int j = 0; j < nodes.size() ; ++j ) {
      if ( !found[j] && dist[j] < cd ) {
	cd = dist[j];
	i = j;
      }
    }
  }

  if ( t == -1 || dist[t] == INT_MAX ) {
    std::cerr << "[Pathfinder::dijkstra] Error: Target impossible to reach from (" << r0 << "," << c0 <<")\n";
    return;
  }
  std::vector<int> track = construct_track(start, t, parents);
  std::cout << "\nDijkstra: \n";
  print_track(track);
  plot_track(track);
  
}



void
Pathfinder::print_nodes()
{
  for (const auto& n: nodes ) {
    std::cout << "node " << n.index << ": " << n.type << " -> ";
    node* nn = n.next;
    while ( nn != nullptr ) {
      std::cout << nn->index << " - " ;
      nn = nn->next;
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}



void
Pathfinder::plot_board()
{
  for (const auto& n: nodes ) {
    if ( n.index % cols == 0 ) std::cout << "\n";
    std::cout << n.type ;
  }
  std::cout << "\n";
}


void
Pathfinder::plot_track(std::vector<int> track)
{
  std::priority_queue<int, std::vector<int>, std::greater<int> > pq(std::greater<int>(), track);
  
  for (const auto& n: nodes ) {
    if ( n.index % cols == 0 ) std::cout << "\n";
    if ( n.index == pq.top() ) {
      pq.pop();
      if ( n.index == track.back() ) std::cout << "\033[0;36mS\033[0;37m";
      else std::cout << "\033[0;36m.\033[0;37m";
    }
    else {
      if ( n.type == 'T' ) std::cout << "\033[0;36m" << n.type << "\033[0;37m";
      else std::cout << n.type ;
    }
  }
  std::cout << "\n\n";

}


void
Pathfinder::print_track(std::vector<int> track)
{
  std::cout << "track: " ;
  for ( int i = track.size()-1 ; i >= 0 ; --i ) std::cout << track[i] << " - ";
  std::cout << "\n";
}



std::vector<int>
Pathfinder::construct_track(int start, int end, int* parents)
{
  std::vector<int>result;
  // result.push_back(end);

  while ( end != start && end != -1) {
    end = parents[end];
    result.push_back(end);
  }
  return result;
}



int main()
{
  std::vector<std::string> board = {"OTOOXOO","OXOXOOO","OOOXXXO","XOOOOXO","OXOOOOO","XXXOOOO"};
  Pathfinder pf(board);
  //  pf.print_nodes();

  pf.plot_board();
  pf.dijkstra(5, 5);
  pf.dijkstra(4, 0);

  pf.bfs(5, 5);
  pf.bfs(4, 0);
  pf.dfs(5, 5);
  pf.dfs(4, 0);
}
