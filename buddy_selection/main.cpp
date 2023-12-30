#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::undirectedS
> graph;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;

typedef std::vector<std::string> VS;
typedef std::vector<VS> VVS;

// Linear traversal over two sorted lists of interests.
int common_interests(VS& a, VS& b)
{
  int i = 0;
  int j = 0;
  int common = 0;

  while (i < (int) a.size() && j < (int) b.size())
  {
    if (a[i] == b[j])
    {
      common++;
      i++;
      j++;
    }
    else if (a[i] < b[j])
      i++;
    else
      j++;
  }

  return common;
}

void testcase()
{
  int n, c, f; std::cin >> n >> c >> f;

  // Read in interests O(n * c log c)
  VVS chars(n, VS(c));
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < c; j++)
      std::cin >> chars[i][j];

    // Sort such that we can linearly compare interests of two students.
    std::sort(chars[i].begin(), chars[i].end());
  }

  // Create graphs such that two vertices have an edge if the amount of common
  // interests is greater than the minimum. Then, we later check whether it is
  // possible to make a matching with this graph with all vertices. O(n^2 * c)
  graph G(n);
  for (int i = 0; i < n; i++)
    for (int j = i+1; j < n; j++)
      if (common_interests(chars[i], chars[j]) > f)
        boost::add_edge(i, j, G);

  // Find the maximum cardinality matching within the graph. O(n^3)
  std::vector<vertex_desc> mate(n);
  boost::edmonds_maximum_cardinality_matching(G, &mate[0]);
  int matching_size = boost::matching_size(G, &mate[0]);

  // If possible, output "not optimal", otherwise output "optimal".
  if (2 * matching_size == n)
    std::cout << "not optimal" << std::endl;
  else
    std::cout << "optimal" << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
