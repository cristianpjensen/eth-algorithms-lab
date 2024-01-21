#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

int floor_to_double(const CGAL::Quotient<ET> &x)
{
  int a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

struct Material {
  int required;
  int supply;
  int price;
};

void dfs(
  VVI& adj,
  VI& danger_index,
  VVI& mine_materials,
  VVI& danger_adj,
  int m,
  int danger_parent,
  int v
)
{
  int next_danger_parent = danger_parent;

  if (danger_index[v] != -1 && v != 0)
  {
    danger_adj[danger_parent].push_back(danger_index[v]);
    next_danger_parent = danger_index[v];
  }

  for (int child : adj[v])
  {
    dfs(adj, danger_index, mine_materials, danger_adj, m, next_danger_parent, child);

    // Do not add from dangerous vertices to their parent
    if (danger_index[child] != -1)
      continue;

    // Add children's mine materials to their parent
    for (int j = 0; j < m; j++)
      mine_materials[v][j] += mine_materials[child][j];
  }
}

void testcase()
{
  int n, m; std::cin >> n >> m;

  // 0 is reserved for the root
  int num_dangerous = 1;
  VI danger_index(n, -1);
  danger_index[0] = 0;

  VI danger(n);
  VVI mine_materials(n, VI(m));
  for (int i = 0; i < n; i++)
  {
    std::cin >> danger[i];

    if (danger[i] != -1)
      danger_index[i] = num_dangerous++;

    for (int j = 0; j < m; j++)
      std::cin >> mine_materials[i][j];
  }

  // Read in tree
  VVI adj(n);
  for (int i = 0; i < n-1; i++)
  {
    int u, v; std::cin >> u >> v;
    adj[v].push_back(u);
  }

  // Construct the danger mines tree graph and compute how many materials can go
  // unconstrained (i.e. no dangerous mines in between) to dangerous mines
  VVI danger_adj(num_dangerous);
  dfs(adj, danger_index, mine_materials, danger_adj, m, 0, 0);

  // Read in material requirements, and shop supply and price
  std::vector<Material> materials(m);
  for (int j = 0; j < m; j++)
  {
    Material material;
    std::cin >> material.required >> material.supply >> material.price;
    materials[j] = material;
  }

  // create an LP with Ax <= b, lower bound 0 and no upper bounds
  Program lp(CGAL::SMALLER, true, 0, false, 0); 

  int num_constraints = 0;

  // Add constraint such that the summed materials going through dangerous
  // mines is less than danger level
  for (int i = 0; i < n; i++)
  {
    int index = danger_index[i];

    // The root has no danger level
    if (index == -1 || index == 0)
      continue;

    for (int j = 0; j < m; j++)
    {
      int var_index = index * m + j;
      lp.set_a(var_index, num_constraints, 1);
    }

    lp.set_b(num_constraints, danger[i]);

    num_constraints++;
  }

  // Add constraints such that the amount going through dangerous mines (and the
  // root) is not greater than the amount that can go through it based on its
  // children's materials
  for (int i = 0; i < n; i++)
  {
    int index = danger_index[i];

    if (index == -1)
      continue;

    for (int j = 0; j < m; j++)
    {
      int var_index = index * m + j;
      lp.set_a(var_index, num_constraints, 2);

      // Also consider the dangerous mines under it
      for (auto danger_child : danger_adj[index])
      {
        int child_var_index = danger_child * m + j;
        lp.set_a(child_var_index, num_constraints, -1);
      }

      lp.set_b(num_constraints, 2 * mine_materials[i][j]);

      num_constraints++;
    }
  }

  // Make sure that the remaining materials needed are available from the shop,
  // and that we do not get more than needed
  for (int j = 0; j < m; j++)
  {
    lp.set_u(j, true, materials[j].required);
    lp.set_l(j, true, materials[j].required - materials[j].supply);
  }

  // Minimize total cost
  int price_required_sum = 0;
  for (int j = 0; j < m; j++)
  {
    lp.set_c(j, -materials[j].price);
    price_required_sum += materials[j].price * materials[j].required;
  }

  lp.set_c0(price_required_sum);

  Solution s = CGAL::solve_linear_program(lp, ET());
  
  if (s.is_infeasible())
    std::cout << "Impossible!" << std::endl;
  else
    std::cout << floor_to_double(s.objective_value()) << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  while (t--) testcase();
}
