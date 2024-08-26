import random
import heapq

class DirectedGraph:
    def __init__(self, nr_vertices, nr_edges, file_name):
        self.nr_vertices = nr_vertices
        self.nr_edges = nr_edges
        self.file_name = file_name
        self.din = {}
        self.dout = {}
        self.dcost = {}
        for i in range(self.nr_vertices):
            self.din[i] = []
            self.dout[i] = []

    def add_vertex(self, x):
        """
        Adds a vertex to the graph
        :param x: The vertex to be added
        :raises: ValueError is the vertex already exists
        """

        if not self.is_vertex(x):
            self.din[x] = []
            self.dout[x] = []
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

        if not self.is_edge(x, y):
            self.din[y].append(x)
            self.dout[x].append(y)
            self.dcost[(x, y)] = cost
        else:
            raise ValueError("Edge already exists")

    def is_vertex(self, x):
        """
        Checks if a vertex exists
        :param x: The vertex
        :return: True if the vertex exists, False otherwise
        """

        return x in self.din.keys() or x in self.dout.keys()

    def is_edge(self, x, y):
        """
        Checks if an edge exists
        :param x: The first vertex
        :param y: The second vertex
        :return: True if the edge exists, False otherwise
        """

        if self.is_vertex(x) and self.is_vertex(y):
            return x in self.din[y] and y in self.dout[x]
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
        self.din[y].remove(x)
        self.dout[x].remove(y)
        del self.dcost[(x, y)]

    def delete_vertex(self, x):
        """
        Deletes a vertex
        :param x: The vertex
        :raises: ValueError if the vertex does not exist
        """

        if not self.is_vertex(x):
            raise ValueError("Vertex does not exist")
        for y in self.din[x]:
            if self.is_edge(y, x):
                self.dout[y].remove(x)
                del self.dcost[(y, x)]
        for y in self.dout[x]:
            if self.is_edge(x, y):
                self.din[y].remove(x)
                del self.dcost[(x, y)]
        del self.din[x]
        del self.dout[x]

    def parse_nout(self, x):
        """
        Returns the outbound edges of a vertex
        :param x: The vertex
        :return: A list of outbound edges
        """
        return list(self.dout[x])

    def parse_nin(self, x):
        """
        Returns the inbound edges of a vertex
        :param x: The vertex
        :return: A list of inbound edges
        """
        return list(self.din[x])

    def parse_vertices(self):
        """
        Returns a list of all vertices
        :return: A list of all vertices
        """
        return list(self.din.keys())


def save_graph(file_name, graph):
    """
    Saves the graph to a file
    :param file_name: the name of the file
    :param graph: the graph to be saved
    """

    with open(file_name, mode='w') as file:
        for vertex in graph.parse_vertices():
            if len(graph.dout[vertex]) == 0 and len(graph.din[vertex]) == 0:
                file.write(str(vertex) + "\n")
            else:
                for neighbor in graph.parse_nout(vertex):
                    if (vertex, neighbor) in graph.dcost.keys():
                        file.write(str(vertex) + " " + str(neighbor) + " " +
                                   str(graph.dcost[(vertex, neighbor)]) + "\n")

    file.close()


def save_graph_new_file(file_name, graph):
    """
    Saves the graph to a new file and creates it
    :param file_name: the name of the file
    :param graph: the graph to be saved
    """

    try:
        with open(file_name, mode='w') as file:
            # file.write(str(len(graph.parse_vertices())) + " " + str(len(graph.dcost)) + "\n")
            for vertex in graph.parse_vertices():
                if len(graph.dout[vertex]) == 0 and len(graph.din[vertex]) == 0:
                    file.write(str(vertex) + "\n")
                else:
                    for neighbor in graph.parse_nout(vertex):
                        if (vertex, neighbor) in graph.dcost.keys():
                            file.write(
                                str(vertex) + " " + str(neighbor) + " " + str(graph.dcost[(vertex, neighbor)]) + "\n")

        file.close()
    except EOFError:
        pass
    except FileNotFoundError:
        pass

def read_vertices_edges(file_name):
    """
    Reads the number of vertices and edges from a file
    :param file_name: the name of the file
    :return: the number of vertices and edges
    """

    with open(file_name, mode='r') as file:
        nr_vertices, nr_edges = file.readline().split()
        return int(nr_vertices), int(nr_edges)

def read_graph(file_name, graph, nr_edges):
    """
    Reads the graph from a file
    :param file_name: the name of the file
    :param graph: the graph to be read
    :param nr_edges: the number of edges of the graph
    """

    with open(file_name, mode='r') as file:
        file.readline().split()
        for _ in range(int(nr_edges)):
            x, y, cost = file.readline().split()
            x, y, cost = int(x), int(y), int(cost)

            if not graph.is_vertex(x):
                graph.add_vertex(x)
            if not graph.is_vertex(y):
                graph.add_vertex(y)
            try:
                if not graph.is_edge(x, y):
                    graph.add_edge(x, y, cost)
            except ValueError:
                pass

def read_graph_from_saved_file(file_name, graph):
    """
    Reads the graph from a file with the format: vertex1 vertex2 cost or vertex if it has no edges
    :param file_name: the name of the file
    :param graph: the graph to be read
    """

    with open(file_name, mode='r') as file:
        for line in file:
            line = line.split()
            if len(line) == 1:
                vertex = int(line[0])
                if not graph.is_vertex(vertex):
                    graph.add_vertex(vertex)
            elif len(line) == 3:
                x, y, cost = int(line[0]), int(line[1]), int(line[2])
                if not graph.is_vertex(x):
                    graph.add_vertex(x)
                if not graph.is_vertex(y):
                    graph.add_vertex(y)
                graph.add_edge(x, y, cost)
    file.close()
    return graph

def create_random_graph(nr_vertices, nr_edges, file_name):
    """
    Creates a random graph and saves it to a file
    :param nr_vertices: the number of vertices
    :param nr_edges: the number of edges
    :param file_name: the name of the file to save the graph
    """

    random_graph = DirectedGraph(nr_vertices, nr_edges, file_name)

    while nr_edges > 0:
        vertex_x = random.randint(0, nr_vertices - 1)
        vertex_y = random.randint(0, nr_vertices - 1)
        cost = random.randint(-5, 100)

        if not random_graph.is_edge(vertex_x, vertex_y):
            random_graph.add_edge(vertex_x, vertex_y, cost)
            nr_edges -= 1

    save_graph_new_file(file_name, random_graph)

    return random_graph

def print_graph(graph: DirectedGraph):
    """
    Prints the graph form the file to the console
    :param graph: the graph to be printed
    """

    vertices = graph.parse_vertices()
    vertices.sort()

    for vertex in vertices:
        if len(graph.dout[vertex]) == 0 and len(graph.din[vertex]) == 0:
            print(vertex)
        else:
            for neighbour in graph.parse_nout(vertex):
                print(vertex, neighbour, graph.dcost[(vertex, neighbour)])


def backward_dijkstra(graph, t):
    """
    Returns a tuple of two dictionaries: next and dist, each having as keys all the accessible
    vertices from t and the values are: the parent (None for the root) and the distance from t
    :param graph: the graph to perform the algorithm on
    :param t: the starting vertex
    :return: the tuple of dictionaries
    """

    queue = [(0, t)]
    next = {t: None}
    dist = {t: 0}
    while queue:
        dx, x = heapq.heappop(queue)
        # parsing inbound edges
        nin = graph.parse_nin(x)
        for y in nin:
            # look for the cost from y to x
            cost = graph.dcost[(y, x)]
            if y not in next or dist[x] + cost < dist[y]:
                next[y] = x
                dist[y] = dist[x] + cost
                heapq.heappush(queue, (dist[y], y))

    return next, dist

def min_cost_path_backward_dijkstra(graph, s, t):
    """
    Returns the minimum cost path from s to t using backward Dijkstra
    :param graph: the graph to perform the algorithm on
    :param s: the starting vertex
    :param t: the ending vertex
    :return: the path as a list of vertices or None if there is no path and the cost of the path
    """

    if not graph.is_vertex(s) or not graph.is_vertex(t):
        raise ValueError("Invalid vertices")
    next, dist = backward_dijkstra(graph, t)  # start from t instead of s
    if s not in next:
        return None, None
    v = s
    result = []
    while v != t:
        result.append(v)
        v = next[v]
    result.append(t)
    result.reverse()
    return result, dist[s]
