#Ahmet Emin Kazan 19010011039
GRAPH = []

with open("C:/Users/ahmet/Desktop/Algoritmalar/GRAF.txt", "r") as file:
    data = file.readlines()
    GRAPH.append(data)

GRAPH = GRAPH[0]
print(GRAPH)

graph_size = GRAPH[0]

print("graph size : ",graph_size)

neighbor_matrix = {}
control = 0
i = 0
for g in GRAPH:
    if control == 0:
        control = 1 # ilk değer grafdaki node sayısını verdiği için listeye eklemiyoruz
        continue
    dizi = g.split(',')
    elements = [x.strip() for x in dizi if x != g[0] and x != ','] #x.strip  "\n" ifadesini siler
    #print(g)
    print(elements)
    neighbor_matrix[i] = elements
    i += 1
    
    
print(neighbor_matrix)

def convert_to_int(string_dict):
    int_dict = {}
    for key, value in string_dict.items():
        int_list = []
        for item in value:
            sub_items = item.split('-')
            int_sub_items = [int(sub_item) for sub_item in sub_items]
            int_list.append(int_sub_items)
        int_dict[key] = int_list
    return int_dict

neighbor_matrix = convert_to_int(neighbor_matrix)
print(neighbor_matrix)

class Graph:
    def __init__(self):
        self.graph = {}

    def add_vertex(self, vertex):
        if vertex not in self.graph:
            self.graph[vertex] = {}

    def add_edge(self, start_vertex, end_vertex, weight):
        if start_vertex in self.graph and end_vertex in self.graph:
            self.graph[start_vertex][end_vertex] = weight

    def get_edge_weight(self, start_vertex, end_vertex):
        if start_vertex in self.graph and end_vertex in self.graph[start_vertex]:
            return self.graph[start_vertex][end_vertex]
        else:
            return None

    def getgraph(self):
        return self.graph
        

g = Graph()

for i in range(int(graph_size)):
    g.add_vertex(i)
    
print(neighbor_matrix[0][0][1])
g.add_edge(0,neighbor_matrix[0][0][0],neighbor_matrix[0][0][1])

print(g)

print(g.get_edge_weight(0,1))

print(neighbor_matrix)
print(len(neighbor_matrix))
print(len(neighbor_matrix[0]))
print(len(neighbor_matrix[0][0]))
for i in range(len(neighbor_matrix) - 1):
    g.add_vertex(i)
    for j in range(len(neighbor_matrix[i])):
        g.add_edge(i,neighbor_matrix[i][j][0],neighbor_matrix[i][j][1])
    
# print(neighbor_matrix[0])
# print(neighbor_matrix[0][0])
# print(neighbor_matrix[0][0][0])
# print(neighbor_matrix[0][0][1])


# print(len(neighbor_matrix))
# print(len(neighbor_matrix[0]))
# print(len(neighbor_matrix[0][0]))
# print((neighbor_matrix[0][0][0]))

# print(neighbor_matrix[0])
# print(neighbor_matrix[0][0])

print(g)

graph = g.getgraph()

def dijkstra(graph, start):
    mesafeler = {}
    for node in graph:
        mesafeler[node] = float('inf')

    mesafeler[start] = 0

    unvisited = list(graph.keys())

    while unvisited:
        print("anlık mesafeler:", mesafeler)
        print("z edilmemis:", unvisited)

        min_distance = float('inf')
        min_node = None
        for node in unvisited:
            if mesafeler[node] < min_distance:
                min_distance = mesafeler[node]
                min_node = node

        # En kısa mesafeli düğümü ziyaret et
        print("gidilen:", min_node)
        unvisited.remove(min_node)
        
        for neighbor, weight in graph[min_node].items():
            new_distance = mesafeler[min_node] + weight
            if new_distance < mesafeler[neighbor]:
                mesafeler[neighbor] = new_distance

    return mesafeler

def bellman_ford(graph, kaynak):
    
    for deger in graph.values():
        if isinstance(deger, int) and deger < 0:
            print("grafda negatif deger var")
            return None
    
    mesafeler = {}
    for dugum in graph:
        mesafeler[dugum] = float("inf")
    mesafeler[kaynak] = 0

    for _ in range(len(graph) - 1):
        for dugum in graph:
            for hedef, agirlik in graph[dugum].items():
                if mesafeler[dugum] != float("inf"):
                    yeni_mesafe = mesafeler[dugum] + agirlik
                    if yeni_mesafe < mesafeler[hedef]:
                        mesafeler[hedef] = yeni_mesafe

    return mesafeler

start_node = 0

dijkstra_sonuc = dijkstra(graph, start_node)
bellman_ford_sonuc = bellman_ford(graph, start_node)

print("en kısa mesafeler: ",dijkstra_sonuc)
print("en kısa mesafeler: ",bellman_ford_sonuc)