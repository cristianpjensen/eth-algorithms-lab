#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

// Idea: Build a graph for max flow, such that it is constrained by the amount
// of letters and cutouts it is allowed to pick. If it can pick the maximum
// amount of letters (i.e. the length of the note), then there is a solution.

void testcase()
{
  int h, w; std::cin >> h >> w;
  std::string note; std::cin >> note;

  std::vector<std::string> front_lines(h);
  for (int i = 0; i < h; i++)
    std::cin >> front_lines[i];

  std::vector<std::string> back_lines(h);
  for (int i = 0; i < h; i++)
    std::cin >> back_lines[i];

  VI note_counts(26, 0);
  VVI cutout_counts(26, VI(26, 0));

  // Set note letter counts
  for (char letter : note)
    note_counts[letter-'A']++;

  // Set cutout counts
  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      char front = front_lines[i][j];
      char back = back_lines[i][w-j-1];

      // Make sure that the smaller letter is first, so that we do not have
      // (x,y) and (y,x) vertices.
      int a = std::min(front, back) - 'A';
      int b = std::max(front, back) - 'A';
      cutout_counts[a][b]++;
    }
  }

  graph G(26 + 26 * 26);
  edge_adder adder(G);

  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_target = boost::add_vertex(G);

  // Add edges between source and letters that denote how many letters should be
  // picked
  for (int i = 0; i < 26; i++)
    adder.add_edge(v_source, i, note_counts[i]);

  // Add edges between cutouts and target that denote how many times the cutout is
  // allowed to be picked. Also, add edges between letters and cutouts, which
  // could theoretically have infinite capacity, but they are upper-bounded by
  // the amount of times they appear in the note, so just use that.
  for (int i = 0; i < 26; i++)
  {
    for (int j = 0; j < 26; j++)
    {
      int index = 26 + (i*26 + j);
      adder.add_edge(index, v_target, cutout_counts[i][j]);
      adder.add_edge(i, index, note_counts[i]);
      adder.add_edge(j, index, note_counts[j]);
    }
  }

  int flow = boost::push_relabel_max_flow(G, v_source, v_target);
  if (flow == (int) note.size())
    std::cout << "Yes" << std::endl;
  else
    std::cout << "No" << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
