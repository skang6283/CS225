#include <queue>
#include <algorithm>
#include <string>
#include <list>

/**
 * Returns an std::list of vertex keys that creates any shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * You should use undirected edges. Hint: There are no edge weights in the Graph.
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  // TODO: Part 3
  std::list<std::string> path;

  std::unordered_map<string,string> pred;
  std::unordered_map<string, int> distance;

  //Dijkstra's algorithm
  for(auto it = vertexMap.begin(); it != vertexMap.end(); ++it){
    pred[it->first] = ""; // NULL 
    distance[it->first] = -1; // infinity
  }

  std::cout<<"start:"<<start<<std::endl;
  std::cout<<"end:"<<end<<std::endl;


  std::string current_node;
  std::string next_node;
  std::queue<string> q;
  q.push(start);
  distance[start]= 0;


  while(!q.empty()){
    current_node = q.front();
    q.pop();

    std::list<edgeListIter> temp = adjList.at(current_node);
    for(auto it: temp) {
        if((*it).get().source().key() == current_node){
          next_node = (*it).get().dest().key();
        }else{
          next_node = (*it).get().source().key();
        }
        if(distance[next_node] == -1){
          q.push(next_node);
          pred[next_node] = current_node;
          distance[next_node] = distance[current_node]+1;
        }
    }
  }

  for(auto it = pred.begin(); it != pred.end(); ++it){
    std::cout<<it->first<<it->second<<std::endl;
  }

  current_node = end;
  while(current_node != start){
    path.push_front(current_node);
    current_node = pred[current_node];
  }

  path.push_front(start);


  return path;
}
