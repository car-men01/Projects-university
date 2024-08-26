from directed_graph import *
from undirected_graph import *

def print_menu():
    """
    Prints the menu of the application
    """

    print("\nGraph application menu:")
    print("1. Read the graph from a file")
    print("2. Read the graph from a saved file")
    print("3. Print the graph to the console")
    print("4. Save the graph / copy the graph to a new file")
    print("5. Create a random graph")
    print("6. Get the number of vertices")
    print("7. Parse the vertices")
    print("8. Get the number of edges")
    print("9. Check if there is an edge between two vertices")
    print("10. Get the in degree and the out degree of a vertex")
    print("11. Parse the set of inbound edges of a vertex")
    print("12. Parse the set of outbound edges of a vertex")
    print("13. Get the cost of an edge")
    print("14. Modify the cost of an edge")
    print("15. Add edge")
    print("16. Add vertex")
    print("17. Delete edge")
    print("18. Delete vertex")
    print("19. Show the connected components - undirected graph")
    print("20. Find the lowest cost walk between the given vertices using backwards Dijkstra algorithm - directed graph")
    print("21. Construct a minimal spanning tree using the Kruskal's algorithm - undirected graph")
    print("22. Find a Hamiltonian cycle (if it exists) - undirected graph")
    print("23. Exit the program")


if __name__ == '__main__':
    d = 0
    und = 0
    graph_dir = None
    graph_undir = None

    print("Welcome to the graph application!")
    print("Do you want to work with a directed graph or an undirected graph?")

    while d == 0 and und == 0:

        graph_type = input("Enter 'd' for directed graph or 'u' for undirected graph: ")
        if graph_type == 'd':
            d = 1
        elif graph_type == 'u':
            und = 1
        else:
            print("Invalid option")

    while True:
        print_menu()
        option = input("Enter an option from the menu: ")
        print("")

        try:
            option = int(option)

            if option == 1:
                file_name = input("Enter the name of the file: ")

                try:
                    nr_vertices, nr_edges = read_vertices_edges(file_name)

                    if d == 1:
                        graph_dir = DirectedGraph(nr_vertices, nr_edges, file_name)
                        read_graph(file_name, graph_dir, nr_edges)
                    if und == 1:
                        graph_undir = UndirectedGraph(nr_vertices, nr_edges, file_name)
                        read_graph(file_name, graph_undir, nr_edges)

                    print("The graph was read successfully!")
                except FileNotFoundError:
                    print(f"The file {file_name} does not exist.")

            elif option == 2:
                print("You are reading a graph from a saved file.")
                file_name = input("Enter the name of the file: ")
                try:
                    if d == 1:
                        graph_dir = DirectedGraph(0, 0, file_name)
                        graph_dir = read_graph_from_saved_file(file_name, graph_dir)
                    if und == 1:
                        graph_undir = UndirectedGraph(0, 0, file_name)
                        graph_undir = read_graph_from_saved_file(file_name, graph_undir)
                    print("The graph was read successfully!")
                except FileNotFoundError:
                    print(f"The file {file_name} does not exist.")

            elif option == 3:
                if d == 1:
                    if graph_dir is not None:
                        print("The graph is:")
                        print_graph(graph_dir)
                    else:
                        print("The graph is empty. Please read a graph first.")
                if und == 1:
                    if graph_undir is not None:
                        print("The graph is:")
                        print_graph_undirected(graph_undir)
                    else:
                        print("The graph is empty. Please read a graph first.")

            elif option == 4:
                if d == 1:
                    if graph_dir is not None:
                        copy_graph = graph_dir
                        file_name_copy = input("Enter the name of the file to save/copy of the graph: ")
                        save_graph_new_file_undirected(file_name_copy, copy_graph)
                        # print("The graph is:")
                        # print_graph(copy_graph)
                        print("The graph was saved/copied successfully!")
                    else:
                        print("The graph is empty. Please read a graph first.")
                if und == 1:
                    if graph_undir is not None:
                        copy_graph = graph_undir
                        file_name_copy = input("Enter the name of the file to save/copy of the graph: ")
                        save_graph_new_file_undirected(file_name_copy, copy_graph)
                        # print("The graph is:")
                        # print_graph(copy_graph)
                        print("The graph was saved/copied successfully!")
                    else:
                        print("The graph is empty. Please read a graph first.")

            elif option == 5:
                if d == 1:
                    print("You are creating a random directed graph.")
                    nr_vertices = input("Enter the number of vertices: ")
                    nr_edges = input("Enter the number of edges: ")
                    file_name_random = input("Enter the file name to save the random graph: ")
                    try:
                        nr_vertices = int(nr_vertices)
                        nr_edges = int(nr_edges)
                        if nr_edges > nr_vertices * nr_vertices:
                            print("The number of edges is too large.")
                        else:
                            graph_dir = create_random_graph(nr_vertices, nr_edges, file_name_random)
                            print("The graph is:")
                            print_graph(graph_dir)
                    except ValueError:
                        print("Invalid vertices")
                if und == 1:
                    print("You are creating a random undirected graph.")
                    nr_vertices = input("Enter the number of vertices: ")
                    nr_edges = input("Enter the number of edges: ")
                    file_name_random = input("Enter the file name to save the random graph: ")
                    try:
                        nr_vertices = int(nr_vertices)
                        nr_edges = int(nr_edges)
                        if nr_edges > nr_vertices * nr_vertices / 2:
                            print("The number of edges is too large.")
                        else:
                            graph_undir = create_random_graph_undirected(nr_vertices, nr_edges, file_name_random)
                            print("The graph is:")
                            print_graph_undirected(graph_undir)
                    except ValueError:
                        print("Invalid vertices")

            elif option == 6:
                if d == 1:
                    if graph_dir is not None:
                        print(f"The number of vertices is {len(graph_dir.parse_vertices())}.")
                    else:
                        print("The graph is empty. Please read a graph first.")
                if und == 1:
                    if graph_undir is not None:
                        print(f"The number of vertices is {len(graph_undir.parse_vertices())}.")
                    else:
                        print("The graph is empty. Please read a graph first.")

            elif option == 7:
                if d == 1:
                    if graph_dir is not None:
                        cont = 0
                        print("The vertices are:")
                        vertices = graph_dir.parse_vertices()
                        vertices.sort()
                        for vertex in vertices:
                            print(vertex, end=" ")
                            cont += 1
                            if cont == 20:
                                print("")
                                cont = 0
                        print("")
                    else:
                        print("The graph is empty. Please read a graph first.")
                if und == 1:
                    if graph_undir is not None:
                        cont = 0
                        print("The vertices are:")
                        vertices = graph_undir.parse_vertices()
                        vertices.sort()
                        for vertex in vertices:
                            print(vertex, end=" ")
                            cont += 1
                            if cont == 20:
                                print("")
                                cont = 0
                        print("")
                    else:
                        print("The graph is empty. Please read a graph first.")

            elif option == 8:
                if d == 1:
                    if graph_dir is not None:
                        print(f"The number of edges is {len(graph_dir.dcost.keys())}.")
                    else:
                        print("The graph is empty. Please read a graph first.")
                if und == 1:
                    if graph_undir is not None:
                        print(f"The number of edges is {len(graph_undir.dcost.keys()) // 2}.")
                    else:
                        print("The graph is empty. Please read a graph first.")

            elif option == 9:
                if d == 1:
                    if graph_dir is not None:
                        print("You are checking if there is an edge between two vertices.")
                        vertex_x = input("Enter the vertex x: ")
                        vertex_y = input("Enter the vertex y: ")
                        try:
                            vertex_x = int(vertex_x)
                            vertex_y = int(vertex_y)
                            if graph_dir.is_edge(vertex_x, vertex_y):
                                print(f"There is an edge between {vertex_x} and {vertex_y}, with the cost of "
                                      f"{graph_dir.dcost[(vertex_x, vertex_y)]}.")
                            else:
                                print(f"There is no edge between {vertex_x} and {vertex_y}.")
                        except ValueError:
                            print("Invalid vertices")
                    else:
                        print("The graph is empty. Please read a graph first.")
                if und == 1:
                    if graph_undir is not None:
                        print("You are checking if there is an edge between two vertices.")
                        vertex_x = input("Enter the vertex x: ")
                        vertex_y = input("Enter the vertex y: ")
                        try:
                            vertex_x = int(vertex_x)
                            vertex_y = int(vertex_y)
                            if graph_undir.is_edge(vertex_x, vertex_y):
                                print(f"There is an edge between {vertex_x} and {vertex_y}, with the cost of "
                                      f"{graph_undir.dcost[(vertex_x, vertex_y)]}.")
                            else:
                                print(f"There is no edge between {vertex_x} and {vertex_y}.")
                        except ValueError:
                            print("Invalid vertices")
                    else:
                        print("The graph is empty. Please read a graph first.")

            elif option == 10:
                if d == 1:
                    if graph_dir is not None:
                        print("You are getting the in degree and the out degree of a vertex.")
                        vertex = input("Enter the vertex: ")
                        try:
                            if graph_dir.is_vertex(int(vertex)):
                                vertex = int(vertex)
                                print(f"The vertex {vertex} has the in degree {len(graph_dir.din[vertex])} and the out degree "
                                      f"{len(graph_dir.dout[vertex])}.")
                            else:
                                print(f"The vertex {vertex} does not exist.")
                        except ValueError:
                            print("Invalid vertex")
                    else:
                        print("The graph is empty. Please read a graph first.")
                if und == 1:
                    if graph_undir is not None:
                        print("You are getting the degree of a vertex.")
                        vertex = input("Enter the vertex: ")
                        try:
                            if graph_undir.is_vertex(int(vertex)):
                                vertex = int(vertex)
                                print(f"The vertex {vertex} has the degree {len(graph_undir.dvert[vertex])}.")
                            else:
                                print(f"The vertex {vertex} does not exist.")
                        except ValueError:
                            print("Invalid vertex")
                    else:
                        print("The graph is empty. Please read a graph first.")

            elif option == 11:
                if d == 1:
                    if graph_dir is not None:
                        print("You are parsing the set of inbound edges of a vertex.")
                        vertex = input("Enter the vertex: ")
                        try:
                            if graph_dir.is_vertex(int(vertex)):
                                vertex = int(vertex)
                                if len(graph_dir.din[vertex]) == 0:
                                    print(f"The vertex {vertex} has no inbound edges.")
                                else:
                                    for edge in graph_dir.parse_nin(vertex):
                                        print(str(edge) + " " + str(vertex) + " " + str(graph_dir.dcost[(edge, vertex)]))
                            else:
                                print(f"The vertex {vertex} does not exist.")
                        except ValueError:
                            print("Invalid vertex")
                    else:
                        print("The graph is empty. Please read a graph first.")
                if und == 1:
                    if graph_undir is not None:
                        print("You are parsing the set of inbound edges of a vertex.")
                        vertex = input("Enter the vertex: ")
                        try:
                            if graph_undir.is_vertex(int(vertex)):
                                vertex = int(vertex)
                                if len(graph_undir.dvert[vertex]) == 0:
                                    print(f"The vertex {vertex} has no inbound edges.")
                                else:
                                    for edge in graph_undir.parse_nin(vertex):
                                        print(str(edge) + " " + str(vertex) + " " + str(graph_undir.dcost[(edge, vertex)]))
                            else:
                                print(f"The vertex {vertex} does not exist.")
                        except ValueError:
                            print("Invalid vertex")
                    else:
                        print("The graph is empty. Please read a graph first.")

            elif option == 12:
                if d == 1:
                    if graph_dir is not None:
                        print("You are parsing the set of outbound edges of a vertex.")
                        vertex = input("Enter the vertex: ")
                        try:
                            if graph_dir.is_vertex(int(vertex)):
                                vertex = int(vertex)
                                if len(graph_dir.dout[vertex]) == 0:
                                    print(f"The vertex {vertex} has no outbound edges.")
                                else:
                                    for edge in graph_dir.parse_nout(vertex):
                                        print(str(vertex) + " " + str(edge) + " " + str(graph_dir.dcost[(vertex, edge)]))
                            else:
                                print(f"The vertex {vertex} does not exist.")
                        except ValueError:
                            print("Invalid vertex")
                    else:
                        print("The graph is empty. Please read a graph first.")
                if und == 1:
                    if graph_undir is not None:
                        print("You are parsing the set of outbound edges of a vertex.")
                        vertex = input("Enter the vertex: ")
                        try:
                            if graph_undir.is_vertex(int(vertex)):
                                vertex = int(vertex)
                                if len(graph_undir.dvert[vertex]) == 0:
                                    print(f"The vertex {vertex} has no outbound edges.")
                                else:
                                    for edge in graph_undir.parse_nout(vertex):
                                        print(str(vertex) + " " + str(edge) + " " + str(graph_undir.dcost[(vertex, edge)]))
                            else:
                                print(f"The vertex {vertex} does not exist.")
                        except ValueError:
                            print("Invalid vertex")
                    else:
                        print("The graph is empty. Please read a graph first.")

            elif option == 13:
                if d == 1:
                    if graph_dir is not None:
                        print("You are getting the cost of an edge.")
                        vertex_x = input("Enter the vertex x: ")
                        vertex_y = input("Enter the vertex y: ")
                        try:
                            vertex_x = int(vertex_x)
                            vertex_y = int(vertex_y)
                            if graph_dir.is_edge(vertex_x, vertex_y):
                                print(f"The cost of the edge between {vertex_x} and {vertex_y} is "
                                      f"{graph_dir.dcost[(vertex_x, vertex_y)]}.")
                            else:
                                print(f"There is no edge between {vertex_x} and {vertex_y}.")
                        except ValueError:
                            print("Invalid vertices")
                    else:
                        print("The graph is empty. Please read a graph first.")
                if und == 1:
                    if graph_undir is not None:
                        print("You are getting the cost of an edge.")
                        vertex_x = input("Enter the vertex x: ")
                        vertex_y = input("Enter the vertex y: ")
                        try:
                            vertex_x = int(vertex_x)
                            vertex_y = int(vertex_y)
                            if graph_undir.is_edge(vertex_x, vertex_y):
                                print(f"The cost of the edge between {vertex_x} and {vertex_y} is "
                                      f"{graph_undir.dcost[(vertex_x, vertex_y)]}.")
                            else:
                                print(f"There is no edge between {vertex_x} and {vertex_y}.")
                        except ValueError:
                            print("Invalid vertices")
                    else:
                        print("The graph is empty. Please read a graph first.")

            elif option == 14:
                if d == 1:
                    if graph_dir is not None:
                        print("You are modifying the cost of an edge.")
                        vertex_x = input("Enter the vertex x: ")
                        vertex_y = input("Enter the vertex y: ")
                        cost = input("Enter the new cost: ")
                        try:
                            graph_dir.dcost[(int(vertex_x), int(vertex_y))] = int(cost)
                            # save_graph(graph.file_name, graph)
                            print("The cost was modified successfully!")
                        except ValueError:
                            print("Invalid vertices or cost.")
                    else:
                        print("The graph is empty. Please read a graph first.")
                if und == 1:
                    if graph_undir is not None:
                        print("You are modifying the cost of an edge.")
                        vertex_x = input("Enter the vertex x: ")
                        vertex_y = input("Enter the vertex y: ")
                        cost = input("Enter the new cost: ")
                        try:
                            graph_undir.dcost[(int(vertex_x), int(vertex_y))] = int(cost)
                            graph_undir.dcost[(int(vertex_y), int(vertex_x))] = int(cost)
                            # save_graph(graph.file_name, graph)
                            print("The cost was modified successfully!")
                        except ValueError:
                            print("Invalid vertices or cost.")
                    else:
                        print("The graph is empty. Please read a graph first.")

            elif option == 15:
                if d == 1:
                    if graph_dir is not None:
                        print("You are adding an edge to the graph.")
                        vertex_x = input("Enter the vertex x: ")
                        vertex_y = input("Enter the vertex y: ")
                        cost = input("Enter the cost: ")
                        try:
                            graph_dir.add_edge(int(vertex_x), int(vertex_y), int(cost))
                            # save_graph(graph.file_name, graph)
                            print("The edge was added successfully!")
                        except ValueError:
                            print("Invalid vertices or cost")
                    else:
                        print("The graph is empty. Please read a graph first.")
                if und == 1:
                    if graph_undir is not None:
                        print("You are adding an edge to the graph.")
                        vertex_x = input("Enter the vertex x: ")
                        vertex_y = input("Enter the vertex y: ")
                        cost = input("Enter the cost: ")
                        try:
                            graph_undir.add_edge(int(vertex_x), int(vertex_y), int(cost))
                            # save_graph(graph.file_name, graph)
                            print("The edge was added successfully!")
                        except ValueError:
                            print("Invalid vertices or cost")
                    else:
                        print("The graph is empty. Please read a graph first.")

            elif option == 16:
                if d == 1:
                    if graph_dir is not None:
                        print("You are adding a vertex to the graph.")
                        vertex = input("Enter the vertex: ")
                        try:
                            graph_dir.add_vertex(int(vertex))
                            # save_graph(graph_dir.file_name, graph_dir)
                            print("The vertex was added successfully!")
                        except ValueError:
                            print("Invalid vertex.")
                    else:
                        print("The graph is empty. Please read a graph first.")
                if und == 1:
                    if graph_undir is not None:
                        print("You are adding a vertex to the graph.")
                        vertex = input("Enter the vertex: ")
                        try:
                            graph_undir.add_vertex(int(vertex))
                            # save_graph(graph_dir.file_name, graph_dir)
                            print("The vertex was added successfully!")
                        except ValueError:
                            print("Invalid vertex.")
                    else:
                        print("The graph is empty. Please read a graph first.")

            elif option == 17:
                if d == 1:
                    if graph_dir is not None:
                        print("You are deleting an edge from the graph.")
                        vertex_x = input("Enter the vertex x: ")
                        vertex_y = input("Enter the vertex y: ")
                        try:
                            graph_dir.delete_edge(int(vertex_x), int(vertex_y))
                            # save_graph(graph.file_name, graph)
                            print("The edge was deleted successfully!")
                        except ValueError:
                            print("Invalid vertices.")
                    else:
                        print("The graph is empty. Please read a graph first.")
                if und == 1:
                    if graph_undir is not None:
                        print("You are deleting an edge from the graph.")
                        vertex_x = input("Enter the vertex x: ")
                        vertex_y = input("Enter the vertex y: ")
                        try:
                            graph_undir.delete_edge(int(vertex_x), int(vertex_y))
                            # save_graph(graph.file_name, graph)
                            print("The edge was deleted successfully!")
                        except ValueError:
                            print("Invalid vertices.")
                    else:
                        print("The graph is empty. Please read a graph first.")

            elif option == 18:
                if d == 1:
                    if graph_dir is not None:
                        print("You are deleting a vertex to the graph.")
                        vertex = input("Enter the vertex: ")
                        try:
                            graph_dir.delete_vertex(int(vertex))
                            # save_graph(graph.file_name, graph)
                            print("The vertex was deleted successfully!")
                        except ValueError:
                            print("Invalid vertex.")
                    else:
                        print("The graph is empty. Please read a graph first.")
                if und == 1:
                    if graph_undir is not None:
                        print("You are deleting a vertex to the graph.")
                        vertex = input("Enter the vertex: ")
                        try:
                            graph_undir.delete_vertex(int(vertex))
                            # save_graph(graph.file_name, graph)
                            print("The vertex was deleted successfully!")
                        except ValueError:
                            print("Invalid vertex.")
                    else:
                        print("The graph is empty. Please read a graph first.")

            elif option == 19:
                if und == 1:
                    if graph_undir is not None:
                        print("You are showing the connected components.")
                        connected_component = connected_components(graph_undir)
                        print("The connected components are:")
                        for component in connected_component:
                            print(component)
                    else:
                        print("The graph is empty. Please read a graph first.")
                else:
                    print("This option is only for undirected graphs.")

            elif option == 20:
                if d == 1:
                    if graph_dir is not None:
                        print("You are finding the lowest cost walk between the given vertices using backwards "
                              "Dijkstra algorithm.")
                        print("Enter the source vertex and the destination vertex:")
                        source = input("Source vertex: ")
                        destination = input("Destination vertex: ")

                        try:
                            result, cost = min_cost_path_backward_dijkstra(graph_dir, int(source), int(destination))
                            if result == "Invalid vertices":
                                print("Invalid vertices.")
                            elif result is None:
                                print(f"There is no path between {source} and {destination}.")
                            else:
                                print(f"The lowest cost walk between {source} and {destination} is: {result} "
                                      f"with the cost of {cost}.")
                        except ValueError as ve:
                            print(str(ve))

                    else:
                        print("The graph is empty. Please read a graph first.")
                else:
                    print("This option is only for directed graphs.")

            elif option == 21:
                if und == 1:
                    if graph_undir is not None:
                        print("You are constructing a minimal spanning tree using the Kruskal's algorithm")
                        try:
                            mst, mst_cost = kruskal_mst(graph_undir)
                            print("Edges sorted:")
                            for u, v, weight in mst:
                                print(f"({u}, {v}, {weight})")
                            print(f"Total cost of Minimal Spanning Tree: {mst_cost}")

                        except ValueError as ve:
                            print(str(ve))

                    else:
                        print("The graph is empty. Please read a graph first.")
                else:
                    print("This option is only for undirected graphs.")

            elif option == 22:
                if und == 1:
                    if graph_undir is not None:
                        print("You are finding a Hamiltonian cycle")
                        try:
                            cycle = find_hamiltonian_cycle(graph_undir)
                            if cycle:
                                print("Hamiltonian cycle found:")
                                print(cycle)
                            else:
                                print("No Hamiltonian cycle exists")
                        except ValueError as ve:
                            print(str(ve))
                    else:
                        print("The graph is empty. Please read a graph first.")
                else:
                    print("This option is only for undirected graphs.")

            elif option == 23:
                print("You have exited the program")
                exit()

            else:
                print("Invalid option")
                continue

        except ValueError as ve:
            print("Error. Invalid option: " + str(ve))
            continue
