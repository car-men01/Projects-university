import random
import sys
sys.setrecursionlimit(100000)

class UndirectedGraph:
    def __init__(self, nr_vertices, nr_edges, file_name):
        self.nr_vertices = nr_vertices
        self.nr_edges = nr_edges
        self.file_name = file_name
        self.dvert = {}
        self.dcost = {}
        for i in range(self.nr_vertices):
            self.dvert[i] = []

    def add_vertex(self, x):
        """
        Adds a vertex to the graph
        :param x: The vertex to be added
        :raises: ValueError is the vertex already exists
        """

        if not self.is_vertex(x):
            self.dvert[x] = []
        else:
            raise ValueError("Vertex already exists")

    def add_edge(self, x, y, cost):
        """
        Adds an edge to the graph
        :param x: The first vertex
        :param y: The second vertex
        :param cost: The cost of the edge
        :raises: ValueError if the edge already exists
        """
        # if x == y:
        #     raise ValueError("Cannot add an edge to the same vertex")

        if not self.is_vertex(x) or not self.is_vertex(y):
            raise ValueError("Vertex does not exist")

        if not self.is_edge(x, y) and x != y:
            self.dvert[y].append(x)
            self.dvert[x].append(y)
            self.dcost[(x, y)] = cost
            self.dcost[(y, x)] = cost
        else:
            raise ValueError("Edge already exists")

    def is_vertex(self, x):
        """
        Checks if a vertex exists
        :param x: The vertex
        :return: True if the vertex exists, False otherwise
        """

        return x in self.dvert.keys()

    def is_edge(self, x, y):
        """
        Checks if an edge exists
        :param x: The first vertex
        :param y: The second vertex
        :return: True if the edge exists, False otherwise
        """

        if self.is_vertex(x) and self.is_vertex(y):
            return x in self.dvert[y] and y in self.dvert[x]
        else:
            return False

    def delete_edge(self, x, y):
        """
        Deletes an edge
        :param x: The first vertex
        :param y: The second vertex
        :raises: ValueError if the edge does not exist
        """

        if not self.is_edge(x, y):
            raise ValueError("Edge does not exist")
        self.dvert[y].remove(x)
        self.dvert[x].remove(y)
        del self.dcost[(x, y)]
        del self.dcost[(y, x)]

    def delete_vertex(self, x):
        """
        Deletes a vertex
        :param x: The vertex
        :raises: ValueError if the vertex does not exist
        """

        if not self.is_vertex(x):
            raise ValueError("Vertex does not exist")

        for y in self.dvert[x]:
            if self.is_edge(y, x):
                self.dvert[y].remove(x)
                del self.dcost[(y, x)]
        del self.dvert[x]

    def parse_nout(self, x):
        """
        Returns the outbound edges of a vertex
        :param x: The vertex
        :return: A list of outbound edges
        """
        return list(self.dvert[x])

    def parse_nin(self, x):
        """
        Returns the inbound edges of a vertex
        :param x: The vertex
        :return: A list of inbound edges
        """
        return list(self.dvert[x])

    def parse_vertices(self):
        """
        Returns a list of all vertices
        :return: A list of all vertices
        """
        return list(self.dvert.keys())


def depth_first_search(graph, vertex, visited, component):
    """
    Depth first search algorithm for an undirected graph
    :param graph: The graph to search on
    :param vertex: The vertex to start the search from
    :param visited: The visited vertices
    :param component: The connected component
    :return:
    """
    visited[vertex] = True
    component.append(vertex)
    for neighbor in graph.parse_nin(vertex):
        if not visited[neighbor]:
            depth_first_search(graph, neighbor, visited, component)

def connected_components(graph):
    """
    Returns the connected components of a graph
    :param graph: The graph to search on
    :return: The connected components of the graph
    """
    visited = {vertex: False for vertex in graph.parse_vertices()}
    components = []
    for vertex in graph.parse_vertices():
        if not visited[vertex]:
            component = []
            depth_first_search(graph, vertex, visited, component)
            components.append(component)
    return components

def save_graph_new_file_undirected(file_name, graph):
    """
    Saves the graph to a new file and creates it
    :param file_name: the name of the file
    :param graph: the graph to be saved
    """

    try:
        with open(file_name, mode='w') as file:
            # file.write(str(len(graph.parse_vertices())) + " " + str(len(graph.dcost)) + "\n")
            for vertex in graph.parse_vertices():
                if len(graph.dvert[vertex]) == 0:
                    file.write(str(vertex) + "\n")
                else:
                    for neighbor in graph.parse_nout(vertex):
                        if neighbor > vertex:
                            if (vertex, neighbor) in graph.dcost.keys():
                                file.write(
                                    str(vertex) + " " + str(neighbor) + " " + str(graph.dcost[(vertex, neighbor)]) + "\n")

        file.close()
    except EOFError:
        pass
    except FileNotFoundError:
        pass

def print_graph_undirected(graph: UndirectedGraph):
    """
    Prints the graph form the file to the console
    :param graph: the graph to be printed
    """

    vertices = graph.parse_vertices()
    vertices.sort()

    for vertex in vertices:
        if len(graph.dvert[vertex]) == 0:
            print(vertex)
        else:
            for neighbour in graph.parse_nout(vertex):
                if neighbour > vertex:
                    print(vertex, neighbour, graph.dcost[(vertex, neighbour)])

def create_random_graph_undirected(nr_vertices, nr_edges, file_name):
    """
    Creates a random undirected graph and saves it to a file
    :param nr_vertices: the number of vertices
    :param nr_edges: the number of edges
    :param file_name: the name of the file to save the graph
    """

    random_graph = UndirectedGraph(nr_vertices, nr_edges, file_name)

    while nr_edges > 0:
        vertex_x = random.randint(0, nr_vertices - 1)
        vertex_y = random.randint(0, nr_vertices - 1)
        cost = random.randint(-5, 100)

        if not random_graph.is_edge(vertex_x, vertex_y):
            try:
                random_graph.add_edge(vertex_x, vertex_y, cost)
                nr_edges -= 1
            except ValueError:
                pass

    save_graph_new_file_undirected(file_name, random_graph)

    return random_graph


def find(parent, i):
    """
    Finds the parent of an element i
    :param parent: the parent array
    :param i: the element
    """
    if parent[i] == i:
        return i
    else:
        parent[i] = find(parent, parent[i])  # path compression step
        return parent[i]


def union(parent, rank, x, y):
    """
    Unites two sets containing elements x and y using union by rank
    :param parent: the parent array
    :param rank: the rank array
    :param x: the first element
    :param y: the second element
    """
    root_x = find(parent, x)  # Find the root of the tree containing x
    root_y = find(parent, y)  # Find the root of the tree containing y

    if root_x != root_y:
        # Attach the smaller rank tree under root of the higher rank tree
        if rank[root_x] > rank[root_y]:
            parent[root_y] = root_x
        elif rank[root_x] < rank[root_y]:
            parent[root_x] = root_y
        else:
            # If ranks are the same, make one as root and increment its rank
            parent[root_y] = root_x
            rank[root_x] += 1


def kruskal_mst(graph):
    """
    Function to find the Minimum Spanning Tree (MST) of an undirected graph using Kruskal's algorithm
    :param graph: the graph
    :return: the MST edges and the total cost
    """
    # Collect all edges from the graph with their costs
    edges = []
    for (u, v), cost in graph.dcost.items():
        if u < v:  # Ensure each edge is added only once
            edges.append((u, v, cost))

    # Sort the edges by costs
    edges.sort(key=lambda edge: edge[2])

    parent = list(range(graph.nr_vertices))
    rank = [0] * graph.nr_vertices
    mst = []
    mst_cost = 0

    # Iterate over the sorted edges and construct the MST
    for u, v, weight in edges:
        # Check if the selected edge forms a cycle
        if find(parent, u) != find(parent, v):
            union(parent, rank, u, v)
            mst.append((u, v, weight))
            mst_cost += weight

    return mst, mst_cost


def is_safe(v, graph, path, pos):
    """
    Check if the vertex v can be added at index pos in the Hamiltonian Cycle path
    :param v: the vertex to be added
    :param graph: the graph
    :param path: the path
    :param pos: the position in the path
    :return: True if the vertex can be added, False otherwise
    """
    # Check if this vertex is an adjacent vertex of the previously added vertex
    if v not in graph.parse_nout(path[pos - 1]):
        return False

    # Check if the vertex has already been included int the path
    if v in path:
        return False

    return True

def hamiltonian_cycle_util(graph, path, pos):
    """
    Utility function to find a Hamiltonian Cycle in the given undirected graph
    :param graph: the graph
    :param path: the path
    :param pos: the position in the path
    :return: True if a Hamiltonian Cycle exists, False otherwise
    """
    # Base case: If all vertices are included in the path
    if pos == graph.nr_vertices:
        # And if there is an edge from the last included vertex to the first vertex
        if path[pos - 1] in graph.parse_nout(path[0]):
            return True
        else:
            return False

    # Try different vertices as a next candidate in the Hamiltonian Cycle
    for v in range(1, graph.nr_vertices):
        if is_safe(v, graph, path, pos):
            path[pos] = v

            if hamiltonian_cycle_util(graph, path, pos + 1):
                return True

            # Remove current vertex if it doesn't lead to a solution (backtrack)
            path[pos] = -1

    return False

def find_hamiltonian_cycle(graph):
    """
    Function to find a Hamiltonian Cycle in the given undirected graph
    :param graph: the graph
    :return: the Hamiltonian Cycle path if it exists, None otherwise
    """
    path = [-1] * graph.nr_vertices

    # Put vertex 0 as the first vertex in the path.
    path[0] = 0

    if not hamiltonian_cycle_util(graph, path, 1):
        return None
    else:
        path.append(path[0])  # Add the start vertex to the path to complete the cycle
        return path
